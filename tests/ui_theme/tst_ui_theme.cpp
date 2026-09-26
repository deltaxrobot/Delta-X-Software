#include "CameraSelectionDialog.h"
#include "DrawingExporter.h"
#include "GcodeHighlighter.h"
#include "ModernDialog.h"
#include "PhoneCameraDialog.h"
#include "PhoneCameraServer.h"
#include "RobotPanelLayout.h"
#include "SettingsPanel.h"
#include "UiTheme.h"
#include <QSslSocket>
#include <QtTest>
#include <QtWidgets>
#include <cmath>
#include <opencv2/core/version.hpp>
#if CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 5)
#include <opencv2/objdetect.hpp>
#endif
#include "ui_FilterWindow.h"
#include "ui_MainWindow.h"
#include "ui_RobotWindow.h"

namespace
{
double luminance(const QColor& c)
{
    auto linear = [](double v)
    { return v <= .04045 ? v / 12.92 : std::pow((v + .055) / 1.055, 2.4); };
    return .2126 * linear(c.redF()) + .7152 * linear(c.greenF()) + .0722 * linear(c.blueF());
}
double contrast(const QColor& a, const QColor& b)
{
    const double x = luminance(a), y = luminance(b);
    return (qMax(x, y) + .05) / (qMin(x, y) + .05);
}
void snapshot(QWidget& widget, const QString& name)
{
    const QString directory = qEnvironmentVariable("DELTA_X_UI_SNAPSHOTS");
    if (directory.isEmpty())
        return;
    QDir().mkpath(directory);
    QVERIFY(widget.grab().save(directory + '/' + name + ".png"));
}
} // namespace

