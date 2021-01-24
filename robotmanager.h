#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <QObject>

class RobotManager : public QObject
{
    Q_OBJECT
public:
    explicit RobotManager(QObject *parent = nullptr);

    RobotManager* getInstance();

private:
    RobotManager *instance = NULL;

signals:

};

#endif // ROBOTMANAGER_H
