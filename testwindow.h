#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QCamera>
#include <QImage>
#include <QMainWindow>
#include <QMediaCaptureSession>
#include <QProcess>
#include <QVideoFrame>
#include <QVideoFrameFormat>
#include <QVideoSink>

class TestWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    QCamera *camera;                       // Camera object
    QVideoSink *videoSink;                 // Video sink to capture frames
    QMediaCaptureSession captureSession;   // Capture session binding camera and sink
    QProcess ffmpegProcess;                // Process for FFmpeg

    void setupCamera();    // Setup camera and probe
    void setupFFmpeg();    // Setup FFmpeg process

private slots:
    void captureFrame(const QVideoFrame &frame); // Slot to handle frame capture
};

#else
#include <QMainWindow>

// Stub declaration for Qt 5 builds where the Qt 6 multimedia APIs are absent.
class TestWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow() override;
};
#endif // QT_VERSION check

#endif // TESTWINDOW_H
