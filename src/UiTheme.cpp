#include "UiTheme.h"

#include <QAbstractButton>
#include <QAbstractScrollArea>
#include <QAbstractSpinBox>
#include <QApplication>
#include <QColor>
#include <QComboBox>
#include <QFont>
#include <QFontDatabase>
#include <QGroupBox>
#include <QIconEngine>
#include <QLayout>
#include <QLineEdit>
#include <QList>
#include <QPainter>
#include <QPalette>
#include <QPointer>
#include <QPushButton>
#include <QRegularExpression>
#include <QScrollArea>
#include <QStyle>
#include <QStyleFactory>
#include <QToolButton>
#include <QWidget>

namespace
{
// Tint only explicitly monochrome navigation artwork, not camera/robot icons.
// Resolve the color at paint time so theme switches and selection stay correct.
class NavigationIconEngine final : public QIconEngine
{
  public:
    NavigationIconEngine(const QIcon& source, QAbstractButton* button)
        : m_source(source), m_button(button)
    {
    }
    QIconEngine* clone() const override
    {
        return new NavigationIconEngine(m_source, m_button);
    }
    QPixmap scaledPixmap(const QSize& size, QIcon::Mode mode, QIcon::State state,
                         qreal scale) override
    {
        QPixmap pixmap = m_source.pixmap(size, scale, QIcon::Normal, state);
        if (pixmap.isNull())
            return pixmap;
        const QPalette palette = qApp->palette();
        const bool selected = m_button && (m_button->property("navigationSelected").toBool() ||
                                           m_button->isDown() || state == QIcon::On);
        const QColor color =
            mode == QIcon::Disabled
                ? palette.color(QPalette::Disabled, QPalette::ButtonText)
                : palette.color(selected ? QPalette::HighlightedText : QPalette::ButtonText);
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(pixmap.rect(), color);
        return pixmap;
    }
    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) override
    {
        return scaledPixmap(size, mode, state, 1.0);
    }
    void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) override
    {
        painter->drawPixmap(
            rect, scaledPixmap(rect.size(), mode, state, painter->device()->devicePixelRatioF()));
    }

  private:
    QIcon m_source;
    QPointer<QAbstractButton> m_button;
};

bool hasColoredArtwork(const QPixmap& pixmap)
{
    const QImage image = pixmap.toImage().convertToFormat(QImage::Format_ARGB32);
    int visiblePixels = 0;
    int coloredPixels = 0;
    for (int y = 0; y < image.height(); ++y)
    {
        const QRgb* row = reinterpret_cast<const QRgb*>(image.constScanLine(y));
        for (int x = 0; x < image.width(); ++x)
        {
            const QColor pixel = QColor::fromRgba(row[x]);
            if (pixel.alpha() < 32)
                continue;
            ++visiblePixels;
            if (pixel.hsvSaturation() >= 32)
                ++coloredPixels;
        }
    }
    return visiblePixels > 0 && coloredPixels >= qMax(1, visiblePixels / 50);
}

// Tint only truly monochrome artwork. Colored illustrations are rendered
// exactly as supplied, without recoloring, outlines or other decoration.
class ButtonIconEngine final : public QIconEngine
{
  public:
    ButtonIconEngine(const QIcon& source, QAbstractButton* button)
        : m_source(source), m_button(button)
    {
    }
    QIconEngine* clone() const override
    {
        return new ButtonIconEngine(m_source, m_button);
    }
    QPixmap scaledPixmap(const QSize& size, QIcon::Mode mode, QIcon::State state,
                         qreal scale) override
    {
        QPixmap pixmap = m_source.pixmap(size, scale, QIcon::Normal, state);
        if (pixmap.isNull())
            return pixmap;

        const QPalette palette = qApp->palette();
        QColor color;
        if (mode == QIcon::Disabled || (m_button && !m_button->isEnabled()))
        {
            color = palette.color(QPalette::Disabled, QPalette::ButtonText);
        }
        else
        {
            const QString role =
                m_button ? m_button->property("controlRole").toString() : QString();
            const bool filledRole = !role.isEmpty() && role != QStringLiteral("quiet");
            const auto* pushButton = qobject_cast<QPushButton*>(m_button.data());
            const bool filledState =
                m_button && (m_button->isDown() || m_button->isChecked() || state == QIcon::On ||
                             m_button->property("navigationSelected").toBool() || filledRole ||
                             (pushButton && pushButton->isDefault()));
            color = palette.color(filledState ? QPalette::HighlightedText : QPalette::ButtonText);
        }

        if (hasColoredArtwork(pixmap))
            return pixmap;

        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(pixmap.rect(), color);
        return pixmap;
    }
    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) override
    {
        return scaledPixmap(size, mode, state, 1.0);
    }
    void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) override
    {
        painter->drawPixmap(
            rect, scaledPixmap(rect.size(), mode, state, painter->device()->devicePixelRatioF()));
    }

  private:
    QIcon m_source;
    QPointer<QAbstractButton> m_button;
};

