#include "VersionManager.h"

VersionManager::VersionManager(QWidget *parent) :
    QWidget(parent)
{
    HttpManager = new QNetworkAccessManager(this);
    connect(HttpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(FinishedRequest(QNetworkReply*)));
}

void VersionManager::CheckNewVersion(bool isPopUp)
{
    QUrl url("https://raw.githubusercontent.com/trungdoanhong/DeltaXSoftware/1.2-Ver/version.json");
    QNetworkRequest request = QNetworkRequest(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    HttpManager->get(request);

    if (!QSslSocket::supportsSsl()) {
        qDebug() << "SSL/TLS không được hỗ trợ. Lỗi khởi tạo TLS có thể do thiếu OpenSSL.";
    }
}

void VersionManager::FinishedRequest(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        QVersionNumber latestVersion = QVersionNumber::fromString(jsonObject["latest"].toString());
        QVersionNumber currentVersion = QVersionNumber::fromString(CurrentVersion);

        if (QVersionNumber::compare(currentVersion, latestVersion) < 0)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "There is a new version of Delta X Software", "Do you want to update?",
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                NewVersionSoftwareUrl = jsonObject["versions"].toObject()[latestVersion.toString()].toObject()["url"].toString();
                QDesktopServices::openUrl(NewVersionSoftwareUrl);
//                QApplication::closeAllWindows();
//                QApplication::quit();
            }
        }
    }

    else {
        qDebug() << "Lỗi khi kiểm tra phiên bản: " << reply->errorString();
    }
    reply->deleteLater();
}
