#include "CameraCalibration.h"

#include "VariableManager.h"

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QtMath>

#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

namespace
{
bool finiteMatrix(const cv::Mat& matrix)
{
    if (matrix.empty())
        return false;
    cv::Mat converted;
    matrix.convertTo(converted, CV_64F);
    for (int row = 0; row < converted.rows; ++row) {
        for (int column = 0; column < converted.cols; ++column) {
            if (!qIsFinite(converted.at<double>(row, column)))
                return false;
        }
    }
    return true;
}

QJsonArray matrixToJson(const cv::Mat& matrix)
{
    cv::Mat converted;
    matrix.convertTo(converted, CV_64F);
    QJsonArray values;
    for (int row = 0; row < converted.rows; ++row) {
        for (int column = 0; column < converted.cols; ++column)
            values.append(converted.at<double>(row, column));
    }
    return values;
}

bool jsonToMatrix(const QJsonValue& value, int rows, int columns, cv::Mat& matrix)
{
    if (!value.isArray())
        return false;
    const QJsonArray array = value.toArray();
    if (array.size() != rows * columns)
        return false;
    matrix = cv::Mat(rows, columns, CV_64F);
    for (int i = 0; i < array.size(); ++i) {
        if (!array[i].isDouble() || !qIsFinite(array[i].toDouble()))
            return false;
        matrix.at<double>(i / columns, i % columns) = array[i].toDouble();
    }
    return true;
}
} // namespace

namespace CameraCalibration
{

Result calibrate(const QList<cv::Mat>& images, const QSize& innerCornerCount,
                 double squareSizeMm, double maximumRmsErrorPx)
{
    Result result;
    if (innerCornerCount.width() < 3 || innerCornerCount.height() < 3) {
        result.errorMessage = QStringLiteral("Chessboard must have at least 3 x 3 inner corners");
        return result;
    }
    if (!qIsFinite(squareSizeMm) || squareSizeMm <= 0.0) {
        result.errorMessage = QStringLiteral("Chessboard square size must be greater than zero");
        return result;
    }
    if (images.size() < 8) {
        result.errorMessage = QStringLiteral("At least 8 calibration images are required");
        return result;
    }

    const cv::Size board(innerCornerCount.width(), innerCornerCount.height());
    cv::Size imageSize;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    for (const cv::Mat& image : images) {
        if (image.empty()) {
            ++result.rejectedImages;
            continue;
        }
        if (imageSize.empty())
            imageSize = image.size();
        if (image.size() != imageSize) {
            ++result.rejectedImages;
            continue;
        }
        cv::Mat gray;
        if (image.channels() == 1)
            gray = image;
        else if (image.channels() == 4)
            cv::cvtColor(image, gray, cv::COLOR_BGRA2GRAY);
        else
            cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Point2f> corners;
        const bool found = cv::findChessboardCorners(
            gray, board, corners,
            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK);
        if (!found) {
            ++result.rejectedImages;
            continue;
        }
        cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
                         cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,
                                          40, 1.0e-4));
        imagePoints.push_back(corners);
        ++result.acceptedImages;
    }
    if (imagePoints.size() < 8) {
        result.errorMessage = QStringLiteral("Chessboard was detected in only %1 images; at least 8 are required")
                                  .arg(imagePoints.size());
        return result;
    }

    std::vector<cv::Point3f> boardPoints;
    boardPoints.reserve(static_cast<size_t>(board.area()));
    for (int row = 0; row < board.height; ++row) {
        for (int column = 0; column < board.width; ++column)
            boardPoints.emplace_back(column * squareSizeMm, row * squareSizeMm, 0.0f);
    }
    std::vector<std::vector<cv::Point3f>> objectPoints(imagePoints.size(), boardPoints);
    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distortion = cv::Mat::zeros(8, 1, CV_64F);
    std::vector<cv::Mat> rotations;
    std::vector<cv::Mat> translations;
    double rms = 0.0;
    try {
        rms = cv::calibrateCamera(objectPoints, imagePoints, imageSize,
                                  cameraMatrix, distortion, rotations, translations,
                                  cv::CALIB_RATIONAL_MODEL,
                                  cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,
                                                   100, 1.0e-9));
    } catch (const cv::Exception& error) {
        result.errorMessage = QStringLiteral("OpenCV calibration failed: %1")
                                  .arg(QString::fromUtf8(error.what()));
        return result;
    }
    if (!qIsFinite(rms) || !finiteMatrix(cameraMatrix) || !finiteMatrix(distortion) ||
        cameraMatrix.at<double>(0, 0) <= 0.0 || cameraMatrix.at<double>(1, 1) <= 0.0) {
        result.errorMessage = QStringLiteral("Calibration produced an invalid camera model");
        return result;
    }

    double maximumViewError = 0.0;
    for (size_t i = 0; i < objectPoints.size(); ++i) {
        std::vector<cv::Point2f> projected;
        cv::projectPoints(objectPoints[i], rotations[i], translations[i],
                          cameraMatrix, distortion, projected);
        const double error = cv::norm(imagePoints[i], projected, cv::NORM_L2) /
                             std::sqrt(static_cast<double>(projected.size()));
        maximumViewError = std::max(maximumViewError, error);
    }

    result.profile.cameraMatrix = cameraMatrix.clone();
    result.profile.distortionCoefficients = distortion.clone();
    result.profile.imageSize = QSize(imageSize.width, imageSize.height);
    result.profile.boardSize = innerCornerCount;
    result.profile.squareSizeMm = squareSizeMm;
    result.profile.rmsErrorPx = rms;
    result.profile.maximumViewErrorPx = maximumViewError;
    result.profile.sampleCount = static_cast<int>(imagePoints.size());
    result.profile.calibratedAt = QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs);
    result.profile.isValid = rms <= maximumRmsErrorPx && maximumViewError <= maximumRmsErrorPx * 2.5;
    result.isValid = result.profile.isValid;
    if (!result.isValid) {
        result.errorMessage = QStringLiteral("Calibration quality is too low (RMS %1 px, worst view %2 px)")
                                  .arg(rms, 0, 'f', 3)
                                  .arg(maximumViewError, 0, 'f', 3);
    }
    return result;
}

