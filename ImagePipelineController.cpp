#include "ImagePipelineController.h"

#include "ImageProcessing.h"
#include "SocketConnectionManager.h"
#include "TaskNode.h"

#include <QObject>
#include "QtMatrixCompat.h"

ImagePipelineController::ImagePipelineController(ImageProcessing* processing, QObject* parent)
    : QObject(parent),
      m_processing(processing)
{
    if (!m_processing)
        return;

    qRegisterMetaType<QMatrix>("QMatrix");

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

    if (m_mappingMatrixNode)
    {
        // Keep a single connection; UniqueConnection with functor triggers assert in Qt6
        auto matrixSignal = static_cast<void (TaskNode::*)(QMatrix)>(&TaskNode::HadOutput);
        QObject::disconnect(m_mappingMatrixNode, matrixSignal, this, nullptr);
        connect(m_mappingMatrixNode,
                matrixSignal,
                this,
                [this](QMatrix matrix) {
                    m_latestMappingMatrix = matrix;
                    emit mappingMatrixUpdated(matrix);
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
        m_warpImageNode->IsPass = true;
        m_cropImageNode->IsPass = false;
    }
    else if (warpEnabled && cropEnabled)
    {
        m_warpImageNode->IsPass = false;
        m_cropImageNode->IsPass = false;
    }
    else if (!warpEnabled && !cropEnabled)
    {
        m_warpImageNode->IsPass = true;
        m_cropImageNode->IsPass = true;
    }
    else if (warpEnabled && !cropEnabled)
    {
        m_warpImageNode->IsPass = false;
        m_cropImageNode->IsPass = true;
    }
}

void ImagePipelineController::configureAutoResize(bool autoResizeEnabled)
{
    if (!m_resizeImageNode)
        return;

    // Auto resize checked => Resize node runs (IsPass = false)
    m_resizeImageNode->IsPass = !autoResizeEnabled;
}

void ImagePipelineController::configureAlgorithm(const QString& algorithmName, SocketConnectionManager* connectionManager)
{
    TaskNode* visibleObjectsNode = node("VisibleObjectsNode");
    if (!m_colorFilterNode || !m_getObjectsNode || !m_findCirclesNode || !m_cropImageNode || !visibleObjectsNode)
        return;

    // Clear previous dynamic connections
    QObject::disconnect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_getObjectsNode, SLOT(Input(cv::Mat)));
    QObject::disconnect(m_colorFilterNode, SIGNAL(HadOutput(cv::Mat)), m_findCirclesNode, SLOT(Input(cv::Mat)));
    QObject::disconnect(m_getObjectsNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)));
    QObject::disconnect(m_findCirclesNode, SIGNAL(HadOutput(QVector<Object>)), visibleObjectsNode, SLOT(Input(QVector<Object>)));
    if (connectionManager)
    {
        QObject::disconnect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)), connectionManager, SLOT(sendImageToImageClients(cv::Mat)));
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
        QObject::connect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)), connectionManager, SLOT(sendImageToImageClients(cv::Mat)), Qt::UniqueConnection);
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
        m_resizeImageNode->Input(size);
    }
}

void ImagePipelineController::inputCropArea(QRectF rect)
{
    if (m_cropImageNode)
    {
        m_cropImageNode->Input(rect);
    }
}

void ImagePipelineController::inputPerspectiveQuadrangle(QPolygonF quad)
{
    TaskNode* perspective = node("GetPerspectiveNode");
    if (perspective)
    {
        perspective->Input(quad);
    }
}

void ImagePipelineController::inputMappingPolygon(QPolygonF poly)
{
    if (m_mappingMatrixNode)
    {
        m_mappingMatrixNode->Input(poly);
    }
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
        m_getImageNode->Input(mat);
    }
}

void ImagePipelineController::inputColorFilterValues(QList<int> values)
{
    if (m_colorFilterNode)
    {
        m_colorFilterNode->Input(values);
    }
}

void ImagePipelineController::inputColorFilterBlur(int blur)
{
    if (m_colorFilterNode)
    {
        m_colorFilterNode->Input(blur);
    }
}

void ImagePipelineController::inputColorFilterInvert(bool inverted)
{
    if (m_colorFilterNode)
    {
        m_colorFilterNode->Input(inverted);
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
                             m_latestMappingMatrix = matrix;
                             emit mappingMatrixUpdated(matrix);
                         });
        m_mappingConnectionEstablished = true;
    }

    // Static pipeline connections
    QObject::connect(m_getImageNode, SIGNAL(HadOutput(cv::Mat)), m_resizeImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
    QObject::connect(m_resizeImageNode, SIGNAL(HadOutput(cv::Mat)), m_warpImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
    QObject::connect(m_warpImageNode, SIGNAL(HadOutput(cv::Mat)), m_cropImageNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);
    QObject::connect(m_cropImageNode, SIGNAL(HadOutput(cv::Mat)), m_colorFilterNode, SLOT(Input(cv::Mat)), Qt::UniqueConnection);

    // Mapping matrix to visible objects
    QObject::connect(m_mappingMatrixNode, SIGNAL(HadOutput(QMatrix)), visibleObjectsNode, SLOT(Input(QMatrix)), Qt::UniqueConnection);

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

void ImagePipelineController::inputChessboardSize(cv::Size size)
{
    TaskNode* chessboardNode = node("FindChessboardNode");
    if (chessboardNode)
    {
        chessboardNode->Input(size);
    }
}

void ImagePipelineController::inputChessboardQuadrangle(cv::Mat mat)
{
    TaskNode* chessboardNode = node("FindChessboardNode");
    if (chessboardNode)
    {
        chessboardNode->Input(mat);
    }
}

void ImagePipelineController::inputCalibPoints(QPolygonF poly)
{
    if (m_mappingMatrixNode)
    {
        m_mappingMatrixNode->Input(poly);
    }
}

void ImagePipelineController::inputVisibleObjects(QVector<Object> objects)
{
    TaskNode* visibleObjectsNode = node("VisibleObjectsNode");
    if (visibleObjectsNode)
    {
        visibleObjectsNode->Input(objects);
    }
}

void ImagePipelineController::inputObjectFilter(Object obj)
{
    if (m_getObjectsNode)
    {
        m_getObjectsNode->Input(obj);
    }
}
