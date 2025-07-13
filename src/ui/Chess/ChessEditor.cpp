#include "ChessEditor.h"
#include "../../Common.h"
#include "../../managers/BoardViewManager.h"
#include "../../managers/SwitchEditorButton.h"
#include "../../core/ChessInfoJson.h"

#include "Subwidgets/ChessEditor/Right/RightMenuWidget.h"
#include "Subwidgets/ChessEditor/Left/ChessJsonList.h"

#include <QDir>
#include <QFile>
#include <QLabel>
#include <QLayout>
#include <QJsonArray>
#include <QPushButton>
#include <QGraphicsView>
#include <QJsonDocument>

ChessEditor::ChessEditor(QWidget* parent) : BaseWidget(parent)
{
  setObjectName("ChessEditor");

  m_display = new QGraphicsView;
  m_currentType = CellType::None;
  
  connect(this, &ChessEditor::updateScheneJson,
          &BoardViewManager::getInstance(), &BoardViewManager::onUpdateFromJson);
  
  connect(&BoardViewManager::getInstance(), &BoardViewManager::cellName,
          this, &ChessEditor::toggleCellState);

  setup();
  setupStyleSheet();
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
  qDebug()<<cell;
  if (cell.isEmpty())
    return;
  
  QJsonObject boardObj = ChessInfoJson::instance().getValue(BOARD).toObject();
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
    // m_currentInfoChess[BOARD] = boardObj;
    // updateChess(m_currentInfoChess);
  }
  
  if(boardObj.contains(TYPE_CHESS))
  {
    SwitchEditorButton& btnGroup = SwitchEditorButton::instance();
    int id = btnGroup.checkedId();
    if(id <= 2)
      return;
    
    QAbstractButton* btn = btnGroup.button(id);
    if(btn->objectName().isEmpty())
    {
      btn->setObjectName(cell);
      return;
    }

    qobject_cast<RightMenuWidget*>(m_variabels.getWidget(RIGHT_MENU_WIDGET))->updatePosFigure(cell, btn);
    btn->setObjectName("");
  }
}

void ChessEditor::setup()
{
  QWidget* mainWidget = new QWidget(this);
  
  RightMenuWidget* RightSidebar = new RightMenuWidget;
  m_variabels.addWidget(RIGHT_MENU_WIDGET, RightSidebar);

  ChessJsonList* chessJsonList = new ChessJsonList();

  QGridLayout* layout = new QGridLayout;
  layout->setSpacing(0);
  layout->addWidget(initTopToolbar(), 0, 0, 1, 3);
  layout->addWidget(chessJsonList, 1, 0, 1, 1);
  layout->addWidget(initCenterSidebar(), 1, 1, 1, 1);
  layout->addWidget(RightSidebar, 1, 2, 1, 1);
  
  mainWidget->setLayout(layout);
  mainWidget->setFixedSize(1280, 720);

  connect(chessJsonList, &ChessJsonList::updateFormInfo, this, &ChessEditor::updateFormInfo);
  connect(RightSidebar, &RightMenuWidget::updateScheneJson,
          this, &ChessEditor::updateScheneJson);
}

QWidget* ChessEditor::initTopToolbar()
{
  QWidget* mainWidget = new QWidget;
  
  QPushButton* back = new QPushButton("назад");
  back->setObjectName(WIDGET_CHESS_GAME);
  
  QPushButton* btnNoShowCells = setupBtnIcon(LINK_IMG_DELETE_1);
  btnNoShowCells->setCheckable(true);
  btnNoShowCells->setObjectName(NO_SHOW_CELLS);
  btnNoShowCells->setFixedSize(QSize(55,55));
  btnNoShowCells->setIconSize(QSize(50,50));
  btnNoShowCells->hide();

  QPushButton* add = setupBtnIcon(LINK_IMG_ADD_1);
  add->setCheckable(true);
  add->setFixedSize(QSize(55,55));
  add->setIconSize(QSize(50,50));
  add->hide();

  QPushButton* join = setupBtnIcon(LINK_IMG_JOIN_1);
  join->setCheckable(true);
  join->setFixedSize(QSize(55, 55));
  join->setIconSize(QSize(50,50));
  join->hide();
  
  SwitchEditorButton& btnGroup =  SwitchEditorButton::instance();
  btnGroup.addButton(add, 0);

  btnGroup.addButton(join, 1);
  btnGroup.addButton(btnNoShowCells, 2);
  
  QGridLayout* mainBox = new QGridLayout;
  mainBox->addWidget(back, 0, 0);
  mainBox->addWidget(btnNoShowCells, 0, 1);
  mainBox->addWidget(add, 0, 2);
  mainBox->addWidget(join, 0, 3);

  connect(back, &QPushButton::clicked, this, &BaseWidget::onSetWidgetClicked);
  connect(btnNoShowCells, &QPushButton::clicked, this, [this]() {
    m_currentType = (m_currentType == CellType::NoShow) ? CellType::None : CellType::NoShow;
  });
  
  mainWidget->setLayout(mainBox);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

void ChessEditor::updateFormInfo()
{
  qDebug()<<Q_FUNC_INFO;
  ChessInfoJson data = ChessInfoJson::instance();

  qobject_cast<RightMenuWidget*>(m_variabels.getWidget(RIGHT_MENU_WIDGET))->updateFormInfo(data.getData());
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
  testGame->setCheckable(true);
  connect(testGame, &QPushButton::clicked, [this, testGame](){
    if(testGame->isChecked())
      BoardViewManager::getInstance().setEditMode(EditMode::Playing);
    else
      BoardViewManager::getInstance().setEditMode(EditMode::Standard);
  });
  
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
  
  m_display->setScene(BoardViewManager::getInstance().getScene());
  
  connect(square, &QPushButton::clicked, [this](){
    QJsonObject data = ChessInfoJson::instance().getValue(BOARD).toObject();
    data[TYPE_CHESS] = SQUARE;

    ChessInfoJson::instance().addOrUpdateKey(BOARD, data);

    emit updateScheneJson(ChessInfoJson::instance().getData());
  });
  
  connect(circle, &QPushButton::clicked, [this](){
    QJsonObject data = ChessInfoJson::instance().getValue(BOARD).toObject();
    data[TYPE_CHESS] = CIRCLE;
    ChessInfoJson::instance().addOrUpdateKey(BOARD, data);

    emit updateScheneJson(ChessInfoJson::instance().getData());
  });
    
  mainWidget->setLayout(mainBox);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

void ChessEditor::setupStyleSheet()
{
  setStyleSheet(QString(R"(

  #ChessEditor {
    background: transparent;
  }

  QGraphicsView {
      border: 4px solid #8b5a2b;
      border-radius: 4px;
  }
  )"));
}
