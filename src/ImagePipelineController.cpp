#include "ImagePipelineController.h"

#include "ImageProcessing.h"
#include "SocketConnectionManager.h"
#include "TaskNode.h"

#include <QObject>
#include <QtMath>
#include "QtMatrixCompat.h"

ImagePipelineController::ImagePipelineController(ImageProcessing* processing, QObject* parent)
    : QObject(parent),
      m_processing(processing)
{
    if (!m_processing)
        return;

    qRegisterMetaType<QMatrix>("QMatrix");
    qRegisterMetaType<VisionFrame>("VisionFrame");
    qRegisterMetaType<VisionDetections>("VisionDetections");

    m_resizeImageNode = node("ResizeImageNode");
    m_warpImageNode = node("WarpImageNode");
    m_cropImageNode = node("CropImageNode");
    m_colorFilterNode = node("ColorFilterNode");
    m_getObjectsNode = node("GetObjectsNode");
    m_findCirclesNode = node("FindCirclesNode");
    m_mappingMatrixNode = node("MappingMatrixNode");
    m_displayImageNode = node("DisplayImageNode");
    m_getImageNode = node("GetImageNode");

    connectPipeline();

    m_frameTimeout.setSingleShot(true);
    m_frameTimeout.setInterval(4000);
    connect(&m_frameTimeout, &QTimer::timeout, this, [this]() {
        if (!m_frameInFlight)
            return;
        emit frameRejected(m_activeFrame.trackingId, m_activeFrame.frameId,
                           m_activeFrame.requestId,
                           QStringLiteral("Vision pipeline timed out"));
        finishActiveFrame();
    });

    connect(m_processing, &ImageProcessing::mappedDetectedObjects,
            this, &ImagePipelineController::handleMappedDetections);

    if (m_mappingMatrixNode)
    {
        // Keep a single connection; UniqueConnection with functor triggers assert in Qt6
        auto matrixSignal = static_cast<void (TaskNode::*)(QMatrix)>(&TaskNode::HadOutput);
        QObject::disconnect(m_mappingMatrixNode, matrixSignal, this, nullptr);
        connect(m_mappingMatrixNode,
                matrixSignal,
                this,
                [this](QMatrix matrix) {
                    inputMappingMatrix(matrix);
                });
    }
}

TaskNode* ImagePipelineController::node(const QString& name) const
{
    return m_processing ? m_processing->GetNode(name) : nullptr;
}

void ImagePipelineController::configureWarpCrop(bool warpEnabled, bool cropEnabled)
{
    if (!m_warpImageNode || !m_cropImageNode)
        return;

    // Mirror old logic in RobotWindow::EditImage
    if (!warpEnabled && cropEnabled)
    {
        setPassThrough(m_warpImageNode, true);
        setPassThrough(m_cropImageNode, false);
    }
    else if (warpEnabled && cropEnabled)
    {
        setPassThrough(m_warpImageNode, false);
        setPassThrough(m_cropImageNode, false);
    }
    else if (!warpEnabled && !cropEnabled)
    {
        setPassThrough(m_warpImageNode, true);
        setPassThrough(m_cropImageNode, true);
    }
    else if (warpEnabled && !cropEnabled)
    {
        setPassThrough(m_warpImageNode, false);
        setPassThrough(m_cropImageNode, true);
    }
    invalidateMapping(QStringLiteral("Warp/crop configuration changed"));
}

void ImagePipelineController::configureAutoResize(bool autoResizeEnabled)
{
    if (!m_resizeImageNode)
        return;

    // Auto resize checked => Resize node runs (IsPass = false)
    setPassThrough(m_resizeImageNode, !autoResizeEnabled);
    invalidateMapping(QStringLiteral("Resize configuration changed"));
}

