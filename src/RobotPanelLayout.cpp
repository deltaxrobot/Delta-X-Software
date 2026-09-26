#include "RobotPanelLayout.h"
#include "UiTheme.h"
#include "ui_RobotWindow.h"
#include <QtWidgets>

namespace {
QString text(const char* value) { return QCoreApplication::translate("RobotPanelLayout", value); }

// Remove layout items, never the controls: their identity and signal bindings
// are used by RobotWindow, settings persistence and the device command broker.
void clearLayout(QLayout* layout)
{
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (item->layout())
            clearLayout(item->layout());
        delete item;
    }
}

QVBoxLayout* resetPanel(QWidget* panel)
{
    if (panel->layout()) {
        clearLayout(panel->layout());
        delete panel->layout();
    }
    panel->setMinimumSize(0, 0);
    panel->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    auto* layout = new QVBoxLayout(panel);
    layout->setContentsMargins(10, 8, 10, 8);
    layout->setSpacing(8);
    return layout;
}

QLabel* note(const char* value, QWidget* parent)
{
    auto* label = new QLabel(text(value), parent);
    label->setWordWrap(true);
    label->setTextFormat(Qt::PlainText);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    label->setProperty("robotHint", true);
    return label;
}

QScrollArea* page(QTabWidget* tabs, const char* title, const char* name)
{
    auto* scroll = new QScrollArea(tabs);
    scroll->setObjectName(QString::fromLatin1(name));
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    auto* content = new QWidget(scroll);
    auto* layout = resetPanel(content);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    scroll->setWidget(content);
    tabs->addTab(scroll, text(title));
    return scroll;
}

void inputBank(QGroupBox* bank, const QString& suffix)
{
    auto* rows = resetPanel(bank);
    for (QLabel* label : bank->findChildren<QLabel*>(QString(), Qt::FindDirectChildrenOnly))
        if (label->objectName().startsWith("label_"))
            label->hide();
    auto* grid = new QGridLayout;
    grid->setHorizontalSpacing(6);
    int row = 0;
    for (const QString& channel : {QString("I0"), QString("I1"), QString("I2"), QString("I3"),
                                   QString("Ix"), QString("A0"), QString("A1"), QString("Ax")}) {
        auto* read = bank->findChild<QPushButton*>("pbRead" + channel + suffix);
        if (!read)
            continue;
        QWidget* channelLabel = channel.endsWith('x')
            ? static_cast<QWidget*>(bank->findChild<QLineEdit*>("le" + channel + suffix))
            : static_cast<QWidget*>(new QLabel(channel, bank));
        if (!channelLabel)
            continue;
        channelLabel->setMinimumWidth(0);
        channelLabel->setMaximumWidth(50);
        grid->addWidget(channelLabel, row, 0);
        grid->addWidget(bank->findChild<QLabel*>("lb" + channel + "Value" + suffix), row, 1);
        read->setText(text("Read"));
        grid->addWidget(read, row, 2);
        const QString id = channel.mid(1);
        if (channel.startsWith('I')) {
            auto* wait = bank->findChild<QCheckBox*>("cbToggle" + id + suffix);
            wait->setText(text("Wait toggle"));
            wait->setToolTip(text("Read sends M07; with Wait toggle enabled it sends M08."));
            grid->addWidget(wait, row, 3);
        } else {
            auto* delay = bank->findChild<QLineEdit*>("leA" + id + "Delay" + suffix);
            delay->setMinimumWidth(0);
            delay->setMaximumWidth(90);
            delay->setPlaceholderText(text("W (optional)"));
            delay->setToolTip(text("Optional W argument for M08. Leave blank to omit it."));
            grid->addWidget(delay, row, 3);
        }
        ++row;
    }
    grid->setColumnStretch(1, 1);
    rows->addLayout(grid);
}
}

