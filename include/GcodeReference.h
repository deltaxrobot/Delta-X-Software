#pragma once

#include <QWidget>
#include "ui_GcodeReference.h"

class GcodeReference : public QWidget
{
	Q_OBJECT

public:
	GcodeReference(QWidget *parent = Q_NULLPTR);
	~GcodeReference();

public slots:
	void SelectGcodeItem(QListWidgetItem *item);
	void SelectLineTextEdit();
private:
	Ui::GcodeReference ui;
};
