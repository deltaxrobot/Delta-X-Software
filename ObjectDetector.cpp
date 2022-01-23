#include "ObjectDetector.h"

ObjectDetector::ObjectDetector(RobotWindow *parent)
	: QWidget(parent)
{
    mParent = parent;

    // ---------- Blob Filter Window---------
	ParameterPanel = new HSVWindow(parent);
	connect(ParameterPanel, SIGNAL(ValueChanged(int, int, int, int, int, int)), this, SLOT(SetHSV(int, int, int, int, int, int)));
	connect(ParameterPanel, SIGNAL(ValueChanged(int)), this, SLOT(SetThreshold(int)));

    //----------- Camera ------------
	Camera = new cv::VideoCapture();	

    //---------- Camera Display ---------
    ProcessingImageTimer = new QTimer(this);
    connect(ProcessingImageTimer, SIGNAL(timeout()), this, SLOT(UpdateEvent()));
    ProcessingImageTimer->start(CameraTimerInterval);

    //------- Object ----------
	PobjectRec.width = DEFAULT_OBJECT_WIDTH;
	PobjectRec.height = DEFAULT_OBJECT_HEIGHT;
	minObjectArea = MIN_OBJECT_AREA;
	maxObjectArea = MAX_OBJECT_AREA;

    //changeAxisDirection();
    DisplayObjects = new QList<cv::RotatedRect>();

	ObjectManager = new BlobManager(parent);

    //---------- Conveyor ----------
	ObjectMovingCalculaterTimer = new QTimer(this);
//    connect(ObjectMovingCalculaterTimer, SIGNAL(timeout()), this, SLOT(UpdateObjectPositionOnConveyor()));
//    ObjectMovingCalculaterTimer->start(CONVEYOR_TIMER_INTERVAL);

    //-------- Camera Window ---------
	cameraWindow = new QWidget();
	cameraWindow->setWindowTitle("Camera Window");
	cameraWindow->setWindowFlags(Qt::WindowStaysOnTopHint);

    //--------- Camera Thread -----------
    VideoProcessorThread = new VideoProcessor();
    VideoProcessorThread->moveToThread(new QThread(SoftwareManager::GetInstance()->SoftwarePointer));
    qRegisterMetaType< cv::Mat >("cv::Mat");
    connect(VideoProcessorThread->thread(), SIGNAL(started()), VideoProcessorThread, SLOT(startVideo()));
    connect(VideoProcessorThread->thread(), SIGNAL(finished()), VideoProcessorThread, SLOT(deleteLater()));
    connect(VideoProcessorThread, SIGNAL(captureImage(cv::Mat)), this, SLOT(GetImage(cv::Mat)));
    connect(VideoProcessorThread, SIGNAL(readImageFailed()), this, SLOT(ProcessErrorCamera()));

    VideoProcessorThread->thread()->start();

    //-------- Camera Display Thread -----------
    VideoDisplayThread = new VideoDisplay();
    VideoDisplayThread->moveToThread(new QThread(SoftwareManager::GetInstance()->SoftwarePointer));
    qRegisterMetaType< cv::Mat >("cv::Mat");
    connect(VideoDisplayThread->thread(), SIGNAL(started()), VideoDisplayThread, SLOT(Loop()));
    connect(VideoDisplayThread->thread(), SIGNAL(finished()), VideoDisplayThread, SLOT(deleteLater()));
    connect(VideoDisplayThread, SIGNAL(neededUpdatePixmapToLabel(QLabel*, QPixmap)), this, SLOT(UpdatePixmapToLabel(QLabel*, QPixmap)));

    VideoDisplayThread->thread()->start();
}

ObjectDetector::~ObjectDetector()
{
    VideoProcessorThread->CloseLoop();
    VideoProcessorThread->thread()->quit();
    VideoProcessorThread->thread()->wait();

    VideoDisplayThread->CloseLoop();
    VideoDisplayThread->thread()->quit();
    VideoDisplayThread->thread()->wait();
}

void ObjectDetector::LoadTestImage()
{
	QString imageName;
	imageName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	if (imageName == "")
		return;

	cv::String imgName = imageName.toStdString();
	captureImage = cv::imread(imgName, cv::IMREAD_COLOR);
	processImage();
}

void ObjectDetector::LoadCamera2()
{
    if (cbExternalCamera != NULL)
    {
        if(cbExternalCamera->isChecked() == true)
        {
            QMessageBox::information(this, "Notify", "You are using the camera from the outside. Please uncheck the box below if you want to use the webcam.");
            return;
        }
    }

    QToolButton* loadBt = qobject_cast<QToolButton*>(sender());
	if (loadBt->isChecked())
	{        
        QStringList cameraItems;

        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        for (int i = 0; i < cameras.size(); i++)
        {
            cameraItems.append(QString::number(i) + QString(" - ") + cameras[i].description());
        }

		bool ok;
        QString text = QInputDialog::getItem(this, tr("Open camera"), tr("Camera ID: "), cameraItems, 0, false, &ok);

		if (ok && !text.isEmpty())
        {
            QString cameraIDText = text.mid(0, text.indexOf(" - "));
            int cameraID = cameraIDText.toInt();

            if (cameraItems.count() > 2)
            {
                if (cameraID == 0)
                {
                    cameraID = 1;
                }
                else if(cameraID == 1)
                {
                    cameraID = 0;
                }
            }

            RunningCamera = cameraID;

			lbCameraState->setEnabled(true);
			pbPlayCammera->setChecked(true);
            //cameraWidget->InitParameter();

            loadBt->setText("Stop Camera");

            bool isCameraUsingByOtherRobot = false;

            if (mParent->RobotManagerPointer != NULL)
            {
                if (mParent->RobotManagerPointer->RobotWindows.size() > 0)
                {
                    for (int i = 0; i < mParent->RobotManagerPointer->RobotWindows.size(); i++)
                    {
                        if (mParent == mParent->RobotManagerPointer->RobotWindows.at(i))
                            continue;

                        if (mParent->RobotManagerPointer->RobotWindows.at(i)->DeltaImageProcesser->RunningCamera == RunningCamera)
                        {
                            Camera = mParent->RobotManagerPointer->RobotWindows.at(i)->DeltaImageProcesser->Camera;
                            VideoProcessorThread->getCamera(Camera);
                            isCameraUsingByOtherRobot = true;
                        }
                    }
                }
            }

            if (isCameraUsingByOtherRobot == false)
            {
//                Camera->open(cameraID);
//                Camera->set(cv::CAP_PROP_FRAME_WIDTH, leWidth->text().toInt());
//                Camera->set(cv::CAP_PROP_FRAME_HEIGHT, leHeight->text().toInt());

//                leWidth->setText(QString::number((int)Camera->get(cv::CAP_PROP_FRAME_WIDTH)));
//                leHeight->setText(QString::number((int)Camera->get(cv::CAP_PROP_FRAME_HEIGHT)));

                VideoProcessorThread->getCamera(Camera, cameraID, leWidth, leHeight);
            }

            UpdateRatios(Camera->get(cv::CAP_PROP_FRAME_WIDTH), Camera->get(cv::CAP_PROP_FRAME_HEIGHT));
            ChangeCameraWidgetHeight(QString::number(CameraWidgetHeight));

			IsCameraPause = false;
		}
		else
		{			
			loadBt->setChecked(false);
			IsCameraPause = false;
			RunningCamera = -1;
		}
	}
	else
	{
		stopCamera();
		return;
	}
}

void ObjectDetector::CaptureCamera()
{
	if (!Camera->isOpened())
		return;	

    if (!Camera->read(captureImage))
	{
		stopCamera();
        QMessageBox::information(this, "Problem", "The camera has lost connection!");
		return;
    }
}

