#include "MoveConditionForm.h"
#include "../../../Common.h"

#include <QLabel>
#include <QLayout>
#include <QComboBox>
#include <QPushButton>

MoveConditionForm::MoveConditionWidgets::MoveConditionWidgets()
{
  direction = new QComboBox;
  figureType = new QComboBox;
  condition = new QComboBox;
  event = new QComboBox;

  QStringList directionTexts = {"влево-вверх", "вверх", "вправо-вверх", "влево",
      "вправо", "влево-вниз", "вниз", "вправо-вниз"};

  QStringList directionCodes = {"UL", "U", "UR", "L",
      "R", "DL", "D", "DR"};

  for (int i = 0; i < directionTexts.size() && i < directionCodes.size(); ++i) {
      direction->addItem(directionTexts[i], directionCodes[i]);
  }

  QMap<QString, QString> groupOptions = {
      {ALLIES, "Союзники"},
      {ENEMIES, "Враги"},
      {ALL,    "Все"}
  };

  QMap<QString, QString> conditionOptions = {
      {CONDITION_HAS_PIECE, "Есть фигура"}
  };

  QMap<QString, QString> eventOptions = {
      {EVENT_CANCEL_MOVE, "Отмена хода"},
      {EVENT_ADD_MOVE,    "Создание хода"}
  };

  // Пример заполнения combobox'ов:
  for (auto it = groupOptions.constBegin(); it != groupOptions.constEnd(); ++it)
      figureType->addItem(it.value(), it.key());

  for (auto it = conditionOptions.constBegin(); it != conditionOptions.constEnd(); ++it)
      condition->addItem(it.value(), it.key());

  for (auto it = eventOptions.constBegin(); it != eventOptions.constEnd(); ++it)
      event->addItem(it.value(), it.key());
}

MoveConditionForm::MoveConditionForm()
{
  m_listEventWidget = new QVBoxLayout;
  m_playersList = new QComboBox;

  setup();
}

void MoveConditionForm::setup()
{
  QPushButton* addBtn = new QPushButton("Добавить условие");
  connect(addBtn, &QPushButton::clicked, this, &MoveConditionForm::onAddCondition);

  QGridLayout* titleLayout = new QGridLayout(this);
  titleLayout->addWidget(new QLabel("Условия для"), 0, 0);
  titleLayout->addWidget(m_playersList, 0, 1);

  titleLayout->addLayout(m_listEventWidget, 1, 0, 1, 2);
  titleLayout->addWidget(addBtn, 2, 0, 1, 2);
}

QWidget* MoveConditionForm::createConditionWidget()
{
  QWidget* widget = new QWidget;
  widget->setObjectName("widget");
  QGridLayout* layout = new QGridLayout(widget);

  MoveConditionWidgets widgets;

  layout->addWidget(new QLabel("Напр:"), 1, 0);
  layout->addWidget(widgets.direction, 1, 1); // направления

  layout->addWidget(new QLabel("Тип:"), 1, 2);
  layout->addWidget(widgets.figureType, 1, 3); // тип фигуры

  layout->addWidget(new QLabel("Усл:"), 2, 0);
  layout->addWidget(widgets.condition, 2, 1, 1, 3); // условие

  layout->addWidget(new QLabel("Соб:"), 3, 0);
  layout->addWidget(widgets.event, 3, 1, 1, 3); // событие

  layout->addWidget(new QLabel("Услови"), 0, 0, 1, 2);

  QPushButton* deleteBtn = new QPushButton("Удалить");
  layout->addWidget(deleteBtn, 0, 2, 1, 2);

  m_listEvent.append(widgets);

  connect(deleteBtn, &QPushButton::clicked, this, [this, widget, widgets]() {
      m_listEventWidget->removeWidget(widget);
      widget->deleteLater();

      int index = m_listEvent.indexOf(widgets);
      if (index != -1) {
          m_listEvent.removeAt(index);
      }
  });

  widget->setStyleSheet(R"(
  #widget {
      background-color: rgba(255, 255, 255, 0.1);
      border: 2px solid #a67c52;
      border-radius: 8px;
      padding: 6px;
  }

  QComboBox {
    border: 2px solid #a67c52;
    border-radius: 4px;
    padding: 4px 24px 4px 8px;
    background-color: #ffffff;
    color: #2e2e2e;
    font-size: 14px;
  }
    )");

  return widget;
}

void MoveConditionForm::onAddCondition()
{
  QWidget* condWidget = createConditionWidget();
  m_listEventWidget->addWidget(condWidget);
}

QJsonObject MoveConditionForm::toJson(QJsonObject data)
{
  QJsonObject movePatterns = data.value(MOVE_PATTERNS).toObject();
  QJsonObject moveRules = movePatterns.value(MOVE_RULES).toObject();

  if(m_countPlayers == 0)
    return data;

  int index = 0;
  QJsonObject events;
  for (const MoveConditionWidgets& widgets : m_listEvent)
  {
    QJsonObject eventObject;

    eventObject[DIRECTIONS]  = widgets.direction->currentData().toString();
    eventObject[TYPE_FIGURE] = widgets.figureType->currentData().toString();
    eventObject[CONDITION]   = widgets.condition->currentData().toString();
    eventObject[ACTION]      = widgets.event->currentData().toString();
    events[EVENT_N.arg(index)] = eventObject;

    index++;
  }

  moveRules[PLAYER_EN.arg(m_playersList->currentIndex())] = events;
  movePatterns[MOVE_RULES] = moveRules;
  data[MOVE_PATTERNS] = movePatterns;

  return data;
}

void MoveConditionForm::updateForm()
{
  m_playersList->clear();
  for(int i = 0; i < m_countPlayers; i++)
  {

    m_playersList->addItem(PLAYER_RU.arg(i) ,PLAYER_EN.arg(i));
  }
}
