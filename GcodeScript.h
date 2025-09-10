#ifndef GCODE_SCRIPT
#define GCODE_SCRIPT

#include <QObject>
#include "UnityTool.h"
#include <QMap>
#include <QtMath>
#include <QMutex>
#include <QElapsedTimer>
#include "Parameter.h"
#include <QFileInfo>
#include <QVector3D>
#include <QMatrix>
#include <QTransform>
#include <QVariant>
#include <QRegularExpression>
#include <QStack>

// Forward declarations for cloud point mapping
class CloudPointMapper;
class SoftwareManager;

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

    void SendGcodeToDevice(QString deviceId, QString gcode);

    void AddObject(QString listName, QList<QStringList> objectsInfo);
    void AddObjectArray(QString listName, QList<QStringList> objectsInfo);
    void AddObjectArray2D(QString listName, QList<QStringList> objectsInfo, int rows, int cols);
    void AddObjectArray3D(QString listName, QList<QStringList> objectsInfo, int layers, int rows, int cols);

    void MoveToObject(QString listName, int objectId, float offsetX, float offsetY, float offsetZ);
    void MoveToObject3D(QString listName, int objectId, float offsetX, float offsetY, float offsetZ);
    void MoveToObject2D(QString listName, int objectId, float offsetX, float offsetY, float offsetZ);
    void MoveToFirstObject(QString listName);
    void MoveToLastObject(QString listName);
    void MoveToNearestObject(QString listName, float x, float y, float z);

    void AdjustZAxis(QString listName, int objectId, float z);
    void AdjustZAxis2D(QString listName, int objectId, float z);
    void AdjustZAxis3D(QString listName, int objectId, float z);

    void SetArrayMoveOrder(QString listName, int rows, int cols, int order);
    void SetArrayMoveOrder3D(QString listName, int layers, int rows, int cols, int order);

    void SetObjectNotPicked(QString listName, int objectId);
    void SetObjectPicked(QString listName, int objectId);

    void GetObjectValue(QString listName, int objectId, QString property);
    void GetObjectsCount(QString listName);
    void GetObjectsInArea(QString listName, QString inAreaListName, float min, float max, bool isXDirection);
    void GetObjectsInArea2D(QString listName, QString inAreaListName, float minX, float maxX, float minY, float maxY);
    void GetObjectsInArea3D(QString listName, QString inAreaListName, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

    void GetObjectsInRadius(QString listName, QString inAreaListName, float centerX, float centerY, float radius);
    void GetObjectsInRadius3D(QString listName, QString inAreaListName, float centerX, float centerY, float centerZ, float radius);

    void GetObjectsInPolygon(QString listName, QString inAreaListName, QList<QPointF> polygon);
    void GetObjectsInPolygon3D(QString listName, QString inAreaListName, QList<QVector3D> polygon);

    void GetObjectsInLine(QString listName, QString inAreaListName, QPointF start, QPointF end, float width);
    void GetObjectsInLine3D(QString listName, QString inAreaListName, QVector3D start, QVector3D end, float width);

    void GetObjectsInDirection(QString listName, QString inAreaListName, QPointF start, QPointF direction, float length, float width);
    void GetObjectsInDirection3D(QString listName, QString inAreaListName, QVector3D start, QVector3D direction, float length, float width);

    void GetObjectsByProperty(QString listName, QString inAreaListName, QString property, QString value);
    void GetObjectsByProperty2D(QString listName, QString inAreaListName, QString property, QString value);
    void GetObjectsByProperty3D(QString listName, QString inAreaListName, QString property, QString value);

    void SortObjects(QString listName, QString property, bool ascending);
    void SortObjects2D(QString listName, QString property, bool ascending);
    void SortObjects3D(QString listName, QString property, bool ascending);

    void FilterObjects(QString listName, QString inAreaListName, QString property, float min, float max);
    void FilterObjects2D(QString listName, QString inAreaListName, QString property, float min, float max);
    void FilterObjects3D(QString listName, QString inAreaListName, QString property, float min, float max);

    void GroupObjects(QString listName, QString inAreaListName, QString property);
    void GroupObjects2D(QString listName, QString inAreaListName, QString property);
    void GroupObjects3D(QString listName, QString inAreaListName, QString property);

    void GetObjectsStatistics(QString listName, QString property);
    void GetObjectsStatistics2D(QString listName, QString property);
    void GetObjectsStatistics3D(QString listName, QString property);

    void GetObjectsDistance(QString listName, int objectId1, int objectId2);
    void GetObjectsDistance2D(QString listName, int objectId1, int objectId2);
    void GetObjectsDistance3D(QString listName, int objectId1, int objectId2);

    void GetObjectsAngle(QString listName, int objectId1, int objectId2);
    void GetObjectsAngle2D(QString listName, int objectId1, int objectId2);
    void GetObjectsAngle3D(QString listName, int objectId1, int objectId2);

    void GetObjectsCenter(QString listName, QString inAreaListName);
    void GetObjectsCenter2D(QString listName, QString inAreaListName);
    void GetObjectsCenter3D(QString listName, QString inAreaListName);

    void GetObjectsBounds(QString listName, QString inAreaListName);
    void GetObjectsBounds2D(QString listName, QString inAreaListName);
    void GetObjectsBounds3D(QString listName, QString inAreaListName);

    void GetObjectsConvexHull(QString listName, QString inAreaListName);
    void GetObjectsConvexHull2D(QString listName, QString inAreaListName);
    void GetObjectsConvexHull3D(QString listName, QString inAreaListName);

    void GetObjectsCluster(QString listName, QString inAreaListName, int clusterCount);
    void GetObjectsCluster2D(QString listName, QString inAreaListName, int clusterCount);
    void GetObjectsCluster3D(QString listName, QString inAreaListName, int clusterCount);

    void GetObjectsPath(QString listName, QString inAreaListName, QString algorithm);
    void GetObjectsPath2D(QString listName, QString inAreaListName, QString algorithm);
    void GetObjectsPath3D(QString listName, QString inAreaListName, QString algorithm);

    void GetObjectsOptimalPath(QString listName, QString inAreaListName);
    void GetObjectsOptimalPath2D(QString listName, QString inAreaListName);
    void GetObjectsOptimalPath3D(QString listName, QString inAreaListName);

    void GetObjectsNearestNeighbor(QString listName, int objectId, int count);
    void GetObjectsNearestNeighbor2D(QString listName, int objectId, int count);
    void GetObjectsNearestNeighbor3D(QString listName, int objectId, int count);

    void GetObjectsKMeans(QString listName, QString inAreaListName, int k);
    void GetObjectsKMeans2D(QString listName, QString inAreaListName, int k);
    void GetObjectsKMeans3D(QString listName, QString inAreaListName, int k);

    void GetObjectsDBSCAN(QString listName, QString inAreaListName, float epsilon, int minPoints);
    void GetObjectsDBSCAN2D(QString listName, QString inAreaListName, float epsilon, int minPoints);
    void GetObjectsDBSCAN3D(QString listName, QString inAreaListName, float epsilon, int minPoints);

    void GetObjectsDelaunayTriangulation(QString listName, QString inAreaListName);
    void GetObjectsDelaunayTriangulation2D(QString listName, QString inAreaListName);
    void GetObjectsDelaunayTriangulation3D(QString listName, QString inAreaListName);

    void GetObjectsVoronoiDiagram(QString listName, QString inAreaListName);
    void GetObjectsVoronoiDiagram2D(QString listName, QString inAreaListName);
    void GetObjectsVoronoiDiagram3D(QString listName, QString inAreaListName);

    void GetObjectsMinimumSpanningTree(QString listName, QString inAreaListName);
    void GetObjectsMinimumSpanningTree2D(QString listName, QString inAreaListName);
    void GetObjectsMinimumSpanningTree3D(QString listName, QString inAreaListName);

    void GetObjectsTravelingSalesman(QString listName, QString inAreaListName);
    void GetObjectsTravelingSalesman2D(QString listName, QString inAreaListName);
    void GetObjectsTravelingSalesman3D(QString listName, QString inAreaListName);

    void GetObjectsShortestPath(QString listName, int startObjectId, int endObjectId);
    void GetObjectsShortestPath2D(QString listName, int startObjectId, int endObjectId);
    void GetObjectsShortestPath3D(QString listName, int startObjectId, int endObjectId);
    
    // Variable management signals
    void ChangeExternalVariable(QString value);
    void CatchVariable2(QString name, QVariant value);

private:
    QString gcodeScript;
    QString programPath;
    QString programName;
    bool isRunning;

    //......... Global values

    QList<QString> gcodeList;
    QList<int> gcodeNumberList;
    int gcodeOrder;
    int currentGcodeEditorCursor;
    QString currentLine;
    QString response;
    QString transmitMsg;
    QString transmitDeviceId;
    QElapsedTimer elapsedTimer;
    
    // Cache for line numbers for optimized GOTO operations
    QMap<int, int> lineNumberCache;  // lineNumber -> gcodeOrder
    bool lineNumberCacheValid = false;
    
    // IF block state tracking
    struct IfBlockState {
        bool conditionMet;          // True if condition was met
        bool isExecuting;           // True if currently executing this block
        bool insideBlock;           // True if inside this block
        int startLine;              // Line where IF starts
        
        IfBlockState() : conditionMet(false), isExecuting(false), insideBlock(false), startLine(-1) {}
        IfBlockState(bool met, bool exec, int line) : conditionMet(met), isExecuting(exec), insideBlock(false), startLine(line) {}
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

    // WHILE loop state tracking
    struct WhileLoopState {
        QString condition;              // Condition expression
        int startLine;                  // Line where WHILE starts
        int endWhileLine;               // Line where ENDWHILE is located
        
        WhileLoopState() : startLine(-1), endWhileLine(-1) {}
        WhileLoopState(QString cond, int line) : condition(cond), startLine(line), endWhileLine(-1) {}
    };
    
    QStack<WhileLoopState> whileLoopStack;  // Stack to handle nested WHILE loops
    
    // SWITCH/CASE state tracking
    struct SwitchCaseState {
        QString switchVariable;         // Variable being switched on
        QString switchValue;            // Current value of switch variable
        int startLine;                  // Line where SWITCH starts
        int endSwitchLine;              // Line where ENDSWITCH is located
        bool caseMatched;               // Whether a case has been matched
        bool defaultFound;              // Whether default case was found
        
        SwitchCaseState() : startLine(-1), endSwitchLine(-1), caseMatched(false), defaultFound(false) {}
        SwitchCaseState(QString var, QString val, int line) : switchVariable(var), switchValue(val), startLine(line), endSwitchLine(-1), caseMatched(false), defaultFound(false) {}
    };
    
    QStack<SwitchCaseState> switchCaseStack;  // Stack to handle nested SWITCH statements
    
    // Loop control flags
    bool breakRequested;                // Flag for BREAK statement
    bool continueRequested;             // Flag for CONTINUE statement

    // Function call stacks
    struct CallFrame {
        QMap<QString, QVariant> locals;  // local variables (params + locals)
        QString retTarget;               // variable name (without #) to assign return value to
    };
    QStack<CallFrame> callStack;         // stack for function frames
    QStack<int> functionReturnStack;     // stack for return addresses
    
    // Variables for program control
    int returnPointerOrder;
    int returnSubProPointer[20];  // Array for subprogram pointers
    bool IsConveyorSync;
    QStringList deviceNames;
    
    // Simple function definition struct
    struct SimpleFunctionDef {
        QString name;
        QStringList parameters;  // Parameter names (without #)
        int startLine;
        int endLine;             // Inclusive ENDFUNCTION line
        
        SimpleFunctionDef() : startLine(-1), endLine(-1) {}
        SimpleFunctionDef(QString n, QStringList params, int line, int end = -1) 
            : name(n), parameters(params), startLine(line), endLine(end) {}
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

    float GetResultOfMathFunction(QString expression);
    bool isGlobalVariable(QString name);
    bool isConveyorGcode(QString gcode);
    bool isSlidingGcode(QString gcode);
    bool isEncoderGcode(QString gcode);
    bool isMovingGcode(QString gcode);

    bool findExeGcodeAndTransmit();

    void processVARIABLE();
    QString processFUNCTION(QString funcName, QStringList paras);
    
    // Missing function declarations
    bool handleGOTO(QList<QString> valuePairs, int i);
    bool handleIF(QList<QString> valuePairs, int i);
    bool handleELIF(QList<QString> valuePairs, int i);
    bool handleELSE(QList<QString> valuePairs, int i);
    bool handleENDIF(QList<QString> valuePairs, int i);
    void skipToNextConditional(); // Skip to next ELIF, ELSE, or ENDIF
    bool handleFOR(QList<QString> valuePairs, int i);
    bool handleENDFOR(QList<QString> valuePairs, int i);
    void skipToEndFor();
    bool executeForLoopIteration(); // Execute next iteration of FOR loop
    int findEndForLine(int startLine); // Find matching ENDFOR line
    
    // Removed unused/undefined WHILE/SWITCH/BREAK/CONTINUE and logical helpers
    
    // Simple function methods
    bool handleFUNCTION(QList<QString> valuePairs, int i);
    bool handleENDFUNCTION(QList<QString> valuePairs, int i);
    bool handleRETURN(QList<QString> valuePairs, int i);
    bool callFunction(QString functionName, QStringList arguments);
    bool callFunction(QString functionName, QStringList arguments, const QString& retTarget);
    bool isFunctionCall(QString line);
    QString parseFunctionCall(QString line, QStringList& arguments);
    bool handleLOCAL(QList<QString> valuePairs, int i);

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
    
    // Helpers for functions/expressions

    QStringList splitArgsRespectingParens(const QString& s);
    QString cleanedVarName(const QString& name) const; // remove leading '#', trim
    bool evaluatePureFunction(const QString& functionName, const QStringList& arguments, QString& outValue);
    float EvaluateFunctionToFloat(QString expression);
    bool isNotNegative(QString s);
    QString getValueAsString(QString var);
    QVariant getValueAsQVariant(QString key);
    void updateVariables(QString str);
    void saveVariable(QString name, QString value);
    void saveVariable(QString name, QVariant value);
    void processResponse(QString response);
    bool checkExclution(QString response);

    // Cloud Point Mapping Functions
    /**
     * @brief Add a calibration point to cloud mapping
     * @param imageX Image X coordinate
     * @param imageY Image Y coordinate
     * @param imageZ Image Z coordinate
     * @param realX Real X coordinate
     * @param realY Real Y coordinate
     * @param realZ Real Z coordinate
     * @param confidence Confidence level (0.0-1.0)
     * @param label Optional label
     * @return Point index or -1 if failed
     */
    float cloudPointAddCalibration(float imageX, float imageY, float imageZ, float realX, float realY, float realZ, float confidence = 1.0f, QString label = "");

    /**
     * @brief Transform image coordinates to real coordinates using cloud mapping
     * @param imageX Image X coordinate
     * @param imageY Image Y coordinate
     * @param imageZ Image Z coordinate
     * @param method Interpolation method (0=Linear, 1=Bilinear, 2=Cubic, 3=Radial, 4=Kriging)
     * @return Real X coordinate
     */
    float cloudPointTransformX(float imageX, float imageY, float imageZ, int method = 1);

    /**
     * @brief Transform image coordinates to real coordinates using cloud mapping
     * @param imageX Image X coordinate
     * @param imageY Image Y coordinate
     * @param imageZ Image Z coordinate
     * @param method Interpolation method (0=Linear, 1=Bilinear, 2=Cubic, 3=Radial, 4=Kriging)
     * @return Real Y coordinate
     */
    float cloudPointTransformY(float imageX, float imageY, float imageZ, int method = 1);

    /**
     * @brief Transform image coordinates to real coordinates using cloud mapping
     * @param imageX Image X coordinate
     * @param imageY Image Y coordinate
     * @param imageZ Image Z coordinate
     * @param method Interpolation method (0=Linear, 1=Bilinear, 2=Cubic, 3=Radial, 4=Kriging)
     * @return Real Z coordinate
     */
    float cloudPointTransformZ(float imageX, float imageY, float imageZ, int method = 1);

    /**
     * @brief Get transformation confidence for given image coordinates
     * @param imageX Image X coordinate
     * @param imageY Image Y coordinate
     * @param imageZ Image Z coordinate
     * @param method Interpolation method
     * @return Confidence level (0.0-1.0)
     */
    float cloudPointGetConfidence(float imageX, float imageY, float imageZ, int method = 1);

    /**
     * @brief Get estimated error for given image coordinates
     * @param imageX Image X coordinate
     * @param imageY Image Y coordinate
     * @param imageZ Image Z coordinate
     * @param method Interpolation method
     * @return Estimated error in mm
     */
    float cloudPointGetError(float imageX, float imageY, float imageZ, int method = 1);

    /**
     * @brief Get cloud mapping statistics
     * @return Statistics string
     */
    QString cloudPointGetStats();

    /**
     * @brief Get number of calibration points
     * @return Point count
     */
    float cloudPointGetCount();

    /**
     * @brief Check if cloud mapping is valid and ready for use
     * @return 1 if valid, 0 if not valid
     */
    float cloudPointIsValid();

    /**
     * @brief Clear all calibration points
     * @return 1 if successful, 0 if failed
     */
    float cloudPointClear();

    /**
     * @brief Build mapping grid with specified resolution
     * @param resolution Grid resolution (cells per unit)
     * @return 1 if successful, 0 if failed
     */
    float cloudPointBuildGrid(float resolution = 10.0f);

    /**
     * @brief Validate mapping accuracy
     * @param validationRatio Ratio of points to use for validation (0.0-1.0)
     * @return Average error in mm
     */
    float cloudPointValidate(float validationRatio = 0.2f);

    /**
     * @brief Save cloud mapping to file
     * @param filename File path
     * @return 1 if successful, 0 if failed
     */
    float cloudPointSave(QString filename);

    /**
     * @brief Load cloud mapping from file
     * @param filename File path
     * @return 1 if successful, 0 if failed
     */
    float cloudPointLoad(QString filename);

    /**
     * @brief Export cloud mapping to VariableManager
     * @param variableName Variable name to use
     * @return 1 if successful, 0 if failed
     */
    float cloudPointExport(QString variableName);

    /**
     * @brief Import cloud mapping from VariableManager
     * @param variableName Variable name to load from
     * @return 1 if successful, 0 if failed
     */
    float cloudPointImport(QString variableName);

    /**
     * @brief Remove a calibration point by index
     * @param index Point index
     * @return 1 if successful, 0 if failed
     */
    float cloudPointRemove(int index);

    /**
     * @brief Update a calibration point
     * @param index Point index
     * @param imageX New image X coordinate
     * @param imageY New image Y coordinate
     * @param imageZ New image Z coordinate
     * @param realX New real X coordinate
     * @param realY New real Y coordinate
     * @param realZ New real Z coordinate
     * @param confidence New confidence level
     * @return 1 if successful, 0 if failed
     */
    float cloudPointUpdate(int index, float imageX, float imageY, float imageZ, float realX, float realY, float realZ, float confidence = 1.0f);

    /**
     * @brief Get calibration point image X coordinate
     * @param index Point index
     * @return Image X coordinate
     */
    float cloudPointGetImageX(int index);

    /**
     * @brief Get calibration point image Y coordinate
     * @param index Point index
     * @return Image Y coordinate
     */
    float cloudPointGetImageY(int index);

    /**
     * @brief Get calibration point image Z coordinate
     * @param index Point index
     * @return Image Z coordinate
     */
    float cloudPointGetImageZ(int index);

    // ========== Z-PLANE LIMITING FUNCTIONS ==========
    
    /**
     * @brief Calculate Z-limit at given X,Y position based on configured plane
     * @param x X coordinate in mm
     * @param y Y coordinate in mm
     * @return Z-limit coordinate in mm (minimum safe Z level)
     */
    float zPlaneCalculateZ(float x, float y);
    
    /**
     * @brief Check if Z-plane limiting is enabled
     * @return true if Z-plane limiting is active, false otherwise
     */
    bool zPlaneIsEnabled();
    
    /**
     * @brief Check if a point is below (unsafe) the Z-plane
     * @param x X coordinate in mm
     * @param y Y coordinate in mm
     * @param z Z coordinate in mm
     * @return true if point is below the limiting plane (unsafe), false if safe
     */
    bool zPlaneIsPointBelow(float x, float y, float z);
    
    /**
     * @brief Get the Z-plane equation coefficients
     * @param a Reference to store coefficient A
     * @param b Reference to store coefficient B  
     * @param c Reference to store coefficient C
     * @param d Reference to store coefficient D
     * @return true if plane is valid, false otherwise
     * @note Plane equation: ax + by + cz + d = 0
     */
    bool zPlaneGetEquation(float& a, float& b, float& c, float& d);
    
    // ========== CLOUD POINT MAPPING FUNCTIONS ==========

    /**
     * @brief Get calibration point real X coordinate
     * @param index Point index
     * @return Real X coordinate
     */
    float cloudPointGetRealX(int index);

    /**
     * @brief Get calibration point real Y coordinate
     * @param index Point index
     * @return Real Y coordinate
     */
    float cloudPointGetRealY(int index);

    /**
     * @brief Get calibration point real Z coordinate
     * @param index Point index
     * @return Real Z coordinate
     */
    float cloudPointGetRealZ(int index);

    /**
     * @brief Get calibration point confidence
     * @param index Point index
     * @return Confidence level (0.0-1.0)
     */
    float cloudPointGetPointConfidence(int index);

    /**
     * @brief Get calibration point error
     * @param index Point index
     * @return Error in mm
     */
    float cloudPointGetPointError(int index);

    /**
     * @brief Get calibration point label
     * @param index Point index
     * @return Label string
     */
    QString cloudPointGetLabel(int index);

    // Helper methods for cloud point mapping
    CloudPointMapper* getCloudPointMapper();
    void initializeCloudPointMapper();
    bool isCloudPointMapperAvailable();
    
    // Cloud point mapping instance
    CloudPointMapper* m_cloudPointMapper;
    bool m_cloudPointMapperInitialized;
};

#endif


