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
	connect(ui->cbPump, SIGNAL(stateChanged(int)), this, SLOT(SetPump(int)));
	connect(ui->vsZAdjsution, SIGNAL(valueChanged(int)), this, SLOT(UpdateZValue(int)));
	connect(ui->vsZAdjsution, SIGNAL(sliderReleased()), this, SLOT(UpdateDeltaPosition()));

	connect(DeltaParameter, SIGNAL(Moved(float, float, float)), this, SLOT(UpdatePositionValue(float, float, float)));
	connect(DeltaParameter, SIGNAL(FinishMoving()), this, SLOT(UpdateDeltaPosition()));
	
	connect(ui->leTerminal, SIGNAL(returnPressed()), this, SLOT(TerminalTransmit()));

	connect(DeltaPort, SIGNAL(FinishReadLine(QString)), this, SLOT(PrintReceiveData(QString)));
	connect(DeltaPort, SIGNAL(DeltaResponeReady()), this, SLOT(NoticeConnected()));
	connect(DeltaPort, SIGNAL(InHomePosition(float, float, float)), this, SLOT(UpdateHomePosition(float, float, float)));

	connect(ui->pbG01, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->pbG28, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->pbM03, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));
	connect(ui->pbM204, SIGNAL(clicked(bool)), this, SLOT(AddGcodeLine()));

	connect(ui->pbFormat, SIGNAL(clicked(bool)), this, SLOT(StandardFormatEditor()));

	connect(ui->pbFilter, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(OpenParameterPanel()));
	connect(ui->pbLoadTestImage, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadTestImage()));
	connect(ui->pbLoadCamera, SIGNAL(clicked(bool)), DeltaImageProcesser, SLOT(LoadCamera()));
	connect(ui->pbObjectRect, SIGNAL(clicked(bool)), ui->lbScreenStreamer, SLOT(rectObject()));
	connect(ui->pbObjectLine, SIGNAL(clicked(bool)), ui->lbScreenStreamer, SLOT(lineObject()));
}

void MainWindow::InitVariables()
{
    DeltaPort = new ConnectionManager();
	DeltaPort->SetBaudrate(9600);

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

	DeltaImageProcesser = new ImageProcesser(this);
	DeltaImageProcesser->SetProcessScreenPointer(ui->lbTestImage);
	DeltaImageProcesser->SetResultScreenPointer(ui->lbScreenStreamer);
	DeltaImageProcesser->SetFPSInputBox(ui->leFPS);
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

		if (pbExe->isChecked())
		{

		}
		else
		{
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
	DeltaPort->Send(QString("G01 X") + ui->leX->text() + QString(" Y") + ui->leY->text() + QString(" Z") + ui->leZ->text() + QString(" W") + ui->leW->text() + "\n");
}

void MainWindow::UpdatePositionValue(float x, float y, float z)
{
	ui->leX->setText(QString::number(x));
	ui->leY->setText(QString::number(y));
	ui->leZ->setText(QString::number(z));

	UpdateDeltaPosition();
}

void MainWindow::UpdateHomePosition(float x, float y, float z)
{
	DeltaParameter->XHome = x;
	DeltaParameter->YHome = y;
	DeltaParameter->ZHome = z;

	UpdatePositionValue(x, y, z);
}

void MainWindow::Grip()
{
	if (ui->pbGrip->text() == "Grip")
	{
		ui->pbGrip->setText("Release");
		DeltaPort->Send(QString("G42 V0"));
	}
	else
	{
		ui->pbGrip->setText("Grip");
		DeltaPort->Send(QString("G42 V1"));
	}
}

void MainWindow::SetPump(int value)
{
	if (value == 0)
	{
		DeltaPort->Send(QString("G41 P0"));
	}
	else
	{
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
	msg.replace("\n", "");
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
			if (line[0] != ';')
			{
				line = QString("N") + QString::number(i) + " " + line;
			}
		}		
		
		editorText += line + "\n";
		i += 5;
	}

	ui->pteGcodeArea->setPlainText(editorText);
}
