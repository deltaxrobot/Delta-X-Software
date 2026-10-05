#ifndef GSCRIPTANALYZER_H
#define GSCRIPTANALYZER_H

#include <QList>
#include <QMetaType>
#include <QString>
#include <QStringList>

struct GScriptDiagnostic
{
    enum Severity {
        Info = 0,
        Warning = 1,
        Error = 2
    };

    Severity severity = Info;
    QString code;
    int line = 1;
    int column = 1;
    QString message;
    QString hint;

    QString severityName() const;
};

Q_DECLARE_METATYPE(GScriptDiagnostic)
Q_DECLARE_METATYPE(QList<GScriptDiagnostic>)

struct GScriptAnalysisResult
{
    QList<GScriptDiagnostic> diagnostics;
    int executableLineCount = 0;
    int functionCount = 0;
    int labelCount = 0;

    bool hasErrors() const;
    int errorCount() const;
    int warningCount() const;
};

class GScriptAnalyzer final
{
public:
    static GScriptAnalysisResult analyze(const QString& source);
    static QStringList knownKeywords();

private:
    GScriptAnalyzer() = delete;
};

#endif // GSCRIPTANALYZER_H