void ObjectDetector::GetImage(cv::Mat mat)
{
    if (IsCameraPause == true)
        return;

    if (captureImage.empty() == false)
        captureImage.release();

    captureImage = mat;

    EncoderPositionAtCameraCapture = EncoderPosition;

}

void ObjectDetector::PauseCamera()
{
	IsCameraPause = true;
	pbPlayCammera->setChecked(false);
}

void ObjectDetector::PlayCamera(bool state)
{
	if (state == true)
	{
		ResumeCamera();
	}
	else
	{
		PauseCamera();
	}
}

void ObjectDetector::ResumeCamera()
{
	IsCameraPause = false;
	pbPlayCammera->setChecked(true);
}

void ObjectDetector::stopCamera()
{
	lbCameraState->setEnabled(false);
	Camera->release();
	RunningCamera = -1;
	IsCameraPause = false;
    isFirstRead = true;
    pbLoadCamera->setText("Load Camera");

    VideoProcessorThread->stopVideo();
}

void ObjectDetector::processImage()
{
    //ElapsedTimer.start();
    if (cameraWidget->pixmap() != nullptr && isFirstLoad == true)
	{
        //cameraWidget->InitParameter();
		isFirstLoad = false;
	}

	if (!captureImage.data)
	{
		return;
	}

    if (isFirstRead == true)
    {
        CalculateMappingMatrix();
    }

    //qDebug() << "matrix: " << ElapsedTimer.elapsed();


    if (IsPerspectiveMode == true)
    {
        transformPerspective(captureImage, PperspectivePoints, calibImage);
    }
    else
    {
        calibImage = captureImage.clone();
    }

    //qDebug() << "transform: " << ElapsedTimer.elapsed();

    filterMat = calibImage.clone();
    resultImage = calibImage.clone();
    //qDebug() << "copy: " << ElapsedTimer.elapsed();

    //----------------------
    // Detect objects in image and manage them
    if (rbBlobFilter->isChecked())
    {
        postProcessing();
        //qDebug() << "post processing: " << ElapsedTimer.elapsed();
        detectBlobObjects(filterMat);

        processDetectingObjectOnCamera(resultImage, *DisplayObjects, BLUE_COLOR);
        DisplayObjects->clear();
        UpdateTrackingInfo();

        UpdateDetectingResultToWidgets();
    }
    else if (rbCircleFilter->isChecked())
    {
        detectCircleObjects(calibImage);
    }
    else if (rbExternalFilter->isChecked())
    {
        if (cbImageSourceForExternal->currentText() == "Origin Image")
        {
            sendImageToExternalScript(captureImage);
        }
        else if (cbImageSourceForExternal->currentText() == "Calib Image")
        {
            static int i = 0;
            putText(calibImage, std::to_string(i++), cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 2);
            qDebug() << "detect: " << ElapsedTimer.elapsed();
            ElapsedTimer.start();
            sendImageToExternalScript(calibImage);
        }
        else if (cbImageSourceForExternal->currentText() == "Filter Image")
        {
            postProcessing();

            sendImageToExternalScript(filterMat);
        }
    }
    //qDebug() << "detect: " << ElapsedTimer.elapsed();

    ElapsedTimer.start();
    processDetectingObjectOnCamera(resultImage, *DisplayObjects, BLUE_COLOR);
    qDebug() << "time in ms: " << ElapsedTimer.elapsed();
    //DisplayObjects->clear();
    UpdateTrackingInfo();

    UpdateDetectingResultToWidgets();

}

void ObjectDetector::UpdateEvent()
{
    processImage();

    if (IsEncoderEnable == false)
    {
        UpdateObjectPositionOnConveyor();
    }

    if (!cameraWindow->isVisible() && cameraWidget->parentWidget() == cameraWindow)
    {
        CloseCameraWindow();
    }
}

void ObjectDetector::SaveFPS()
{
    CameraFPS = leFPS->text().toFloat();
    CameraTimerInterval = 1000.0f / CameraFPS;

	if (CameraFPS > 0)
        ProcessingImageTimer->setInterval(CameraTimerInterval);
}

void ObjectDetector::ProcessErrorCamera()
{
    stopCamera();
    QMessageBox::information(this, "Problem", "The camera has lost connection!");
}

void ObjectDetector::SetObjectSizePointer(QLineEdit * wRec, QLineEdit * lRec, QLineEdit* hRec)//, QLineEdit * distance, QLineEdit * xCoor, QLineEdit * yCoor)
{
    leWRec = wRec;
    leLRec = lRec;
    leHRec = hRec;
}

void ObjectDetector::SetObjectErrorPointer(QLineEdit *objectErrorSize, QLineEdit *trackingError)
{
    leObjectErrorSize = objectErrorSize;
    leTrackingError = trackingError;
}

void ObjectDetector::SetCalibLinePointer(QLineEdit *realityLine, QLineEdit *imageLine)
{
    leRealityLine = realityLine;
    leImageLine = imageLine;

    if (cameraWidget != NULL)
    {
        int imageLine = leImageLine->text().toInt();
        float realLine = leRealityLine->text().toFloat();

        cameraWidget->ChangeRealLineValue(realLine);
        cameraWidget->ChangeImageLineValue(imageLine);
    }
}

void ObjectDetector::SetScaleRoateEnablePointer(QCheckBox *scaleRotateEnable)
{
    cbScaleRotateToolEnable = scaleRotateEnable;
}

void ObjectDetector::SetRealityCalibPointPointer(QLineEdit *realityPoint1X, QLineEdit *realityPoint1Y, QLineEdit *realityPoint2X, QLineEdit *realityPoint2Y)
{
    leRealityPoint1X = realityPoint1X;
    leRealityPoint1Y = realityPoint1Y;
    leRealityPoint2X = realityPoint2X;
    leRealityPoint2Y = realityPoint2Y;

    if (cameraWidget != NULL)
    {
        int x1 = leRealityPoint1X->text().toInt();
        int y1 = leRealityPoint1Y->text().toInt();
        int x2 = leRealityPoint2X->text().toInt();
        int y2 = leRealityPoint2Y->text().toInt();

        cameraWidget->ChangeRealPointValue(QPoint(x1, y1));
        cameraWidget->ChangeRealPoint2Value(QPoint(x2, y2));
    }
}

void ObjectDetector::SetImageCalibPointPointer(QLineEdit *imagePoint1X, QLineEdit *imagePoint1Y, QLineEdit *imagePoint2X, QLineEdit *imagePoint2Y)
{
    leImagePoint1X = imagePoint1X;
    leImagePoint1Y = imagePoint1Y;
    leImagePoint2X = imagePoint2X;
    leImagePoint2Y = imagePoint2Y;

    if (cameraWidget != NULL)
    {
        int x1 = leImagePoint1X->text().toInt();
        int y1 = leImagePoint1Y->text().toInt();
        int x2 = leImagePoint2X->text().toInt();
        int y2 = leImagePoint2Y->text().toInt();

        cameraWidget->ChangeImagePointValue(QPoint(x1, y1));
        cameraWidget->ChangeImagePoint2Value(QPoint(x2, y2));
    }
}

void ObjectDetector::SetResultScreenPointer(CameraWidget * resultImage)
{
    cameraWidget = resultImage;
    cameraLayout = cameraWidget->parentWidget();
	cameraBox = new QVBoxLayout(cameraLayout);
	cameraBox->setMargin(0);
    cameraBox->addWidget(cameraWidget);
}

void ObjectDetector::SetObjectScreenPointer(QLabel * objectImage)
{
	lbObjectImage = objectImage;
}

