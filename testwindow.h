#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QVideoFrame>
#include <QVideoFrameFormat>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QProcess>
#include <QImage>

class TestWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    QCamera *camera;          // Camera object
    QVideoSink *videoSink;    // Video sink to capture frames
    QMediaCaptureSession captureSession; // Capture session binding camera and sink
    QProcess ffmpegProcess;   // Process for FFmpeg

    void setupCamera();       // Setup camera and probe
    void setupFFmpeg();       // Setup FFmpeg process

private slots:
    void captureFrame(const QVideoFrame &frame); // Slot to handle frame capture
};

#endif // TESTWINDOW_H
