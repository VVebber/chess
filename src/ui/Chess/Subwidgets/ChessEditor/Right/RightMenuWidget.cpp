#include "RightMenuWidget.h"
#include "FigureForm.h"
#include "FigureMoveForm.h"

#include "../../../../../Common.h"
#include "../../../../../core/ChessInfoJson.h"

#include <QMenu>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QScrollArea>
#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QJsonArray>

RightMenuWidget::RightMenuWidget()
{
  setObjectName("RightMenuWidget");
  m_dimensions = new QLineEdit;
  m_nameChess = new QLineEdit;
  m_countPlayers = new QSpinBox;
  m_countPlayers->setFocusPolicy(Qt::StrongFocus);

  m_btnSwich = new QButtonGroup;

  m_figuresFormList = new QVBoxLayout;

  setup();
  setupVariabels();
  setupStyleSheet();
}

void RightMenuWidget::updatePosFigure(const QString& pos, QAbstractButton* btn)
{
  QPushButton* button = qobject_cast<QPushButton*>(btn);
  for(auto& object : m_figuresListObject)
  {
    for(auto& figure : object->m_figures)
      if(btn == figure.updatePos)
      {
        QString currentText = figure.posLabel->text();
        QStringList positions = currentText.split(',', Qt::SkipEmptyParts);
        int i = positions.indexOf(btn->objectName());

        if(i == -1)
          return;

        positions[i] = pos;

        figure.posLabel->setText(positions.join(","));
        return;
      }
  }
}

void RightMenuWidget::setupVariabels()
{
  m_dimensions->setPlaceholderText("2x2");
  m_nameChess->setPlaceholderText("Введите название");
  m_countPlayers->setValue(0);
}

void RightMenuWidget::updateFormInfo(QJsonObject data)
{
  m_nameChess->setText(data[NAME].toString());
  m_countPlayers->setValue(data[COUNT_PLAYERS].toInt());

  clearLayout(m_figuresFormList);
  m_figuresListObject.clear();

  QJsonArray figures = data[FIGURES].toArray();
  for(int i = 0; i < figures.size(); i++)
  {
    onClickedAddFigureForm();
    m_figuresListObject[i]->updateFormInfo(figures[i].toObject());
  }

  QJsonObject board = data[BOARD].toObject();
  QJsonArray array = board[DIMENSIONS].toArray();
  QStringList list;
  for(auto str : array)
    list.push_back(str.toString());

  m_dimensions->setText(list.join("x"));
}

void RightMenuWidget::setup()
{
  QWidget* mainWidget = new QWidget;
  mainWidget->setStyleSheet("background: transparent;"); // <- проверь это!

  QScrollArea* scrol = new QScrollArea;
  scrol->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  scrol->setWidgetResizable(true);

  QLabel* features = new QLabel("Свойтва");
  features->setObjectName("title");
  QPushButton* saveProperties = new QPushButton("Сохранить/Обновить");

  QToolButton* toolBtn = initFiguresToolButton();
  QWidget* figuresWidget = initFiguresWidget();

  QGridLayout* mainLayout = new QGridLayout;
  mainLayout->addWidget(features, 0, 0, 1, 2, Qt::AlignVCenter);
  mainLayout->addWidget(new QLabel("Название:"), 1, 0, 1, 1);
  mainLayout->addWidget(m_nameChess, 1, 1, 1, 1);

  mainLayout->addWidget(new QLabel("Размеры:"), 2, 0, 1, 1);
  mainLayout->addWidget(m_dimensions, 2, 1, 1, 1);

  mainLayout->addLayout(initPlayerCountRow(), 3, 0, 1, 2);
  mainLayout->addWidget(toolBtn, 4, 0, 1, 2);
  mainLayout->addWidget(figuresWidget, 5, 0, 1, 2);
  mainLayout->addWidget(saveProperties, 6, 0, 1, 2);

  QVBoxLayout* layout = new QVBoxLayout(mainWidget);
  layout->addLayout(mainLayout);
  layout->addStretch();

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mainWidget->setFixedWidth(mainWidget->size().width() * 1.4);

  scrol->setFixedWidth(mainWidget->width());
  scrol->setWidget(mainWidget);

  QVBoxLayout* thisLayout = new QVBoxLayout(this);
  thisLayout->setSpacing(0);
  layout->setContentsMargins(10, 10, 20, 0);

  thisLayout->addWidget(scrol);
  this->setLayout(thisLayout);
  this->setFixedWidth(scrol->size().width());

  connect(toolBtn, &QToolButton::clicked, this, [figuresWidget](){
    figuresWidget->setVisible(!figuresWidget->isVisible());
  });

  connect(saveProperties, &QPushButton::clicked, this, &RightMenuWidget::onClickedSaveJson);
}

