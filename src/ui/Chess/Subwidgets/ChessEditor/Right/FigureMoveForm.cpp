#include "FigureMoveForm.h"

#include "../../../Forms/Forms.h"
#include "../../../../../Common.h"

#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>

FigureMoveForm::FigureMoveForm(int countPlayer)
{
  m_countPlayers = countPlayer;
  m_figuresList = new QComboBox();
  m_typeMove = new QComboBox();

  m_stepForm = new StepForm;
  m_jumpForm = new JumpForm;
  m_moveConditionForm = new MoveConditionForm;
  m_moveConditionForm->hide();

  m_initConditionsForm = new InitialConditionsForm;
  m_initConditionsForm->hide();

  setup();
  setupStyleSheet();

  // updateForm();
}

void FigureMoveForm::setup()
{
  qDebug()<<Q_FUNC_INFO;

  m_typeMove->addItem("Ход", STEP_FORM);
  m_typeMove->addItem("Прыжок", JUMP_FORM);

  QCheckBox* cellEvents = new QCheckBox("Условие клетки");
  QCheckBox* firstMove = new QCheckBox("Начальные условия");


  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Фигура: "), 0, 0);
  layout->addWidget(m_figuresList, 0, 1);

  layout->addWidget(new QLabel("Тип хода:"), 1, 0, 1, 1);
  layout->addWidget(m_typeMove, 1, 1, 1, 1);

  layout->addWidget(m_stepForm, 2, 0, 1, 2);
  layout->addWidget(m_jumpForm, 2, 0, 1, 2);

  layout->addWidget(cellEvents, 3, 0, 1, 2);
  layout->addWidget(m_moveConditionForm, 4, 0, 1, 2);

  layout->addWidget(firstMove, 5, 0, 1, 2);
  layout->addWidget(m_initConditionsForm, 6, 0, 1, 2);

  connect(m_typeMove, &QComboBox::currentIndexChanged, this, &FigureMoveForm::onChangedTypeMove);
  connect(m_figuresList, &QComboBox::currentIndexChanged, this, &FigureMoveForm::onUpdateDataForm);
  connect(cellEvents, &QCheckBox::stateChanged, this, [=](int state){
      m_moveConditionForm->setVisible(state == Qt::Checked);
  });

  connect(firstMove, &QCheckBox::stateChanged, this, [=](int state){
      m_initConditionsForm->setVisible(state == Qt::Checked);
  });

  onChangedTypeMove(0);

  this->setLayout(layout);
}

void FigureMoveForm::toJson(QJsonArray& data)
{
  int i = m_figuresList->currentIndex();

  if(i == -1)
    return;

  if(m_stepForm->isVisible())
  {
    data[i] = m_stepForm->toJson(data[i].toObject());
  }
  else if(m_jumpForm->isVisible())
  {
    data[i] = m_jumpForm->toJson(data[i].toObject());
  }

  if(m_moveConditionForm->isVisible())
  {
    data[i] = m_moveConditionForm->toJson(data[i].toObject());
  }

  if(m_initConditionsForm->isVisible())
  {
    data[i] = m_initConditionsForm->toJson(data[i].toObject());
  }
}

void FigureMoveForm::onChangedTypeMove(int index)
{
  static int previousIndex;

  if(index == 0)
  {
    m_stepForm->show();
    m_jumpForm->hide();
  }
  else if(index == 1)
  {
    m_stepForm->hide();
    m_jumpForm->show();
  }

}

void FigureMoveForm::onUpdateDataForm(int id)
{
  if(id == -1)
    return;

  m_stepForm->onUpdateFormInfo(m_figuresData[id].toObject());
}

void FigureMoveForm::onUpdateFormInfo(const QJsonObject& data)
{
  qDebug()<<Q_FUNC_INFO;
  m_figuresData = data.value(FIGURES).toArray();

  m_figuresList->clear();
  for(int i = 0; i < m_figuresData.size(); i++)
  {
    QJsonObject figureInfo = m_figuresData.at(i).toObject();
    m_figuresList->addItem(figureInfo[TYPE_FIGURE].toString());
  }

  int i = m_figuresList->currentIndex();

  if(i == -1)
    return;

  if(m_stepForm->isVisible())
    m_stepForm->onUpdateFormInfo(m_figuresData[i].toObject());
}

void FigureMoveForm::onUpdateCountPlaters(const int& count)
{
  m_countPlayers = count;
  BaseForm::setCountPlayer(count);
  m_stepForm->updateForm();
  m_moveConditionForm->updateForm();
}

void FigureMoveForm::setupStyleSheet()
{
  qDebug()<<Q_FUNC_INFO;
  setStyleSheet(R"(

  QComboBox {
    border: 2px solid #a67c52;
    border-radius: 4px;
    padding: 4px 4px 4px 8px;
    background-color: #ffffff;
    color: #2e2e2e;
    font-size: 14px;
  }

  QComboBox:hover {
    border-color: #d4a373;
  }

  QComboBox:focus {
    border-color: #8b5e3c;
    background-color: #fdf6ec;
  }

  /* Стрелка */
  QComboBox::drop-down {
    subcontrol-origin: padding;
    subcontrol-position: top right;
    width: 20px;
    border-left: 1px solid #a67c52;
    background-color: #f0e6d2; /* <- УСТАНОВИМ НЕПРОЗРАЧНЫЙ ФОН */
    border-top-right-radius: 4px;
    border-bottom-right-radius: 4px;
  }

  QComboBox::down-arrow {
    width: 0;
    height: 0;
    margin-right: 2px;
    border-left: 5px solid transparent;
    border-right: 5px solid transparent;
    border-top: 6px solid #6e4f32;
    background: transparent;
  }

  QComboBox::down-arrow:on {
    top: 1px;
    transform: rotate(180deg);
  }

  QComboBox QAbstractItemView {
    border: 2px solid #a67c52;
    background-color: #fffaf3;
    selection-background-color: #f0d9b5;
    selection-color: #000;
    outline: 0;
  }

  QCheckBox {
    spacing: 6px;
    font-size: 14px;
    color: white;
    font-weight: bold;
  }

  QCheckBox::indicator {
    width: 16px;
    height: 16px;
    border: 2px solid #a67c52;
    border-radius: 4px;
    background-color: #ffffff;
  }

  QCheckBox::indicator:hover {
    border-color: #d4a373;
    background-color: #f9f0e3;
  }

  QCheckBox::indicator:checked {
    background-color: #bf9469;
    image: none;
  }

  QCheckBox::indicator:checked:hover {
    background-color: #d4a373;
  }

  QCheckBox::indicator:disabled {
    background-color: #e0e0e0;
    border-color: #c0c0c0;
  }

  #title {
    font-size: 16px;
    font-weight: bold;
    color: #bf9469;
  }
  )");
}
