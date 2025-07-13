#ifndef INITIALCONDITIONSFORM_H
#define INITIALCONDITIONSFORM_H

#include "BaseForm.h"

class QSpinBox;

class InitialConditionsForm: public BaseForm
{
  Q_OBJECT
public:
  InitialConditionsForm();

  QJsonObject toJson(QJsonObject data) override;

public slots:
  void updateForm() override;

private:
  void setup();

private:
  QSpinBox* m_strokeLength;

};

#endif // INITIALCONDITIONSFORM_H
