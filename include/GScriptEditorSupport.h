#ifndef GSCRIPTEDITORSUPPORT_H
#define GSCRIPTEDITORSUPPORT_H

#include <QString>
#include <QStringList>

struct GScriptRobotTemplateOptions
{
    int trackingId = 0;
    int robotId = 0;
    int typeFilter = -1;
    double minX = -180.0;
    double maxX = 180.0;
    double minY = 300.0;
    double maxY = 450.0;
    bool useVacuumFeedback = false;
    QString vacuumVariable = QStringLiteral("Vacuum.R0.OK");
};

class GScriptEditorSupport final
{
public:
    static QStringList builtInCompletions();
    static QString signatureHelp(const QString& line, int cursorColumn);
    static QStringList referencedVariables(const QString& source);
    static QString normalizeWatchName(const QString& name);
    static QString visionTemplate(int trackingId, int loopDelayMs = 10);
    static QString robotTemplate(const GScriptRobotTemplateOptions& options);

private:
    GScriptEditorSupport() = delete;
};

#endif // GSCRIPTEDITORSUPPORT_H