class UiThemeTest : public QObject
{
    Q_OBJECT
  private slots:
    void initTestCase()
    {
        QStandardPaths::setTestModeEnabled(true);
        QCoreApplication::setOrganizationName("DeltaXUiTests");
        QCoreApplication::setApplicationName("ui-theme-test");
#ifdef Q_OS_WIN
        // Windows offscreen QPA has no native font database by default.
        const QString fonts = qEnvironmentVariable("WINDIR") + "/Fonts/";
        QFontDatabase::addApplicationFont(fonts + "segoeui.ttf");
        QFontDatabase::addApplicationFont(fonts + "segoeuib.ttf");
        QFontDatabase::addApplicationFont(fonts + "consola.ttf");
        for (const QString& family :
             {QString("Sans Serif"), QString("MS Shell Dlg 2"), QString(".AppleSystemUIFont")})
            QFont::insertSubstitution(family, "Segoe UI");
#endif
    }
    void themes_data()
    {
        QTest::addColumn<QString>("theme");
        QTest::newRow("dark") << QStringLiteral("Dark");
        QTest::newRow("light") << QStringLiteral("Light");
    }
    void themes()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        QWidget gallery;
        auto* grid = new QGridLayout(&gallery);
        int row = 0;
        for (const QString& role :
             {QString("primary"), QString("success"), QString("warning"), QString("danger")})
        {
            auto* enabled = new QPushButton(role, &gallery);
            auto* disabled = new QPushButton(role + " (disabled)", &gallery);
            UiTheme::setControlRole(enabled, role);
            UiTheme::setControlRole(disabled, role);
            disabled->setEnabled(false);
            grid->addWidget(enabled, row, 0);
            grid->addWidget(disabled, row++, 1);
            enabled->ensurePolished();
            disabled->ensurePolished();
            QVERIFY2(contrast(enabled->palette().color(QPalette::ButtonText),
                              enabled->palette().color(QPalette::Button)) >= 4.5,
                     qPrintable(theme + ' ' + role + " text contrast"));
            QVERIFY(enabled->palette().color(QPalette::Button) !=
                    disabled->palette().color(QPalette::Disabled, QPalette::Button));
        }
        for (int state = 0; state < 3; ++state)
        {
            auto* checkbox = new QCheckBox(QString("Check state %1").arg(state));
            checkbox->setTristate(true);
            checkbox->setCheckState(static_cast<Qt::CheckState>(state));
            grid->addWidget(checkbox, row++, 0);
        }
        auto* radio = new QRadioButton("Selected radio");
        radio->setChecked(true);
        grid->addWidget(radio, row++, 0);
        auto* combo = new QComboBox;
        combo->addItems({"Camera source", "USB / GigE"});
        grid->addWidget(combo, row, 0);
        grid->addWidget(new QSpinBox, row++, 1);
        for (const QString& glyph :
             {QString("up-light"), QString("down-light"), QString("up-dark"), QString("down-dark"),
              QString("right-light"), QString("right-dark"), QString("check"), QString("mixed"),
              QString("dot")})
            QVERIFY2(!QIcon(":/icon/theme/" + glyph + ".svg").pixmap(16, 16).isNull(),
                     qPrintable(glyph));
        auto* icon = new QToolButton;
        QPixmap lowContrastIcon(16, 16);
        lowContrastIcon.fill(QColor("#777777"));
        icon->setIcon(QIcon(lowContrastIcon));
        icon->setMaximumSize(20, 20);
        icon->setToolTip("Save program");
        grid->addWidget(icon, row++, 0);
        auto* coloredIcon = new QPushButton("Colored artwork");
        QImage coloredArtwork(16, 16, QImage::Format_ARGB32);
        coloredArtwork.fill(Qt::transparent);
        for (int y = 2; y < 14; ++y)
            for (int x = 2; x < 14; ++x)
                coloredArtwork.setPixelColor(x, y, x < 8 ? QColor("#E53935") : QColor("#1565C0"));
        coloredIcon->setIcon(QIcon(QPixmap::fromImage(coloredArtwork)));
        grid->addWidget(coloredIcon, row++, 0);
        UiTheme::polishWidgetTree(&gallery);
        gallery.resize(550, 420);
        gallery.show();
        QCoreApplication::processEvents();
        QVERIFY(icon->width() >= 30);
        QVERIFY(icon->height() >= 30);
        QCOMPARE(icon->accessibleName(), QString("Save program"));
        QVERIFY(icon->property("deltaContrastIcon").toBool());
        QCOMPARE(icon->icon().pixmap(16, 16, QIcon::Normal, QIcon::Off).toImage().pixelColor(8, 8),
                 qApp->palette().color(QPalette::ButtonText));
        icon->setCheckable(true);
        icon->setChecked(true);
        QCOMPARE(icon->icon().pixmap(16, 16, QIcon::Normal, QIcon::On).toImage().pixelColor(8, 8),
                 qApp->palette().color(QPalette::HighlightedText));
        icon->setEnabled(false);
        QCOMPARE(icon->icon().pixmap(16, 16, QIcon::Disabled, QIcon::On).toImage().pixelColor(8, 8),
                 qApp->palette().color(QPalette::Disabled, QPalette::ButtonText));
        const QImage preserved =
            coloredIcon->icon().pixmap(16, 16, QIcon::Normal, QIcon::Off).toImage();
        QCOMPARE(preserved.pixelColor(4, 8), QColor("#E53935"));
        QCOMPARE(preserved.pixelColor(11, 8), QColor("#1565C0"));
        QCOMPARE(preserved.pixelColor(1, 8).alpha(), 0);
        snapshot(gallery, theme + "-controls");
        ModernDialog dialog;
        dialog.setTitle("Choose camera or project");
        dialog.setItems({"USB camera", "GigE camera"});
        dialog.show();
        QCoreApplication::processEvents();
        auto* ok = dialog.findChild<QPushButton*>("okButton");
        QVERIFY(ok);
        QVERIFY(ok->height() >= ok->sizeHint().height());
        snapshot(dialog, theme + "-dialog");
    }
    void phoneCameraLayout_data()
    {
        themes_data();
    }
    void phoneCameraLayout()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        PhoneCameraServer server;
        PhoneCameraDialog dialog(&server);
        dialog.show();
        QCoreApplication::processEvents();
        auto* toggle = dialog.findChild<QToolButton*>("phoneCameraSetupToggle");
        auto* setup = dialog.findChild<QWidget*>("phoneCameraSetup");
        auto* start = dialog.findChild<QPushButton*>("phoneCameraStart");
        QVERIFY(toggle);
        QVERIFY(setup);
        QVERIFY(start);
        toggle->setChecked(true);
        QCoreApplication::processEvents();
        QVERIFY(setup->isVisible());
        QVERIFY2(dialog.height() <= 760, "Phone pairing must fit a laptop-height display");
        for (auto* button : dialog.findChildren<QPushButton*>())
        {
            QVERIFY2(button->height() >= button->sizeHint().height(), qPrintable(button->text()));
            QVERIFY2(button->width() >= button->sizeHint().width(), qPrintable(button->text()));
        }
        snapshot(dialog, theme + "-phone-camera-setup");
        toggle->setChecked(false);
        QCoreApplication::processEvents();
        QVERIFY(!setup->isVisible());
        snapshot(dialog, theme + "-phone-camera");
        // Missing credentials should show the setup without blocking on the UI thread.
        start->click();
        QVERIFY(setup->isVisible());
        QVERIFY(!server.isListening());
    }
    void phoneCameraQr()
    {
#if CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 5)
        const auto openssl = QStandardPaths::findExecutable("openssl");
        if (openssl.isEmpty() || !QSslSocket::supportsSsl())
            QSKIP("QR pairing integration needs test TLS credentials");
        QTemporaryDir directory;
        QVERIFY(directory.isValid());
        const auto cert = directory.filePath("test.crt"), key = directory.filePath("test.key");
        QProcess process;
        process.start(openssl, {"req", "-x509", "-newkey", "rsa:2048", "-nodes", "-days", "1",
                                "-subj", "/CN=localhost", "-addext", "subjectAltName=IP:127.0.0.1",
                                "-keyout", key, "-out", cert});
        QVERIFY(process.waitForFinished(15000));
        QCOMPARE(process.exitCode(), 0);
        PhoneCameraServer server;
        PhoneCameraDialog dialog(&server);
        dialog.findChild<QLineEdit*>("phoneCameraCertificate")->setText(cert);
        dialog.findChild<QLineEdit*>("phoneCameraKey")->setText(key);
        auto* network = dialog.findChild<QComboBox*>("phoneCameraNetwork");
        network->addItem("Localhost (test only)", "127.0.0.1");
        network->setCurrentIndex(network->count() - 1);
        dialog.show();
        dialog.findChild<QPushButton*>("phoneCameraStart")->click();
        QVERIFY(server.isListening());
        const QImage qr = dialog.findChild<QLabel*>("phoneCameraQr")
                              ->pixmap()
                              .toImage()
                              .convertToFormat(QImage::Format_Grayscale8);
        QVERIFY(!qr.isNull());
        cv::Mat pixels(qr.height(), qr.width(), CV_8UC1, const_cast<uchar*>(qr.constBits()),
                       qr.bytesPerLine());
        QCOMPARE(QString::fromStdString(cv::QRCodeDetector().detectAndDecode(pixels)),
                 server.pairingUrl());
        snapshot(dialog, "phone-camera-qr");
        dialog.reject();
        QVERIFY(!server.isListening());
        QSettings settings;
        settings.remove("PhoneCamera");
#else
        QSKIP("QR encoder needs OpenCV 4.5+");
#endif
    }
    void syntaxContrastAndThemeSwitch()
    {
        QTextDocument document;
        GCodeHighlighter highlighter(&document);
        document.setPlainText("G1 X0\nIF #ready THEN\n; comment\nPclaimObject\n\"part\"");
        for (const QString& theme : {QString("Dark"), QString("Light"), QString("Dark")})
        {
            UiTheme::apply(*qApp, theme);
            QCoreApplication::processEvents();
            highlighter.rehighlight();
            for (QTextBlock block = document.begin(); block.isValid(); block = block.next())
            {
                for (const auto& range : block.layout()->formats())
                {
                    QVERIFY2(contrast(range.format.foreground().color(),
                                      qApp->palette().color(QPalette::Base)) >= 4.5,
                             qPrintable(theme + " syntax: " + block.text()));
                }
            }
        }
    }
    void cameraSelectionIdentifiesDevices_data()
    {
        themes_data();
    }
    void cameraSelectionIdentifiesDevices()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        CameraSelectionDialog dialog(nullptr, false);
        dialog.addTestCameraItem(2, "Logitech BRIO 4K Stream Edition", "USB / UVC",
                                 "Media Foundation", "up to 3840 × 2160 @ 30 fps",
                                 "usb#vid_046d&pid_085e#unit-a", true);
        dialog.addTestCameraItem(-1, "OBS Virtual Camera", "Virtual camera",
                                 "Unavailable to OpenCV", {}, "obs-virtual-camera", false, false);
        dialog.show();
        QCoreApplication::processEvents();
        auto* list = dialog.findChild<QListWidget*>("cameraList");
        auto* refresh = dialog.findChild<QPushButton*>("refreshButton");
        QVERIFY(list);
        QVERIFY(refresh);
        QCOMPARE(list->count(), 2);
        const QString firstAccessible = list->item(0)->data(Qt::AccessibleTextRole).toString();
        QVERIFY(firstAccessible.contains("Logitech BRIO 4K Stream Edition"));
        QVERIFY(firstAccessible.contains("3840 × 2160"));
        QVERIFY(firstAccessible.contains("VID:PID 046D:085E"));
        QVERIFY(firstAccessible.contains("Default"));
        QVERIFY(list->itemWidget(list->item(0)));
        QVERIFY(!(list->item(1)->flags() & Qt::ItemIsEnabled));
        QVERIFY(list->item(1)->data(Qt::AccessibleTextRole).toString().contains("Unavailable"));
        QVERIFY(dialog.width() >= 520);
        QVERIFY(dialog.height() >= 320);
        snapshot(dialog, theme + "-camera-selection");
    }
    void gcodeDirtyStateIgnoresPresentationChanges()
    {
        QTextDocument document;
        document.setPlainText(QStringLiteral("G28\nG1 X10"));
        const QString cleanText = document.toPlainText();
        document.setModified(false);

        QTextCursor cursor(&document);
        cursor.select(QTextCursor::Document);
        QTextCharFormat format;
        format.setFontPointSize(18.0);
        cursor.mergeCharFormat(format);

        QVERIFY(document.isModified());
        QCOMPARE(document.toPlainText(), cleanText);

        cursor.movePosition(QTextCursor::End);
        cursor.insertText(QStringLiteral("\nG1 Y20"));
        QVERIFY(document.toPlainText() != cleanText);
    }
    void formLayout_data()
    {
        themes_data();
    }
    void formLayout()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        QMainWindow window;
        Ui::RobotWindow ui;
        ui.setupUi(&window);
        const QSize jogMaximum = ui.pbContinuousBackward->maximumSize();
        UiTheme::prepareForm(
            &window, {ui.wConveyorCanvas, ui.ImageFrame, ui.lbImageForDrawing, ui.lbDrawingArea});
        for (QAbstractButton* button : window.findChildren<QAbstractButton*>())
        {
            if (button->icon().isNull() ||
                button->property("Func").toString() == QStringLiteral("Jogging"))
                continue;
            QVERIFY2(button->property("deltaNavigationIcon").toBool() ||
                         button->property("deltaContrastIcon").toBool() ||
                         button->property("preserveIconColors").toBool(),
                     qPrintable(button->objectName() + " has an unmanaged fixed-color icon"));
        }
        QCOMPARE(ui.pbContinuousBackward->maximumSize(), jogMaximum);
        DrawingExporter drawing(&window);
        drawing.SetDrawingParameterPointer(
            ui.lbImageForDrawing, ui.lbImageWidth, ui.lbImageHeight, ui.leHeightScale,
            ui.leWidthScale, ui.leSpace, ui.leDrawingThreshold, ui.hsDrawingThreshold,
            ui.cbReverseDrawing, ui.cbDrawMethod, ui.cbConversionTool);
        drawing.SetDrawingAreaWidget(ui.lbDrawingArea);
        drawing.SetGcodeEditor(ui.pteGcodeArea);
        drawing.SetEffector(ui.cbDrawingEffector);
        drawing.SetGcodeExportParameterPointer(ui.leSafeZHeight, ui.leTravelSpeed,
                                               ui.leDrawingSpeed, ui.leDrawingAcceleration);
        drawing.SetDrawingPointInPlane(ui.leADrawingPoint, ui.leBDrawingPoint, ui.leCDrawingPoint);
        drawing.SetupPanel(ui.tDrawing);
        ui.lbDrawingArea->replacePaths({{{-20, -20}, {20, -20}, {20, 20}, {-20, 20}, {-20, -20}}});
        QCOMPARE(ui.wObjectDetecting->minimumHeight(), 0);
        QCOMPARE(ui.wgJoggingScrollWidget->minimumHeight(), 0);
        QVERIFY(ui.pbSaveGcode->maximumWidth() >= 30);
        QVERIFY(ui.pbReadEncoder->maximumHeight() >= ui.pbReadEncoder->sizeHint().height());
        window.resize(1600, 950);
        window.show();
        QCoreApplication::processEvents();
        for (QToolButton* button : ui.frame_31->findChildren<QToolButton*>())
        {
            QVERIFY2(ui.frame_31->rect().contains(
                         QRect(button->mapTo(ui.frame_31, QPoint()), button->size())),
                     qPrintable(button->objectName() + " clipped by jogging panel"));
            if (button->property("jogStep").toBool())
                QCOMPARE(button->size(), QSize(48, 48));
        }
        for (int index = 0; index < ui.twModule->count(); ++index)
        {
            ui.twModule->setCurrentIndex(index);
            QCoreApplication::processEvents();
            snapshot(window, theme + QString("-workspace-%1").arg(index));
            if (ui.twModule->currentWidget() == ui.tDrawing)
            {
                QVERIFY(ui.lbDrawingArea->isVisible());
                QVERIFY(ui.lbDrawingArea->width() >= 240);
                QVERIFY(ui.pbExportDrawingGcodes->isVisible());
                snapshot(*ui.tDrawing, theme + "-drawing");
            }
        }
        for (int index = 0; index < ui.twDevices->count(); ++index)
        {
            ui.twDevices->setCurrentIndex(index);
            QCoreApplication::processEvents();
            snapshot(*ui.DeviceTabManagerWidget, theme + QString("-device-%1").arg(index));
        }
    }
    void mainFormLayout_data()
    {
        themes_data();
    }
    void robotWorkspace_data()
    {
        themes_data();
    }
    void robotWorkspace()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        QMainWindow form;
        Ui::RobotWindow ui;
        ui.setupUi(&form);
        UiTheme::prepareForm(&form);
        QObject* inputParent = ui.pbReadI0X3->parent();
        QObject* inputOptionParent = ui.cbToggle0X3->parent();
        QSignalSpy homeCommands(ui.pbHome, &QToolButton::clicked);
        QSignalSpy jogCommands(ui.pbForward, &QToolButton::pressed);
        QSignalSpy outputCommands(ui.pbPumpX3, &QPushButton::clicked);
        QSignalSpy dofCommands(ui.cbRobotDOF, qOverload<int>(&QComboBox::currentIndexChanged));
        RobotPanelLayout::setup(ui);
        RobotPanelLayout::setup(ui); // Idempotent; no duplicated pages/bindings.
        QCOMPARE(homeCommands.count(), 0);
        QCOMPARE(jogCommands.count(), 0);
        QCOMPARE(outputCommands.count(), 0);
        QCOMPARE(dofCommands.count(), 0);
        QCOMPARE(ui.pbReadI0X3->parent(), inputParent);
        QCOMPARE(ui.cbToggle0X3->parent(), inputOptionParent);
        QVERIFY(!ui.leW->isEnabled());
        auto* tabs = ui.tRobot->findChild<QTabWidget*>("robotControlTabs");
        QVERIFY(tabs);
        QCOMPARE(tabs->count(), 3);
        ui.tRobot->setParent(nullptr);
        QScopedPointer<QWidget> panel(ui.tRobot);
        ui.pbConnectRobot->setText("Disconnect");
        ui.lbComName->setText("COM123");
        panel->show();
        for (int dof : {0, 3})
        {
            ui.cbRobotDOF->setCurrentIndex(dof); // Isolated form: no device/controller.
            for (int width : {380, 480, 720})
            {
                panel->resize(width, 850);
                QTest::qWait(20);
                QCOMPARE(panel->width(), width);
                QVERIFY(ui.cbSelectedRobot->width() >= ui.cbSelectedRobot->sizeHint().width());
                for (int index = 0; index < tabs->count(); ++index)
                {
                    tabs->setCurrentIndex(index);
                    QTest::qWait(20);
                    auto* scroll = qobject_cast<QScrollArea*>(tabs->widget(index));
                    QVERIFY(scroll);
                    QVERIFY2(scroll->horizontalScrollBar()->maximum() == 0,
                             qPrintable(QString("%1 width=%2 dof=%3 scroll=%4")
                                            .arg(scroll->objectName())
                                            .arg(width)
                                            .arg(dof)
                                            .arg(scroll->horizontalScrollBar()->maximum())));
                    if (index == 0)
                    {
                        for (QToolButton* button : ui.frame_31->findChildren<QToolButton*>())
                        {
                            if (!button->isVisible())
                                continue;
                            QVERIFY2(ui.frame_31->rect().contains(QRect(
                                         button->mapTo(ui.frame_31, QPoint()), button->size())),
                                     qPrintable(button->objectName() + " escapes jogging panel"));
                        }
                        QVERIFY(!ui.frame_31->geometry().intersects(ui.frame_32->geometry()));
                    }
                    snapshot(*panel,
                             theme + QString("-robot-%1-%2-%3").arg(dof).arg(width).arg(index));
                }
            }
        }
        QCOMPARE(ui.pbForward->size(), QSize(48, 48));
        QCOMPARE(ui.pbContinuousForward->height(), 10);
        QCOMPARE(ui.pbContinuousLeft->width(), 10);
        QVERIFY(ui.leW->isEnabled());
        QVERIFY(ui.pbPlusPitch->isEnabled());
        QCOMPARE(homeCommands.count(), 0);
        QCOMPARE(jogCommands.count(), 0);
        QCOMPARE(outputCommands.count(), 0);
    }
    void robotConnectionAndProgramControls_data()
    {
        themes_data();
    }
    void robotConnectionAndProgramControls()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        QMainWindow window;
        Ui::RobotWindow ui;
        ui.setupUi(&window);
        UiTheme::prepareForm(&window);
        ui.cbEditGcodeLock->setText("Safe line run");
        // Exercise the actual Designer connection card at a narrow dock width.
        ui.frame_12->setParent(nullptr);
        QScopedPointer<QFrame> connectionCard(ui.frame_12);
        connectionCard->resize(500, connectionCard->sizeHint().height());
        connectionCard->show();
        window.resize(1600, 950);
        window.show();
        QCoreApplication::processEvents();
        QVERIFY(ui.cbEditGcodeLock->width() >= ui.cbEditGcodeLock->sizeHint().width());
        for (QComboBox* combo : {ui.cbRobotModel, ui.cbRobotDOF})
        {
            QVERIFY2(combo->width() >= combo->sizeHint().width(), qPrintable(combo->objectName()));
            QVERIFY(connectionCard->rect().contains(
                QRect(combo->mapTo(connectionCard.data(), QPoint()), combo->size())));
        }
        QVERIFY(ui.groupBox_3->y() > ui.groupBox->y());
        snapshot(*connectionCard, theme + "-robot-connection");
    }
    void mainFormLayout()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        QMainWindow window;
        Ui::MainWindow ui;
        ui.setupUi(&window);
        ui.wgLeftPanel->setProperty("navigationRail", true);
        UiTheme::prepareForm(&window);
        SettingsPanel settings(ui.twSettingsCategories);
        UiTheme::polishWidgetTree(&window);
        ui.stackedWidget->setCurrentWidget(ui.page);
        window.resize(1280, 800);
        window.show();
        QCoreApplication::processEvents();
        QVERIFY2(window.width() <= 1280, "Main shell cannot shrink to 1280 logical pixels");
        for (QToolButton* button : ui.wgLeftPanel->findChildren<QToolButton*>())
            QVERIFY2(button->width() >= button->fontMetrics().horizontalAdvance(button->text()) + 8,
                     qPrintable(button->objectName() + " navigation text clipped"));
        for (QPushButton* button : ui.pSetting->findChildren<QPushButton*>())
        {
            if (button->property("colorSwatch").toBool())
            {
                button->ensurePolished();
                QVERIFY(contrast(button->palette().color(QPalette::ButtonText),
                                 button->palette().color(QPalette::Button)) >= 4.5);
            }
        }
        for (QWidget* page : {ui.pVariable, ui.pOperator, ui.pHome, ui.pSetting, ui.pProject})
        {
            ui.swPageStack->setCurrentWidget(page);
            QCoreApplication::processEvents();
            snapshot(window, theme + "-main-" + page->objectName());
            if (page == ui.pSetting)
            {
                for (int index = 0; index < ui.twSettingsCategories->count(); ++index)
                {
                    ui.twSettingsCategories->setCurrentIndex(index);
                    QCoreApplication::processEvents();
                    snapshot(window, theme + QString("-settings-%1").arg(index));
                }
            }
        }
    }
    void navigationThemeSwitch()
    {
        QMainWindow window;
        Ui::MainWindow ui;
        ui.setupUi(&window);
        ui.wgLeftPanel->setProperty("navigationRail", true);
        UiTheme::prepareForm(&window);
        for (const QString& theme : {QString("Dark"), QString("Light"), QString("Dark")})
        {
            UiTheme::apply(*qApp, theme);
            for (bool selected : {false, true})
            {
                ui.tbProject->setProperty("navigationSelected", selected);
                const QImage pixels = ui.tbProject->icon().pixmap(20, 20).toImage();
                const QColor expected = qApp->palette().color(selected ? QPalette::HighlightedText
                                                                       : QPalette::ButtonText);
                int opaquePixels = 0;
                for (int y = 0; y < pixels.height(); ++y)
                {
                    for (int x = 0; x < pixels.width(); ++x)
                    {
                        const QColor pixel = pixels.pixelColor(x, y);
                        if (pixel.alpha() == 255)
                        {
                            QCOMPARE(pixel, expected);
                            ++opaquePixels;
                        }
                    }
                }
                QVERIFY(opaquePixels > 5);
            }
        }
    }
    void filterFormLayout_data()
    {
        themes_data();
    }
    void filterFormLayout()
    {
        QFETCH(QString, theme);
        UiTheme::apply(*qApp, theme);
        QDialog dialog;
        Ui::FilterWindow ui;
        ui.setupUi(&dialog);
        UiTheme::prepareForm(&dialog);
        dialog.resize(1000, 750);
        dialog.show();
        QCoreApplication::processEvents();
        snapshot(dialog, theme + "-filter");
        QVERIFY2(dialog.height() <= 750, "Image filter controls exceed a laptop-height window");
    }
};
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    if (app.arguments().contains("--robot-preview"))
    {
        // Native visual review without RobotWindow, device objects, settings or
        // command connections. Safe even when a real cell is running elsewhere.
        UiTheme::apply(app, QStringLiteral("Dark"));
        QMainWindow form;
        Ui::RobotWindow ui;
        ui.setupUi(&form);
        UiTheme::prepareForm(&form);
        ui.cbRobotModel->setCurrentIndex(2);
        ui.gbX1->hide();
        ui.gbOutputXS->hide();
        ui.gbInputXS->hide();
        for (QLineEdit* field : {ui.leX, ui.leY, ui.leZ, ui.leW, ui.leU, ui.leV})
            field->setText("0");
        ui.leVelocity->setText("200");
        RobotPanelLayout::setup(ui);
        UiTheme::setControlRole(ui.pbConnectRobot, "primary");
        UiTheme::setControlRole(ui.tbDisableRobot, "warning");
        ui.tRobot->setParent(nullptr);
        QScopedPointer<QWidget> panel(ui.tRobot);
        panel->setWindowTitle("Robot panel preview - no hardware commands");
        panel->resize(560, 900);
        panel->show();
        return app.exec();
    }
    UiThemeTest test;
    return QTest::qExec(&test, argc, argv);
}
#include "tst_ui_theme.moc"
