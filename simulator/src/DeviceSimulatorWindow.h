#ifndef DEVICESIMULATORWINDOW_H
#define DEVICESIMULATORWINDOW_H

#include "VirtualDeviceServer.h"
#include "VirtualSerialPort.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QSplitter>
#include <QTabWidget>
#include <QTimer>
#include <functional>

struct RobotSimState
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double w = 0.0;
    double u = 0.0;
    double v = 0.0;
    double f = 500.0;
    double a = 8000.0;
    double s = 30.0;
    double e = 40.0;
    double j = 255000.0;
    bool outputEnabled = false;
    int outputValue = 0;
};

struct LinearSimState
{
    double position = 0.0;
    double speed = 50.0;
    bool running = false;
};

class DeviceSimulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceSimulatorWindow(QWidget *parent = nullptr);

private slots:
    void appendLog(const QString &message);
    void startAllServers();
    void stopAllServers();
    void syncStateFromUi();
    void updateSimulation();
    void copyEndpointSummaryToClipboard();
    void openEndpointSummaryFile();

private:
    using ResponseSender = std::function<void(const QString &)>;

    struct ServerWidgets {
        QSpinBox *portSpin = nullptr;
        QPushButton *toggleButton = nullptr;
        QLabel *statusLabel = nullptr;
        QLabel *clientsLabel = nullptr;
        QLabel *serialStatusLabel = nullptr;
        QLabel *serialPathLabel = nullptr;
    };

    QWidget *buildCentralWidget();
    QWidget *createConnectionsPanel();
    QGroupBox *createServerGroup(VirtualDeviceServer *server, ServerWidgets &widgets);
    QGroupBox *createRobotStateGroup();
    QGroupBox *createMotionStateGroup();
    QScrollArea *createScrollableSection(QWidget *content) const;
    void applyInitialWindowSize();
    void updateOverviewLabels();
    void connectServer(VirtualDeviceServer *server, ServerWidgets &widgets);
    void updateServerWidgets(VirtualDeviceServer *server, ServerWidgets &widgets);
    void writeEndpointSummary();
    QString endpointSummaryText() const;
    void applyRobotState(const RobotSimState &state);
    void applyRobotMotionParameters(const RobotSimState &state);
    void scheduleRobotCompletion(const RobotSimState &targetState,
                                 int delayMs,
                                 const QString &command,
                                 ResponseSender respond);
    void scheduleLinearCompletion(QDoubleSpinBox *positionSpin,
                                  QCheckBox *runningCheck,
                                  double targetPosition,
                                  int delayMs,
                                  const QString &deviceName,
                                  const QString &command,
                                  ResponseSender respond);
    int calculateRobotMoveDurationMs(const RobotSimState &startState, const RobotSimState &targetState) const;
    int calculateLinearMoveDurationMs(double startPosition, double targetPosition, double speed) const;

    void handleRobotCommand(const QString &command, ResponseSender respond);
    void handleConveyorCommand(const QString &command, ResponseSender respond);
    void handleEncoderCommand(const QString &command, ResponseSender respond);
    void handleSliderCommand(const QString &command, ResponseSender respond);
    void handleGenericDeviceCommand(const QString &command, ResponseSender respond);

    QString formatRobotPosition() const;
    QString formatEncoderResponse(int channel, double position) const;

    RobotSimState m_robotState;
    LinearSimState m_conveyorState;
    LinearSimState m_encoderState;
    LinearSimState m_sliderState;

    VirtualDeviceServer m_robotServer;
    VirtualDeviceServer m_conveyorServer;
    VirtualDeviceServer m_encoderServer;
    VirtualDeviceServer m_sliderServer;
    VirtualDeviceServer m_genericServer;

    VirtualSerialPort m_robotSerial;
    VirtualSerialPort m_conveyorSerial;
    VirtualSerialPort m_encoderSerial;
    VirtualSerialPort m_sliderSerial;
    VirtualSerialPort m_genericSerial;

    ServerWidgets m_robotServerWidgets;
    ServerWidgets m_conveyorServerWidgets;
    ServerWidgets m_encoderServerWidgets;
    ServerWidgets m_sliderServerWidgets;
    ServerWidgets m_genericServerWidgets;

    QLabel *m_runtimeStatusLabel = nullptr;
    QLabel *m_endpointStatusLabel = nullptr;
    QPlainTextEdit *m_logView = nullptr;

    QDoubleSpinBox *m_robotXSpin = nullptr;
    QDoubleSpinBox *m_robotYSpin = nullptr;
    QDoubleSpinBox *m_robotZSpin = nullptr;
    QDoubleSpinBox *m_robotWSpin = nullptr;
    QDoubleSpinBox *m_robotUSpin = nullptr;
    QDoubleSpinBox *m_robotVSpin = nullptr;
    QDoubleSpinBox *m_robotFSpin = nullptr;
    QDoubleSpinBox *m_robotASpin = nullptr;
    QDoubleSpinBox *m_robotSSpin = nullptr;
    QDoubleSpinBox *m_robotESpin = nullptr;
    QDoubleSpinBox *m_robotJSpin = nullptr;
    QCheckBox *m_robotOutputEnabled = nullptr;
    QSpinBox *m_robotOutputValueSpin = nullptr;

    QDoubleSpinBox *m_conveyorPositionSpin = nullptr;
    QDoubleSpinBox *m_conveyorSpeedSpin = nullptr;
    QCheckBox *m_conveyorRunningCheck = nullptr;

    QDoubleSpinBox *m_encoderPositionSpin = nullptr;
    QDoubleSpinBox *m_encoderSpeedSpin = nullptr;
    QCheckBox *m_encoderRunningCheck = nullptr;
    QCheckBox *m_encoderFollowConveyorCheck = nullptr;

    QDoubleSpinBox *m_sliderPositionSpin = nullptr;
    QDoubleSpinBox *m_sliderSpeedSpin = nullptr;
    QCheckBox *m_sliderRunningCheck = nullptr;

    QTimer m_simulationTimer;
};

#endif // DEVICESIMULATORWINDOW_H
