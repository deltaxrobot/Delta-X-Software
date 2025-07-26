#include "TaskNode.h"
#include <vector>

QElapsedTimer TaskNode::DebugTimer;

TaskNode::TaskNode(QString name, int type)
{
    this->type = type;
    this->name = name;

    qRegisterMetaType< QVector<Object>* >("QVector<Object>*");
    qRegisterMetaType< QVector<Object>>("QVector<Object>");
    qRegisterMetaType< QVector<Object>>("QVector<QSharedPointer<Object>>");


    if (type == RESIZE_IMAGE_NODE)
    {
        size = cv::Size(0, 0);
    }

    if (type == WARP_IMAGE_NODE)
    {
        inputPoints[0] = cv::Point2f(0.2f, 0.8f);
        inputPoints[1] = cv::Point2f(0.2f, 0.2f);
        inputPoints[2] = cv::Point2f(0.8f, 0.2f);
        inputPoints[3] = cv::Point2f(0.8f, 0.8f);
    }

    if (type == COLOR_FILTER_NODE)
    {
        intPara = 1;
        intParas.append(150);
    }

    if (type == GET_OBJECTS_NODE)
    {
        inputObject.Width.Image = 100;
        inputObject.Length.Image = 150;
    }

    if (type == VISIBLE_OBJECTS_NODE)
    {
        inputMatrix.reset();

    }
}

TaskNode::~TaskNode()
{
    // Clean up connections
    ClearInputConnections();
    ClearOutputConnections();
    
    // Release OpenCV mats
    inputMat.release();
    inputMat2.release();
    outputMat.release();
}

void TaskNode::SetNextNode(TaskNode *next)
{
    nextTaskNodes.append(next);
    connectInOutNode(this, next);
}

void TaskNode::SetPreviousNode(TaskNode *previous)
{
    previousTaskNodes.append(previous);
    connectInOutNode(previous, this);
}

void TaskNode::ClearInputConnections()
{
    foreach(QMetaObject::Connection con, InputConnections)
    {
        QObject::disconnect(con);
    }

    InputConnections.clear();

    previousTaskNodes.clear();
}

void TaskNode::RemoveInputConnection(TaskNode* previous)
{
    int index = previousTaskNodes.indexOf(previous);
    QObject::disconnect(InputConnections.at(index));

    previousTaskNodes.removeOne(previous);
}

void TaskNode::ClearOutputConnections()
{
    nextTaskNodes.clear();
}

QSize TaskNode::GetImageSize()
{
    QMutexLocker locker(&dataMutex);
    return QSize(inputMat.cols, inputMat.rows);
}

QMatrix TaskNode::GetMatrix()
{
    QMutexLocker locker(&dataMutex);
    return inputMatrix;
}

cv::Mat TaskNode::GetOutputImage()
{
    QMutexLocker locker(&dataMutex);
    return outputMat.clone();
}

cv::Mat TaskNode::GetInputImage()
{
    QMutexLocker locker(&dataMutex);
    return inputMat.clone();
}

Object& TaskNode::GetInputObject()
{
    // Note: Returning reference to member variable is inherently unsafe in multithreaded context
    // Consider returning a copy instead if thread safety is critical for this method
    QMutexLocker locker(&dataMutex);
    return inputObject;
}

QPointF *TaskNode::GetInputPointPointer()
{
    return &inputPoint;
}

bool TaskNode::ClearVariable(QString name)
{
    QMutexLocker locker(&dataMutex);
    
    if (name.toLower() == QString("outputObjects").toLower())
    {
        clear(outputObjects);
        
        // Create safe copy for signal emission
        QVector<Object> safeCopy = outputObjects;
        locker.unlock(); // Unlock before signal emission
        
        HadOutput(safeCopy);

        return true;
    }

    if (name.toLower() == QString("inputObjects").toLower())
    {
        clear(inputObjects);

        return true;
    }

    return false;
}

void TaskNode::Input(cv::Size size)
{
    {
        QMutexLocker locker(&dataMutex);
        this->size = size;
    }

    DoWork();
}

void TaskNode::Input(cv::Mat mat)
{
    {
        QMutexLocker locker(&dataMutex);
        inputMat = mat;
    }

    DoWork();
}

void TaskNode::Input2(cv::Mat mat)
{
    QMutexLocker locker(&dataMutex);
    inputMat2 = mat;
}

