#include "DeltaVisualizer.h"

DeltaVisualizer::DeltaVisualizer(QWidget *parent) :QLabel(parent)
{
	setMouseTracking(true);
    lbParent = (QLabel*)parent;
}

DeltaVisualizer::~DeltaVisualizer()
{
	
}

void DeltaVisualizer::InitGrid()
{

}

void DeltaVisualizer::MoveToHome()
{
    emit Moved(XHome, YHome, ZHome, WHome, UHome, VHome);
	emit FinishMoving();
}

QSize DeltaVisualizer::minimumSizeHint()
{
	return QSize(50, 50);
}

QSize DeltaVisualizer::sizeHint()
{
	return QSize(400, 400);
}

void DeltaVisualizer::SetDivisionComboBox(QComboBox* division)
{
	cbDivision = division;
}

void DeltaVisualizer::ChangeXY(float x, float y)
{
    QPixmap pi = QPixmap(width(), height());
	pi.fill(QColor(0, 0, 0, 0));

    QPixmap pix = QPixmap(QString::fromUtf8(":/icon/moving-base.png"));

//    QPixmap pix1 = QPixmap(QString::fromUtf8(":/icon/grid-10-pixel-3.png"));
//    QPixmap pix2 = QPixmap(QString::fromUtf8(":/icon/grid-axis-2.png"));

	QPainter p(&pi);
    p.setPen(QPen(Qt::blue, 1));

//    p.drawPixmap(0, 0, width(), height(), pix1);
//    p.drawPixmap(0, 0, width(), height(), pix2);
//    for (int i = 0; i <= width(); i+=10)
//    {
//        p.drawLine(QPoint(i, 0), QPoint(i, height()));
//    }

//    for (int i = 0; i <= height(); i+=10)
//    {
//        p.drawLine(QPoint(0, i), QPoint(width(), i));
//    }

    p.drawLine(QPoint(width() / 2, 0), QPoint(width() / 2, height() - 1));
    p.drawLine(QPoint(0, height() / 2), QPoint(width() - 1, height() / 2));
    p.drawLine(QPoint(0, 0), QPoint(width() - 1, 0));
    p.drawLine(QPoint(width() - 1, 0), QPoint(width() - 1, height() - 1));
    p.drawLine(QPoint(width() - 1, height() - 1), QPoint(0, height() - 1));
    p.drawLine(QPoint(0, height() - 1), QPoint(0, 0));

    p.drawPixmap(width() / 2 + x - MOVING_BASE_SIZE / 2, height() / 2 - MOVING_BASE_SIZE / 2 - y, MOVING_BASE_SIZE, MOVING_BASE_SIZE, pix);
    p.drawText(QPoint(width() / 2 + x + MOVING_BASE_SIZE / 2, height() / 2 - y), QString("X:%1, Y:%2").arg(QString::number(X), QString::number(Y)));
    p.drawEllipse(QPoint(width() / 2 + X, height() / 2 - Y), 5, 5);
    p.drawEllipse(QPoint(width() / 2 + X, height() / 2 - Y), 1, 1);

    setPixmap(pi);
    setScaledContents(true);
	
    update();

	X = x;
	Y = y;
}

void DeltaVisualizer::mousePressEvent(QMouseEvent *event)
{
	int x = event->pos().x() - width() / 2;
	int y = -event->pos().y() + height() / 2;

	ChangeXY(x, y);

    emit Moved(X, Y, Z, W, U, V);
}

void DeltaVisualizer::mouseReleaseEvent(QMouseEvent *event)
{
	emit FinishMoving();
    emit CursorMoved(X, Y);
}

void DeltaVisualizer::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x() - width() / 2;
    int y = -event->pos().y() + height() / 2;

    //emit CursorMoved(x, y);

    if (event->buttons() & Qt::LeftButton)
    {
        ChangeXY(x, y);

        emit Moved(X, Y, Z, W, U, V);
    }
}

