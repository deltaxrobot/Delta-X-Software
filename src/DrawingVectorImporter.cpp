#include "DrawingVectorImporter.h"

#include <QFile>
#include <QFileInfo>
#include <QPainterPath>
#include <QRegularExpression>
#include <QTransform>
#include <QXmlStreamReader>
#include <algorithm>
#include <cmath>

namespace DrawingVectorImporter {
namespace {

constexpr double Pi = 3.14159265358979323846;
constexpr double SvgPxToMm = 25.4 / 96.0;
constexpr qint64 MaxFileSize = 20 * 1024 * 1024;

bool fail(QString* error, const QString& message)
{
    if (error) *error = message;
    return false;
}

bool finite(double value) { return std::isfinite(value); }

bool parseNumber(const QString& text, double* value)
{
    bool ok = false;
    const double parsed = text.trimmed().toDouble(&ok);
    if (!ok || !finite(parsed)) return false;
    *value = parsed;
    return true;
}

bool parseSvgLengthMm(const QString& text, double* value)
{
    static const QRegularExpression expression(
        QStringLiteral(R"(^\s*([+-]?(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)\s*(mm|cm|in|pt|pc|px|q)?\s*$)"),
        QRegularExpression::CaseInsensitiveOption);
    const auto match = expression.match(text);
    if (!match.hasMatch()) return false;
    double number = 0;
    if (!parseNumber(match.captured(1), &number)) return false;
    const QString unit = match.captured(2).toLower();
    double factor = SvgPxToMm;
    if (unit == QStringLiteral("mm")) factor = 1.0;
    else if (unit == QStringLiteral("cm")) factor = 10.0;
    else if (unit == QStringLiteral("in")) factor = 25.4;
    else if (unit == QStringLiteral("pt")) factor = 25.4 / 72.0;
    else if (unit == QStringLiteral("pc")) factor = 25.4 / 6.0;
    else if (unit == QStringLiteral("q")) factor = 0.25;
    *value = number * factor;
    return finite(*value);
}

QVector<double> numbers(const QString& text)
{
    static const QRegularExpression expression(
        QStringLiteral(R"([+-]?(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)"));
    QVector<double> result;
    auto iterator = expression.globalMatch(text);
    while (iterator.hasNext()) {
        bool ok = false;
        const double value = iterator.next().captured().toDouble(&ok);
        if (ok && finite(value)) result.append(value);
    }
    return result;
}

QTransform parseTransform(const QString& text, bool* ok)
{
    QTransform result;
    *ok = true;
    static const QRegularExpression functionExpression(
        QStringLiteral(R"(([A-Za-z]+)\s*\(([^)]*)\))"));
    auto iterator = functionExpression.globalMatch(text);
    int matched = 0;
    while (iterator.hasNext()) {
        const auto match = iterator.next();
        matched += match.capturedLength();
        const QString name = match.captured(1).toLower();
        const auto values = numbers(match.captured(2));
        QTransform operation;
        if (name == QStringLiteral("matrix") && values.size() == 6)
            operation = QTransform(values[0], values[1], values[2], values[3], values[4], values[5]);
        else if (name == QStringLiteral("translate") && (values.size() == 1 || values.size() == 2))
            operation.translate(values[0], values.size() == 2 ? values[1] : 0.0);
        else if (name == QStringLiteral("scale") && (values.size() == 1 || values.size() == 2))
            operation.scale(values[0], values.size() == 2 ? values[1] : values[0]);
        else if (name == QStringLiteral("rotate") && (values.size() == 1 || values.size() == 3)) {
            if (values.size() == 3) operation.translate(values[1], values[2]);
            operation.rotate(values[0]);
            if (values.size() == 3) operation.translate(-values[1], -values[2]);
        } else if (name == QStringLiteral("skewx") && values.size() == 1)
            operation.shear(std::tan(values[0] * Pi / 180.0), 0.0);
        else if (name == QStringLiteral("skewy") && values.size() == 1)
            operation.shear(0.0, std::tan(values[0] * Pi / 180.0));
        else {
            *ok = false;
            return {};
        }
        // SVG applies the transform functions in the written order.
        result = operation * result;
    }
    if (!text.trimmed().isEmpty() && matched == 0) *ok = false;
    return result;
}

class SvgPathParser {
public:
    SvgPathParser(QString data, QPainterPath* output) : m_data(std::move(data)), m_path(output) {}

