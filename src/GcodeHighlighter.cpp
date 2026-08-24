#include "GcodeHighlighter.h"


GCodeHighlighter::GCodeHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    QTextCharFormat gcodeFormat;
    gcodeFormat.setForeground(QColor("#DBDBDC"));

//    gcodeFormat.setBackground(Qt::yellow);
    gcodeFormat.setFontWeight(QFont::Bold);
    QRegularExpression gcodeRegex("[Gg]\\d{1,3}\\b");
    highlightRule rule = {gcodeRegex, gcodeFormat};
    highlightRules.append(rule);

    QTextCharFormat mcodeFormat;
    mcodeFormat.setForeground(QColor("#DBDBDC"));
    mcodeFormat.setFontWeight(QFont::Bold);
    QRegularExpression mcodeRegex("[Mm]\\d{1,3}\\b");
    rule = {mcodeRegex, mcodeFormat};
    highlightRules.append(rule);

    QTextCharFormat lineNumberFormat;
    lineNumberFormat.setForeground(QColor(Qt::gray));
    QRegularExpression numberRegex("^N\\d+");
    rule = {numberRegex, lineNumberFormat};
    highlightRules.append(rule);

    QTextCharFormat gotoFormat;
    gotoFormat.setForeground(QColor("#3195EF"));
    gotoFormat.setFontWeight(QFont::Bold);
    QRegularExpression gotoRegex("\\b(?:GOTO|JUMP|LABEL|SELECT|SYNC)\\b",
                                 QRegularExpression::CaseInsensitiveOption);
    rule = {gotoRegex, gotoFormat};
    highlightRules.append(rule);

    QTextCharFormat ifthenFormat;
    ifthenFormat.setForeground(QColor("#3195EF"));
    ifthenFormat.setFontWeight(QFont::Bold);
    QRegularExpression ifRegex("\\b(?:IF|THEN|ELIF|ELSE|ENDIF|FOR|ENDFOR|EACH|IN|TO|STEP|FUNCTION|ENDFUNCTION|RETURN|LOCAL)\\b",
                               QRegularExpression::CaseInsensitiveOption);
    rule = {ifRegex, ifthenFormat};
    highlightRules.append(rule);

    QTextCharFormat format;
    format.setFontItalic(true);
    format.setForeground(QColor("#d7a8ff"));
    QRegularExpression pattern("#[A-Za-z_][A-Za-z0-9_.]*");
    rule = {pattern, format};
    highlightRules.append(rule);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::darkGreen);
    commentFormat.setFontItalic(true);
    highlightRules.append({QRegularExpression(";.*"), commentFormat});

    QTextCharFormat stringFormat;
    stringFormat.setForeground(QColor("#ce9178"));
    highlightRules.append({QRegularExpression("\"(?:\\\\.|[^\"\\\\])*\"|'(?:\\\\.|[^'\\\\])*'"), stringFormat});

    QTextCharFormat trackingFormat;
    trackingFormat.setForeground(QColor("#4ec9b0"));
    trackingFormat.setFontWeight(QFont::DemiBold);
    highlightRules.append({QRegularExpression("\\bP(?:captureAndDetect|updateTracking|claimObject|releaseObject|completeObject|clearObjects)\\b",
                                              QRegularExpression::CaseInsensitiveOption), trackingFormat});
}

void GCodeHighlighter::highlightBlock(const QString &text)
{
    for (const highlightRule &rule : qAsConst(highlightRules)) {
        QRegularExpressionMatchIterator i = rule.pattern.globalMatch(text);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
