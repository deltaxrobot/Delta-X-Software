#include "PhoneCameraDialog.h"
#include "PhoneCameraServer.h"
#include "UiTheme.h"
#include <QFutureWatcher>
#include <QNetworkInterface>
#include <QProcess>
#include <QtConcurrentRun>
#include <QtWidgets>
#include <opencv2/core/version.hpp>
#if CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && \
    (CV_VERSION_MINOR > 5 || (CV_VERSION_MINOR == 5 && CV_VERSION_REVISION >= 5)))
#include <opencv2/objdetect.hpp>
#endif

PhoneCameraDialog::PhoneCameraDialog(PhoneCameraServer* server, QWidget* parent)
    : QDialog(parent), m_server(server)
{
    setWindowTitle(tr("Phone Camera"));
    resize(500, 610);
    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    auto* intro = new QLabel(tr("Connect your phone and computer to the same Wi-Fi."));
    intro->setWordWrap(true);
    layout->addWidget(intro);
    auto* interfaces = new QComboBox(this);
    interfaces->setAccessibleName(tr("Local network"));
    interfaces->setObjectName("phoneCameraNetwork");
    int bestNetworkScore = -1;
    for (const auto& network : QNetworkInterface::allInterfaces())
    {
        if (!(network.flags() & QNetworkInterface::IsUp) ||
            network.flags() & QNetworkInterface::IsLoopBack)
            continue;
        for (const auto& entry : network.addressEntries())
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                interfaces->addItem(network.humanReadableName() + " · " + entry.ip().toString(),
                                    entry.ip().toString());
                int score = network.type() == QNetworkInterface::Wifi       ? 30
                            : network.type() == QNetworkInterface::Ethernet ? 20
                                                                            : 10;
                if (network.humanReadableName().contains(
                        QRegularExpression("tailscale|virtual|vmware|vpn|hyper-v|wsl|docker",
                                           QRegularExpression::CaseInsensitiveOption)))
                    score = 0;
                if (!(network.flags() & QNetworkInterface::IsRunning))
                    score = 0;
                if (score > bestNetworkScore)
                {
                    bestNetworkScore = score;
                    interfaces->setCurrentIndex(interfaces->count() - 1);
                }
            }
    }
    layout->addWidget(interfaces);
    auto* qr = new QLabel(tr("Start pairing to display a QR code"));
    qr->setObjectName("phoneCameraQr");
    qr->setAlignment(Qt::AlignCenter);
    qr->setMinimumSize(280, 280);
    layout->addWidget(qr, 1);
    auto* url = new QLineEdit;
    url->setReadOnly(true);
    url->setPlaceholderText(tr("Pairing address"));
    layout->addWidget(url);
    auto* status = new QLabel(tr("HTTPS Setup is required once on each phone."));
    status->setWordWrap(true);
    layout->addWidget(status);
    auto* setupToggle = new QToolButton;
    setupToggle->setText(tr("HTTPS Setup"));
    setupToggle->setCheckable(true);
    setupToggle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setupToggle->setArrowType(Qt::RightArrow);
    setupToggle->setObjectName("phoneCameraSetupToggle");
    auto* helpRow = new QHBoxLayout;
    helpRow->addWidget(setupToggle);
    helpRow->addStretch();
    auto* guide = new QPushButton(tr("Setup guide"));
    helpRow->addWidget(guide);
    layout->addLayout(helpRow);
    auto* setup = new QWidget;
    setup->setObjectName("phoneCameraSetup");
    auto* form = new QFormLayout(setup);
    form->setContentsMargins(0, 0, 0, 0);
    QSettings settings;
    auto* cert = new QLineEdit(settings.value("PhoneCamera/Certificate").toString());
    auto* key = new QLineEdit(settings.value("PhoneCamera/Key").toString());
    cert->setObjectName("phoneCameraCertificate");
    key->setObjectName("phoneCameraKey");
    auto addFile = [&](const QString& name, QLineEdit* edit)
    {
        auto* row = new QWidget;
        auto* box = new QHBoxLayout(row);
        box->setContentsMargins(0, 0, 0, 0);
        box->addWidget(edit);
        auto* browse = new QPushButton("…");
        browse->setMaximumWidth(36);
        box->addWidget(browse);
        form->addRow(name, row);
        connect(browse, &QPushButton::clicked, this,
                [=]
                {
                    const auto path = QFileDialog::getOpenFileName(
                        this, name, {}, "PEM files (*.pem *.crt *.key);;All files (*)");
                    if (!path.isEmpty())
                        edit->setText(path);
                });
    };
    addFile(tr("Certificate"), cert);
    addFile(tr("Private key"), key);
    auto* generate = new QPushButton(tr("Create local certificates"));
    form->addRow(generate);
    layout->addWidget(setup);
    connect(setupToggle, &QToolButton::toggled, this,
            [=](bool checked)
            {
                setup->setVisible(checked);
                setupToggle->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
            });
    setup->setVisible(false);
    setupToggle->setChecked(cert->text().isEmpty() || key->text().isEmpty());
    connect(guide, &QPushButton::clicked, this,
            [this]
            {
                QDialog dialog(this);
                dialog.setWindowTitle(tr("Phone Camera Setup"));
                dialog.resize(760, 650);
                auto* l = new QVBoxLayout(&dialog);
                auto* browser = new QTextBrowser;
                QFile file(":/docs/phone-camera.md");
                if (file.open(QIODevice::ReadOnly))
                    browser->setMarkdown(QString::fromUtf8(file.readAll()));
                l->addWidget(browser);
                auto* close = new QDialogButtonBox(QDialogButtonBox::Close);
                connect(close, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
                l->addWidget(close);
                dialog.exec();
            });
    connect(generate, &QPushButton::clicked, this,
            [=]
            {
                const auto openssl = QStandardPaths::findExecutable("openssl");
                if (openssl.isEmpty())
                {
                    status->setText(tr("OpenSSL was not found. Install it or select an existing "
                                       "certificate and key."));
                    return;
                }
                const QString address = interfaces->currentData().toString();
                if (address.isEmpty())
                {
                    status->setText(tr("No local IPv4 network is available."));
                    return;
                }
                const QString directory =
                    QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +
                    "/phone-camera/" + QUuid::createUuid().toString(QUuid::Id128);
                if (!QDir().mkpath(directory))
                {
                    status->setText(tr("Cannot create certificate directory."));
                    return;
                }
                generate->setEnabled(false);
                status->setText(tr("Creating certificates…"));
                auto* watcher = new QFutureWatcher<bool>(this);
                connect(watcher, &QFutureWatcher<bool>::finished, this,
                        [=]
                        {
                            const bool succeeded = watcher->result();
                            watcher->deleteLater();
                            generate->setEnabled(true);
                            if (!succeeded)
                            {
                                status->setText(tr("Certificate generation failed. Use OpenSSL "
                                                   "1.1.1+ or import existing PEM files."));
                                return;
                            }
                            cert->setText(directory + "/phone-server.crt");
                            key->setText(directory + "/phone-server.key");
                            status->setText(tr("Certificates created for %1. Install and trust "
                                               "phone-root.crt on your phone (see Setup guide).")
                                                .arg(address));
                            QDesktopServices::openUrl(QUrl::fromLocalFile(directory));
                        });
                watcher->setFuture(QtConcurrent::run(
                    [openssl, directory, address]
                    {
                        auto run = [&](QStringList args)
                        {
                            QProcess process;
                            process.setProgram(openssl);
                            process.setArguments(args);
                            process.start();
                            if (!process.waitForFinished(15000))
                            {
                                process.kill();
                                process.waitForFinished();
                                return false;
                            }
                            return process.exitStatus() == QProcess::NormalExit &&
                                   process.exitCode() == 0;
                        };
                        const auto root = directory + "/phone-root.crt",
                                   rootKey = directory + "/phone-root.key";
                        const auto leaf = directory + "/phone-server.crt",
                                   leafKey = directory + "/phone-server.key";
                        const bool ca =
                            run({"req", "-x509", "-newkey", "rsa:2048", "-nodes", "-days", "365",
                                 "-sha256", "-subj", "/CN=Delta X Phone Camera Local CA", "-addext",
                                 "basicConstraints=critical,CA:TRUE", "-addext",
                                 "keyUsage=critical,keyCertSign,cRLSign", "-keyout", rootKey,
                                 "-out", root});
                        const bool csr = ca && run({"req", "-new", "-newkey", "rsa:2048", "-nodes",
                                                    "-subj", "/CN=Delta X Phone Camera", "-keyout",
                                                    leafKey, "-out", directory + "/server.csr"});
                        QFile extensions(directory + "/server.ext");
                        bool ext = extensions.open(QIODevice::WriteOnly);
                        if (ext)
                        {
                            extensions.write(
                                ("basicConstraints=critical,CA:FALSE\nkeyUsage=critical,"
                                 "digitalSignature,keyEncipherment\nextendedKeyUsage="
                                 "serverAuth\nsubjectAltName=IP:" +
                                 address + "\n")
                                    .toUtf8());
                            extensions.close();
                        }
                        const bool signedCert =
                            csr && ext &&
                            run({"x509", "-req", "-in", directory + "/server.csr", "-CA", root,
                                 "-CAkey", rootKey, "-CAcreateserial", "-days", "90", "-sha256",
                                 "-extfile", directory + "/server.ext", "-out", leaf});
                        QFile::setPermissions(rootKey, QFile::ReadOwner | QFile::WriteOwner);
                        QFile::setPermissions(leafKey, QFile::ReadOwner | QFile::WriteOwner);
                        return signedCert;
                    }));
            });
    auto* row = new QHBoxLayout;
    auto* start = new QPushButton(tr("Start pairing"));
    start->setObjectName("phoneCameraStart");
    UiTheme::setControlRole(start, "primary");
    auto* copy = new QPushButton(tr("Copy link"));
    copy->setEnabled(false);
    auto* cancel = new QPushButton(tr("Cancel"));
    row->addWidget(start);
    row->addWidget(copy);
    row->addWidget(cancel);
    layout->addLayout(row);
    connect(copy, &QPushButton::clicked, this,
            [url] { QApplication::clipboard()->setText(url->text()); });
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(server, &PhoneCameraServer::statusChanged, status, &QLabel::setText);
    connect(server, &PhoneCameraServer::pairedChanged, this,
            [this](bool connected)
            {
                if (connected)
                    accept();
            });
    connect(start, &QPushButton::clicked, this,
            [=]
            {
                const QHostAddress address(interfaces->currentData().toString());
                if (address.isNull())
                {
                    status->setText(tr("Select an active Wi-Fi or Ethernet interface."));
                    return;
                }
                bool ok = false;
                QString error, link;
                const QString certificatePath = cert->text(), privateKeyPath = key->text();
                QMetaObject::invokeMethod(
                    m_server,
                    [&]
                    {
                        ok = m_server->start(address, 0, certificatePath, privateKeyPath, &error);
                        link = m_server->pairingUrl();
                    },
                    m_server->thread() == QThread::currentThread() ? Qt::DirectConnection
                                                                   : Qt::BlockingQueuedConnection);
                if (!ok)
                {
                    status->setText(error);
                    setupToggle->setChecked(true);
                    return;
                }
                QSettings preferences;
                preferences.setValue("PhoneCamera/Certificate", cert->text());
                preferences.setValue("PhoneCamera/Key", key->text());
                url->setText(link);
                url->setCursorPosition(0);
                copy->setEnabled(true);
                start->setText(tr("New QR"));
                setupToggle->setChecked(false);
#if CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && \
    (CV_VERSION_MINOR > 5 || (CV_VERSION_MINOR == 5 && CV_VERSION_REVISION >= 5)))
                try
                {
                    cv::Mat matrix;
                    cv::QRCodeEncoder::create()->encode(link.toStdString(), matrix);
                    QImage image(matrix.data, matrix.cols, matrix.rows, int(matrix.step),
                                 QImage::Format_Grayscale8);
                    QImage bordered(matrix.cols + 8, matrix.rows + 8, QImage::Format_RGB32);
                    bordered.fill(Qt::white);
                    QPainter painter(&bordered);
                    painter.drawImage(4, 4, image);
                    painter.end();
                    qr->setPixmap(QPixmap::fromImage(bordered).scaled(280, 280, Qt::KeepAspectRatio,
                                                                      Qt::FastTransformation));
                }
                catch (const cv::Exception&)
                {
                    qr->setText(tr("QR unavailable. Open the copied link on your phone."));
                }
#else
                qr->setText(tr("QR needs OpenCV 4.5.5+. Open the copied link on your phone."));
#endif
            });
    connect(this, &QDialog::rejected, server, &PhoneCameraServer::stop);
}
