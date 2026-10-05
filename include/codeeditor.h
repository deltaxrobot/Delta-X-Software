#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QTextEdit>
#include <QTextDocument>
#include <QObject>
#include <QHash>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QCompleter;
class QStringListModel;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class CodeEditor : public QTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setTabWidth(int width);
    void setDiagnosticLines(const QHash<int, int>& lines);
    void setExecutionLine(int oneBasedLine);
    void goToLine(int oneBasedLine);
    void setCompletionWords(const QStringList& words);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void insertFromMimeData(const QMimeData *source) override;

public slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void setLockState(int state);

private:
    QWidget *lineNumberArea;
    QHash<int, int> diagnosticLines;
    int executionLine = -1;
    QCompleter* completer = nullptr;
    QStringListModel* completionModel = nullptr;

    void commentSelectedLines();
    void indentText();
    void deleleIndentText();
    void refreshExtraSelections();
    QString completionPrefix() const;
    void insertCompletion(const QString& completion);
    void showCompletionPopup(bool force = false);

signals:
    void lineClicked(int lineNumber, QString lineText);
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

//![extraarea]

#endif
