#include "InspectionPlugin.h"

#include "DeltaXHostContext.h"

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

InspectionPlugin::~InspectionPlugin()
{
    delete m_panel;
}

QString InspectionPlugin::id() const
{
    return QStringLiteral("example.inspection");
}

QString InspectionPlugin::displayName() const
{
    return QStringLiteral("Reference Inspection");
}

QString InspectionPlugin::version() const
{
    return QStringLiteral("1.0.0");
}

QStringList InspectionPlugin::capabilities() const
{
    return {QStringLiteral("commands"), QStringLiteral("gscript.primitives"),
            QStringLiteral("panel"), QStringLiteral("services.provider")};
}

void InspectionPlugin::loadSettings(QSettings& settings)
{
    m_minimumConfidence = qBound(
        0.0, settings.value(QStringLiteral("minimumConfidence"), 0.8).toDouble(),
        1.0);
    m_lastTrackingId = qMax(
        0, settings.value(QStringLiteral("trackingId"), 0).toInt());
}

void InspectionPlugin::saveSettings(QSettings& settings) const
{
    settings.setValue(QStringLiteral("minimumConfidence"), m_minimumConfidence);
    settings.setValue(QStringLiteral("trackingId"), m_lastTrackingId);
}

bool InspectionPlugin::initialize(DeltaXHostContext* context, QString* error)
{
    if (!context) {
        if (error)
            *error = QStringLiteral("host context is required");
        return false;
    }
    m_context = context;
    return true;
}

bool InspectionPlugin::start(QString*)
{
    if (!m_context)
        return false;
    QString ignored;
    m_context->reportHealth(QStringLiteral("ready"),
                            QStringLiteral("Inspection provider is ready"),
                            {}, &ignored);
    m_context->publishEvent(QStringLiteral("inspection.started"), {}, &ignored);
    return true;
}

void InspectionPlugin::stop()
{
    if (!m_context)
        return;
    QString ignored;
    m_context->reportHealth(QStringLiteral("stopped"), {}, {}, &ignored);
}

QWidget* InspectionPlugin::panel()
{
    if (m_panel)
        return m_panel;

    m_panel = new QWidget;
    auto* root = new QVBoxLayout(m_panel);
    auto* explanation = new QLabel(
        QStringLiteral("Counts confirmed tracked objects at or above the "
                       "selected confidence threshold."),
        m_panel);
    explanation->setWordWrap(true);
    root->addWidget(explanation);

    auto* form = new QFormLayout;
    auto* tracking = new QSpinBox(m_panel);
    tracking->setRange(0, 999);
    tracking->setValue(m_lastTrackingId);
    auto* confidence = new QDoubleSpinBox(m_panel);
    confidence->setRange(0.0, 1.0);
    confidence->setSingleStep(0.05);
    confidence->setDecimals(2);
    confidence->setValue(m_minimumConfidence);
    form->addRow(QStringLiteral("Tracking ID"), tracking);
    form->addRow(QStringLiteral("Minimum confidence"), confidence);
    root->addLayout(form);

    auto* inspect = new QPushButton(QStringLiteral("Inspect Snapshot"), m_panel);
    m_status = new QLabel(QStringLiteral("No inspection has run."), m_panel);
    m_status->setWordWrap(true);
    root->addWidget(inspect);
    root->addWidget(m_status);
    root->addStretch();

    connect(tracking, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [this](int value) { m_lastTrackingId = value; });
    connect(confidence, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [this](double value) { m_minimumConfidence = value; });
    connect(inspect, &QPushButton::clicked,
            this, &InspectionPlugin::refreshPanel);
    return m_panel;
}

QVariantMap InspectionPlugin::evaluate(int trackingId,
                                       double minimumConfidence,
                                       QString* error) const
{
    if (!m_context) {
        if (error)
            *error = QStringLiteral("plugin is not initialized");
        return {};
    }
    const QVariantList objects = m_context->trackingSnapshot(trackingId, error);
    if (error && !error->isEmpty())
        return {};

    int accepted = 0;
    int confirmed = 0;
    for (const QVariant& value : objects) {
        const QVariantMap object = value.toMap();
        if (!object.value(QStringLiteral("confirmed")).toBool())
            continue;
        ++confirmed;
        if (object.value(QStringLiteral("confidence"), 1.0).toDouble() >=
            minimumConfidence)
            ++accepted;
    }
    return {
        {QStringLiteral("trackingId"), trackingId},
        {QStringLiteral("total"), objects.size()},
        {QStringLiteral("confirmed"), confirmed},
        {QStringLiteral("accepted"), accepted},
        {QStringLiteral("rejected"), confirmed - accepted},
        {QStringLiteral("minimumConfidence"), minimumConfidence},
    };
}