bool undistort(const Profile& profile, const cv::Mat& source, cv::Mat& destination,
               QString* errorMessage)
{
    if (!profile.isValid || !finiteMatrix(profile.cameraMatrix) ||
        !finiteMatrix(profile.distortionCoefficients)) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Intrinsic camera profile is invalid");
        return false;
    }
    if (source.empty()) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Camera frame is empty");
        return false;
    }
    cv::Mat adjusted = profile.cameraMatrix.clone();
    if (profile.imageSize.width() <= 0 || profile.imageSize.height() <= 0) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Intrinsic camera profile has no image size");
        return false;
    }
    if (source.cols != profile.imageSize.width() || source.rows != profile.imageSize.height()) {
        const double sourceAspect = static_cast<double>(source.cols) / source.rows;
        const double profileAspect = static_cast<double>(profile.imageSize.width()) / profile.imageSize.height();
        if (qAbs(sourceAspect - profileAspect) > 1.0e-3) {
            if (errorMessage)
                *errorMessage = QStringLiteral("Frame aspect ratio does not match the intrinsic calibration");
            return false;
        }
        const double scaleX = static_cast<double>(source.cols) / profile.imageSize.width();
        const double scaleY = static_cast<double>(source.rows) / profile.imageSize.height();
        adjusted.at<double>(0, 0) *= scaleX;
        adjusted.at<double>(0, 2) *= scaleX;
        adjusted.at<double>(1, 1) *= scaleY;
        adjusted.at<double>(1, 2) *= scaleY;
    }
    try {
        cv::undistort(source, destination, adjusted, profile.distortionCoefficients);
    } catch (const cv::Exception& error) {
        if (errorMessage)
            *errorMessage = QString::fromUtf8(error.what());
        return false;
    }
    return !destination.empty();
}

