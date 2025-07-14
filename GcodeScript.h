#ifndef GCODE_SCRIPT
#define GCODE_SCRIPT

#include <QObject>
#include "UnityTool.h"
#include <QMap>
#include <QtMath>
#include <QMutex>
#include <QElapsedTimer>
#include "Parameter.h"
#include "SoftwareManager.h"
#include <QFileInfo>
#include <QVector3D>
#include <QMatrix>
#include <QTransform>
#include <QVariant>
#include <QRegularExpression>
#include <QStack>

class GcodeScript : public QObject
{
    Q_OBJECT
public:
    GcodeScript();
    ~GcodeScript();

    enum
    {
        BEGIN = 0,
        CURSOR_POSITION,
    };

    QString ProjectName = "project0";

    QString DefaultRobot = "robot0";
    QString DefaultConveyor = "conveyor0";
    QString DefaultEncoder = "encoder0";
    QString DefaultSlider = "slider0";
    QString DefaultDevice = "device0";
    QString ID = "thread0";

    void SetGcodeScript(QString gcode);
    QString GetGcodeScript();
    void SetProgramPath(QString path);
    QString GetProgramPath();
    QString GetProgramName();
    bool IsRunning();

public slots:
    void ExecuteGcode(QString gcodes, int position);
    void GetResponse(QString deviceId, QString response);
    void SendMsgToDevice(QString deviceId, QString msg);
    void TransmitNextGcode();
    void ExecuteFunction(QString functionName, QStringList paras);
    void Stop();
    void ReceivedGcode(QString gcode);

signals:
    void Finished();
    void Moved(int cursorPos);
    void RobotMoved(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e);
    void RobotMoved(QString gcode);

    void DeleteAllObjects();
    void DeleteAllObjects(QString listName);
    void DeleteObject(int id);
    void PauseCamera();
    void CaptureCamera();
    void ResumeCamera();

    void UpdateTrackingRequest(int id);
    void GetObjectsRequest(int trackingID, QString inAreaListName, float min, float max, bool isXDirection);
    void CaptureAndDetectRequest();

    void SendGcodeToDevice(QString deviceName, QString gcode);
    void SendToDevice(QString deviceName, QString gcode);

    void CatchVariable(QString key, QString value);
    void CatchVariable2(QString key, QVariant value);

    void ChangeExternalVariable(QString cmd);
    void AddObject(QString listName, QList<QStringList> list);
private:

    bool isRunning = false;
    QString gcodeScript = "";
    QString programPath = "";
    QString programName = "";

    QString transmitDeviceId = DefaultRobot;
    QString transmitMsg = "";

    QStringList deviceNames = {"robot", "device", "conveyor", "slider", "encoder"};

    QList<QString> gcodeList;
    QString functionScripts = "";

    QVector<int> gcodeNumberList;
    int gcodeOrder = 0;
    
    // Performance optimization: Cache line numbers for O(1) GOTO lookups
    QMap<int, int> lineNumberCache;  // lineNumber -> gcodeOrder mapping
    bool lineNumberCacheValid = false;
    int currentGcodeEditorCursor = 0;
    int returnSubProPointer[20];
    int returnPointerOrder = -1;
    QString currentLine;

    QString response = "";

    bool IsConveyorSync = false;
    float syncStartArea = -100;
    float syncEndArea = 100;

    QMap<QString, QString>* vars;

    QMutex mMutex;

    QElapsedTimer elapsedTimer;
    
    // IF-ELIF-ELSE-ENDIF block state tracking
    struct IfBlockState {
        bool conditionMet;      // True if any IF/ELIF condition was met
        bool insideBlock;       // True if we're inside this IF block
        int startLine;          // Line number where this IF block started
        int endLine;            // Line number where this IF block ends (ENDIF)
        
        IfBlockState() : conditionMet(false), insideBlock(false), startLine(-1), endLine(-1) {}
        IfBlockState(bool met, bool inside, int start) : conditionMet(met), insideBlock(inside), startLine(start), endLine(-1) {}
    };
    
    QStack<IfBlockState> ifBlockStack;  // Stack to handle nested IF blocks
    
    // FOR loop state tracking
    enum ForLoopType {
        NUMERIC_FOR,    // FOR i = start TO end STEP step
        FOREACH_FOR     // FOR EACH item IN list
    };
    
    struct ForLoopState {
        ForLoopType type;           // Type of FOR loop
        QString counterVar;         // Counter variable name (without #)
        float startValue;           // Start value for numeric FOR
        float endValue;             // End value for numeric FOR
        float stepValue;            // Step value for numeric FOR
        float currentValue;         // Current counter value
        QString listName;           // List name for FOREACH
        int currentIndex;           // Current index for FOREACH
        int startLine;              // Line where FOR starts
        int endForLine;             // Line where ENDFOR is located
        
