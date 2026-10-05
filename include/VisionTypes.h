#ifndef VISIONTYPES_H
#define VISIONTYPES_H

#include <QMetaType>
#include <QString>
#include <QtGlobal>
#include <opencv2/core.hpp>

#include "VisionDetections.h"

// Immutable-at-the-boundary frame envelope used from acquisition through
// detection. Producers must call detached() before crossing a thread boundary
// so a VideoCapture/SDK buffer can never be overwritten under a consumer.
struct VisionFrame
{
    quint64 frameId = 0;
    quint64 requestId = 0; // 0 means preview/continuous capture.
    int trackingId = 0;
    qint64 capturedAtMonotonicNs = 0;
    QString source;
    cv::Mat image;

    bool isValid() const
    {
        return frameId != 0 && !image.empty() && image.cols > 0 && image.rows > 0;
    }

    VisionFrame detached() const
    {
        VisionFrame copy = *this;
        copy.image = image.clone();
        return copy;
    }
};

Q_DECLARE_METATYPE(VisionFrame)

#endif // VISIONTYPES_H
