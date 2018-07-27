#include <UnityTool.h>

QLabel* DebugLB;

void Debug(QString msg)
{
	DebugLB->setText(msg);
}