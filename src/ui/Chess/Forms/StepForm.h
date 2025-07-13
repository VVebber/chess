#ifndef STEPFORM_H
#define STEPFORM_H

#include "BaseForm.h"

class QSpinBox;
class QCheckBox;
class QComboBox;

class StepForm : public BaseForm
{
  Q_OBJECT
public:
  StepForm();

  QJsonObject toJson(QJsonObject data) override;

public slots:
  void updateForm() override;
  void updateForm2();
  void onUpdateFormInfo(const QJsonObject& data);

private:
  void setup();
  void setupStyleSheet();

  QWidget* setupDirectionsGrid();

  void paintEvent(QPaintEvent* event) override;
  QCheckBox* checkBoxWithImage(int rotate);

private:
  QSpinBox* m_strokeLength;

  QComboBox* m_playersList;
  QVector<QCheckBox*> m_directionBoxes;

  QJsonObject m_data;
};

#endif // STEPFORM_H
