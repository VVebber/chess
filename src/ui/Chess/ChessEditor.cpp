#include "ChessEditor.h"
#include "../../Common.h"
#include "../../managers/ChessBoardManager.h"

#include "Subwidgets/FigureForm.h"

#include <QMenu>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QJsonArray>
#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QWidgetAction>
#include <QGraphicsView>

ChessEditor::ChessEditor()
{
  m_dimensions = new QLineEdit;
  m_nameBoard = new QLineEdit;
  m_countPlayers = new QSpinBox;
  m_figuresListWidget = new QVBoxLayout;

  m_btnGroup = new QButtonGroup;
  m_btnGroup->setExclusive(false);

  m_display = new QGraphicsView;
  m_currentType = CellType::None;

  connect(this, &ChessEditor::update,
          &ChessBoardManager::getInstance(), &ChessBoardManager::update);

  connect(&ChessBoardManager::getInstance(), &ChessBoardManager::cellName,
          this, &ChessEditor::toggleCellState);
  setup();
}

bool ChessEditor::toggleCellInArray(QJsonObject& boardObj, const QString& arrayKey, const QString& cell)
{
    QJsonArray cells = boardObj.value(arrayKey).toArray();
    int index = findIndexInJsonArray(cells, cell);

    if (index != -1)
        cells.removeAt(index);
    else
        cells.append(cell);

    boardObj[arrayKey] = cells;
    return true;
}

void ChessEditor::toggleCellState(const QString cell)
{
  if (cell.isEmpty())
      return;

  QJsonObject boardObj = m_infoBoard.value(BOARD).toObject();
  bool modified = false;

  switch (m_currentType) {
  case CellType::NoShow:
      modified = toggleCellInArray(boardObj, NO_SHOW_CELLS, cell);
      break;
  case CellType::Special:
      // modified = toggleCellInArray(boardObj, SPECIAL_CELLS, cell);
      break;
  case CellType::Wrap:
      // modified = toggleCellInWrapArray(boardObj, WRAP_CELLS, cell);
      break;
  default:
      break;
  }

  if (modified) {
      m_infoBoard[BOARD] = boardObj;
      update(m_infoBoard);
  }

  if(boardObj.contains(TYPE_CHESS))
  {
    int id = m_btnGroup->checkedId();
    if(id <= 2)
      return;

    QAbstractButton* btn = m_btnGroup->button(id);
    if(btn->objectName().isEmpty())
    {
      btn->setObjectName(cell);
      return;
    }

   m_updatePos[id]->chanPos(cell, btn);
   btn->setObjectName("");
  }
}

void ChessEditor::setup()
{
  QWidget* mainWidget = new QWidget(this);

  QGridLayout* layout = new QGridLayout;
  layout->setSpacing(0);
  layout->addWidget(initTopToolbar(), 0, 0, 1, 3);
  layout->addWidget(initLeftSidebar(), 1, 0, 1, 1, Qt::AlignTop);
  layout->addWidget(initCenterSidebar(), 1, 1, 1, 1);
  layout->addWidget(initRightSidebar(), 1, 2, 1, 1, Qt::AlignTop);

  mainWidget->setLayout(layout);
  mainWidget->setFixedSize(1280, 720);
}

