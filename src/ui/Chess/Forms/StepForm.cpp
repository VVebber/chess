#include "StepForm.h"
#include "../../../Common.h"
#include "../../../managers/TextureManager.h"

#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QJsonArray>
#include <QStyleOption>
#include <QPainter>

void StepForm::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}


StepForm::StepForm()
{
  setObjectName("StepForm");
  m_strokeLength = new QSpinBox;
  m_playersList = new QComboBox;

  m_directionBoxes = {
    checkBoxWithImage(-45), checkBoxWithImage(0),
    checkBoxWithImage(45),
    checkBoxWithImage(-90), checkBoxWithImage(90),
    checkBoxWithImage(-135),
    checkBoxWithImage(180), checkBoxWithImage(135)
  };

  setup();
  setupStyleSheet();


  connect(m_playersList, &QComboBox::currentIndexChanged, this, &StepForm::updateForm2);
}

void StepForm::setup()
{
  qDebug()<<Q_FUNC_INFO;

  updateForm();

  QGridLayout* mainLayout = new QGridLayout(this);
  mainLayout->addWidget(new QLabel("Напровление хода\nдля игрока:"), 0, 0, 1, 1);
  mainLayout->addWidget(m_playersList, 0, 1, 1, 1);
  mainLayout->addWidget(setupDirectionsGrid(), 1, 0, 1, 2, Qt::AlignCenter);
  mainLayout->addWidget(new QLabel("Длина хода"), 2, 0, 1, 1);
  mainLayout->addWidget(m_strokeLength, 2, 1, 1, 1);

  this->setLayout(mainLayout);
}

QWidget* StepForm::setupDirectionsGrid()
{
  QWidget* mainWidget = new QWidget;

  QGridLayout* layout = new QGridLayout(mainWidget);
  layout->setSpacing(0);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_directionBoxes[0], 0, 0);
  layout->addWidget(m_directionBoxes[1], 0, 1);
  layout->addWidget(m_directionBoxes[2], 0, 2);
  layout->addWidget(m_directionBoxes[3], 1, 0);
  layout->addWidget(new QLabel("*"), 1, 1, Qt::AlignCenter);
  layout->addWidget(m_directionBoxes[4], 1, 2);
  layout->addWidget(m_directionBoxes[5], 2, 0);
  layout->addWidget(m_directionBoxes[6], 2, 1);
  layout->addWidget(m_directionBoxes[7], 2, 2);

  mainWidget->setLayout(layout);
  mainWidget->setContentsMargins(0,0,0,0);
  mainWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

QJsonObject StepForm::toJson(QJsonObject data)
{
  if(m_countPlayers == 0)
    return data;
  QJsonObject movePatterns = data.value(MOVE_PATTERNS).toObject();
  QJsonObject directions = movePatterns.value(DIRECTIONS).toObject();
  QJsonObject step = directions.value(STEPS).toObject();


  QStringList directionCodes = {"UL", "U", "UR", "L", "R", "DL", "D", "DR"};

  QString str = m_playersList->currentData().toString();

  QJsonArray array;
  for (int i = 0; i < m_directionBoxes.size(); ++i)
  {
    if (m_directionBoxes[i]->isChecked())
    {
      array.append(directionCodes[i]);
    }
  }

  step[str] = array;
  directions[STEPS] = step;
  movePatterns[DIRECTIONS] = directions;
  movePatterns[STROKE_LENGTH] = m_strokeLength->value();

  data[MOVE_PATTERNS] = movePatterns;

  return data;
}

QCheckBox* StepForm::checkBoxWithImage(int rotate)
{
  static QPixmap arrow = TextureManager::instance().getTexture(ARROW_START);

  QTransform transform;

  QCheckBox* checkBox = new QCheckBox;
  transform.rotate(rotate);
  checkBox->setIcon(arrow.transformed(transform));

  return checkBox;
}

void StepForm::updateForm()
{
  m_playersList->clear();
  for(int i = 0; i < m_countPlayers; i++)
  {
    m_playersList->addItem(PLAYER_RU.arg(i) ,PLAYER_EN.arg(i));
  }
}

void StepForm::updateForm2()
{
  QStringList directionCodes = {"UL", "U", "UR", "L", "R", "DL", "D", "DR"};

  QString str = m_playersList->currentData().toString();
  QJsonArray array = m_data[str].toArray();
  for (int i = 0; i < m_directionBoxes.size(); ++i)
  {
    m_directionBoxes[i]->setChecked(array.contains(directionCodes[i]));
  }
}

void StepForm::onUpdateFormInfo(const QJsonObject& data)
{
  QJsonObject movePatterns = data.value(MOVE_PATTERNS).toObject();
  QJsonObject direction = movePatterns.value(DIRECTIONS).toObject();
  m_data = direction.value(STEPS).toObject();

  m_strokeLength->setValue(movePatterns.value(STROKE_LENGTH).toInt());
  updateForm2();
}

void StepForm::setupStyleSheet()
{
  setStyleSheet(R"(
    #StepForm {
      background-color: rgba(255, 255, 255, 0.1);
      border: 2px solid #a67c52;
      border-radius: 8px;
      padding: 6px;
    }
  )");
}
