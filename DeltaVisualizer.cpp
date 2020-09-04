#include "DeltaVisualizer.h"

DeltaVisualizer::DeltaVisualizer(QWidget *parent) :QLabel(parent)
{
	setMouseTracking(true);
}

DeltaVisualizer::~DeltaVisualizer()
{
	
}

void DeltaVisualizer::InitGrid()
{
}

void DeltaVisualizer::MoveToHome()
{
	emit Moved(XHome, YHome, ZHome, WHome);
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

void DeltaVisualizer::ChangeXY(int x, int y)
{
	QPixmap pi = QPixmap(width(), height());
	pi.fill(QColor(0, 0, 0, 0));

	QPixmap pix = QPixmap(QString::fromUtf8("icon/moving-base.png"));

	QPixmap pix1 = QPixmap(QString::fromUtf8("icon/grid-10-pixel-3.png"));
	QPixmap pix2 = QPixmap(QString::fromUtf8("icon/grid-axis-2.png"));

	QPainter p(&pi);

	p.begin(this);

	p.drawPixmap(0, 0, width(), height(), pix1);
	p.drawPixmap(0, 0, width(), height(), pix2);
	p.drawPixmap(width() / 2 + x - MOVING_BASE_SIZE / 2, height() / 2 - MOVING_BASE_SIZE / 2 - y, MOVING_BASE_SIZE, MOVING_BASE_SIZE, pix);
	
	p.end();

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

	emit Moved(X, Y, Z, W);
}

void DeltaVisualizer::mouseReleaseEvent(QMouseEvent *event)
{
	emit FinishMoving();
}

void DeltaVisualizer::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x() - width() / 2;
	int y = -event->pos().y() + height() / 2;

	emit CursorMoved(x, y);

	if (event->buttons() & Qt::LeftButton) 
	{
		ChangeXY(x, y);

		emit Moved(X, Y, Z, W);
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

	emit Moved(X, Y, Z, W);
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

		emit Moved(X, Y, Z, W);
		emit FinishMoving();
		return true;
	}

	return false;
}

void DeltaVisualizer::MoveUp()
{
	float division = cbDivision->currentText().toFloat();
	Z += division;

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}

void DeltaVisualizer::MoveDown()
{
	float division = cbDivision->currentText().toFloat();
	Z -= division;

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}

void DeltaVisualizer::MoveForward()
{
	float division = cbDivision->currentText().toFloat();
	Y += division;

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}

void DeltaVisualizer::MoveBackward()
{
	float division = cbDivision->currentText().toFloat();
	Y -= division;

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}

void DeltaVisualizer::MoveLeft()
{
	float division = cbDivision->currentText().toFloat();
	X -= division;

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}

void DeltaVisualizer::MoveRight()
{
	float division = cbDivision->currentText().toFloat();
	X += division;

	emit Moved(X, Y, Z, W);
	emit FinishMoving();
}
