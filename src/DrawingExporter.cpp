#include "DrawingExporter.h"
#include "DrawingVectorImporter.h"
#include <QFileDialog>
#include <QImageReader>
#include <QSvgRenderer>
#include <QPainter>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QFileInfo>
#include <QToolButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QSplitter>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QTextBrowser>
#include <QDialog>
#include <QDialogButtonBox>
#include <opencv2/imgproc.hpp>
#if CV_VERSION_MAJOR >= 5
#include <opencv2/geometry.hpp>
#endif
#include <cmath>

DrawingExporter::DrawingExporter(QWidget* parent) : QWidget(parent) { hide(); }
void DrawingExporter::SetDrawingParameterPointer(QLabel* preview, QLabel* pw, QLabel* ph,
    QLineEdit* height, QLineEdit* width, QLineEdit* spacing, QLineEdit* threshold,
    QSlider* slider, QCheckBox* inverse, QComboBox* method, QComboBox* conversion)
{
    m_preview=preview; m_pixelWidth=pw; m_pixelHeight=ph; m_height=height; m_width=width;
    m_spacing=spacing; m_threshold=threshold; m_slider=slider; m_inverse=inverse;
    m_method=method; m_conversion=conversion;
    m_conversion->clear(); m_conversion->addItems({"Threshold","Vectorize"});
    m_slider->setRange(0,255);
    m_slider->setValue(m_threshold->text().toInt());
    m_threshold->setValidator(new QIntValidator(0,255,m_threshold));
    for(auto* field:{m_width,m_height,m_spacing}) {
        auto* validator=new QDoubleValidator(0.001,100000,3,field);
        validator->setLocale(QLocale::c()); validator->setNotation(QDoubleValidator::StandardNotation);
        field->setValidator(validator);
    }
    connect(m_slider,&QSlider::valueChanged,this,[this](int value) {
        m_threshold->setText(QString::number(value));
    });
    connect(m_slider,&QSlider::sliderReleased,this,&DrawingExporter::ApplyConversion);
    connect(m_threshold,&QLineEdit::editingFinished,this,[this] {
        if(m_threshold->hasAcceptableInput()) { m_slider->setValue(m_threshold->text().toInt()); ApplyConversion(); }
    });
    connect(m_width,&QLineEdit::editingFinished,this,&DrawingExporter::updateSize);
    connect(m_height,&QLineEdit::editingFinished,this,&DrawingExporter::updateSize);
    connect(m_conversion,&QComboBox::currentTextChanged,this,&DrawingExporter::ApplyConversion);
    connect(m_inverse,&QCheckBox::toggled,this,&DrawingExporter::ApplyConversion);
}
void DrawingExporter::SetGcodeExportParameterPointer(QLineEdit* z,QLineEdit* travel,QLineEdit* draw,QLineEdit* acceleration)
{
    m_travelZ=z; m_travelSpeed=travel; m_drawingSpeed=draw; m_acceleration=acceleration;
    for(auto* field:{z,travel,draw,acceleration}) {
        auto* validator=new QDoubleValidator(field); validator->setLocale(QLocale::c());
        validator->setNotation(QDoubleValidator::StandardNotation); field->setValidator(validator);
    }
    travel->setText("100"); draw->setText("20"); acceleration->setText("500");
    z->setPlaceholderText(tr("Absolute robot Z"));
}
void DrawingExporter::SetDrawingPointInPlane(QLineEdit* a,QLineEdit* b,QLineEdit* c)
{
    m_a=a; m_b=b; m_c=c;
    for(auto* field:{a,b,c}) {
        field->setPlaceholderText("X, Y, Z");
        connect(field,&QLineEdit::textChanged,this,&DrawingExporter::refreshMarkers);
    }
}
void DrawingExporter::SetDrawingAreaWidget(DrawingWidget* canvas)
{
    m_canvas=canvas; updateSize();
    connect(canvas,&DrawingWidget::physicalSizeChanged,this,[this] {
        m_width->setText(QString::number(m_canvas->physicalSize().width()));
        m_height->setText(QString::number(m_canvas->physicalSize().height()));
    });
}
void DrawingExporter::updateSize()
{
    if(m_canvas) m_canvas->SetPhysicalSize(m_width->text().toFloat(),m_height->text().toFloat());
}
bool DrawingExporter::parsePoint(const QString& text,QVector3D& point) const
{
    const auto parts=text.split(',',Qt::KeepEmptyParts);
    if(parts.size()!=3) return false;
    float values[3];
    for(int i=0;i<3;++i) {
        bool ok=false; values[i]=parts[i].trimmed().toFloat(&ok);
        if(!ok || !std::isfinite(values[i]) || std::abs(values[i])>100000) return false;
    }
    point={values[0],values[1],values[2]}; return true;
}
void DrawingExporter::refreshMarkers()
{
    if(!m_canvas) return;
    QVector3D a,b,c;
    if(parsePoint(m_a->text(),a) && parsePoint(m_b->text(),b) && parsePoint(m_c->text(),c))
        m_canvas->SetPlaneMarkers({{a.x(),a.y()},{b.x(),b.y()},{c.x(),c.y()}});
    else m_canvas->SetPlaneMarkers({});
}
void DrawingExporter::showError(const QString& error) { QMessageBox::warning(this,tr("Drawing"),error); }
bool DrawingExporter::loadImage(const QString& fileName,QString* error)
{
    auto fail=[&](const QString& message) { if(error)*error=message; return false; };
    QImage image;
    if(QFileInfo(fileName).size()>20000000) return fail(tr("Image file exceeds 20 MB."));
    if(QFileInfo(fileName).suffix().compare("svg",Qt::CaseInsensitive)==0) {
        QSvgRenderer svg(fileName);
        if(!svg.isValid() || svg.defaultSize().isEmpty()) return fail(tr("Invalid SVG image."));
        const QSize size=svg.defaultSize().scaled(1600,1600,Qt::KeepAspectRatio);
        image=QImage(size,QImage::Format_ARGB32); image.fill(Qt::white);
        QPainter painter(&image); svg.render(&painter);
    } else {
        QImageReader reader(fileName); reader.setAutoTransform(true);
        if(!reader.size().isValid() || qint64(reader.size().width())*reader.size().height()>64000000)
            return fail(tr("Invalid image or image larger than 64 megapixels."));
        if(reader.size().width()>1600 || reader.size().height()>1600)
            reader.setScaledSize(reader.size().scaled(1600,1600,Qt::KeepAspectRatio));
        image=reader.read();
        if(image.isNull()) return fail(reader.errorString());
    }
    if(image.isNull()) return fail(tr("Could not load image."));
    // Composite transparency onto white; semitransparent antialiased edges remain correct.
    m_original=QImage(image.size(),QImage::Format_RGB32); m_original.fill(Qt::white);
    { QPainter painter(&m_original); painter.drawImage(0,0,image); }
    ApplyConversion(); return true;
}
void DrawingExporter::OpenImage()
{
    const auto file=QFileDialog::getOpenFileName(this,tr("Load Image"),{},tr("Raster images (*.png *.jpg *.jpeg *.bmp)"));
    if(file.isEmpty()) return;
    QString error; if(!loadImage(file,&error)) showError(error);
}
bool DrawingExporter::importVectorFile(const QString& fileName,QString* error,QString* notice)
{
    if(!m_canvas) { if(error)*error=tr("Drawing canvas is unavailable."); return false; }
    DrawingVectorImporter::Result imported;
    if(!DrawingVectorImporter::importFile(fileName,&imported,error)) return false;
    m_canvas->replacePaths(imported.paths);
    m_canvas->SetPhysicalSize(imported.sizeMm.width(),imported.sizeMm.height());
    m_canvas->FitView();
    if(notice) *notice=imported.warnings.join('\n');
    return true;
}
void DrawingExporter::OpenVector()
{
    const auto file=QFileDialog::getOpenFileName(this,tr("Import Vector"),{},tr("Vector drawings (*.svg *.dxf)"));
    if(file.isEmpty()) return;
    if(!m_canvas->paths().isEmpty() && QMessageBox::question(this,tr("Import Vector"),
       tr("Replace the current paths with this vector drawing? You can undo this change."),
       QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel)!=QMessageBox::Yes) return;
    QString error,notice;
    if(!importVectorFile(file,&error,&notice)) { showError(error); return; }
    if(!notice.isEmpty()) QMessageBox::information(this,tr("Vector Import"),notice);
}
void DrawingExporter::ConvertSVGToArea(QString fileName)
{
    QString error; if(!loadImage(fileName,&error)) showError(error);
}
void DrawingExporter::ApplyConversion()
{
    if(m_method) m_method->setEnabled(m_conversion->currentIndex()==0);
    if(m_original.isNull()) return;
    m_effect=QImage(m_original.size(),QImage::Format_Grayscale8);
    const int threshold=m_slider->value();
    for(int y=0;y<m_original.height();++y) {
        auto* row=m_effect.scanLine(y);
        for(int x=0;x<m_original.width();++x) {
            bool black=qGray(m_original.pixel(x,y))<threshold;
            if(m_inverse->isChecked()) black=!black;
            row[x]=black ? 0 : 255;
        }
    }
    m_preview->setPixmap(QPixmap::fromImage(m_effect).scaled(260,150,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    m_pixelWidth->setText(tr("%1 × %2 px").arg(m_original.width()).arg(m_original.height()));
}
bool DrawingExporter::convertImage(QString* error)
{
    auto fail=[&](const QString& message) { if(error)*error=message; return false; };
    if(!m_canvas || m_effect.isNull()) return fail(tr("Load an image first."));
    bool okW=false,okH=false,okS=false;
    const double w=m_width->text().toDouble(&okW), h=m_height->text().toDouble(&okH), spacing=m_spacing->text().toDouble(&okS);
    if(!okW || !okH || !okS || !std::isfinite(w) || !std::isfinite(h) || !std::isfinite(spacing) ||
       w<=0 || h<=0 || w>100000 || h>100000 || spacing<=0)
        return fail(tr("Enter positive width, height and spacing."));
    DrawingProgram::Paths paths;
    if(m_conversion->currentIndex()==1) {
        try {
            cv::Mat gray(m_effect.height(),m_effect.width(),CV_8UC1,m_effect.bits(),m_effect.bytesPerLine());
            cv::Mat ink; cv::bitwise_not(gray,ink);
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(ink,contours,cv::RETR_LIST,cv::CHAIN_APPROX_SIMPLE);
            for(const auto& contour:contours) {
                if(contour.size()<3) continue;
                std::vector<cv::Point> approx;
                cv::approxPolyDP(contour,approx,0.5,true);
                if(approx.size()<3) continue;
                QVector<QPointF> path;
                for(const auto& p:approx) path.append(QPointF((p.x+0.5)*w/m_effect.width()-w/2,h/2-(p.y+0.5)*h/m_effect.height()));
                path.append(path.first()); paths.append(path);
            }
        } catch(const cv::Exception&) { return fail(tr("Image conversion failed. Try a smaller image.")); }
        if(!DrawingProgram::validatePaths(paths,error)) return false;
    } else if(!DrawingProgram::rasterPaths(m_effect,w,h,spacing,m_method->currentText()=="Dot",&paths,error)) return false;
    m_canvas->replacePaths(paths); updateSize(); m_canvas->FitView(); return true;
}
void DrawingExporter::ConvertToDrawingArea()
{
    if(!m_canvas->paths().isEmpty() && QMessageBox::question(this,tr("Replace Drawing"),
       tr("Replace the current paths with this image? You can undo this change."),
       QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel)!=QMessageBox::Yes) return;
    QString error; if(!convertImage(&error)) showError(error);
}
bool DrawingExporter::generateProgram(QString* output,QString* error) const
{
    auto fail=[&](const QString& message) { if(error)*error=message; return false; };
    if(!m_canvas) return fail(tr("Drawing canvas is unavailable."));
    DrawingProgram::Settings s;
    if(!parsePoint(m_a->text(),s.a) || !parsePoint(m_b->text(),s.b) || !parsePoint(m_c->text(),s.c))
        return fail(tr("Enter valid X, Y, Z coordinates for plane points A, B and C."));
    bool ok=false;
    auto read=[&](QLineEdit* field,double& value) { value=field->text().toDouble(&ok); return ok && std::isfinite(value); };
    if(!read(m_travelZ,s.travelZ) || !read(m_travelSpeed,s.travelSpeed) ||
       !read(m_drawingSpeed,s.drawingSpeed) || !read(m_acceleration,s.acceleration))
        return fail(tr("Enter Travel Z, travel speed, drawing speed and acceleration."));
    s.laser=m_effector && m_effector->currentText()=="Laser";
    return DrawingProgram::generate(m_canvas->paths(),s,output,error);
}
void DrawingExporter::ExportGcodes()
{
    QString output,error;
    if(!generateProgram(&output,&error)) { showError(error); return; }
    if(!m_editor) return;
    if(m_editor->isReadOnly()) {
        showError(tr("The G-code Editor is locked. Stop the running program before replacing it."));
        return;
    }
    if(m_effector->currentText()=="Laser" && QMessageBox::warning(this,tr("Laser Output"),
       tr("This program uses M03 S255 for full power and M03 S0 for off. Verify firmware, laser configuration and safety interlocks before running."),
       QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)!=QMessageBox::Ok) return;
    if(!m_editor->toPlainText().trimmed().isEmpty() && QMessageBox::question(this,tr("Replace G-code"),
       tr("Replace the G-code Editor contents with the drawing program?"),
       QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel)!=QMessageBox::Yes) return;
    // Keep editor undo history, so an accidental replacement is recoverable.
    auto cursor=m_editor->textCursor(); cursor.beginEditBlock(); cursor.select(QTextCursor::Document);
    cursor.insertText(output); cursor.endEditBlock(); m_editor->setTextCursor(cursor);
    QMessageBox::information(this,tr("Drawing"),tr("G-code is ready in the Program editor. No robot commands were sent."));
}

void DrawingExporter::SaveSettings(QSettings* settings) const
{
    settings->beginGroup("Drawing");
    settings->setValue("SchemaVersion",2);
    for(auto* field:{m_width,m_height,m_spacing,m_threshold,m_travelZ,m_travelSpeed,m_drawingSpeed,m_acceleration,m_a,m_b,m_c})
        settings->setValue(field->objectName(),field->text());
    for(auto* combo:{m_method,m_conversion,m_effector}) settings->setValue(combo->objectName(),combo->currentText());
    settings->setValue("Inverse",m_inverse->isChecked());
    settings->endGroup();
}
void DrawingExporter::LoadSettings(QSettings* settings)
{
    settings->beginGroup("Drawing");
    if(settings->value("SchemaVersion").toInt()==2) {
        for(auto* field:{m_width,m_height,m_spacing,m_threshold,m_travelZ,m_travelSpeed,m_drawingSpeed,m_acceleration,m_a,m_b,m_c})
            field->setText(settings->value(field->objectName(),field->text()).toString());
        for(auto* combo:{m_method,m_conversion,m_effector}) {
            const int index=combo->findText(settings->value(combo->objectName(),combo->currentText()).toString());
            if(index>=0) combo->setCurrentIndex(index);
        }
        m_inverse->setChecked(settings->value("Inverse",false).toBool());
        m_slider->setValue(m_threshold->text().toInt()); updateSize(); refreshMarkers();
    }
    settings->endGroup();
}

QVariantMap DrawingExporter::parameters() const
{
    QVariantMap values{{"SchemaVersion",2},{"Inverse",m_inverse->isChecked()}};
    for(auto* field:{m_width,m_height,m_spacing,m_threshold,m_travelZ,m_travelSpeed,m_drawingSpeed,m_acceleration,m_a,m_b,m_c})
        values.insert(field->objectName(),field->text());
    for(auto* combo:{m_method,m_conversion,m_effector}) values.insert(combo->objectName(),combo->currentText());
    return values;
}
void DrawingExporter::restoreParameters(const QVariantMap& values)
{
    if(values.value("SchemaVersion").toInt()!=2) return;
    QSignalBlocker guard(this);
    for(auto* field:{m_width,m_height,m_spacing,m_threshold,m_travelZ,m_travelSpeed,m_drawingSpeed,m_acceleration,m_a,m_b,m_c})
        field->setText(values.value(field->objectName(),field->text()).toString());
    for(auto* combo:{m_method,m_conversion,m_effector}) {
        const int index=combo->findText(values.value(combo->objectName(),combo->currentText()).toString());
        if(index>=0) combo->setCurrentIndex(index);
    }
    m_inverse->setChecked(values.value("Inverse",false).toBool());
    m_slider->setValue(m_threshold->text().toInt()); updateSize(); refreshMarkers();
}

void DrawingExporter::SetupPanel(QWidget* page)
{
    // Reuse existing controls and signal identities; retire the unused legacy fields.
    auto* content=new QWidget(page);
    auto* root=new QVBoxLayout(content); root->setContentsMargins(8,8,8,8); root->setSpacing(8);
    auto* toolbar=new QHBoxLayout; toolbar->setSpacing(6);
    auto adoptButton=[&](const char* name,const QString& text) {
        auto* button=page->findChild<QToolButton*>(name);
        button->setParent(content); button->setText(text); button->setToolTip(text);
        button->setAccessibleName(text); button->setMinimumSize(30,30); button->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
        button->setToolButtonStyle(Qt::ToolButtonTextOnly); button->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
        button->setShortcut(QKeySequence()); return button;
    };
    auto* group=new QButtonGroup(content); group->setExclusive(true);
    const QList<QPair<const char*,QString>> tools={{"pbCursor",tr("Pan")},{"pbDrawLine",tr("Line")},
        {"pbDrawRectangle",tr("Rectangle")},{"pbDrawCircle",tr("Circle")},{"pbDrawArc",tr("Arc")}};
    for(const auto& tool:tools) {
        auto* b=adoptButton(tool.first,tool.second); b->setCheckable(true); group->addButton(b); toolbar->addWidget(b);
        if(tool.first==tools.first().first) b->setChecked(true);
        if(QString(tool.first)=="pbDrawArc") b->setToolTip(tr("Drag the diameter of a counterclockwise semicircle."));
    }
    toolbar->addStretch();
    root->addLayout(toolbar);
    auto* actions=new QHBoxLayout; actions->setSpacing(6);
    auto addAction=[&](const QString& text,auto callback) {
        auto* b=new QPushButton(text,content); b->setAccessibleName(text); actions->addWidget(b);
        connect(b,&QPushButton::clicked,this,callback); return b;
    };
    auto* undo=addAction(tr("Undo"),[this]{m_canvas->Undo();});
    auto* redo=addAction(tr("Redo"),[this]{m_canvas->Redo();});
    actions->addWidget(adoptButton("pbEraserAll",tr("Clear")));
    auto* zoomOut=adoptButton("pbZoomOut",tr("−"));
    zoomOut->setToolTip(tr("Zoom out")); zoomOut->setAccessibleName(tr("Zoom out")); actions->addWidget(zoomOut);
    auto* zoomIn=adoptButton("pbZoomIn",tr("+"));
    zoomIn->setToolTip(tr("Zoom in")); zoomIn->setAccessibleName(tr("Zoom in")); actions->addWidget(zoomIn);
    addAction(tr("Fit"),[this]{m_canvas->FitView();});
    actions->addStretch();
    root->addLayout(actions);
    auto* splitter=new QSplitter(Qt::Horizontal,content); splitter->setChildrenCollapsible(false);
    m_canvas->setParent(splitter); m_canvas->setStyleSheet({}); m_canvas->setMinimumSize(240,240);
    m_canvas->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX); m_canvas->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    auto* scroll=new QScrollArea(splitter); scroll->setWidgetResizable(true); scroll->setMinimumWidth(280);
    auto* settings=new QWidget; auto* forms=new QVBoxLayout(settings); forms->setContentsMargins(8,0,8,0); forms->setSpacing(12);
    auto section=[&](const QString& name) {
        auto* box=new QGroupBox(name,settings); auto* form=new QFormLayout(box);
        form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        form->setRowWrapPolicy(QFormLayout::WrapLongRows); form->setSpacing(8); forms->addWidget(box); return form;
    };
    auto field=[&](QWidget* widget) {
        widget->setParent(settings); widget->setMinimumWidth(0); widget->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
        widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed); widget->show(); return widget;
    };
    auto* image=section(tr("Image"));
    image->addRow(adoptButton("pbOpenPicture",tr("Load Image…")));
    m_preview->setParent(settings); m_preview->setScaledContents(false); m_preview->setAlignment(Qt::AlignCenter);
    m_preview->setMinimumSize(0,150); m_preview->setMaximumSize(QWIDGETSIZE_MAX,150); m_preview->setStyleSheet({});
    m_preview->setText(tr("No image")); image->addRow(m_preview);
    m_pixelWidth->setText({}); image->addRow(field(m_pixelWidth));
    image->addRow(tr("Conversion"),field(m_conversion));
    auto* threshold=new QWidget(settings); auto* thresholdRow=new QHBoxLayout(threshold); thresholdRow->setContentsMargins(0,0,0,0);
    thresholdRow->addWidget(field(m_slider)); m_threshold->setMaximumWidth(64); thresholdRow->addWidget(field(m_threshold));
    image->addRow(tr("Threshold"),threshold);
    m_inverse->setText(tr("Invert")); image->addRow(field(m_inverse));
    image->addRow(tr("Raster"),field(m_method)); image->addRow(tr("Spacing (mm)"),field(m_spacing));
    auto* vector=section(tr("Vector"));
    auto* importVector=new QPushButton(tr("Import SVG / DXF…"),settings);
    importVector->setObjectName(QStringLiteral("pbImportVector"));
    importVector->setAccessibleName(tr("Import vector drawing"));
    importVector->setToolTip(tr("Import native SVG or ASCII DXF paths without raster conversion."));
    vector->addRow(field(importVector));
    connect(importVector,&QPushButton::clicked,this,&DrawingExporter::OpenVector);
    auto* size=section(tr("Canvas Size"));
    size->addRow(tr("Width (mm)"),field(m_width)); size->addRow(tr("Height (mm)"),field(m_height));
    m_width->setToolTip(tr("Canvas width. Raster conversion uses this size; existing paths retain their millimetre coordinates."));
    m_height->setToolTip(m_width->toolTip());
    size->addRow(adoptButton("pbPainting",tr("Convert to Paths")));
    auto* plane=section(tr("Drawing Plane"));
    const QList<QPair<QLineEdit*,const char*>> points={{m_a,"pbGetPlaneAPoint"},{m_b,"pbGetPlaneBPoint"},{m_c,"pbGetPlaneCPoint"}};
    for(int i=0;i<points.size();++i) {
        auto* row=new QWidget(settings); auto* layout=new QHBoxLayout(row); layout->setContentsMargins(0,0,0,0);
        layout->addWidget(field(points[i].first));
        auto* paste=page->findChild<QPushButton*>(points[i].second); field(paste);
        paste->setText(tr("Paste")); paste->setToolTip(tr("Paste copied robot coordinates.")); layout->addWidget(paste);
        plane->addRow(QString(QChar('A'+i)),row);
    }
    auto* motion=section(tr("Tool & Motion"));
    m_effector->setCurrentText("Pen");
    motion->addRow(tr("Tool"),field(m_effector)); motion->addRow(tr("Travel Z (mm)"),field(m_travelZ));
    m_travelZ->setToolTip(tr("Absolute robot Z above every path, within the robot workspace. Drawing Z comes from plane A/B/C."));
    motion->addRow(tr("Travel (mm/s)"),field(m_travelSpeed));
    motion->addRow(tr("Drawing (mm/s)"),field(m_drawingSpeed));
    motion->addRow(tr("Acceleration (mm/s²)"),field(m_acceleration));
    forms->addStretch(); scroll->setWidget(settings);
    splitter->setStretchFactor(0,1); splitter->setStretchFactor(1,0); splitter->setSizes({600,310});
    root->addWidget(splitter,1);
    auto* files=new QHBoxLayout; files->setSpacing(6);
    auto fileAction=[&](const QString& text,auto callback) {
        auto* b=new QPushButton(text,content); files->addWidget(b); connect(b,&QPushButton::clicked,this,callback);
    };
    fileAction(tr("Open Drawing…"),[this] {
        const auto path=QFileDialog::getOpenFileName(this,tr("Open Drawing"),{},tr("Delta X Drawing (*.dxdraw)"));
        if(path.isEmpty()) return;
        if(!m_canvas->paths().isEmpty() && QMessageBox::question(this,tr("Open Drawing"),
            tr("Replace current paths? Unsaved changes can be recovered with Undo."),
            QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel)!=QMessageBox::Yes) return;
        QString error; if(!m_canvas->loadDrawing(path,&error)) showError(error);
    });
    fileAction(tr("Save Drawing…"),[this] {
        QFileDialog dialog(this,tr("Save Drawing"),{},tr("Delta X Drawing (*.dxdraw)"));
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setDefaultSuffix("dxdraw");
        if(dialog.exec()!=QDialog::Accepted || dialog.selectedFiles().isEmpty()) return;
        const auto path=dialog.selectedFiles().first();
        QString error; if(!m_canvas->saveDrawing(path,&error)) showError(error);
    });
    fileAction(tr("Help"),[this] {
        QDialog dialog(this); dialog.setWindowTitle(tr("Drawing Guide")); dialog.resize(760,620);
        auto* layout=new QVBoxLayout(&dialog); auto* browser=new QTextBrowser(&dialog);
        QFile file(":/docs/drawing.md"); if(file.open(QIODevice::ReadOnly)) browser->setMarkdown(QString::fromUtf8(file.readAll()));
        layout->addWidget(browser); auto* buttons=new QDialogButtonBox(QDialogButtonBox::Close,&dialog);
        connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject); layout->addWidget(buttons); dialog.exec();
    });
    files->addStretch();
    auto* exportButton=adoptButton("pbExportDrawingGcodes",tr("Send to G-code Editor"));
    exportButton->setProperty("controlRole","primary"); files->addWidget(exportButton);
    root->addLayout(files);
    auto updateActions=[this,undo,redo,exportButton] {
        undo->setEnabled(m_canvas->canUndo()); redo->setEnabled(m_canvas->canRedo());
        exportButton->setEnabled(!m_canvas->paths().isEmpty());
    };
    connect(m_canvas,&DrawingWidget::pathsChanged,this,updateActions); updateActions();
    const auto oldChildren=page->findChildren<QWidget*>(QString(),Qt::FindDirectChildrenOnly);
    for(auto* child:oldChildren) if(child!=content) child->hide();
    delete page->layout();
    auto* layout=new QVBoxLayout(page); layout->setContentsMargins(0,0,0,0); layout->addWidget(content);
    content->show();
    for(auto* edit:{m_width,m_height,m_spacing,m_threshold,m_travelZ,m_travelSpeed,m_drawingSpeed,m_acceleration,m_a,m_b,m_c})
        connect(edit,&QLineEdit::textChanged,this,&DrawingExporter::parametersChanged);
    for(auto* combo:{m_method,m_conversion,m_effector})
        connect(combo,&QComboBox::currentTextChanged,this,&DrawingExporter::parametersChanged);
    connect(m_inverse,&QCheckBox::toggled,this,&DrawingExporter::parametersChanged);
}
