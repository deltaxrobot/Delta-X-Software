#include "DrawingWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSaveFile>
#include <QFile>
#include <algorithm>
#include <cmath>

DrawingWidget::DrawingWidget(QWidget* parent) : QLabel(parent)
{
    setMinimumSize(240, 240);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    setAccessibleName(tr("Drawing canvas"));
    select(Pan);
}
double DrawingWidget::scale() const
{
    return std::max(0.01, std::min((width() - 36) / m_size.width(), (height() - 36) / m_size.height()) * m_zoom);
}
QPointF DrawingWidget::mapToLogical(const QPointF& p) const
{
    const auto d = (p - QPointF(width()/2.0, height()/2.0) - m_pan) / scale();
    return {d.x(), -d.y()};
}
QPointF DrawingWidget::mapToWidget(const QPointF& p) const
{
    return QPointF(width()/2.0, height()/2.0) + m_pan + QPointF(p.x(), -p.y()) * scale();
}
void DrawingWidget::SetPhysicalSize(float w, float h)
{
    if (!std::isfinite(w) || !std::isfinite(h) || w <= 0 || h <= 0 || w > 100000 || h > 100000) return;
    if (m_size == QSizeF(w,h)) return;
    cancelGesture(); m_size = QSizeF(w,h); update(); emit physicalSizeChanged();
}
void DrawingWidget::SetPlaneMarkers(const QVector<QPointF>& markers) { m_markers = markers; update(); }
void DrawingWidget::cancelGesture() { m_dragging = false; m_preview.clear(); update(); }
void DrawingWidget::replacePaths(const DrawingProgram::Paths& paths)
{
    cancelGesture();
    if (m_paths == paths) return;
    m_undo.append(m_paths);
    qint64 points = 0;
    for (const auto& state : m_undo) for (const auto& path : state) points += path.size();
    while (m_undo.size() > 30 || (points > 1000000 && m_undo.size() > 1)) {
        for (const auto& path : m_undo.first()) points -= path.size();
        m_undo.removeFirst();
    }
    m_redo.clear(); m_paths = paths; update(); emit pathsChanged();
}
void DrawingWidget::Undo() { cancelGesture(); if (canUndo()) { m_redo.append(m_paths); m_paths=m_undo.takeLast(); update(); emit pathsChanged(); } }
void DrawingWidget::Redo() { cancelGesture(); if (canRedo()) { m_undo.append(m_paths); m_paths=m_redo.takeLast(); update(); emit pathsChanged(); } }
void DrawingWidget::EraserAll() { replacePaths({}); }
void DrawingWidget::FitView() { cancelGesture(); m_zoom=1; m_pan={}; update(); }
void DrawingWidget::SelectZoomInTool() { cancelGesture(); m_zoom=std::min(16.0,m_zoom*1.25); update(); }
void DrawingWidget::SelectZoomOutTool() { cancelGesture(); m_zoom=std::max(0.25,m_zoom/1.25); update(); }
void DrawingWidget::select(Tool tool) { cancelGesture(); m_tool=tool; setCursor(tool==Pan ? Qt::OpenHandCursor : Qt::CrossCursor); }
void DrawingWidget::SelectLineTool() { select(Line); }
void DrawingWidget::SelectRectangleTool() { select(Rectangle); }
void DrawingWidget::SelectCircleTool() { select(Circle); }
void DrawingWidget::SelectArcTool() { select(Arc); }
void DrawingWidget::SelectCursor() { select(Pan); }
QVector<QPointF> DrawingWidget::gesturePath(const QPointF& end) const
{
    if (m_tool==Line) return {m_start,end};
    if (m_tool==Rectangle) return {m_start,{end.x(),m_start.y()},end,{m_start.x(),end.y()},m_start};
    const QPointF center = m_tool==Arc ? (m_start+end)/2 : m_start;
    const double radius = QLineF(center,end).length(), pi=3.14159265358979323846;
    const double sweep = m_tool==Arc ? pi : 2*pi;
    const double start = m_tool==Arc ? std::atan2(m_start.y()-center.y(),m_start.x()-center.x()) : 0;
    const int segments=std::clamp(int(std::ceil(sweep*radius/0.5)),24,4096);
    QVector<QPointF> points;
    for (int i=0;i<=segments;++i) {
        const double a=start+sweep*i/segments;
        points.append(center+QPointF(radius*std::cos(a),radius*std::sin(a)));
    }
    if (m_tool==Circle) points.last()=points.first();
    else { points.first()=m_start; points.last()=end; }
    return points;
}
void DrawingWidget::mousePressEvent(QMouseEvent* e)
{
    if (e->button()!=Qt::LeftButton) return;
    setFocus(); m_dragging=true; m_start=mapToLogical(e->pos()); m_last=e->pos();
}
void DrawingWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (!m_dragging) return;
    if (m_tool==Pan) { m_pan+=e->pos()-m_last; m_last=e->pos(); }
    else m_preview=gesturePath(mapToLogical(e->pos()));
    update();
}
void DrawingWidget::mouseReleaseEvent(QMouseEvent* e)
{
    if (!m_dragging || e->button()!=Qt::LeftButton) return;
    const auto end=mapToLogical(e->pos());
    if (m_tool!=Pan && QLineF(m_start,end).length()>0.01) {
        auto paths=m_paths; paths.append(gesturePath(end));
        if (DrawingProgram::validatePaths(paths,nullptr)) replacePaths(paths);
    }
    cancelGesture();
}
void DrawingWidget::keyPressEvent(QKeyEvent* e)
{
    if (e->matches(QKeySequence::Undo)) Undo();
    else if (e->matches(QKeySequence::Redo)) Redo();
    else if (e->key()==Qt::Key_Escape) cancelGesture();
    else QLabel::keyPressEvent(e);
}
void DrawingWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this); p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(),palette().base());
    const QRectF area(mapToWidget({-m_size.width()/2,m_size.height()/2}),mapToWidget({m_size.width()/2,-m_size.height()/2}));
    p.setPen(QPen(palette().mid().color(),1));
    const double step=std::pow(10.0,std::ceil(std::log10(35.0/scale())));
    const QPointF lo=mapToLogical({0,double(height())}), hi=mapToLogical({double(width()),0});
    for (double x=std::ceil(lo.x()/step)*step;x<=hi.x();x+=step) p.drawLine(mapToWidget({x,lo.y()}),mapToWidget({x,hi.y()}));
    for (double y=std::ceil(lo.y()/step)*step;y<=hi.y();y+=step) p.drawLine(mapToWidget({lo.x(),y}),mapToWidget({hi.x(),y}));
    p.setPen(QPen(palette().text().color(),1,Qt::DashLine)); p.drawRect(area);
    p.drawLine(mapToWidget({lo.x(),0}),mapToWidget({hi.x(),0}));
    p.drawLine(mapToWidget({0,lo.y()}),mapToWidget({0,hi.y()}));
    auto drawPath=[&](const QVector<QPointF>& path) {
        QPolygonF polygon; for (const auto& point:path) polygon.append(mapToWidget(point));
        if (polygon.size()==1) p.drawEllipse(polygon.first(),2,2); else p.drawPolyline(polygon);
    };
    p.setPen(QPen(palette().highlight().color(),2));
    for (const auto& path:m_paths) drawPath(path);
    p.setPen(QPen(palette().text().color(),2,Qt::DashLine)); drawPath(m_preview);
    for (int i=0;i<m_markers.size();++i) {
        const auto at=mapToWidget(m_markers[i]); p.drawEllipse(at,4,4);
        p.drawText(at+QPointF(7,-7),QString(QChar('A'+i)));
    }
    p.setPen(palette().text().color());
    p.drawText(QRect(8,8,width()-16,24),Qt::AlignLeft,tr("X →   Y ↑   |   Grid %1 mm").arg(step));
}
bool DrawingWidget::saveDrawing(const QString& fileName, QString* error) const
{
    QJsonArray paths;
    for (const auto& path:m_paths) { QJsonArray points; for (const auto& p:path) points.append(QJsonArray{p.x(),p.y()}); paths.append(points); }
    const QJsonDocument doc(QJsonObject{{"format","delta-x-drawing"},{"version",1},{"width",m_size.width()},{"height",m_size.height()},{"paths",paths}});
    QSaveFile file(fileName);
    const auto bytes=doc.toJson();
    if (!file.open(QIODevice::WriteOnly) || file.write(bytes)!=bytes.size() || !file.commit()) { if(error)*error=file.errorString(); return false; }
    return true;
}
bool DrawingWidget::loadDrawing(const QString& fileName, QString* error)
{
    auto fail=[&](const QString& message) { if(error)*error=message; return false; };
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return fail(file.errorString());
    if(file.size()>20000000) return fail(tr("Drawing file exceeds 20 MB."));
    QJsonParseError parse;
    const auto doc=QJsonDocument::fromJson(file.readAll(),&parse);
    const auto obj=doc.object();
    const double w=obj["width"].toDouble(), h=obj["height"].toDouble();
    if(parse.error!=QJsonParseError::NoError || obj["format"]!="delta-x-drawing" || obj["version"].toInt()!=1 ||
       !obj["paths"].isArray() || !std::isfinite(w) || !std::isfinite(h) || w<=0 || h<=0 || w>100000 || h>100000)
        return fail(tr("Invalid or unsupported Drawing document."));
    DrawingProgram::Paths paths;
    for(const auto& path:obj["paths"].toArray()) {
        if(!path.isArray() || path.toArray().isEmpty()) return fail(tr("Invalid path."));
        QVector<QPointF> points;
        for(const auto& point:path.toArray()) {
            const auto xy=point.toArray();
            if(xy.size()!=2 || !xy[0].isDouble() || !xy[1].isDouble()) return fail(tr("Invalid point."));
            points.append({xy[0].toDouble(),xy[1].toDouble()});
        }
        paths.append(points);
    }
    if(!paths.isEmpty() && !DrawingProgram::validatePaths(paths,error)) return false;
    replacePaths(paths); SetPhysicalSize(w,h); FitView(); return true;
}