void ObjectDetector::SetCameraInfoWidget(QLineEdit* fps, QLabel* state, QToolButton* playBt, QToolButton* loadBt = NULL)
{
	pbPlayCammera = playBt;
	leFPS = fps;
	lbCameraState = state;
    pbLoadCamera = loadBt;
}

void ObjectDetector::SetTrackingWidgetPointer(QLabel* lbTracking, QLabel* lbVisible)
{
	lbTrackingObjectNumber = lbTracking;
    lbVisibleObjectNumber = lbVisible;
}

void ObjectDetector::SetResolutionWidget(QLineEdit *w, QLineEdit *h)
{
    leWidth = w;
    leHeight = h;
}

void ObjectDetector::SetDisplayInfoWidget(QLabel *scale, QLabel *size)
{
    lbScale = scale;
    lbImageSize = size;
}

void ObjectDetector::SetChessboardWidget(QLineEdit *chessW, QLineEdit *chessH, QLineEdit *chesSquareSize, QLineEdit *chessPoints[4][2])
{
    leChessboardWidth = chessW;
    leChessboardHeight = chessH;
    leChessboardSquareSize = chesSquareSize;

    leChessboardPoints = chessPoints;
}

void ObjectDetector::SetXAngleWidget(QLineEdit *xAngle)
{
    leXAxisAngle = xAngle;
}

void ObjectDetector::SetObjectFilterWidget(QRadioButton *blobFilter, QRadioButton *externalFilter, QRadioButton *circleFilter)
{
    rbBlobFilter = blobFilter;
    rbExternalFilter = externalFilter;
    rbCircleFilter = circleFilter;
}

void ObjectDetector::SetFilterParaWidget(QLineEdit *pythonUrl)
{
    lePythonUrl = pythonUrl;
}

void ObjectDetector::SetHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV)
{
	// Make binary image
	HSVValue[0] = minH;
	HSVValue[1] = maxH;
	HSVValue[2] = minS;
	HSVValue[3] = maxS;
	HSVValue[4] = minV;
	HSVValue[5] = maxV;

	filterMethod = HSV_SPACE;

    if (calibImage.empty())
        return;

    cvtColor(calibImage, filterMat, CV_BGR2HSV);

	cv::Scalar minScalar(minH, minS, minV);
	cv::Scalar maxScalar(maxH, maxS, maxV);

    cv::inRange(filterMat, minScalar, maxScalar, filterMat);
}

void ObjectDetector::SetThreshold(int value)
{
	// Make binary image
	thresholdValue = value;

	filterMethod = THRESHOLD_SPACE;

    if (calibImage.empty())
        return;

    cvtColor(calibImage, filterMat, CV_BGR2GRAY);

    cv::threshold(filterMat, filterMat, value, 255, CV_THRESH_BINARY);
}

void ObjectDetector::OpenExternalFilterScript()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Python Script"), lePythonUrl->text(), tr("Python Files (*.py)"));
    lePythonUrl->setText(path);
}

void ObjectDetector::GetObjectInfo(int x, int y, int l, int w)
{
	Dobject.setX(x);
	Dobject.setY(y);
	Dobject.setHeight(l);
	Dobject.setWidth(w);

	PobjectRec.x = x / DnPRatio;
	PobjectRec.y = y / DnPRatio;

	GetObjectInfo(l, w);
	
	leWRec->setText(QString::number((int)(w / DnRratio)));
	leLRec->setText(QString::number((int)(l / DnRratio)));
}

void ObjectDetector::GetObjectInfo(int l, int w)
{
    if (cameraWidget->pixmap() == NULL)
		return;

	Dobject.setHeight(l);
	Dobject.setWidth(w);
	// Update information about the object to be identified
	
	PobjectRec.width = w / DnPRatio;
	PobjectRec.height = l / DnPRatio;

    ObjectError = leObjectErrorSize->text().toFloat();

    if (ObjectError >= 1)
    {
        ObjectError = 0.5f;
    }

    minObjectArea = (PobjectRec.width * ( 1.0 - ObjectError)) * (PobjectRec.height * (1.0 - APPROXIMATE_RATIO));
    maxObjectArea = (PobjectRec.width * (1.0 + ObjectError)) * (PobjectRec.height + (1.0 + APPROXIMATE_RATIO));

	//ObjectManager->SetApproximateValue(cv::Point3d((float)l * 0.8f, (float)w * 0.8f, 60));

	//Display ROI is cut from widget
    QPixmap regionPixmap = cameraWidget->pixmap()->copy(Dobject.x(), Dobject.y(), w, l);

	if (w > l)
		regionPixmap = regionPixmap.scaledToWidth(lbObjectImage->width());
	else
		regionPixmap = regionPixmap.scaledToHeight(lbObjectImage->height());

    lbObjectImage->setPixmap(regionPixmap);
}

void ObjectDetector::GetObjectError()
{
    QLineEdit* le = qobject_cast<QLineEdit*>(sender());

    if (le == NULL)
        return;

    if (le->text().toFloat() >= 1)
    {
        ObjectError = 0.5f;
    }

    ObjectError = le->text().toFloat();
}

void ObjectDetector::GetPerspectivePoints(QPoint a, QPoint b, QPoint c, QPoint d)
{
	DperspectivePoints[0] = a;
	DperspectivePoints[1] = b;
	DperspectivePoints[2] = c;
	DperspectivePoints[3] = d;

	PperspectivePoints.clear();
	PperspectivePoints.push_back(cv::Point(a.x(), a.y()) / DnPRatio);
	PperspectivePoints.push_back(cv::Point(b.x(), b.y()) / DnPRatio);
	PperspectivePoints.push_back(cv::Point(c.x(), c.y()) / DnPRatio);
	PperspectivePoints.push_back(cv::Point(d.x(), d.y()) / DnPRatio);

    updatePerspectivePointsToUI();
}

void ObjectDetector::GetProcessArea(QRect processArea)
{
	DselectedRec = processArea;

	PselectedRectangle.width = processArea.width() / DnPRatio;
	PselectedRectangle.height = processArea.height() / DnPRatio;
	PselectedRectangle.x = processArea.x() / DnPRatio;
	PselectedRectangle.y = processArea.y() / DnPRatio;
}

void ObjectDetector::GetCalibLine(QPoint p1, QPoint p2)
{
//	DcalibLine.setP1(p1);
//	DcalibLine.setP2(p2);



//	PcalibLinePoint1 = cv::Point(p1.x() / DnPRatio, p1.y() / DnPRatio);
//	PcalibLinePoint2 = cv::Point(p2.x() / DnPRatio, p2.y()) / DnPRatio;

    //GetCalibPoint(DcalibPoint.x(), DcalibPoint.y());
}

void ObjectDetector::GetDistance(int distance)
{
    leImageLine->setText(QString::number(distance));
//    float realDistance = leRealityLine->text().toFloat();
//    cameraWidget->ChangeRealLineValue(realDistance);

//	float processDistance = (float)distance / DnPRatio;
//	PnRRatio = processDistance / realDistance;
//	DnRratio = (float)distance / realDistance;
}

//void ObjectDetector::GetCalibPoint(int x, int y)
//{
//	DcalibPoint.setX(x);
//	DcalibPoint.setY(y);

//	if (resizeImage.cols > 0)
//	{
//		PcalibPoint.x = x / DnPRatio;
//		PcalibPoint.y = y / DnPRatio;
//	}

//    if (leRealityPoint1X == NULL)
//		return;

//    float xRealCalibPoint = leRealityPoint1X->text().toFloat();
//    float yRealCalibPoint = leRealityPoint1Y->text().toFloat();

//	float theta = 0;

//	if (axisDirection == X_AXIS_DOWN)
//	{
//		/*xRealCamOri = xRealCalibPoint - y / DnRratio;
//		yRealCamOri = yRealCalibPoint - x / DnRratio;*/

