#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H

#include <QMainWindow>
#include "robotmanager.h"

namespace Ui {
class MainWindowManager;
}

class MainWindowManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowManager(QWidget *parent = nullptr);
    ~MainWindowManager();


private:
    Ui::MainWindowManager *ui;
};

#endif // MAINWINDOWMANAGER_H
