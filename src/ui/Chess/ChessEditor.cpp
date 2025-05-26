#include "ChessEditor.h"
#include "../../Common.h"
#include "../../managers/ChessBoardManager.h"

#include "Subwidgets/FigureForm.h"
#include "Subwidgets/FigureMoveForm.h"

#include <QDir>
#include <QFile>
#include <QMenu>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QJsonArray>
#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QJsonDocument>

ChessEditor::ChessEditor()
{
  m_dimensions = new QLineEdit;
  m_nameChess = new QLineEdit;

  m_figuresFormList = new QVBoxLayout;
  
  m_figureMoveForm = new FigureMoveForm;
  m_figureMoveForm->hide();
  
  m_btnGroup = new QButtonGroup;
  m_btnGroup->setExclusive(false);
  
  m_display = new QGraphicsView;
  m_currentType = CellType::None;
  
  connect(this, &ChessEditor::updateChess,
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

void ChessEditor::onUpdateCountPlayers(int count)
{
  m_currentInfoChess[COUNT_PLAYERS] = count;
  for(auto& figure : m_figuresListObject)
  {
    figure->updateForm();
  }
  m_figureMoveForm->updateJson();
}


void ChessEditor::toggleCellState(const QString cell)
{
  if (cell.isEmpty())
    return;
  
  QJsonObject boardObj = m_currentInfoChess.value(BOARD).toObject();
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
    m_currentInfoChess[BOARD] = boardObj;
    updateChess(m_currentInfoChess);
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
  layout->addWidget(initRightSidebar(), 1, 2, 1, 1/*, Qt::AlignTop*/);
  
  mainWidget->setLayout(layout);
  mainWidget->setFixedSize(1280, 720);
}

QWidget* ChessEditor::initTopToolbar()
{
  QWidget* mainWidget = new QWidget;
  
  QPushButton* back = new QPushButton("назад");
  QPushButton* saveJson = new QPushButton("Сохранить");
  
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
  
  QGridLayout* mainBox = new QGridLayout;
  mainBox->addWidget(back, 0, 0);
  mainBox->addWidget(saveJson, 1, 0);
  mainBox->addWidget(btnNoShowCells, 0, 1);
  mainBox->addWidget(add, 0, 2);
  mainBox->addWidget(join, 0, 3);

  connect(saveJson, &QPushButton::clicked, this, &ChessEditor::onSaveToFileClicked);
  connect(btnNoShowCells, &QPushButton::clicked, this, [this]() {
    m_currentType = (m_currentType == CellType::NoShow) ? CellType::None : CellType::NoShow;
  });
  
  mainWidget->setLayout(mainBox);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

void ChessEditor::onSaveToFileClicked()
{
  QJsonDocument doc(m_currentInfoChess);

  if(!m_currentInfoChess.contains(NAME))
    return;

  QString name = m_currentInfoChess.value(NAME).toString();
  QString path = "/home/daniel/Документы/JSON/" + name + ".json";
  QFile file(path);
  if(!file.open(QIODevice::WriteOnly)) {
    qWarning() << "Не удалось открыть файл для записи";
    return;
  }
  file.write(doc.toJson(QJsonDocument::Indented));
  file.close();
}

QWidget* ChessEditor::initLeftSidebar()
{
  QWidget* mainWidget = new QWidget;
  
  QStringList files;
  QDir dir("/home/daniel/Документы/JSON/");
  if(!dir.exists())
  {
    qWarning() << "Папка не существует:";
  }
  else
  {
    QStringList filters;
    filters << "*.json";
    files = dir.entryList(filters, QDir::Files);
  }

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(new QLabel("Виды:"));

  int row = 1;
  for(auto& fileName : files)
  {
    QString name = QFileInfo(fileName).completeBaseName();
    QString fullPath = dir.filePath(fileName);
    QPushButton* btn = new QPushButton(name);
    layout->addWidget(btn, row, 0);
    row++;

    connect(btn, &QPushButton::clicked, [=](){
      QFile file(fullPath);
      if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл:" << fullPath;
        return;
      }
      QByteArray array = file.readAll();
      file.close();

      QJsonParseError parseError;
      QJsonDocument doc = QJsonDocument::fromJson(array, &parseError);
      if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Ошибка парсинга JSON:" << parseError.errorString();
        return;
      }

      m_currentInfoChess = doc.object();
      this->updateInfoForm();
      qDebug()<<m_currentInfoChess;
    });
  }

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
  return mainWidget;
}

void ChessEditor::updateInfoForm()
{
  qDebug()<<Q_FUNC_INFO;
  m_nameChess->setText(m_currentInfoChess[NAME].toString());

  QJsonObject board = m_currentInfoChess[BOARD].toObject();
  QJsonArray dimensions = board[DIMENSIONS].toArray();

  QStringList parts;
  for (auto part : dimensions)
  {
    parts.append(part.toString());
  }

  m_dimensions->setText(parts.join("x"));

  QSpinBox* countPlayers = qobject_cast<QSpinBox*>(m_variabels.getWidget(COUNT_PLAYERS));
  countPlayers->setValue(m_currentInfoChess.value(COUNT_PLAYERS).toInt());

  QJsonArray figures = m_currentInfoChess[FIGURES].toArray();
  for(auto figure : figures)
  {
    FigureForm* figureForm = new FigureForm(figure.toObject());
    m_figuresListObject.append(figureForm);

    for(QPushButton* keys : figureForm->m_updatePos.keys())
    {
      int posInBtnGroup = m_btnGroup->buttons().count();
      m_btnGroup->addButton(keys, posInBtnGroup);
      m_updatePos[posInBtnGroup] = figureForm;
    }

    m_figuresFormList->addWidget(figureForm);
  }
}


QWidget* ChessEditor::initFiguresFormList()
{
  QWidget* widget = new QWidget;
  
  QPushButton* addFigure = new QPushButton("Добавить");
  
  QVBoxLayout* figuresList = new QVBoxLayout(widget);
  figuresList->addLayout(m_figuresFormList);
  figuresList->addWidget(addFigure);
  
  connect(addFigure, &QPushButton::clicked, this, &ChessEditor::onClickedAddFigureForm);
  return widget;
}

QHBoxLayout* ChessEditor::initModeSwitchFigure()
{
  QHBoxLayout* layout = new QHBoxLayout;
  
  QButtonGroup* btnGroup = new QButtonGroup;
  QPushButton* btn1 = new QPushButton("Фигуры");
  QPushButton* btn2 = new QPushButton("Ходы");
  
  btn1->setCheckable(true);
  btn2->setCheckable(true);
  btn1->setChecked(true);
  
  btnGroup->addButton(btn1, 0);
  btnGroup->addButton(btn2, 1);
  
  layout->addWidget(btn1);
  layout->addWidget(btn2);
  
  m_variabels.addWidget(FIGURES, btn1);
  
  connect(btn2, &QPushButton::clicked, m_figureMoveForm, &FigureMoveForm::updateJson);
  
  connect(btnGroup, &QButtonGroup::buttonClicked, [layout, btnGroup](){
    QVBoxLayout* box = qobject_cast<QVBoxLayout*>(layout->parent());
    
    int i = btnGroup->checkedId();
    if(i == 0)
    {
      box->itemAt(2)->widget()->hide();
      box->itemAt(1)->widget()->show();
      ChessBoardManager::getInstance().setEditMode(EditMode::Standard);
    }
    else if(i == 1)
    {
      box->itemAt(1)->widget()->hide();
      box->itemAt(2)->widget()->show();
      ChessBoardManager::getInstance().setEditMode(EditMode::FigureSettings);
    }
    
  });
  
  return layout;
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
  connect(testGame, &QPushButton::clicked, [this](){
    ChessBoardManager::getInstance().setEditMode(EditMode::Playing);
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
  
  m_display->setScene(ChessBoardManager::getInstance().getChessBoard());
  
  connect(square, &QPushButton::clicked, [this](){
    QJsonObject boardObj = m_currentInfoChess.value(BOARD).toObject();
    boardObj[TYPE_CHESS] = SQUARE;
    m_currentInfoChess[BOARD] = boardObj;
    save();
  });
  
  connect(circle, &QPushButton::clicked, [this](){
    QJsonObject boardObj = m_currentInfoChess.value(BOARD).toObject();
    boardObj[TYPE_CHESS] = CIRCLE;
    m_currentInfoChess[BOARD] = boardObj;
    save();
  });
    
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
  
  QJsonObject board = m_currentInfoChess[BOARD].toObject();
  
  QJsonArray dimensions;
  for (const QString &part : parts)
    dimensions.append(part);
  
  QJsonArray figuresArray  = m_currentInfoChess.value(FIGURES).toArray();
  QPushButton* btn = qobject_cast<QPushButton*>(m_variabels.getWidget(FIGURES));

  if(btn->isChecked())
  {
    for(int i = 0; i < m_figuresListObject.size(); i++)
    {
      if(i < figuresArray.size())
      {
        figuresArray[i] = m_figuresListObject[i]->toJson(figuresArray[i].toObject());
      }
      else
      {
        figuresArray.append(m_figuresListObject[i]->toJson(QJsonObject()));
      }
    }
  }
  else
  {
    figuresArray = m_figureMoveForm->toJson();
  }
  board[DIMENSIONS] = dimensions;

  m_currentInfoChess[NAME] = m_nameChess->text();
  m_currentInfoChess[BOARD] = board;
  m_currentInfoChess[FIGURES] = figuresArray;
  updateChess(m_currentInfoChess);
  qDebug()<<m_currentInfoChess;
}

QWidget* ChessEditor::initRightSidebar()
{
  QWidget* mainWidget = new QWidget;


  QScrollArea* scrol = new QScrollArea();
  scrol->setWidgetResizable(true);
  
  m_dimensions->setPlaceholderText("2x2");
  
  QPushButton* saveProperties = new QPushButton("Сохранить");
  
  QSpinBox* countPlayers = new QSpinBox;
  m_variabels.addWidget(COUNT_PLAYERS, countPlayers);
  
  QHBoxLayout* countPlayersBox = new QHBoxLayout;
  countPlayersBox->addWidget(new QLabel("Количество игроков"));
  countPlayersBox->addWidget(countPlayers);

  m_nameChess->setPlaceholderText("Ввите название");
  
  QToolButton* toolBtn1 = new QToolButton;
  toolBtn1->setText("Фигуры");
  QMenu* menu1 = new QMenu(toolBtn1);
  
  toolBtn1->setMenu(menu1);
  toolBtn1->setPopupMode(QToolButton::MenuButtonPopup);
  
  QWidget* figuresWidget = new QWidget;
  QVBoxLayout* figuresLayout = new QVBoxLayout(figuresWidget);
  figuresLayout->addLayout(initModeSwitchFigure());
  figuresLayout->addWidget(initFiguresFormList());
  figuresLayout->addWidget(m_figureMoveForm);
  
  figuresWidget->setLayout(figuresLayout);
  figuresWidget->setVisible(false);

  m_nameChess->setPlaceholderText("Ввите название");

  QGridLayout* layout = new QGridLayout();
  layout->addWidget(new QLabel("Свойства"), 0, 0, 1, 2, Qt::AlignVCenter);
  
  layout->addWidget(new QLabel("Название:"), 1, 0, 1, 1);
  layout->addWidget(m_nameChess, 1, 1, 1, 1);
  
  layout->addWidget(new QLabel("Размеры:"), 2, 0, 1, 1);
  layout->addWidget(m_dimensions, 2, 1, 1, 1);
  
  layout->addLayout(countPlayersBox, 3, 0, 1, 2);
  layout->addWidget(toolBtn1, 4, 0, 1, 2);
  layout->addWidget(figuresWidget, 5, 0, 1, 2);
  layout->addWidget(saveProperties, 6, 0, 1, 2);
  
  connect(countPlayers, &QSpinBox::valueChanged, this, &ChessEditor::onUpdateCountPlayers);
  connect(saveProperties, &QPushButton::clicked, this, &ChessEditor::save);
  connect(toolBtn1, &QToolButton::clicked, [figuresWidget](){
    figuresWidget->setVisible(!figuresWidget->isVisible());
  });

  QGridLayout* layout2 = new QGridLayout(mainWidget);
  layout2->addLayout(layout, 0, 0,1, 1, Qt::AlignTop);

  mainWidget->setLayout(layout2);
  mainWidget->adjustSize();
  mainWidget->setFixedWidth(mainWidget->size().width() * 1.3);

  scrol->setFixedWidth(mainWidget->width());
  scrol->setWidget(mainWidget);

  return scrol;
}

void ChessEditor::onClickedAddFigureForm()
{
  FigureForm* figureForm = new FigureForm();
  m_figuresListObject.append(figureForm);
  
  for(QPushButton* keys : figureForm->m_updatePos.keys())
  {
    int posInBtnGroup = m_btnGroup->buttons().count();
    m_btnGroup->addButton(keys, posInBtnGroup);
    m_updatePos[posInBtnGroup] = figureForm;
  }
  
  m_figuresFormList->addWidget(figureForm);
}
