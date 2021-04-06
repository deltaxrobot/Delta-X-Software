#include "geisttextedit.h"
#include <iostream>

GeistTextEdit::GeistTextEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    filepath = "";
    fileType = "";
    highlighter = NULL;

    lineColor = QColor(207, 207, 207);
    theme = "tomorrow";
    language = "py";

    numBlocks = 1;

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(onBlockCountChanged(int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    setHighlighter(new Highlighter(language, theme, document()));
}
/*
 *****************************
 *        Editing            *
 *****************************
*/

// Selects Current Line Where Cursor Is Positioned
void GeistTextEdit::selectLine(){
    QTextCursor cur = this->textCursor();
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    this->setTextCursor(cur);
}

// Selects Current Word Where Cursor Is Positioned
void GeistTextEdit::selectWord(){
    QTextCursor cur = this->textCursor();
    cur.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
    this->setTextCursor(cur);
}

// Returns Word Under Cursor
QString GeistTextEdit::lineUnderCursor(){
    selectLine();
    QTextCursor cur = this->textCursor();
    QString line = cur.selectedText();
    cur.clearSelection();
    this->setTextCursor(cur);
    return line;
}

// Returns Word Under Cursor
QString GeistTextEdit::wordUnderCursor(){
    selectWord();
    QTextCursor cur = this->textCursor();
    QString word = cur.selectedText();
    cur.clearSelection();
    this->setTextCursor(cur);
    return word;
}

// Deletes Current Line Where Cursor Is Positioned
void GeistTextEdit::deleteLine(){
    selectLine();
    QTextCursor cur = this->textCursor();
    if(cur.selectedText() != ""){
        cur.removeSelectedText();
    }
    this->setTextCursor(cur);
}

// Deletes Current Word Where Cursor Is Positioned
void GeistTextEdit::deleteWord(){
    selectWord();
    QTextCursor cur = this->textCursor();

    if (cur.selectedText() != ""){
        cur.removeSelectedText();
    }

    this->setTextCursor(cur);
}

// Joins Line Where Cursor Is Currently Positioned With The Line Below It
void GeistTextEdit::joinLines(){
    QTextCursor cur = this->textCursor();

    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
    cur.deleteChar();

    this->setTextCursor(cur);
}

// Swaps Line Where Cursor Is Currently Positioned With The Line Above It
void GeistTextEdit::swapLineUp(){
    QTextCursor cur = this->textCursor();
    //  Select Current Line And Store Value
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newTop = cur.selectedText();
    cur.removeSelectedText();
    // Select Line Above And Store Value
    cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newBottom = cur.selectedText();
    cur.removeSelectedText();
    // Insert New Values
    cur.insertText(newTop);
    cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    cur.insertText(newBottom);
    // Position Cursor
    cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

    this->setTextCursor(cur);
}

// Swaps Line Where Cursor Is Currently Positioned With The Line Below It
void GeistTextEdit::swapLineDown(){
    QTextCursor cur = this->textCursor();
    //  Select Current Line And Store Value
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newBottom = cur.selectedText();
    cur.removeSelectedText();
    // Select Line Below And Store Value
    cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString newTop = cur.selectedText();
    cur.removeSelectedText();
    // Insert New Values
    cur.insertText(newBottom);
    cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    cur.insertText(newTop);
    // Position Cursor
    cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

    this->setTextCursor(cur);
}



/*
 *  Toggles currently selected line(s) between commented out and uncommented
 *  Comments based on language of file type
 *  If no text is selected then it selects the current line
*/
void GeistTextEdit::toggleComment(){
    QTextCursor cur = this->textCursor();
    if (!cur.hasSelection()){
        selectLine();
    }

    int endSelection = cur.selectionEnd();
    cur.setPosition(cur.selectionStart());
    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    this->setTextCursor(cur);

    QString line = lineUnderCursor();

    QString commentStart;
    QString commentEnd;

    if(fileType == "html" || fileType == "css"){

        if(fileType == "html"){
            commentStart = "<!--";
            commentEnd = "-->";
        }else{
            commentStart = "/*";
            commentEnd = "*/";
        }

        if(line.startsWith(commentStart)){
            for(int i=0; i < commentStart.length(); i++){
                cur.deleteChar();
            }
            endSelection -= commentStart.length();

            cur.setPosition(endSelection);
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            this->setTextCursor(cur);
            QString line = lineUnderCursor();

            if(line.endsWith(commentEnd)){
                for(int i=0; i < commentEnd.length(); i++){
                    cur.deletePreviousChar();
                }
            }
        }else{
            cur.insertText(commentStart);
            endSelection += commentStart.length();

            cur.setPosition(endSelection);
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            this->setTextCursor(cur);
            QString line = lineUnderCursor();

            if(!line.endsWith(commentEnd)){
                cur.insertText(commentEnd);
            }
        }

    }else{
        if(fileType == "py"){
            commentStart = "#";
        }else{
            commentStart = "//";
        }

        if(line.startsWith(commentStart)){
            for(int i=0; i < commentStart.length(); i++){
                cur.deleteChar();
            }
            endSelection -= commentStart.length();
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

            while(cur.position() < endSelection){
                cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
                this->setTextCursor(cur);
                line = lineUnderCursor();

                if(line.startsWith(commentStart)){
                    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
                    for(int i=0; i < commentStart.length(); i++){
                        cur.deleteChar();
                    }
                    endSelection -= commentStart.length();

                }
                cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

            }

        }else{
            cur.insertText(commentStart);
            endSelection += commentStart.length();
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);

            while(cur.position() < endSelection){
                cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
                this->setTextCursor(cur);
                line = lineUnderCursor();

                if(!line.startsWith(commentStart)){
                    cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
                    cur.insertText(commentStart);
                    endSelection += commentStart.length();
                }

                cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            }
        }

    }

    this->setTextCursor(cur);
}

