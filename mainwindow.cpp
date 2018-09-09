#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitVariables();
    InitEvents();

	HideExampleWidgets();
	InterpolateCircle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitEvents()
{
    connect(ui->pbConnect, SIGNAL(clicked(bool)), this, SLOT(ConnectDeltaRobot()));
	connect(ui->pbAddNewProgram, SIGNAL(clicked(bool)), this, SLOT(AddNewProgram()));
	connect(ui->pbSaveGcode, SIGNAL(clicked(bool)), this, SLOT(SaveProgram()));
	connect(ui->pbExecuteGcodes, SIGNAL(clicked(bool)), this, SLOT(ExecuteProgram()));

	connect(ui->pbHome, SIGNAL(clicked(bool)), this, SLOT(Home()));
	connect(ui->pbZ, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->pbY, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->pbX, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZValue(int)));
	connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPosition()));

	connect(DeltaParameter, SIGNAL(Moved(float, float, float)), this, SLOT(UpdatePositionValue(float, float, float)));
	connect(DeltaParameter, SIGNAL(FinishMoving()), this, SLOT(UpdateDeltaPosition()));

	connect(ui->pbHSV, SIGNAL(clicked(bool)), this, SLOT(OpenHSVPanel()));
}

void MainWindow::InitVariables()
{
    DeltaPort = new ConnectionManager(this);

	DeltaGcodeManager = new GcodeProgramManager(ui->wgProgramContainer, ui->pteGcodeArea, DeltaPort);
	
	DebugLB = ui->lbDebug;

	DeltaGcodeManager->LoadPrograms();
	
	DeltaParameter = new DeltaVisualizer(ui->t2D);
	DeltaParameter->setObjectName(QStringLiteral("wg2D"));
	DeltaParameter->setGeometry(QRect(50, 10, 300, 300));

	//------------ OpenGl Init ----------
	
	/*VisualArea = new GLWidget();
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(VisualArea);
    ui->wgOpenGl->setLayout(container);*/

	//---------- OpenCV Init -------------

    cap = cv::VideoCapture(0);
    Timer1 = new QTimer(this);
    connect(Timer1, SIGNAL(timeout()), this, SLOT(UpdateCameraScreen()));
    Timer1->start(50);
}

void MainWindow::ConnectDeltaRobot()
{
	if (ui->pbConnect->text() == "Connect" && !DeltaPort->IsConnect())
	{
		if (DeltaPort->FindDeltaRobot() == true)
		{
			ui->lbState->setText("Delta Robot is connected !");
			Debug(DeltaPort->GetNamePort());

			ui->pbConnect->setText("Disconnect");
		}
	}

	else if (ui->pbConnect->text() == "Disconnect")
	{
		ui->pbConnect->setText("Connect");
		ui->lbState->setText("Delta is not available !");

		if (DeltaPort->IsConnect())
			DeltaPort->Disconnect();
	}
}

void MainWindow::UpdateCameraScreen()
{
    cv::Mat mat;
    cap.read(mat);

    cv::cvtColor( mat, mat, cv::COLOR_BGR2GRAY );
    cv::blur( mat, mat, cv::Size(3,3) );
    cv::Canny( mat, mat, 100, 100 * 2 );
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours( mat, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    std::vector<cv::Rect> boundRect( contours.size() );
    std::vector<cv::Point2f>centers( contours.size() );
    std::vector<float>radius( contours.size() );

    for( size_t i = 0; i < contours.size(); i++ )
    {
        cv::approxPolyDP( contours[i], contours_poly[i], 3, true );
        boundRect[i] = boundingRect( contours_poly[i] );
        cv::minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
    }

    cv::Mat drawing = cv::Mat::zeros( mat.size(), CV_8UC3);
    cv::RNG rng(12345);

    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        cv::drawContours( drawing, contours_poly, (int)i, color );
        cv:: rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2 );
        cv::circle( drawing, centers[i], (int)radius[i], color, 2 );
    }

    QImage img = ImageTool::cvMatToQImage(drawing);
    ui->lbCameraArea->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::AddNewProgram()
{
	DeltaGcodeManager->AddNewProgram();
}

void MainWindow::SaveProgram()
{
	DeltaGcodeManager->SaveGcodeIntoFile();
}

void MainWindow::ExecuteProgram()
{
	if (DeltaPort->IsConnect())
	{
		QString exeGcodes = ui->pteGcodeArea->toPlainText();
		DeltaGcodeManager->ExecuteGcode(exeGcodes);
	}

	else
		Debug("Delta Robot is not connecting !");
}

void MainWindow::UpdateZValue(int z)
{
	ui->leZ->setText(QString::number(DeltaParameter->ZHome - z));
}

void MainWindow::UpdateDeltaPosition()
{
	DeltaParameter->X = ui->leX->text().toFloat();
	DeltaParameter->Y = ui->leY->text().toFloat();
	DeltaParameter->Z = ui->leZ->text().toFloat();

	ui->vsZAdjsution->setValue(DeltaParameter->ZHome - DeltaParameter->Z);
	DeltaParameter->ChangeXY(ui->leX->text().toFloat(), ui->leY->text().toFloat());

	DeltaGcodeManager->ExecuteGcode(QString("G01 X") + ui->leX->text() + QString(" Y") + ui->leY->text() + QString(" Z") + ui->leZ->text());
}

void MainWindow::UpdatePositionValue(float x, float y, float z)
{
	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));

	//UpdateDeltaPosition();
}

void MainWindow::Home()
{
	DeltaGcodeManager->ExecuteGcode("G28");

	ui->leX->setText(QString::number(DeltaParameter->XHome));
	ui->leY->setText(QString::number(DeltaParameter->YHome));
	ui->leZ->setText(QString::number(DeltaParameter->ZHome));

	DeltaParameter->X = DeltaParameter->XHome;
	DeltaParameter->Y = DeltaParameter->YHome;
	DeltaParameter->Z = DeltaParameter->ZHome;

	DeltaParameter->ChangeXY(0, 0);
	ui->vsZAdjsution->setValue(0);
}

void MainWindow::HideExampleWidgets()
{
	ui->frExProgram->setVisible(false);
}

void MainWindow::InterpolateCircle()
{
	float r = 120;
	int resolution = 120;
	float raMinAngle;
	int xO = 0;
	int yO = 0;
	int x;
	int y;
	float raAngle;
	QString gcode;

	raMinAngle = qDegreesToRadians(360.0f / resolution);

	for (int i = 0; i < resolution; i++)
	{
		raAngle = raMinAngle * i;
		x = xO + r * qCos(raAngle);
		y = yO + r * qSin(raAngle);
		gcode += QString("G01 X") + QString::number(x) + " Y" + QString::number(y) + "\n";
	}

	ui->pteGcodeArea->setPlainText(gcode);
}

void MainWindow::OpenHSVPanel()
{
	
}