//		theta = -M_PI_2;
//	}
//	else if (axisDirection == X_AXIS_RIGHT)
//	{
//		/*xRealCamOri = -xRealCalibPoint + x / DnRratio;
//		yRealCamOri = yRealCalibPoint + y / DnRratio;*/

//		theta = 0;
//	}

//	else if (axisDirection == X_AXIS_LEFT)
//	{
//		/*xRealCamOri = -xRealCalibPoint - x / DnRratio;
//		yRealCamOri = yRealCalibPoint - y / DnRratio;*/

//		theta = M_PI;
//	}

//	else if (axisDirection == X_AXIS_UP)
//	{
//		/*xRealCamOri = xRealCalibPoint + y / DnRratio;
//		yRealCamOri = yRealCalibPoint + x / DnRratio;*/

//		theta = M_PI_2;
//	}

//	//  ScaleMatrix * RotateMatrix * TranslateMatrix * PPoint = RPoint
	
//	QMatrix RotateMatrix(qCos(theta), -qSin(theta), qSin(theta), qCos(theta), 0, 0);
//	QMatrix ScaleMatrix(1.0f / PnRRatio, 0, 0, -1.0f / PnRRatio, 0, 0);

//	QMatrix ScaleRotateMatrix = ScaleMatrix * RotateMatrix;

//	// x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
//	// y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

//	float dx = xRealCalibPoint - (ScaleRotateMatrix.m11() * (x / DnPRatio) + ScaleRotateMatrix.m21() * (y / DnPRatio));
//	float dy = yRealCalibPoint - (ScaleRotateMatrix.m12() * (x / DnPRatio) + ScaleRotateMatrix.m22() * (y / DnPRatio));

//	P2RMatrix.setMatrix(ScaleRotateMatrix.m11(), ScaleRotateMatrix.m12(), ScaleRotateMatrix.m21(), ScaleRotateMatrix.m22(), dx, dy);
	
//    QPoint result = P2RMatrix.map(QPoint(x / DnPRatio, y / DnPRatio));
//}

void ObjectDetector::GetCalibPoint(QPoint p1, QPoint p2)
{
    leImagePoint1X->setText(QString::number(p1.x() / DnPRatio));
    leImagePoint1Y->setText(QString::number(p1.y() / DnPRatio));
    leImagePoint2X->setText(QString::number(p2.x() / DnPRatio));
    leImagePoint2Y->setText(QString::number(p2.y() / DnPRatio));
}

void ObjectDetector::GetMappingPoint(QPoint mappingPoint)
{
    mappingPoint = mappingPoint / DnPRatio;
    QPointF RPoint = P2RMatrix.map(QPointF(mappingPoint.x(), 0 - mappingPoint.y()));
    cameraWidget->ChangeRealMappingValue(RPoint);
}

void ObjectDetector::SwitchLayer()
{
	cameraLayer++;
	if (cameraLayer > 2)
	{
		cameraLayer = 0;
	}
}

void ObjectDetector::SelectLayer(int id)
{
	cameraLayer = id;
}

void ObjectDetector::changeAxisDirection()
{
    if (leRealityPoint1X != NULL)
    {
        int newX = leRealityPoint1Y->text().toInt();
        int newY = 0 - leRealityPoint1X->text().toInt();
        leRealityPoint1X->setText(QString::number(newX));
        leRealityPoint1Y->setText(QString::number(newY));

        cameraWidget->ChangeRealPointValue(QPoint(newX, newY));
    }

	if (axisDirection == X_AXIS_LEFT)
    {
        axisDirection = X_AXIS_DOWN;
        cameraWidget->ChangeXDirection(-90);
        leXAxisAngle->setText("-90");
	}
	else if (axisDirection == X_AXIS_DOWN)
	{		
        axisDirection = X_AXIS_RIGHT;
        cameraWidget->ChangeXDirection(0);
        leXAxisAngle->setText("0");
	}
	else if (axisDirection == X_AXIS_RIGHT)
    {
        axisDirection = X_AXIS_UP;
        cameraWidget->ChangeXDirection(90);
        leXAxisAngle->setText("90");
	}
	else if (axisDirection == X_AXIS_UP)
    {
        axisDirection = X_AXIS_LEFT;
        cameraWidget->ChangeXDirection(180);
        leXAxisAngle->setText("180");
	}

    //GetCalibPoint(DcalibPoint.x(), DcalibPoint.y());
}

void ObjectDetector::TurnTransformPerspective(bool isTurnOn)
{
    IsPerspectiveMode = isTurnOn;
    cameraWidget->IsQuadrangleEnable = isTurnOn;
    if (pbPlayCammera->isChecked() == false)
    {
        pbPlayCammera->click();
    }
}

