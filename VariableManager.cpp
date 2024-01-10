#include "VariableManager.h"

VariableManager &VariableManager::instance()
{
    static VariableManager _instance;
    return _instance;
}

void VariableManager::addItemModel(QStandardItemModel *model)
{
    model->setHorizontalHeaderLabels(QStringList() << "Name" << "Value");
    connect(&instance(), SIGNAL(varUpdated(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));
    connect(&instance(), SIGNAL(varAdded(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));
    itemModelList.append(model);
}

void VariableManager::addVar(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(fullKey, value);
}

void VariableManager::setVariable(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(fullKey, value);
}

void VariableManager::updateVar(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varUpdated(fullKey, value);
}

QVariant VariableManager::getVariable(const QString &key, QVariant defaultValue)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    if(dataMap.find(fullKey) != dataMap.end())
    {
        return dataMap[fullKey];
    }
    return defaultValue;
}

QVariant VariableManager::getVar(const QString &key, QVariant defaultValue)
{
    return getVariable(key);
}

void VariableManager::removeVar(const QString &key)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap.remove(fullKey);
    emit varRemoved(fullKey);
}

bool VariableManager::contains(const QString &key)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    return (dataMap.find(fullKey) != dataMap.end());
}

void VariableManager::saveToQSettings()
{
    std::lock_guard<std::mutex> lock(dataMutex);
//    for(const auto& kv : dataMap)
//    {
//        settings.setValue(kv.first, kv.second);
//    }

    foreach (const QString &key, dataMap.keys())
    {
        settings.setValue(key, dataMap[key]);
    }
}

void VariableManager::loadFromQSettings()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    QStringList keys = settings.allKeys();
    for(const QString& key : keys)
    {
        dataMap[key] = settings.value(key);
        emit varAdded(key, settings.value(key));
    }
}

QSettings *VariableManager::getSettings()
{
    saveToQSettings();
    return &settings;
}

void VariableManager::UpdateVarToModel(QString key, QVariant value)
{
    for (QStandardItemModel* model : itemModelList)
    {
        QStandardItem *parent = model->invisibleRootItem();
        UnityTool::UpdateVarToModel(parent, key, value);
    }

//    QString valueString = value.toString();
//    if (value.canConvert<QVector3D>())
//    {
//        QVector3D vector = value.value<QVector3D>();
//        valueString = QString("(%1, %2, %3)")
//                .arg(vector.x())
//                .arg(vector.y())
//                .arg(vector.z());
//    }
//    else if (value.canConvert<QPointF>())
//    {
//        QPointF point = value.value<QPointF>();
//        valueString = QString("(%1, %2)")
//                .arg(point.x())
//                .arg(point.y());
//    }

//    else if (value.canConvert<QPolygonF>())
//    {
//        QPolygonF poly = value.value<QPolygonF>();
//        valueString = "";
//        for (const QPointF &point : poly) {
//            valueString += QString("(%1, %2)")
//                    .arg(point.x())
//                    .arg(point.y());
//        }
//    }

//    for (QStandardItemModel* model : itemModelList)
//    {
//        QStandardItem *parent = model->invisibleRootItem();
//        QStringList parts = key.split('.');

//        for (int i = 0; i < parts.count() - 1; ++i) {
//            QString part = parts[i];
//            QStandardItem *child = nullptr;
//            for (int j = 0; j < parent->rowCount(); ++j) {
//                if (parent->child(j)->text() == part) {
//                    child = parent->child(j);
//                    break;
//                }
//            }
//            if (!child) {
//                child = new QStandardItem(part);
//                parent->appendRow(child);
//            }
//            parent = child;
//        }
//        bool found = false;
//        for (int i = 0; i < parent->rowCount(); ++i) {
//            if (parent->child(i)->text() == parts.last()) {

//                parent->child(i, 1)->setText(valueString);
//                found = true;
//                break;
//            }
//        }
//        if (!found) {
//            parent->appendRow(QList<QStandardItem*>() << new QStandardItem(parts.last()) << new QStandardItem(valueString));
//        }
//    }
}

const QString VariableManager::getFullKey(const QString key)
{
    QString fullKey = key;
    if (Prefix != "")
    {
        fullKey = Prefix + "." + key;
    }

    fullKey.replace("#", "");

    return fullKey;
}
