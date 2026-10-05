#ifndef UITHEME_H
#define UITHEME_H

#include <QString>
#include <QList>

class QApplication;
class QWidget;

namespace UiTheme
{
// Applies the shared application palette, typography, and widget stylesheet.
// Supported values are "Dark", "Light", and "Auto" (case-insensitive).
void apply(QApplication& application, const QString& requestedTheme);

QString effectiveTheme(const QString& requestedTheme);
void setStatusRole(QWidget* widget, const QString& role);
void setControlRole(QWidget* widget, const QString& role);
void polishWidgetTree(QWidget* root);
// Remove legacy form styles before applying the shared component rules.
// Domain canvases may keep their own rendering styles.
void prepareForm(QWidget* root, const QList<QWidget*>& preservedRoots = {});
}

#endif // UITHEME_H