void RightMenuWidget::onClickedAddFigureForm()
{
  qDebug()<<Q_FUNC_INFO;
  FigureForm* figureForm = new FigureForm(m_countPlayers->value());
  m_figuresListObject.append(figureForm);

  connect(m_countPlayers, &QSpinBox::valueChanged, figureForm, &FigureForm::updateCountPlayers);

  m_figuresFormList->addWidget(figureForm);
}

void RightMenuWidget::onClickedSaveJson()
{
  qDebug()<<Q_FUNC_INFO;
  QRegularExpression regex(R"(^(\d+)(x\d+)*$)");
  if (!regex.match(m_dimensions->text()).hasMatch()) {
    qWarning()<<"Incorrect board size entered";
  }
  QStringList parts = m_dimensions->text().split("x");

  QJsonArray dimensions;
  for (const QString &part : parts)
    dimensions.append(part);

  ChessInfoJson& data = ChessInfoJson::instance();

  QJsonObject board = data.getValue(BOARD).toObject();
  board[DIMENSIONS] = dimensions;

  data.addOrUpdateKey(BOARD, board);
  data.addOrUpdateKey(COUNT_PLAYERS, m_countPlayers->value());
  data.addOrUpdateKey(NAME, m_nameChess->text());

  QJsonArray figuresArray = data.getValue(FIGURES).toArray();
  if(m_btnSwich->checkedId() == 0)
  {
    for(int i = 0; i < m_figuresListObject.size(); i++)
      if(i < figuresArray.size())
      {
        figuresArray[i] = m_figuresListObject[i]->toJson(figuresArray[i].toObject());
      }
      else
      {
        figuresArray.append(m_figuresListObject[i]->toJson(QJsonObject()));
      }
  }
  else
  {
    FigureMoveForm* form = qobject_cast<FigureMoveForm*>(m_valiabeles.getWidget(FIGURE_MOVE_FORM));
    form->toJson(figuresArray);
  }

  data.addOrUpdateKey(FIGURES, figuresArray);

  updateScheneJson(data.getData());
  data.debugDump();
  if(!m_nameChess->text().isEmpty())
    data.saveToFile(m_nameChess->text());
}

QHBoxLayout* RightMenuWidget::initPlayerCountRow()
{
  QLabel* label = new QLabel("Количество игроков");

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(label);
  layout->addWidget(m_countPlayers);

  return layout;
}

QToolButton* RightMenuWidget::initFiguresToolButton()
{
  QToolButton* toolBtn = new QToolButton;
  toolBtn->setText("Фигуры");

  QMenu* menu = new QMenu(toolBtn);
  toolBtn->setMenu(menu);
  toolBtn->setPopupMode(QToolButton::MenuButtonPopup);

  return toolBtn;
}

QWidget* RightMenuWidget::initFiguresWidget()
{
  QWidget* widget = new QWidget;

  m_valiabeles.addWidget(FIGURE_FORM, initFiguresFormList());
  FigureMoveForm* form =  new FigureMoveForm(m_countPlayers->value());

  m_valiabeles.addWidget(FIGURE_MOVE_FORM, form);

  QVBoxLayout* layout = new QVBoxLayout(widget);
  layout->addLayout(initModeSwitchFigure());
  layout->addWidget(m_valiabeles.getWidget(FIGURE_FORM));
  layout->addWidget(form);

  widget->setLayout(layout);
  widget->setVisible(false);

  onClickedSwich();
  connect(m_countPlayers, &QSpinBox::valueChanged, form, &FigureMoveForm::onUpdateCountPlaters);

  return widget;
}