void ImagePipelineController::configureAlgorithm(const QString& algorithmName, SocketConnectionManager* connectionManager)
{
    TaskNode* visibleObjectsNode = node("VisibleObjectsNode");
    if (!m_colorFilterNode || !m_getObjectsNode || !m_findCirclesNode || !m_cropImageNode || !visibleObjectsNode)
        return;

    m_algorithmName = algorithmName;

    // Clear previous dynamic connections
    QObject::disconnect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_getObjectsNode, SLOT(Input(cv::Mat)));
    QObject::disconnect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_findCirclesNode, SLOT(Input(cv::Mat)));
    QObject::disconnect(m_getObjectsNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)));
    QObject::disconnect(m_findCirclesNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)));
    if (connectionManager)
    {
        QObject::disconnect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)),
                            this, SLOT(forwardExternalImage(cv::Mat)));
        QObject::disconnect(connectionManager, SIGNAL(externalDetectionsReceived(VisionDetections)),
                            this, SLOT(inputExternalDetections(VisionDetections)));
        QObject::disconnect(connectionManager,
                            SIGNAL(externalVisionFrameFailed(int,quint64,quint64,QString)),
                            this,
                            SLOT(inputExternalFailure(int,quint64,quint64,QString)));
        QObject::disconnect(connectionManager,
                            SIGNAL(externalVisionStatusChanged(bool,QString)),
                            this, SLOT(inputExternalStatus(bool,QString)));
    }

    if (algorithmName == "Find Blobs")
    {
        QObject::connect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_getObjectsNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
        QObject::connect(m_getObjectsNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)), Qt::UniqueConnection);
    }
    else if (algorithmName == "Find Circles")
    {
        QObject::connect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_findCirclesNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
        QObject::connect(m_findCirclesNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)), Qt::UniqueConnection);
    }
    else if (algorithmName == "External Script" && connectionManager)
    {
        QObject::connect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)),
                         this, SLOT(forwardExternalImage(cv::Mat)), Qt::UniqueConnection);
        QObject::connect(connectionManager, SIGNAL(externalDetectionsReceived(VisionDetections)),
                         this, SLOT(inputExternalDetections(VisionDetections)), Qt::UniqueConnection);
        QObject::connect(connectionManager,
                         SIGNAL(externalVisionFrameFailed(int,quint64,quint64,QString)),
                         this,
                         SLOT(inputExternalFailure(int,quint64,quint64,QString)),
                         Qt::UniqueConnection);
        QObject::connect(connectionManager,
                         SIGNAL(externalVisionStatusChanged(bool,QString)),
                         this, SLOT(inputExternalStatus(bool,QString)),
                         Qt::UniqueConnection);
        // Keep getObjects path for external script outputs (e.g., from socket)
        QObject::connect(m_getObjectsNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)), Qt::UniqueConnection);
    }
}

void ImagePipelineController::setDisplayTarget(QObject* displayReceiver)
{
    if (!m_displayImageNode || !displayReceiver)
        return;

    // connect DisplayImageNode output to receiver slot SetImage(QPixmap)
    QObject::connect(m_displayImageNode, SIGNAL(HadOutput(QPixmap)),
                     displayReceiver, SLOT(SetImage(QPixmap)),
                     Qt::UniqueConnection);
}

void ImagePipelineController::setOverlayTarget(QObject* overlayReceiver)
{
    if (!overlayReceiver)
        return;

    // Draw polygons from blob detection
    if (m_getObjectsNode)
    {
        QObject::connect(m_getObjectsNode, SIGNAL(HadOutput(QList<QPolygonF>)),
                         overlayReceiver, SLOT(DrawObjects(QList<QPolygonF>)),
                         Qt::UniqueConnection);
    }

    // Draw polygons from circle detection
    if (m_findCirclesNode)
    {
        QObject::connect(m_findCirclesNode, SIGNAL(HadOutput(QList<QPolygonF>)),
                         overlayReceiver, SLOT(DrawObjects(QList<QPolygonF>)),
                         Qt::UniqueConnection);
    }
}

void ImagePipelineController::inputResize(cv::Size size)
{
    if (m_resizeImageNode)
    {
        QMetaObject::invokeMethod(m_resizeImageNode, [node = m_resizeImageNode, size]() {
            node->Input(size);
        }, Qt::QueuedConnection);
    }
    invalidateMapping(QStringLiteral("Image resize changed"));
}

