#ifndef FILTERWORK_H
#define FILTERWORK_H

#include <QList>
#include <QObject>
#include <QString>

#include <opencv2/core.hpp>

class FilterWork : public QObject
{
    Q_OBJECT

public:
    enum Algorithm
    {
        THRESHOLD = 0,
        HSV
    };

    explicit FilterWork(QObject* parent = nullptr);

public slots:
    void DoFilter(cv::Mat mat, QList<int> parameters, bool isInvert, int blurSize);

signals:
    void FinishedFilter(cv::Mat result);
    void FilterFailed(const QString& message);
};

#endif // FILTERWORK_H
