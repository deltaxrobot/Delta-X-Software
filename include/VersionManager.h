#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QMessageBox>
#include <QVersionNumber>
#include <QDesktopServices>
#include <QApplication>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslSocket>
#include <QDebug>

class VersionManager : public QWidget
{
    Q_OBJECT
public:
    VersionManager(QWidget *parent = 0);

    QString CurrentVersion = "";
    QString UpdateVersion = "";
    QString SoftwareName = "";
    QString CheckVersionUrl = "";
    QString NewVersionSoftwareUrl = "";

    void CheckNewVersion(bool isPopUp);

    QNetworkAccessManager *HttpManager;

public slots:
    void FinishedRequest(QNetworkReply *reply);
};

#endif // VERSIONMANAGER_H
