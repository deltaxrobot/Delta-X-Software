#include "GcodeScript.h"

// Simple compile test for function system
int main() {
    GcodeScript script;
    
    // Test basic functionality
    QStringList args;
    args << "100" << "200";
    
    script.callFunction("testFunc", args);
    script.handleFUNCTION(QList<QString>(), 0);
    script.handleENDFUNCTION(QList<QString>(), 0);
    script.handleRETURN(QList<QString>(), 0);
    
    return 0;
} 