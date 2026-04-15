#include "DeviceSimulatorWindow.h"

#include <ScurveInterpolator.h>

#include <QClipboard>
#include <QDateTime>
#include <QDesktopServices>
#include <QFile>
#include <QFrame>
#include <QFormLayout>
#include <QGuiApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRegularExpression>
#include <QScrollArea>
#include <QScreen>
#include <QSplitter>
#include <QStyle>
#include <QTabWidget>
#include <QToolButton>
#include <QTextStream>
#include <QUrl>
#include <QVBoxLayout>

#include <algorithm>
#include <cmath>

namespace {
QDoubleSpinBox *createAxisSpinBox(double minValue, double maxValue, double value, int decimals = 2)
{
    auto *spin = new QDoubleSpinBox();
    spin->setRange(minValue, maxValue);
    spin->setDecimals(decimals);
    spin->setValue(value);
    spin->setSingleStep(1.0);
    return spin;
}

QString tokenValue(const QString &token)
{
    if (token.size() <= 1)
        return QString();
    return token.mid(1);
}
}

DeviceSimulatorWindow::DeviceSimulatorWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_robotServer("robot", 8855, this)
    , m_conveyorServer("conveyor", 8856, this)
    , m_encoderServer("encoder", 8857, this)
    , m_sliderServer("slider", 8858, this)
    , m_genericServer("device", 8859, this)
    , m_robotSerial("robot", this)
    , m_conveyorSerial("conveyor", this)
    , m_encoderSerial("encoder", this)
    , m_sliderSerial("slider", this)
    , m_genericSerial("device", this)
{
    setWindowTitle("Delta X Virtual Device Simulator");
    setUnifiedTitleAndToolBarOnMac(true);
    setCentralWidget(buildCentralWidget());
    applyInitialWindowSize();

    m_robotServer.setLineHandler([this](const QString &command, ResponseSender respond) { handleRobotCommand(command, respond); });
    m_conveyorServer.setLineHandler([this](const QString &command, ResponseSender respond) { handleConveyorCommand(command, respond); });
    m_encoderServer.setLineHandler([this](const QString &command, ResponseSender respond) { handleEncoderCommand(command, respond); });
    m_sliderServer.setLineHandler([this](const QString &command, ResponseSender respond) { handleSliderCommand(command, respond); });
    m_genericServer.setLineHandler([this](const QString &command, ResponseSender respond) { handleGenericDeviceCommand(command, respond); });

    m_robotSerial.setLineHandler([this](const QString &command, ResponseSender respond) { handleRobotCommand(command, respond); });
    m_conveyorSerial.setLineHandler([this](const QString &command, ResponseSender respond) { handleConveyorCommand(command, respond); });
    m_encoderSerial.setLineHandler([this](const QString &command, ResponseSender respond) { handleEncoderCommand(command, respond); });
    m_sliderSerial.setLineHandler([this](const QString &command, ResponseSender respond) { handleSliderCommand(command, respond); });
    m_genericSerial.setLineHandler([this](const QString &command, ResponseSender respond) { handleGenericDeviceCommand(command, respond); });

    connectServer(&m_robotServer, m_robotServerWidgets);
    connectServer(&m_conveyorServer, m_conveyorServerWidgets);
    connectServer(&m_encoderServer, m_encoderServerWidgets);
    connectServer(&m_sliderServer, m_sliderServerWidgets);
    connectServer(&m_genericServer, m_genericServerWidgets);

    connect(&m_robotSerial, &VirtualSerialPort::logMessage, this, &DeviceSimulatorWindow::appendLog);
    connect(&m_conveyorSerial, &VirtualSerialPort::logMessage, this, &DeviceSimulatorWindow::appendLog);
    connect(&m_encoderSerial, &VirtualSerialPort::logMessage, this, &DeviceSimulatorWindow::appendLog);
    connect(&m_sliderSerial, &VirtualSerialPort::logMessage, this, &DeviceSimulatorWindow::appendLog);
    connect(&m_genericSerial, &VirtualSerialPort::logMessage, this, &DeviceSimulatorWindow::appendLog);

    connect(&m_simulationTimer, &QTimer::timeout, this, &DeviceSimulatorWindow::updateSimulation);
    m_simulationTimer.start(100);

    syncStateFromUi();
    appendLog("Use the Socket connection mode in Delta X Software and connect to 127.0.0.1 with the ports shown below.");
    startAllServers();
}

