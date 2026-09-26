#include "CameraSelectionDialog.h"
#include "UiTheme.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QCryptographicHash>
#include <QEventLoop>
#include <QRegularExpression>
#include <QSet>
#include <algorithm>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dshow.h>
#endif
#if defined(Q_OS_MACOS) && QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QPermissions>
#endif
#include <QScreen>
#include <opencv2/videoio.hpp>

namespace {
enum CameraItemRole {
    CameraIdRole = Qt::UserRole,
    CameraNameRole,
    CameraDetailsRole,
    CameraDeviceIdRole
};

struct NativeCameraInfo {
    QString name;
    QString deviceId;
};

#ifdef Q_OS_WIN
QList<NativeCameraInfo> directShowVideoInputs()
{
    QList<NativeCameraInfo> devices;
    const HRESULT initializeResult = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    const bool uninitialize = initializeResult == S_OK || initializeResult == S_FALSE;
    if (FAILED(initializeResult) && initializeResult != RPC_E_CHANGED_MODE)
        return devices;

    ICreateDevEnum* deviceEnumerator = nullptr;
    IEnumMoniker* monikerEnumerator = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER,
                                   IID_ICreateDevEnum,
                                   reinterpret_cast<void**>(&deviceEnumerator))) &&
        deviceEnumerator &&
        deviceEnumerator->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
                                                &monikerEnumerator, 0) == S_OK &&
        monikerEnumerator) {
        IMoniker* moniker = nullptr;
        while (monikerEnumerator->Next(1, &moniker, nullptr) == S_OK) {
            NativeCameraInfo info;
            IPropertyBag* properties = nullptr;
            if (SUCCEEDED(moniker->BindToStorage(nullptr, nullptr, IID_IPropertyBag,
                                                 reinterpret_cast<void**>(&properties))) &&
                properties) {
                auto readString = [properties](const wchar_t* key) {
                    VARIANT value; VariantInit(&value);
                    QString result;
                    if (SUCCEEDED(properties->Read(key, &value, nullptr)) && value.vt == VT_BSTR)
                        result = QString::fromWCharArray(value.bstrVal).trimmed();
                    VariantClear(&value);
                    return result;
                };
                info.name = readString(L"FriendlyName");
                info.deviceId = readString(L"DevicePath");
                properties->Release();
            }
            if (info.deviceId.isEmpty()) {
                IBindCtx* context = nullptr;
                LPOLESTR displayName = nullptr;
                if (SUCCEEDED(CreateBindCtx(0, &context)) && context) {
                    if (SUCCEEDED(moniker->GetDisplayName(context, nullptr, &displayName)) && displayName) {
                        info.deviceId = QString::fromWCharArray(displayName);
                        CoTaskMemFree(displayName);
                    }
                    context->Release();
                }
            }
            if (!info.name.isEmpty()) devices.append(info);
            moniker->Release();
        }
    }
    if (monikerEnumerator) monikerEnumerator->Release();
    if (deviceEnumerator) deviceEnumerator->Release();
    if (uninitialize) CoUninitialize();
    return devices;
}
#endif

QString compactDeviceIdentity(const QString& deviceId)
{
    const auto match = QRegularExpression(
        QStringLiteral("vid[_-]?([0-9a-f]{4}).*pid[_-]?([0-9a-f]{4})"),
        QRegularExpression::CaseInsensitiveOption).match(deviceId);
    if (match.hasMatch())
        return QStringLiteral("VID:PID %1:%2")
            .arg(match.captured(1).toUpper(), match.captured(2).toUpper());
    if (deviceId.isEmpty())
        return {};
    return QStringLiteral("ID %1")
        .arg(QString::fromLatin1(QCryptographicHash::hash(
            deviceId.toUtf8(), QCryptographicHash::Sha256).toHex().left(8)).toUpper());
}

QString cameraTransport(const QString& name, const QString& deviceId)
{
    const QString identity = (name + QLatin1Char(' ') + deviceId).toLower();
    if (identity.contains(QStringLiteral("virtual")) ||
        identity.contains(QStringLiteral("obs camera")) ||
        identity.contains(QStringLiteral("obs-camera")) ||
        identity.contains(QStringLiteral("snap camera")))
        return QStringLiteral("Virtual camera");
    return QStringLiteral("USB / UVC");
}

