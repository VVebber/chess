#include "FigureMoveForm.h"
#include "../../../Common.h"
#include "../../../managers/TextureManager.h"
#include "../../../managers/ChessBoardManager.h"

#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

#include <functional>

FigureMoveForm::FigureMoveForm()
{
  m_infoFigures = m_currentInfoChess[FIGURES].toArray();

  m_listFigure = new QComboBox;
  m_directionsGrid = new QGridLayout;
  m_directionsGrid->setHorizontalSpacing(25);
  m_directionsGrid->setContentsMargins(1, 1, 1, 1);

  m_previousId = -1;

  m_firstMove = new QSpinBox;

  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  connect(m_listFigure, &QComboBox::currentIndexChanged, [=](int id){
    ChessBoardManager::getInstance().setIdFigure(id);

    if(m_previousId != -1)
    {
      QJsonObject infoFigure = m_infoFigures.at(m_previousId).toObject();
      infoFigure[MOVE_PATTERNS] = m_infoMovePatterns;
      m_infoMovePatterns = QJsonObject();
    }

    m_previousId = id;
    updateForm();
  });
  setup();
}

void FigureMoveForm::updateForm()
{
  QJsonArray figures = m_currentInfoChess[FIGURES].toArray();

  QSpinBox* strokeLength = qobject_cast<QSpinBox*>(m_variabels.getWidget(STROKE_LENGTH));

  QJsonObject figure;
  if(figures.size() >= m_previousId)
  {
    figure = figures.at(m_previousId).toObject();
  }

  QJsonObject movePatterns = figure[MOVE_PATTERNS].toObject();

  strokeLength->setValue(movePatterns[STROKE_LENGTH].toInt());

  QJsonObject dimensions = movePatterns[DIMENSIONS].toObject();
  for(auto key : m_direction.keys())
    m_direction[key](key, dimensions[key].toArray());
}

QJsonArray FigureMoveForm::toJson()
{
 int index = m_listFigure->currentIndex();

 if(index == -1)
   return QJsonArray();

 QJsonObject infoFigure = m_infoFigures.at(index).toObject();
 QJsonObject movePatterns;

 QCheckBox* isCellEmpty = qobject_cast<QCheckBox*>(m_variabels.getWidget(IS_CELL_EMPTY));
 QSpinBox* strokeLength = qobject_cast<QSpinBox*>(m_variabels.getWidget(STROKE_LENGTH));


 movePatterns[IS_CELL_EMPTY] = isCellEmpty->isChecked();
 movePatterns[STROKE_LENGTH] = strokeLength->value();

 QJsonObject directions;
 QStringList keys = m_jsonDirection.keys();
 for(auto& key : keys)
 {
   directions.insert(key, m_jsonDirection.value(key)());
 }

 movePatterns[DIMENSIONS] = directions;

 infoFigure[MOVE_PATTERNS] = movePatterns;
 m_infoFigures[index] = infoFigure;

 return m_infoFigures;
}

void FigureMoveForm::updateJson()
{
  qDebug()<<Q_FUNC_INFO;
  m_infoFigures = m_currentInfoChess[FIGURES].toArray();
  ChessBoardManager::getInstance().setIdFigure(m_listFigure->currentIndex());

  m_listFigure->clear();
  m_jsonDirection.clear();
  m_direction.clear();
  for(int i = 0; i < m_infoFigures.size(); i++)
  {
    QJsonObject figureInfo = m_infoFigures.at(i).toObject();
    m_listFigure->addItem(figureInfo[TYPE_FIGURE].toString());
  }

  initDirectionsGrid();
}

void FigureMoveForm::setup()
{
  qDebug()<<Q_FUNC_INFO;

  initDirectionsGrid();

  QCheckBox* isCellEmpty = new QCheckBox("Клетка должна быть пустой");

  QSpinBox* strokeLength = new QSpinBox;
  m_variabels.addWidget(STROKE_LENGTH, strokeLength);

  QCheckBox* firsMove = new QCheckBox("Первый ход");
  QWidget* firsMoveWidget = initFirstMoveForm();
  firsMoveWidget->hide();

  QCheckBox* cellHasEnemy = new QCheckBox("Клетка с врагом");
  QWidget* cellHasEnemyWidget = initCellHasEnemyForm();
  cellHasEnemyWidget->hide();

  QCheckBox* isTransformation = new QCheckBox("Превращение");
  QWidget* transformationWidget = initTransformationForm();
  transformationWidget->hide();

  QCheckBox* isInitialConditions = new QCheckBox("Начальные условия");
  QWidget* initialConditionsWidget = initInitialConditionsForm();
  initialConditionsWidget->hide();

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Тип: "), 0, 0);
  layout->addWidget(m_listFigure, 0, 1);
  layout->addWidget(new QLabel("Напровление хода:"), 1, 0, 1, 2);
  layout->addLayout(m_directionsGrid, 2, 0, 1, 2, Qt::AlignHCenter);
  layout->addWidget(new QLabel("Длина хода"), 3, 0, 1, 1);
  layout->addWidget(strokeLength,3, 1, 1, 1);

  layout->addWidget(isCellEmpty, 4, 0, 1, 2);

  layout->addWidget(firsMove, 5, 0, 1, 2);
  layout->addWidget(firsMoveWidget, 6, 0, 1, 2);

  layout->addWidget(cellHasEnemy, 7, 0, 1, 2);
  layout->addWidget(cellHasEnemyWidget, 8, 0, 1, 2);

  layout->addWidget(isTransformation, 9, 0, 1, 2);
  layout->addWidget(transformationWidget, 10, 0, 1, 2);

  layout->addWidget(isInitialConditions, 11, 0, 1, 2);
  layout->addWidget(initialConditionsWidget, 12, 0, 1, 2);

  m_variabels.addWidget(IS_CELL_EMPTY, isCellEmpty);

  connect(isCellEmpty, &QCheckBox::toggled, [=](){
    m_infoMovePatterns[IS_CELL_EMPTY] = isCellEmpty->isChecked();
  });
  connect(firsMove, &QCheckBox::toggled, firsMoveWidget, &QWidget::setVisible);
  connect(isTransformation, &QCheckBox::toggled, transformationWidget, &QWidget::setVisible);
  connect(isInitialConditions, &QCheckBox::toggled, initialConditionsWidget, &QWidget::setVisible);
  connect(cellHasEnemy, &QCheckBox::toggled, cellHasEnemyWidget, &QWidget::setVisible);

  this->setLayout(layout);
}

