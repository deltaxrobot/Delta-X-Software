#ifndef OBJECTINFOMODEL_H
#define OBJECTINFOMODEL_H

#include <QAbstractTableModel>
#include <QVector3D>
#include <QVector>
#include <ObjectInfo.h>

class ObjectInfoModel : public QAbstractTableModel {
    Q_OBJECT

public:
    ObjectInfoModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    void setObjectInfoList(const QVector<ObjectInfo> &objectInfos) {
        beginResetModel();
        this->objectInfos = objectInfos;
        endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return objectInfos.count();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        // Có 10 cột: id, type, X, Y, Z, width, height, angle, isPicked, offset
        return 10;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        const ObjectInfo &info = objectInfos.at(index.row());

        switch (index.column()) {
            case 0: return info.id;
            case 1: return info.type;
            case 2: return info.center.x();
            case 3: return info.center.y();
            case 4: return info.center.z();
            case 5: return info.width;
            case 6: return info.height;
            case 7: return info.angle;
            case 8: return info.isPicked;
            case 9: return QString("%1, %2").arg(info.offset.x()).arg(info.offset.y());
            default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
            return QVariant();

        switch (section) {
            case 0: return QStringLiteral("ID");
            case 1: return QStringLiteral("TYPE");
            case 2: return QStringLiteral("X");
            case 3: return QStringLiteral("Y");
            case 4: return QStringLiteral("Z");
            case 5: return QStringLiteral("Width");
            case 6: return QStringLiteral("Height");
            case 7: return QStringLiteral("Angle");
            case 8: return QStringLiteral("Is Picked");
            case 9: return QStringLiteral("Offset");
            default: return QVariant();
        }
    }

private:
    QVector<ObjectInfo> objectInfos;
};


#endif // OBJECTINFOMODEL_H