QWidget *DeviceSimulatorWindow::buildCentralWidget()
{
    auto *root = new QWidget(this);
    auto *rootLayout = new QVBoxLayout(root);
    rootLayout->setContentsMargins(14, 14, 14, 14);
    rootLayout->setSpacing(12);

    auto *heroCard = new QFrame();
    heroCard->setObjectName("heroCard");
    auto *headerLayout = new QVBoxLayout(heroCard);
    headerLayout->setContentsMargins(16, 16, 16, 16);
    headerLayout->setSpacing(12);

    auto *titleLabel = new QLabel("Delta X Virtual Device Simulator");
    titleLabel->setObjectName("heroTitle");
    headerLayout->addWidget(titleLabel);

    auto *hintLabel = new QLabel("Native macOS utility UI for TCP and PTY endpoints used by Delta X Software.");
    hintLabel->setObjectName("heroSubtitle");
    hintLabel->setWordWrap(true);
    headerLayout->addWidget(hintLabel);

    auto *buttonRow = new QHBoxLayout();
    buttonRow->setSpacing(8);
    auto makeToolbarButton = [this](const QString &text, QStyle::StandardPixmap iconType) {
        auto *button = new QToolButton(this);
        button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        button->setText(text);
        button->setIcon(style()->standardIcon(iconType));
        button->setAutoRaise(false);
        return button;
    };
    auto *startAllButton = makeToolbarButton("Start All", QStyle::SP_MediaPlay);
    auto *stopAllButton = makeToolbarButton("Stop All", QStyle::SP_MediaStop);
    auto *copyPathsButton = makeToolbarButton("Copy Endpoints", QStyle::SP_FileDialogDetailedView);
    auto *openMappingButton = makeToolbarButton("Open Mapping File", QStyle::SP_DirOpenIcon);
    connect(startAllButton, &QToolButton::clicked, this, &DeviceSimulatorWindow::startAllServers);
    connect(stopAllButton, &QToolButton::clicked, this, &DeviceSimulatorWindow::stopAllServers);
    connect(copyPathsButton, &QToolButton::clicked, this, &DeviceSimulatorWindow::copyEndpointSummaryToClipboard);
    connect(openMappingButton, &QToolButton::clicked, this, &DeviceSimulatorWindow::openEndpointSummaryFile);
    buttonRow->addWidget(startAllButton);
    buttonRow->addWidget(stopAllButton);
    buttonRow->addWidget(copyPathsButton);
    buttonRow->addWidget(openMappingButton);
    buttonRow->addStretch();
    headerLayout->addLayout(buttonRow);

    auto *overviewRow = new QHBoxLayout();
    overviewRow->setSpacing(10);

    auto *runtimeCard = new QFrame();
    runtimeCard->setObjectName("infoCard");
    auto *runtimeLayout = new QVBoxLayout(runtimeCard);
    runtimeLayout->setContentsMargins(12, 12, 12, 12);
    runtimeLayout->setSpacing(4);
    auto *runtimeTitle = new QLabel("Runtime Status");
    runtimeTitle->setObjectName("infoCardTitle");
    m_runtimeStatusLabel = new QLabel("-");
    m_runtimeStatusLabel->setWordWrap(true);
    runtimeLayout->addWidget(runtimeTitle);
    runtimeLayout->addWidget(m_runtimeStatusLabel);

    auto *endpointCard = new QFrame();
    endpointCard->setObjectName("infoCard");
    auto *endpointLayout = new QVBoxLayout(endpointCard);
    endpointLayout->setContentsMargins(12, 12, 12, 12);
    endpointLayout->setSpacing(4);
    auto *endpointTitle = new QLabel("Endpoint Snapshot");
    endpointTitle->setObjectName("infoCardTitle");
    m_endpointStatusLabel = new QLabel("-");
    m_endpointStatusLabel->setWordWrap(true);
    endpointLayout->addWidget(endpointTitle);
    endpointLayout->addWidget(m_endpointStatusLabel);

    overviewRow->addWidget(runtimeCard, 1);
    overviewRow->addWidget(endpointCard, 1);
    headerLayout->addLayout(overviewRow);

    rootLayout->addWidget(heroCard);

    auto *mainTabs = new QTabWidget();
    mainTabs->setDocumentMode(true);
    mainTabs->setUsesScrollButtons(true);
    mainTabs->addTab(createScrollableSection(createConnectionsPanel()), "Connections");
    mainTabs->addTab(createScrollableSection(createRobotStateGroup()), "Robot");
    mainTabs->addTab(createScrollableSection(createMotionStateGroup()), "Linear");

    m_logView = new QPlainTextEdit();
    m_logView->setReadOnly(true);
    m_logView->setMaximumBlockCount(800);
    m_logView->setPlaceholderText("Command and response log...");

    auto *logFrame = new QFrame();
    logFrame->setObjectName("logFrame");
    auto *logLayout = new QVBoxLayout(logFrame);
    logLayout->setContentsMargins(0, 0, 0, 0);
    logLayout->setSpacing(8);
    auto *logTitle = new QLabel("Activity Log");
    logTitle->setObjectName("sectionTitle");
    auto *logTitleWrap = new QWidget();
    auto *logTitleLayout = new QHBoxLayout(logTitleWrap);
    logTitleLayout->setContentsMargins(12, 12, 12, 0);
    logTitleLayout->addWidget(logTitle);
    logTitleLayout->addStretch();
    logLayout->addWidget(logTitleWrap);
    logLayout->addWidget(m_logView);

    auto *splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(mainTabs);
    splitter->addWidget(logFrame);
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);
    splitter->setStretchFactor(0, 4);
    splitter->setStretchFactor(1, 2);
    splitter->setSizes({560, 220});
    rootLayout->addWidget(splitter, 1);

    root->setStyleSheet(
        "QFrame#heroCard {"
        "  background: palette(alternate-base);"
        "  border: 1px solid palette(midlight);"
        "  border-radius: 14px;"
        "}"
        "QFrame#infoCard, QFrame#logFrame {"
        "  background: palette(base);"
        "  border: 1px solid palette(midlight);"
        "  border-radius: 12px;"
        "}"
        "QLabel#heroTitle {"
        "  font-size: 20px;"
        "  font-weight: 700;"
        "}"
        "QLabel#heroSubtitle {"
        "  color: palette(window-text);"
        "}"
        "QLabel#infoCardTitle {"
        "  color: palette(window-text);"
        "  font-size: 11px;"
        "  font-weight: 600;"
        "}"
        "QLabel#sectionTitle {"
        "  font-weight: 600;"
        "}"
        "QLabel#sectionCaption {"
        "  color: palette(window-text);"
        "}"
        "QTabWidget::pane {"
        "  border: 1px solid palette(midlight);"
        "  border-radius: 12px;"
        "  top: -1px;"
        "}"
        "QTabBar::tab {"
        "  min-width: 114px;"
        "  padding: 9px 14px;"
        "  color: white;"
        "  background: #5b6575;"
        "  border: 1px solid #4a5361;"
        "  border-bottom: none;"
        "  border-top-left-radius: 10px;"
        "  border-top-right-radius: 10px;"
        "}"
        "QTabBar::tab:selected {"
        "  background: #0a84ff;"
        "  border-color: #0a84ff;"
        "}"
        "QTabBar::tab:!selected {"
        "  margin-top: 3px;"
        "}"
        "QTabBar::tab:hover:!selected {"
        "  background: #697487;"
        "}"
        "QGroupBox {"
        "  font-weight: 600;"
        "  margin-top: 10px;"
        "  border: 1px solid palette(midlight);"
        "  border-radius: 12px;"
        "  background: palette(base);"
        "  padding: 8px;"
        "}"
        "QGroupBox::title {"
        "  subcontrol-origin: margin;"
        "  left: 10px;"
        "  padding: 0 6px 0 6px;"
        "}"
        "QPlainTextEdit {"
        "  border: 0px;"
        "  padding: 12px;"
        "  background: transparent;"
        "}"
        "QToolButton {"
        "  padding: 6px 10px;"
        "}"
        "QScrollArea {"
        "  border: none;"
        "}"
    );

    updateOverviewLabels();

    return root;
}