bool saveToVariables(const QString& projectName, const QString& variableName,
                     const Profile& profile)
{
    if (!profile.isValid || !finiteMatrix(profile.cameraMatrix) ||
        !finiteMatrix(profile.distortionCoefficients))
        return false;
    QJsonObject json;
    json[QStringLiteral("schemaVersion")] = 1;
    json[QStringLiteral("cameraMatrix")] = matrixToJson(profile.cameraMatrix);
    json[QStringLiteral("distortionCoefficients")] = matrixToJson(profile.distortionCoefficients.reshape(1, 1));
    json[QStringLiteral("distortionCount")] = static_cast<int>(profile.distortionCoefficients.total());
    json[QStringLiteral("imageWidth")] = profile.imageSize.width();
    json[QStringLiteral("imageHeight")] = profile.imageSize.height();
    json[QStringLiteral("boardColumns")] = profile.boardSize.width();
    json[QStringLiteral("boardRows")] = profile.boardSize.height();
    json[QStringLiteral("squareSizeMm")] = profile.squareSizeMm;
    json[QStringLiteral("rmsErrorPx")] = profile.rmsErrorPx;
    json[QStringLiteral("maximumViewErrorPx")] = profile.maximumViewErrorPx;
    json[QStringLiteral("sampleCount")] = profile.sampleCount;
    json[QStringLiteral("calibratedAt")] = profile.calibratedAt;
    VariableManager::instance().updateVarScoped(
        projectName, variableName,
        QString::fromUtf8(QJsonDocument(json).toJson(QJsonDocument::Compact)));
    return true;
}

bool loadFromVariables(const QString& projectName, const QString& variableName,
                       Profile& profile, QString* errorMessage)
{
    const QVariant stored = VariableManager::instance().getVarScoped(projectName, variableName);
    if (!stored.isValid() || stored.toString().trimmed().isEmpty()) {
        if (errorMessage)
            *errorMessage = QStringLiteral("No intrinsic camera profile is stored");
        return false;
    }
    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(stored.toString().toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Intrinsic camera profile JSON is invalid");
        return false;
    }
    const QJsonObject json = document.object();
    if (json.value(QStringLiteral("schemaVersion")).toInt() != 1) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Intrinsic camera profile version is unsupported");
        return false;
    }
    Profile parsed;
    const int distortionCount = json.value(QStringLiteral("distortionCount")).toInt();
    if (!jsonToMatrix(json.value(QStringLiteral("cameraMatrix")), 3, 3, parsed.cameraMatrix) ||
        distortionCount < 4 || distortionCount > 14 ||
        !jsonToMatrix(json.value(QStringLiteral("distortionCoefficients")), 1,
                      distortionCount, parsed.distortionCoefficients)) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Intrinsic camera profile matrices are invalid");
        return false;
    }
    parsed.imageSize = QSize(json.value(QStringLiteral("imageWidth")).toInt(),
                             json.value(QStringLiteral("imageHeight")).toInt());
    parsed.boardSize = QSize(json.value(QStringLiteral("boardColumns")).toInt(),
                             json.value(QStringLiteral("boardRows")).toInt());
    parsed.squareSizeMm = json.value(QStringLiteral("squareSizeMm")).toDouble();
    parsed.rmsErrorPx = json.value(QStringLiteral("rmsErrorPx")).toDouble();
    parsed.maximumViewErrorPx = json.value(QStringLiteral("maximumViewErrorPx")).toDouble();
    parsed.sampleCount = json.value(QStringLiteral("sampleCount")).toInt();
    parsed.calibratedAt = json.value(QStringLiteral("calibratedAt")).toString();
    parsed.isValid = parsed.imageSize.width() > 0 && parsed.imageSize.height() > 0 &&
                     parsed.sampleCount >= 8 && qIsFinite(parsed.rmsErrorPx) &&
                     parsed.rmsErrorPx >= 0.0 && finiteMatrix(parsed.cameraMatrix) &&
                     finiteMatrix(parsed.distortionCoefficients);
    if (!parsed.isValid) {
        if (errorMessage)
            *errorMessage = QStringLiteral("Intrinsic camera profile failed validation");
        return false;
    }
    profile = parsed;
    return true;
}

} // namespace CameraCalibration