struct ThemeTokens
{
    QString window;
    QString surface;
    QString raised;
    QString input;
    QString border;
    QString borderStrong;
    QString text;
    QString muted;
    QString disabled;
    QString accent;
    QString accentHover;
    QString accentPressed;
    QString selectionText;
    QString hover;
    QString danger;
    QString warning;
    QString success;
};

ThemeTokens darkTokens()
{
    return {QStringLiteral("#171A1F"), QStringLiteral("#1E232A"), QStringLiteral("#272E37"),
            QStringLiteral("#11151A"), QStringLiteral("#38424E"), QStringLiteral("#596879"),
            QStringLiteral("#E6EDF3"), QStringLiteral("#9BA7B4"), QStringLiteral("#7F8A98"),
            QStringLiteral("#176BA6"), QStringLiteral("#1976B8"), QStringLiteral("#105986"),
            QStringLiteral("#FFFFFF"), QStringLiteral("#303946"), QStringLiteral("#B93636"),
            QStringLiteral("#855800"), QStringLiteral("#267A4A")};
}

ThemeTokens lightTokens()
{
    return {QStringLiteral("#F3F5F7"), QStringLiteral("#FFFFFF"), QStringLiteral("#E9EDF2"),
            QStringLiteral("#FFFFFF"), QStringLiteral("#CFD6DE"), QStringLiteral("#94A1AF"),
            QStringLiteral("#1F252D"), QStringLiteral("#5D6976"), QStringLiteral("#9CA6B1"),
            QStringLiteral("#146FA8"), QStringLiteral("#1976B8"), QStringLiteral("#105986"),
            QStringLiteral("#FFFFFF"), QStringLiteral("#E5EAF0"), QStringLiteral("#B93636"),
            QStringLiteral("#9A650B"), QStringLiteral("#267A4A")};
}

QPalette buildPalette(const ThemeTokens& token)
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(token.window));
    palette.setColor(QPalette::WindowText, QColor(token.text));
    palette.setColor(QPalette::Base, QColor(token.input));
    palette.setColor(QPalette::AlternateBase, QColor(token.raised));
    palette.setColor(QPalette::ToolTipBase, QColor(token.raised));
    palette.setColor(QPalette::ToolTipText, QColor(token.text));
    palette.setColor(QPalette::Text, QColor(token.text));
    palette.setColor(QPalette::Button, QColor(token.raised));
    palette.setColor(QPalette::ButtonText, QColor(token.text));
    palette.setColor(QPalette::Light, QColor(token.borderStrong));
    palette.setColor(QPalette::Midlight, QColor(token.raised));
    palette.setColor(QPalette::Mid, QColor(token.border));
    palette.setColor(QPalette::Dark, QColor(token.borderStrong));
    palette.setColor(QPalette::Shadow, QColor(token.input));
    palette.setColor(QPalette::BrightText, QColor(token.danger));
    palette.setColor(QPalette::Highlight, QColor(token.accent));
    palette.setColor(QPalette::HighlightedText, QColor(token.selectionText));
    palette.setColor(QPalette::PlaceholderText, QColor(token.muted));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(token.disabled));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(token.disabled));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(token.disabled));
    return palette;
}