QWidget *DeviceSimulatorWindow::createConnectionsPanel()
{
    auto *panel = new QWidget();
    auto *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    auto *summary = new QLabel("Each device exposes both a localhost TCP endpoint and a real PTY serial path. Use the mapping file or the copy button to paste paths into Delta X Software.");
    summary->setObjectName("sectionCaption");
    summary->setWordWrap(true);
    layout->addWidget(summary);

    auto *serversLayout = new QGridLayout();
    serversLayout->setHorizontalSpacing(10);
    serversLayout->setVerticalSpacing(10);
    serversLayout->addWidget(createServerGroup(&m_robotServer, m_robotServerWidgets), 0, 0);
    serversLayout->addWidget(createServerGroup(&m_conveyorServer, m_conveyorServerWidgets), 0, 1);
    serversLayout->addWidget(createServerGroup(&m_encoderServer, m_encoderServerWidgets), 1, 0);
    serversLayout->addWidget(createServerGroup(&m_sliderServer, m_sliderServerWidgets), 1, 1);
    serversLayout->addWidget(createServerGroup(&m_genericServer, m_genericServerWidgets), 2, 0, 1, 2);
    layout->addLayout(serversLayout);
    layout->addStretch();

    return panel;
}

QScrollArea *DeviceSimulatorWindow::createScrollableSection(QWidget *content) const
{
    auto *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidget(content);
    return scrollArea;
}

void DeviceSimulatorWindow::applyInitialWindowSize()
{
    setMinimumSize(880, 640);

    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect available = screen->availableGeometry();
        const int width = std::min(1100, std::max(880, static_cast<int>(available.width() * 0.64)));
        const int height = std::min(860, std::max(640, static_cast<int>(available.height() * 0.8)));
        resize(width, height);
    } else {
        resize(980, 740);
    }
}

void DeviceSimulatorWindow::updateOverviewLabels()
{
    const int tcpReadyCount = (m_robotServer.isListening() ? 1 : 0) +
                              (m_conveyorServer.isListening() ? 1 : 0) +
                              (m_encoderServer.isListening() ? 1 : 0) +
                              (m_sliderServer.isListening() ? 1 : 0) +
                              (m_genericServer.isListening() ? 1 : 0);
    const int serialReadyCount = (m_robotSerial.isOpen() ? 1 : 0) +
                                 (m_conveyorSerial.isOpen() ? 1 : 0) +
                                 (m_encoderSerial.isOpen() ? 1 : 0) +
                                 (m_sliderSerial.isOpen() ? 1 : 0) +
                                 (m_genericSerial.isOpen() ? 1 : 0);
    const int clientCount = m_robotServer.clientCount() +
                            m_conveyorServer.clientCount() +
                            m_encoderServer.clientCount() +
                            m_sliderServer.clientCount() +
                            m_genericServer.clientCount();

    if (m_runtimeStatusLabel) {
        m_runtimeStatusLabel->setText(
            QString("%1/5 TCP ready, %2/5 PTY ready, %3 active client(s).")
                .arg(tcpReadyCount)
                .arg(serialReadyCount)
                .arg(clientCount));
    }

    if (m_endpointStatusLabel) {
        m_endpointStatusLabel->setText(
            QString("Robot %1 • Encoder %2 • Slider %3")
                .arg(m_robotSerial.slavePath().isEmpty() ? QStringLiteral("-") : m_robotSerial.slavePath())
                .arg(m_encoderSerial.slavePath().isEmpty() ? QStringLiteral("-") : m_encoderSerial.slavePath())
                .arg(m_sliderSerial.slavePath().isEmpty() ? QStringLiteral("-") : m_sliderSerial.slavePath()));
    }
}

QGroupBox *DeviceSimulatorWindow::createServerGroup(VirtualDeviceServer *server, ServerWidgets &widgets)
{
    auto *group = new QGroupBox(QString("%1 server").arg(server->deviceName()));
    auto *layout = new QVBoxLayout(group);
    layout->setSpacing(8);
    group->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    auto *form = new QFormLayout();
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    form->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    widgets.portSpin = new QSpinBox();
    widgets.portSpin->setRange(1, 65535);
    widgets.portSpin->setValue(server->defaultPort());
    widgets.statusLabel = new QLabel("Stopped");
    widgets.clientsLabel = new QLabel("0 clients");

    form->addRow("Port", widgets.portSpin);
    form->addRow("TCP status", widgets.statusLabel);
    form->addRow("TCP clients", widgets.clientsLabel);
    widgets.serialStatusLabel = new QLabel("Stopped");
    widgets.serialPathLabel = new QLabel("-");
    widgets.serialPathLabel->setWordWrap(true);
    widgets.serialPathLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    form->addRow("Serial status", widgets.serialStatusLabel);
    form->addRow("Serial path", widgets.serialPathLabel);
    layout->addLayout(form);

    widgets.toggleButton = new QPushButton("Start");
    layout->addWidget(widgets.toggleButton);

    connect(widgets.toggleButton, &QPushButton::clicked, this, [this, server, &widgets]() {
        VirtualSerialPort *serial = nullptr;
        if (server == &m_robotServer) serial = &m_robotSerial;
        if (server == &m_conveyorServer) serial = &m_conveyorSerial;
        if (server == &m_encoderServer) serial = &m_encoderSerial;
        if (server == &m_sliderServer) serial = &m_sliderSerial;
        if (server == &m_genericServer) serial = &m_genericSerial;

        if (server->isListening()) {
            server->stop();
            if (serial)
                serial->stop();
        } else {
            server->start(static_cast<quint16>(widgets.portSpin->value()));
            if (serial)
                serial->start();
        }
        updateServerWidgets(server, widgets);
    });

    updateServerWidgets(server, widgets);
    return group;
}