void DeltaVisualizer::wheelEvent(QWheelEvent *e)
{
	int n = 1;

	if (timer.isValid() == false)
	{
		timer.start();
	}
	else
	{
		n = 200 - timer.elapsed();

		if (n < 0)
		{
			n = 1;
		}

		n = log2(n) + 1;		
	}

	int delta = e->delta();
	
	Z -= (delta / abs(delta)) * n;

	if (Z > ZHome)
	{
		Z = ZHome;
	}

    emit Moved(X, Y, Z, W, U, V);
	emit FinishMoving();

	if (timer.elapsed() < 30)
		return;

	timer.restart();
}

bool DeltaVisualizer::eventFilter(QObject *dist, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		float division = cbDivision->currentText().toFloat();

		if (QString("1234567890").indexOf(keyEvent->text()) == -1) 
			return true;

		else if (keyEvent->key() == Qt::Key_Up) 
		{ 
			emit up_arrow();
			Y += division;
		}
		else if (keyEvent->key() == Qt::Key_Down) 
		{ 
			emit down_arrow(); 
			Y -= division;
		}
		else if (keyEvent->key() == Qt::Key_Left) 
		{ 
			emit left_arrow(); 
			X += division;
		}
		else if (keyEvent->key() == Qt::Key_Right) 
		{ 
			emit right_arrow(); 
			X -= division;
		}

        emit Moved(X, Y, Z, W, U, V);
		emit FinishMoving();
		return true;
	}

    return false;
}

void DeltaVisualizer::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    const QPixmap* curPix = this->pixmap();

    if (curPix == NULL)
        return;

    QPixmap mPix = *curPix;

    QPainter painter;

    painter.begin(this);

    QPainter tempPainter(&mPix);

    //------ Display cursor position -----------

    tempPainter.setPen(QPen(Qt::red, 1));

    QPoint curPosInWidget = mapFromGlobal(QCursor::pos());

    if (curPosInWidget.x() > 0)
    {
        int workingX = curPosInWidget.x() - width() / 2;
        int workingY = - curPosInWidget.y() + height() / 2;
        tempPainter.drawText(curPosInWidget.x() + 10, curPosInWidget.y() - 10, QString("(%1, %2)").arg(QString::number(workingX), QString::number(workingY)));
    }
    //

    painter.drawPixmap(0, 0, mPix);

    painter.end();

    update();
}

void DeltaVisualizer::setWorkingSize(int width)
{
    int fixSize = width;

    if (fixSize > lbParent->width())
        fixSize = lbParent->width();

    lbParent->setMinimumHeight(fixSize);
    setGeometry(QRect(0, 0, fixSize, fixSize));

    ChangeXY(X, Y);
}

void DeltaVisualizer::JumpOneStep(float *axis, float step)
{
    float division = cbDivision->currentText().toFloat();
    *axis += (division * step);

    emit Moved(X, Y, Z, W, U, V);
    emit FinishMoving();
}

void DeltaVisualizer::MoveUp()
{
    JumpOneStep(&Z, 1);
}

void DeltaVisualizer::MoveDown()
{
    JumpOneStep(&Z, -1);
}

void DeltaVisualizer::MoveForward()
{
    JumpOneStep(&Y, 1);
}

void DeltaVisualizer::MoveBackward()
{
    JumpOneStep(&Y, -1);
}

void DeltaVisualizer::MoveLeft()
{
    JumpOneStep(&X, -1);
}

void DeltaVisualizer::MoveRight()
{
    JumpOneStep(&X, 1);
}

void DeltaVisualizer::SubW()
{
    JumpOneStep(&W, -1);
}

void DeltaVisualizer::SubU()
{
    JumpOneStep(&U, -1);
}

void DeltaVisualizer::SubV()
{
    JumpOneStep(&V, -1);
}

void DeltaVisualizer::PlusW()
{
    JumpOneStep(&W, 1);
}

void DeltaVisualizer::PlusU()
{
    JumpOneStep(&U, 1);
}

void DeltaVisualizer::PlusV()
{
    JumpOneStep(&V, 1);
}

void DeltaVisualizer::ChangeWorkingSize(int option)
{
    switch (option) {
    case 0: setWorkingSize(300); break;
    case 1: setWorkingSize(400); break;
    case 2: setWorkingSize(600); break;
    case 3: setWorkingSize(800); break;

    }
}
