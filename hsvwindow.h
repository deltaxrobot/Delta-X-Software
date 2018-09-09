#ifndef HSVWINDOW_H
#define HSVWINDOW_H

#include <QDialog>

namespace Ui {
class HSVWindow;
}

class HSVWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HSVWindow(QWidget *parent = 0);
    ~HSVWindow();

private:
    Ui::HSVWindow *ui;
};

#endif // HSVWINDOW_H
