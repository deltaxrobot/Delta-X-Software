#include "GcodeHighlighter.h"
#include <QApplication>
#include <QPalette>


GCodeHighlighter::GCodeHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    refreshTheme();
    connect(qApp, &QGuiApplication::paletteChanged, this,
            [this](const QPalette&) { refreshTheme(); rehighlight(); });
}

void GCodeHighlighter::refreshTheme()
{
    highlightRules.clear();
    const QPalette palette = QApplication::palette();
    const bool dark = palette.color(QPalette::Base).lightness() < 128;
    const QColor keyword = dark ? QColor("#80C4FF") : QColor("#125E99");
    QTextCharFormat gcodeFormat;
    gcodeFormat.setForeground(palette.color(QPalette::Text));

//    gcodeFormat.setBackground(Qt::yellow);
    gcodeFormat.setFontWeight(QFont::Bold);
    QRegularExpression gcodeRegex("[Gg]\\d{1,3}\\b");
    highlightRule rule = {gcodeRegex, gcodeFormat};
    highlightRules.append(rule);

    QTextCharFormat mcodeFormat;
    mcodeFormat.setForeground(palette.color(QPalette::Text));
    mcodeFormat.setFontWeight(QFont::Bold);
    QRegularExpression mcodeRegex("[Mm]\\d{1,3}\\b");
    rule = {mcodeRegex, mcodeFormat};
    highlightRules.append(rule);

    QTextCharFormat lineNumberFormat;
    lineNumberFormat.setForeground(dark ? QColor("#A6B2BF") : QColor("#5D6976"));
    QRegularExpression numberRegex("^N\\d+");
    rule = {numberRegex, lineNumberFormat};
    highlightRules.append(rule);

    QTextCharFormat gotoFormat;
    gotoFormat.setForeground(keyword);
    gotoFormat.setFontWeight(QFont::Bold);
    QRegularExpression gotoRegex("\\b(?:GOTO|JUMP|LABEL|SELECT|SYNC)\\b",
                                 QRegularExpression::CaseInsensitiveOption);
    rule = {gotoRegex, gotoFormat};
    highlightRules.append(rule);

    QTextCharFormat ifthenFormat;
    ifthenFormat.setForeground(keyword);
    ifthenFormat.setFontWeight(QFont::Bold);
    QRegularExpression ifRegex("\\b(?:IF|THEN|ELIF|ELSE|ENDIF|FOR|ENDFOR|EACH|IN|TO|STEP|FUNCTION|ENDFUNCTION|RETURN|LOCAL)\\b",
                               QRegularExpression::CaseInsensitiveOption);
    rule = {ifRegex, ifthenFormat};
    highlightRules.append(rule);

    QTextCharFormat format;
    format.setFontItalic(true);
    format.setForeground(dark ? QColor("#D7A8FF") : QColor("#7435A8"));
    QRegularExpression pattern("#[A-Za-z_][A-Za-z0-9_.]*");
    rule = {pattern, format};
    highlightRules.append(rule);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(dark ? QColor("#91BC8B") : QColor("#35652F"));
    commentFormat.setFontItalic(true);
    highlightRules.append({QRegularExpression(";.*"), commentFormat});

    QTextCharFormat stringFormat;
    stringFormat.setForeground(dark ? QColor("#E4AD94") : QColor("#8A4120"));
    highlightRules.append({QRegularExpression("\"(?:\\\\.|[^\"\\\\])*\"|'(?:\\\\.|[^'\\\\])*'"), stringFormat});

    QTextCharFormat trackingFormat;
    trackingFormat.setForeground(dark ? QColor("#70D6BF") : QColor("#006B58"));
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
