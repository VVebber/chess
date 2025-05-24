#include "FigureForm.h"
#include "../../../Common.h"

#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>

int FigureForm::m_countPlauers;

FigureForm::FigureForm(int countPlayers)
{
  m_figureCount = new QGridLayout;
  m_startPosList = new QGridLayout;

  m_typeFigure = new QComboBox;

  m_countPlauers = countPlayers;
  setup();
}

void FigureForm::setup()
{
  setupCountFigure();
  setupStartPosList();

  m_typeFigure->addItems({"Пешка", "Конь", "Ферзь", "Слон", "Кароль", "Ладья"});

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Тип: "), 0, 0);
  layout->addWidget(m_typeFigure, 0, 1);
  layout->addWidget(new QLabel("Фигуры"), 1, 0, 1, 2, Qt::AlignCenter);
  layout->addLayout(m_figureCount, 2, 0, 1, 2);
  layout->addWidget(new QLabel("Начальные позиции"), 3, 0, 1, 2, Qt::AlignCenter);
  layout->addLayout(m_startPosList, 4, 0, 1, 2);

  QStringList keys = m_spinbox.keys();
  for(auto& key :keys)
  {
    connect(m_spinbox[key], &QSpinBox::valueChanged, [key, this](int newCount){
      if(newCount == 1)
      {
        m_poslabels[key]->setText("A1");
        return;
      } else if(newCount == 0)
      {
        m_poslabels[key]->setText("");
      }

      QString currentText = m_poslabels[key]->text();
      QStringList positions = currentText.split(',', Qt::SkipEmptyParts);

      int count = positions.size();
      if(count < newCount)
      {
        for (int i = 0; i < newCount - count; ++i) {
          positions.append("A1");
        }
      }
      else if(count > newCount)
      {
        positions = positions.mid(0, newCount);
      }
      m_poslabels[key]->setText(positions.join(","));
    });
  }

  this->setLayout(layout);
}

QJsonObject FigureForm::toJson()
{
  QJsonObject data;

  int count = 0;
  for(auto& fcount : m_spinbox)
  {
    count += fcount->value();
  }

  QJsonObject posPlayer;
  QStringList keys = m_poslabels.keys();
  for (const QString& key : m_poslabels.keys())
  {
    QStringList list = m_poslabels[key]->text().split(',', Qt::SkipEmptyParts);

    QJsonArray array;
    for (const QString &str : list) {
      array.append(str);
    }
    posPlayer.insert(key, array);
  }

  data[TYPE_FIGURE] = m_typeFigure->currentText();
  data[COUNT_FIGURE] = count;
  data[START_POSITIONS] = posPlayer;

  return data;
}

void FigureForm::setupCountFigure()
{
  QString player = "Игрок_%1";
  for(int i = 0; i < m_countPlauers; i++)
  {
    QSpinBox* spinBox = new QSpinBox;
    m_spinbox[player.arg(i)] = spinBox;

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(new QLabel(player.arg(i)));
    box->addWidget(spinBox);

    int x = m_figureCount->count() / 2;
    int y = m_figureCount->count() % 2;
    m_figureCount->addLayout(box, x, y);
  }
}

void FigureForm::chanPos(const QString& newPos, QAbstractButton* btn)
{
  QPushButton* button = qobject_cast<QPushButton*>(btn);
  QString currentText = m_updatePos[button]->text();
  QStringList positions = currentText.split(',', Qt::SkipEmptyParts);
  int i = positions.indexOf(btn->objectName());

  if(i == -1)
    return;

  positions[i] = newPos;

  m_updatePos[button]->setText(positions.join(","));
}

void FigureForm::setupStartPosList()
{
  QString player = "Игрок_%1";

  for(int i = 0; i < m_countPlauers; i++)
  {
    QLabel* pos = new QLabel();
    QPushButton* upDatePos = new QPushButton;
    upDatePos->setCheckable(true);

    m_poslabels[player.arg(i)] = pos;
    m_updatePos[upDatePos] = pos;

    QHBoxLayout* Hbox = new QHBoxLayout;
    Hbox->addWidget(new QLabel(player.arg(i)));
    Hbox->addWidget(upDatePos);
    Hbox->addWidget(new QLabel("Позиция:"));
    Hbox->addWidget(pos);

    int x = m_startPosList->count();
    m_startPosList->addLayout(Hbox, x, 0);
  }
}

