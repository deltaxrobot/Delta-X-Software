#pragma once
#include <QDialog>
class PhoneCameraServer;
class PhoneCameraDialog : public QDialog
{
    Q_OBJECT
  public:
    explicit PhoneCameraDialog(PhoneCameraServer* server, QWidget* parent = nullptr);

  private:
    PhoneCameraServer* m_server;
};