void GeistTextEdit::setLineNumberWidget(QListWidget*lineNumberWL)
{
    lwLineNumber = lineNumberWL;

    lwLineNumber->addItem("1");


    lwLineNumber->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lwLineNumber->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), lwLineNumber->verticalScrollBar(), SLOT(setValue(int)));
}

void GeistTextEdit::updateLineNums(int newBlockCount){

    if (lwLineNumber == NULL)
        return;

    if (newBlockCount > numBlocks){
        //  Add Line Numbers
        while (numBlocks < newBlockCount){
            numBlocks++;
            QString lineNum = QString::number(numBlocks);
            lwLineNumber->addItem(lineNum);
            QListWidgetItem *item = lwLineNumber->item(numBlocks-1);
            item->setSizeHint(QSize(item->sizeHint().height(), 14));
        }

    } else {
        //  Remove Line Numbers
        while (numBlocks > newBlockCount){
            lwLineNumber->takeItem(numBlocks - 1);
            numBlocks--;
        }
    }

    if (lbDebugLine == NULL)
        return;

    QString numLinesText = QString::number(newBlockCount) + " Lines";
    lbDebugLine->setText(numLinesText);
}

void GeistTextEdit::setDebugLine(QLabel *debugLineLabel)
{
    lbDebugLine = debugLineLabel;
}

void GeistTextEdit::setHighlighterTheme(QString theme){
    if (highlighter != NULL){
        highlighter->setTheme(fileType, theme);
    }
}

void GeistTextEdit::setHighlighter(Highlighter * h){
    if(highlighter != NULL){
        delete highlighter;
    }

    highlighter = h;
}

/*
 *****************************
 *         File Info         *
 *****************************
*/
QString GeistTextEdit::getFilepath(){
    return filepath;
}

QString GeistTextEdit::getFileType(){
    return fileType;
}

void GeistTextEdit::setFilePath(QString newFilepath){
    filepath = newFilepath;
}
void GeistTextEdit::setFileType(QString newFileType){
    fileType = newFileType;
}

/*
 *****************************
 *         Virtual functions *
 *****************************
*/

void GeistTextEdit::keyPressEvent ( QKeyEvent * e ){
    // Indent Selection On Tab
    if(e->key() == 16777217){
        QTextCursor cur = this->textCursor();
        if (cur.hasSelection()){
            int endSelection = cur.selectionEnd();
            cur.setPosition(cur.selectionStart());
            cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
            cur.insertText("\t");
            endSelection++;
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            while(cur.position() < endSelection){
                cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
                cur.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
                cur.insertText("\t");
                endSelection++;
                cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            }

            this->setTextCursor(cur);

        }else{
            QPlainTextEdit::keyPressEvent(e);
        }

    }else if(e->key() == 16777218){
        // Unindent Selection On Backtab
        QTextCursor cur = this->textCursor();
        if (!cur.hasSelection()){
            selectLine();
        }
        int endSelection = cur.selectionEnd();
        cur.setPosition(cur.selectionStart());
        cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        cur.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
        QString line = cur.selectedText();
        cur.clearSelection();
        if(line.startsWith("\t")){
            cur.deleteChar();
            endSelection -= 1;
        }

        cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        while(cur.position() < endSelection){
            cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
            cur.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
            QString line = cur.selectedText();
            cur.clearSelection();
            if(line.startsWith("\t")){
                cur.deleteChar();
                endSelection -= 1;
            }
            cur.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        }

        this->setTextCursor(cur);

    }else{
        QPlainTextEdit::keyPressEvent(e);
    }
}

void GeistTextEdit::onBlockCountChanged(int newBlockCount)
{
    /*  Auto-Indent New Lines   */

    //  If Block Count Only Increased By One
    if (newBlockCount == numBlocks + 1){

        QString data = toPlainText();
        int cursorPosition = textCursor().position();

        // If Beginning Cursor At Beginning Of New Line
        if (data.mid(cursorPosition-1, 1) == "\n"){
            int pos;

            // Get Position Of Start Of New Line
            for (pos=cursorPosition-2; pos>=0; pos--){

                if (data.mid(pos, 1) == "\n") {
                    break;
                    }
                }

                //  For Each Tab Char At Beggining Of Previous Line: Add Tab To New Line
                while (data.mid(pos + 1, 1) == "\t"){
                    textCursor().insertText("\t");
                    pos++;
                }
         }
    }

    // Update Line Numbers
    updateLineNums(newBlockCount);
}

void GeistTextEdit::highlightCurrentLine()
{
    if (lwLineNumber == NULL)
        return;

    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selections;
    selections.format.setBackground(lineColor);
    selections.format.setProperty(QTextFormat::FullWidthSelection, true);
    selections.cursor = textCursor();
    selections.cursor.clearSelection();
    extraSelections.append(selections);

    setExtraSelections(extraSelections);
    //lwLineNumber->verticalScrollBar()->setValue(verticalScrollBar()->value());
}