void TaskNode::Input(QVector<Object> objects)
{
    {
        QMutexLocker locker(&dataMutex);
        this->inputObjects = objects;
        inputType = "objects";
    }

    DoWork();
}

void TaskNode::Input(QList<int> paras)
{
    {
        QMutexLocker locker(&dataMutex);
        intParas = paras;
    }

    DoWork();
}

void TaskNode::Input(int para)
{
    {
        QMutexLocker locker(&dataMutex);
        intPara = para;
    }

    DoWork();
}

void TaskNode::Input(bool value)
{
    {
        QMutexLocker locker(&dataMutex);
        boolPara = value;
    }

    DoWork();
}

void TaskNode::Input(float para)
{
    QMutexLocker locker(&dataMutex);
    this->floatPara = para;
}

void TaskNode::Input(QString name, Range range)
{
    QMutexLocker locker(&dataMutex);
    ranges.insert(name, range);
}

void TaskNode::Input(QMatrix matrix)
{
    {
        QMutexLocker locker(&dataMutex);
        this->inputMatrix = matrix;
    }

    DoWork();
}

void TaskNode::Input(QPointF point)
{
    {
        QMutexLocker locker(&dataMutex);
        this->inputPoint = point;
        this->inputType = "point";
    }

    DoWork();
}

void TaskNode::Input(cv::Point2f points[])
{
    {
        QMutexLocker locker(&dataMutex);
        this->inputPoints[0] = points[0];
        this->inputPoints[1] = points[1];
        this->inputPoints[2] = points[2];
        this->inputPoints[3] = points[3];
    }

    DoWork();
}

void TaskNode::Input(QPolygonF poly)
{
    bool shouldDoWork = false;
    
    {
        QMutexLocker locker(&dataMutex);
        inputPoly = poly;

        if (poly.count() >= 4)
        {
            this->inputPoints[0] = cv::Point2f(poly.at(0).x(), poly.at(0).y());
            this->inputPoints[1] = cv::Point2f(poly.at(1).x(), poly.at(1).y());
            this->inputPoints[2] = cv::Point2f(poly.at(2).x(), poly.at(2).y());
            this->inputPoints[3] = cv::Point2f(poly.at(3).x(), poly.at(3).y());
            shouldDoWork = true;
        }
    }
    
    if (shouldDoWork)
    {
        DoWork();
    }
}

void TaskNode::Input(QRectF rect)
{
    QMutexLocker locker(&dataMutex);
    inputRect = rect;
}

void TaskNode::Input(Object obj)
{
    QMutexLocker locker(&dataMutex);
    inputObject.CopyFrom(obj);
}

void TaskNode::Input(int edgeThresh, int centerThresh, int minRad, int maxRad)
{
    QMutexLocker locker(&dataMutex);
    edgeThreshold = edgeThresh;
    centerThreshold = centerThresh;
    minRadius = minRad;
    maxRadius = maxRad;
}

void TaskNode::Input(QStringList objects)
{
    QVector<Object> tempObjects;
    QList<QPolygonF> tempPolys;
    
    // Process data without holding mutex for long time
    foreach(QString obj, objects)
    {
        if (obj.trimmed().isEmpty())
            continue;

        QStringList objInfo = obj.split(",");
        
        // Validate minimum required fields (at least Type, X, Y)
        if (objInfo.count() < 3)
        {
            qDebug() << "Warning: Object data has insufficient fields:" << obj;
            continue;
        }

        Object object;

        // Safe parsing with bounds checking
        if (objInfo.count() > 0)
            object.Type = objInfo[0];
        if (objInfo.count() > 1)
            object.X.Image = objInfo[1].toFloat();
        if (objInfo.count() > 2)
            object.Y.Image = objInfo[2].toFloat();
        if (objInfo.count() > 3)
            object.Length.Image = objInfo[3].toFloat();
        if (objInfo.count() > 4)
            object.Width.Image = objInfo[4].toFloat();
        if (objInfo.count() > 5)
            object.Angle.Image = objInfo[5].toFloat();

        tempObjects.append(object);
        tempPolys.append(object.ToPolygon());
    }
    
    // Update output containers with mutex protection
    {
        QMutexLocker locker(&dataMutex);
        outputObjects.clear();
        outputPolys.clear();
        outputObjects = tempObjects;
        outputPolys = tempPolys;
    }

    emit HadOutput(tempObjects);
    emit HadOutput(tempPolys);
    emit Done(defaultThreadId);
}

