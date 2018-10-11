#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitVariables();
    InitEvents();

	hideExampleWidgets();
	//interpolateCircle();
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
	connect(ui->pbW, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->pbZ, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->pbY, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->pbX, SIGNAL(clicked(bool)), this, SLOT(UpdateDeltaPosition()));
	connect(ui->pbGrip, SIGNAL(clicked(bool)), this, SLOT(Grip()));
	connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZValue(int)));
	connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPosition()));

	connect(DeltaParameter, SIGNAL(Moved(float, float, float)), this, SLOT(UpdatePositionValue(float, float, float)));
	connect(DeltaParameter, SIGNAL(FinishMoving()), this, SLOT(UpdateDeltaPosition()));
	
	connect(ui->leTerminal, SIGNAL(returnPressed()), this, SLOT(TerminalTransmit()));
	connect(DeltaPort, SIGNAL(FinishReadLine(QString)), this, SLOT(PrintReceiveData(QString)));

	connect(DeltaPort, SIGNAL(DeltaResponeReady()), this, SLOT(NoticeConnected()));

	connect(ui->pbG01, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->pbG28, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->pbM03, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->pbM204, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));

	connect(ui->pbFormat, SIGNAL(clicked(bool)), this, SLOT(StandardFormatEditor()));

	connect(ui->pbHSV, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenHSVPanel()));
	connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadTestImage()));

}

void MainWindow::InitVariables()
{
    DeltaPort = new ConnectionManager();

	DeltaGcodeManager = new GcodeProgramManager(ui->wgProgramContainer, ui->pteGcodeArea, DeltaPort);
	
	DebugLB = ui->lbDebug;

	DeltaGcodeManager->LoadPrograms();
	
	DeltaParameter = new DeltaVisualizer(ui->t2D);
	DeltaParameter->setObjectName(QStringLiteral("wg2D"));
	DeltaParameter->setGeometry(QRect(50, 10, 300, 300));

	EditorTimer = new QTimer(this);
	//connect(EditorTimer, SIGNAL(timeout()), this, SLOT(RunSmartEditor()));
	//EditorTimer->start(500);

	//------------ OpenGl Init ----------
	
	/*VisualArea = new GLWidget();
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(VisualArea);
    ui->wgOpenGl->setLayout(container);*/

	//---------- OpenCV Init -------------

    /*cap = cv::VideoCapture(0);
    Timer1 = new QTimer(this);
    connect(Timer1, SIGNAL(timeout()), this, SLOT(UpdateCameraScreen()));
    Timer1->start(50);*/

	DeltaImageProcesser = new ImageProcesser(this);
	DeltaImageProcesser->SetProcessScreenPointer(ui->lbTestImage);
	DeltaImageProcesser->SetResultScreenPointer(ui->lbCameraArea);
}

void MainWindow::ConnectDeltaRobot()
{
	if (ui->pbConnect->text() == "Connect" && !DeltaPort->IsConnect())
	{
		DeltaPort->FindDeltaRobot();			
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
    /*cv::Mat mat;
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
    ui->lbCameraArea->setPixmap(QPixmap::fromImage(img));*/
}

void MainWindow::RunSmartEditor()
{
	
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
		QPushButton* pbExe = qobject_cast<QPushButton*>(sender());

		if (pbExe->text() == "Execute")
		{
			pbExe->setText("Stop");
		}
		else
		{
			pbExe->setText("Execute");
			DeltaGcodeManager->Stop();
			return;
		}

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
	DeltaParameter->W = ui->leW->text().toFloat();

	ui->vsZAdjsution->setValue(DeltaParameter->ZHome - DeltaParameter->Z);
	DeltaParameter->ChangeXY(ui->leX->text().toFloat(), ui->leY->text().toFloat());

	//DeltaGcodeManager->ExecuteGcode(QString("G01 X") + ui->leX->text() + QString(" Y") + ui->leY->text() + QString(" Z") + ui->leZ->text());
	DeltaPort->Send(QString("G01 X") + ui->leX->text() + QString(" Y") + ui->leY->text() + QString(" Z") + ui->leZ->text() + QString(" W") + ui->leW->text());
}

void MainWindow::UpdatePositionValue(float x, float y, float z)
{
	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));

	//UpdateDeltaPosition();
}

void MainWindow::Grip()
{
	if (ui->pbGrip->text() == "Grip")
	{
		ui->pbGrip->setText("Release");
		DeltaPort->Send(QString("G41 P0"));
	}
	else
	{
		ui->pbGrip->setText("Grip");
		DeltaPort->Send(QString("G41 P1"));
	}
}

void MainWindow::Home()
{
	DeltaGcodeManager->ExecuteGcode("G28");

	ui->leX->setText(QString::number(DeltaParameter->XHome));
	ui->leY->setText(QString::number(DeltaParameter->YHome));
	ui->leZ->setText(QString::number(DeltaParameter->ZHome));
	ui->leW->setText(QString::number(DeltaParameter->WHome));

	DeltaParameter->X = DeltaParameter->XHome;
	DeltaParameter->Y = DeltaParameter->YHome;
	DeltaParameter->Z = DeltaParameter->ZHome;
	DeltaParameter->W = DeltaParameter->WHome;

	DeltaParameter->ChangeXY(0, 0);
	ui->vsZAdjsution->setValue(0);
}

void MainWindow::AddGcodeLine()
{
	QPushButton* bt = qobject_cast<QPushButton*>(sender());

	if (bt->text() == "G01")
	{
		DeltaGcodeManager->AddG01(DeltaParameter->X, DeltaParameter->Y, DeltaParameter->Z);
	}
	if (bt->text() == "G28")
	{
		DeltaGcodeManager->AddG28();
	}
	if (bt->text() == "M03")
	{
		DeltaGcodeManager->AddM03(4000);
	}
	if (bt->text() == "M204")
	{
		DeltaGcodeManager->AddM204(8000);
	}
}

void MainWindow::TerminalTransmit()
{
	DeltaPort->Send(ui->leTerminal->text());
	ui->leTerminal->setText("");
}

void MainWindow::PrintReceiveData(QString msg)
{
	Debug(msg);
}

void MainWindow::NoticeConnected()
{
	ui->lbState->setText("Delta Robot is connected !");
	Debug(DeltaPort->GetNamePort());

	ui->pbConnect->setText("Disconnect");
}

void MainWindow::hideExampleWidgets()
{
	ui->frExProgram->setVisible(false);
}

void MainWindow::interpolateCircle()
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

void MainWindow::StandardFormatEditor()
{
	QString editorText = ui->pteGcodeArea->toPlainText();
	QList<QString> lines = editorText.split('\n');

	editorText = "";

	int i = 0;

	foreach(QString line, lines)
	{
		while (1)
		{
			if (line[0] == ' ')
			{
				line.replace(" ", "");
			}
			else
			{
				break;
			}
		}

		if (line[0] == 'N')
		{
			int spacePos = line.indexOf(' ');
			QString mS = line.mid(0, spacePos + 1);
			line.replace(mS, "");
		}

		while (1)
		{
			if (line[0] == ' ')
			{
				line.replace(" ", "");
			}
			else
			{
				break;
			}
		}

		if (line != "")
		{
			line = QString("N") + QString::number(i) + " " + line;
		}		
		
		editorText += line + "\n";
		i += 5;
	}

	ui->pteGcodeArea->setPlainText(editorText);
}
