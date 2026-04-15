#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QWidget>
#include <QMap>

class Global: public QObject
{
    Q_OBJECT
public:
    Global();
    static Global& getInstance();

    QMap<QString, QString> values;
};

#endif // GLOBAL_H