    bool parse(QString* error)
    {
        QChar command;
        while (skipSeparators(), m_pos < m_data.size()) {
            if (m_data[m_pos].isLetter()) command = m_data[m_pos++];
            else if (command.isNull()) return fail(error, QStringLiteral("SVG path data starts without a command."));
            if (!execute(command, error)) return false;
        }
        return true;
    }

private:
    void skipSeparators()
    {
        while (m_pos < m_data.size() && (m_data[m_pos].isSpace() || m_data[m_pos] == ',')) ++m_pos;
    }

    bool hasNumber()
    {
        skipSeparators();
        if (m_pos >= m_data.size()) return false;
        const QChar c = m_data[m_pos];
        return c.isDigit() || c == '+' || c == '-' || c == '.';
    }

    bool number(double* output)
    {
        skipSeparators();
        static const QRegularExpression expression(
            QStringLiteral(R"(^[+-]?(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)"));
        const auto match = expression.match(m_data.mid(m_pos));
        if (!match.hasMatch()) return false;
        bool ok = false;
        *output = match.captured().toDouble(&ok);
        if (!ok || !finite(*output)) return false;
        m_pos += match.capturedLength();
        return true;
    }

    bool pair(QPointF* point)
    {
        double x = 0, y = 0;
        if (!number(&x) || !number(&y)) return false;
        *point = {x, y};
        return true;
    }

    QPointF absolute(const QPointF& point, bool relative) const
    {
        return relative ? m_current + point : point;
    }

    void appendArc(double rx, double ry, double rotation, bool largeArc, bool sweep, const QPointF& target)
    {
        const QPointF start = m_current;
        rx = std::abs(rx); ry = std::abs(ry);
        if (rx < 1e-12 || ry < 1e-12 || QLineF(start, target).length() < 1e-12) {
            m_path->lineTo(target); m_current = target; return;
        }
        const double phi = rotation * Pi / 180.0;
        const double cosPhi = std::cos(phi), sinPhi = std::sin(phi);
        const double dx = (start.x() - target.x()) / 2.0;
        const double dy = (start.y() - target.y()) / 2.0;
        const double xp = cosPhi * dx + sinPhi * dy;
        const double yp = -sinPhi * dx + cosPhi * dy;
        const double lambda = xp*xp/(rx*rx) + yp*yp/(ry*ry);
        if (lambda > 1.0) { const double scale = std::sqrt(lambda); rx *= scale; ry *= scale; }
        const double numerator = std::max(0.0, rx*rx*ry*ry - rx*rx*yp*yp - ry*ry*xp*xp);
        const double denominator = rx*rx*yp*yp + ry*ry*xp*xp;
        double coefficient = denominator > 0 ? std::sqrt(numerator / denominator) : 0.0;
        if (largeArc == sweep) coefficient = -coefficient;
        const double cxp = coefficient * (rx * yp / ry);
        const double cyp = coefficient * (-ry * xp / rx);
        const double cx = cosPhi*cxp - sinPhi*cyp + (start.x()+target.x())/2.0;
        const double cy = sinPhi*cxp + cosPhi*cyp + (start.y()+target.y())/2.0;
        auto angle = [](double ux, double uy, double vx, double vy) {
            return std::atan2(ux*vy-uy*vx, ux*vx+uy*vy);
        };
        const double ux = (xp-cxp)/rx, uy = (yp-cyp)/ry;
        const double vx = (-xp-cxp)/rx, vy = (-yp-cyp)/ry;
        double startAngle = angle(1,0,ux,uy);
        double delta = angle(ux,uy,vx,vy);
        if (!sweep && delta > 0) delta -= 2*Pi;
        if (sweep && delta < 0) delta += 2*Pi;
        const int segments = std::clamp(int(std::ceil(std::abs(delta) / (Pi/36.0))), 1, 4096);
        for (int i=1; i<=segments; ++i) {
            const double theta = startAngle + delta * i / segments;
            const double x = cx + cosPhi*rx*std::cos(theta) - sinPhi*ry*std::sin(theta);
            const double y = cy + sinPhi*rx*std::cos(theta) + cosPhi*ry*std::sin(theta);
            m_path->lineTo(i == segments ? target : QPointF(x,y));
        }
        m_current = target;
    }