        ForLoopState() : type(NUMERIC_FOR), startValue(0), endValue(0), stepValue(1), 
                        currentValue(0), currentIndex(0), startLine(-1), endForLine(-1) {}
        ForLoopState(ForLoopType t, QString var, float start, float end, float step, int line) 
            : type(t), counterVar(var), startValue(start), endValue(end), stepValue(step), 
              currentValue(start), currentIndex(0), startLine(line), endForLine(-1) {}
        ForLoopState(ForLoopType t, QString var, QString list, int line)
            : type(t), counterVar(var), listName(list), startValue(0), endValue(0), stepValue(1),
              currentValue(0), currentIndex(0), startLine(line), endForLine(-1) {}
    };
    
    QStack<ForLoopState> forLoopStack;  // Stack to handle nested FOR loops
    
    // Simple function system similar to M98/M99
    int returnFunctionPointer[20];
    int returnFunctionOrder = -1;
    
    // Simple function definition struct
    struct SimpleFunctionDef {
        QString name;
        QStringList parameters;  // Parameter names (without #)
        int startLine;
        
        SimpleFunctionDef() : startLine(-1) {}
        SimpleFunctionDef(QString n, QStringList params, int line) 
            : name(n), parameters(params), startLine(line) {}
    };
    
    QMap<QString, SimpleFunctionDef> functionDefinitions; // function name -> definition

    // Pre-compiled regex patterns for better performance
    static const QRegularExpression m98Regex;
    static const QRegularExpression objectInAreaRegex;

    void prepareCurrentLine();
    bool shouldSkipLine();
    void collapseGcodeLine();
    int findClosingBracket(int openIndex);
    void normalizeOperators();
    void normalizeExpressionOperators(QString& expression);
    
    // Performance optimization methods
    void buildLineNumberCache();
    bool handleGOTO_Optimized(int goID);
    QString normalizeWhitespace(const QString& line);
    void preprocessGcodeScript();  // Normalize entire script once

    void processGOTOStatement(const QList<QString>& valuePairs);

    float GetResultOfMathFunction(QString expression);
    bool isGlobalVariable(QString name);
    bool isConveyorGcode(QString gcode);
    bool isSlidingGcode(QString gcode);
    bool isEncoderGcode(QString gcode);
    bool isMovingGcode(QString gcode);

    bool findExeGcodeAndTransmit();

    void processVARIABLE();
    QString processFUNCTION(QString funcName, QStringList paras);

    bool handleGOTO(QList<QString> valuePairs, int i);
    bool handleIF(QList<QString> valuePairs, int i);
    bool handleELIF(QList<QString> valuePairs, int i);
    bool handleELSE(QList<QString> valuePairs, int i);
    bool handleENDIF(QList<QString> valuePairs, int i);
    void skipToNextConditional(); // Skip to next ELIF, ELSE, or ENDIF
    bool handleFOR(QList<QString> valuePairs, int i);
    bool handleENDFOR(QList<QString> valuePairs, int i);
    void skipToEndFor(); // Skip to ENDFOR
    bool executeForLoopIteration(); // Execute next iteration of FOR loop
    int findEndForLine(int startLine); // Find matching ENDFOR line
    
    // Simple function methods
    bool handleFUNCTION(QList<QString> valuePairs, int i);
    bool handleENDFUNCTION(QList<QString> valuePairs, int i);
    bool handleRETURN(QList<QString> valuePairs, int i);
    bool callFunction(QString functionName, QStringList arguments);
    bool isFunctionCall(QString line);
    QString parseFunctionCall(QString line, QStringList& arguments);

    bool handleVARIABLE(QList<QString> valuePairs, int i);
    bool handleDEFINE_SUBPROGRAM(QList<QString> valuePairs, int i);
    bool handleGCODE(QString transmitGcode);
    void handleSENT_TO_DEVICE(QList<QString> valuePairs, int i);

    QString calculateExpressions(QString expression);
    QString calculateExpressions2(QString expression);
    QString getLeftWord(QString s, int pos);
    QString getRightWord(QString s, int pos);
    QString deleteSpaces(QString s);
    QString formatSpaces(QString s);
    bool isNotNegative(QString s);
    QString getValueAsString(QString var);
    QVariant getValueAsQVariant(QString key);
    void updateVariables(QString str);
    void saveVariable(QString name, QString value);
    void saveVariable(QString name, QVariant value);
    void processResponse(QString response);
    bool checkExclution(QString response);

};

#endif