#if defined(Q_OS_MACOS) && QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
Qt::PermissionStatus ensureCameraPermission(QWidget *parent)
{
    auto *app = QCoreApplication::instance();
    if (!app)
        return Qt::PermissionStatus::Denied;

    QCameraPermission permission;
    Qt::PermissionStatus status = app->checkPermission(permission);
    qDebug() << "Camera permission status before request:" << status;
    if (status == Qt::PermissionStatus::Undetermined) {
        app->requestPermission(permission, parent, [&](const QPermission &grantedPermission) {
            qDebug() << "Camera permission callback status:" << grantedPermission.status();
        });
    }

    return status;
}
#endif
}

CameraSelectionDialog::CameraSelectionDialog(QWidget* parent, bool autoScan)
    : QDialog(parent)
    , m_mainLayout(nullptr)
    , m_titleLabel(nullptr)
    , m_cameraList(nullptr)
    , m_okButton(nullptr)
    , m_cancelButton(nullptr)
    , m_refreshButton(nullptr)
    , m_statusLabel(nullptr)
    , m_selectedCameraID(-1)
{
    setupUI();
    applyTheme();
    
    // Set dialog properties
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setModal(true);
    resize(620, 390);
    setMinimumSize(520, 320);
    
    // Center the dialog
    if (parent) {
        move(parent->geometry().center() - rect().center());
    }
    if (autoScan)
        QTimer::singleShot(0, this, &CameraSelectionDialog::loadAvailableCameras);
}

CameraSelectionDialog::~CameraSelectionDialog()
{
}

int CameraSelectionDialog::getCameraID(QWidget* parent, bool* ok)
{
#if defined(Q_OS_MACOS) && QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    const Qt::PermissionStatus permissionStatus = ensureCameraPermission(parent);
    if (permissionStatus != Qt::PermissionStatus::Granted) {
        if (ok)
            *ok = false;

        if (permissionStatus == Qt::PermissionStatus::Denied) {
            QMessageBox::warning(
                parent,
                QObject::tr("Camera Permission"),
                QObject::tr("Delta X Software does not have permission to access the camera. Please allow camera access in System Settings > Privacy & Security > Camera, then try again.")
            );
        } else {
            QMessageBox::information(
                parent,
                QObject::tr("Camera Permission"),
                QObject::tr("Delta X Software has requested camera access from macOS. Please choose Allow in the system prompt, then click Load Camera again.")
            );
        }
        return -1;
    }
#endif

    CameraSelectionDialog dialog(parent);
    
    int result = dialog.exec();
    if (ok) *ok = (result == QDialog::Accepted);
    
    return (result == QDialog::Accepted) ? dialog.getSelectedCameraID() : -1;
}