    bool execute(QChar command, QString* error)
    {
        const bool relative = command.isLower();
        const QChar upper = command.toUpper();
        if (upper == 'Z') {
            m_path->closeSubpath(); m_current = m_subpathStart;
            m_lastCubic = m_lastQuadratic = m_current; m_previous = upper; return true;
        }
        bool consumed = false;
        bool parametersOk = true;
        int item = 0;
        while (hasNumber()) {
            consumed = true;
            QPointF p, p1, p2;
            double a=0,b=0,c=0,d=0,e=0;
            if (upper == 'M' || upper == 'L' || upper == 'T') {
                if (!pair(&p)) { parametersOk=false; break; } p = absolute(p, relative);
                if (upper == 'M' && item == 0) { m_path->moveTo(p); m_subpathStart = p; }
                else if (upper == 'T') {
                    const QPointF control = m_previous == 'Q' || m_previous == 'T' ? 2*m_current-m_lastQuadratic : m_current;
                    m_path->quadTo(control,p); m_lastQuadratic=control;
                } else m_path->lineTo(p);
                m_current=p;
            } else if (upper == 'H') {
                if (!number(&a)) { parametersOk=false; break; } p={relative?m_current.x()+a:a,m_current.y()}; m_path->lineTo(p); m_current=p;
            } else if (upper == 'V') {
                if (!number(&a)) { parametersOk=false; break; } p={m_current.x(),relative?m_current.y()+a:a}; m_path->lineTo(p); m_current=p;
            } else if (upper == 'C') {
                if (!pair(&p1)||!pair(&p2)||!pair(&p)) { parametersOk=false; break; }
                p1=absolute(p1,relative); p2=absolute(p2,relative); p=absolute(p,relative);
                m_path->cubicTo(p1,p2,p); m_lastCubic=p2; m_current=p;
            } else if (upper == 'S') {
                if (!pair(&p2)||!pair(&p)) { parametersOk=false; break; }
                p2=absolute(p2,relative); p=absolute(p,relative);
                p1=(m_previous=='C'||m_previous=='S')?2*m_current-m_lastCubic:m_current;
                m_path->cubicTo(p1,p2,p); m_lastCubic=p2; m_current=p;
            } else if (upper == 'Q') {
                if (!pair(&p1)||!pair(&p)) { parametersOk=false; break; }
                p1=absolute(p1,relative); p=absolute(p,relative);
                m_path->quadTo(p1,p); m_lastQuadratic=p1; m_current=p;
            } else if (upper == 'A') {
                if (!number(&a)||!number(&b)||!number(&c)||!number(&d)||!number(&e)||!pair(&p)) { parametersOk=false; break; }
                p=absolute(p,relative); appendArc(a,b,c,d!=0,e!=0,p);
            } else return fail(error, QStringLiteral("Unsupported SVG path command: %1").arg(command));
            ++item;
            m_previous = upper;
        }
        if (!consumed || !parametersOk) return fail(error, QStringLiteral("Invalid SVG path parameters near position %1.").arg(m_pos));
        return true;
    }

