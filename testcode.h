#ifndef TESTCODE_H
#define TESTCODE_H

#include <QObject>
#include <QDebug>
#include <QThread>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(QObject *parent = nullptr);

public slots:
    void run();

};


#endif // TESTCODE_H
