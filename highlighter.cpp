#include <QtGui>
#include <QRegularExpression>
#include <QDebug>

#include "highlighter.h"

Highlighter::Highlighter(QString filetype, QString theme, QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    // Initialize with invalid expressions
    commentStartExpression = QRegularExpression();
    commentEndExpression = QRegularExpression();
    
    // Validate input parameters
    if (filetype.isEmpty()) {
        qDebug() << "Warning: Empty filetype in Highlighter constructor";
        filetype = "txt"; // Default fallback
    }
    if (theme.isEmpty()) {
        qDebug() << "Warning: Empty theme in Highlighter constructor"; 
        theme = "monokai"; // Default fallback
    }
    
    setupHighlighter(filetype, theme);
}

void Highlighter::setupHighlighter(QString filetype, QString theme){
    // Clear existing rules first
    highlightingRules.clear();
    
    // Supported languages by type/syntax style
    compiledLanguages = QString("adb abs c cpp cs dart go h java m rs rlib swift vala vapi").split(" ");
    scriptingLanguages = QString("bat coffee hs js lua php pl ps1 py rb sh vb").split(" ");
    markupLanguages = QString("htm html json twig ui xml").split(" ");

    // Validate and set color values
    if (theme.isEmpty()) {
        qDebug() << "Warning: Empty theme provided, using default";
        theme = "monokai";
    }
    setColorValues(theme);

    // Validate filetype and apply appropriate rules
    if (filetype.isEmpty()) {
        qDebug() << "Warning: Empty filetype provided, using compiled language rules as default";
        setCompiledLanguageRules();
    } else if (compiledLanguages.contains(filetype.toLower())){
        setCompiledLanguageRules();
    } else if (scriptingLanguages.contains(filetype.toLower())){
        setScriptingLanguageRules();
    } else if (markupLanguages.contains(filetype.toLower())){
        setMarkupLanguageRules();
    } else if (filetype.toLower() == "asm"){
        setAsmRules();
    } else if (filetype.toLower() == "css"){
        setCssRules();
    } else if (filetype.toLower() == "sql"){
        setSqlRules();
    } else {
        qDebug() << "Warning: Unknown filetype:" << filetype << "using compiled language rules as fallback";
        setCompiledLanguageRules();
    }
    
    qDebug() << "Highlighter setup complete for filetype:" << filetype << "with" << highlightingRules.size() << "rules";
}

void Highlighter::setTheme(QString filetype, QString theme){
    setupHighlighter(filetype, theme);
    rehighlight();
}

// Helper method to safely create regex patterns
bool Highlighter::addHighlightingRule(const QString &pattern, const QTextCharFormat &format) {
    QRegularExpression regex(pattern);
    if (!regex.isValid()) {
        qDebug() << "Warning: Invalid regex pattern:" << pattern << "Error:" << regex.errorString();
        return false;
    }
    
    HighlightingRule rule;
    rule.pattern = regex;
    rule.format = format;
    highlightingRules.append(rule);
    return true;
}