QString buildStyleSheet(const ThemeTokens& token)
{
    QString style = QStringLiteral(R"QSS(
/* Delta X application theme. Keep shared widget geometry and state styling here. */
QMainWindow, QDialog { background-color: @window; color: @text; }
QWidget { color: @text; }
QLabel { color: @text; background: transparent; }
QLabel:disabled { color: @disabled; }
QLabel[robotHint="true"] { color: @muted; }
QLabel[robotSectionTitle="true"] { font-weight: 600; font-size: 13px; }
QLabel[settingsLabel="true"] { color: @muted; }
QLabel[previewField="true"] { color: @muted; background-color: @input; border: 1px solid @border; border-radius: 4px; padding: 5px; }
QLabel#loadingPopup { background-color: @surface; border: 1px solid @borderStrong; border-radius: 6px; }
QWidget[validationState="error"] { border: 1px solid @danger; }

QPushButton, QToolButton {
    background-color: @raised;
    color: @text;
    border: 1px solid @border;
    border-radius: 4px;
    min-height: 20px;
    padding: 4px 10px;
}
QPushButton[iconOnly="true"], QToolButton[iconOnly="true"] { min-width: 20px; min-height: 20px; padding: 4px; }
QPushButton:focus, QToolButton:focus { border-color: @accentHover; }
QPushButton:hover, QToolButton:hover { background-color: @hover; border-color: @borderStrong; }
QPushButton:pressed, QToolButton:pressed { background-color: @accentPressed; border-color: @accent; color: @selectionText; }
QPushButton:checked, QToolButton:checked { background-color: @accent; border-color: @accentHover; color: @selectionText; }
QPushButton:disabled, QToolButton:disabled { background-color: @surface; color: @disabled; border-color: @border; }
QPushButton:default { background-color: @accent; color: @selectionText; border-color: @accentHover; font-weight: 600; }
QAbstractButton[controlRole="primary"] { background-color: @accent; color: @selectionText; border-color: @accentHover; font-weight: 600; }
QAbstractButton[controlRole="primary"]:hover { background-color: @accentHover; }
QAbstractButton[controlRole="primary"]:pressed { background-color: @accentPressed; }
QAbstractButton[controlRole="success"] { background-color: @success; color: @selectionText; border-color: @success; font-weight: 600; }
QAbstractButton[controlRole="danger"] { background-color: @danger; color: @selectionText; border-color: @danger; font-weight: 600; }
QAbstractButton[controlRole="warning"] { background-color: @warning; color: @selectionText; border-color: @warning; font-weight: 600; }
QAbstractButton[controlRole="quiet"] { background: transparent; border-color: transparent; color: @muted; }
QAbstractButton[controlRole="quiet"]:hover { background-color: @hover; color: @text; }
/* Jogging uses a dedicated geometry contract, independent of toolbar buttons. */
QToolButton[Func="Jogging"] { background-color: @accent; color: @selectionText; border: none; border-radius: 4px; min-width: 0; min-height: 0; padding: 0; }
QToolButton[jogStep="true"] { min-width: 48px; max-width: 48px; min-height: 48px; max-height: 48px; font-size: 13px; font-weight: 600; }
QToolButton[jogStrip="horizontal"] { width: 48px; height: 10px; }
QToolButton[jogStrip="vertical"] { width: 10px; height: 48px; }
QToolButton[Func="Jogging"]:hover { background-color: @accentHover; }
QToolButton[Func="Jogging"]:pressed { background-color: @accentPressed; }
QToolButton[Func="Jogging"]:disabled { background-color: @surface; color: @disabled; }
QFrame#frame_32 QRadioButton { background-color: @raised; color: @text; padding: 5px; min-width: 30px; border: 1px solid @border; }
QFrame#frame_32 QRadioButton::indicator { width: 0; height: 0; border: none; image: none; }
QFrame#frame_32 QRadioButton:checked { background-color: @accent; color: @selectionText; border-color: @accent; }
QFrame#frame_32 QRadioButton:focus { border-color: @accentHover; }
QFrame[Func="Title"] { background-color: @raised; }
QPushButton[controlRole]:disabled, QToolButton[controlRole]:disabled,
QPushButton:default:disabled { background-color: @surface; color: @disabled; border-color: @border; }
QPushButton[controlRole]:pressed, QToolButton[controlRole]:pressed { border-color: @text; }

QLineEdit, QTextEdit, QPlainTextEdit, QSpinBox, QDoubleSpinBox,
QComboBox, QDateEdit, QTimeEdit, QDateTimeEdit {
    background-color: @input;
    color: @text;
    border: 1px solid @border;
    border-radius: 4px;
    min-height: 20px;
    padding: 4px 6px;
    selection-background-color: @accent;
    selection-color: @selectionText;
}
QLineEdit:hover, QTextEdit:hover, QPlainTextEdit:hover, QSpinBox:hover,
QDoubleSpinBox:hover, QComboBox:hover { border-color: @borderStrong; }
QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus, QSpinBox:focus,
QDoubleSpinBox:focus, QComboBox:focus { border: 1px solid @accentHover; }
QLineEdit:disabled, QTextEdit:disabled, QPlainTextEdit:disabled,
QSpinBox:disabled, QDoubleSpinBox:disabled, QComboBox:disabled {
    background-color: @surface; color: @disabled;
}
QComboBox { padding-right: 24px; }
QSpinBox, QDoubleSpinBox, QDateTimeEdit { padding-right: 24px; }
QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 22px; border-left: 1px solid @border; }
QComboBox::down-arrow { image: url(:/icon/theme/down-@glyph.svg); width: 10px; height: 6px; }
QAbstractSpinBox::up-button, QAbstractSpinBox::down-button { subcontrol-origin: border; width: 22px; background-color: @raised; border-left: 1px solid @border; }
QAbstractSpinBox::up-button { subcontrol-position: top right; border-bottom: 1px solid @border; border-top-right-radius: 4px; }
QAbstractSpinBox::down-button { subcontrol-position: bottom right; border-bottom-right-radius: 4px; }
QAbstractSpinBox::up-button:hover, QAbstractSpinBox::down-button:hover { background-color: @hover; }
QAbstractSpinBox::up-button:pressed, QAbstractSpinBox::down-button:pressed { background-color: @borderStrong; }
QAbstractSpinBox::up-arrow { image: url(:/icon/theme/up-@glyph.svg); width: 10px; height: 6px; }
QAbstractSpinBox::down-arrow { image: url(:/icon/theme/down-@glyph.svg); width: 10px; height: 6px; }
QAbstractSpinBox::up-button:off, QAbstractSpinBox::down-button:off { background-color: @surface; }
QLineEdit:read-only { background-color: @surface; }
QComboBox QAbstractItemView {
    background-color: @surface; color: @text; border: 1px solid @border;
    selection-background-color: @accent; selection-color: @selectionText;
}

QCheckBox, QRadioButton { color: @text; spacing: 7px; }
/* Explicit glyphs keep all three check states visible on both palettes. */
QCheckBox::indicator, QRadioButton::indicator { width: 14px; height: 14px; border: 1px solid @borderStrong; background-color: @input; }
QCheckBox::indicator { border-radius: 3px; }
QRadioButton::indicator { border-radius: 8px; }
QCheckBox::indicator:checked, QCheckBox::indicator:indeterminate,
QRadioButton::indicator:checked { background-color: @accent; border-color: @accent; }
QCheckBox::indicator:checked { image: url(:/icon/theme/check.svg); }
QCheckBox::indicator:indeterminate { image: url(:/icon/theme/mixed.svg); }
QRadioButton::indicator:checked { image: url(:/icon/theme/dot.svg); }
QCheckBox::indicator:hover, QRadioButton::indicator:hover { border-color: @accentHover; }
QCheckBox::indicator:disabled, QRadioButton::indicator:disabled { background-color: @raised; border-color: @border; }
QCheckBox::indicator:checked:disabled, QCheckBox::indicator:indeterminate:disabled,
QRadioButton::indicator:checked:disabled { background-color: @muted; }
QCheckBox:disabled, QRadioButton:disabled { color: @disabled; }
QCheckBox:focus, QRadioButton:focus { color: @text; }
QCheckBox::indicator:focus, QRadioButton::indicator:focus { border-color: @accentHover; }

QGroupBox {
    background-color: transparent;
    color: @text;
    border: 1px solid @border;
    border-radius: 6px;
    margin-top: 12px;
    padding: 9px 7px 7px 7px;
}
QGroupBox::title { subcontrol-origin: margin; left: 8px; padding: 0 5px; color: @text; font-weight: 600; }
QGroupBox::indicator { width: 14px; height: 14px; border: 1px solid @borderStrong; border-radius: 3px; background-color: @input; }
QGroupBox::indicator:checked { background-color: @accent; border-color: @accent; image: url(:/icon/theme/check.svg); }
QGroupBox[collapsibleSection="true"]::indicator { border: none; background: transparent; image: url(:/icon/theme/right-@glyph.svg); }
QGroupBox[collapsibleSection="true"]::indicator:checked { image: url(:/icon/theme/down-@glyph.svg); }

QTabWidget::pane { background-color: @surface; border: 1px solid @border; }
QTabBar::tab {
    background-color: @raised; color: @muted; border: 1px solid @border;
    border-bottom: none; min-height: 27px; padding: 4px 12px; margin-right: 1px;
}
QTabBar::tab:hover { background-color: @hover; color: @text; }
QTabBar::tab:selected { background-color: @accent; color: @selectionText; border-color: @accent; }
QTabBar::tab:disabled { color: @disabled; }

QTreeView, QTableView, QListView, QListWidget, QTableWidget, QTreeWidget {
    background-color: @surface; alternate-background-color: @raised; color: @text;
    border: 1px solid @border; gridline-color: @border;
    selection-background-color: @accent; selection-color: @selectionText;
    outline: none;
}
QTreeView::item, QTableView::item, QListView::item { min-height: 22px; padding: 2px 4px; }
QTreeView::item:hover:!selected, QTableView::item:hover:!selected, QListView::item:hover:!selected { background-color: @hover; }
QHeaderView::section {
    background-color: @raised; color: @text; border: none;
    border-right: 1px solid @border; border-bottom: 1px solid @border;
    min-height: 25px; padding: 3px 6px; font-weight: 600;
}
QTableCornerButton::section { background-color: @raised; border: 1px solid @border; }

QMenuBar, QMenu { background-color: @surface; color: @text; }
QMenuBar::item, QMenu::item { padding: 5px 10px; }
QMenuBar::item:selected, QMenu::item:selected { background-color: @accent; color: @selectionText; }
QMenu::separator { height: 1px; background-color: @border; margin: 4px 7px; }
QMenu::item:disabled { color: @disabled; }

QScrollArea, QAbstractScrollArea { background: transparent; border: none; }
QScrollBar:vertical { background: @window; width: 12px; margin: 2px; }
QScrollBar:horizontal { background: @window; height: 12px; margin: 2px; }
QScrollBar::handle:vertical { background: @borderStrong; border-radius: 4px; min-height: 28px; }
QScrollBar::handle:horizontal { background: @borderStrong; border-radius: 4px; min-width: 28px; }
QScrollBar::handle:vertical:hover, QScrollBar::handle:horizontal:hover { background: @accentHover; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; background: transparent; border: none; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }

QSplitter::handle { background-color: @border; }
QSplitter::handle:hover { background-color: @accent; }
QProgressBar { background-color: @input; color: @text; border: 1px solid @border; border-radius: 4px; text-align: center; min-height: 18px; }
QProgressBar::chunk { background-color: @accent; border-radius: 3px; }
QSlider::groove:horizontal { background: @border; height: 5px; border-radius: 2px; }
QSlider::sub-page:horizontal { background: @accent; border-radius: 2px; }
QSlider::handle:horizontal { background: @accentHover; width: 14px; margin: -5px 0; border-radius: 7px; }
QStatusBar { background-color: @surface; color: @muted; border-top: 1px solid @border; }
QToolTip { background-color: @raised; color: @text; border: 1px solid @borderStrong; padding: 4px 6px; }
QFrame#gscriptStatusBar { background-color: @surface; border-top: 1px solid @border; }
QFrame#gscriptStatusBar QLabel { padding: 2px 6px; }
QFrame#gscriptStatusBar QPushButton { padding: 3px 10px; }
QLabel#gscriptSignatureLabel { color: @statusInfo; }

QWidget[navigationRail="true"] { background-color: @surface; border-right: 1px solid @border; }
QWidget[navigationRail="true"] QToolButton { background: transparent; border: none; border-radius: 5px; padding: 6px 4px; }
QWidget[navigationRail="true"] QToolButton:hover { background-color: @hover; }
QWidget[navigationRail="true"] QToolButton[navigationSelected="true"] { background-color: @accent; color: @selectionText; }

QDialog[deltaDialog="true"] { background-color: @surface; border: 1px solid @borderStrong; border-radius: 8px; }
QDialog[deltaDialog="true"] QWidget#titleBar,
QDialog[deltaDialog="true"] QWidget#buttonWidget { background-color: @raised; }
QDialog[deltaDialog="true"] QWidget#titleBar { border-bottom: 1px solid @border; }
QDialog[deltaDialog="true"] QWidget#buttonWidget { border-top: 1px solid @border; }
QDialog[deltaDialog="true"] QWidget#contentWidget { background-color: @surface; }
QDialog[deltaDialog="true"] QLabel#subtitleLabel,
QDialog[deltaDialog="true"] QLabel#contentLabel,
QDialog[deltaDialog="true"] QLabel#statusLabel { color: @muted; }
QDialog[deltaDialog="true"] QPushButton#okButton:enabled { background-color: @accent; color: @selectionText; font-weight: 600; }

QFrame#pointToolOverview { background-color: @surface; border: 1px solid @border; border-radius: 7px; }
QLabel#pointToolTitle { color: @text; font-size: 18px; font-weight: 600; }
QLabel[pointToolRole="subtitle"], QLabel[pointToolRole="description"] { color: @muted; }
QLabel[pointToolRole="chip"] { color: @text; background-color: @raised; border: 1px solid @borderStrong; border-radius: 10px; padding: 3px 9px; }
QLabel[pointToolRole="step"] { color: @text; background-color: @raised; border: 1px solid @border; border-radius: 4px; padding: 7px 9px; }
QLabel[pointToolRole="category"] { color: @muted; font-size: 11px; font-weight: 600; padding: 7px 2px 1px 2px; }
QPushButton#pointToolOpenButton { background-color: @accent; border-color: @accentHover; color: @selectionText; font-weight: 600; min-height: 26px; }

*[statusRole="success"] { color: @statusSuccess; }
*[statusRole="warning"] { color: @statusWarning; }
*[statusRole="danger"], *[statusRole="error"] { color: @statusDanger; }
*[statusRole="info"] { color: @statusInfo; }
*[statusRole="muted"] { color: @muted; }
)QSS");

    const QList<QPair<QString, QString>> replacements = {
        {QStringLiteral("@window"), token.window},
        {QStringLiteral("@surface"), token.surface},
        {QStringLiteral("@raised"), token.raised},
        {QStringLiteral("@input"), token.input},
        {QStringLiteral("@borderStrong"), token.borderStrong},
        {QStringLiteral("@border"), token.border},
        {QStringLiteral("@text"), token.text},
        {QStringLiteral("@muted"), token.muted},
        {QStringLiteral("@disabled"), token.disabled},
        {QStringLiteral("@accentHover"), token.accentHover},
        {QStringLiteral("@accentPressed"), token.accentPressed},
        {QStringLiteral("@accent"), token.accent},
        {QStringLiteral("@selectionText"), token.selectionText},
        {QStringLiteral("@hover"), token.hover},
        {QStringLiteral("@danger"), token.danger},
        {QStringLiteral("@warning"), token.warning},
        {QStringLiteral("@success"), token.success}};
    const bool dark = QColor(token.window).lightness() < 128;
    style.replace(QStringLiteral("@glyph"),
                  dark ? QStringLiteral("light") : QStringLiteral("dark"));
    style.replace(QStringLiteral("@statusSuccess"),
                  dark ? QStringLiteral("#78D9A2") : token.success);
    style.replace(QStringLiteral("@statusWarning"),
                  dark ? QStringLiteral("#F2C46D") : token.warning);
    style.replace(QStringLiteral("@statusDanger"), dark ? QStringLiteral("#FF9292") : token.danger);
    style.replace(QStringLiteral("@statusInfo"), dark ? QStringLiteral("#80C4FF") : token.accent);
    for (const auto& replacement : replacements)
        style.replace(replacement.first, replacement.second);
    return style;
}
} // namespace

