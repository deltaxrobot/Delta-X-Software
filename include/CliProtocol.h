#pragma once

#include <QCryptographicHash>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

namespace CliProtocol {
constexpr int MaxMessageBytes = 4 * 1024 * 1024;
inline QString serverName()
{
    const auto user = QCryptographicHash::hash(QDir::homePath().toUtf8(),
                                              QCryptographicHash::Sha256).toHex().left(16);
    return QStringLiteral("deltax-cli-v1-") + QString::fromLatin1(user);
}
inline QByteArray encode(const QJsonObject& message)
{
    return QJsonDocument(message).toJson(QJsonDocument::Compact) + '\n';
}
}
