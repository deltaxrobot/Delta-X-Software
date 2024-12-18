#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QVideoProbe>
#include <QVideoFrame>
#include <QProcess>
#include <QImage>

class TestWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    QCamera *camera;          // Camera object
    QVideoProbe *probe;       // Video probe to capture frames
    QProcess ffmpegProcess;   // Process for FFmpeg

    void setupCamera();       // Setup camera and probe
    void setupFFmpeg();       // Setup FFmpeg process

private slots:
    void captureFrame(const QVideoFrame &frame); // Slot to handle frame capture
};

#endif // TESTWINDOW_H