QWidget* ChessEditor::initTopToolbar()
{
  QWidget* mainWidget = new QWidget;

  QPushButton* back = new QPushButton("назад");

  QPushButton* btnNoShowCells = setupBtnIcon(LINK_IMG_DELETE_1);
  btnNoShowCells->setCheckable(true);
  btnNoShowCells->setObjectName(NO_SHOW_CELLS);
  btnNoShowCells->setFixedSize(QSize(55,55));
  btnNoShowCells->setIconSize(QSize(50,50));

  QPushButton* add = setupBtnIcon(LINK_IMG_ADD_1);
  add->setCheckable(true);
  add->setFixedSize(QSize(55,55));
  add->setIconSize(QSize(50,50));

  QPushButton* join = setupBtnIcon(LINK_IMG_JOIN_1);
  join->setCheckable(true);
  join->setFixedSize(QSize(55, 55));
  join->setIconSize(QSize(50,50));

  m_btnGroup->addButton(add, 0);
  m_btnGroup->addButton(join, 1);
  m_btnGroup->addButton(btnNoShowCells, 2);

  QHBoxLayout* mainBox = new QHBoxLayout;
  mainBox->addWidget(back);
  mainBox->addWidget(btnNoShowCells);
  mainBox->addWidget(add);
  mainBox->addWidget(join);

  connect(btnNoShowCells, &QPushButton::clicked, this, [this]() {
      m_currentType = (m_currentType == CellType::NoShow) ? CellType::None : CellType::NoShow;
  });

  mainWidget->setLayout(mainBox);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

QWidget* ChessEditor::initLeftSidebar()
{
  QWidget* mainWidget = new QWidget;

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Виды:"));

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

QWidget* ChessEditor::initCenterSidebar()
{
  QWidget* mainWidget = new QWidget;

  QPushButton* square = setupBtnIcon(LINK_IMG_SQUARE);
  square->setFixedSize(QSize(30,30));

  QPushButton* circle = setupBtnIcon(LINK_IMG_CIRCLE);
  circle->setFixedSize(QSize(30,30));

  QPushButton* triangle = setupBtnIcon(LINK_IMG_TRIANGLE);
  triangle->setFixedSize(QSize(30,30));

  QPushButton* testGame = new QPushButton("Тестовая игра");

  m_display->setFixedSize(550, 550);

  QWidget* widgetType = new QWidget;
  QHBoxLayout* boardType = new QHBoxLayout(widgetType);
  boardType->addWidget(square);
  boardType->addWidget(circle);
  boardType->addWidget(triangle);

  widgetType->adjustSize();
  widgetType->setFixedSize(widgetType->size());

  QGridLayout* mainBox = new QGridLayout;
  mainBox->setSpacing(0);
  mainBox->addWidget(widgetType,0, 0, 1, 1, Qt::AlignCenter);
  mainBox->addWidget(testGame, 0, 1, 1, 1);
  mainBox->addWidget(m_display, 1, 0, 1, 2);

  m_display->setScene(ChessBoardManager::getInstance().getChessBoard());

  connect(square, &QPushButton::clicked, [this](){
    QJsonObject boardObj = m_infoBoard.value(BOARD).toObject();
    boardObj[TYPE_CHESS] = SQUARE;
    m_infoBoard[BOARD] = boardObj;

    emit update(m_infoBoard);
  });

  connect(circle, &QPushButton::clicked, [this](){
    QJsonObject boardObj = m_infoBoard.value(BOARD).toObject();
    boardObj[TYPE_CHESS] = CIRCLE;
    m_infoBoard[BOARD] = boardObj;

    emit update(m_infoBoard);
  });

  square->click();

  mainWidget->setLayout(mainBox);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

void ChessEditor::save()
{
  QRegularExpression regex(R"(^(\d+)(x\d+)*$)");
  if (!regex.match(m_dimensions->text()).hasMatch()) {
    qDebug()<<"2222";
  }
  QStringList parts = m_dimensions->text().split("x");

  QJsonObject board = m_infoBoard[BOARD].toObject();

  QJsonArray dimensions;
  for (const QString &part : parts)
      dimensions.append(part);

  QJsonArray figuresArray;
  for (const auto& f : m_figuresListObject)
    figuresArray.append(f->toJson());

  board[DIMENSIONS] = dimensions;

  m_infoBoard[NAME] = m_nameBoard->text();
  m_infoBoard[BOARD] = board;
  m_infoBoard[COUNT_PLAYERS] = m_countPlayers->value();
  m_infoBoard[FIGURES] = figuresArray;

  qDebug()<<m_infoBoard;
}

QWidget* ChessEditor::initRightSidebar()
{
  QWidget* mainWidget = new QWidget;

  m_dimensions->setPlaceholderText("2x2");

  QPushButton* addFigure = new QPushButton("Добавить");
  QPushButton* saveProperties = new QPushButton("Сохранить");

  QHBoxLayout* countPlayersBox = new QHBoxLayout;
  countPlayersBox->addWidget(new QLabel("Количество игроков"));
  countPlayersBox->addWidget(m_countPlayers);

  QToolButton* toolBtn1 = new QToolButton;
  toolBtn1->setText("Фигуры");
  QMenu* menu1 = new QMenu(toolBtn1);

  toolBtn1->setMenu(menu1);
  toolBtn1->setPopupMode(QToolButton::MenuButtonPopup);

  QWidget* figuresWidget = new QWidget;
  QVBoxLayout* figuresList = new QVBoxLayout(figuresWidget);
  figuresList->addLayout(m_figuresListWidget);
  figuresList->addWidget(addFigure);
  figuresWidget->setLayout(figuresList);
  figuresWidget->setVisible(false);

  QGridLayout* layout = new QGridLayout();
  layout->addWidget(new QLabel("Свойства"), 0, 0, 1, 2, Qt::AlignCenter);

  layout->addWidget(new QLabel("Название:"), 1, 0, 1, 1);
  layout->addWidget(m_nameBoard, 1, 1, 1, 1);

  layout->addWidget(new QLabel("Размеры:"), 2, 0, 1, 1);
  layout->addWidget(m_dimensions, 2, 1, 1, 1);

  layout->addLayout(countPlayersBox, 3, 0, 1, 2);
  layout->addWidget(toolBtn1, 4, 0, 1, 2);
  layout->addWidget(figuresWidget, 5, 0, 1, 2);
  layout->addWidget(saveProperties, 6, 0, 1, 2);

  connect(addFigure, &QPushButton::clicked, this, &ChessEditor::onClickedAddFigureForm);
  connect(saveProperties, &QPushButton::clicked, this, &ChessEditor::save);
  connect(toolBtn1, &QToolButton::clicked, [figuresWidget](){
    figuresWidget->setVisible(!figuresWidget->isVisible());
  });

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setFixedWidth(mainWidget->size().width() * 1.2);
  return mainWidget;
}

void ChessEditor::onClickedAddFigureForm()
{
  FigureForm* figureForm = new FigureForm(m_countPlayers->value());
  m_figuresListObject.append(figureForm);

  for(QPushButton* keys : figureForm->m_updatePos.keys())
  {
    int posInBtnGroup = m_btnGroup->buttons().count();
    m_btnGroup->addButton(keys, posInBtnGroup);
    m_updatePos[posInBtnGroup] = figureForm;
  }


  m_figuresListWidget->addWidget(figureForm);
}

void ChessEditor::setupFigureForm()
{
  QComboBox* typeFigure = new QComboBox();
  typeFigure->addItems({"Пешка", "Конь", "Ферзь", "Слон", "Кароль", "Ладья"});

  QSpinBox* countFigure = new QSpinBox();

  QLabel* pos = new QLabel();
  QPushButton* isSetPos = new QPushButton;
  isSetPos->setCheckable(true);

  int posInBtnGroup = m_btnGroup->buttons().count();
  m_btnGroup->addButton(isSetPos, posInBtnGroup);
// ww
  QWidget* widgetPos = new QWidget;
  QHBoxLayout* HBoxLayout = new QHBoxLayout(widgetPos);
  HBoxLayout->addWidget(isSetPos);
  HBoxLayout->addWidget(new QLabel("Позиция:"));
  HBoxLayout->addWidget(pos);
  widgetPos->setLayout(HBoxLayout);
// ww
  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Тип: "), 0, 0);
  layout->addWidget(typeFigure, 0, 1);

  layout->addWidget(new QLabel("Количество"), 1, 0, 1, 2, Qt::AlignCenter);
  layout->addWidget(countFigure, 2, 1);
  layout->addWidget(widgetPos, 3,0, 1, 2);

  // m_updatePos[posInBtnGroup] = [=](const QString& str){
  //   QString currentText = pos->text();
  //   QStringList positions = currentText.split(',', Qt::SkipEmptyParts);
  //   int i = positions.indexOf(isSetPos->objectName());

  //   if(i == -1)
  //     return;

  //   positions[i] = str;

  //   pos->setText(positions.join(","));
  // };

  m_figuresListWidget->addLayout(layout);
}
