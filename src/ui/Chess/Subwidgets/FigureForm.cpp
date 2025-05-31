#include "FigureForm.h"
#include "../../../Common.h"

#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>

FigureForm::FigureForm(QJsonObject data)
{
  m_figureCount = new QGridLayout;
  m_startPosList = new QGridLayout;

  m_typeFigure = new QComboBox;
  m_typeFigure->addItems({"Пешка", "Конь", "Королева", "Слон", "Король", "Ладья"});

  if(data.contains(TYPE_FIGURE))
  {
    QString type = data.value(TYPE_FIGURE).toString();
    int index = m_typeFigure->findText(type);
    if (index != -1)
        m_typeFigure->setCurrentIndex(index);
  }

  m_countPlayers = 0;

  setup();
  updateForm(data);
}

void FigureForm::updateForm(QJsonObject data)
{
  m_countPlayers = m_currentInfoChess[COUNT_PLAYERS].toInt();
  while(m_figureCount->count() > m_countPlayers)
  {
    delete m_spinbox.take(m_spinbox.lastKey());
    removeLastFromLayout(m_figureCount);
    m_figureCount->update();
  }
  setupCountFigure(data);

  while(m_startPosList->count() > m_countPlayers)
  {
    delete m_poslabels.take(m_poslabels.lastKey());
    removeLastFromLayout(m_startPosList);
    m_startPosList->update();
  }
  setupStartPosList(data);

  connectSpinboxSignals();
}

void FigureForm::setup()
{

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Тип: "), 0, 0);
  layout->addWidget(m_typeFigure, 0, 1);
  layout->addWidget(new QLabel("Фигуры"), 1, 0, 1, 2, Qt::AlignCenter);
  layout->addLayout(m_figureCount, 2, 0, 1, 2);
  layout->addWidget(new QLabel("Начальные позиции"), 3, 0, 1, 2, Qt::AlignCenter);
  layout->addLayout(m_startPosList, 4, 0, 1, 2);
  connectSpinboxSignals();

  this->setLayout(layout);
}

void FigureForm::connectSpinboxSignals()
{
  QStringList keys = m_spinbox.keys();
  for(auto& key :keys)
  {
    m_spinbox[key]->disconnect();
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
}

QJsonObject FigureForm::toJson(QJsonObject data)
{
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

void FigureForm::setupCountFigure(QJsonObject data)
{
  for(int i = m_figureCount->count(); i < m_countPlayers; i++)
  {
    QSpinBox* spinBox = new QSpinBox;
    m_spinbox[PLAYER.arg(i)] = spinBox;

    if(data.contains(START_POSITIONS))
    {
      QJsonObject startPos = data[START_POSITIONS].toObject();
      int count = startPos.value(PLAYER.arg(i)).toArray().size();
      spinBox->setValue(count);
    }

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(new QLabel(PLAYER.arg(i)));
    box->addWidget(spinBox);

    int x = i / 2;
    int y = i % 2;
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

void FigureForm::setupStartPosList(QJsonObject data)
{

  for(int i = m_startPosList->count(); i < m_countPlayers; i++)
  {
    QLabel* pos = new QLabel();
    QPushButton* upDatePos = new QPushButton;
    upDatePos->setCheckable(true);

    m_poslabels[PLAYER.arg(i)] = pos;
    m_updatePos[upDatePos] = pos;

    QHBoxLayout* Hbox = new QHBoxLayout;
    Hbox->addWidget(new QLabel(PLAYER.arg(i)));
    Hbox->addWidget(upDatePos);
    Hbox->addWidget(new QLabel("Позиция:"));
    Hbox->addWidget(pos);

    if(data.contains(START_POSITIONS))
    {
      QJsonArray startPos = data[START_POSITIONS].toObject().value(PLAYER.arg(i)).toArray();
      QStringList parts;
      for (auto part : startPos)
      {
        parts.append(part.toString());
      }
      pos->setText(parts.join(","));
    }

    int x = m_startPosList->count();
    m_startPosList->addLayout(Hbox, i, 0);
  }
}

