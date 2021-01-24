//#pragma once
//#include <QApplication>

//#ifdef Q_OS_WIN

//#include <QMainWindow>

//#include <QtCore/qt_windows.h>

//#include <QObject>
//#include <qframe.h>
//#include <qtimer.h>
//#include <qapplication.h>
//#include <qdatetime.h>
//#include <qmessagebox.h>
//#include <UnityTool.h>
//#include <mainwindow.h>
//#include <TCPConnectionManager.h>

//class MainWindow;

//extern HWND unityHWND;

//class ROS : public QObject
//{
//	Q_OBJECT

//public:
//	ROS(QObject *parent, QFrame* panel, QString app);
//	~ROS();
		
//public slots:
//	void Run();
//	void SetConnectionManager(TCPConnectionManager* connectionMg);
//	void ResetView();
//	void ProcessROS();
//	QFrame* GetDisplay();
//	void Foces();
//	QLayout* GetDisplayLayout();
//	bool IsRunning();
//	void Close();
//	void G01_Relative(float x, float y, float z);
	
//private:
//	QFrame* display;
//	QWidget* displayParent;

//	QTimer* ROSTimer;
//	QString appPath;

//	TCPConnectionManager* connectionManager = NULL;

//	QHBoxLayout *displayLayout;
//	MainWindow* mParent;

//	void initROS();
//	bool isRunning = false;
//};

//#endif // Q_OS_WIN
