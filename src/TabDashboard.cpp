#include "TabDashboard.h"
#include <QStyle>

TabDashboard::TabDashboard(QWidget *parent) : QWidget(parent)
{
    TabPages = new  QList<TabPage*>();
}

void TabDashboard::InitPage(QAbstractButton *button, QWidget *page)
{
    TabPage* tabPage = new TabPage(button, page);
    TabPages->append(tabPage);

    connect(button, SIGNAL(clicked()), this, SLOT(SelectPage()));

}

void TabDashboard::InitPanel(QWidget *panel, QStackedWidget* pageStack)
{
    qPanel = panel;
    swPageStack = pageStack;
    if (qPanel)
        qPanel->setProperty("navigationRail", true);
}

void TabDashboard::SelectPage()
{
    if (Lock == true)
    {
//        QMessageBox::information(this, "Permission", "You do not have permission to access these tabs.");
        bool ok;
        QString text = QInputDialog::getText(this, tr("Permission"),
                                             tr("Password (default \"1234\"):"), QLineEdit::Password, "", &ok);
        if (ok && !text.isEmpty())
        {
            if (text == Pass)
            {
                if (SoftwareAuthority != NULL)
                {
                    SoftwareAuthority->ReturnProgramer();
                }

                Lock = false;
            }
            else
            {
                QMessageBox::information(this, "Wrong", "You have entered the wrong password!");
                return;
            }
        }
    }



    if (Lock == true)
    {
        return;
    }

    QAbstractButton* senderButton = qobject_cast<QAbstractButton*>(sender());

    for(int i = 0; i < TabPages->length(); i++)
    {
        const bool selected = TabPages->at(i)->Button == senderButton;
        TabPages->at(i)->Button->setProperty("navigationSelected", selected);
        TabPages->at(i)->Button->style()->unpolish(TabPages->at(i)->Button);
        TabPages->at(i)->Button->style()->polish(TabPages->at(i)->Button);

        if(selected)
        {
            swPageStack->setCurrentWidget(TabPages->at(i)->Page);

            emit TabChanged(TabPages->at(i)->Button);
        }
    }
}

TabPage::TabPage(QAbstractButton *button, QWidget *page)
{
    Button = button;
    Page = page;


}
