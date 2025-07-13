#ifndef BASEFORM_H
#define BASEFORM_H

#include <QWidget>
#include <QJsonObject>

class BaseForm : public QWidget
{
  Q_OBJECT
public:
  BaseForm();
  virtual ~BaseForm();

  virtual QJsonObject toJson(QJsonObject data) = 0;

public slots:
  virtual void updateForm() = 0;

  static void setCountPlayer(int count);

protected:
  static int m_countPlayers;
};

#endif // BASEFORM_H