void ObjectDetector::FindChessboard()
{
    if (pbPlayCammera->isChecked() == true)
    {
        pbPlayCammera->click();
    }

    int width = leChessboardWidth->text().toInt();
    int height = leChessboardHeight->text().toInt();

    cv::Size patternsize(width, height);
    cv::Mat gray;
    cv::Mat mat = calibImage.clone();

    cvtColor(calibImage, gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool patternfound = findChessboardCorners(gray, patternsize, corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

    if(patternfound)
    {
      cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

      std::vector<cv::Point> points;
      PperspectivePoints.clear();

      points.push_back(cv::Point(corners[0].x, corners[0].y));
      points.push_back(cv::Point(corners[width - 1].x, corners[width - 1].y));
      if (height % 2 == 1)
      {
          points.push_back(cv::Point(corners[width * height - 1].x, corners[width * height - 1].y));
          points.push_back(cv::Point(corners[width * (height - 1)].x, corners[width * (height - 1)].y));
      }
      else
      {
        points.push_back(cv::Point(corners[width * (height - 1)].x, corners[width * (height - 1)].y));
        points.push_back(cv::Point(corners[width * height - 1].x, corners[width * height - 1].y));
      }

      if (points[2].x < points[0].x)
      {
          PperspectivePoints.push_back(points[3]);
          PperspectivePoints.push_back(points[2]);
          PperspectivePoints.push_back(points[1]);
          PperspectivePoints.push_back(points[0]);
      }
      else
      {
          PperspectivePoints.push_back(points[0]);
          PperspectivePoints.push_back(points[3]);
          PperspectivePoints.push_back(points[2]);
          PperspectivePoints.push_back(points[1]);
      }

      updatePerspectivePointsToUI();

      circle(calibImage, PperspectivePoints[0], 10, cv::Scalar(0, 255, 0), 2);
      putText(calibImage, "1", PperspectivePoints[0], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);

      circle(calibImage, PperspectivePoints[1], 10, cv::Scalar(255, 0, 0), 2);
      putText(calibImage, "2", PperspectivePoints[1], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);

      circle(calibImage, PperspectivePoints[2], 10, cv::Scalar(0, 0, 255), 2);
      putText(calibImage, "3", PperspectivePoints[2], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);

      circle(calibImage, PperspectivePoints[3], 10, cv::Scalar(255, 255, 0), 2, cv::LINE_AA);
      putText(calibImage, "4", PperspectivePoints[3], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 0), 2, cv::LINE_AA);


      drawChessboardCorners(calibImage, patternsize, cv::Mat(corners), patternfound);

      QVector<QPointF> fPoints(4);
      fPoints[0].setX(float(PperspectivePoints[0].x) / calibImage.cols);
      fPoints[0].setY(float(PperspectivePoints[0].y) / calibImage.rows);
      fPoints[1].setX(float(PperspectivePoints[1].x) / calibImage.cols);
      fPoints[1].setY(float(PperspectivePoints[1].y) / calibImage.rows);
      fPoints[2].setX(float(PperspectivePoints[2].x) / calibImage.cols);
      fPoints[2].setY(float(PperspectivePoints[2].y) / calibImage.rows);
      fPoints[3].setX(float(PperspectivePoints[3].x) / calibImage.cols);
      fPoints[3].setY(float(PperspectivePoints[3].y) / calibImage.rows);

      cameraWidget->ChangeQuadrangle(fPoints);

      UpdateLabelImage(calibImage, cameraWidget);
    }
    else
    {
        QMessageBox::information(this, "Problem", "Chess board not found");
    }
}

void ObjectDetector::UpdateCalibLine(int realLine, int imageLine)
{
    leRealityLine->setText(QString::number(realLine));
    leImageLine->setText(QString::number(imageLine));
}

void ObjectDetector::TurnCalibDisplay(bool state)
{
    IsCalibInfoVisible = state;
    cameraWidget->IsCalibVisible = state;
}

void ObjectDetector::ExpandCameraWidget(bool isExpand)
{
	if (isExpand == true)
	{
        cameraWidget->ChangeSize(600 * CameraRatio, 600);
	}
	else
	{
        cameraWidget->ChangeSize(300 * CameraRatio, 300);
    }
}

void ObjectDetector::ChangeCameraWidgetHeight(QString valueS)
{
    CameraWidgetHeight = valueS.toInt();
    if (cameraWidget->parent() != cameraWindow)
    {
        cameraWidget->parentWidget()->parentWidget()->parentWidget()->setMinimumHeight(CameraWidgetHeight);
    }

    cameraWidget->ChangeSize(CameraWidgetHeight * CameraRatio, CameraWidgetHeight);
}

void ObjectDetector::OpenCameraWindow()
{
    cameraWidget->setParent(cameraWindow);
	cameraWindow->show();


    //lbResultImage->ChangeSize(800, 600);
}

void ObjectDetector::CloseCameraWindow()
{
    cameraBox->addWidget(cameraWidget);
    //cameraWidget->ChangeSize(400, 300);
}

void ObjectDetector::UpdateToCameraWidget()
{
    float realX1 = leRealityPoint1X->text().toFloat();
    float realY1 = leRealityPoint1Y->text().toFloat();
    float realX2 = leRealityPoint2X->text().toFloat();
    float realY2 = leRealityPoint2Y->text().toFloat();

    cameraWidget->ChangeRealPointValue(QPoint(realX1, realY1));
    cameraWidget->ChangeRealPoint2Value(QPoint(realX2, realY2));
}

void ObjectDetector::UpdatePixmapToLabel(QLabel *lb, QPixmap pm)
{
    lb->setPixmap(pm);
}

void ObjectDetector::UpdateObjectPositionOnConveyor()
{
    float distance = 0;

    if (IsEncoderEnable == false)
    {
        distance = ConveyorVel * ((float)CONVEYOR_TIMER_INTERVAL / 1000);
    }
    else
    {
        distance = MovingDistance;
    }

    float xOffset1 = 100;
    float yOffset1 = 100;
    float xOffset2 = 100;
    float yOffset2 = 100;
    float xOffset = 100;
    float yOffset = 100;

    UpdatePointPositionOnConveyor(xOffset2, yOffset2, DeviationAngle, distance);

    xOffset = xOffset2 - xOffset1;
    yOffset = yOffset2 - yOffset1;

    if (DeviationAngle != 0)
    {
        ObjectManager->UpdateNewObjectMoving(xOffset, yOffset);
    }
    else
    {
        if (DirName.toLower() == "x")
        {
            ObjectManager->UpdateNewObjectMoving(distance, 0);
        }
        else
        {
            ObjectManager->UpdateNewObjectMoving(0, distance);
        }
    }

	emit ObjectValueChanged(ObjectManager->ObjectContainer);

	//Debug(QString::number((distance)));

}

void ObjectDetector::EncoderEnabled(bool status)
{
    IsEncoderEnable = status;
}

void ObjectDetector::SaveSetting(QString fileName)
{
    ParameterPanel->SaveSetting(fileName);

    QSettings settings(fileName, QSettings::IniFormat);

    SaveSetting(&settings);
}

void ObjectDetector::SaveSetting(QSettings *setting)
{
    setting->beginGroup("Parameter");
    ParameterPanel->SaveSetting(setting);
    setting->endGroup();

    setting->setValue("CameraWidth", leWidth->text());
    setting->setValue("CameraHeight", leHeight->text());
    setting->setValue("CameraFPS", leFPS->text());

    setting->setValue("ExternalCameraEnable", cbExternalCamera->isChecked());

    setting->setValue("ChessWidth", leChessboardWidth->text());
    setting->setValue("ChessHeight", leChessboardHeight->text());
    setting->setValue("ChessSize", leChessboardSquareSize->text());


    setting->setValue("ObjectWidth", PobjectRec.width);
    setting->setValue("ObjectHeight", PobjectRec.height);
    setting->setValue("RealObjectWidth", leWRec->text());
    setting->setValue("RealObjectLength", leLRec->text());
    setting->setValue("RealObjectHeight", leHRec->text());
    setting->setValue("ObjectErrorSize", leObjectErrorSize->text());
    setting->setValue("TrackingError", leTrackingError->text());
    setting->setValue("MinObjectArea", minObjectArea);
    setting->setValue("MaxObjectArea", maxObjectArea);

    setting->setValue("RealCalibPointX", leRealityPoint1X->text());
    setting->setValue("RealCalibPointY", leRealityPoint1Y->text());
    setting->setValue("RealCalibPoint2X", leRealityPoint2X->text());
    setting->setValue("RealCalibPoint2Y", leRealityPoint2Y->text());
    setting->setValue("RealCalibLine", leRealityLine->text());

    QString filterCheckState = (rbBlobFilter->isChecked())?"100":(rbExternalFilter->isChecked()?"010":"001");
    setting->setValue("Filter", filterCheckState);
    setting->setValue("ExternalScriptUrl", lePythonUrl->text());
}

void ObjectDetector::LoadSetting(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);

    LoadSetting(&settings);
}

void ObjectDetector::LoadSetting(QSettings *setting)
{
    setting->beginGroup("Parameter");
    ParameterPanel->LoadSetting(setting);
    setting->endGroup();

    leWidth->setText(setting->value("CameraWidth", leWidth->text()).toString());
    leHeight->setText(setting->value("CameraHeight", leHeight->text()).toString());
    leFPS->setText(setting->value("CameraFPS", leFPS->text()).toString());

    cbExternalCamera->setChecked(setting->value("ExternalCameraEnable", false).toBool());

    leChessboardWidth->setText(setting->value("ChessWidth", leChessboardWidth->text()).toString());
    leChessboardHeight->setText(setting->value("ChessHeight", leChessboardHeight->text()).toString());
    leChessboardSquareSize->setText(setting->value("ChessSize", leChessboardSquareSize->text()).toString());


    PobjectRec.width = setting->value("ObjectWidth", PobjectRec.width).toInt();
    PobjectRec.height = setting->value("ObjectHeight", PobjectRec.height).toInt();
    leWRec->setText(setting->value("RealObjectWidth", leWRec->text()).toString());
    leLRec->setText(setting->value("RealObjectLength", leLRec->text()).toString());
    leHRec->setText(setting->value("RealObjectHeight", leHRec->text()).toString());
    leObjectErrorSize->setText(setting->value("ObjectErrorSize", leObjectErrorSize->text()).toString());
    leTrackingError->setText(setting->value("TrackingError", leTrackingError->text()).toString());
    minObjectArea = setting->value("MinObjectArea", minObjectArea).toInt();
    maxObjectArea = setting->value("MaxObjectArea", maxObjectArea).toInt();

    leRealityPoint1X->setText(setting->value("RealCalibPointX", leRealityPoint1X->text()).toString());
    leRealityPoint1Y->setText(setting->value("RealCalibPointY", leRealityPoint1Y->text()).toString());
    leRealityPoint2X->setText(setting->value("RealCalibPoint2X", leRealityPoint2X->text()).toString());
    leRealityPoint2Y->setText(setting->value("RealCalibPoint2Y", leRealityPoint2Y->text()).toString());

    cameraWidget->ChangeRealPointValue(QPoint(leRealityPoint1X->text().toFloat(), leRealityPoint1Y->text().toFloat()));
    cameraWidget->ChangeRealPoint2Value(QPoint(leRealityPoint2X->text().toFloat(), leRealityPoint2Y->text().toFloat()));

    leRealityLine->setText(setting->value("RealCalibLine", leRealityLine->text()).toString());

    QString filterCheckState = setting->value("Filter", "100").toString();
    if (filterCheckState.length() >= 3)
    {
        rbBlobFilter->setChecked(filterCheckState[0] == '1'?true:false);
        rbExternalFilter->setChecked(filterCheckState[1] == '1'?true:false);
        rbCircleFilter->setChecked(filterCheckState[2] == '1'?true:false);
    }

    lePythonUrl->setText(setting->value("ExternalScriptUrl", lePythonUrl->text()).toString());


}