    QString m_data;
    qsizetype m_pos = 0;
    QPainterPath* m_path = nullptr;
    QPointF m_current, m_subpathStart, m_lastCubic, m_lastQuadratic;
    QChar m_previous;
};

double attributeNumber(const QXmlStreamAttributes& attributes, const QString& name, double fallback = 0)
{
    const QString text = attributes.value(name).toString();
    if (text.isEmpty()) return fallback;
    const auto parsed = numbers(text);
    return parsed.isEmpty() ? fallback : parsed.first();
}

bool hiddenElement(const QXmlStreamAttributes& attributes)
{
    const QString style = attributes.value(QStringLiteral("style")).toString().toLower();
    QString compactStyle=style; compactStyle.remove(QRegularExpression(QStringLiteral("\\s+")));
    const QString display = attributes.value(QStringLiteral("display")).toString().toLower();
    const QString visibility = attributes.value(QStringLiteral("visibility")).toString().toLower();
    const QString opacity = attributes.value(QStringLiteral("opacity")).toString();
    static const QRegularExpression zeroOpacity(QStringLiteral(R"((?:^|;)opacity\s*:\s*0(?:\.0+)?\s*(?:;|$))"));
    bool opacityOk=false; const double opacityValue=opacity.trimmed().toDouble(&opacityOk);
    return display == QStringLiteral("none") || visibility == QStringLiteral("hidden") ||
           compactStyle.contains(QStringLiteral("display:none")) || compactStyle.contains(QStringLiteral("visibility:hidden")) ||
           ((opacityOk && opacityValue == 0.0) || zeroOpacity.match(style).hasMatch());
}

void appendPainterPath(const QPainterPath& source, const QVector<QTransform>& transforms,
                       const QTransform& root, DrawingProgram::Paths* paths)
{
    QPainterPath path = source;
    for (auto it = transforms.crbegin(); it != transforms.crend(); ++it) path = it->map(path);
    path = root.map(path);
    constexpr double precision = 8.0;
    const auto polygons = path.toSubpathPolygons(QTransform::fromScale(precision, precision));
    for (const auto& polygon : polygons) {
        QVector<QPointF> converted;
        converted.reserve(polygon.size());
        for (const auto& point : polygon) {
            const QPointF p = point / precision;
            if (converted.isEmpty() || QLineF(converted.last(),p).length() > 1e-6) converted.append(p);
        }
        if (!converted.isEmpty()) paths->append(converted);
    }
}

struct DxfPair { int code = 0; QString value; };

bool dxfDouble(const QVector<DxfPair>& entity, int code, double* value, int occurrence = 0)
{
    int found = 0;
    for (const auto& pair : entity) if (pair.code == code) {
        if (found++ == occurrence) return parseNumber(pair.value, value);
    }
    return false;
}

int dxfInt(const QVector<DxfPair>& entity, int code, int fallback = 0)
{
    for (const auto& pair : entity) if (pair.code == code) {
        bool ok=false; const int value=pair.value.trimmed().toInt(&ok); return ok?value:fallback;
    }
    return fallback;
}

QVector<QPointF> dxfEllipse(QPointF center, QPointF major, double ratio, double start, double end, double unitScale)
{
    while (end < start) end += 2*Pi;
    const double sweep = std::min(end-start,2*Pi);
    const int segments = std::clamp(int(std::ceil(std::abs(sweep)*std::max(major.manhattanLength()*unitScale,1.0)/0.25)),24,4096);
    const QPointF minor(-major.y()*ratio,major.x()*ratio);
    QVector<QPointF> path; path.reserve(segments+1);
    for(int i=0;i<=segments;++i) {
        const double a=start+sweep*i/segments;
        path.append(center+major*std::cos(a)+minor*std::sin(a));
    }
    if(std::abs(sweep-2*Pi)<1e-6) path.last()=path.first();
    return path;
}

struct DxfVertex { QPointF point; double bulge = 0; };

void appendDxfSegment(QVector<QPointF>* path, const DxfVertex& from, const QPointF& to, double unitScale)
{
    if(path->isEmpty()) path->append(from.point);
    if(std::abs(from.bulge)<1e-12||QLineF(from.point,to).length()<1e-12){path->append(to);return;}
    const QPointF delta=to-from.point;
    const double chord=std::hypot(delta.x(),delta.y());
    const QPointF left(-delta.y()/chord,delta.x()/chord);
    const QPointF center=(from.point+to)/2+left*(chord*(1-from.bulge*from.bulge)/(4*from.bulge));
    const double sweep=4*std::atan(from.bulge);
    const double radius=QLineF(center,from.point).length();
    const double start=std::atan2(from.point.y()-center.y(),from.point.x()-center.x());
    const int segments=std::clamp(int(std::ceil(std::max(std::abs(sweep)/(Pi/36.0),std::abs(sweep)*radius*unitScale/0.25))),1,4096);
    for(int i=1;i<=segments;++i){const double a=start+sweep*i/segments;path->append(i==segments?to:center+QPointF(radius*std::cos(a),radius*std::sin(a)));}
}

double dxfUnitMm(int unit)
{
    switch(unit) {
    case 1:return 25.4; case 2:return 304.8; case 3:return 1609344.0; case 4:return 1.0;
    case 5:return 10.0; case 6:return 1000.0; case 7:return 1000000.0; case 8:return 0.0000254;
    case 9:return 0.0254; case 10:return 914.4; case 11:return 1e-7; case 12:return 1e-6;
    case 13:return 0.001; case 14:return 100.0; default:return 1.0;
    }
}

} // namespace

bool importSvg(const QByteArray& data, Result* result, QString* error)
{
    if (!result) return fail(error, QStringLiteral("Vector import output is unavailable."));
    QXmlStreamReader xml(data);
    QRectF viewBox;
    double widthMm = 0, heightMm = 0;
    bool haveRoot = false;
    bool preserveNone = false;
    QVector<QTransform> transforms;
    QVector<bool> hidden;
    int ignoredDepth = 0;
    DrawingProgram::Paths paths;
    QStringList warnings;
    QTransform root;

    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            const QString name = xml.name().toString().toLower();
            const auto attributes = xml.attributes();
            if (!haveRoot) {
                if (name != QStringLiteral("svg")) return fail(error, QStringLiteral("The document root is not SVG."));
                const auto box = numbers(attributes.value(QStringLiteral("viewBox")).toString());
                if (box.size() == 4 && box[2] > 0 && box[3] > 0) viewBox={box[0],box[1],box[2],box[3]};
                const bool haveWidth=parseSvgLengthMm(attributes.value(QStringLiteral("width")).toString(),&widthMm);
                const bool haveHeight=parseSvgLengthMm(attributes.value(QStringLiteral("height")).toString(),&heightMm);
                if (viewBox.isEmpty()) {
                    if (!haveWidth || !haveHeight) return fail(error, QStringLiteral("SVG needs a valid viewBox or physical width and height."));
                    viewBox={0,0,widthMm/SvgPxToMm,heightMm/SvgPxToMm};
                }
                if (!haveWidth) { widthMm=viewBox.width()*SvgPxToMm; warnings<<QStringLiteral("SVG width has no physical unit; 96 DPI was assumed."); }
                if (!haveHeight) { heightMm=viewBox.height()*SvgPxToMm; warnings<<QStringLiteral("SVG height has no physical unit; 96 DPI was assumed."); }
                if (widthMm<=0 || heightMm<=0 || widthMm>100000 || heightMm>100000)
                    return fail(error,QStringLiteral("SVG physical dimensions are invalid or exceed 100000 mm."));
                preserveNone=attributes.value(QStringLiteral("preserveAspectRatio")).toString().trimmed().startsWith(QStringLiteral("none"),Qt::CaseInsensitive);
                double sx=widthMm/viewBox.width(), sy=heightMm/viewBox.height(), ox=0, oy=0;
                if(!preserveNone) { const double scale=std::min(sx,sy); sx=sy=scale; ox=(widthMm-viewBox.width()*scale)/2; oy=(heightMm-viewBox.height()*scale)/2; }
                root=QTransform(sx,0,0,-sy,ox-widthMm/2-viewBox.x()*sx,heightMm/2-oy+viewBox.y()*sy);
                haveRoot=true;
            }
            bool transformOk=true;
            transforms.append(parseTransform(attributes.value(QStringLiteral("transform")).toString(),&transformOk));
            hidden.append((hidden.isEmpty()?false:hidden.last())||hiddenElement(attributes));
            if(!transformOk) return fail(error,QStringLiteral("Unsupported SVG transform on <%1>.").arg(name));
            const bool ignored = name==QStringLiteral("defs")||name==QStringLiteral("clippath")||name==QStringLiteral("mask")||
                                 name==QStringLiteral("pattern")||name==QStringLiteral("marker")||name==QStringLiteral("symbol");
            if(ignoredDepth>0||ignored) { ++ignoredDepth; continue; }
            if(hidden.last()||name==QStringLiteral("svg")||name==QStringLiteral("g")||name==QStringLiteral("title")||
               name==QStringLiteral("desc")||name==QStringLiteral("metadata")||name==QStringLiteral("style")) continue;
            QPainterPath path;
            if(name==QStringLiteral("line")) {
                path.moveTo(attributeNumber(attributes,"x1"),attributeNumber(attributes,"y1"));
                path.lineTo(attributeNumber(attributes,"x2"),attributeNumber(attributes,"y2"));
            } else if(name==QStringLiteral("rect")) {
                const double x=attributeNumber(attributes,"x"), y=attributeNumber(attributes,"y");
                const double w=attributeNumber(attributes,"width"), h=attributeNumber(attributes,"height");
                const double rx=attributeNumber(attributes,"rx"), ry=attributeNumber(attributes,"ry",rx);
                if(w>0&&h>0) { if(rx>0||ry>0) path.addRoundedRect({x,y,w,h},rx,ry,Qt::AbsoluteSize); else path.addRect({x,y,w,h}); }
            } else if(name==QStringLiteral("circle")) {
                const double cx=attributeNumber(attributes,"cx"),cy=attributeNumber(attributes,"cy"),r=attributeNumber(attributes,"r");
                if(r>0) path.addEllipse({cx-r,cy-r,2*r,2*r});
            } else if(name==QStringLiteral("ellipse")) {
                const double cx=attributeNumber(attributes,"cx"),cy=attributeNumber(attributes,"cy");
                const double rx=attributeNumber(attributes,"rx"),ry=attributeNumber(attributes,"ry");
                if(rx>0&&ry>0) path.addEllipse({cx-rx,cy-ry,2*rx,2*ry});
            } else if(name==QStringLiteral("polyline")||name==QStringLiteral("polygon")) {
                const auto values=numbers(attributes.value(QStringLiteral("points")).toString());
                if(values.size()>=2&&values.size()%2==0) { path.moveTo(values[0],values[1]); for(int i=2;i<values.size();i+=2)path.lineTo(values[i],values[i+1]); if(name==QStringLiteral("polygon"))path.closeSubpath(); }
            } else if(name==QStringLiteral("path")) {
                SvgPathParser parser(attributes.value(QStringLiteral("d")).toString(),&path);
                QString pathError; if(!parser.parse(&pathError)) return fail(error,pathError);
            } else if(name==QStringLiteral("use")||name==QStringLiteral("text")||name==QStringLiteral("image")) {
                warnings<<QStringLiteral("Skipped unsupported SVG <%1> element.").arg(name); continue;
            } else continue;
            if(!path.isEmpty()) appendPainterPath(path,transforms,root,&paths);
        } else if(xml.isEndElement()) {
            if(ignoredDepth>0)--ignoredDepth;
            if(!transforms.isEmpty())transforms.removeLast();
            if(!hidden.isEmpty())hidden.removeLast();
        }
    }
    if(xml.hasError())return fail(error,QStringLiteral("Invalid SVG XML: %1").arg(xml.errorString()));
    if(!haveRoot)return fail(error,QStringLiteral("SVG root element is missing."));
    if(!DrawingProgram::validatePaths(paths,error))return false;
    warnings.removeDuplicates();
    result->paths=paths; result->sizeMm={widthMm,heightMm}; result->warnings=warnings;
    return true;
}