void Highlighter::setCompiledLanguageRules(){
    HighlightingRule rule;
    
    // Clear existing rules
    highlightingRules.clear();
    
    //Functions
    functionFormat.setForeground(functionsColor);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    if (!rule.pattern.isValid()) {
        qDebug() << "Warning: Invalid function pattern in setCompiledLanguageRules";
        return;
    }
    rule.format = functionFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(keywordColor);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bint\\b" << "\\bfloat\\b" << "\\bdouble\\b"
                    << "\\bstruct\\b" << "\\benum\\b" << "\\bvoid\\b" << "\\bshort\\b"
                    << "\\blong\\b" << "\\btrue\\b" << "\\bfalse\\b" << "\\bboolean\\b"
                    << "\\bnull\\b" << "\\bthis\\b" << "\\bfinal\\b"
                    << "\\band\\b" << "\\bor\\b" << "\\bxor\\b"
                    << "\\bconst\\b" << "\\bstatic\\b" << "\\bsigned\\b" << "\\bunsigned\\b"
                    << "\\bimport\\b" << "\\bnamespace\\b" << "\\breturn\\b" << "\\busing\\b"
                    << "\\bfor\\b" << "\\bwhile\\b" << "\\bif\\b" << "\\belse\\b"
                    << "\\bcase\\b" << "\\bswitch\\b" << "\\bdo\\b" << "\\bunion\\b"
                    << "\\bnew\\b" << "\\bclass\\b" << "\\bprivate\\b" << "\\bprotected\\b"
                    << "\\bpublic\\b" << "\\bvirtual\\b" << "\\bslots\\b" << "\\bvolatile\\b"
                    << "\\babstract\\b" << "\\bextends\\b" << "\\bimplements\\b" << "\\bsuper\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\btry\\b" << "\\bcatch\\b" << "\\bthrow\\b" << "\\bbreak\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        if (!rule.pattern.isValid()) {
            qDebug() << "Warning: Invalid keyword pattern:" << pattern;
            continue;
        }
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //Nums :D
    numberFormat.setForeground(numColor);
    rule.pattern = QRegularExpression("\\b[0-9\\.]+\\b");
    if (!rule.pattern.isValid()) {
        qDebug() << "Warning: Invalid number pattern in setCompiledLanguageRules";
        return;
    }
    rule.format = numberFormat;
    highlightingRules.append(rule);

    //Quotes
    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\".*\"");
    if (rule.pattern.isValid()) {
        rule.format = quotationFormat;
        highlightingRules.append(rule);
    }

    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("'.*'");
    if (rule.pattern.isValid()) {
        rule.format = quotationFormat;
        highlightingRules.append(rule);
    }

    //Format strings
    formatStringFormat.setForeground(formatStringColor);
    rule.pattern = QRegularExpression("%[sdifFuoxXeEgGaAcpn]+\\b");
    if (rule.pattern.isValid()) {
        rule.format = formatStringFormat;
        highlightingRules.append(rule);
    }

    //Comments
    singleLineCommentFormat.setFontItalic(true);
    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setFontItalic(true);
    multiLineCommentFormat.setForeground(commentColor);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::setScriptingLanguageRules(){
    HighlightingRule rule;
    //Functions
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(functionsColor);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(keyword2Color);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bdef\\b" << "\\bnull\\b" << "\\bimport\\b" << "\\breturn\\b"
                    << "\\bbreak\\b" << "\\bdel\\b" << "\\brequire\\b"
                    << "\\bfor\\b" << "\\bforeach\\b" << "\\bif\\b" << "\\belse\\b"
                    << "\\bin\\b" << "\\bdo\\b" << "\\bwhile\\b" << "\\bnot\\b"
                    << "\\band\\b" << "\\bor\\b" << "\\bwith\\b" << "\\bas\\b"
                    << "\\bclass\\b" << "\\bprivate\\b" << "\\bpublic\\b" << "\\bnew\\b"
                    << "\\bprint\\b" << "\\becho\\b" << "\\btry\\b" << "\\bexcept\\b"
                    << "\\bend\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //Operators :D
    operatorFormat.setForeground(operatorColor);
    rule.pattern = QRegularExpression("\\b[+-*/=<>]+\\b");
    rule.format = operatorFormat;
    highlightingRules.append(rule);

    operatorFormat.setForeground(operatorColor);
    rule.pattern = QRegularExpression("\\s[+-*/=<>]+\\s");
    rule.format = operatorFormat;
    highlightingRules.append(rule);

    //php pl vars
    phpVarFormat.setForeground(varColor);
    rule.pattern = QRegularExpression("\\$\\w+\\b");
    rule.format = phpVarFormat;
    highlightingRules.append(rule);

    //Ruby class/instance vars
    rubyVarFormat.setForeground(varColor);
    rule.pattern = QRegularExpression("@\\b\\w+\\b");
    rule.format = rubyVarFormat;
    highlightingRules.append(rule);

    rubyVarFormat.setForeground(varColor);
    rule.pattern = QRegularExpression("@@\\b\\w+\\b");
    rule.format = rubyVarFormat;
    highlightingRules.append(rule);

    //Nums :D
    numberFormat.setForeground(numColor);
    rule.pattern = QRegularExpression("\\b[0-9\\.]+\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    //Quotes
    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //Comments
    singleLineCommentFormat.setFontItalic(true);
    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setFontItalic(true);
    multiLineCommentFormat.setForeground(commentColor);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::setMarkupLanguageRules(){
    HighlightingRule rule;
    //Functions
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(functionsColor);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // Tags
    tagFormat.setForeground(tagColor);
    rule.pattern = QRegularExpression("<\\w+\\s+[^>]*>");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    tagFormat.setForeground(tagColor);
    rule.pattern = QRegularExpression("<\\w+>");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    tagFormat.setForeground(tagColor);
    rule.pattern = QRegularExpression("</\\b\\w+\\b>");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(htmlAttributesColor);
    QStringList keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bid\\b" << "\\bhref\\b" << "\\bsrc\\b"
                    << "\\blang\\b" << "\\bcharset\\b" << "\\bname\\b" << "\\bcontent\\b"
                    << "\\brel\\b" << "\\btype\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

//    classFormat.setForeground(QColor(209, 84, 84));
//    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

    //Quotes
    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //Comments
    multiLineCommentFormat.setFontItalic(true);
    multiLineCommentFormat.setForeground(commentColor);

    commentStartExpression = QRegularExpression("<!--");
    commentEndExpression = QRegularExpression("-->");
}

void Highlighter::setAsmRules(){
    HighlightingRule rule;
    //Functions
    functionFormat.setForeground(functionsColor);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_<>-@]+:");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    //Nums :D
    numberFormat.setForeground(numColor);
    rule.pattern = QRegularExpression("\\b[0-9a-fx\\.]+\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(keyword2Color);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bcall\\b" << "\\bpush\\b" << "\\bpop\\b" << "\\blea\\b"
                    << "\\bret\\b" << "\\bcmp\\b" << "\\bmov\\b" << "\\bint\\b"
                    << "\\bjmp\\b" << "\\bje\\b" << "\\bjne\\b" << "\\bjl\\b"
                    << "\\bjg\\b" << "\\bjge\\b" << "\\bjle\\b" << "\\bjz\\b"
                    << "\\bjnz\\b" << "\\bjb\\b" << "\\bja\\b" << "\\bjae\\b"
                    << "\\bjbe\\b" << "\\bjs\\b" << "\\bjns\\b" << "\\bleave\\b"
                    << "\\bxor\\b" << "\\bnot\\b" << "\\band\\b" << "\\bor\\b"
                    << "\\bsal\\b" << "\\bsar\\b" << "\\bshl\\b" << "\\bshr\\b"
                    << "\\bnop\\b" << "\\btest\\b" << "\\bxchg\\b"
                    << "\\badd\\b" << "\\bsub\\b" << "\\bmul\\b" << "\\bdiv\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //Quotes
    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //Comments
    singleLineCommentFormat.setFontItalic(true);
    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(commentColor);
    rule.pattern = QRegularExpression(";[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setFontItalic(true);
    multiLineCommentFormat.setForeground(commentColor);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::setCssRules(){
    HighlightingRule rule;
    keywordFormat.setForeground(keywordColor);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bhtml\\b" << "\\bbody\\b" << "\\bp\\b" << "\\ba\\b" << "\\bhr\\b"
                    << "\\bimg\\b" << "\\bheader\\b" << "\\bfooter\\b" << "\\bh1\\b"
                    << "\\bh2\\b" << "\\bh3\\b" << "\\bh4\\b" << "\\bh5\\b" << "\\bh6\\b"
                    << "\\bul\\b" << "\\bol\\b" << "\\bli\\b" << "\\bmain\\b" << "\\bnav\\b"
                    << "\\bmenu\\b" << "\\bmenuitem\\b" << "\\bq\\b" << "\\btable\\b" << "\\btd\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //Nums :D
    numberFormat.setForeground(numColor);
    rule.pattern = QRegularExpression("\\b[0-9\\.]+\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    valueFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\\b[0-9\\.]+[pt|px]+\\b");
    rule.format = valueFormat;
    highlightingRules.append(rule);

    // Attributes
    attributeFormat.setForeground(cssAttributesColor);
    rule.pattern = QRegularExpression("\\w+:");
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    attributeFormat.setForeground(cssAttributesColor);
    rule.pattern = QRegularExpression("\\w+-\\w+:");
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    // IDs
    idFormat.setForeground(cssClassesIDsColor);
    rule.pattern = QRegularExpression("#\\w+\\b");
    rule.format = idFormat;
    highlightingRules.append(rule);

    // classes
    classFormat.setForeground(cssClassesIDsColor);
    rule.pattern = QRegularExpression("\\.\\w+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    //Quotes
    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::setSqlRules(){
    HighlightingRule rule;

    keywordFormat.setForeground(keywordColor);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bSELECT\\b" << "\\bFROM\\b" << "\\bWHERE\\b" << "\\bAND\\b" << "\\bOR\\b"
                    << "\\bDELETE\\b" << "\\bORDER\\b" << "\\bUNION\\b" << "\\bUPDATE\\b"
                    << "\\bINSERT\\b" << "\\bINTO\\b" << "\\bVALUES\\b" << "\\bCREATE\\b"
                    << "\\bTABLE\\b" << "\\bAS\\b" << "\\bBY\\b" << "\\bFOR\\b"
                    << "\\bIF\\b" << "\\bNOT\\b" << "\\bEXISTS\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    //Quotes
    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(valueColor);
    rule.pattern = QRegularExpression("'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::setColorValues(QString theme){
    if (theme == "monokai"){
        // monokai
        keywordColor = QColor(102, 217, 239);
        keyword2Color = QColor(249, 38, 114);
        functionsColor = QColor(166, 226, 46);
        valueColor = QColor(230, 218, 117);
        numColor = QColor(174, 130, 255);
        operatorColor = QColor(249, 38, 114);
        formatStringColor = QColor(174, 130, 255);
        commentColor = QColor(178, 179, 191);
        varColor = QColor(102, 217, 239);
        tagColor = QColor(249, 38, 114);
        htmlAttributesColor = QColor(166, 226, 46);
        cssClassesIDsColor = QColor(166, 226, 46);
        cssAttributesColor = QColor(102, 217, 239);
    } else if (theme == "tomorrow"){
        // tomorrow
        keywordColor = QColor(135, 88, 166);
        keyword2Color = QColor(135, 88, 166);
        functionsColor = QColor(66, 114, 173);
        valueColor = QColor(112, 138, 0);
        numColor = QColor(245, 135, 32);
        operatorColor = QColor(77, 77, 76);
        formatStringColor = QColor(199, 40, 40);
        commentColor = QColor(144, 143, 140);
        varColor = QColor(199, 40, 40);
        tagColor = QColor(199, 40, 40);
        htmlAttributesColor = QColor(245, 135, 32);
        cssClassesIDsColor = QColor(62, 153, 158);
        cssAttributesColor = QColor(77, 77, 76);
    } else if (theme == "tomorrowNight"){
        // tomorrow night
        keywordColor = QColor(177, 149, 186);
        keyword2Color = QColor(177, 149, 186);
        functionsColor = QColor(128, 162, 189);
        valueColor = QColor(182, 189, 106);
        numColor = QColor(222, 146, 95);
        operatorColor = QColor(197, 199, 198);
        formatStringColor = QColor(222, 146, 95);
        commentColor = QColor(149, 150, 149);
        varColor = QColor(204, 102, 102);
        tagColor = QColor(204, 102, 102);
        htmlAttributesColor = QColor(222, 146, 95);
        cssClassesIDsColor = QColor(138, 189, 181);
        cssAttributesColor = QColor(197, 199, 198);
    } else {
        // Solarized
        keywordColor = QColor(181, 137, 0);
        keyword2Color = QColor(133, 153, 0);
        functionsColor = QColor(88, 110, 117);
        valueColor = QColor(42, 161, 152);
        numColor = QColor(42, 161, 152);
        operatorColor = QColor(181, 137, 0);
        formatStringColor = QColor(220, 50, 47);
        commentColor = QColor(178, 179, 191);
        varColor = QColor(38, 139, 210);
        tagColor = QColor(38, 139, 210);
        htmlAttributesColor = QColor(181, 137, 0);
        cssClassesIDsColor = QColor(133, 153, 0);
        cssAttributesColor = QColor(77,171,171);
    }
}

void Highlighter::highlightBlock(const QString &text)
{
    // Validate input
    if (text.isNull()) {
        return;
    }
    
    foreach (const HighlightingRule &rule, highlightingRules) {
        // Skip invalid patterns
        if (!rule.pattern.isValid()) {
            continue;
        }
        
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            int index = match.capturedStart();
            int length = match.capturedLength();
            
            // Safety check to prevent infinite loops
            if (length <= 0) {
                qDebug() << "Warning: Zero-length match detected, breaking";
                break;
            }
            
            setFormat(index, length, rule.format);
        }
    }
    setCurrentBlockState(0);

    // Handle multiline comments with safer validation
    if (commentStartExpression.isValid() && commentEndExpression.isValid()) {
        int startIndex = 0;
        if (previousBlockState() != 1) {
            QRegularExpressionMatch startMatch = commentStartExpression.match(text);
            startIndex = startMatch.hasMatch() ? startMatch.capturedStart() : -1;
        }

        while (startIndex >= 0) {
            QRegularExpressionMatch endMatch = commentEndExpression.match(text, startIndex);
            int endIndex = endMatch.hasMatch() ? endMatch.capturedStart() : -1;
            int commentLength;
            
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex + endMatch.capturedLength();
            }
            
            // Safety check
            if (commentLength <= 0) {
                qDebug() << "Warning: Invalid comment length, breaking";
                break;
            }
            
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            
            // Find next comment start after current comment
            QRegularExpressionMatch nextStartMatch = commentStartExpression.match(text, startIndex + commentLength);
            startIndex = nextStartMatch.hasMatch() ? nextStartMatch.capturedStart() : -1;
        }
    }
}