void ObjectDetector::GetExternalScriptSocket(QTcpSocket *socket)
{
    PythonTcpClient = socket;
}

void ObjectDetector::OpenParameterPanel()
{	
	ParameterPanel->exec();
}

void ObjectDetector::UpdateLabelImage(cv::Mat mat, QLabel* label)
{
	QImage img = ImageTool::cvMatToQImage(mat);
    label->setPixmap(QPixmap::fromImage(img).scaledToHeight(label->size().height()));
}

void ObjectDetector::SetConvenyorVelocity(float val, QString dir)
{
    ConveyorVel = val;
    DirName = dir;
}

void ObjectDetector::ProcessDisplayAfterReceivingObjectData()
{
    processDetectingObjectOnCamera(resultImage, *DisplayObjects, BLUE_COLOR);

    UpdateTrackingInfo();

    UpdateDetectingResultToWidgets();
}

void ObjectDetector::UpdatePointPositionOnConveyor(QLineEdit *x, QLineEdit *y, float angle, float distance)
{
    QPointF point3;

    point3.setX(x->text().toFloat());
    point3.setY(y->text().toFloat());


    QLineF line;
    line.setP1(point3);
    line.setAngle(angle);

    if (distance == 0)
        return;

    line.setLength(distance);

    if (point3 == QPointF(0, 0))
    {
        float cosa = qCos(qDegreesToRadians(360 - angle));
        float sina = qSin(qDegreesToRadians(360 - angle));

        line.setP2(QPointF(distance * cosa, distance * sina));
    }

    float p2X = ((float)((int)(line.p2().x() * 100))) / 100;
    float p2Y = ((float)((int)(line.p2().y() * 100))) / 100;

    x->setText(QString::number(p2X));
    y->setText(QString::number(p2Y));
}

void ObjectDetector::UpdatePointPositionOnConveyor(float& x, float& y, float angle, float distance)
{
    QPointF point3;

    point3.setX(x);
    point3.setY(y);


    QLineF line;
    line.setP1(point3);
    line.setAngle(angle);

    if (distance == 0)
        return;

    line.setLength(distance);

    if (point3 == QPointF(0, 0))
    {
        float cosa = qCos(qDegreesToRadians(360 - angle));
        float sina = qSin(qDegreesToRadians(360 - angle));

        line.setP2(QPointF(distance * cosa, distance * sina));
    }

    float p2X = ((float)((int)(line.p2().x() * 100))) / 100;
    float p2Y = ((float)((int)(line.p2().y() * 100))) / 100;

    x = p2X;
    y = p2Y;
}

void ObjectDetector::drawXAxis(cv::Mat resultsMat)
{
	drawBlackWhiteLine(resultsMat, cv::Point(xAxis.p1().x(), xAxis.p1().y()), cv::Point(xAxis.p2().x(), xAxis.p2().y()), 1);
	drawBlackWhiteLine(resultsMat, cv::Point(arrow1.p1().x(), arrow1.p1().y()), cv::Point(arrow1.p2().x(), arrow1.p2().y()), 1);
	drawBlackWhiteLine(resultsMat, cv::Point(arrow2.p1().x(), arrow2.p1().y()), cv::Point(arrow2.p2().x(), arrow2.p2().y()), 1);
	
	if (axisDirection == X_AXIS_DOWN)
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() - 10, xAxis.p2().y() + 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() - 11, xAxis.p2().y() + 21), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else if (axisDirection == X_AXIS_RIGHT)
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 20, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 21, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else if (axisDirection == X_AXIS_LEFT)
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 20, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 21, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
	else
	{
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 10, xAxis.p2().y() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, BLACK_COLOR, 1);
		putText(resultsMat, "+x", cv::Point(xAxis.p2().x() + 11, xAxis.p2().y() + 11), cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE_COLOR, 1);
	}
}

void ObjectDetector::SelectProcessRegion(cv::Mat processMat)
{
	if (PperspectivePoints.size() == 0)
		return;
	
	cv::Mat filterMat(cv::Size(processMat.cols, processMat.rows), CV_8UC1, BLACK_COLOR);
	cv::rectangle(filterMat, PselectedRectangle, WHITE_COLOR, cv::FILLED);

	cv::bitwise_and(filterMat, processMat, processMat);
}

void ObjectDetector::transformPerspective(cv::Mat processMat, std::vector<cv::Point> points, cv::Mat & transMat)
{
	if (points.size() < 3)
		return;

	cv::Point2f outputQuad[4];
	cv::Point2f inputQuad[4];

	inputQuad[0] = points[0];
	inputQuad[1] = points[1];
	inputQuad[2] = points[2];
	inputQuad[3] = points[3];

	// ---------Find new position-------------------
	cv::Point2f center;
	center.x = (points[0].x + points[1].x + points[2].x + points[3].x)/4;
	center.y = (points[0].y + points[1].y + points[2].y + points[3].y) / 4;

	int maxLength = 0;
	
	for (int i = 0; i < 4; i++)
	{
		QLineF line;
		line.setP1(QPoint(inputQuad[i].x, inputQuad[i].y));
		if (i == 3)
		{
			line.setP2(QPoint(inputQuad[0].x, inputQuad[0].y));
		}
		else
		{
			line.setP2(QPoint(inputQuad[i + 1].x, inputQuad[i + 1].y));
		}		

		int len = line.length();

		if (len > maxLength)
		{
			maxLength = len;
		}
	}

	int halfLen = maxLength / 2;

	outputQuad[0] = center + cv::Point2f(-halfLen, -halfLen);
	outputQuad[1] = center + cv::Point2f(-halfLen, halfLen);
	outputQuad[2] = center + cv::Point2f(halfLen, halfLen);
	outputQuad[3] = center + cv::Point2f(halfLen, -halfLen);

	cv:: Mat lambda = cv::Mat::zeros(processMat.rows, processMat.cols, processMat.type());

	lambda = cv::getPerspectiveTransform(inputQuad, outputQuad);

    warpPerspective(processMat, transMat, lambda, transMat.size(), cv::INTER_NEAREST);
}