QGroupBox *DeviceSimulatorWindow::createRobotStateGroup()
{
    auto *group = new QGroupBox("Robot state");
    auto *layout = new QFormLayout(group);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_robotXSpin = createAxisSpinBox(-10000.0, 10000.0, m_robotState.x);
    m_robotYSpin = createAxisSpinBox(-10000.0, 10000.0, m_robotState.y);
    m_robotZSpin = createAxisSpinBox(-10000.0, 10000.0, m_robotState.z);
    m_robotWSpin = createAxisSpinBox(-360.0, 360.0, m_robotState.w);
    m_robotUSpin = createAxisSpinBox(-360.0, 360.0, m_robotState.u);
    m_robotVSpin = createAxisSpinBox(-360.0, 360.0, m_robotState.v);
    m_robotFSpin = createAxisSpinBox(0.0, 200000.0, m_robotState.f);
    m_robotASpin = createAxisSpinBox(0.0, 500000.0, m_robotState.a);
    m_robotSSpin = createAxisSpinBox(0.0, 200000.0, m_robotState.s);
    m_robotESpin = createAxisSpinBox(0.0, 200000.0, m_robotState.e);
    m_robotJSpin = createAxisSpinBox(0.0, 1000000.0, m_robotState.j);
    m_robotOutputEnabled = new QCheckBox("Output enabled");
    m_robotOutputValueSpin = new QSpinBox();
    m_robotOutputValueSpin->setRange(0, 999999);

    layout->addRow("X", m_robotXSpin);
    layout->addRow("Y", m_robotYSpin);
    layout->addRow("Z", m_robotZSpin);
    layout->addRow("W", m_robotWSpin);
    layout->addRow("U", m_robotUSpin);
    layout->addRow("V", m_robotVSpin);
    layout->addRow("F", m_robotFSpin);
    layout->addRow("A", m_robotASpin);
    layout->addRow("S", m_robotSSpin);
    layout->addRow("E", m_robotESpin);
    layout->addRow("J", m_robotJSpin);
    layout->addRow(m_robotOutputEnabled);
    layout->addRow("Output value", m_robotOutputValueSpin);

    auto *resetButton = new QPushButton("Home Robot");
    connect(resetButton, &QPushButton::clicked, this, [this]() {
        m_robotXSpin->setValue(0.0);
        m_robotYSpin->setValue(0.0);
        m_robotZSpin->setValue(0.0);
        m_robotWSpin->setValue(0.0);
        m_robotUSpin->setValue(0.0);
        m_robotVSpin->setValue(0.0);
        syncStateFromUi();
        appendLog("[robot] state reset to home");
    });
    layout->addRow(resetButton);

    const QList<QObject *> robotInputs = {
        m_robotXSpin, m_robotYSpin, m_robotZSpin, m_robotWSpin, m_robotUSpin, m_robotVSpin,
        m_robotFSpin, m_robotASpin, m_robotSSpin, m_robotESpin, m_robotJSpin,
        m_robotOutputEnabled, m_robotOutputValueSpin
    };
    for (QObject *input : robotInputs) {
        if (auto *spin = qobject_cast<QDoubleSpinBox *>(input)) {
            connect(spin, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &DeviceSimulatorWindow::syncStateFromUi);
        } else if (auto *intSpin = qobject_cast<QSpinBox *>(input)) {
            connect(intSpin, qOverload<int>(&QSpinBox::valueChanged), this, &DeviceSimulatorWindow::syncStateFromUi);
        } else if (auto *check = qobject_cast<QCheckBox *>(input)) {
            connect(check, &QCheckBox::toggled, this, &DeviceSimulatorWindow::syncStateFromUi);
        }
    }

    return group;
}

