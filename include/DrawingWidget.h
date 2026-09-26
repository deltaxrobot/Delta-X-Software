#pragma once
#include "DrawingProgram.h"
#include <QLabel>

class DrawingWidget : public QLabel
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget* parent = nullptr);
    const DrawingProgram::Paths& paths() const { return m_paths; }
    void replacePaths(const DrawingProgram::Paths& paths);
    void SetPhysicalSize(float widthMm, float heightMm);
    void SetPlaneMarkers(const QVector<QPointF>& markers);
    QSizeF physicalSize() const { return m_size; }
    QPointF mapToLogical(const QPointF& point) const;
    QPointF mapToWidget(const QPointF& point) const;
    bool saveDrawing(const QString& path, QString* error) const;
    bool loadDrawing(const QString& path, QString* error);
    bool canUndo() const { return !m_undo.isEmpty(); }
    bool canRedo() const { return !m_redo.isEmpty(); }
public slots:
    void SelectZoomInTool();
    void SelectZoomOutTool();
    void FitView();
    void EraserAll();
    void Undo();
    void Redo();
    void SelectLineTool();
    void SelectRectangleTool();
    void SelectCircleTool();
    void SelectArcTool();
    void SelectCursor();
signals:
    void pathsChanged();
    void physicalSizeChanged();
protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent*) override;
private:
    enum Tool { Pan, Line, Rectangle, Circle, Arc };
    void select(Tool tool);
    void cancelGesture();
    QVector<QPointF> gesturePath(const QPointF& end) const;
    double scale() const;
    DrawingProgram::Paths m_paths;
    QVector<DrawingProgram::Paths> m_undo, m_redo;
    QVector<QPointF> m_markers, m_preview;
    QSizeF m_size{100, 100};
    double m_zoom = 1;
    QPointF m_pan, m_start, m_last;
    Tool m_tool = Pan;
    bool m_dragging = false;
};