void CameraSelectionDialog::loadAvailableCameras()
{
    m_cameraList->clear();
    m_availableCameras.clear();
    m_selectedCameraID = -1;
    m_okButton->setEnabled(false);
    m_refreshButton->setEnabled(false);
    m_statusLabel->setText(tr("Scanning connected cameras…"));
    UiTheme::setStatusRole(m_statusLabel, QStringLiteral("muted"));
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    m_availableCameras = QMediaDevices::videoInputs();
#else
    m_availableCameras = QCameraInfo::availableCameras();
#endif
    qDebug() << "Qt camera enumeration found" << m_availableCameras.size() << "camera(s)";
#ifdef Q_OS_WIN
    const QList<NativeCameraInfo> nativeCameras = directShowVideoInputs();
    QSet<int> matchedNativeCameras;
    qDebug() << "DirectShow enumeration found" << nativeCameras.size() << "camera source(s)";
#endif
    
    // The selected ID is consumed by OpenCV, so enumerate verified OpenCV
    // indices. Qt Multimedia device ordering is not guaranteed to match it.
    constexpr int maxProbeIndices = 10;
    int verifiedOrdinal = 0;
    for (int i = 0; i < maxProbeIndices; ++i) {
        cv::VideoCapture probe;
        bool opened = false;
        QString backendName;
        try {
#ifdef Q_OS_WIN
            opened = probe.open(i, cv::CAP_MSMF);
            backendName = opened ? QStringLiteral("Media Foundation") : QString();
            if (!opened) {
                probe.release();
                opened = probe.open(i, cv::CAP_DSHOW);
                if (opened)
                    backendName = QStringLiteral("DirectShow");
            }
#else
            opened = probe.open(i);
            if (opened)
                backendName = QStringLiteral("OpenCV");
#endif
        } catch (const cv::Exception& error) {
            qWarning() << "USB/UVC camera probe failed for index" << i
                       << ":" << error.what();
            opened = false;
        }
        if (!opened)
            continue;
        probe.set(cv::CAP_PROP_BUFFERSIZE, 1);
        const int openedWidth = qRound(probe.get(cv::CAP_PROP_FRAME_WIDTH));
        const int openedHeight = qRound(probe.get(cv::CAP_PROP_FRAME_HEIGHT));
        const double openedFps = probe.get(cv::CAP_PROP_FPS);
        probe.release();

        QString description;
        QString deviceId;
        QString mode;
        bool isDefault = false;
        bool nativeIdentityUsed = false;
#ifdef Q_OS_WIN
        if (backendName == QStringLiteral("DirectShow") && i < nativeCameras.size()) {
            description = nativeCameras.at(i).name;
            deviceId = nativeCameras.at(i).deviceId;
            matchedNativeCameras.insert(i);
            nativeIdentityUsed = true;
        }
#endif
        if (!nativeIdentityUsed && verifiedOrdinal < m_availableCameras.size()) {
            const auto& camera = m_availableCameras.at(verifiedOrdinal);
            description = camera.description();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            deviceId = QString::fromUtf8(camera.id());
            isDefault = camera.isDefault();
            QSize bestResolution;
            qreal bestFps = 0;
            for (const auto& format : camera.videoFormats()) {
                const QSize resolution = format.resolution();
                if (qint64(resolution.width()) * resolution.height() >
                        qint64(bestResolution.width()) * bestResolution.height() ||
                    (resolution == bestResolution && format.maxFrameRate() > bestFps)) {
                    bestResolution = resolution;
                    bestFps = format.maxFrameRate();
                }
            }
            if (bestResolution.isValid())
                mode = bestFps > 0
                    ? QStringLiteral("up to %1 × %2 @ %3 fps")
                          .arg(bestResolution.width()).arg(bestResolution.height())
                          .arg(bestFps, 0, 'f', bestFps < 10 ? 1 : 0)
                    : QStringLiteral("up to %1 × %2")
                          .arg(bestResolution.width()).arg(bestResolution.height());
#else
            deviceId = camera.deviceName();
            isDefault = camera == QCameraInfo::defaultCamera();
#endif
        }
#ifdef Q_OS_WIN
        if (description.isEmpty() && i < nativeCameras.size()) {
            description = nativeCameras.at(i).name;
            deviceId = nativeCameras.at(i).deviceId;
            matchedNativeCameras.insert(i);
        }
#endif
        ++verifiedOrdinal;
        if (mode.isEmpty() && openedWidth > 0 && openedHeight > 0) {
            mode = openedFps > 0
                ? QStringLiteral("opens at %1 × %2 @ %3 fps")
                      .arg(openedWidth).arg(openedHeight).arg(openedFps, 0, 'f', openedFps < 10 ? 1 : 0)
                : QStringLiteral("opens at %1 × %2").arg(openedWidth).arg(openedHeight);
        }
        qDebug() << "Verified OpenCV camera option" << i << ":" << description
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                 << deviceId;
#else
                 << deviceId;
#endif
        
        if (description.trimmed().isEmpty())
            description = tr("USB Camera %1").arg(i);
        addCameraItem(i, description, cameraTransport(description, deviceId),
                      backendName, mode, deviceId, isDefault);
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
#ifndef Q_OS_WIN
        if (!m_availableCameras.isEmpty() && verifiedOrdinal >= m_availableCameras.size())
            break;
#else
        if (!nativeCameras.isEmpty() && i + 1 >= nativeCameras.size() &&
            verifiedOrdinal >= m_availableCameras.size())
            break;
#endif
    }

    const int verifiedCount = verifiedOrdinal;
#ifdef Q_OS_WIN
    for (int i = 0; i < nativeCameras.size(); ++i) {
        if (matchedNativeCameras.contains(i)) continue;
        const auto& camera = nativeCameras.at(i);
        addCameraItem(i, camera.name, cameraTransport(camera.name, camera.deviceId),
                      tr("Unavailable to OpenCV"), {}, camera.deviceId, false, false, i);
    }
    const int detectedCount = nativeCameras.size();
#else
    for (int i = verifiedOrdinal; i < m_availableCameras.size(); ++i) {
        const auto& camera = m_availableCameras.at(i);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        const QString deviceId = QString::fromUtf8(camera.id());
        const bool isDefault = camera.isDefault();
#else
        const QString deviceId = camera.deviceName();
        const bool isDefault = camera == QCameraInfo::defaultCamera();
#endif
        const QString name = camera.description().trimmed().isEmpty()
            ? tr("Camera device %1").arg(i + 1) : camera.description();
        addCameraItem(-1, name, cameraTransport(name, deviceId),
                      tr("Unavailable to OpenCV"), {}, deviceId, isDefault, false);
    }
    const int detectedCount = m_availableCameras.size();
#endif

    if (verifiedCount == 0) {
        m_statusLabel->setText(detectedCount == 0
            ? tr("No compatible USB/UVC camera was found")
            : tr("%1 camera(s) detected by the operating system, but none can be opened")
                  .arg(detectedCount));
        UiTheme::setStatusRole(m_statusLabel, QStringLiteral("error"));
        m_okButton->setEnabled(false);
        m_refreshButton->setEnabled(true);
        return;
    }
    
    // Select first camera by default
    if (m_cameraList->count() > 0) {
        m_cameraList->setCurrentRow(0);
        m_selectedCameraID = m_cameraList->item(0)->data(CameraIdRole).toInt();
        m_statusLabel->setText(
            tr("%1 verified camera(s) available")
                .arg(verifiedCount));
        UiTheme::setStatusRole(m_statusLabel, QStringLiteral("success"));
        m_okButton->setEnabled(true);
    }
    m_refreshButton->setEnabled(true);
}

