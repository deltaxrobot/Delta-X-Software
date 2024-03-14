/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "codeeditor.h"

//![constructor]

CodeEditor::CodeEditor(QWidget *parent) : QTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

//    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
//    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

//![constructor]

//![extraAreaWidth]

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::setTabWidth(int width)
{
    QFontMetrics metrics(font());
    setTabStopWidth(width * metrics.width(' '));
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void CodeEditor::updateLineNumberAreaWidth(int newBlockCount )
{
	/*int lineNumber = newBlockCount;
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);*/
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    /*if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);*/
}

void CodeEditor::setLockState(int state)
{
    if (state == Qt::Checked)
        setTextInteractionFlags(Qt::TextBrowserInteraction);
    else
        setTextInteractionFlags(Qt::TextEditorInteraction);
}

void CodeEditor::commentSelectedLines()
{
    QTextCursor cursor = textCursor();
    cursor.beginEditBlock();

    int startPos = cursor.selectionStart();
    int endPos = cursor.selectionEnd();

    cursor.setPosition(startPos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfLine);

    bool allLinesCommented = true;
    while (cursor.position() <= endPos) {
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
        if (cursor.selectedText() != ";") {
            allLinesCommented = false;
            break;
        }
        cursor.movePosition(QTextCursor::Down);
        cursor.movePosition(QTextCursor::StartOfLine);
    }

    cursor.setPosition(startPos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfLine);

    while (cursor.position() <= endPos) {
        if (allLinesCommented) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
            if (cursor.selectedText() == ";") {
                cursor.removeSelectedText();
            }
        } else {
            cursor.insertText(";");
        }
        cursor.movePosition(QTextCursor::Down);
        cursor.movePosition(QTextCursor::StartOfLine);
    }

    cursor.endEditBlock();
}

void CodeEditor::indentText()
{
    QTextCursor cursor = textCursor();
    if (!cursor.selectedText().isEmpty()) {
        cursor.beginEditBlock();

        int startPos = cursor.selectionStart();
        int endPos = cursor.selectionEnd();

        cursor.setPosition(startPos, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::StartOfLine);

        while (cursor.position() <= endPos) {
            cursor.insertText("\t");
            cursor.movePosition(QTextCursor::Down);
            cursor.movePosition(QTextCursor::StartOfLine);
        }

        cursor.endEditBlock();
    }
    else
    {
        // Chèn một tab vào vị trí của cursor
        cursor.insertText("\t");

        // Cập nhật cursor của QTextEdit
        setTextCursor(cursor);
    }
}

void CodeEditor::deleleIndentText()
{
    QTextCursor cursor = textCursor();
    if (!cursor.selectedText().isEmpty()) {
        cursor.beginEditBlock();

        int startPos = cursor.selectionStart();
        int endPos = cursor.selectionEnd();

        cursor.setPosition(startPos, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::StartOfLine);

        while (cursor.position() <= endPos) {
            // nếu dòng hiện tại có ký tự tab thì xóa ký tự tab đó
            if (cursor.block().text().startsWith("\t"))
                cursor.deleteChar();
            cursor.movePosition(QTextCursor::Down);
            cursor.movePosition(QTextCursor::StartOfLine);
        }

        cursor.endEditBlock();
    }
    else
    {
        // nếu dòng hiện tại có ký tự tab thì xóa ký tự tab đó
        if (cursor.block().text().startsWith("\t"))
            cursor.deletePreviousChar();

        // Cập nhật cursor của QTextEdit
        setTextCursor(cursor);
    }
}

//![slotUpdateRequest]

//![resizeEvent]

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    /*QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));*/
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Slash) {
        commentSelectedLines();
    }
    else if (event->key() == Qt::Key_Tab)
    {
        indentText();
    }
    else if (event->key() == Qt::Key_Backtab)
    {
        deleleIndentText();
    }
    else {
        QTextEdit::keyPressEvent(event);
    }
}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    QTextEdit::mousePressEvent(event);
    QTextCursor cursor = cursorForPosition(event->pos());
    int lineNumber = cursor.blockNumber();

    QString lineText = cursor.block().text();

    emit lineClicked(lineNumber, lineText);
}

//![resizeEvent]

//![cursorPositionChanged]

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;


    QTextEdit::ExtraSelection selection;

    QColor lineColor = QColor(QColor("#101010")).lighter(160);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);

    selection.cursor = textCursor();

    selection.cursor.clearSelection();
    extraSelections.append(selection);

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	/*    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block = document()->firstBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }*/
}
//![extraAreaPaintEvent_2]

