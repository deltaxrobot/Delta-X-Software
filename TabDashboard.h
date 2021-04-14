#ifndef TABDASHBOARD_H
#define TABDASHBOARD_H

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QStackedWidget>

class TabPage
{
public:
    TabPage(QAbstractButton* button, QWidget* page);

    QAbstractButton* Button;
    QWidget* Page;
};

class TabDashboard : public QWidget
{
    Q_OBJECT
public:
    TabDashboard(QWidget* parent = NULL);

    void InitPage(QAbstractButton* button, QWidget* page);
    void InitPanel(QWidget* panel, QStackedWidget* pageStack);
    void SetSelectedState(QString qss);

public slots:
    void SelectPage();

private:
    QWidget* qPanel;
    QStackedWidget* swPageStack;
    QList<TabPage*>* TabPages;
    QString SelectedStateQSS;
};

#endif // TABDASHBOARD_H
