#ifndef TABDASHBOARD_H
#define TABDASHBOARD_H

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QStackedWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <Authority.h>

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

    bool Lock = false;
    QString Pass = "1234";

    Authority* SoftwareAuthority = NULL;

public slots:
    void SelectPage();

signals:
    void TabChanged(QAbstractButton* tabButton);

private:
    QWidget* qPanel;
    QStackedWidget* swPageStack;
    QList<TabPage*>* TabPages;
    QString SelectedStateQSS;
};

#endif // TABDASHBOARD_H
