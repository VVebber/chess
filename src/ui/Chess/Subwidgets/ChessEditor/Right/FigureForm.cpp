#include "FigureForm.h"
#include "../../../../../Common.h"
#include "../../../../../managers/SwitchEditorButton.h"

#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QStyleOption>
#include <QPainter>

void FigureForm::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);  // обязательно вызываем базовую реализацию
}

FigureForm::FigureForm(int countPlayer) : m_countPlayers(countPlayer)
{
  setObjectName("FigureForm");
  setAutoFillBackground(true);

  m_figureCountList = new QGridLayout;
  m_startPosList = new QGridLayout;
  m_typeFigure = new QComboBox;

  m_typeFigure->addItems({"Пешка", "Конь", "Королева", "Слон", "Король", "Ладья"});

  setup();
  updateForm();
  setupStyleSheet();
}

FigureForm::FigureSettings::FigureSettings()
{
  spinBox = new QSpinBox();
  updatePos = new QPushButton();
  posLabel = new QLabel();

  updatePos->setCheckable(true);
}

void FigureForm::updateFormInfo(QJsonObject data)
{
  QJsonObject  startPos = data[START_POSITIONS].toObject();
  for(int i = 0; i < m_figures.count(); i++)
  {
    QJsonArray array = startPos[m_figures[i].playerKey].toArray();
    QStringList list;
    for(auto str : array)
      list.push_back(str.toString());
    m_figures[i].spinBox->setValue(list.size());
    m_figures[i].posLabel->setText(list.join(","));

    QString type = data[TYPE_FIGURE].toString();
    int j = m_typeFigure->findText(type);
    m_typeFigure->setCurrentIndex(j == -1? 0: j);
  }
}

void FigureForm::updateForm()
{
  qDebug()<<Q_FUNC_INFO;
  while(m_figures.count() > m_countPlayers)
  {
    m_figures.removeLast();
    removeLastFromLayout(m_figureCountList);
    removeLastFromLayout(m_startPosList);

    m_figureCountList->update();
    m_startPosList->update();
  }
  setupSettingsForm();

  connectSpinboxSignals();
}

void FigureForm::setup()
{
  QLabel* titleFigure = new QLabel("Фигуры");
  titleFigure->setObjectName("title");

  QLabel* titleStartPos = new QLabel("Начальные позиции");
  titleStartPos->setObjectName("title");

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Тип: "), 0, 0);
  layout->addWidget(m_typeFigure, 0, 1);
  layout->addWidget(titleFigure, 1, 0, 1, 2, Qt::AlignCenter);
  layout->addLayout(m_figureCountList, 2, 0, 1, 2);
  layout->addWidget(titleStartPos, 3, 0, 1, 2, Qt::AlignCenter);
  layout->addLayout(m_startPosList, 4, 0, 1, 2);
  connectSpinboxSignals();

  this->setLayout(layout);
}

void FigureForm::connectSpinboxSignals()
{
  for (auto& figure : m_figures)
  {
    figure.spinBox->disconnect();
    connect(figure.spinBox, &QSpinBox::valueChanged, [this, &figure](int newCount){
      if(newCount == 1)
      {
        figure.posLabel->setText("A1");
        return;
      } else if(newCount == 0)
      {
        figure.posLabel->setText("");
      }

      QString currentText = figure.posLabel->text();
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
      figure.posLabel->setText(positions.join(","));
    });
  }
}

QJsonObject FigureForm::toJson(QJsonObject data)
{
  int count = 0;

  QJsonObject posFigure;
  for(const auto& figure : m_figures)
  {
    count += figure.spinBox->value();

    QStringList list = figure.posLabel->text().split(',', Qt::SkipEmptyParts);

    QJsonArray array;
    for (const QString& str : list)
    {
      array.append(str);
    }

    posFigure.insert(figure.playerKey, array);
  }
  data[TYPE_FIGURE] = m_typeFigure->currentText();
  data[COUNT_FIGURE] = count;
  data[START_POSITIONS] = posFigure;
  return data;
}

void FigureForm::chanPos(const QString& newPos, QAbstractButton* btn)
{
  // QPushButton* button = qobject_cast<QPushButton*>(btn);
  // QString currentText;// = m_updatePos[button]->text();
  // QStringList positions = currentText.split(',', Qt::SkipEmptyParts);
  // int i = positions.indexOf(btn->objectName());

  // if(i == -1)
  return;

  // positions[i] = newPos;

  // m_updatePos[button]->setText(positions.join(","));
}

void FigureForm::setupSettingsForm()
{
  for(int i = m_figures.size(); i < m_countPlayers; i++)
  {
    FigureSettings figure;
    figure.playerKey = PLAYER_EN.arg(i);

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(new QLabel(PLAYER_EN.arg(i)));
    box->addWidget(figure.spinBox);

    int x = i / 2;
    int y = i % 2;
    m_figureCountList->addLayout(box, x, y);

    QHBoxLayout* Hbox = new QHBoxLayout;
    Hbox->addWidget(new QLabel(PLAYER_EN.arg(i)));
    Hbox->addWidget(figure.updatePos);
    Hbox->addWidget(new QLabel("Позиция:"));
    Hbox->addWidget(figure.posLabel);
    m_startPosList->addLayout(Hbox, i, 0);

    SwitchEditorButton::instance().addButton(figure.updatePos);
    m_figures.push_back(figure);
  }
}

void FigureForm::updateCountPlayers(int countPlayer)
{
  m_countPlayers = countPlayer;
  updateForm();
}

void FigureForm::setupStyleSheet()
{
  qDebug()<<Q_FUNC_INFO;
  setStyleSheet(R"(
    #FigureForm {
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
    width: 24px;
    border-left: 1px solid #a67c52;
    background-color: #f0e6d2; /* <- УСТАНОВИМ НЕПРОЗРАЧНЫЙ ФОН */
    border-top-right-radius: 4px;
    border-bottom-right-radius: 4px;
  }

  QComboBox::down-arrow {
    width: 0;
    height: 0;
    margin-right: 6px;
    border-left: 6px solid transparent;
    border-right: 6px solid transparent;
    border-top: 6px solid #6e4f32;
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

  QPushButton {
    width: 20px;
    height: 20px;
    border: 2px solid #a67c52;
    border-radius: 4px;
    background-color: #f0e6d2;
  }

  QPushButton:hover {
    background-color: #e6d3b3;
    border-color: #c29668;
  }

  QPushButton:checked {
    background-color: #8b5e3c;
    border-color: #70452a;
  }

  QPushButton:pressed {
    background-color: #a67c52;
  }

  #title {
    font-size: 16px;
    font-weight: bold;
    color: #bf9469;
  }
  )");
}

