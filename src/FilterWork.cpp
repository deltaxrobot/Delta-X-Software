#include "FilterWork.h"

#include <QtGlobal>

#include <opencv2/imgproc.hpp>

FilterWork::FilterWork(QObject* parent)
    : QObject(parent)
{
}

void FilterWork::DoFilter(cv::Mat mat, QList<int> parameters, bool isInvert,
                          int blurSize)
{
    try {
        if (mat.empty())
            return;

        if (parameters.size() == 1) {
            cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
            cv::threshold(mat, mat, parameters.at(0), 255, cv::THRESH_BINARY);
        } else if (parameters.size() == 6) {
            const cv::Scalar minimum(parameters.at(0), parameters.at(2),
                                     parameters.at(4));
            const cv::Scalar maximum(parameters.at(1), parameters.at(3),
                                     parameters.at(5));
            cv::cvtColor(mat, mat, cv::COLOR_BGR2HSV);
            cv::inRange(mat, minimum, maximum, mat);
        } else {
            emit FilterFailed(QStringLiteral("Unsupported filter parameter count: %1")
                                  .arg(parameters.size()));
            return;
        }

        if (isInvert)
            cv::bitwise_not(mat, mat);

        int safeBlurSize = qMax(1, blurSize);
        if ((safeBlurSize % 2) == 0)
            ++safeBlurSize;
        cv::medianBlur(mat, mat, safeBlurSize);
        emit FinishedFilter(mat);
    } catch (const cv::Exception& exception) {
        emit FilterFailed(QString::fromUtf8(exception.what()));
    }
}
