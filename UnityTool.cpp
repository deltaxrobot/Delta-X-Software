#include <UnityTool.h>

QLabel* DebugLB;

QString ConvenyorString;

void Debug(QString msg)
{
	DebugLB->setText(msg);
}