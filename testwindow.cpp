#include "testwindow.h"
#include "ui_testwindow.h"

#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QDebug>

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TestWindow), timer(new QTimer(this)) {
    ui->setupUi(this);

    // Kết nối sự kiện nút bấm mở camera
    connect(ui->openCameraButton, &QPushButton::clicked, this, &TestWindow::onOpenCameraButtonClicked);
    connect(timer, &QTimer::timeout, this, &TestWindow::captureFrame);

    // Thiết lập timer với thời gian lấy khung hình là 30ms (~33 fps)
    timer->setInterval(30);
}

TestWindow::~TestWindow() {
    if (webcam.isOpened()) {
        webcam.release();
    }
    delete ui;
}

void TestWindow::onOpenCameraButtonClicked() {
    if (webcam.isOpened()) {
        // Đóng camera nếu đang mở
        webcam.release();
        timer->stop();
        ui->openCameraButton->setText("Open Camera");
        qDebug() << "Camera closed.";
    } else {
        // Mở camera với ID = 0
        if (webcam.open(0)) {
            ui->openCameraButton->setText("Close Camera");
            timer->start();  // Bắt đầu lấy khung hình
            qDebug() << "Camera opened successfully.";
        } else {
            QMessageBox::warning(this, "Error", "Failed to open the camera.");
        }
    }
}

void TestWindow::captureFrame() {
    if (!webcam.isOpened()) {
        return;
    }

    cv::Mat frame;
    if (webcam.read(frame)) {
        // Chuyển đổi BGR (OpenCV) sang RGB (Qt)
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        displayFrame(qimg);
    } else {
        qDebug() << "Failed to capture frame.";
    }
}

void TestWindow::displayFrame(const QImage &frame) {
    // Hiển thị hình ảnh trên QLabel
    ui->cameraLabel->setPixmap(QPixmap::fromImage(frame));
}
