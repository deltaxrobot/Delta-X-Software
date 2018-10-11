#ifndef HSVWINDOW_H
#define HSVWINDOW_H

#include <QDialog>
#include <qslider.h>
#include <qlabel.h>

namespace Ui {
class HSVWindow;
}

class HSVWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HSVWindow(QWidget *parent = 0);
    ~HSVWindow();

	void InitEvents();
	void InitVariables();

	QSlider *sPara[6];
	QLabel *lbPara[6];

	bool IsInvertBinary();

public slots:
	void UpdateSliderValueToLabel();
signals:
	void ValueChanged(int minH, int maxH, int minS, int maxS, int minV, int maxV);
	void ValueChanged(int threshold);

private:
    Ui::HSVWindow *ui;
};

#endif // HSVWINDOW_H
