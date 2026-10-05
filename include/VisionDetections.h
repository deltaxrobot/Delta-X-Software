#ifndef VISIONDETECTIONS_H
#define VISIONDETECTIONS_H

#include <QMetaType>
#include <QString>
#include <QVector>
#include <QtGlobal>

#include "ObjectInfo.h"

struct VisionDetections
{
    quint64 frameId = 0;
    quint64 requestId = 0;
    int trackingId = 0;
    QString coordinateSpace = QStringLiteral("conveyor");
    QVector<ObjectInfo> objects;
};

Q_DECLARE_METATYPE(VisionDetections)

#endif // VISIONDETECTIONS_H
