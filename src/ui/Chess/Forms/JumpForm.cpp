#include "JumpForm.h"
#include "../../../Common.h"

#include <QLabel>
#include <QSpinBox>
#include <QJsonArray>
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>

void JumpForm::paintEvent(QPaintEvent* event)
{
  QStyleOption opt;
  opt.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

  QWidget::paintEvent(event);
}

JumpForm::JumpForm()
{
  setObjectName("JumpForm");
  m_moveList = new QListWidget(this);

  m_spinX = new QSpinBox();
  m_spinX->setPrefix("X: ");
  m_spinX->setRange(-1000, 1000);

  m_spinY = new QSpinBox();
  m_spinY->setPrefix("Y: ");
  m_spinY->setRange(-1000, 1000);

  setup();
  setupStyleSheet();
}

void JumpForm::setup()
{
  QPushButton* addMove = new QPushButton("Добавить ход");
  QPushButton* removeMove = new QPushButton("Удалить ход");

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(m_moveList, 0, 0, 2 ,1);
  layout->addWidget(m_spinX, 0, 1, 1, 1);
  layout->addWidget(m_spinY, 1, 1, 1, 1);

  QGridLayout* mainGrid = new QGridLayout(this);
  mainGrid->addWidget(new QLabel("Ходы:"), 0, 0);
  mainGrid->addLayout(layout, 1, 0, 1, 2);
  mainGrid->addWidget(addMove, 2, 0);
  mainGrid->addWidget(removeMove, 2, 1);

  connect(addMove, &QPushButton::clicked, this, &JumpForm::addMoveClicked);
  connect(removeMove, &QPushButton::clicked, this, &JumpForm::removeMoveClicked);


  this->setLayout(mainGrid);
}

void JumpForm::addMoveClicked()
{
  int x = m_spinX->value();
  int y = m_spinY->value();
  QString coordText = QString("%1, %2").arg(x).arg(y);
  m_moveList->addItem(coordText);
}

void JumpForm::removeMoveClicked()
{
  QListWidgetItem* item = m_moveList->currentItem();
  if (item)
    delete item;
}

QJsonObject JumpForm::toJson(QJsonObject data)
{
  if(m_countPlayers == 0)
    return data;
  QJsonObject movePatterns = data.value(MOVE_PATTERNS).toObject();
  QJsonObject jump = movePatterns.value(JUMPS).toObject();
  QJsonObject directions = jump.value(DIMENSIONS).toObject();

  QJsonArray moveArray;

  for (int i = 0; i < m_moveList->count(); ++i) {
    QListWidgetItem* item = m_moveList->item(i);
    QStringList coords = item->text().split(",");
    if (coords.size() == 2) {
      int x = coords[0].trimmed().toInt();
      int y = coords[1].trimmed().toInt();

      QJsonObject point;
      point["x"] = x;
      point["y"] = y;

      moveArray.append(point);
    }
  }
  for(int i = 0; i < m_countPlayers; i++)
    directions[PLAYER_EN.arg(i)] = moveArray;

  jump[JUMPS] = directions;
  movePatterns[DIRECTIONS] = jump;
  data[MOVE_PATTERNS] = movePatterns;


  return data;
}

void JumpForm::setupStyleSheet()
{
  setStyleSheet(R"(
    #JumpForm {
      background-color: rgba(255, 255, 255, 0.1);
      border: 2px solid #a67c52;
      border-radius: 8px;
      padding: 6px;
    }

    QListWidget {
      border: 2px solid #a67c52;
      border-radius: 6px;
      background-color: #fffaf3;
      color: #2e2e2e;
      font-size: 14px;
      padding: 4px;
    }

    QListWidget::item {
      padding: 6px 10px;
      border: none;
    }

    QListWidget::item:selected {
      background-color: #f0d9b5;
      color: #000;
      border-radius: 4px;
    }

    QListWidget::item:hover {
      background-color: #f9e7c5;
      border-radius: 4px;
    }

  )");
}

