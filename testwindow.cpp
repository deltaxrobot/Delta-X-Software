#include "testwindow.h"
#include <QDebug>

TestWindow::TestWindow(QWidget *parent) : QMainWindow(parent) {
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
    if (probe) {
        delete probe;
    }
    ffmpegProcess.close();
}

void TestWindow::setupCamera() {
    // Khởi tạo camera
    camera = new QCamera;
    probe = new QVideoProbe;

    // Kết nối probe để bắt frame
    if (!probe->setSource(camera)) {
        qCritical() << "Không thể kết nối probe với camera!";
        return;
    }

    connect(probe, &QVideoProbe::videoFrameProbed, this, &TestWindow::captureFrame);
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
    cloneFrame.map(QAbstractVideoBuffer::ReadOnly); // Đảm bảo frame được ánh xạ đúng cách

    // Chuyển frame thành QImage
    QImage::Format imgFormat = QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat());
    QImage image((uchar *)cloneFrame.bits(0), cloneFrame.width(), cloneFrame.height(), cloneFrame.bytesPerLine(0), imgFormat);

    // Chuyển đổi sang RGB888 nếu cần
    QImage rgbImage = image.convertToFormat(QImage::Format_RGB888);

    // Gửi dữ liệu thô vào ffmpeg qua stdin
    uchar *data = rgbImage.bits();
    int dataSize = rgbImage.sizeInBytes(); // Thay thế byteCount() bằng sizeInBytes()
    ffmpegProcess.write((const char *)data, dataSize);

    cloneFrame.unmap(); // Giải phóng frame
}