QWidget* FigureMoveForm::initFirstMoveForm()
{
  QWidget* mainWidget = new QWidget;

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(new QLabel("Длинна хода:"));
  layout->addWidget(m_firstMove);

  mainWidget->setLayout(layout);
  return mainWidget;
}

QWidget* FigureMoveForm::initCellHasEnemyForm()
{
  QWidget* mainWidget = new QWidget;

  QComboBox* players = new QComboBox;

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(players, 0, 0, 1, 2);
  layout->addWidget(new QLabel("Напровление"), 1, 0, 1, 1);
  layout->addWidget(new QComboBox, 1, 1, 1, 1);
  layout->addWidget(new QLabel("Растояние"), 2, 0, 1, 1);
  layout->addWidget(new QSpinBox, 2, 1, 1, 1);
  layout->addWidget(new QLabel("Растояние"), 3, 0, 1, 1);
  layout->addWidget(new QComboBox, 3, 1, 1, 1);

  mainWidget->setLayout(layout);
  return mainWidget;
}

QWidget* FigureMoveForm::initTransformationForm()
{
  QWidget* mainWidget = new QWidget;

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(new QLabel("Тип"));
  layout->addWidget(new QComboBox);
  layout->addWidget(new QPushButton("+"));

  mainWidget->setLayout(layout);
  return mainWidget;
}

QWidget* FigureMoveForm::initInitialConditionsForm()
{
  QWidget* mainWidget = new QWidget;

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(new QLabel("Событие"));
  layout->addWidget(new QComboBox);

  mainWidget->setLayout(layout);
  return mainWidget;
}

void FigureMoveForm::initDirectionsGrid()
{
  clearLayout(m_directionsGrid);
  int countPlayers = m_currentInfoChess[COUNT_PLAYERS].toInt();

  for(int i = 0; i < countPlayers; i++)
  {
    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(new QLabel(QString("Игрок_%0").arg(i)), Qt::AlignHCenter);
    box->addWidget(directionsGrid());


    int x = m_directionsGrid->count() / 2;
    int y = m_directionsGrid->count() % 2;

    m_directionsGrid->addLayout(box, x, y);
  }

  m_directionsGrid->update();
}

QWidget* FigureMoveForm::directionsGrid()
{
  QWidget* mainWidget = new QWidget;

  QCheckBox* upLeft = checkBoxWithImage(-45);
  QCheckBox* up = checkBoxWithImage(0);
  QCheckBox* upRight = checkBoxWithImage(45);
  QCheckBox* rigt = checkBoxWithImage(90);
  QCheckBox* downLeft = checkBoxWithImage(-135);;
  QCheckBox* down = checkBoxWithImage(180);;
  QCheckBox* downRight = checkBoxWithImage(135);
  QCheckBox* left = checkBoxWithImage(-90);

  QGridLayout* layout = new QGridLayout(mainWidget);
  layout->setSpacing(0);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(upLeft, 0, 0);
  layout->addWidget(up, 0, 1);
  layout->addWidget(upRight, 0, 2);
  layout->addWidget(left, 1, 0);
  layout->addWidget(new QLabel("*"), 1, 1, Qt::AlignCenter);
  layout->addWidget(rigt, 1, 2);
  layout->addWidget(downLeft, 2, 0);
  layout->addWidget(down, 2, 1);
  layout->addWidget(downRight, 2, 2);



  QString player = PLAYER.arg(m_directionsGrid->count());
  m_jsonDirection.insert(player,[=]()->QJsonArray{
    QVector<QString> codes = {"UL", "U", "UR", "R", "DL", "D", "DR", "L"};
    QVector<QCheckBox*> boxes = {upLeft, up, upRight, rigt, downLeft, down, downRight, left};

    QJsonArray array;
    for (int i = 0; i < boxes.size(); ++i) {
        if (boxes[i]->isChecked())
            array.append(codes[i]);
    }
    return array;
  });

  m_direction.insert(player, [=](QString& player, QJsonArray array){

    QVector<QCheckBox*> boxes = {upLeft, up, upRight, rigt, downLeft, down, downRight, left};
    QVector<QString> codes = {"UL", "U", "UR", "R", "DL", "D", "DR", "L"};

    for(int i = 0; i < boxes.size(); i++)
    {
      boxes[i]->setChecked(array.contains(codes[i]));
    }
  });

  mainWidget->setLayout(layout);
  mainWidget->setContentsMargins(0,0,0,0);
  mainWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  return mainWidget;
}

QCheckBox* FigureMoveForm::checkBoxWithImage(int rotate)
{
  static QPixmap arrow = TextureManager::instance().getTexture(ARROW_SSTART);

  QTransform transform;

  QCheckBox* checkBox = new QCheckBox;
  transform.rotate(rotate);
  checkBox->setIcon(arrow.transformed(transform));

  return checkBox;
}

