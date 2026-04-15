#ifndef GCODEHIGHLIGHTER_H
#define GCODEHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QFont>
#include <QColor>

class GCodeHighlighter : public QSyntaxHighlighter
{
public:
    GCodeHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct highlightRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<highlightRule> highlightRules;
};

#endif // GCODEHIGHLIGHTER_H