QString UiTheme::effectiveTheme(const QString& requestedTheme)
{
    if (requestedTheme.compare(QStringLiteral("Light"), Qt::CaseInsensitive) == 0)
        return QStringLiteral("Light");
    if (requestedTheme.compare(QStringLiteral("Auto"), Qt::CaseInsensitive) == 0)
    {
        QApplication* application = qobject_cast<QApplication*>(QApplication::instance());
        if (!application)
            return QStringLiteral("Dark");
        QVariant nativeLightness = application->property("deltaSystemWindowLightness");
        if (!nativeLightness.isValid())
        {
            nativeLightness = application->palette().color(QPalette::Window).lightness();
            application->setProperty("deltaSystemWindowLightness", nativeLightness);
        }
        return nativeLightness.toInt() < 128 ? QStringLiteral("Dark") : QStringLiteral("Light");
    }
    return QStringLiteral("Dark");
}

void UiTheme::apply(QApplication& application, const QString& requestedTheme)
{
    const QString theme = effectiveTheme(requestedTheme);
    const ThemeTokens token = theme == QStringLiteral("Light") ? lightTokens() : darkTokens();

    if (QStyle* fusion = QStyleFactory::create(QStringLiteral("Fusion")))
        application.setStyle(fusion);

    QFont font = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
    if (font.pointSizeF() < 9.0)
        font.setPointSizeF(9.0);
    application.setFont(font);
    application.setPalette(buildPalette(token));
    application.setStyleSheet(buildStyleSheet(token));
    application.setProperty("deltaTheme", theme);
}

