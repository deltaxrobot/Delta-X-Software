#ifndef QTMATRIXCOMPAT_H
#define QTMATRIXCOMPAT_H

#include <QtGlobal>
#include <QMetaType>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QTransform>
using QMatrix = QTransform;
#else
#include <QMatrix>
#endif

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
Q_DECLARE_METATYPE(QMatrix)
#endif

namespace QtMatrixCompat
{
inline void setMatrix2D(QMatrix &matrix,
                        qreal m11, qreal m12,
                        qreal m21, qreal m22,
                        qreal dx, qreal dy)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    // In QTransform (Qt6), translation terms are m31/m32, not m13/m23
    matrix.setMatrix(m11, m12, 0.0,
                     m21, m22, 0.0,
                     dx,  dy,  1.0);
#else
    matrix.setMatrix(m11, m12, m21, m22, dx, dy);
#endif
}
}

#endif // QTMATRIXCOMPAT_H
