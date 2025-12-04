#include "testwindow.h"

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QDebug>

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent)
    , camera(nullptr)
    , videoSink(nullptr)
{
    setupCamera();
    setupFFmpeg();
    camera->start();
}

TestWindow::~TestWindow()
{
    if (camera) {
        camera->stop();
        delete camera;
    }
    if (videoSink) {
        delete videoSink;
    }
    ffmpegProcess.close();
}

void TestWindow::setupCamera()
{
    camera = new QCamera(this);
    videoSink = new QVideoSink(this);

    captureSession.setCamera(camera);
    captureSession.setVideoSink(videoSink);

    connect(videoSink, &QVideoSink::videoFrameChanged, this, &TestWindow::captureFrame);
}

void TestWindow::setupFFmpeg()
{
    // RTMP endpoint
    QString rtmpUrl = "rtmp://13.88.44.47/stream/live";

    int width = 640;
    int height = 480;
    int fps = 30;

    // ffmpeg command arguments
    QStringList args;
    args << "-y"
         << "-f" << "rawvideo"
         << "-vcodec" << "rawvideo"
         << "-pix_fmt" << "bgr24"
         << "-s" << QString("%1x%2").arg(width).arg(height)
         << "-r" << QString::number(fps)
         << "-i" << "-"
         << "-c:v" << "libx264"
         << "-pix_fmt" << "yuv420p"
         << "-preset" << "veryfast"
         << "-tune" << "zerolatency"
         << "-f" << "flv"
         << rtmpUrl;

    ffmpegProcess.setProcessChannelMode(QProcess::MergedChannels);
    ffmpegProcess.start("ffmpeg", args);

    if (!ffmpegProcess.waitForStarted()) {
        qCritical() << "Cannot start ffmpeg";
    }
}

void TestWindow::captureFrame(const QVideoFrame &frame)
{
    if (!frame.isValid()) {
        qWarning() << "Frame invalid";
        return;
    }

    QVideoFrame cloneFrame(frame);
    if (!cloneFrame.map(QVideoFrame::ReadOnly)) {
        qWarning() << "Cannot map frame for reading";
        return;
    }

    QImage::Format imgFormat = QVideoFrameFormat::imageFormatFromPixelFormat(cloneFrame.pixelFormat());
    QImage image((uchar *)cloneFrame.bits(0), cloneFrame.width(), cloneFrame.height(), cloneFrame.bytesPerLine(0), imgFormat);

    // Convert to RGB888 if needed
    QImage rgbImage = image.convertToFormat(QImage::Format_RGB888);

    uchar *data = rgbImage.bits();
    int dataSize = rgbImage.sizeInBytes();
    ffmpegProcess.write((const char *)data, dataSize);

    cloneFrame.unmap();
}

#else

// Qt 5 stub implementations to keep the project building without Qt 6 multimedia APIs.
TestWindow::TestWindow(QWidget *parent) : QMainWindow(parent) {}
TestWindow::~TestWindow() = default;

#endif // QT_VERSION check
