#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include <QVector3D>
#include <QMetaType>
#include <QString>
#include <QtGlobal>

class ObjectInfo {
public:
    int uid;
    int type;
    QVector3D center;  // X, Y, Z position
    double width;
    double height;
    double angle;
    double confidence;       // Detector confidence in [0, 1]
    QString label;           // Optional human-readable class name
    QString externalId;      // Optional detector-side identifier for diagnostics
    bool isPicked;  // Indicates if the object has been picked
    QVector3D offset;
    QString claimOwner;      // Worker/robot that currently owns this object
    qint64 claimExpiresAtMs; // UTC epoch milliseconds; 0 means not claimed
    qint64 claimExpiresAtMonotonicMs; // Internal monotonic deadline

    // Track lifecycle. New detector tracks must be observed repeatedly before
    // robots can claim them. Missing observations are retained briefly so a
    // single dropped frame does not change the UID.
    bool confirmed;
    int hitCount;
    int missedFrames;
    qint64 lastSeenAtMs;
    int candidateType;
    int candidateTypeHits;

    // Default constructor required for Qt metatype system when used in containers
    ObjectInfo()
        : uid(0), type(0), center(QVector3D(0,0,0)), width(0.0), height(0.0),
          angle(0.0), confidence(1.0), isPicked(false), offset(QVector3D(0,0,0)),
          claimExpiresAtMs(0), claimExpiresAtMonotonicMs(0), confirmed(false),
          hitCount(1), missedFrames(0), lastSeenAtMs(0), candidateType(-1),
          candidateTypeHits(0) {}

    ObjectInfo(int id, int type, QVector3D center, double width, double height, double angle,
               bool isPicked=false, QVector3D offset=QVector3D(0,0,0),
               QString claimOwner=QString(), qint64 claimExpiresAtMs=0,
               double confidence=1.0, QString label=QString(),
               QString externalId=QString())
        : uid(id), type(type), center(center), width(width), height(height), angle(angle),
          confidence(confidence), label(label), externalId(externalId),
          isPicked(isPicked), offset(offset), claimOwner(claimOwner),
          claimExpiresAtMs(claimExpiresAtMs), claimExpiresAtMonotonicMs(0),
          confirmed(false), hitCount(1), missedFrames(0), lastSeenAtMs(0),
          candidateType(-1), candidateTypeHits(0) {}
};

#ifndef Q_MOC_RUN
Q_DECLARE_METATYPE(ObjectInfo)
#endif

#endif // OBJECTINFO_H