void CameraSelectionDialog::addCameraItem(int cameraId, const QString& name,
    const QString& transport, const QString& backend, const QString& mode,
    const QString& deviceId, bool isDefault, bool available, int insertAt)
{
    QStringList details{transport};
    if (cameraId >= 0) details << tr("Camera %1").arg(cameraId);
    else details << tr("Not available to the capture backend");
    if (!mode.isEmpty()) details << mode;
    if (!backend.isEmpty()) details << backend;
    const QString identity = compactDeviceIdentity(deviceId);
    if (!identity.isEmpty()) details << identity;
    const QString detailText = details.join(QStringLiteral("  ·  "));
    const QString cameraIdText = cameraId >= 0 ? QString::number(cameraId) : tr("Not available");
    QString title = isDefault ? tr("%1  ·  Default").arg(name) : name;
    if (!available) title += tr("  ·  Unavailable");

    auto* item = new QListWidgetItem();
    item->setData(Qt::AccessibleTextRole, title + QLatin1Char('\n') + detailText);
    item->setData(CameraIdRole, cameraId);
    item->setData(CameraNameRole, name);
    item->setData(CameraDetailsRole, detailText);
    item->setData(CameraDeviceIdRole, deviceId);
    item->setSizeHint(QSize(0, 62));
    item->setToolTip(tr("%1\nType: %2\nOpenCV camera ID: %3\nBackend: %4\nMode: %5\nDevice ID: %6")
        .arg(name).arg(transport).arg(cameraIdText)
        .arg(backend.isEmpty() ? tr("Not reported") : backend)
        .arg(mode.isEmpty() ? tr("Not reported") : mode)
        .arg(deviceId.isEmpty() ? tr("Not reported") : deviceId));
    if (!available)
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    if (insertAt >= 0 && insertAt <= m_cameraList->count())
        m_cameraList->insertItem(insertAt, item);
    else
        m_cameraList->addItem(item);

    auto* row = new QWidget(m_cameraList);
    row->setAttribute(Qt::WA_TransparentForMouseEvents);
    auto* layout = new QVBoxLayout(row);
    layout->setContentsMargins(10, 7, 10, 7);
    layout->setSpacing(3);
    auto* titleLabel = new QLabel(title, row);
    QFont titleFont = titleLabel->font(); titleFont.setBold(true); titleLabel->setFont(titleFont);
    titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
    auto* detailLabel = new QLabel(detailText, row);
    QFont detailFont = detailLabel->font(); detailFont.setPointSizeF(std::max(8.0, detailFont.pointSizeF()-1));
    detailLabel->setFont(detailFont);
    detailLabel->setForegroundRole(QPalette::PlaceholderText);
    detailLabel->setTextInteractionFlags(Qt::NoTextInteraction);
    layout->addWidget(titleLabel);
    layout->addWidget(detailLabel);
    m_cameraList->setItemWidget(item, row);
}

#ifdef QT_TESTLIB_LIB
void CameraSelectionDialog::addTestCameraItem(int cameraId, const QString& name,
    const QString& transport, const QString& backend, const QString& mode,
    const QString& deviceId, bool isDefault, bool available)
{
    addCameraItem(cameraId, name, transport, backend, mode, deviceId, isDefault, available);
}
#endif

int CameraSelectionDialog::getSelectedCameraID() const
{
    return m_selectedCameraID;
}

void CameraSelectionDialog::onOkClicked()
{
    if (m_cameraList->currentItem()) {
        m_selectedCameraID = m_cameraList->currentItem()->data(CameraIdRole).toInt();
        accept();
    }
}

