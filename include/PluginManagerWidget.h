#ifndef PLUGINMANAGERWIDGET_H
#define PLUGINMANAGERWIDGET_H

#include <QWidget>

class QLabel;
class PluginManager;
class QCheckBox;
class QResizeEvent;
class QTableWidget;

class PluginManagerWidget final : public QWidget
{
    Q_OBJECT

public:
    explicit PluginManagerWidget(PluginManager* manager,
                                 const QString& builtInDirectory,
                                 QWidget* parent = nullptr);

    void refresh();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateDisabledPlugin(int row, int column);
    void updateUserDirectorySetting(bool enabled);
    void openBuiltInDirectory();
    void openUserDirectory();
    void openDocumentation();
    void configurePermissions();

private:
    QString userPluginDirectory() const;
    QString documentationPath() const;
    void markRestartRequired();
    void updateResponsiveColumns();

    PluginManager* m_manager = nullptr;
    QString m_builtInDirectory;
    QLabel* m_explanationLabel = nullptr;
    QLabel* m_summaryLabel = nullptr;
    QLabel* m_restartLabel = nullptr;
    QCheckBox* m_enableUserDirectory = nullptr;
    QTableWidget* m_table = nullptr;
    bool m_refreshing = false;
};

#endif // PLUGINMANAGERWIDGET_H