void UiTheme::setStatusRole(QWidget* widget, const QString& role)
{
    if (!widget)
        return;
    widget->setProperty("statusRole", role);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}

void UiTheme::setControlRole(QWidget* widget, const QString& role)
{
    if (!widget)
        return;
    widget->setProperty("controlRole", role);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}

void UiTheme::polishWidgetTree(QWidget* root)
{
    if (!root)
        return;

    for (QWidget* panel : root->findChildren<QWidget*>())
    {
        if (!panel->property("navigationRail").toBool())
            continue;
        int railWidth = 80;
        for (QToolButton* button : panel->findChildren<QToolButton*>())
        {
            railWidth =
                qMax(railWidth, button->fontMetrics().horizontalAdvance(button->text()) + 16);
            button->setMinimumWidth(0);
            button->setMaximumWidth(QWIDGETSIZE_MAX);
            if (!button->icon().isNull() && !button->property("deltaNavigationIcon").toBool())
            {
                button->setIcon(QIcon(new NavigationIconEngine(button->icon(), button)));
                button->setProperty("deltaNavigationIcon", true);
                button->setIconSize(QSize(20, 20));
            }
        }
        panel->setFixedWidth(railWidth);
    }

    // Designer-era 20px height caps predate the shared font and padding.
    // Let layout-managed controls negotiate their size; leave the custom
    // jogging cluster alone because its narrow strips are intentional.
    for (QWidget* widget : root->findChildren<QWidget*>())
    {
        bool jogging = widget->property("Func").toString() == QStringLiteral("Jogging");
        if (jogging)
        {
            auto* button = qobject_cast<QToolButton*>(widget);
            if (button)
            {
                if (button->maximumHeight() <= 10)
                    button->setProperty("jogStrip", "horizontal");
                else if (button->maximumWidth() <= 10)
                    button->setProperty("jogStrip", "vertical");
                else
                {
                    button->setToolButtonStyle(Qt::ToolButtonTextOnly);
                    button->setProperty("jogStep", true);
                    button->setFixedSize(48, 48);
                }
                button->style()->unpolish(button);
                button->style()->polish(button);
            }
            continue;
        }
        const bool control = qobject_cast<QPushButton*>(widget) ||
                             qobject_cast<QToolButton*>(widget) ||
                             qobject_cast<QLineEdit*>(widget) || qobject_cast<QComboBox*>(widget) ||
                             qobject_cast<QAbstractSpinBox*>(widget);
        if (control && widget->maximumHeight() < 32)
            widget->setMaximumHeight(QWIDGETSIZE_MAX);
        if (widget->layout() && widget->maximumHeight() <= 200)
        {
            widget->setMaximumHeight(QWIDGETSIZE_MAX);
            widget->setMinimumHeight(0);
            widget->setSizePolicy(widget->sizePolicy().horizontalPolicy(), QSizePolicy::Fixed);
            widget->layout()->setSizeConstraint(QLayout::SetMinimumSize);
        }
        if (widget->layout() &&
            (qobject_cast<QFrame*>(widget) || qobject_cast<QGroupBox*>(widget)) &&
            !qobject_cast<QAbstractScrollArea*>(widget))
        {
            widget->setMinimumHeight(0);
            widget->layout()->setSizeConstraint(QLayout::SetMinimumSize);
        }
    }
    for (QScrollArea* scroll : root->findChildren<QScrollArea*>())
    {
        if (scroll->widgetResizable() && scroll->widget())
        {
            scroll->widget()->setMinimumHeight(0);
            if (scroll->widget()->layout())
                scroll->widget()->layout()->setSizeConstraint(QLayout::SetMinimumSize);
        }
    }

    const QList<QAbstractButton*> buttons = root->findChildren<QAbstractButton*>();
    for (QAbstractButton* button : buttons)
    {
        if (button->property("Func").toString() == QStringLiteral("Jogging"))
            continue;
        if (!button->icon().isNull() && !button->property("deltaNavigationIcon").toBool() &&
            !button->property("deltaContrastIcon").toBool() &&
            !button->property("preserveIconColors").toBool())
        {
            button->setIcon(QIcon(new ButtonIconEngine(button->icon(), button)));
            button->setProperty("deltaContrastIcon", true);
        }
        const QString visibleText = button->text().trimmed();
        const auto* toolButton = qobject_cast<QToolButton*>(button);
        const bool iconOnly =
            (visibleText.isEmpty() && !button->icon().isNull()) ||
            visibleText == QStringLiteral("...") ||
            (toolButton && toolButton->toolButtonStyle() == Qt::ToolButtonIconOnly &&
             !button->icon().isNull());
        if (!iconOnly)
            continue;

        button->setProperty("iconOnly", true);
        if (button->maximumWidth() < 30)
            button->setMaximumWidth(30);
        button->setMinimumSize(qMax(30, button->minimumWidth()), qMax(30, button->minimumHeight()));
        button->style()->unpolish(button);
        button->style()->polish(button);

        QString description = button->toolTip().trimmed();
        if (description.isEmpty())
        {
            description = button->objectName();
            description.remove(QRegularExpression(QStringLiteral("^(pb|tb|btn)"),
                                                  QRegularExpression::CaseInsensitiveOption));
            description.replace(QRegularExpression(QStringLiteral("([a-z0-9])([A-Z])")),
                                QStringLiteral("\\1 \\2"));
            description = description.trimmed();
        }
        if (!description.isEmpty())
        {
            if (button->toolTip().isEmpty())
                button->setToolTip(description);
            if (button->accessibleName().isEmpty())
                button->setAccessibleName(description);
        }
    }
}

void UiTheme::prepareForm(QWidget* root, const QList<QWidget*>& preservedRoots)
{
    if (!root)
        return;
    root->setStyleSheet(QString());
    for (QWidget* widget : root->findChildren<QWidget*>())
    {
        bool preserve = false;
        for (QWidget* canvas : preservedRoots)
        {
            if (canvas && (widget == canvas || canvas->isAncestorOf(widget)))
            {
                preserve = true;
                break;
            }
        }
        if (!preserve && !widget->styleSheet().isEmpty())
            widget->setStyleSheet(QString());
    }
    polishWidgetTree(root);
}
