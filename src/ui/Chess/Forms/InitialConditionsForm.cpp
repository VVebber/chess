#include "InitialConditionsForm.h"
#include "../../../Common.h"

#include <QLabel>
#include <QLayout>
#include <QSpinBox>

InitialConditionsForm::InitialConditionsForm()
{
  m_strokeLength = new QSpinBox;
  setup();
}

void InitialConditionsForm::setup()
{
  QGridLayout* layout = new QGridLayout(this);
  layout->addWidget(new QLabel("Длина хода"), 0, 0);
  layout->addWidget(m_strokeLength, 0, 1);

}

QJsonObject InitialConditionsForm::toJson(QJsonObject data)
{
  QJsonObject movePatterns = data.value(MOVE_PATTERNS).toObject();
  QJsonObject initCondition = movePatterns.value(INITIAL_CONDIYIONS).toObject();

  if(m_countPlayers == 0)
    return data;

  QJsonObject info;
  for(int i = 0; i < m_countPlayers; i++)
  {
    info[PLAYER_EN.arg(i)] = m_strokeLength->value();
  }

  initCondition[STROKE_LENGTH] = info;
  movePatterns[INITIAL_CONDIYIONS] = initCondition;
  data[MOVE_PATTERNS] = movePatterns;

  return data;
}

void InitialConditionsForm::updateForm()
{

}
