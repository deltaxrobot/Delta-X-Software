#ifndef IMAGEPIPELINECONTROLLER_H
#define IMAGEPIPELINECONTROLLER_H

#include <QObject>
#include <QString>
#include "QtMatrixCompat.h"
#include <QRectF>
#include <QPolygonF>
#include <opencv2/core.hpp>
#include "Object.h"

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
    void updateFrameSize(cv::Mat mat);
    void requestFrameSize();
    void requestColorFilterInput();
    void inputImage(cv::Mat mat);
    void inputColorFilterValues(QList<int> values);
    void inputColorFilterBlur(int blur);
    void inputColorFilterInvert(bool inverted);
    void inputChessboardSize(cv::Size size);
    void inputChessboardQuadrangle(cv::Mat mat);
    void inputCalibPoints(QPolygonF poly);
    void inputVisibleObjects(QVector<Object> objects);
    void inputObjectFilter(Object obj);
    void connectPipeline();

    // Latest mapping matrix (updated from MappingMatrixNode output)
    QMatrix currentMappingMatrix() const { return m_latestMappingMatrix; }
    FrameSnapshot currentFrameSnapshot() const { return m_frameSnapshot; }

signals:
    void mappingMatrixUpdated(QMatrix matrix);
    void frameSizeUpdated(int width, int height);
    void colorFilterInputReady(cv::Mat image);

private:
    TaskNode* node(const QString& name) const;

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
};

#endif // IMAGEPIPELINECONTROLLER_H
