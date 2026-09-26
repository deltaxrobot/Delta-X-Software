#pragma once
#include "DrawingWidget.h"
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSlider>
#include <QTextEdit>
#include <QSettings>

class DrawingExporter : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingExporter(QWidget* parent);
    void SetDrawingParameterPointer(QLabel*, QLabel*, QLabel*, QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*, QSlider*, QCheckBox*, QComboBox*, QComboBox*);
    void SetGcodeExportParameterPointer(QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*);
    void SetDrawingPointInPlane(QLineEdit*, QLineEdit*, QLineEdit*);
    void SetDrawingAreaWidget(DrawingWidget*);
    void SetGcodeEditor(QTextEdit* editor) { m_editor=editor; }
    void SetEffector(QComboBox* effector) { m_effector=effector; }
    void SetupPanel(QWidget* page);
    void LoadSettings(QSettings*);
    void SaveSettings(QSettings*) const;
    QVariantMap parameters() const;
    void restoreParameters(const QVariantMap&);
    bool loadImage(const QString& fileName, QString* error);
    bool importVectorFile(const QString& fileName, QString* error, QString* notice = nullptr);
    bool convertImage(QString* error);
    bool generateProgram(QString* output, QString* error) const;
public slots:
    void OpenImage();
    void OpenVector();
    void ConvertToDrawingArea();
    void ConvertSVGToArea(QString fileName);
    void ExportGcodes();
    void ApplyConversion();
signals:
    void parametersChanged();
private:
    bool parsePoint(const QString&, QVector3D&) const;
    void updateSize();
    void refreshMarkers();
    void showError(const QString&);
    QImage m_original, m_effect;
    DrawingWidget* m_canvas=nullptr;
    QTextEdit* m_editor=nullptr;
    QLabel *m_preview=nullptr, *m_pixelWidth=nullptr, *m_pixelHeight=nullptr;
    QLineEdit *m_width=nullptr, *m_height=nullptr, *m_spacing=nullptr, *m_threshold=nullptr;
    QSlider* m_slider=nullptr;
    QCheckBox* m_inverse=nullptr;
    QComboBox *m_method=nullptr, *m_conversion=nullptr, *m_effector=nullptr;
    QLineEdit *m_travelZ=nullptr, *m_travelSpeed=nullptr, *m_drawingSpeed=nullptr, *m_acceleration=nullptr;
    QLineEdit *m_a=nullptr, *m_b=nullptr, *m_c=nullptr;
};