void ObjectDetector::MakeBrightProcessRegion(cv::Mat resultsMat)
{
	if (PperspectivePoints.size() == 0)
		return;

	int darkValue = 60;

	cv::Mat filterMat(cv::Size(resultsMat.cols, resultsMat.rows), CV_8UC1, BLACK_COLOR);

	cv::Rect cvRec;
	cvRec.x = DselectedRec.x();
	cvRec.y = DselectedRec.y();
	cvRec.width = DselectedRec.width();
	cvRec.height = DselectedRec.height();

	cv::rectangle(filterMat, cvRec, WHITE_COLOR, cv::FILLED);

	for (int y = 0; y < resultsMat.rows; y++) 
	{
		for (int x = 0; x < resultsMat.cols; x++) 
		{
			for (int c = 0; c < resultsMat.channels(); c++) 
			{
				int vl = resultsMat.at<cv::Vec3b>(y, x)[c] - darkValue;

				if (vl < 0)
					vl = 0;

				if (filterMat.at<uchar>(y, x) == 0)
				{
					resultsMat.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(vl);
				}
				
			}
		}
	}
}

void ObjectDetector::postProcessing()
{
    if (filterMethod == HSV_SPACE)
    {
        SetHSV(HSVValue[0], HSVValue[1], HSVValue[2], HSVValue[3], HSVValue[4], HSVValue[5]);
    }

    if (filterMethod == THRESHOLD_SPACE)
    {
        SetThreshold(thresholdValue);
    }

	// Invert binary image
	if (ParameterPanel->IsInvertBinary())
        cv::bitwise_not(filterMat, filterMat);

    SelectProcessRegion(filterMat);
}

void ObjectDetector::detectBlobObjects(cv::Mat input)
{	
	//Find contour in image
	std::vector<std::vector<cv::Point> > contoursContainer;
    findContours(input, contoursContainer, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    //qDebug() << "contour: " << ElapsedTimer.elapsed();

//	std::vector<std::vector<cv::Point> >hullsContainer(contoursContainer.size());

//	for (size_t i = 0; i < contoursContainer.size(); i++)
//	{
//		convexHull(contoursContainer[i], hullsContainer[i]);
//	}

	//Calculate size of contours

	int visibleCounter = 0;

	for (size_t i = 0; i < contoursContainer.size(); i++)
	{
		
        cv::RotatedRect object = cv::minAreaRect(cv::Mat(contoursContainer[i]));

        float h = object.size.height;
        float w = object.size.width;
		float s = w * h;

		if (w > h)
		{
			float t = h;
			h = w;
			w = t;
		}

		float obHei = PobjectRec.height;
		float obWid = PobjectRec.width;

		if (obWid > obHei)
		{
			float t = obHei;
			obHei = obWid;
			obWid = t;
		}

		//Find an object of equal size

        if (s > minObjectArea && s < maxObjectArea && h < obHei && w < obWid && object.boundingRect().y > 0 && (object.boundingRect().y + object.boundingRect().height + 5) < input.rows)
        {
            int angle = object.angle + 180;

            if (object.size.width > object.size.height)
            {
                angle = object.angle + 90;
            }

            object.angle = angle;

            DisplayObjects->append(object);

			visibleCounter += 1;
		}
	}

    ObjectManager->VisibleObjectNumber = visibleCounter;
}

void ObjectDetector::detectCircleObjects(cv::Mat input)
{
    cv::Mat gray;
    cv::cvtColor(input, gray, CV_BGR2GRAY);
    cv::Mat img_blur;
    medianBlur(gray, img_blur, 5);

    int radius = PobjectRec.width;
    int minRaius = radius * 0.7;
    int maxRaius = radius * 1.7;

    // Apply Hough Transform
    HoughCircles(img_blur, CircleObjects, cv::HOUGH_GRADIENT, 1, calibImage.rows/64, 200, 10, minRaius, maxRaius);
}

void ObjectDetector::sendImageToExternalScript(cv::Mat input)
{
    if (PythonTcpClient == NULL)
        return;

    int paras[3];
    paras[0] = input.cols;
    paras[1] = input.rows;
    paras[2] = input.channels();

    int len = 3 * sizeof(int);

    PythonTcpClient->write((char*)paras, len);

    char* pos = (char*)input.data;

    int colByte = input.cols*input.channels() * sizeof(uchar);
    for (int i = 0; i < input.rows; i++)
    {
        char* data = (char*)input.ptr<uchar>(i); //first address of the i-th line
        int sedNum = 0;
        char buf[1024] = { 0 };

        while (sedNum < colByte)
        {
            int sed = (1024 < colByte - sedNum) ? 1024 : (colByte - sedNum);
            memcpy(buf, &data[sedNum], sed);
            int SendSize = PythonTcpClient->write(buf, sed);

            if (SendSize == -1)
                return;
            sedNum += SendSize;
        }
    }
}

void ObjectDetector::drawRotateRec(cv::Mat& mat, int angle, cv::Rect rec, cv::Scalar color)
{
	cv::RotatedRect rRect = cv::RotatedRect(cv::Point2f(rec.x + rec.width / 2, rec.y + rec.height / 2), cv::Size2f(rec.width, rec.height), 30);
	cv::Point2f vertices[4];
	rRect.points(vertices);
	for (int i = 0; i < 4; i++)
		line(mat, vertices[i], vertices[(i + 1) % 4], color, 1);
}

float ObjectDetector::processDetectingObjectOnCamera(cv::Mat& mat, QList<cv::RotatedRect> objects, cv::Scalar color)
{
    if (rbCircleFilter->isChecked())
    {
        // Draw detected circles
        for(size_t i=0; i < CircleObjects.size(); i++)
        {
            cv::Point center(cvRound(CircleObjects[i][0]), cvRound(CircleObjects[i][1]));
            int radius = cvRound(CircleObjects[i][2]);
            circle(mat, center, radius, cv::Scalar(255, 255, 255), 2, 8, 0);
        }
    }

    else
    {
        foreach(cv::RotatedRect object, objects)
        {
            cv::Point2f rectPoints[4];
            object.points(rectPoints);

            for (int i = 0; i < 4; i++)
            {
                if (rectPoints[i].x < 0)
                {
                    rectPoints[i].x = 0;
                }
                if (rectPoints[i].y < 0)
                {
                    rectPoints[i].y = 0;
                }
            }




            int xRealObject = 0;
            int yRealObject = 0;

            QPoint PPoint(object.center.x, 0 - object.center.y);
            QPoint RPoint = P2RMatrix.map(PPoint);

            xRealObject = RPoint.x();
            yRealObject = RPoint.y();

            cv::RotatedRect realObject = object;

            realObject.center.x = xRealObject;
            realObject.center.y = yRealObject;
            realObject.size.height = object.size.height * PnRRatio;
            realObject.size.width = object.size.width * PnRRatio;
            realObject.angle = object.angle;

            float delta = EncoderPosition - EncoderPositionAtCameraCapture;

            UpdatePointPositionOnConveyor(realObject.center.x, realObject.center.y, DeviationAngle, delta);

            // Add object to object list if it is new object
            ObjectManager->AddNewObject(realObject);
            // Add object info to screen
            // Draw a rectangle outside the object
            if (mat.data)
            {
                for (int j = 0; j < 4; j++)
                    cv::line(mat, rectPoints[j], rectPoints[(j + 1) % 4], color, 2, 8);

                putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)realObject.angle), cv::Point(object.center.x - 40, object.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.4, BLACK_COLOR, 2);
                putText(mat, std::to_string((int)xRealObject) + "," + std::to_string((int)yRealObject) + "," + std::to_string((int)realObject.angle), cv::Point(object.center.x - 40, object.center.y), cv::FONT_HERSHEY_SIMPLEX, 0.4, WHITE_COLOR, 1);


            }
        }
    }
    return 0;
}

void ObjectDetector::UpdateRatios(float w, float h)
{
    DnPRatio = (float)cameraWidget->height() / h;
    CameraRatio = w / h;

    D2PMatrix.setMatrix(DnPRatio, 0, 0, DnPRatio, 0, 0);
}

