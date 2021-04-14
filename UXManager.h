#ifndef UXMANAGER_H
#define UXMANAGER_H

#include <QWidget>
#include <QTabWidget>
#include <QMap>
#include <QLayout>
#include <QStackedWidget>

class UXManager : public QWidget
{
    Q_OBJECT
public:
    explicit UXManager(QWidget *parent = nullptr);

public slots:
signals:

private:
};

#endif // UXMANAGER_H
