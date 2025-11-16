#include "testwindow.h"
#include <QDebug>

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent)
    , camera(nullptr)
    , videoSink(nullptr)
{
    // Khởi tạo camera và ffmpeg
    setupCamera();
    setupFFmpeg();

    // Bắt đầu camera
    camera->start();
}

TestWindow::~TestWindow() {
    if (camera) {
        camera->stop();
        delete camera;
    }
    if (videoSink) {
        delete videoSink;
    }
    ffmpegProcess.close();
}

void TestWindow::setupCamera() {
    // Khởi tạo camera
    camera = new QCamera(this);
    videoSink = new QVideoSink(this);

    captureSession.setCamera(camera);
    captureSession.setVideoSink(videoSink);

    connect(videoSink, &QVideoSink::videoFrameChanged, this, &TestWindow::captureFrame);
}

void TestWindow::setupFFmpeg() {
    // Cấu hình đường dẫn RTMP
    QString rtmpUrl = "rtmp://13.88.44.47/stream/live";

    // Thông số giả định, bạn có thể thay đổi theo camera
    int width = 640;
    int height = 480;
    int fps = 30;

    // Thiết lập lệnh ffmpeg
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

    // Khởi chạy ffmpeg
    ffmpegProcess.setProcessChannelMode(QProcess::MergedChannels);
    ffmpegProcess.start("ffmpeg", args);

    if (!ffmpegProcess.waitForStarted()) {
        qCritical() << "Không thể khởi động ffmpeg!";
    }
}

void TestWindow::captureFrame(const QVideoFrame &frame) {
    if (!frame.isValid()) {
        qWarning() << "Frame không hợp lệ!";
        return;
    }

    QVideoFrame cloneFrame(frame);
    if (!cloneFrame.map(QVideoFrame::ReadOnly)) {
        qWarning() << "Không thể ánh xạ frame để đọc dữ liệu!";
        return;
    }

    // Chuyển frame thành QImage
    QImage::Format imgFormat = QVideoFrameFormat::imageFormatFromPixelFormat(cloneFrame.pixelFormat());
    QImage image((uchar *)cloneFrame.bits(0), cloneFrame.width(), cloneFrame.height(), cloneFrame.bytesPerLine(0), imgFormat);

    // Chuyển đổi sang RGB888 nếu cần
    QImage rgbImage = image.convertToFormat(QImage::Format_RGB888);

    // Gửi dữ liệu thô vào ffmpeg qua stdin
    uchar *data = rgbImage.bits();
    int dataSize = rgbImage.sizeInBytes(); // Thay thế byteCount() bằng sizeInBytes()
    ffmpegProcess.write((const char *)data, dataSize);

    cloneFrame.unmap(); // Giải phóng frame
}
