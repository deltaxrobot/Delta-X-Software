#ifndef GeistTextEdit_H
#define GeistTextEdit_H

#include <QPlainTextEdit>
#include "highlighter.h"
#include <QListWidget>
#include <QLabel>
#include <QScrollBar>
#include <QTextCursor>
#include <QTextBlockFormat>

class GeistTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    GeistTextEdit(QWidget *parent = 0);
    QString getFilepath();
    QString getFileType();
    void setFilePath(QString newFilepath);
    void setFileType(QString newFileType);
    void setHighlighter(Highlighter * h);
    void setHighlighterTheme(QString theme);
    void selectLine();
    void selectWord();
    QString lineUnderCursor();
    QString wordUnderCursor();
    void deleteLine();
    void deleteWord();
    void joinLines();
    void swapLineUp();
    void swapLineDown();
    void toggleComment();

    void setLineNumberWidget(QListWidget* lineNumberWL);
    void updateLineNums(int newBlockCount);
    void setDebugLine(QLabel* debugLineLabel);

protected:
    virtual void keyPressEvent(QKeyEvent * e);

public slots:
    void onBlockCountChanged(int newBlockCount);
    void highlightCurrentLine();
private:
    QString filepath;
    QString fileType;
    Highlighter * highlighter;

    QListWidget* lwLineNumber;
    QLabel* lbDebugLine;
    int numBlocks;
    QColor lineColor;
    QString theme;
    QString language;

};

#endif // GeistTextEdit_H