void TaskNode::DoWork()
{
    if (type == GET_IMAGE_NODE)
    {
        doGetImageWork();
    }

    if (type == RESIZE_IMAGE_NODE)
    {
        doResizeWork();
    }

    if (type == FIND_CHESSBOARD_NODE)
    {
        doFindChessboardWork();
    }

    if (type == GET_PERSPECTIVE_NODE)
    {
        doGetPerspectiveWork();
    }

    if (type == WARP_IMAGE_NODE)
    {
        doWarpWork();
    }

    if (type == CROP_IMAGE_NODE)
    {
        doCropWork();
    }

    if (type == DISPLAY_IMAGE_NODE)
    {
        doDisplayImageWork();
    }

    if (type == COLOR_FILTER_NODE)
    {
        doColorFilterWork();
    }

    if (type == MAPPING_MATRIX_NODE)
    {
        doMappingMatrixWork();
    }

    if (type == GET_OBJECTS_NODE)
    {
        doGetObjectsWork();
    }

    if (type == FIND_CIRCLES_NODE)
    {
        doFindCirclesWork();
    }

    if (type == VISIBLE_OBJECTS_NODE)
    {
        doVisibleObjectsWork();
    }
}

void TaskNode::ClearOutput()
{

}

void TaskNode::DeleteOutput(int id)
{
    QVector<Object> safeCopy;
    
    {
        QMutexLocker locker(&dataMutex);
        if (id >= 0 && id < outputObjects.size())
        {
            outputObjects.removeAt(id);
            safeCopy = outputObjects;
        }
        else
        {
            return; // Invalid index
        }
    }
    
    HadOutput(safeCopy);
}

void TaskNode::connectInOutNode(TaskNode* previous, TaskNode *next)
{
    // ------ Next ------
    if (next->type == RESIZE_IMAGE_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));
    }

    if (next->type == FIND_CHESSBOARD_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));
    }

    if (next->type == GET_PERSPECTIVE_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(QPolygonF)), next, SLOT(Input(QPolygonF)));
    }

    if (next->type == WARP_IMAGE_NODE)
    {
        if (previous->type == RESIZE_IMAGE_NODE)
            next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));

        if (previous->type == GET_PERSPECTIVE_NODE)
            next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input2(cv::Mat)));
    }

    if (next->type == CROP_IMAGE_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));
    }

    if (next->type == DISPLAY_IMAGE_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));
    }

    if (next->type == TaskNode::COLOR_FILTER_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));
    }

    if (next->type == TaskNode::MAPPING_MATRIX_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(QMatrix)), next, SLOT(Input(QMatrix)));
    }

    if (next->type == TaskNode::GET_OBJECTS_NODE)
    {
        next->InputConnections << connect(previous, SIGNAL(HadOutput(cv::Mat)), next, SLOT(Input(cv::Mat)));
    }

    if (next->type == TaskNode::VISIBLE_OBJECTS_NODE)
    {
        if (previous->type == GET_OBJECTS_NODE)
            next->InputConnections << connect(previous, SIGNAL(HadOutput(QVector<Object>)), next, SLOT(Input(QVector<Object>)));

        if (previous->type == MAPPING_MATRIX_NODE)
            next->InputConnections << connect(previous, SIGNAL(HadOutput(QMatrix)), next, SLOT(Input(QMatrix)));

    }

//    // ------ Previous -----
//    if (previous->type == TaskNode::GET_OBJECTS_NODE)
//    {
//        next->InputConnections << connect(previous, SIGNAL(HadOutput(QList<Object>)), next, SLOT(Input(QList<Object>)));
//    }
}

void TaskNode::doGetImageWork()
{
//    qDebug() << "capture: " << DebugTimer.restart();
    cv::Mat safeMat;
    
    {
        QMutexLocker locker(&dataMutex);
        outputMat.release();
        outputMat = inputMat;
        safeMat = outputMat.clone();
    }

    emit HadOutput(safeMat);
}

void TaskNode::doResizeWork()
{
    if (inputMat.empty())
        return;

    if (IsPass == true)
    {
        emit HadOutput(inputMat);
        return;
    }

    if (size != cv::Size(0, 0))
    {
        size.height = size.width * ((float)inputMat.rows / inputMat.cols);

        cv::resize(inputMat, outputMat, size, cv::INTER_NEAREST);
    }
    else
    {
        outputMat = inputMat.clone();
    }

    emit HadOutput(outputMat);
}

