#include "TaskNode.h"
#include "CalibrationMath.h"
#include <vector>
#include <cmath>

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

void TaskNode::SetPassThrough(bool passThrough)
{
    QMutexLocker locker(&dataMutex);
    IsPass = passThrough;
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

Object TaskNode::GetInputObject() const
{
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

    // Updating calibration is configuration, not a new detection event. The
    // visible-object node runs only when a fresh object vector arrives.
    if (type != VISIBLE_OBJECTS_NODE)
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
    cv::Mat input;
    cv::Size requestedSize;
    bool passThrough = false;
    {
        QMutexLocker locker(&dataMutex);
        input = inputMat.clone();
        requestedSize = size;
        passThrough = IsPass;
    }
    if (input.empty())
        return;

    if (passThrough) {
        emit HadOutput(input);
        return;
    }

    cv::Mat output;
    try {
        if (requestedSize.width > 0) {
            requestedSize.height = qMax(1, qRound(requestedSize.width *
                                                  (static_cast<double>(input.rows) / input.cols)));
            cv::resize(input, output, requestedSize, 0, 0, cv::INTER_LINEAR);
        } else {
            output = input;
        }
    } catch (const cv::Exception& error) {
        qWarning() << "Resize node failed:" << error.what();
        return;
    }
    {
        QMutexLocker locker(&dataMutex);
        outputMat = output;
    }
    emit HadOutput(output);
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

        // Order the four points consistently around the polygon.
        // Point 1 must always be the top-left corner.
        
        // Top-left has the smallest x + y.
        int topLeftIndex = 0;
        float minSum = points[0].x + points[0].y;
        for (int i = 1; i < 4; i++) {
            float sum = points[i].x + points[i].y;
            if (sum < minSum) {
                minSum = sum;
                topLeftIndex = i;
            }
        }
        
        // Bottom-right has the largest x + y.
        int bottomRightIndex = 0;
        float maxSum = points[0].x + points[0].y;
        for (int i = 1; i < 4; i++) {
            float sum = points[i].x + points[i].y;
            if (sum > maxSum) {
                maxSum = sum;
                bottomRightIndex = i;
            }
        }
        
        // Resolve top-right and bottom-left from the remaining points.
        std::vector<int> remainingIndices;
        for (int i = 0; i < 4; i++) {
            if (i != topLeftIndex && i != bottomRightIndex) {
                remainingIndices.push_back(i);
            }
        }
        
        int topRightIndex, bottomLeftIndex;
        // Top-right has a larger x and smaller y than bottom-left.
        if (points[remainingIndices[0]].x > points[remainingIndices[1]].x) {
            topRightIndex = remainingIndices[0];
            bottomLeftIndex = remainingIndices[1];
        } else {
            topRightIndex = remainingIndices[1];
            bottomLeftIndex = remainingIndices[0];
        }
        
                 // Store in clockwise order: top-left, bottom-left, bottom-right, top-right.
         outputPoints[0] = points[topLeftIndex];      // Point 1: top-left
         outputPoints[1] = points[bottomLeftIndex];   // Point 2: bottom-left
         outputPoints[2] = points[bottomRightIndex];  // Point 3: bottom-right
         outputPoints[3] = points[topRightIndex];     // Point 4: top-right

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
    cv::Mat input;
    cv::Mat transform;
    bool passThrough = false;
    {
        QMutexLocker locker(&dataMutex);
        input = inputMat.clone();
        transform = inputMat2.clone();
        passThrough = IsPass;
    }
    if (passThrough) {
        emit HadOutput(input);
        return;
    }

    if (input.empty() || transform.empty()) {
        emit HadOutput(input);
        return;
    }
    cv::Mat output;
    try {
        cv::warpPerspective(input, output, transform, input.size(), cv::INTER_LINEAR);
    } catch (const cv::Exception& error) {
        qWarning() << "Warp node failed:" << error.what();
        return;
    }
    {
        QMutexLocker locker(&dataMutex);
        outputMat = output;
    }
    emit HadOutput(output);
}

void TaskNode::doCropWork()
{
    cv::Mat input;
    QRectF requestedRect;
    bool passThrough = false;
    {
        QMutexLocker locker(&dataMutex);
        input = inputMat.clone();
        requestedRect = inputRect.normalized();
        passThrough = IsPass;
    }
    if (input.empty())
        return;
    if (passThrough) {
        emit HadOutput(input);
        return;
    }

    cv::Mat output = input;
    if (!requestedRect.isNull() && !requestedRect.isEmpty()) {
        const int left = qBound(0, qFloor(requestedRect.left()), input.cols);
        const int top = qBound(0, qFloor(requestedRect.top()), input.rows);
        const int right = qBound(0, qCeil(requestedRect.right()), input.cols);
        const int bottom = qBound(0, qCeil(requestedRect.bottom()), input.rows);
        if (right > left && bottom > top) {
            try {
                output = input(cv::Rect(left, top, right - left, bottom - top)).clone();
            } catch (const cv::Exception& error) {
                qWarning() << "Crop node failed:" << error.what();
                return;
            }
        }
    }
    {
        QMutexLocker locker(&dataMutex);
        outputMat = output;
    }
    emit HadOutput(output);
}

void TaskNode::doDisplayImageWork()
{
    QPixmap pixmap = ImageTool::cvMatToQPixmap(inputMat);

    emit HadOutput(pixmap);
//    emit HadOutput(pixmap, inputObjects);
}

void TaskNode::doColorFilterWork()
{
    cv::Mat input;
    QList<int> parameters;
    int blur = 1;
    bool inverted = false;
    {
        QMutexLocker locker(&dataMutex);
        input = inputMat.clone();
        parameters = intParas;
        blur = intPara;
        inverted = boolPara;
    }
    if (input.empty())
        return;

    blur = qBound(1, blur, 99);
    if ((blur % 2) == 0)
        ++blur;

    cv::Mat filtered;
    try {

    if (parameters.count() == 1)
    {
        if (input.channels() == 1)
            filtered = input;
        else
            cv::cvtColor(input, filtered,
                         input.channels() == 4 ? cv::COLOR_BGRA2GRAY : cv::COLOR_BGR2GRAY);

        cv::threshold(filtered, filtered, qBound(0, parameters[0], 255), 255, cv::THRESH_BINARY);
    }

    else if (parameters.count() == 6)
    {
        cv::Mat bgr;
        if (input.channels() == 4)
            cv::cvtColor(input, bgr, cv::COLOR_BGRA2BGR);
        else if (input.channels() == 1)
            cv::cvtColor(input, bgr, cv::COLOR_GRAY2BGR);
        else
            bgr = input;
        cv::cvtColor(bgr, filtered, cv::COLOR_BGR2HSV);

        cv::Scalar minScalar(qBound(0, parameters[0], 179), qBound(0, parameters[2], 255), qBound(0, parameters[4], 255));
        cv::Scalar maxScalar(qBound(0, parameters[1], 179), qBound(0, parameters[3], 255), qBound(0, parameters[5], 255));

        cv::inRange(filtered, minScalar, maxScalar, filtered);
    }
    else {
        qWarning() << "Color filter requires 1 threshold or 6 HSV parameters";
        return;
    }

    if (inverted)
    {
        cv::bitwise_not(filtered, filtered);
    }

    if (blur > 1)
        cv::medianBlur(filtered, filtered, blur);
    } catch (const cv::Exception& error) {
        qWarning() << "Color filter node failed:" << error.what();
        return;
    }

    {
        QMutexLocker locker(&dataMutex);
        outputMat = filtered;
    }
    emit HadOutput(filtered);
}

void TaskNode::doMappingMatrixWork()
{
    QPolygonF points;
    {
        QMutexLocker locker(&dataMutex);
        points = inputPoly;
    }
    if (points.size() < 4) {
        qWarning() << "Mapping requires two image points and two real-world points";
        return;
    }

    const QPointF image1(points[0].x(), -points[0].y());
    const QPointF image2(points[1].x(), -points[1].y());
    const QPointF real1 = points[2];
    const QPointF real2 = points[3];
    const CalibrationMath::SimilarityResult calibration =
        CalibrationMath::calculateSimilarity(image1, image2, real1, real2);
    if (!calibration.isValid) {
        qWarning() << "Mapping calculation failed:" << calibration.errorMessage;
        return;
    }
    const QMatrix result = calibration.matrix;
    {
        QMutexLocker locker(&dataMutex);
        outputMatrix = result;
    }
    emit HadOutput(result);
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
        findContours(workingMat, contoursContainer, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

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
                obPointer.Type = workingInputObject.Type;
                
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
                circleObject.Type = workingInputObject.Type;
                
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
    QVector<Object> workingObjects;
    QMatrix workingMatrix;

    {
        QMutexLocker locker(&dataMutex);
        workingObjects = inputObjects;
        workingMatrix = inputMatrix;
    }

    QVector<Object> mappedObjects;
    mappedObjects.reserve(workingObjects.size());
    for (auto obj : workingObjects)
    {
        obj.Map(workingMatrix);
        mappedObjects.append(obj);
    }

    {
        QMutexLocker locker(&dataMutex);
        outputObjects = mappedObjects;
    }

    emit HadOutput(mappedObjects);
    emit Done(defaultThreadId);
}

void TaskNode::clear(QVector<Object>& objs)
{
    objs.clear();
}
