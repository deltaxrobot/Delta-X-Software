#ifndef IMAGEPIPELINECONTROLLER_H
#define IMAGEPIPELINECONTROLLER_H

#include <QObject>
#include <QString>
#include "QtMatrixCompat.h"
#include <QRectF>
#include <QPolygonF>
#include <opencv2/core.hpp>
#include <QQueue>
#include <QTimer>
#include "Object.h"
#include "VisionTypes.h"
#include "CameraCalibration.h"

Q_DECLARE_METATYPE(cv::Size)

struct FrameSnapshot
{
    int width = 0;
    int height = 0;
};

class ImageProcessing;
class TaskNode;
class SocketConnectionManager;

/*
 * Lightweight controller to manage image-processing pipeline toggles without
 * spreading TaskNode wiring logic across the UI code.
 * It only adjusts node pass-through flags and connects/disconnects algorithm-specific
 * outputs; all heavy image work remains inside existing TaskNode implementations.
 */
class ImagePipelineController : public QObject
{
    Q_OBJECT
public:
    explicit ImagePipelineController(ImageProcessing* processing, QObject* parent = nullptr);

    // Enable/disable warp & crop steps (keeps existing behaviour of EditImage)
    void configureWarpCrop(bool warpEnabled, bool cropEnabled);

    // Toggle auto-resize step
    void configureAutoResize(bool autoResizeEnabled);

    // Switch algorithm wiring between blobs / circles / external script
    void configureAlgorithm(const QString& algorithmName, SocketConnectionManager* connectionManager);

    // Register output delivery for UI display
    void setDisplayTarget(QObject* displayReceiver);
    // Register overlay drawing target (polygons) for object/circle detection
    void setOverlayTarget(QObject* overlayReceiver);

public slots:
    void inputResize(cv::Size size);
    void inputCropArea(QRectF rect);
    void inputPerspectiveQuadrangle(QPolygonF quad);
    void inputMappingPolygon(QPolygonF poly);
    void inputMappingMatrix(QMatrix matrix);
    void invalidateMapping(QString reason = QString());
    void updateFrameSize(cv::Mat mat);
    void requestFrameSize();
    void requestColorFilterInput();
    void inputImage(cv::Mat mat);
    void inputFrame(VisionFrame frame);
    void setIntrinsicCalibration(CameraCalibration::Profile profile);
    void clearIntrinsicCalibration();
    void inputColorFilterValues(QList<int> values);
    void inputColorFilterBlur(int blur);
    void inputColorFilterInvert(bool inverted);
    void inputVisibleObjects(QVector<Object> objects);
    void inputObjectFilter(Object obj);
    void connectPipeline();
    void inputExternalDetections(VisionDetections detections);
    void inputExternalFailure(int trackingId, quint64 frameId, quint64 requestId,
                              QString reason);
    void inputExternalStatus(bool connected, QString peer);

    // Latest mapping matrix (updated from MappingMatrixNode output)
    QMatrix currentMappingMatrix() const { return m_latestMappingMatrix; }
    bool hasValidMapping() const { return m_mappingValid; }
    FrameSnapshot currentFrameSnapshot() const { return m_frameSnapshot; }

signals:
    void mappingMatrixUpdated(QMatrix matrix);
    void frameSizeUpdated(int width, int height);
    void colorFilterInputReady(cv::Mat image);
    void detectionsReady(VisionDetections detections);
    void frameRejected(int trackingId, quint64 frameId, quint64 requestId, QString reason);
    void externalFrameReady(VisionFrame frame);
    void externalResponseIgnored(quint64 frameId, quint64 requestId, int trackingId,
                                 QString reason);
    void mappingValidityChanged(bool valid, QString reason);

private:
    TaskNode* node(const QString& name) const;
    void setPassThrough(TaskNode* taskNode, bool passThrough);
    void startNextFrame();
    void finishActiveFrame();
    void handleMappedDetections(QVector<ObjectInfo> objects, QString legacyListName);
    QVector<ObjectInfo> mapExternalImageObjects(const QVector<ObjectInfo>& objects) const;
    static bool isFiniteInvertibleMatrix(const QMatrix& matrix);

private slots:
    void forwardExternalImage(cv::Mat image);

private:

    ImageProcessing* m_processing;
    TaskNode* m_resizeImageNode = nullptr;
    TaskNode* m_warpImageNode = nullptr;
    TaskNode* m_cropImageNode = nullptr;
    TaskNode* m_colorFilterNode = nullptr;
    TaskNode* m_getObjectsNode = nullptr;
    TaskNode* m_findCirclesNode = nullptr;
    TaskNode* m_mappingMatrixNode = nullptr;
    TaskNode* m_displayImageNode = nullptr;
    TaskNode* m_getImageNode = nullptr;

    FrameSnapshot m_frameSnapshot;
    QMatrix m_latestMappingMatrix;
    bool m_mappingConnectionEstablished = false;
    bool m_mappingValid = false;
    QString m_mappingInvalidReason = QStringLiteral("Camera mapping has not been calibrated");
    QString m_algorithmName = QStringLiteral("Find Blobs");
    QQueue<VisionFrame> m_pendingFrames;
    VisionFrame m_activeFrame;
    bool m_frameInFlight = false;
    int m_maxPendingFrames = 8;
    QTimer m_frameTimeout;
    CameraCalibration::Profile m_intrinsicCalibration;
};

#endif // IMAGEPIPELINECONTROLLER_H
