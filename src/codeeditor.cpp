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
#include <QMimeData>
#include <QCompleter>
#include <QStringListModel>

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

void CodeEditor::setCompletionWords(const QStringList& words)
{
    QStringList normalized = words;
    normalized.removeAll(QString());
    normalized.removeDuplicates();
    normalized.sort(Qt::CaseInsensitive);

    if (!completionModel) {
        completionModel = new QStringListModel(this);
        completer = new QCompleter(completionModel, this);
        completer->setWidget(this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionMode(QCompleter::PopupCompletion);
        completer->setFilterMode(Qt::MatchStartsWith);
        completer->setMaxVisibleItems(14);
        connect(completer, QOverload<const QString&>::of(&QCompleter::activated),
                this, &CodeEditor::insertCompletion);
    }
    if (completionModel->stringList() != normalized)
        completionModel->setStringList(normalized);
}

//![constructor]

//![extraAreaWidth]

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    QTextDocument *doc = document();
    if (!doc) {
        qDebug() << "Warning: Null document in lineNumberAreaWidth";
        return 50; // Return reasonable default width
    }
    
    int max = qMax(1, doc->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::setTabWidth(int width)
{
    QFontMetrics metrics(font());
    setTabStopDistance(width * metrics.horizontalAdvance(' '));
}

void CodeEditor::setDiagnosticLines(const QHash<int, int>& lines)
{
    diagnosticLines = lines;
    refreshExtraSelections();
}

void CodeEditor::setExecutionLine(int oneBasedLine)
{
    executionLine = oneBasedLine;
    refreshExtraSelections();
}

void CodeEditor::goToLine(int oneBasedLine)
{
    if (oneBasedLine < 1)
        return;
    QTextBlock block = document()->findBlockByNumber(oneBasedLine - 1);
    if (!block.isValid())
        return;
    QTextCursor cursor(block);
    setTextCursor(cursor);
    ensureCursorVisible();
    setFocus();
    refreshExtraSelections();
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
    if (cursor.isNull()) {
        qDebug() << "Warning: Invalid cursor in commentSelectedLines";
        return;
    }
    
    cursor.beginEditBlock();

    int startPos = cursor.selectionStart();
    int endPos = cursor.selectionEnd();
    
    // Validate selection positions
    if (startPos < 0 || endPos < 0 || startPos > endPos) {
        cursor.endEditBlock();
        return;
    }

    cursor.setPosition(startPos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfLine);

    bool allLinesCommented = true;
    int previousPosition = -1;
    while (cursor.position() <= endPos && cursor.position() != previousPosition) {
        previousPosition = cursor.position();
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
        if (cursor.selectedText() != ";") {
            allLinesCommented = false;
            break;
        }
        if (!cursor.movePosition(QTextCursor::Down)) {
            // Cannot move down, we're at the last line
            break;
        }
        cursor.movePosition(QTextCursor::StartOfLine);
    }

    cursor.setPosition(startPos, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::StartOfLine);

    previousPosition = -1;
    while (cursor.position() <= endPos && cursor.position() != previousPosition) {
        previousPosition = cursor.position();
        if (allLinesCommented) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
            if (cursor.selectedText() == ";") {
                cursor.removeSelectedText();
            }
        } else {
            cursor.insertText(";");
        }
        if (!cursor.movePosition(QTextCursor::Down)) {
            // Cannot move down, we're at the last line
            break;
        }
        cursor.movePosition(QTextCursor::StartOfLine);
    }

    cursor.endEditBlock();
}

void CodeEditor::indentText()
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull()) {
        qDebug() << "Warning: Invalid cursor in indentText";
        return;
    }
    
    if (!cursor.selectedText().isEmpty()) {
        cursor.beginEditBlock();

        int startPos = cursor.selectionStart();
        int endPos = cursor.selectionEnd();
        
        // Validate selection positions
        if (startPos < 0 || endPos < 0 || startPos > endPos) {
            cursor.endEditBlock();
            return;
        }

        cursor.setPosition(startPos, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::StartOfLine);

        int previousPosition = -1;
        while (cursor.position() <= endPos && cursor.position() != previousPosition) {
            previousPosition = cursor.position();
            cursor.insertText("\t");
            if (!cursor.movePosition(QTextCursor::Down)) {
                // Cannot move down, we're at the last line
                break;
            }
            cursor.movePosition(QTextCursor::StartOfLine);
        }

        cursor.endEditBlock();
    }
    else
    {
        // Insert a tab at the cursor.
        cursor.insertText("\t");

        // Update the QTextEdit cursor.
        setTextCursor(cursor);
    }
}

void CodeEditor::deleleIndentText()
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull()) {
        qDebug() << "Warning: Invalid cursor in deleleIndentText";
        return;
    }
    
    if (!cursor.selectedText().isEmpty()) {
        cursor.beginEditBlock();

        int startPos = cursor.selectionStart();
        int endPos = cursor.selectionEnd();
        
        // Validate selection positions
        if (startPos < 0 || endPos < 0 || startPos > endPos) {
            cursor.endEditBlock();
            return;
        }

        cursor.setPosition(startPos, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::StartOfLine);

        int previousPosition = -1;
        while (cursor.position() <= endPos && cursor.position() != previousPosition) {
            previousPosition = cursor.position();
            // Remove a leading tab from the current line when present.
            QTextBlock currentBlock = cursor.block();
            if (currentBlock.isValid() && currentBlock.text().startsWith("\t")) {
                cursor.deleteChar();
            }
            if (!cursor.movePosition(QTextCursor::Down)) {
                // Cannot move down, we're at the last line
                break;
            }
            cursor.movePosition(QTextCursor::StartOfLine);
        }

        cursor.endEditBlock();
    }
    else
    {
        // Remove a leading tab from the current line when present.
        QTextBlock currentBlock = cursor.block();
        if (currentBlock.isValid() && currentBlock.text().startsWith("\t")) {
            cursor.deletePreviousChar();
        }

        // Update the QTextEdit cursor.
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
    if (!event)
        return;

    if (completer && completer->popup()->isVisible()) {
        switch (event->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            event->ignore();
            return;
        default:
            break;
        }
    }

    const bool completionShortcut =
        event->key() == Qt::Key_Space &&
        event->modifiers().testFlag(Qt::ControlModifier);
    if (completionShortcut) {
        showCompletionPopup(true);
        return;
    }

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

    if (textInteractionFlags().testFlag(Qt::TextEditable))
        showCompletionPopup(false);
}

