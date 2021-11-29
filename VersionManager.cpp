#include "VersionManager.h"

VersionManager::VersionManager(QWidget *parent) :
    QWidget(parent)
{
    HttpManager = new QNetworkAccessManager(this);
    connect(HttpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(FinishedRequest(QNetworkReply*)));
}

void VersionManager::CheckNewVersion(bool isPopUp)
{
    QString Url = QString("%1?software=%2&info=version").arg(CheckVersionUrl).arg(SoftwareName);
    QNetworkRequest request = QNetworkRequest(QUrl("http://imwi.space/admin/server.php?software=DeltaXSoftware&info=version"));
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    HttpManager->get(request);
}

void VersionManager::FinishedRequest(QNetworkReply *reply)
{
    UpdateVersion = QString(reply->readAll());

    QVersionNumber currentVersion = QVersionNumber::fromString(UpdateVersion);
    QVersionNumber appVersion = QVersionNumber::fromString(CurrentVersion);
    int compare = QVersionNumber::compare(appVersion, currentVersion);

    if (compare < 0)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "There is a new version of Delta X Software", "Do you want to update?",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QUrl myUrl(NewVersionSoftwareUrl);
            QDesktopServices::openUrl(myUrl);
            QApplication::closeAllWindows();
            QApplication::quit();
        }
    }
}
