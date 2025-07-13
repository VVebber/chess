#ifndef FIGUREMOVEFORM_H
#define FIGUREMOVEFORM_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>

class StepForm;
class JumpForm;
class MoveConditionForm;
class InitialConditionsForm;

class QComboBox;
class QGridLayout;

class FigureMoveForm : public QWidget
{
  Q_OBJECT
public:
  FigureMoveForm(int countPlayer);

  void toJson(QJsonArray& data);

public slots:
  void onUpdateFormInfo(const QJsonObject& data);
  void onUpdateDataForm(int id);
  void onUpdateCountPlaters(const int& count);
  void onChangedTypeMove(int index);

private:
  void setup();
  void setupStyleSheet();

private:
  int m_countPlayers;
  QJsonArray m_figuresData;

  QComboBox* m_figuresList;
  QComboBox* m_typeMove;

  StepForm* m_stepForm;
  JumpForm* m_jumpForm;
  MoveConditionForm* m_moveConditionForm;
  InitialConditionsForm* m_initConditionsForm;
};

#endif // FIGUREMOVEFORM_H
