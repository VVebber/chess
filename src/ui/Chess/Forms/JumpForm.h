#ifndef JUMPFORM_H
#define JUMPFORM_H

#include "BaseForm.h"

class QSpinBox;
class QListWidget;

class JumpForm : public BaseForm
{
  Q_OBJECT
public:
  JumpForm();

  QJsonObject toJson(QJsonObject data) override;

public slots:
  void updateForm() override{};
  void addMoveClicked();
  void removeMoveClicked();

private:
  void setup();
  void setupStyleSheet();

  void paintEvent(QPaintEvent* event) override;

private:
  QSpinBox* m_spinX;
  QSpinBox* m_spinY;

  QListWidget* m_moveList;
};

#endif // JUMPFORM_H