QWidget* RightMenuWidget::initFiguresFormList()
{
  QWidget* mainWidget = new QWidget;
  QPushButton* addFigure = new QPushButton("Добавить");

  QVBoxLayout* figuresList = new QVBoxLayout;
  figuresList->addLayout(m_figuresFormList);
  figuresList->addWidget(addFigure);

  connect(addFigure, &QPushButton::clicked, this, &RightMenuWidget::onClickedAddFigureForm);

  mainWidget->setLayout(figuresList);
  return mainWidget;
}

QHBoxLayout* RightMenuWidget::initModeSwitchFigure()
{
  QHBoxLayout* layout = new QHBoxLayout;

  QPushButton* btn1 = new QPushButton("Фигуры");
  QPushButton* btn2 = new QPushButton("Ходы");

  btn1->setCheckable(true);
  btn2->setCheckable(true);
  btn1->setChecked(true);

  m_btnSwich->addButton(btn1, 0);
  m_btnSwich->addButton(btn2, 1);

  layout->addWidget(btn1);
  layout->addWidget(btn2);

  FigureMoveForm* form = qobject_cast<FigureMoveForm*>(m_valiabeles.getWidget(FIGURE_MOVE_FORM));

  connect(m_btnSwich, &QButtonGroup::buttonClicked, this, &RightMenuWidget::onClickedSwich);
  return layout;
}

void RightMenuWidget::onClickedSwich()
{
  int i = m_btnSwich->checkedId();
  if(i == 0)
  {
    m_valiabeles.getWidget(FIGURE_FORM)->show();
    m_valiabeles.getWidget(FIGURE_MOVE_FORM)->hide();

    // ChessBoardManager::getInstance().setEditMode(EditMode::Standard);
  }
  else if(i == 1)
  {
    FigureMoveForm* form = qobject_cast<FigureMoveForm*>(m_valiabeles.getWidget(FIGURE_MOVE_FORM));

    m_valiabeles.getWidget(FIGURE_FORM)->hide();
    form->show();

    form->onUpdateFormInfo(ChessInfoJson::instance().getData());

    // ChessBoardManager::getInstance().setEditMode(EditMode::FigureSettings);
  }
  // ChessBoardManager::getInstance().m_currentScene->update();
}

void RightMenuWidget::setupStyleSheet()
{
  setStyleSheet(R"(
    #RightMenuWidget {
        background: transparent;
    }

    QLabel {
        color: white;
        font-size: 14px;
        font-weight: bold;
    }

    #title {
      font-weight: bold;
      font-size: 29px;
      border-bottom: 2px dashed #a67c52;
      padding-bottom: 2px;
    }

    QLineEdit {
      background-color: rgba(255, 255, 255, 0.8);
      border: none;
      border-bottom: 2px solid #a67c52;
      border-radius: 0px;
      padding: 4px;
      font-size: 14px;
      color: white;
    }

    QSpinBox {
      background-color: rgba(255, 255, 255, 0.8);
      border: 2px solid #a67c52;
      border-radius: 6px;
      padding: 4px;
      color: white;
      font-size: 13px;
    }

    QPushButton, QToolButton {
        background-color: #2c3e50;
        border: 3px solid #8b5e3c;
        border-radius: 8px;
        padding: 5px 10px;
        color: white;
        font-weight: bold;
    }

    QPushButton:hover, QToolButton:hover {
        background-color: #34495e;
        border: 2px solid #2980b9;
    }

    QPushButton:checked {
        background-color: #cba26e;
    }

    QScrollArea {
        background: transparent;
    }

    QGroupBox {
        border: 1px solid #bfa27d;
        border-radius: 6px;
        margin-top: 6px;
    }

    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top center;
        padding: 0 4px;
        background-color: rgba(210, 180, 140, 0.6);
    }

    QScrollBar:vertical {
        background: transparent;
        width: 10px;
        margin: 2px 0 2px 0;
        border: none;
    }

    QScrollBar::handle:vertical {
        background: rgba(166, 124, 82, 0.6); /* Полупрозрачный коричневый */
        min-height: 20px;
        border-radius: 4px;
    }

    QScrollBar::handle:vertical:hover {
        background: rgba(166, 124, 82, 0.9); /* Более насыщенный при наведении */
    }

    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
    height: 0px;
    subcontrol-position: none;
    subcontrol-origin: margin;
    }

    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none;
    }
    )");
}