void TaskNode::doFindChessboardWork()
{    
    int width = size.width;
    int height = size.height;

    if (inputMat.empty() || width == 0 || height == 0)
        return;

    cvtColor(inputMat, outputMat, cv::COLOR_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool patternfound = findChessboardCorners(outputMat, size, corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

    if(patternfound)
    {
        cornerSubPix(outputMat, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

        std::vector<cv::Point> points;

        points.push_back(cv::Point(corners[0].x, corners[0].y));
        points.push_back(cv::Point(corners[width - 1].x, corners[width - 1].y));
        if (size.height % 2 == 1)
        {
          points.push_back(cv::Point(corners[width * height - 1].x, corners[width * height - 1].y));
          points.push_back(cv::Point(corners[width * (height - 1)].x, corners[width * (height - 1)].y));
        }
        else
        {
        points.push_back(cv::Point(corners[width * (height - 1)].x, corners[width * (height - 1)].y));
        points.push_back(cv::Point(corners[width * height - 1].x, corners[width * height - 1].y));
        }

        // Sắp xếp 4 điểm theo thứ tự: top-left, top-right, bottom-right, bottom-left
        // Để đảm bảo điểm số 1 luôn là góc trên-trái
        
        // Tìm điểm top-left (x + y nhỏ nhất)
        int topLeftIndex = 0;
        float minSum = points[0].x + points[0].y;
        for (int i = 1; i < 4; i++) {
            float sum = points[i].x + points[i].y;
            if (sum < minSum) {
                minSum = sum;
                topLeftIndex = i;
            }
        }
        
        // Tìm điểm bottom-right (x + y lớn nhất)
        int bottomRightIndex = 0;
        float maxSum = points[0].x + points[0].y;
        for (int i = 1; i < 4; i++) {
            float sum = points[i].x + points[i].y;
            if (sum > maxSum) {
                maxSum = sum;
                bottomRightIndex = i;
            }
        }
        
        // Tìm top-right và bottom-left từ 2 điểm còn lại
        std::vector<int> remainingIndices;
        for (int i = 0; i < 4; i++) {
            if (i != topLeftIndex && i != bottomRightIndex) {
                remainingIndices.push_back(i);
            }
        }
        
        int topRightIndex, bottomLeftIndex;
        // Top-right có x lớn hơn, y nhỏ hơn so với bottom-left
        if (points[remainingIndices[0]].x > points[remainingIndices[1]].x) {
            topRightIndex = remainingIndices[0];
            bottomLeftIndex = remainingIndices[1];
        } else {
            topRightIndex = remainingIndices[1];
            bottomLeftIndex = remainingIndices[0];
        }
        
                 // Gán theo thứ tự chiều kim đồng hồ: top-left, bottom-left, bottom-right, top-right
         outputPoints[0] = points[topLeftIndex];      // Điểm số 1: top-left
         outputPoints[1] = points[bottomLeftIndex];   // Điểm số 2: bottom-left  
         outputPoints[2] = points[bottomRightIndex];  // Điểm số 3: bottom-right
         outputPoints[3] = points[topRightIndex];     // Điểm số 4: top-right

        outputPoly.clear();

        for (int i = 0; i < 4; i++)
        {
//          outputPoints[i].x = outputPoints[i].x / inputMat.cols;
//          outputPoints[i].y = outputPoints[i].y / inputMat.rows;

          outputPoly.append(QPointF(outputPoints[i].x, outputPoints[i].y));
        }

        emit HadOutput(outputPoly);
        emit HadOutput(outputPoints);
    }
}

void TaskNode::doGetPerspectiveWork()
{
    cv::Point2f outputQuad[4];

    for (int i = 0; i < 4; i++)
    {
        inputPoints[i].x = inputPoly.at(i).x();
        inputPoints[i].y = inputPoly.at(i).y();
    }

    // ---------Find new position-------------------
    cv::Point2f center;
    center.x = (inputPoints[0].x + inputPoints[1].x + inputPoints[2].x + inputPoints[3].x)/4;
    center.y = (inputPoints[0].y + inputPoints[1].y + inputPoints[2].y + inputPoints[3].y) / 4;

    int maxLength = 0;

    for (int i = 0; i < 4; i++)
    {
        QLineF line;
        line.setP1(QPoint(inputPoints[i].x, inputPoints[i].y));
        if (i == 3)
        {
            line.setP2(QPoint(inputPoints[0].x, inputPoints[0].y));
        }
        else
        {
            line.setP2(QPoint(inputPoints[i + 1].x, inputPoints[i + 1].y));
        }

        float len = line.length();

        if (len > maxLength)
        {
            maxLength = len;
        }
    }

    float halfLen = maxLength / 2;

    outputQuad[0] = center + cv::Point2f(-halfLen, -halfLen);
    outputQuad[1] = center + cv::Point2f(-halfLen, halfLen);
    outputQuad[2] = center + cv::Point2f(halfLen, halfLen);
    outputQuad[3] = center + cv::Point2f(halfLen, -halfLen);

    outputMat = cv::getPerspectiveTransform(inputPoints, outputQuad);

    emit HadOutput(outputMat);
}

void TaskNode::doWarpWork()
{
    if (IsPass == true)
    {
        emit HadOutput(inputMat);
        return;
    }

    if (inputMat.empty() || inputMat2.empty())
    {
        outputMat.release();
        outputMat = inputMat.clone();
        emit HadOutput(outputMat);
        return;
    }
    else
    {
//        qDebug() << "Warp start: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
        cv::warpPerspective(inputMat, outputMat, inputMat2, inputMat.size(), cv::INTER_NEAREST);
//        qDebug() << "Warp end: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

        emit HadOutput(outputMat);
    }
}

void TaskNode::doCropWork()
{
    if (IsPass == true)
    {
        emit HadOutput(inputMat);
        return;
    }

    outputMat.release();
    outputMat = inputMat.clone();

    if (!(inputRect.topLeft() == QPointF(0, 0) && inputRect.bottomRight() == QPointF(0, 0)))
    {
        cv::Rect cropRegion(inputRect.topLeft().x(), inputRect.topLeft().y(), inputRect.width(), inputRect.height());
        if (cropRegion.x + cropRegion.width < inputMat.cols && cropRegion.y + cropRegion.height < inputMat.rows)
        {
            outputMat = outputMat(cropRegion);
            emit HadOutput(outputMat);
            return;
        }
    }

    emit HadOutput(outputMat);
}

void TaskNode::doDisplayImageWork()
{
    QPixmap pixmap = ImageTool::cvMatToQPixmap(inputMat);

    emit HadOutput(pixmap);
//    emit HadOutput(pixmap, inputObjects);
}

void TaskNode::doColorFilterWork()
{
    if (inputMat.empty())
        return;

    if (intParas.count() == 1)
    {
        cvtColor(inputMat, outputMat, CV_BGR2GRAY);

        cv::threshold(outputMat, outputMat, intParas[0], 255, CV_THRESH_BINARY);
    }

    if (intParas.count() == 6)
    {
        cv::cvtColor(inputMat, outputMat, CV_BGR2HSV);

        cv::Scalar minScalar(intParas[0], intParas[2], intParas[4]);
        cv::Scalar maxScalar(intParas[1], intParas[3], intParas[5]);

        cv::inRange(outputMat, minScalar, maxScalar, outputMat);
    }

    if (boolPara == true)
    {
        cv::bitwise_not(outputMat, outputMat);
    }

    cv::medianBlur(outputMat, outputMat, intPara);

    emit HadOutput(outputMat);
}

void TaskNode::doMappingMatrixWork()
{
    float x1 = inputPoly[0].x();
    float y1 = 0 - inputPoly[0].y();
    float x2 = inputPoly[1].x();
    float y2 = 0 - inputPoly[1].y();

    if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
        return;

    float xx1 = inputPoly[2].x();
    float yy1 = inputPoly[2].y();
    float xx2 = inputPoly[3].x();
    float yy2 = inputPoly[3].y();

    if (xx1 == 0 && yy1 == 0 && xx2 == 0 && yy2 == 0)
        return;

    float a1 = x2 - x1;
    float b1 = y2 - y1;
    float a2 = xx2 -xx1;
    float b2 = yy2 - yy1;

    float n1n2 = a1 * a2 + b1 * b2;
    float _n1 = qSqrt(qPow(a1, 2) + qPow(b1, 2));
    float _n2 = qSqrt(qPow(a2, 2) + qPow(b2, 2));
    float ratio = _n2/_n1;

    float _n1_n2_ = _n1 * _n2;

    float cosTheta = n1n2 / _n1_n2_;
    //float cosTheta = a2 / _n2;
    float tanTheta = (a1 * b2 - b1 * a2) / (a1 * a2 + b1 * b2);
    float theta = qAcos(cosTheta);

    if (cosTheta < 0)
    {
        if (tanTheta > 0)
        {
            theta = 0 - theta;
        }
    }
    else
    {
        if (tanTheta < 0)
        {
            theta = 0 - theta;
        }
    }

    float angle = 0 - theta * (180 / M_PI);

    QMatrix RotateMatrix(qCos(theta), qSin(theta), -qSin(theta), qCos(theta), 0, 0);

    QMatrix ScaleMatrix(ratio, 0, 0, ratio, 0, 0);

    QMatrix ScaleRotateMatrix = ScaleMatrix * RotateMatrix;

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float dx = xx1 - (ScaleRotateMatrix.m11() * x1 + ScaleRotateMatrix.m21() * y1);
    float dy = yy1 - (ScaleRotateMatrix.m12() * x1 + ScaleRotateMatrix.m22() * y1);

    outputMatrix.setMatrix(ScaleRotateMatrix.m11(), ScaleRotateMatrix.m12(), ScaleRotateMatrix.m21(), ScaleRotateMatrix.m22(), dx, dy);
    QString prefix = ProjectName + "." + "tracking0" + ".";
    QString matrixString = QString("%1,%2,%3,%4,%5,%6")
                                   .arg(outputMatrix.m11())
                                   .arg(outputMatrix.m12())
                                   .arg(outputMatrix.m21())
                                   .arg(outputMatrix.m22())
                                   .arg(outputMatrix.dx())
                                   .arg(outputMatrix.dy());
    VariableManager::instance().updateVar(prefix + "ImageToRealWorldMatrixString", matrixString);
    VariableManager::instance().updateVar(prefix + "ImageToRealWorldMatrix", outputMatrix);

    emit HadOutput(outputMatrix);
}

void TaskNode::doGetObjectsWork()
{
    // Create working copies to avoid race conditions
    cv::Mat workingMat;
    Object workingInputObject;
    
    {
        QMutexLocker locker(&dataMutex);
        if (inputMat.empty())
            return;
        
        // Make safe copies of data
        workingMat = inputMat.clone();
        
        // Validate clone was successful
        if (workingMat.empty()) {
            qDebug() << "Warning: workingMat is empty after clone in doGetObjectsWork";
            return;
        }
        
        workingInputObject.CopyFrom(inputObject);  // Use CopyFrom instead of assignment
        
        // Clear output containers under mutex protection
        outputObjects.clear();
        outputPolys.clear();
    }

    try {
        std::vector<std::vector<cv::Point> > contoursContainer;
        findContours(workingMat, contoursContainer, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        const int borderMargin = 5; // Make magic number a named constant

        for (size_t i = 0; i < contoursContainer.size(); i++)
        {
            // Validate contour has enough points
            if (contoursContainer[i].size() < 3)
                continue;

            cv::RotatedRect rectObject = cv::minAreaRect(cv::Mat(contoursContainer[i]));
            cv::Rect box = cv::boundingRect(contoursContainer[i]);
            
            // Check bounds with safer validation
            if (box.x <= borderMargin || box.y <= borderMargin || 
                (box.x + box.width) >= (workingMat.cols - borderMargin) || 
                (box.y + box.height) >= (workingMat.rows - borderMargin))
                continue;

            // Validate rect dimensions
            if (rectObject.size.width <= 0 || rectObject.size.height <= 0)
                continue;

            Object obj(rectObject);
            if (workingInputObject.IsSameType(obj))
            {
                Object obPointer(rectObject);
                
                // Thread-safe append
                {
                    QMutexLocker locker(&dataMutex);
                    outputObjects.append(obPointer);
                    outputPolys.append(obPointer.ToPolygon());
                }
            }
        }
    }
    catch (const cv::Exception& e)
    {
        qDebug() << "OpenCV error in doGetObjectsWork:" << e.what();
        return;
    }

    // Emit signals with thread-safe copies
    QVector<Object> safeOutputObjects;
    QList<QPolygonF> safeOutputPolys;
    
    {
        QMutexLocker locker(&dataMutex);
        safeOutputObjects = outputObjects;
        safeOutputPolys = outputPolys;
    }
    
    emit HadOutput(safeOutputObjects);
    emit HadOutput(safeOutputPolys);
}

void TaskNode::doFindCirclesWork()
{
    // Create working copies to avoid race conditions
    cv::Mat workingMat;
    Object workingInputObject;
    int workingMinRadius, workingMaxRadius;
    int workingEdgeThreshold, workingCenterThreshold;
    
    {
        QMutexLocker locker(&dataMutex);
        if (inputMat.empty())
            return;
        
        // Make safe copies of data
        workingMat = inputMat.clone();
        
        // Validate clone was successful
        if (workingMat.empty()) {
            qDebug() << "Warning: workingMat is empty after clone in doFindCirclesWork";
            return;
        }
        
        workingInputObject.CopyFrom(inputObject);  // Use CopyFrom instead of assignment
        workingMinRadius = minRadius;
        workingMaxRadius = maxRadius;
        workingEdgeThreshold = edgeThreshold;
        workingCenterThreshold = centerThreshold;
        
        // Clear output containers under mutex protection
        outputObjects.clear();
        outputPolys.clear();
    }

    try {
        cv::Mat grayMat;
        
        // Convert to grayscale if needed
        if (workingMat.channels() == 3)
            cv::cvtColor(workingMat, grayMat, cv::COLOR_BGR2GRAY);
        else
            grayMat = workingMat.clone();

        // Apply Gaussian blur to reduce noise
        cv::GaussianBlur(grayMat, grayMat, cv::Size(5, 5), 0);

        std::vector<cv::Vec3f> circles;
        
        // Use HoughCircles to detect circles
        cv::HoughCircles(grayMat, circles, cv::HOUGH_GRADIENT, 1, 
                        std::max(workingMinRadius * 2, 30),  // minDist between circle centers
                        workingEdgeThreshold,                 // higher threshold for edge detection
                        workingCenterThreshold,               // accumulator threshold for center detection
                        workingMinRadius,                     // minimum radius
                        workingMaxRadius);                    // maximum radius

        const int borderMargin = 5;

        for (size_t i = 0; i < circles.size(); i++)
        {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);

            // Check if circle is within image bounds with margin
            if (center.x - radius <= borderMargin || center.y - radius <= borderMargin ||
                center.x + radius >= (workingMat.cols - borderMargin) || 
                center.y + radius >= (workingMat.rows - borderMargin))
                continue;

            // Create Object from circle
            cv::RotatedRect rectObject(
                cv::Point2f(center.x, center.y),    // center
                cv::Size2f(radius * 2, radius * 2), // size (diameter)
                0                                    // angle
            );

            Object obj(rectObject);
            
            // Apply object filtering if needed
            if (workingInputObject.Type.isEmpty() || workingInputObject.IsSameType(obj))
            {
                Object circleObject(rectObject);
                
                // Thread-safe append
                {
                    QMutexLocker locker(&dataMutex);
                    outputObjects.append(circleObject);
                    outputPolys.append(circleObject.ToPolygon());
                }
            }
        }
    }
    catch (const cv::Exception& e)
    {
        qDebug() << "OpenCV error in doFindCirclesWork:" << e.what();
        return;
    }

    // Emit signals with thread-safe copies
    QVector<Object> safeOutputObjects;
    QList<QPolygonF> safeOutputPolys;
    
    {
        QMutexLocker locker(&dataMutex);
        safeOutputObjects = outputObjects;
        safeOutputPolys = outputPolys;
    }
    
    emit HadOutput(safeOutputObjects);
    emit HadOutput(safeOutputPolys);
    emit Done(defaultThreadId);
}

void TaskNode::doVisibleObjectsWork()
{
    outputObjects.clear();
    QVector<ObjectInfo*> infoObjects;
    for (int i = 0; i < inputObjects.count(); i++)
    {
        inputObjects[i].Map(inputMatrix);
        outputObjects.append(inputObjects[i]);
    }
    emit HadOutput(outputObjects);
    emit Done(defaultThreadId);
}

void TaskNode::clear(QVector<Object>& objs)
{
    objs.clear();
}