void ObjectDetector::UpdateRatios()
{
    if (captureImage.empty())
        return;

    UpdateRatios(captureImage.cols, captureImage.rows);
}

void ObjectDetector::CalculateMappingMatrix()
{
    float x1 = leImagePoint1X->text().toFloat();
    float y1 = 0 - leImagePoint1Y->text().toFloat();
    float x2 = leImagePoint2X->text().toFloat();
    float y2 = 0 - leImagePoint2Y->text().toFloat();

    float xx1 = leRealityPoint1X->text().toFloat();
    float yy1 = leRealityPoint1Y->text().toFloat();
    float xx2 = leRealityPoint2X->text().toFloat();
    float yy2 = leRealityPoint2Y->text().toFloat();

    float a1 = x2 - x1;
    float b1 = y2 - y1;
    float a2 = xx2 -xx1;
    float b2 = yy2 - yy1;

    float n1n2 = a1 * a2 + b1 * b2;
    float _n1 = qSqrt(qPow(a1, 2) + qPow(b1, 2));
    float _n2 = qSqrt(qPow(a2, 2) + qPow(b2, 2));
    float ratio = PnRRatio = _n2/_n1;

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

    if (cbScaleRotateToolEnable->isChecked() == true)
    {
        float imageLine = leImageLine->text().toFloat();
        float realLine = leRealityLine->text().toFloat();
        ratio = PnRRatio = realLine / imageLine;

        float angle = leXAxisAngle->text().toFloat();
        theta = angle * (M_PI / 180);
    }
    else
    {
        leImageLine->setText(QString::number(_n1));
        leRealityLine->setText(QString::number(_n2));

        float angle = 0 - theta * (180 / M_PI);
        leXAxisAngle->setText(QString::number(angle));

        cameraWidget->ChangeXDirection(angle);
    }

    QMatrix RotateMatrix(qCos(theta), qSin(theta), -qSin(theta), qCos(theta), 0, 0);
    //QMatrix RotateMatrix(cosTheta, -sinTheta, sinTheta, cosTheta, 0, 0);
    QMatrix ScaleMatrix(ratio, 0, 0, ratio, 0, 0);

    QMatrix ScaleRotateMatrix = ScaleMatrix * RotateMatrix;

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float dx = xx1 - (ScaleRotateMatrix.m11() * x1 + ScaleRotateMatrix.m21() * y1);
    float dy = yy1 - (ScaleRotateMatrix.m12() * x1 + ScaleRotateMatrix.m22() * y1);

    P2RMatrix.setMatrix(ScaleRotateMatrix.m11(), ScaleRotateMatrix.m12(), ScaleRotateMatrix.m21(), ScaleRotateMatrix.m22(), dx, dy);

}

void ObjectDetector::UpdateTrackingInfo()
{
	lbTrackingObjectNumber->setText(QString::number(ObjectManager->ObjectContainer.size()));
    lbVisibleObjectNumber->setText(QString::number(ObjectManager->VisibleObjectNumber));
}

void ObjectDetector::UpdateDetectingResultToWidgets()
{
    if (cameraLayer == ORIGIN)
    {
        VideoDisplayThread->UpdateLabelImage(calibImage, cameraWidget, 0);
    }
    else if (cameraLayer == PROCESSING)
    {
        VideoDisplayThread->UpdateLabelImage(filterMat, cameraWidget, 0);
    }
    else if (cameraLayer == RESULT)
    {
        DisplayAdditionalInfo(resultImage);

        VideoDisplayThread->UpdateLabelImage(resultImage, cameraWidget, 0);
    }

    if (ParameterPanel->isHidden() == false)
    {
        VideoDisplayThread->UpdateLabelImage(filterMat, ParameterPanel->lbProcessImage, 1);
        VideoDisplayThread->UpdateLabelImage(calibImage, ParameterPanel->lbOriginImage, 2);
    }
}

void ObjectDetector::DisplayAdditionalInfo(cv::Mat & displayMat)
{
    float scale = DnPRatio * 100;

    lbScale->setText(QString("%1%").arg(scale));
    lbImageSize->setText(QString("%1x%2").arg(displayMat.cols).arg(displayMat.rows));
}

void ObjectDetector::drawBlackWhiteLine(cv::Mat& displayMat, cv::Point p1, cv::Point p2, int thin = 1)
{
	cv::line(displayMat, p1, p2, BLACK_COLOR, thin);
	cv::line(displayMat, cv::Point(p1.x + 1, p1.y + 1), cv::Point(p2.x + 1, p2.y + 1), WHITE_COLOR, thin);
}

void ObjectDetector::drawBlackWhiteLine(cv::Mat & displayMat, QLine line, int thin)
{
	cv::Point p1 = cv::Point(line.x1(), line.y1());
	cv::Point p2 = cv::Point(line.x2(), line.y2());

	drawBlackWhiteLine(displayMat, p1, p2, thin);
}

void ObjectDetector::drawBlackWhiteLines(cv::Mat& displayMat, std::vector<cv::Point> points, int thin = 1)
{
	cv::polylines(displayMat, points, true, BLACK_COLOR, thin);
	cv::polylines(displayMat, points, true, WHITE_COLOR, thin);
}

void ObjectDetector::drawBlackWhiteRect(cv::Mat & displayMat, cv::Point p, cv::Size size)
{
	cv::rectangle(displayMat, cv::Rect(p, size), BLACK_COLOR, 1);
	cv::rectangle(displayMat, cv::Rect(cv::Point(p.x + 1, p.y + 1), size), WHITE_COLOR, 1);
}

void ObjectDetector::drawBlackWhiteRect(cv::Mat & displayMat, QRect rect)
{
	cv::Point pos = cv::Point(rect.x(), rect.y());
	cv::Point pos2 = cv::Point(rect.x() - 1, rect.y() - 1);
	cv::Size size = cv::Size(rect.size().width(), rect.size().height());
	cv::Size size2 = cv::Size(rect.size().width() + 2, rect.size().height() + 2);

	cv::rectangle(displayMat, cv::Rect(pos, size), BLACK_COLOR, 1);
	cv::rectangle(displayMat, cv::Rect(pos2, size2), WHITE_COLOR, 1);
}

void ObjectDetector::drawLine(cv::Mat & displayMat, QPoint p1, QPoint p2)
{
	cv::Point cvPoint1 = cv::Point(p1.x(), p1.y());
	cv::Point cvPoint2 = cv::Point(p2.x(), p2.y());
	drawBlackWhiteLine(displayMat, cvPoint1, cvPoint2, 1);
}

void ObjectDetector::drawCorner(cv::Mat & displayMat, QPoint p)
{
	cv::Point RectcvPoint1 = cv::Point(p.x() - 4, p.y() - 4);

    drawBlackWhiteRect(displayMat, RectcvPoint1, cv::Size(10, 10));
}

void ObjectDetector::updatePerspectivePointsToUI()
{
    leChessboardPoints[0][0]->setText(QString::number(PperspectivePoints[0].x));
    leChessboardPoints[0][1]->setText(QString::number(PperspectivePoints[0].y));
    leChessboardPoints[1][0]->setText(QString::number(PperspectivePoints[1].x));
    leChessboardPoints[1][1]->setText(QString::number(PperspectivePoints[1].y));
    leChessboardPoints[2][0]->setText(QString::number(PperspectivePoints[2].x));
    leChessboardPoints[2][1]->setText(QString::number(PperspectivePoints[2].y));
    leChessboardPoints[3][0]->setText(QString::number(PperspectivePoints[3].x));
    leChessboardPoints[3][1]->setText(QString::number(PperspectivePoints[3].y));

}
