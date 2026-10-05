#ifndef CAMERACALIBRATION_H
#define CAMERACALIBRATION_H

#include <QList>
#include <QSize>
#include <QString>

#include <opencv2/core.hpp>

namespace CameraCalibration
{

struct Profile
{
    bool isValid = false;
    cv::Mat cameraMatrix;
    cv::Mat distortionCoefficients;
    QSize imageSize;
    QSize boardSize;
    double squareSizeMm = 0.0;
    double rmsErrorPx = 0.0;
    double maximumViewErrorPx = 0.0;
    int sampleCount = 0;
    QString calibratedAt;
};

struct Result
{
    bool isValid = false;
    QString errorMessage;
    Profile profile;
    int acceptedImages = 0;
    int rejectedImages = 0;
};

Result calibrate(const QList<cv::Mat>& images, const QSize& innerCornerCount,
                 double squareSizeMm, double maximumRmsErrorPx = 1.5);

bool undistort(const Profile& profile, const cv::Mat& source, cv::Mat& destination,
               QString* errorMessage = nullptr);

bool saveToVariables(const QString& projectName, const QString& variableName,
                     const Profile& profile);
bool loadFromVariables(const QString& projectName, const QString& variableName,
                       Profile& profile, QString* errorMessage = nullptr);

} // namespace CameraCalibration

#endif // CAMERACALIBRATION_H
