#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include "testcode.h"
#include <QThread>

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
};

#endif // TESTWINDOW_H
