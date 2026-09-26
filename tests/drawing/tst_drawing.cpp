#include <QtTest>
#include <QTemporaryDir>
#include <QFile>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSignalSpy>
#include <QMessageBox>
#include <QTimer>
#include <limits>
#include "DrawingProgram.h"
#include "DrawingVectorImporter.h"
#include "DrawingWidget.h"
#include "DrawingExporter.h"

using namespace DrawingProgram;
#ifndef Q_MOC_RUN
namespace {
Settings settings() {
    Settings s; s.a={0,0,-350}; s.b={100,0,-350}; s.c={0,100,-350}; s.travelZ=-340; return s;
}
struct Panel {
    QWidget page;
    DrawingExporter exporter{&page};
    DrawingWidget canvas{&page};
    QTextEdit editor{&page};
    QLabel preview{&page}, pw{&page}, ph{&page};
    QLineEdit w{"100",&page}, h{"100",&page}, spacing{"1",&page}, threshold{"150",&page};
    QSlider slider{Qt::Horizontal,&page};
    QCheckBox inverse{&page};
    QComboBox method{&page}, conversion{&page}, effector{&page};
    QLineEdit z{"-340",&page}, travel{&page}, speed{&page}, acceleration{&page};
    QLineEdit a{"0,0,-350",&page}, b{"100,0,-350",&page}, c{"0,100,-350",&page};
    Panel() {
        int i=0;
        for(auto* field:{&w,&h,&spacing,&threshold,&z,&travel,&speed,&acceleration,&a,&b,&c}) field->setObjectName(QString("field%1").arg(i++));
        method.setObjectName("method"); conversion.setObjectName("conversion"); effector.setObjectName("effector");
        method.addItems({"Line","Dot"}); effector.addItems({"Laser","Pen"});
        exporter.SetDrawingParameterPointer(&preview,&pw,&ph,&h,&w,&spacing,&threshold,&slider,&inverse,&method,&conversion);
        exporter.SetDrawingAreaWidget(&canvas); exporter.SetGcodeEditor(&editor);
        exporter.SetEffector(&effector);
        exporter.SetGcodeExportParameterPointer(&z,&travel,&speed,&acceleration);
        exporter.SetDrawingPointInPlane(&a,&b,&c);
    }
    void setup();
};
void writeFile(const QString& path,const QByteArray& bytes) { QFile f(path); QVERIFY(f.open(QIODevice::WriteOnly)); QCOMPARE(f.write(bytes),qint64(bytes.size())); }
QRectF pathBounds(const Paths& paths) {
    double minX=0,maxX=0,minY=0,maxY=0; bool first=true;
    for(const auto& path:paths) for(const auto& point:path) {
        if(first){minX=maxX=point.x();minY=maxY=point.y();first=false;}
        else {minX=std::min(minX,point.x());maxX=std::max(maxX,point.x());minY=std::min(minY,point.y());maxY=std::max(maxY,point.y());}
    }
    return {minX,minY,maxX-minX,maxY-minY};
}
}
#endif
class DrawingTest : public QObject {
    Q_OBJECT
private slots:
    void absoluteCoordinatesAndSafeMoves();
    void slopedPlane();
    void invalidInput_data();
    void invalidInput();
    void laserOffDuringTravel();
    void rasterRowsAndDimensions();
    void rasterRejectsDenseOrEmpty();
    void coordinatesSurviveViewChanges();
    void lineDragRegressionAndUndo();
    void shapes_data();
    void shapes();
    void documentRoundTripAndAtomicFailure();
    void imageAndSvgConversion();
    void nativeSvgImport();
    void nativeDxfImport();
    void vectorImportIsAtomic();
    void rejectMalformedPlaneAndRememberSettings();
    void panelLayout();
    void exportProtectsEditor();
};
void Panel::setup() {
        new QVBoxLayout(&page);
        for(const char* name:{"pbCursor","pbDrawLine","pbDrawRectangle","pbDrawCircle","pbDrawArc",
            "pbEraserAll","pbZoomOut","pbZoomIn","pbOpenPicture","pbPainting","pbExportDrawingGcodes"}) {
            auto* button=new QToolButton(&page); button->setObjectName(name);
        }
        for(const char* name:{"pbGetPlaneAPoint","pbGetPlaneBPoint","pbGetPlaneCPoint"}) {
            auto* button=new QPushButton(&page); button->setObjectName(name);
        }
        exporter.SetupPanel(&page);

}
void DrawingTest::absoluteCoordinatesAndSafeMoves() {
        auto s=settings(); s.travelSpeed=100; s.drawingSpeed=20;
        QString out,error;
        QVERIFY2(generate({{{10,20},{30,40}},{{-10,-20},{0,0}}},s,&out,&error),qPrintable(error));
        QVERIFY(out.contains("G90")); QVERIFY(!out.contains("G28"));
        QVERIFY(out.contains("G01 F100.000\nG01 Z-340.000\nG01 X10.000 Y20.000\nG01 F20.000"));
        QVERIFY(out.contains("G01 X30.000 Y40.000 Z-350.000\nG01 F100.000\nG01 Z-340.000"));
        QVERIFY(out.contains("G01 X-10.000 Y-20.000"));

}
void DrawingTest::slopedPlane() {
        auto s=settings(); s.b={100,0,-340}; s.travelZ=-320;
        QString out,error;
        QVERIFY(generate({{{0,0},{200,50}}},s,&out,&error));
        QVERIFY(out.contains("G01 X200.000 Y50.000 Z-330.000"));
        s.travelZ=-335; out="unchanged";
        QVERIFY(!generate({{{0,0},{200,50}}},s,&out,&error)); QCOMPARE(out,QString("unchanged"));

}
void DrawingTest::invalidInput_data() {
        QTest::addColumn<int>("kind");
        for(int i=0;i<9;++i) QTest::newRow(qPrintable(QString::number(i)))<<i;

}
void DrawingTest::invalidInput() {
        QFETCH(int,kind); auto s=settings(); Paths paths{{{0,0},{10,10}}};
        if(kind==0) paths.clear();
        if(kind==1) paths={{}};
        if(kind==2) paths[0][0].setX(std::numeric_limits<double>::quiet_NaN());
        if(kind==3) s.b=s.a;
        if(kind==4) s.c={200,0,-350};
        if(kind==5) { s.b={0,10,-350}; s.c={0,0,-340}; }
        if(kind==6) s.travelZ=-350;
        if(kind==7) s.drawingSpeed=0;
        if(kind==8) s.acceleration=std::numeric_limits<double>::infinity();
        QString out="keep",error; QVERIFY(!generate(paths,s,&out,&error)); QVERIFY(!error.isEmpty()); QCOMPARE(out,QString("keep"));

}
void DrawingTest::laserOffDuringTravel() {
        auto s=settings(); s.laser=true; QString out,error;
        QVERIFY(generate({{{0,0},{10,0}},{{20,20},{30,30}}},s,&out,&error));
        QVERIFY(out.indexOf("M03 S0")<out.indexOf("G01"));
        QCOMPARE(out.count("M03 S255"),2);
        QCOMPARE(out.split('\n').count("M03 S0"),3);
        QVERIFY(out.contains("Z-350.000\nM03 S255"));
        QVERIFY(out.contains("M03 S0\nG01 F100.000\nG01 Z-340.000"));
        QVERIFY(!out.contains("M360"));

}
void DrawingTest::rasterRowsAndDimensions() {
        QImage image(4,2,QImage::Format_RGB32); image.fill(Qt::black);
        Paths paths; QString error; QVERIFY(rasterPaths(image,40,20,10,false,&paths,&error));
        QCOMPARE(paths.size(),2); QCOMPARE(paths[0],(QVector<QPointF>{{-20,5},{20,5}}));
        QCOMPARE(paths[1],(QVector<QPointF>{{20,-5},{-20,-5}}));
        image.setPixelColor(1,0,Qt::white);
        QVERIFY(rasterPaths(image,40,20,10,false,&paths,&error)); QCOMPARE(paths.size(),3);
        QVERIFY(rasterPaths(image,40,20,10,true,&paths,&error)); QCOMPARE(paths.size(),7);

}
void DrawingTest::rasterRejectsDenseOrEmpty() {
        QImage image(4,4,QImage::Format_RGB32); image.fill(Qt::white);
        Paths paths{{{1,2}}}; QString error;
        QVERIFY(!rasterPaths(image,100,100,0,false,&paths,&error));
        QVERIFY(!rasterPaths(image,100,100,0.001,false,&paths,&error));
        QVERIFY(!rasterPaths(image,100,100,1,false,&paths,&error));
        QCOMPARE(paths,(Paths{{{1,2}}}));

}
void DrawingTest::coordinatesSurviveViewChanges() {
        DrawingWidget canvas; canvas.resize(800,400); canvas.SetPhysicalSize(100,100);
        const QPointF p(20,30);
        QVERIFY(QLineF(canvas.mapToLogical(canvas.mapToWidget(p)),p).length()<1e-6);
        const double dx=canvas.mapToWidget({10,0}).x()-canvas.mapToWidget({0,0}).x();
        const double dy=canvas.mapToWidget({0,0}).y()-canvas.mapToWidget({0,10}).y();
        QCOMPARE(dx,dy);
        canvas.replacePaths({{p,{0,0}}}); const auto original=canvas.paths();
        canvas.resize(350,700); canvas.SelectZoomInTool();
        QVERIFY(QLineF(canvas.mapToLogical(canvas.mapToWidget(p)),p).length()<1e-6);
        QCOMPARE(canvas.paths(),original); canvas.FitView(); QCOMPARE(canvas.paths(),original);

}
void DrawingTest::lineDragRegressionAndUndo() {
        DrawingWidget canvas; canvas.resize(500,400); canvas.show(); QTest::qWait(10);
        canvas.SelectLineTool();
        QTest::mousePress(&canvas,Qt::LeftButton,Qt::NoModifier,{100,100});
        QTest::mouseMove(&canvas,{150,180});
        QTest::mouseMove(&canvas,{180,190});
        QTest::mouseRelease(&canvas,Qt::LeftButton,Qt::NoModifier,{300,280});
        QCOMPARE(canvas.paths().size(),1);
        QCOMPARE(canvas.paths()[0].last(),canvas.mapToLogical({300,280}));
        canvas.Undo(); QVERIFY(canvas.paths().isEmpty()); canvas.Redo(); QCOMPARE(canvas.paths().size(),1);
        canvas.EraserAll(); QVERIFY(canvas.paths().isEmpty()); canvas.Undo(); QCOMPARE(canvas.paths().size(),1);

}
void DrawingTest::shapes_data() {
        QTest::addColumn<int>("tool");
        QTest::newRow("rectangle")<<0; QTest::newRow("circle")<<1; QTest::newRow("arc")<<2;

}
void DrawingTest::shapes() {
        QFETCH(int,tool); DrawingWidget canvas; canvas.resize(500,400); canvas.show();
        if(tool==0) canvas.SelectRectangleTool(); else if(tool==1) canvas.SelectCircleTool(); else canvas.SelectArcTool();
        QTest::mousePress(&canvas,Qt::LeftButton,Qt::NoModifier,{300,280});
        QTest::mouseMove(&canvas,{200,220});
        QTest::mouseRelease(&canvas,Qt::LeftButton,Qt::NoModifier,{100,100});
        QCOMPARE(canvas.paths().size(),1); const auto path=canvas.paths().first();
        if(tool<2) QCOMPARE(path.first(),path.last());
        else QCOMPARE(path.last(),canvas.mapToLogical({100,100}));
        QVERIFY(path.size()>=5);

}
void DrawingTest::documentRoundTripAndAtomicFailure() {
        QTemporaryDir temp; DrawingWidget canvas; canvas.SetPhysicalSize(120,80);
        const Paths paths{{{1.5,2.5},{3,4}},{{-5,6}}}; canvas.replacePaths(paths);
        QString error; QVERIFY(canvas.saveDrawing(temp.filePath("a.dxdraw"),&error));
        canvas.EraserAll(); QVERIFY(canvas.loadDrawing(temp.filePath("a.dxdraw"),&error));
        QCOMPARE(canvas.paths(),paths); QCOMPARE(canvas.physicalSize(),QSizeF(120,80));
        writeFile(temp.filePath("bad.dxdraw"),R"({"format":"delta-x-drawing","version":1,"width":100,"height":100,"paths":[[[1]]]} )");
        QVERIFY(!canvas.loadDrawing(temp.filePath("bad.dxdraw"),&error)); QCOMPARE(canvas.paths(),paths);
        canvas.Undo(); QVERIFY(canvas.paths().isEmpty());

}
void DrawingTest::imageAndSvgConversion() {
        Panel p; QTemporaryDir temp; QString error,out;
        QImage image(20,10,QImage::Format_ARGB32); image.fill(Qt::white);
        for(int y=2;y<8;++y) for(int x=2;x<18;++x) image.setPixelColor(x,y,Qt::black);
        QVERIFY(image.save(temp.filePath("image.png")));
        QVERIFY(p.exporter.loadImage(temp.filePath("image.png"),&error));
        p.conversion.setCurrentText("Vectorize");
        QVERIFY2(p.exporter.convertImage(&error),qPrintable(error)); QVERIFY(!p.canvas.paths().isEmpty());
        QCOMPARE(p.canvas.paths().first().first(),p.canvas.paths().first().last());
        QVERIFY(p.exporter.generateProgram(&out,&error));
        QVERIFY(!p.exporter.loadImage(temp.filePath("missing.png"),&error));
        writeFile(temp.filePath("test.SVG"),R"(<svg xmlns="http://www.w3.org/2000/svg" width="100" height="100"><rect x="10" y="10" width="80" height="80"/></svg>)");
        QVERIFY2(p.exporter.loadImage(temp.filePath("test.SVG"),&error),qPrintable(error));
        QVERIFY(p.exporter.convertImage(&error)); QVERIFY(!p.canvas.paths().isEmpty());

}
void DrawingTest::nativeSvgImport() {
    const QByteArray svg=R"SVG(<svg xmlns="http://www.w3.org/2000/svg" width="100mm" height="50mm" viewBox="0 0 100 50">
      <rect x="0" y="0" width="100" height="50"/>
      <circle cx="4.5" cy="4.5" r="1.5"/>
      <g transform="translate(10 5)"><path d="M0 0 C 10 0 10 10 20 10 A 5 5 0 0 1 25 15"/></g>
      <path d="M 5 40 h 10 v 5 h -10 z"/>
    </svg>)SVG";
    DrawingVectorImporter::Result result; QString error;
    QVERIFY2(DrawingVectorImporter::importSvg(svg,&result,&error),qPrintable(error));
    QCOMPARE(result.sizeMm,QSizeF(100,50));
    QVERIFY(result.paths.size()>=4);
    const QRectF bounds=pathBounds(result.paths);
    QVERIFY(std::abs(bounds.left()+50)<0.001);
    QVERIFY(std::abs(bounds.right()-50)<0.001);
    QVERIFY(std::abs(bounds.top()+25)<0.001);
    QVERIFY(std::abs(bounds.bottom()-25)<0.001);
    QVERIFY(result.paths.first().first()==result.paths.first().last());
    QVERIFY(QLineF(result.paths[2].first(),QPointF(-40,20)).length()<0.001);
}
void DrawingTest::nativeDxfImport() {
    const QByteArray dxf=
        "0\nSECTION\n2\nHEADER\n9\n$INSUNITS\n70\n4\n0\nENDSEC\n"
        "0\nSECTION\n2\nENTITIES\n"
        "0\nLWPOLYLINE\n70\n1\n10\n0\n20\n0\n10\n100\n20\n0\n10\n100\n20\n50\n10\n0\n20\n50\n"
        "0\nCIRCLE\n10\n4.5\n20\n4.5\n40\n1.5\n"
        "0\nLWPOLYLINE\n70\n0\n10\n10\n20\n10\n42\n1\n10\n20\n20\n10\n"
        "0\nENDSEC\n0\nEOF\n";
    DrawingVectorImporter::Result result; QString error;
    QVERIFY2(DrawingVectorImporter::importDxf(dxf,&result,&error),qPrintable(error));
    QCOMPARE(result.sizeMm,QSizeF(100,50));
    QCOMPARE(result.paths.size(),3);
    const QRectF bounds=pathBounds(result.paths);
    QVERIFY(std::abs(bounds.left()+50)<0.001);
    QVERIFY(std::abs(bounds.right()-50)<0.001);
    QVERIFY(std::abs(bounds.top()+25)<0.001);
    QVERIFY(std::abs(bounds.bottom()-25)<0.001);
    QVERIFY(result.paths[0].first()==result.paths[0].last());
    QVERIFY(result.paths[2].size()>10);
}
void DrawingTest::vectorImportIsAtomic() {
    Panel p; QTemporaryDir temp; QString error,notice;
    const Paths original{{{1,2},{3,4}}}; p.canvas.replacePaths(original);
    writeFile(temp.filePath("bad.svg"),"<svg><path d='M 0'/></svg>");
    QVERIFY(!p.exporter.importVectorFile(temp.filePath("bad.svg"),&error,&notice));
    QCOMPARE(p.canvas.paths(),original);
    writeFile(temp.filePath("drawing.svg"),R"(<svg xmlns="http://www.w3.org/2000/svg" width="20mm" height="10mm" viewBox="0 0 20 10"><line x1="0" y1="0" x2="20" y2="10"/></svg>)");
    QVERIFY2(p.exporter.importVectorFile(temp.filePath("drawing.svg"),&error,&notice),qPrintable(error));
    QCOMPARE(p.canvas.physicalSize(),QSizeF(20,10));
    QCOMPARE(p.canvas.paths().size(),1);
    QVERIFY(QLineF(p.canvas.paths().first().first(),QPointF(-10,5)).length()<0.001);
    QVERIFY(QLineF(p.canvas.paths().first().last(),QPointF(10,-5)).length()<0.001);
}
void DrawingTest::rejectMalformedPlaneAndRememberSettings() {
        Panel p; QString out,error; p.canvas.replacePaths({{{0,0},{10,10}}});
        p.a.setText("0,,0,-350"); QVERIFY(!p.exporter.generateProgram(&out,&error));
        p.a.setText("nan,0,-350"); QVERIFY(!p.exporter.generateProgram(&out,&error));
        p.a.setText("0,0,-350"); p.z.setText(""); QVERIFY(!p.exporter.generateProgram(&out,&error));
        p.z.setText("-330"); p.w.setText("125"); p.speed.setText("15");
        QTemporaryDir temp; QSettings settings(temp.filePath("drawing.ini"),QSettings::IniFormat);
        p.exporter.SaveSettings(&settings); p.w.setText("20"); p.speed.setText("5");
        p.exporter.LoadSettings(&settings); QCOMPARE(p.w.text(),QString("125")); QCOMPARE(p.speed.text(),QString("15"));

}
void DrawingTest::panelLayout() {
        Panel p; p.setup(); p.page.resize(960,720); p.page.show(); QTest::qWait(30);
        QVERIFY(p.canvas.isVisible()); QVERIFY(p.canvas.width()>=240);
        QCOMPARE(p.effector.currentText(),QString("Pen"));
        auto* importVector=p.page.findChild<QPushButton*>("pbImportVector");
        QVERIFY(importVector); QVERIFY(importVector->isVisible());
        auto* exportButton=p.page.findChild<QToolButton*>("pbExportDrawingGcodes");
        QVERIFY(exportButton); QVERIFY(!exportButton->isEnabled());
        p.canvas.replacePaths({{{-20,20},{20,-20}}}); QVERIFY(exportButton->isEnabled());
        const auto directory=qEnvironmentVariable("DRAWING_SCREENSHOT_DIR");
        if(!directory.isEmpty()) QVERIFY(p.page.grab().save(directory+"/drawing-panel.png"));
        p.page.resize(680,500); QTest::qWait(10);
        QVERIFY(p.canvas.width()>=240); QVERIFY(p.page.rect().contains(exportButton->mapTo(&p.page,exportButton->rect().bottomRight())));

}
void DrawingTest::exportProtectsEditor()
{
    Panel p; p.effector.setCurrentText("Pen");
    p.canvas.replacePaths({{{0,0},{10,10}}});
    p.editor.setPlainText("; existing program");
    QTimer dismiss;
    connect(&dismiss,&QTimer::timeout,this,[] {
        if(auto* box=qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            box->button(QMessageBox::Cancel)->click();
    });
    dismiss.start(5);
    p.exporter.ExportGcodes();
    dismiss.stop();
    QCOMPARE(p.editor.toPlainText(),QString("; existing program"));
    disconnect(&dismiss,nullptr,this,nullptr);
    connect(&dismiss,&QTimer::timeout,this,[] {
        if(auto* box=qobject_cast<QMessageBox*>(QApplication::activeModalWidget()))
            box->button(box->standardButtons().testFlag(QMessageBox::Yes) ? QMessageBox::Yes : QMessageBox::Ok)->click();
    });
    dismiss.start(5);
    p.exporter.ExportGcodes();
    dismiss.stop();
    QVERIFY(p.editor.toPlainText().contains("G01 X10.000 Y10.000"));
    p.editor.undo();
    QCOMPARE(p.editor.toPlainText(),QString("; existing program"));
    p.editor.setReadOnly(true);
    dismiss.start(5);
    p.exporter.ExportGcodes();
    dismiss.stop();
    QCOMPARE(p.editor.toPlainText(),QString("; existing program"));
}
QTEST_MAIN(DrawingTest)
#include "tst_drawing.moc"