QGroupBox *DeviceSimulatorWindow::createMotionStateGroup()
{
    auto *group = new QGroupBox("Linear devices");
    auto *layout = new QFormLayout(group);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_conveyorPositionSpin = createAxisSpinBox(-1000000.0, 1000000.0, m_conveyorState.position, 3);
    m_conveyorSpeedSpin = createAxisSpinBox(-50000.0, 50000.0, m_conveyorState.speed, 3);
    m_conveyorRunningCheck = new QCheckBox("Conveyor running");

    m_encoderPositionSpin = createAxisSpinBox(-1000000.0, 1000000.0, m_encoderState.position, 3);
    m_encoderSpeedSpin = createAxisSpinBox(-50000.0, 50000.0, m_encoderState.speed, 3);
    m_encoderRunningCheck = new QCheckBox("Encoder running");
    m_encoderFollowConveyorCheck = new QCheckBox("Encoder follows conveyor");
    m_encoderFollowConveyorCheck->setChecked(true);

    m_sliderPositionSpin = createAxisSpinBox(-1000000.0, 1000000.0, m_sliderState.position, 3);
    m_sliderSpeedSpin = createAxisSpinBox(-50000.0, 50000.0, m_sliderState.speed, 3);
    m_sliderRunningCheck = new QCheckBox("Slider running");

    layout->addRow("Conveyor position", m_conveyorPositionSpin);
    layout->addRow("Conveyor speed", m_conveyorSpeedSpin);
    layout->addRow(m_conveyorRunningCheck);
    layout->addRow("Encoder position", m_encoderPositionSpin);
    layout->addRow("Encoder speed", m_encoderSpeedSpin);
    layout->addRow(m_encoderRunningCheck);
    layout->addRow(m_encoderFollowConveyorCheck);
    layout->addRow("Slider position", m_sliderPositionSpin);
    layout->addRow("Slider speed", m_sliderSpeedSpin);
    layout->addRow(m_sliderRunningCheck);

    auto *resetMotionButton = new QPushButton("Reset Linear State");
    connect(resetMotionButton, &QPushButton::clicked, this, [this]() {
        m_conveyorPositionSpin->setValue(0.0);
        m_encoderPositionSpin->setValue(0.0);
        m_sliderPositionSpin->setValue(0.0);
        m_conveyorRunningCheck->setChecked(false);
        m_encoderRunningCheck->setChecked(false);
        m_sliderRunningCheck->setChecked(false);
        syncStateFromUi();
        appendLog("[motion] conveyor, encoder, and slider reset");
    });
    layout->addRow(resetMotionButton);

    const QList<QObject *> motionInputs = {
        m_conveyorPositionSpin, m_conveyorSpeedSpin, m_conveyorRunningCheck,
        m_encoderPositionSpin, m_encoderSpeedSpin, m_encoderRunningCheck, m_encoderFollowConveyorCheck,
        m_sliderPositionSpin, m_sliderSpeedSpin, m_sliderRunningCheck
    };
    for (QObject *input : motionInputs) {
        if (auto *spin = qobject_cast<QDoubleSpinBox *>(input)) {
            connect(spin, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &DeviceSimulatorWindow::syncStateFromUi);
        } else if (auto *check = qobject_cast<QCheckBox *>(input)) {
            connect(check, &QCheckBox::toggled, this, &DeviceSimulatorWindow::syncStateFromUi);
        }
    }

    return group;
}

void DeviceSimulatorWindow::connectServer(VirtualDeviceServer *server, ServerWidgets &widgets)
{
    connect(server, &VirtualDeviceServer::logMessage, this, &DeviceSimulatorWindow::appendLog);
    connect(server, &VirtualDeviceServer::clientCountChanged, this, [this, server, &widgets](int) {
        updateServerWidgets(server, widgets);
    });
}

void DeviceSimulatorWindow::updateServerWidgets(VirtualDeviceServer *server, ServerWidgets &widgets)
{
    widgets.portSpin->setEnabled(!server->isListening());
    widgets.toggleButton->setText(server->isListening() ? "Stop" : "Start");
    widgets.statusLabel->setText(server->isListening()
                                     ? QString("Listening on %1").arg(server->port())
                                     : QStringLiteral("Stopped"));
    widgets.clientsLabel->setText(QString("%1 client(s)").arg(server->clientCount()));

    VirtualSerialPort *serial = nullptr;
    if (server == &m_robotServer) serial = &m_robotSerial;
    if (server == &m_conveyorServer) serial = &m_conveyorSerial;
    if (server == &m_encoderServer) serial = &m_encoderSerial;
    if (server == &m_sliderServer) serial = &m_sliderSerial;
    if (server == &m_genericServer) serial = &m_genericSerial;

    if (serial) {
        widgets.serialStatusLabel->setText(serial->isOpen() ? QStringLiteral("Ready") : QStringLiteral("Stopped"));
        widgets.serialPathLabel->setText(serial->isOpen() ? serial->slavePath() : QStringLiteral("-"));
    }

    updateOverviewLabels();
}

void DeviceSimulatorWindow::appendLog(const QString &message)
{
    if (!m_logView)
        return;

    const QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss.zzz");
    m_logView->appendPlainText(QString("[%1] %2").arg(timestamp, message));
}

void DeviceSimulatorWindow::startAllServers()
{
    m_robotServer.start(static_cast<quint16>(m_robotServerWidgets.portSpin->value()));
    m_conveyorServer.start(static_cast<quint16>(m_conveyorServerWidgets.portSpin->value()));
    m_encoderServer.start(static_cast<quint16>(m_encoderServerWidgets.portSpin->value()));
    m_sliderServer.start(static_cast<quint16>(m_sliderServerWidgets.portSpin->value()));
    m_genericServer.start(static_cast<quint16>(m_genericServerWidgets.portSpin->value()));

    m_robotSerial.start();
    m_conveyorSerial.start();
    m_encoderSerial.start();
    m_sliderSerial.start();
    m_genericSerial.start();

    updateServerWidgets(&m_robotServer, m_robotServerWidgets);
    updateServerWidgets(&m_conveyorServer, m_conveyorServerWidgets);
    updateServerWidgets(&m_encoderServer, m_encoderServerWidgets);
    updateServerWidgets(&m_sliderServer, m_sliderServerWidgets);
    updateServerWidgets(&m_genericServer, m_genericServerWidgets);
    writeEndpointSummary();
}

void DeviceSimulatorWindow::stopAllServers()
{
    m_robotServer.stop();
    m_conveyorServer.stop();
    m_encoderServer.stop();
    m_sliderServer.stop();
    m_genericServer.stop();

    m_robotSerial.stop();
    m_conveyorSerial.stop();
    m_encoderSerial.stop();
    m_sliderSerial.stop();
    m_genericSerial.stop();

    updateServerWidgets(&m_robotServer, m_robotServerWidgets);
    updateServerWidgets(&m_conveyorServer, m_conveyorServerWidgets);
    updateServerWidgets(&m_encoderServer, m_encoderServerWidgets);
    updateServerWidgets(&m_sliderServer, m_sliderServerWidgets);
    updateServerWidgets(&m_genericServer, m_genericServerWidgets);
    writeEndpointSummary();
}