void InspectionPlugin::refreshPanel()
{
    QString error;
    const QVariantMap result = evaluate(
        m_lastTrackingId, m_minimumConfidence, &error);
    if (!m_status)
        return;
    if (!error.isEmpty()) {
        m_status->setText(QStringLiteral("Inspection failed: %1").arg(error));
        return;
    }
    m_status->setText(
        QStringLiteral("%1 accepted / %2 confirmed (%3 tracked)")
            .arg(result.value(QStringLiteral("accepted")).toInt())
            .arg(result.value(QStringLiteral("confirmed")).toInt())
            .arg(result.value(QStringLiteral("total")).toInt()));
}

bool InspectionPlugin::executeCommand(const QString& command,
                                      const QVariantMap& arguments,
                                      QVariantMap* result, QString* error)
{
    if (command != QStringLiteral("inspect")) {
        if (error)
            *error = QStringLiteral("unknown command");
        return false;
    }
    const QVariantMap evaluated = evaluate(
        arguments.value(QStringLiteral("trackingId"), m_lastTrackingId).toInt(),
        qBound(0.0,
               arguments.value(QStringLiteral("minimumConfidence"),
                               m_minimumConfidence).toDouble(),
               1.0),
        error);
    if (error && !error->isEmpty())
        return false;
    if (result)
        *result = evaluated;
    return true;
}

QVariantList InspectionPlugin::gscriptPrimitives() const
{
    return {QVariantMap{
        {QStringLiteral("name"), QStringLiteral("inspectioncount")},
        {QStringLiteral("signature"),
         QStringLiteral("M98 PinspectionCount(result, trackingId, minimumConfidence)")},
        {QStringLiteral("description"),
         QStringLiteral("Count confirmed objects that pass inspection")},
        {QStringLiteral("minArgs"), 3},
        {QStringLiteral("maxArgs"), 3},
        {QStringLiteral("resultArgument"), 0},
    }};
}

bool InspectionPlugin::executeGScriptPrimitive(
    const QString& name, const QVariantList& arguments, QVariant* result,
    QString* error)
{
    if (name != QStringLiteral("inspectioncount") || arguments.size() != 2) {
        if (error)
            *error = QStringLiteral("inspectionCount requires trackingId and confidence");
        return false;
    }
    const QVariantMap evaluated = evaluate(
        arguments.at(0).toInt(),
        qBound(0.0, arguments.at(1).toDouble(), 1.0), error);
    if (error && !error->isEmpty())
        return false;
    if (result)
        *result = evaluated.value(QStringLiteral("accepted"));
    return true;
}

QVariantList InspectionPlugin::services() const
{
    return {QVariantMap{
        {QStringLiteral("id"), QStringLiteral("inspection.quality")},
        {QStringLiteral("version"), QStringLiteral("1.0.0")},
        {QStringLiteral("methods"), QStringList{QStringLiteral("evaluate")}},
    }};
}

bool InspectionPlugin::invokeService(const QString& serviceId,
                                     const QString& method,
                                     const QVariantMap& request,
                                     QVariantMap* response, QString* error)
{
    if (serviceId != QStringLiteral("inspection.quality") ||
        method != QStringLiteral("evaluate")) {
        if (error)
            *error = QStringLiteral("unknown inspection service method");
        return false;
    }
    const QVariantMap evaluated = evaluate(
        request.value(QStringLiteral("trackingId"), m_lastTrackingId).toInt(),
        qBound(0.0,
               request.value(QStringLiteral("minimumConfidence"),
                             m_minimumConfidence).toDouble(),
               1.0),
        error);
    if (error && !error->isEmpty())
        return false;
    if (response)
        *response = evaluated;
    return true;
}
