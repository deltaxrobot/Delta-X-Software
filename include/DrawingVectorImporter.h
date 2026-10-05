#pragma once

#include "DrawingProgram.h"
#include <QByteArray>
#include <QSizeF>
#include <QStringList>

namespace DrawingVectorImporter {

struct Result {
    DrawingProgram::Paths paths;
    QSizeF sizeMm;
    QStringList warnings;
};

// Import native vector geometry. SVG paths are mapped from the document
// viewport to millimetres and centred on robot X/Y. ASCII DXF entities are
// converted using $INSUNITS and centred from their geometric bounds.
bool importFile(const QString& fileName, Result* result, QString* error);
bool importSvg(const QByteArray& data, Result* result, QString* error);
bool importDxf(const QByteArray& data, Result* result, QString* error);

} // namespace DrawingVectorImporter
