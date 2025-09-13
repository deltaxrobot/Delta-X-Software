#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include <QVector3D>
#include <QMetaType>

class ObjectInfo {
public:
    int id;
    int type;
    QVector3D center;  // X, Y, Z position
    double width;
    double height;
    double angle;
    bool isPicked;  // Indicates if the object has been picked
    QVector3D offset;

    // Default constructor required for Qt metatype system when used in containers
    ObjectInfo()
        : id(0), type(0), center(QVector3D(0,0,0)), width(0.0), height(0.0), angle(0.0), isPicked(false), offset(QVector3D(0,0,0)) {}

    ObjectInfo(int id, int type, QVector3D center, double width, double height, double angle, bool isPicked=false, QVector3D offset=QVector3D(0,0,0))
        : id(id), type(type), center(center), width(width), height(height), angle(angle), isPicked(isPicked), offset(offset) {}
};

#ifndef Q_MOC_RUN
Q_DECLARE_METATYPE(ObjectInfo)
#endif

#endif // OBJECTINFO_H