void DeviceSimulatorWindow::writeEndpointSummary()
{
    QFile file("/tmp/deltax-virtual-device-endpoints.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);
    stream << endpointSummaryText();
}

QString DeviceSimulatorWindow::endpointSummaryText() const
{
    QString text;
    QTextStream stream(&text);
    stream << "robot,tcp=127.0.0.1:" << m_robotServer.port() << ",serial=" << m_robotSerial.slavePath() << '\n';
    stream << "conveyor,tcp=127.0.0.1:" << m_conveyorServer.port() << ",serial=" << m_conveyorSerial.slavePath() << '\n';
    stream << "encoder,tcp=127.0.0.1:" << m_encoderServer.port() << ",serial=" << m_encoderSerial.slavePath() << '\n';
    stream << "slider,tcp=127.0.0.1:" << m_sliderServer.port() << ",serial=" << m_sliderSerial.slavePath() << '\n';
    stream << "device,tcp=127.0.0.1:" << m_genericServer.port() << ",serial=" << m_genericSerial.slavePath() << '\n';
    return text;
}

void DeviceSimulatorWindow::applyRobotMotionParameters(const RobotSimState &state)
{
    m_robotFSpin->setValue(state.f);
    m_robotASpin->setValue(state.a);
    m_robotSSpin->setValue(state.s);
    m_robotESpin->setValue(state.e);
    m_robotJSpin->setValue(state.j);
}

void DeviceSimulatorWindow::applyRobotState(const RobotSimState &state)
{
    m_robotXSpin->setValue(state.x);
    m_robotYSpin->setValue(state.y);
    m_robotZSpin->setValue(state.z);
    m_robotWSpin->setValue(state.w);
    m_robotUSpin->setValue(state.u);
    m_robotVSpin->setValue(state.v);
    applyRobotMotionParameters(state);
    m_robotOutputEnabled->setChecked(state.outputEnabled);
    m_robotOutputValueSpin->setValue(state.outputValue);
}

int DeviceSimulatorWindow::calculateRobotMoveDurationMs(const RobotSimState &startState,
                                                        const RobotSimState &targetState) const
{
    const double dx = targetState.x - startState.x;
    const double dy = targetState.y - startState.y;
    const double dz = targetState.z - startState.z;
    const double distance = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
    if (distance <= 0.0)
        return 0;

    Scurve_Interpolator scurve;
    scurve.setMaxAcc(static_cast<float>(targetState.a));
    scurve.setMaxVel(static_cast<float>(targetState.f));
    scurve.setMaxJerk(static_cast<float>(targetState.j));
    scurve.setVelStart(static_cast<float>(targetState.s));
    scurve.setVelEnd(static_cast<float>(targetState.e));
    scurve.p_target = static_cast<float>(distance);
    scurve.start();

    return std::max(0, static_cast<int>(std::ceil(scurve.t_target * 1000.0)));
}

int DeviceSimulatorWindow::calculateLinearMoveDurationMs(double startPosition,
                                                         double targetPosition,
                                                         double speed) const
{
    const double distance = std::abs(targetPosition - startPosition);
    const double absSpeed = std::abs(speed);
    if (distance <= 0.0 || absSpeed <= 0.0)
        return 0;

    return std::max(0, static_cast<int>(std::ceil((distance / absSpeed) * 1000.0)));
}

void DeviceSimulatorWindow::scheduleRobotCompletion(const RobotSimState &targetState,
                                                    int delayMs,
                                                    const QString &command,
                                                    ResponseSender respond)
{
    if (delayMs <= 0) {
        applyRobotState(targetState);
        respond(QStringLiteral("Ok"));
        return;
    }

    appendLog(QString("[robot] executing \"%1\" for %2 ms before Ok").arg(command).arg(delayMs));
    QTimer::singleShot(delayMs, this, [this, targetState, respond, command]() {
        applyRobotState(targetState);
        appendLog(QString("[robot] completed \"%1\"").arg(command));
        respond(QStringLiteral("Ok"));
    });
}

void DeviceSimulatorWindow::scheduleLinearCompletion(QDoubleSpinBox *positionSpin,
                                                     QCheckBox *runningCheck,
                                                     double targetPosition,
                                                     int delayMs,
                                                     const QString &deviceName,
                                                     const QString &command,
                                                     ResponseSender respond)
{
    if (delayMs <= 0) {
        positionSpin->setValue(targetPosition);
        if (runningCheck)
            runningCheck->setChecked(false);
        respond(QStringLiteral("Ok"));
        return;
    }

    if (runningCheck)
        runningCheck->setChecked(true);
    appendLog(QString("[%1] executing \"%2\" for %3 ms before Ok").arg(deviceName, command).arg(delayMs));
    QTimer::singleShot(delayMs, this, [this, positionSpin, runningCheck, targetPosition, respond, deviceName, command]() {
        positionSpin->setValue(targetPosition);
        if (runningCheck)
            runningCheck->setChecked(false);
        appendLog(QString("[%1] completed \"%2\"").arg(deviceName, command));
        respond(QStringLiteral("Ok"));
    });
}

void DeviceSimulatorWindow::copyEndpointSummaryToClipboard()
{
    if (QClipboard *clipboard = QGuiApplication::clipboard()) {
        clipboard->setText(endpointSummaryText());
        appendLog("[system] endpoint mapping copied to clipboard");
    }
}

void DeviceSimulatorWindow::openEndpointSummaryFile()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("/tmp/deltax-virtual-device-endpoints.txt"));
    appendLog("[system] opened /tmp/deltax-virtual-device-endpoints.txt");
}