void RobotPanelLayout::setup(Ui::RobotWindow& ui)
{
    if (ui.tRobot->property("robotPanelLayoutReady").toBool())
        return;
    ui.tRobot->setProperty("robotPanelLayoutReady", true);
    auto* root = resetPanel(ui.tRobot);
    root->setContentsMargins(6, 6, 6, 6);

    // Keep selection/connection reachable while scrolling or changing pages.
    ui.verticalLayout_5->removeWidget(ui.frame_12);
    auto* connection = resetPanel(ui.frame_12);
    ui.robotTitile->hide();
    ui.frame_23->hide();
    auto* connectionRow = new QHBoxLayout;
    auto* selectedLabel = new QLabel(text("Robot"));
    selectedLabel->setBuddy(ui.cbSelectedRobot);
    connectionRow->addWidget(selectedLabel);
    ui.cbSelectedRobot->setMinimumWidth(110);
    ui.cbSelectedRobot->setMaximumWidth(QWIDGETSIZE_MAX);
    connectionRow->addWidget(ui.cbSelectedRobot, 1);
    ui.tbAutoScanRobot->setText(text("Auto scan"));
    ui.tbAutoScanRobot->setToolButtonStyle(Qt::ToolButtonTextOnly);
    ui.tbAutoScanRobot->setToolTip(text("Automatically scan serial ports for this robot"));
    connectionRow->addWidget(ui.pbConnectRobot);
    connection->addLayout(connectionRow);
    auto* connectionInfo = new QHBoxLayout;
    connectionInfo->addWidget(ui.tbAutoScanRobot);
    connectionInfo->addWidget(new QLabel(text("Port")));
    ui.lbComName->setFont(ui.tRobot->font());
    ui.lbComName->setMinimumWidth(0);
    connectionInfo->addWidget(ui.lbComName);
    connectionInfo->addStretch();
    connectionInfo->addWidget(new QLabel(text("Baud")));
    ui.lbBaudrate->setFont(ui.tRobot->font());
    connectionInfo->addWidget(ui.lbBaudrate);
    connection->addLayout(connectionInfo);
    root->addWidget(ui.frame_12);

    auto* tabs = new QTabWidget(ui.tRobot);
    tabs->setObjectName("robotControlTabs");
    tabs->setDocumentMode(true);
    auto* control = page(tabs, "Control", "robotControlPage");
    auto* io = page(tabs, "I/O", "robotIoPage");
    auto* setup = page(tabs, "Setup", "robotSetupPage");
    root->addWidget(tabs, 1);
    auto* controlLayout = qobject_cast<QVBoxLayout*>(control->widget()->layout());
    auto* ioLayout = qobject_cast<QVBoxLayout*>(io->widget()->layout());
    auto* setupLayout = qobject_cast<QVBoxLayout*>(setup->widget()->layout());

    // Coordinates are editable motion targets, not read-only telemetry.
    auto* position = resetPanel(ui.frame_28);
    ui.positionTitile->hide();
    ui.frame_29->hide();
    auto* positionTitle = new QLabel(text("Position / axis move"));
    positionTitle->setProperty("robotSectionTitle", true);
    position->addWidget(positionTitle);
    auto* coordinates = new QGridLayout;
    const QList<QLineEdit*> axes = {ui.leX, ui.leY, ui.leZ, ui.leW, ui.leU, ui.leV};
    const QStringList axisNames = {"X", "Y", "Z", "W", "U", "V"};
    for (int i = 0; i < axes.size(); ++i) {
        auto* field = axes[i];
        field->setMinimumWidth(0);
        field->setMaximumWidth(QWIDGETSIZE_MAX);
        field->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        field->setAlignment(Qt::AlignRight);
        const QString caption = axisNames[i] + (i < 3 ? text(" (mm)") : text(" (deg)"));
        auto* label = new QLabel(caption);
        label->setBuddy(field);
        field->setAccessibleName(caption);
        field->setToolTip(text("Press Enter to move this axis to the entered coordinate"));
        coordinates->addWidget(label, (i / 3) * 2, i % 3);
        coordinates->addWidget(field, (i / 3) * 2 + 1, i % 3);
        coordinates->setColumnStretch(i % 3, 1);
    }
    position->addLayout(coordinates);
    auto* positionActions = new QHBoxLayout;
    ui.pbHome->setText(text("Home"));
    ui.pbHome->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui.pbHome->setToolTip(text("Run the robot homing motion (G28). Clear the workspace first."));
    ui.tbDisableRobot->setText(text("Motor hold"));
    ui.tbDisableRobot->setToolTip(text("Toggle motor holding state (M85 / M84). This is not an emergency stop."));
    ui.tbCopyRobotPosition->setToolTip(text("Copy X, Y, Z, W, U and V coordinates"));
    ui.tbRequestPosition->setToolTip(text("Read the current position from the robot controller"));
    positionActions->addWidget(ui.pbHome);
    positionActions->addWidget(ui.tbDisableRobot);
    auto* mouseControl = new QPushButton(text("Mouse control"), ui.frame_28);
    mouseControl->setObjectName(QStringLiteral("pbMouseRobotControl"));
    mouseControl->setToolTip(text("Hold and drag for X/Y; mouse wheel for Z"));
    positionActions->addWidget(mouseControl);
    positionActions->addStretch();
    positionActions->addWidget(ui.tbRequestPosition);
    positionActions->addWidget(ui.tbCopyRobotPosition);
    position->addLayout(positionActions);
    controlLayout->addWidget(ui.frame_28);

    auto* jogging = resetPanel(ui.frame_30);
    ui.robotTitile_4->hide();
    auto* jogTitle = new QLabel(text("Jogging"));
    jogTitle->setProperty("robotSectionTitle", true);
    jogging->addWidget(jogTitle);
    const QList<QPair<QToolButton*, QString>> jogCaptions = {
        {ui.pbLeft, "X −"}, {ui.pbRight, "X +"},
        {ui.pbForward, "Y +"}, {ui.pbBackward, "Y −"},
        {ui.pbUp, "Z +"}, {ui.pbDown, "Z −"},
        {ui.pbSubRoll, "W −"}, {ui.pbPlusRoll, "W +"},
        {ui.pbSubYaw, "U −"}, {ui.pbPlusYaw, "U +"},
        {ui.pbSubPitch, "V −"}, {ui.pbPlusPitch, "V +"},
    };
    for (const auto& caption : jogCaptions) {
        caption.first->setText(caption.second);
        caption.first->setAccessibleName(text("Jog ") + caption.second);
        caption.first->setToolTip(text("Move one step: ") + caption.second);
    }
    auto* cluster = resetPanel(ui.frame_31);
    cluster->setContentsMargins(0, 0, 0, 0);
    // Use stable rows in a dock: changing direction during resize can leave a
    // stale minimum height and overlap the step selector while Qt relayouts.
    auto* clusterRow = new QBoxLayout(QBoxLayout::TopToBottom);
    auto* xyz = new QWidget(ui.frame_31);
    auto* xyzGrid = new QGridLayout(xyz);
    xyzGrid->setContentsMargins(0, 0, 0, 0);
    xyzGrid->setSpacing(6);
    xyzGrid->addWidget(ui.pbContinuousForward, 0, 2);
    xyzGrid->addWidget(ui.pbForward, 1, 2);
    xyzGrid->addWidget(ui.pbContinuousLeft, 2, 0);
    xyzGrid->addWidget(ui.pbLeft, 2, 1);
    xyzGrid->addWidget(ui.pbRight, 2, 3);
    xyzGrid->addWidget(ui.pbContinuousRight, 2, 4);
    xyzGrid->addWidget(ui.pbBackward, 3, 2);
    xyzGrid->addWidget(ui.pbContinuousBackward, 4, 2);
    xyzGrid->setColumnMinimumWidth(5, 10);
    xyzGrid->addWidget(ui.pbContinuousUp, 0, 6);
    xyzGrid->addWidget(ui.pbUp, 1, 6);
    xyzGrid->addWidget(ui.pbDown, 3, 6);
    xyzGrid->addWidget(ui.pbContinuousDown, 4, 6);
    clusterRow->addWidget(xyz, 0, Qt::AlignLeft | Qt::AlignVCenter);
    auto* rotary = new QWidget(ui.frame_31);
    rotary->setObjectName("robotRotaryJog");
    auto* rotaryGrid = new QGridLayout(rotary);
    rotaryGrid->setContentsMargins(0, 0, 0, 0);
    const QList<QToolButton*> minus = {ui.pbSubRoll, ui.pbSubYaw, ui.pbSubPitch};
    const QList<QToolButton*> plus = {ui.pbPlusRoll, ui.pbPlusYaw, ui.pbPlusPitch};
    const QList<QLabel*> rotaryLabels = {ui.label_276, ui.label_275, ui.label_274};
    for (int i = 0; i < 3; ++i) {
        rotaryLabels[i]->setText(axisNames[i + 3] + text(" (deg)"));
        rotaryLabels[i]->setAlignment(Qt::AlignCenter);
        rotaryGrid->addWidget(minus[i], 0, i);
        rotaryGrid->addWidget(rotaryLabels[i], 1, i);
        rotaryGrid->addWidget(plus[i], 2, i);
    }
    clusterRow->addWidget(rotary, 0, Qt::AlignLeft | Qt::AlignVCenter);
    clusterRow->addStretch();
    cluster->addLayout(clusterRow);
    for (QToolButton* unused : {ui.pbContinuous4Plus, ui.pbContinuous4Sub,
                               ui.pbContinuous5Plus, ui.pbContinuous5Sub,
                               ui.pbContinuous6Plus, ui.pbContinuous6Sub}) {
        unused->setShortcut(QKeySequence());
        unused->hide();
    }
    const auto updateAxes = [axes, minus, plus, rotaryLabels, rotary](int dofIndex) {
        rotary->setVisible(dofIndex > 0);
        for (int i = 0; i < 3; ++i) {
            const bool supported = dofIndex > i;
            axes[i + 3]->setEnabled(supported);
            minus[i]->setEnabled(supported);
            plus[i]->setEnabled(supported);
            rotaryLabels[i]->setEnabled(supported);
        }
    };
    QObject::connect(ui.cbRobotDOF, qOverload<int>(&QComboBox::currentIndexChanged), ui.tRobot, updateAxes);
    updateAxes(ui.cbRobotDOF->currentIndex());
    jogging->addWidget(ui.frame_31);

    auto* step = resetPanel(ui.frame_32);
    ui.label_33->hide();
    ui.label_273->hide();
    step->setContentsMargins(0, 0, 0, 0);
    step->addWidget(note("Step size · XYZ: mm / WUV: deg", ui.frame_32));
    auto* steps = new QGridLayout;
    steps->setSpacing(4);
    const QList<QRadioButton*> stepButtons = {ui.rb01, ui.rb05, ui.rb10, ui.rb50, ui.rb100, ui.rb500, ui.rb1000};
    for (int i = 0; i < stepButtons.size(); ++i)
        steps->addWidget(stepButtons[i], i / 4, i % 4);
    step->addLayout(steps);
    jogging->addWidget(ui.frame_32);
    auto* speedRow = new QHBoxLayout;
    speedRow->addWidget(new QLabel(text("Speed (F)")));
    ui.leVelocity->setMinimumWidth(0);
    ui.leVelocity->setMaximumWidth(QWIDGETSIZE_MAX);
    ui.leVelocity->setToolTip(text("Feed rate in mm/s. Press Enter to send the new value."));
    speedRow->addWidget(ui.leVelocity, 1);
    speedRow->addWidget(new QLabel(text("mm/s")));
    jogging->addLayout(speedRow);
    controlLayout->addWidget(ui.frame_30);
    controlLayout->addStretch();

    ioLayout->addWidget(ui.frame_34);
    ioLayout->addWidget(ui.frame_36);
    ioLayout->addStretch();
    inputBank(ui.gbInputXS, QString());
    inputBank(ui.gbInputX3, QStringLiteral("X3"));
    // Narrow I/O cards keep the original checkbox parents and object names.
    const auto digitalBank = [](QWidget* host, const QList<QCheckBox*>& outputs) {
        auto* layout = resetPanel(host);
        layout->setContentsMargins(0, 0, 0, 0);
        for (QLabel* label : host->findChildren<QLabel*>())
            label->hide();
        auto* grid = new QGridLayout;
        for (int i = 0; i < outputs.size(); ++i) {
            outputs[i]->setText(QString("D%1").arg(i));
            outputs[i]->setToolTip(text("Toggle this digital output immediately"));
            grid->addWidget(outputs[i], i / 4, i % 4);
        }
        layout->addLayout(grid);
        return layout;
    };
    auto* xsOutputs = digitalBank(ui.wgDigitalOutput,
        {ui.cbD0, ui.cbD1, ui.cbD2, ui.cbD3, ui.cbD4, ui.cbD5, ui.cbD6, ui.cbD7});
    auto* customOutputs = new QHBoxLayout;
    customOutputs->addWidget(new QLabel(text("Custom")));
    for (auto* field : {ui.leDx, ui.leRx}) {
        field->setMinimumWidth(0);
        field->setMaximumWidth(65);
    }
    customOutputs->addWidget(ui.leDx);
    customOutputs->addWidget(ui.cbDx);
    customOutputs->addWidget(ui.leRx);
    customOutputs->addWidget(ui.cbRx);
    xsOutputs->addLayout(customOutputs);
    auto* x3Outputs = digitalBank(ui.wgDigitalOutput_2,
        {ui.cbX3D0, ui.cbX3D1, ui.cbX3D2, ui.cbX3D3});
    x3Outputs->insertWidget(0, ui.pbPumpX3, 0, Qt::AlignLeft);
    auto* endEffectors = resetPanel(ui.gbX1);
    auto* tools = new QHBoxLayout;
    tools->addWidget(ui.pbPump);
    tools->addWidget(ui.pbLaser);
    endEffectors->addLayout(tools);
    endEffectors->addWidget(ui.gbGripper);
    // Keep each bank's internal parent hierarchy: I/O slots resolve siblings
    // by sender()->parent(). Model visibility continues to be owned by RobotWindow.
    for (QGroupBox* bank : {ui.gbX1, ui.gbOutputXS, ui.gbOutputX3, ui.gbInputXS, ui.gbInputX3}) {
        bank->setMinimumWidth(0);
        for (QPushButton* button : bank->findChildren<QPushButton*>()) {
            button->setText(button->text().trimmed());
            if (button->text().compare("read", Qt::CaseInsensitive) == 0) {
                button->setText(text("Read"));
                button->setToolTip(text("Read this input using the channel and wait option on this row"));
            } else {
                button->setToolTip(text("Send this output command immediately"));
            }
        }
    }

    ui.cbRobotModel->setToolTip(text("Change the selected robot model and its available controls"));
    ui.cbRobotDOF->setToolTip(text("Change controlled axes and send the corresponding robot configuration"));
    setupLayout->addWidget(ui.groupBox_3);
    setupLayout->addWidget(ui.groupBox_4);
    ui.groupBox_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.groupBox_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.groupBox_4->setTitle(text("Controlled axes (DOF)"));
    auto* motion = resetPanel(ui.frame_22);
    ui.frame->hide();
    ui.frame_24->hide();
    auto* motionTitle = new QLabel(text("Motion profile"));
    motionTitle->setProperty("robotSectionTitle", true);
    motion->addWidget(motionTitle);
    auto* profile = new QFormLayout;
    profile->setRowWrapPolicy(QFormLayout::WrapLongRows);
    const QList<QLineEdit*> fields = {ui.leAccel, ui.leJerk, ui.leStartSpeed, ui.leEndSpeed};
    const QList<QString> captions = {text("Acceleration (A) · mm/s²"), text("Jerk (J) · mm/s³"),
                                     text("Start speed (S) · mm/s"), text("End speed (E) · mm/s")};
    for (int i = 0; i < fields.size(); ++i) {
        fields[i]->setMinimumWidth(0);
        fields[i]->setMaximumWidth(QWIDGETSIZE_MAX);
        fields[i]->setAccessibleName(captions[i]);
        fields[i]->setToolTip(text("Press Enter to send this parameter to the selected robot"));
        profile->addRow(captions[i], fields[i]);
    }
    motion->addLayout(profile);
    setupLayout->addWidget(ui.frame_22);
    setupLayout->addStretch();
    ui.scrollArea_2->hide();
    UiTheme::polishWidgetTree(ui.tRobot);
}
