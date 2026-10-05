#pragma once
#include <QTextEdit>
// Form-only preview: no runtime workers, project settings or device commands.
class CodeEditor : public QTextEdit { public: using QTextEdit::QTextEdit; };