void ImagePipelineController::inputCropArea(QRectF rect)
{
    if (m_cropImageNode)
    {
        QMetaObject::invokeMethod(m_cropImageNode, [node = m_cropImageNode, rect]() {
            node->Input(rect);
        }, Qt::QueuedConnection);
    }
    invalidateMapping(QStringLiteral("Crop area changed"));
}

void ImagePipelineController::inputPerspectiveQuadrangle(QPolygonF quad)
{
    TaskNode* perspective = node("GetPerspectiveNode");
    if (perspective)
    {
        QMetaObject::invokeMethod(perspective, [perspective, quad]() {
            perspective->Input(quad);
        }, Qt::QueuedConnection);
    }
    invalidateMapping(QStringLiteral("Perspective transform changed"));
}

void ImagePipelineController::inputMappingPolygon(QPolygonF poly)
{
    if (m_mappingMatrixNode)
    {
        QMetaObject::invokeMethod(m_mappingMatrixNode, [node = m_mappingMatrixNode, poly]() {
            node->Input(poly);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::inputMappingMatrix(QMatrix matrix)
{
    if (!isFiniteInvertibleMatrix(matrix)) {
        invalidateMapping(QStringLiteral("Mapping matrix is singular or contains invalid values"));
        return;
    }

    m_latestMappingMatrix = matrix;
    m_mappingValid = true;
    m_mappingInvalidReason.clear();
    TaskNode* visibleObjectsNode = node("VisibleObjectsNode");
    if (visibleObjectsNode) {
        QMetaObject::invokeMethod(visibleObjectsNode, [visibleObjectsNode, matrix]() {
            visibleObjectsNode->Input(matrix);
        }, Qt::QueuedConnection);
    }
    emit mappingMatrixUpdated(matrix);
    emit mappingValidityChanged(true, QString());
}

void ImagePipelineController::invalidateMapping(QString reason)
{
    m_mappingValid = false;
    m_mappingInvalidReason = reason.isEmpty()
        ? QStringLiteral("Camera mapping is invalid") : reason;
    emit mappingValidityChanged(false, m_mappingInvalidReason);
}

void ImagePipelineController::updateFrameSize(cv::Mat mat)
{
    m_frameSnapshot.width = mat.cols;
    m_frameSnapshot.height = mat.rows;
    emit frameSizeUpdated(m_frameSnapshot.width, m_frameSnapshot.height);
}

void ImagePipelineController::requestFrameSize()
{
    emit frameSizeUpdated(m_frameSnapshot.width, m_frameSnapshot.height);
}

void ImagePipelineController::requestColorFilterInput()
{
    if (!m_colorFilterNode)
        return;
    emit colorFilterInputReady(m_colorFilterNode->GetInputImage());
}

void ImagePipelineController::inputImage(cv::Mat mat)
{
    if (!mat.empty())
        updateFrameSize(mat);

    if (m_getImageNode)
    {
        const cv::Mat owned = mat.clone();
        QMetaObject::invokeMethod(m_getImageNode, [node = m_getImageNode, owned]() {
            node->Input(owned);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::inputFrame(VisionFrame frame)
{
    frame = frame.detached();
    if (!frame.isValid()) {
        emit frameRejected(frame.trackingId, frame.frameId, frame.requestId,
                           QStringLiteral("Invalid or empty camera frame"));
        return;
    }

    if (m_intrinsicCalibration.isValid) {
        cv::Mat corrected;
        QString calibrationError;
        if (!CameraCalibration::undistort(m_intrinsicCalibration, frame.image,
                                          corrected, &calibrationError)) {
            emit frameRejected(frame.trackingId, frame.frameId, frame.requestId,
                               QStringLiteral("Intrinsic correction failed: %1").arg(calibrationError));
            return;
        }
        frame.image = corrected;
    }

    updateFrameSize(frame.image);
    if (m_frameInFlight) {
        if (frame.requestId == 0) {
            emit frameRejected(frame.trackingId, frame.frameId, frame.requestId,
                               QStringLiteral("Preview frame dropped by vision backpressure"));
            return;
        }

        while (m_pendingFrames.size() >= m_maxPendingFrames) {
            int previewIndex = -1;
            for (int i = 0; i < m_pendingFrames.size(); ++i) {
                if (m_pendingFrames.at(i).requestId == 0) {
                    previewIndex = i;
                    break;
                }
            }
            if (previewIndex < 0) {
                emit frameRejected(frame.trackingId, frame.frameId, frame.requestId,
                                   QStringLiteral("Vision request queue is full"));
                return;
            }
            const VisionFrame dropped = m_pendingFrames.takeAt(previewIndex);
            emit frameRejected(dropped.trackingId, dropped.frameId, dropped.requestId,
                               QStringLiteral("Preview frame dropped by vision backpressure"));
        }
        m_pendingFrames.enqueue(frame);
        return;
    }

    m_pendingFrames.enqueue(frame);
    startNextFrame();
}

void ImagePipelineController::setIntrinsicCalibration(CameraCalibration::Profile profile)
{
    if (!profile.isValid)
        return;
    m_intrinsicCalibration = profile;
    invalidateMapping(QStringLiteral("Intrinsic camera calibration changed; recalibrate image-to-world mapping"));
}

void ImagePipelineController::clearIntrinsicCalibration()
{
    if (!m_intrinsicCalibration.isValid)
        return;
    m_intrinsicCalibration = CameraCalibration::Profile();
    invalidateMapping(QStringLiteral("Intrinsic camera calibration disabled; recalibrate image-to-world mapping"));
}

void ImagePipelineController::inputColorFilterValues(QList<int> values)
{
    if (m_colorFilterNode)
    {
        QMetaObject::invokeMethod(m_colorFilterNode, [node = m_colorFilterNode, values]() {
            node->Input(values);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::inputColorFilterBlur(int blur)
{
    if (m_colorFilterNode)
    {
        QMetaObject::invokeMethod(m_colorFilterNode, [node = m_colorFilterNode, blur]() {
            node->Input(blur);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::inputColorFilterInvert(bool inverted)
{
    if (m_colorFilterNode)
    {
        QMetaObject::invokeMethod(m_colorFilterNode, [node = m_colorFilterNode, inverted]() {
            node->Input(inverted);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::connectPipeline()
{
    // Guard against missing nodes
    TaskNode* visibleObjectsNode = node("VisibleObjectsNode");
    if (!m_getImageNode || !m_resizeImageNode || !m_warpImageNode || !m_cropImageNode ||
        !m_colorFilterNode || !m_getObjectsNode || !m_findCirclesNode || !m_displayImageNode ||
        !m_mappingMatrixNode || !visibleObjectsNode)
        return;

    // Clear previous dynamic connections to avoid duplicates
    QObject::disconnect(m_getImageNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_resizeImageNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_warpImageNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_cropImageNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_colorFilterNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_getObjectsNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_findCirclesNode, nullptr, nullptr, nullptr);
    QObject::disconnect(m_displayImageNode, nullptr, nullptr, nullptr);
    QObject::disconnect(visibleObjectsNode, nullptr, nullptr, nullptr);

    // Keep controller subscribed to mapping matrix output (connect once)
    if (!m_mappingConnectionEstablished && m_mappingMatrixNode)
    {
        auto matrixSignal = static_cast<void (TaskNode::*)(QMatrix)>(&TaskNode::HadOutput);
        QObject::connect(m_mappingMatrixNode,
                         matrixSignal,
                         this,
                         [this](QMatrix matrix) {
                             inputMappingMatrix(matrix);
                         });
        m_mappingConnectionEstablished = true;
    }

    // Static pipeline connections
    QObject::connect(m_getImageNode, SIGNAL(HadOutput(cv::Mat)), m_resizeImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
    QObject::connect(m_resizeImageNode, SIGNAL(HadOutput(cv::Mat)), m_warpImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
    QObject::connect(m_warpImageNode, SIGNAL(HadOutput(cv::Mat)), m_cropImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
    QObject::connect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)), m_colorFilterNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);

    // Display node from crop
    QObject::connect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)), m_displayImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);

    // Default algorithm: blobs (color filter -> get objects)
    QObject::connect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_getObjectsNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);

    // Visible objects from getObjects or findCircles
    QObject::connect(m_getObjectsNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)), Qt::UniqueConnection);
    QObject::connect(m_findCirclesNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)), Qt::UniqueConnection);

    // Forward mapped objects back to ImageProcessing so tracking receives them
    QObject::connect(visibleObjectsNode,
                     SIGNAL(HadOutput(QVector<Object>)),
                     m_processing,
                     SLOT(GotVisibleObjects(QVector<Object>)),
                     Qt::UniqueConnection);
}

void ImagePipelineController::inputVisibleObjects(QVector<Object> objects)
{
    TaskNode* visibleObjectsNode = node("VisibleObjectsNode");
    if (visibleObjectsNode)
    {
        QMetaObject::invokeMethod(visibleObjectsNode, [visibleObjectsNode, objects]() {
            visibleObjectsNode->Input(objects);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::inputObjectFilter(Object obj)
{
    if (m_getObjectsNode)
    {
        QMetaObject::invokeMethod(m_getObjectsNode, [node = m_getObjectsNode, obj]() {
            node->Input(obj);
        }, Qt::QueuedConnection);
    }
}

void ImagePipelineController::setPassThrough(TaskNode* taskNode, bool passThrough)
{
    if (!taskNode)
        return;
    QMetaObject::invokeMethod(taskNode, [taskNode, passThrough]() {
        taskNode->SetPassThrough(passThrough);
    }, Qt::QueuedConnection);
}

void ImagePipelineController::startNextFrame()
{
    if (m_frameInFlight || m_pendingFrames.isEmpty() || !m_getImageNode)
        return;
    m_activeFrame = m_pendingFrames.dequeue();
    m_frameInFlight = true;
    m_frameTimeout.start();
    const cv::Mat owned = m_activeFrame.image.clone();
    QMetaObject::invokeMethod(m_getImageNode, [node = m_getImageNode, owned]() {
        node->Input(owned);
    }, Qt::QueuedConnection);
}

void ImagePipelineController::finishActiveFrame()
{
    m_frameTimeout.stop();
    m_activeFrame = VisionFrame();
    m_frameInFlight = false;
    QTimer::singleShot(0, this, &ImagePipelineController::startNextFrame);
}

void ImagePipelineController::handleMappedDetections(QVector<ObjectInfo> objects,
                                                     QString legacyListName)
{
    Q_UNUSED(legacyListName)
    if (!m_frameInFlight)
        return;
    if (m_algorithmName == QStringLiteral("External Script") &&
        m_activeFrame.requestId != 0) {
        emit frameRejected(m_activeFrame.trackingId, m_activeFrame.frameId,
                           m_activeFrame.requestId,
                           QStringLiteral("External detector response is missing DXV1 frame metadata"));
        finishActiveFrame();
        return;
    }
    if (m_algorithmName == QStringLiteral("External Script") && !m_mappingValid) {
        emit frameRejected(m_activeFrame.trackingId, m_activeFrame.frameId,
                           m_activeFrame.requestId, m_mappingInvalidReason);
        finishActiveFrame();
        return;
    }
    if (!m_mappingValid) {
        emit frameRejected(m_activeFrame.trackingId, m_activeFrame.frameId,
                           m_activeFrame.requestId, m_mappingInvalidReason);
        finishActiveFrame();
        return;
    }

    VisionDetections result;
    result.frameId = m_activeFrame.frameId;
    result.requestId = m_activeFrame.requestId;
    result.trackingId = m_activeFrame.trackingId;
    result.coordinateSpace = QStringLiteral("conveyor");
    result.objects = objects;
    emit detectionsReady(result);
    finishActiveFrame();
}

void ImagePipelineController::forwardExternalImage(cv::Mat image)
{
    if (!m_frameInFlight || image.empty())
        return;
    VisionFrame frame = m_activeFrame;
    frame.image = image.clone();
    emit externalFrameReady(frame);
}

void ImagePipelineController::inputExternalDetections(VisionDetections detections)
{
    if (!m_frameInFlight)
        return;
    if (detections.frameId != m_activeFrame.frameId ||
        detections.requestId != m_activeFrame.requestId ||
        detections.trackingId != m_activeFrame.trackingId) {
        emit externalResponseIgnored(
            detections.frameId, detections.requestId, detections.trackingId,
            QStringLiteral("External detector response does not match the active frame"));
        return;
    }

    const QString space = detections.coordinateSpace.trimmed().toLower();
    if (space == QStringLiteral("image")) {
        if (!m_mappingValid) {
            emit frameRejected(m_activeFrame.trackingId, m_activeFrame.frameId,
                               m_activeFrame.requestId, m_mappingInvalidReason);
            finishActiveFrame();
            return;
        }
        detections.objects = mapExternalImageObjects(detections.objects);
        detections.coordinateSpace = QStringLiteral("conveyor");
    } else if (space != QStringLiteral("conveyor") && space != QStringLiteral("world")) {
        emit frameRejected(m_activeFrame.trackingId, m_activeFrame.frameId,
                           m_activeFrame.requestId,
                           QStringLiteral("Unsupported detector coordinate space"));
        finishActiveFrame();
        return;
    }

    emit detectionsReady(detections);
    finishActiveFrame();
}

void ImagePipelineController::inputExternalFailure(int trackingId, quint64 frameId,
                                                   quint64 requestId, QString reason)
{
    if (!m_frameInFlight || trackingId != m_activeFrame.trackingId ||
        frameId != m_activeFrame.frameId || requestId != m_activeFrame.requestId)
        return;
    emit frameRejected(trackingId, frameId, requestId, reason);
    finishActiveFrame();
}

void ImagePipelineController::inputExternalStatus(bool connected, QString peer)
{
    if (connected || !m_frameInFlight ||
        m_algorithmName != QStringLiteral("External Script"))
        return;
    emit frameRejected(
        m_activeFrame.trackingId, m_activeFrame.frameId, m_activeFrame.requestId,
        QStringLiteral("External Vision detector disconnected: %1").arg(peer));
    finishActiveFrame();
}

QVector<ObjectInfo> ImagePipelineController::mapExternalImageObjects(
    const QVector<ObjectInfo>& objects) const
{
    QVector<ObjectInfo> mapped;
    mapped.reserve(objects.size());
    for (const ObjectInfo& info : objects) {
        Object object;
        object.Type = QString::number(info.type);
        object.X.Image = info.center.x();
        object.Y.Image = info.center.y();
        object.Width.Image = info.width;
        object.Length.Image = info.height;
        object.Height.Image = info.center.z();
        object.Angle.Image = info.angle;
        object.Map(m_latestMappingMatrix);
        mapped.append(ObjectInfo(-1, info.type,
                                 QVector3D(object.X.Real, object.Y.Real, info.center.z()),
                                 object.Width.Real, object.Length.Real,
                                 object.Angle.Real, info.isPicked, QVector3D(),
                                 QString(), 0, info.confidence, info.label,
                                 info.externalId));
    }
    return mapped;
}

bool ImagePipelineController::isFiniteInvertibleMatrix(const QMatrix& matrix)
{
    const double values[] = { matrix.m11(), matrix.m12(), matrix.m21(),
                              matrix.m22(), matrix.dx(), matrix.dy() };
    for (double value : values) {
        if (!qIsFinite(value))
            return false;
    }
    return !qFuzzyIsNull(matrix.determinant());
}