QString CodeEditor::completionPrefix() const
{
    QTextCursor cursor = textCursor();
    const QString block = cursor.block().text().left(cursor.positionInBlock());
    int start = block.size();
    while (start > 0) {
        const QChar c = block.at(start - 1);
        if (!c.isLetterOrNumber() && c != '_' && c != '#' && c != '.')
            break;
        --start;
    }
    return block.mid(start);
}

void CodeEditor::insertCompletion(const QString& completion)
{
    if (!completer || completer->widget() != this || completion.isEmpty())
        return;
    const QString prefix = completionPrefix();
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, prefix.size());
    cursor.insertText(completion);
    setTextCursor(cursor);
}

void CodeEditor::showCompletionPopup(bool force)
{
    if (!completer || !completionModel || completionModel->rowCount() == 0 ||
        !textInteractionFlags().testFlag(Qt::TextEditable))
        return;
    const QString prefix = completionPrefix();
    if (!force && prefix.size() < 2) {
        completer->popup()->hide();
        return;
    }
    if (completer->completionPrefix() != prefix) {
        completer->setCompletionPrefix(prefix);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }
    if (completer->completionCount() <= 0) {
        completer->popup()->hide();
        return;
    }
    QRect popupRect = cursorRect();
    popupRect.setWidth(qMax(260, completer->popup()->sizeHintForColumn(0)
                                  + completer->popup()->verticalScrollBar()->sizeHint().width()));
    completer->complete(popupRect);
}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    if (!event) {
        qDebug() << "Warning: Null event in mousePressEvent";
        return;
    }
    
    QTextEdit::mousePressEvent(event);
    QTextCursor cursor = cursorForPosition(event->pos());
    
    if (cursor.isNull()) {
        qDebug() << "Warning: Invalid cursor in mousePressEvent";
        return;
    }
    
    int lineNumber = cursor.blockNumber();
    QString lineText = cursor.block().text();

    emit lineClicked(lineNumber, lineText);
}

//![resizeEvent]

//![cursorPositionChanged]

void CodeEditor::highlightCurrentLine()
{
    refreshExtraSelections();
}

void CodeEditor::refreshExtraSelections()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextCursor cursor = textCursor();
    if (cursor.isNull()) {
        // If cursor is invalid, don't highlight anything
        setExtraSelections(extraSelections);
        return;
    }

    QTextEdit::ExtraSelection currentSelection;
    currentSelection.format.setBackground(palette().color(QPalette::AlternateBase));
    currentSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
    currentSelection.cursor = cursor;
    currentSelection.cursor.clearSelection();
    extraSelections.append(currentSelection);

    for (auto it = diagnosticLines.cbegin(); it != diagnosticLines.cend(); ++it) {
        const QTextBlock block = document()->findBlockByNumber(it.key() - 1);
        if (!block.isValid())
            continue;
        QTextEdit::ExtraSelection diagnosticSelection;
        const QColor color = it.value() >= 2
            ? QColor(220, 70, 70, 55) : QColor(235, 170, 45, 45);
        diagnosticSelection.format.setBackground(color);
        diagnosticSelection.format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        diagnosticSelection.format.setUnderlineColor(
            it.value() >= 2 ? QColor("#ff6b6b") : QColor("#f0b24a"));
        diagnosticSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
        diagnosticSelection.cursor = QTextCursor(block);
        diagnosticSelection.cursor.clearSelection();
        extraSelections.append(diagnosticSelection);
    }

    if (executionLine > 0) {
        const QTextBlock block = document()->findBlockByNumber(executionLine - 1);
        if (block.isValid()) {
            QTextEdit::ExtraSelection executionSelection;
            executionSelection.format.setBackground(QColor(49, 149, 239, 75));
            executionSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
            executionSelection.cursor = QTextCursor(block);
            executionSelection.cursor.clearSelection();
            extraSelections.append(executionSelection);
        }
    }

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	/*    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), palette().color(QPalette::AlternateBase));

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
            painter.setPen(palette().color(QPalette::Text));
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

void CodeEditor::insertFromMimeData(const QMimeData *source)
{
    // Override to ensure only plain text is inserted, preventing rich text formatting issues
    if (source && source->hasText()) {
        QString plainText = source->text();
        
        // Clean the text to remove any unwanted characters
        plainText = plainText.replace('\r', ""); // Remove carriage returns
        
        // Validate cursor before insertion
        QTextCursor cursor = textCursor();
        if (cursor.isNull()) {
            qDebug() << "Warning: Invalid cursor in insertFromMimeData";
            return;
        }
        
        // Insert only plain text to avoid formatting conflicts with syntax highlighter
        cursor.insertText(plainText);
        setTextCursor(cursor);
    } else if (source) {
        // Fallback to default behavior if no text is available
        QTextEdit::insertFromMimeData(source);
    } else {
        qDebug() << "Warning: Null source in insertFromMimeData";
    }
}