void CameraSelectionDialog::onCancelClicked()
{
    m_selectedCameraID = -1;
    reject();
}

void CameraSelectionDialog::onCameraItemClicked(QListWidgetItem* item)
{
    if (item) {
        m_selectedCameraID = item->data(CameraIdRole).toInt();
        m_okButton->setEnabled(true);
        
        // Update status
        m_statusLabel->setText(tr("Ready to connect: %1").arg(item->data(CameraNameRole).toString()));
        UiTheme::setStatusRole(m_statusLabel, QStringLiteral("success"));
    }
}

void CameraSelectionDialog::onCameraItemDoubleClicked(QListWidgetItem* item)
{
    onCameraItemClicked(item);
    onOkClicked();
}

void CameraSelectionDialog::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    
    createTitleBar();
    createContent();
    createButtons();
    
    setLayout(m_mainLayout);
}

void CameraSelectionDialog::createTitleBar()
{
    // Title bar
    QWidget* titleBar = new QWidget();
    titleBar->setMinimumHeight(40);
    titleBar->setObjectName("titleBar");
    
    QHBoxLayout* titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(12, 8, 12, 8);
    
    m_titleLabel = new QLabel(tr("Select Camera"));
    m_titleLabel->setObjectName("titleLabel");
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    
    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    
    m_mainLayout->addWidget(titleBar);
}

void CameraSelectionDialog::createContent()
{
    // Content area
    QWidget* contentWidget = new QWidget();
    contentWidget->setObjectName("contentWidget");
    
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(12, 10, 12, 8);
    contentLayout->setSpacing(8);
    
    // Camera list
    m_cameraList = new QListWidget();
    m_cameraList->setObjectName("cameraList");
    m_cameraList->setAlternatingRowColors(true);
    m_cameraList->setSelectionMode(QAbstractItemView::SingleSelection);
    m_cameraList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_cameraList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    connect(m_cameraList, &QListWidget::itemClicked, 
            this, &CameraSelectionDialog::onCameraItemClicked);
    connect(m_cameraList, &QListWidget::itemDoubleClicked, 
            this, &CameraSelectionDialog::onCameraItemDoubleClicked);
    
    contentLayout->addWidget(m_cameraList);
    
    // Status label
    m_statusLabel = new QLabel(tr("Scanning connected cameras…"));
    m_statusLabel->setObjectName("statusLabel");
    QFont statusFont = m_statusLabel->font();
    statusFont.setPointSize(8);
    m_statusLabel->setFont(statusFont);
    contentLayout->addWidget(m_statusLabel);
    
    m_mainLayout->addWidget(contentWidget);
}

void CameraSelectionDialog::createButtons()
{
    // Button area
    QWidget* buttonWidget = new QWidget();
    buttonWidget->setObjectName("buttonWidget");
    buttonWidget->setMinimumHeight(50);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(12, 8, 12, 8);
    buttonLayout->setSpacing(8);
    
    m_refreshButton = new QPushButton(tr("Refresh"));
    m_refreshButton->setObjectName("refreshButton");
    m_refreshButton->setMinimumSize(80, 32);
    connect(m_refreshButton, &QPushButton::clicked,
            this, &CameraSelectionDialog::loadAvailableCameras);
    buttonLayout->addWidget(m_refreshButton);

    buttonLayout->addStretch();
    
    // Cancel button
    m_cancelButton = new QPushButton(tr("Cancel"));
    m_cancelButton->setObjectName("cancelButton");
    m_cancelButton->setMinimumSize(80, 32);
    connect(m_cancelButton, &QPushButton::clicked, this, &CameraSelectionDialog::onCancelClicked);
    buttonLayout->addWidget(m_cancelButton);
    
    // OK button
    m_okButton = new QPushButton(tr("Connect"));
    m_okButton->setObjectName("okButton");
    m_okButton->setMinimumSize(80, 32);
    m_okButton->setDefault(true);
    m_okButton->setEnabled(false);
    connect(m_okButton, &QPushButton::clicked, this, &CameraSelectionDialog::onOkClicked);
    buttonLayout->addWidget(m_okButton);
    
    m_mainLayout->addWidget(buttonWidget);
}



void CameraSelectionDialog::applyTheme()
{
    setProperty("deltaDialog", true);
    setStyleSheet(QString());
    UiTheme::polishWidgetTree(this);
    
    // Add shadow effect
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(25);
    shadowEffect->setColor(QColor(0, 0, 0, 120));
    shadowEffect->setOffset(0, 8);
    setGraphicsEffect(shadowEffect);
} 