void DeviceSimulatorWindow::syncStateFromUi()
{
    m_robotState.x = m_robotXSpin->value();
    m_robotState.y = m_robotYSpin->value();
    m_robotState.z = m_robotZSpin->value();
    m_robotState.w = m_robotWSpin->value();
    m_robotState.u = m_robotUSpin->value();
    m_robotState.v = m_robotVSpin->value();
    m_robotState.f = m_robotFSpin->value();
    m_robotState.a = m_robotASpin->value();
    m_robotState.s = m_robotSSpin->value();
    m_robotState.e = m_robotESpin->value();
    m_robotState.j = m_robotJSpin->value();
    m_robotState.outputEnabled = m_robotOutputEnabled->isChecked();
    m_robotState.outputValue = m_robotOutputValueSpin->value();

    m_conveyorState.position = m_conveyorPositionSpin->value();
    m_conveyorState.speed = m_conveyorSpeedSpin->value();
    m_conveyorState.running = m_conveyorRunningCheck->isChecked();

    m_encoderState.position = m_encoderPositionSpin->value();
    m_encoderState.speed = m_encoderSpeedSpin->value();
    m_encoderState.running = m_encoderRunningCheck->isChecked();

    m_sliderState.position = m_sliderPositionSpin->value();
    m_sliderState.speed = m_sliderSpeedSpin->value();
    m_sliderState.running = m_sliderRunningCheck->isChecked();
}

void DeviceSimulatorWindow::updateSimulation()
{
    const double stepSeconds = 0.1;

    if (m_conveyorRunningCheck->isChecked()) {
        m_conveyorPositionSpin->setValue(m_conveyorPositionSpin->value() + (m_conveyorSpeedSpin->value() * stepSeconds));
    }

    if (m_encoderFollowConveyorCheck->isChecked()) {
        if (m_encoderPositionSpin->value() != m_conveyorPositionSpin->value())
            m_encoderPositionSpin->setValue(m_conveyorPositionSpin->value());
    } else if (m_encoderRunningCheck->isChecked()) {
        m_encoderPositionSpin->setValue(m_encoderPositionSpin->value() + (m_encoderSpeedSpin->value() * stepSeconds));
    }

    if (m_sliderRunningCheck->isChecked()) {
        m_sliderPositionSpin->setValue(m_sliderPositionSpin->value() + (m_sliderSpeedSpin->value() * stepSeconds));
    }
}

void DeviceSimulatorWindow::handleRobotCommand(const QString &command, ResponseSender respond)
{
    QString normalized = command.trimmed();
    if (normalized.isEmpty()) {
        respond(QStringLiteral("Ok"));
        return;
    }

    const QString upper = normalized.toUpper();
    if (upper == "ISDELTA") {
        respond(QStringLiteral("YesDelta"));
        return;
    }
    if (upper == "POSITION" || upper == "M114") {
        respond(formatRobotPosition());
        return;
    }
    if (upper == "G28" || upper == "M85") {
        const RobotSimState startState = m_robotState;
        RobotSimState targetState = m_robotState;
        targetState.x = 0.0;
        targetState.y = 0.0;
        targetState.z = 0.0;
        targetState.w = 0.0;
        targetState.u = 0.0;
        targetState.v = 0.0;
        scheduleRobotCompletion(targetState, calculateRobotMoveDurationMs(startState, targetState), normalized, respond);
        return;
    }
    if (upper == "M84") {
        respond(QStringLiteral("Ok"));
        return;
    }

    const QStringList tokens = normalized.split(' ', Qt::SkipEmptyParts);
    if (!tokens.isEmpty()) {
        const QString commandName = tokens.first().toUpper();
        if (commandName == "G01" || commandName == "G1" || commandName == "G00" || commandName == "G0") {
            const RobotSimState startState = m_robotState;
            RobotSimState targetState = m_robotState;
            bool hasAxisUpdate = false;

            for (int index = 1; index < tokens.size(); ++index) {
                const QString token = tokens.at(index).trimmed();
                if (token.isEmpty())
                    continue;

                const QChar key = token.at(0).toUpper();
                const double value = tokenValue(token).toDouble();
                switch (key.toLatin1()) {
                case 'X': targetState.x = value; hasAxisUpdate = true; break;
                case 'Y': targetState.y = value; hasAxisUpdate = true; break;
                case 'Z': targetState.z = value; hasAxisUpdate = true; break;
                case 'W': targetState.w = value; hasAxisUpdate = true; break;
                case 'U': targetState.u = value; hasAxisUpdate = true; break;
                case 'V': targetState.v = value; hasAxisUpdate = true; break;
                case 'F': targetState.f = value; break;
                case 'A': targetState.a = value; break;
                case 'S': targetState.s = value; break;
                case 'E': targetState.e = value; break;
                case 'J': targetState.j = value; break;
                default: break;
                }
            }

            if (!hasAxisUpdate) {
                applyRobotState(targetState);
                respond(QStringLiteral("Ok"));
                return;
            }

            applyRobotMotionParameters(targetState);
            scheduleRobotCompletion(targetState, calculateRobotMoveDurationMs(startState, targetState), normalized, respond);
            return;
        }

        if (commandName == "M03") {
            m_robotOutputEnabled->setChecked(true);
            if (tokens.size() >= 2) {
                const QString valueToken = tokens.at(1).trimmed();
                if (valueToken.startsWith('S', Qt::CaseInsensitive))
                    m_robotOutputValueSpin->setValue(tokenValue(valueToken).toInt());
            }
            respond(QStringLiteral("Ok"));
            return;
        }

        if (commandName == "M05") {
            m_robotOutputEnabled->setChecked(false);
            respond(QStringLiteral("Ok"));
            return;
        }

        if (commandName == "M204" || commandName == "M205" || commandName == "M203") {
            RobotSimState targetState = m_robotState;
            for (int index = 1; index < tokens.size(); ++index) {
                const QString token = tokens.at(index).trimmed();
                if (token.isEmpty())
                    continue;
                const QChar key = token.at(0).toUpper();
                const double value = tokenValue(token).toDouble();
                if (key == 'A')
                    targetState.a = value;
                if (key == 'S')
                    targetState.s = value;
                if (key == 'E')
                    targetState.e = value;
                if (key == 'J')
                    targetState.j = value;
                if (key == 'F')
                    targetState.f = value;
            }
            applyRobotState(targetState);
            respond(QStringLiteral("Ok"));
            return;
        }
    }

    respond(QStringLiteral("Ok"));
}