bool importDxf(const QByteArray& data, Result* result, QString* error)
{
    if(!result)return fail(error,QStringLiteral("Vector import output is unavailable."));
    if(data.startsWith("AutoCAD Binary DXF"))return fail(error,QStringLiteral("Binary DXF is not supported. Export an ASCII DXF file."));
    const QString text=QString::fromUtf8(data);
    const QStringList lines=text.split(QRegularExpression(QStringLiteral("\r?\n")));
    QVector<DxfPair> pairs;
    for(int i=0;i+1<lines.size();i+=2) {
        bool ok=false; const int code=lines[i].trimmed().toInt(&ok);
        if(!ok)return fail(error,QStringLiteral("Invalid ASCII DXF group code near line %1.").arg(i+1));
        pairs.append({code,lines[i+1].trimmed()});
    }
    int units=0;
    for(int i=0;i+1<pairs.size();++i)if(pairs[i].code==9&&pairs[i].value==QStringLiteral("$INSUNITS")) {
        for(int j=i+1;j<std::min(i+5,int(pairs.size()));++j)if(pairs[j].code==70){bool ok=false;units=pairs[j].value.toInt(&ok);if(!ok)units=0;break;}
    }
    int begin=-1,end=pairs.size();
    for(int i=0;i+1<pairs.size();++i)if(pairs[i].code==0&&pairs[i].value==QStringLiteral("SECTION")&&pairs[i+1].code==2&&pairs[i+1].value==QStringLiteral("ENTITIES")){begin=i+2;break;}
    if(begin<0)return fail(error,QStringLiteral("DXF ENTITIES section is missing."));
    for(int i=begin;i<pairs.size();++i)if(pairs[i].code==0&&pairs[i].value==QStringLiteral("ENDSEC")){end=i;break;}
    QVector<QPair<QString,QVector<DxfPair>>> entities;
    for(int i=begin;i<end;) {
        if(pairs[i].code!=0){++i;continue;}
        const QString type=pairs[i].value.toUpper(); int j=i+1; while(j<end&&pairs[j].code!=0)++j;
        QVector<DxfPair> fields; for(int k=i+1;k<j;++k)fields.append(pairs[k]); entities.append({type,fields}); i=j;
    }
    const double unit=dxfUnitMm(units);
    DrawingProgram::Paths paths; QStringList warnings;
    for(int index=0;index<entities.size();++index) {
        const QString type=entities[index].first; const auto& entity=entities[index].second;
        if(type==QStringLiteral("LINE")) {
            double x1,y1,x2,y2;if(dxfDouble(entity,10,&x1)&&dxfDouble(entity,20,&y1)&&dxfDouble(entity,11,&x2)&&dxfDouble(entity,21,&y2))paths.append({{x1,y1},{x2,y2}});
        } else if(type==QStringLiteral("LWPOLYLINE")) {
            QVector<DxfVertex> vertices;
            for(const auto& p:entity){double value=0;if(p.code==10&&parseNumber(p.value,&value))vertices.append({{value,0},0});
                else if(!vertices.isEmpty()&&p.code==20&&parseNumber(p.value,&value))vertices.last().point.setY(value);
                else if(!vertices.isEmpty()&&p.code==42&&parseNumber(p.value,&value))vertices.last().bulge=value;}
            QVector<QPointF> path;
            for(int i=0;i+1<vertices.size();++i)appendDxfSegment(&path,vertices[i],vertices[i+1].point,unit);
            if(vertices.size()==1)path.append(vertices.first().point);
            if(vertices.size()>1&&(dxfInt(entity,70)&1))appendDxfSegment(&path,vertices.last(),vertices.first().point,unit);
            if(!path.isEmpty())paths.append(path);
        } else if(type==QStringLiteral("POLYLINE")) {
            QVector<DxfVertex> vertices; const bool closed=dxfInt(entity,70)&1;
            while(index+1<entities.size()&&entities[index+1].first==QStringLiteral("VERTEX")) { ++index;double x,y,bulge=0;if(dxfDouble(entities[index].second,10,&x)&&dxfDouble(entities[index].second,20,&y)){dxfDouble(entities[index].second,42,&bulge);vertices.append({{x,y},bulge});} }
            QVector<QPointF> path; for(int i=0;i+1<vertices.size();++i)appendDxfSegment(&path,vertices[i],vertices[i+1].point,unit);
            if(vertices.size()==1)path.append(vertices.first().point); if(vertices.size()>1&&closed)appendDxfSegment(&path,vertices.last(),vertices.first().point,unit);
            if(!path.isEmpty())paths.append(path);
        } else if(type==QStringLiteral("CIRCLE")||type==QStringLiteral("ARC")) {
            double cx,cy,r;if(!dxfDouble(entity,10,&cx)||!dxfDouble(entity,20,&cy)||!dxfDouble(entity,40,&r)||r<=0)continue;
            double start=0,endAngle=2*Pi;if(type==QStringLiteral("ARC")){double a=0,b=0;if(!dxfDouble(entity,50,&a)||!dxfDouble(entity,51,&b))continue;start=a*Pi/180;endAngle=b*Pi/180;while(endAngle<start)endAngle+=2*Pi;}
            paths.append(dxfEllipse({cx,cy},{r,0},1,start,endAngle,unit));
        } else if(type==QStringLiteral("ELLIPSE")) {
            double cx,cy,mx,my,ratio,start=0,endAngle=2*Pi;
            if(dxfDouble(entity,10,&cx)&&dxfDouble(entity,20,&cy)&&dxfDouble(entity,11,&mx)&&dxfDouble(entity,21,&my)&&dxfDouble(entity,40,&ratio)) {
                dxfDouble(entity,41,&start);dxfDouble(entity,42,&endAngle);paths.append(dxfEllipse({cx,cy},{mx,my},ratio,start,endAngle,unit));
            }
        } else if(type!=QStringLiteral("SEQEND")&&type!=QStringLiteral("VERTEX")&&!type.isEmpty()) warnings<<QStringLiteral("Skipped unsupported DXF %1 entity.").arg(type);
    }
    if(paths.isEmpty())return fail(error,QStringLiteral("DXF contains no supported 2D drawing entities."));
    if(units==0)warnings<<QStringLiteral("DXF has no $INSUNITS value; millimetres were assumed.");
    double minX=0,maxX=0,minY=0,maxY=0; bool first=true;
    for(auto& path:paths)for(auto& p:path){
        p*=unit;
        if(first){minX=maxX=p.x();minY=maxY=p.y();first=false;}
        else {minX=std::min(minX,p.x());maxX=std::max(maxX,p.x());minY=std::min(minY,p.y());maxY=std::max(maxY,p.y());}
    }
    const QPointF center((minX+maxX)/2,(minY+maxY)/2); for(auto& path:paths)for(auto& p:path)p-=center;
    const double width=std::max(1.0,maxX-minX),height=std::max(1.0,maxY-minY);
    if(width>100000||height>100000)return fail(error,QStringLiteral("DXF dimensions exceed 100000 mm."));
    if(!DrawingProgram::validatePaths(paths,error))return false;
    warnings.removeDuplicates(); result->paths=paths;result->sizeMm={width,height};result->warnings=warnings;return true;
}

bool importFile(const QString& fileName, Result* result, QString* error)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))return fail(error,file.errorString());
    if(file.size()>MaxFileSize)return fail(error,QStringLiteral("Vector file exceeds 20 MB."));
    const QByteArray data=file.readAll(); const QString suffix=QFileInfo(fileName).suffix().toLower();
    if(suffix==QStringLiteral("svg"))return importSvg(data,result,error);
    if(suffix==QStringLiteral("dxf"))return importDxf(data,result,error);
    return fail(error,QStringLiteral("Unsupported vector format. Use SVG or ASCII DXF."));
}

} // namespace DrawingVectorImporter
