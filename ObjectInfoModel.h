#ifndef OBJECTINFOMODEL_H
#define OBJECTINFOMODEL_H

#include <QAbstractTableModel>
#include <QVector3D>
#include <QList>
#include <ObjectInfo.h>

class ObjectInfoModel : public QAbstractTableModel {
    Q_OBJECT

public:
    ObjectInfoModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {}

    void setObjectInfoList(const QList<ObjectInfo> &objectInfos) {
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
        // Có 7 cột: id, X, Y, Z, width, height, angle, isPicked
        return 8;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        const ObjectInfo &info = objectInfos.at(index.row());

        switch (index.column()) {
            case 0: return info.id;
            case 1: return info.center.x();
            case 2: return info.center.y();
            case 3: return info.center.z();
            case 4: return info.width;
            case 5: return info.height;
            case 6: return info.angle;
            case 7: return info.isPicked;
            default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
            return QVariant();

        switch (section) {
            case 0: return QStringLiteral("ID");
            case 1: return QStringLiteral("X");
            case 2: return QStringLiteral("Y");
            case 3: return QStringLiteral("Z");
            case 4: return QStringLiteral("Width");
            case 5: return QStringLiteral("Height");
            case 6: return QStringLiteral("Angle");
            case 7: return QStringLiteral("Is Picked");
            default: return QVariant();
        }
    }

private:
    QList<ObjectInfo> objectInfos;
};


#endif // OBJECTINFOMODEL_H