void DeviceSimulatorWindow::handleConveyorCommand(const QString &command, ResponseSender respond)
{
    const QString normalized = command.trimmed();
    const QString upper = normalized.toUpper();
    const QStringList tokens = normalized.split(' ', Qt::SkipEmptyParts);

    if (upper.startsWith("M310")) {
        if (tokens.size() >= 2) {
            const int mode = tokens.at(1).toInt();
            m_conveyorRunningCheck->setChecked(mode != 0);
        }
        respond(QStringLiteral("Ok"));
        return;
    }

    if (upper.startsWith("M311")) {
        if (tokens.size() >= 2)
            m_conveyorSpeedSpin->setValue(tokens.at(1).toDouble());
        m_conveyorRunningCheck->setChecked(!qFuzzyIsNull(m_conveyorSpeedSpin->value()));
        respond(QStringLiteral("Ok"));
        return;
    }

    if (upper.startsWith("M312")) {
        if (tokens.size() >= 2) {
            const double targetPosition = m_conveyorPositionSpin->value() + tokens.at(1).toDouble();
            const int delayMs = calculateLinearMoveDurationMs(m_conveyorPositionSpin->value(),
                                                              targetPosition,
                                                              m_conveyorSpeedSpin->value());
            scheduleLinearCompletion(m_conveyorPositionSpin,
                                     m_conveyorRunningCheck,
                                     targetPosition,
                                     delayMs,
                                     QStringLiteral("conveyor"),
                                     normalized,
                                     respond);
            return;
        }
        respond(QStringLiteral("Ok"));
        return;
    }

    if (upper.startsWith("M313")) {
        if (tokens.size() >= 2)
            m_conveyorSpeedSpin->setValue(tokens.at(1).toDouble());
        m_conveyorRunningCheck->setChecked(false);
        respond(QStringLiteral("Ok"));
        return;
    }

    QRegularExpression regex("^M422\\s+C(\\d+)$", QRegularExpression::CaseInsensitiveOption);
    const QRegularExpressionMatch match = regex.match(normalized);
    if (match.hasMatch()) {
        const int channel = match.captured(1).toInt();
        respond(formatEncoderResponse(channel, m_conveyorPositionSpin->value()));
        return;
    }

    respond(QStringLiteral("Ok"));
}

void DeviceSimulatorWindow::handleEncoderCommand(const QString &command, ResponseSender respond)
{
    const QString normalized = command.trimmed();
    const QString upper = normalized.toUpper();

    if (upper.startsWith("M316"))
    {
        respond(QStringLiteral("Ok"));
        return;
    }

    if (upper.startsWith("M317")) {
        respond(formatEncoderResponse(1, m_encoderPositionSpin->value()));
        return;
    }

    if (upper.startsWith("M318") || upper.startsWith("M319"))
    {
        respond(QStringLiteral("Ok"));
        return;
    }

    respond(formatEncoderResponse(1, m_encoderPositionSpin->value()));
}

void DeviceSimulatorWindow::handleSliderCommand(const QString &command, ResponseSender respond)
{
    const QString normalized = command.trimmed();
    const QString upper = normalized.toUpper();
    const QStringList tokens = normalized.split(' ', Qt::SkipEmptyParts);

    if (upper.startsWith("M320")) {
        const int delayMs = calculateLinearMoveDurationMs(m_sliderPositionSpin->value(), 0.0, m_sliderSpeedSpin->value());
        scheduleLinearCompletion(m_sliderPositionSpin,
                                 m_sliderRunningCheck,
                                 0.0,
                                 delayMs,
                                 QStringLiteral("slider"),
                                 normalized,
                                 respond);
        return;
    }

    if (upper.startsWith("M321")) {
        if (tokens.size() >= 2)
            m_sliderSpeedSpin->setValue(tokens.at(1).toDouble());
        m_sliderRunningCheck->setChecked(!qFuzzyIsNull(m_sliderSpeedSpin->value()));
        respond(QStringLiteral("Ok"));
        return;
    }

    if (upper.startsWith("M322")) {
        if (tokens.size() >= 2) {
            const double targetPosition = tokens.at(1).toDouble();
            const int delayMs = calculateLinearMoveDurationMs(m_sliderPositionSpin->value(),
                                                              targetPosition,
                                                              m_sliderSpeedSpin->value());
            scheduleLinearCompletion(m_sliderPositionSpin,
                                     m_sliderRunningCheck,
                                     targetPosition,
                                     delayMs,
                                     QStringLiteral("slider"),
                                     normalized,
                                     respond);
            return;
        }
        respond(QStringLiteral("Ok"));
        return;
    }

    if (upper.startsWith("M323")) {
        m_sliderRunningCheck->setChecked(false);
        respond(QStringLiteral("Ok"));
        return;
    }

    respond(QStringLiteral("Ok"));
}

void DeviceSimulatorWindow::handleGenericDeviceCommand(const QString &command, ResponseSender respond)
{
    if (command.trimmed().compare("PING", Qt::CaseInsensitive) == 0)
    {
        respond(QStringLiteral("PONG"));
        return;
    }

    respond(QStringLiteral("Ok"));
}

QString DeviceSimulatorWindow::formatRobotPosition() const
{
    return QString("%1,%2,%3,%4,%5,%6")
        .arg(m_robotXSpin->value(), 0, 'f', 3)
        .arg(m_robotYSpin->value(), 0, 'f', 3)
        .arg(m_robotZSpin->value(), 0, 'f', 3)
        .arg(m_robotWSpin->value(), 0, 'f', 3)
        .arg(m_robotUSpin->value(), 0, 'f', 3)
        .arg(m_robotVSpin->value(), 0, 'f', 3);
}

QString DeviceSimulatorWindow::formatEncoderResponse(int channel, double position) const
{
    return QString("P%1:%2").arg(channel).arg(position, 0, 'f', 3);
}
