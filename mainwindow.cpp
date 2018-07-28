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
}

void MainWindow::InitVariables()
{
    DeltaPort = new ConnectionManager(this);

	DeltaGcodeManager = new GcodeProgramManager(ui->wgProgramContainer, ui->pteGcodeArea);

	DebugLB = ui->lbDebug;

	DeltaGcodeManager->LoadPrograms();

	//------------ OpenGl Init ----------
	
	VisualArea = new GLWidget();
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(VisualArea);
    ui->wgOpenGl->setLayout(container);

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
		DeltaPort->ExecuteGcode(exeGcodes);
		Debug(QString("Sending ...") + exeGcodes);
	}

	else
		Debug("Delta Robot is not connecting !");
}

void MainWindow::HideExampleWidgets()
{
	ui->frExProgram->setVisible(false);
}
