#include "TabDashboard.h"

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
}

void TabDashboard::SetSelectedState(QString qss)
{
    SelectedStateQSS = qss;
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
        // clear selected state for all button
        TabPages->at(i)->Button->setStyleSheet("");

        if(TabPages->at(i)->Button == senderButton)
        {
            swPageStack->setCurrentWidget(TabPages->at(i)->Page);
            // Set forcus color for selected button
            TabPages->at(i)->Button->setStyleSheet(SelectedStateQSS);

            emit TabChanged(TabPages->at(i)->Button);
        }
    }
}

TabPage::TabPage(QAbstractButton *button, QWidget *page)
{
    Button = button;
    Page = page;


}
