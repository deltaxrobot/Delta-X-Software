#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QImage>
#include <opencv2/opencv.hpp>

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private slots:
    void onOpenCameraButtonClicked();
    void captureFrame();
    void displayFrame(const QImage &frame);

private:
    Ui::TestWindow *ui;
    cv::VideoCapture webcam;
    QTimer *timer;
    QThread *cameraThread;
};

#endif // TESTWINDOW_H
