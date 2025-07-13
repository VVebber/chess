#include "BoardViewManager.h"
#include "FiguresManager.h"
#include "../models/BoardChess.h"

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>


void BoardViewManager::forwardMousePressToBoard(const QPointF& scenePos, QGraphicsSceneMouseEvent* originalEvent)
{
  if (!m_chessBoard || !m_currentScene)
    return;

  QPointF localPos = m_chessBoard->mapFromScene(scenePos);
  qDebug() << "Forwarding mouse press event: scenePos=" << scenePos << " localPos=" << localPos;

  QGraphicsSceneMouseEvent event(QEvent::GraphicsSceneMousePress);
   event.setScenePos(scenePos);
   event.setPos(localPos);
   event.setScreenPos(originalEvent->screenPos());
   event.setButton(originalEvent->button());
   event.setButtons(originalEvent->buttons());
   event.setModifiers(originalEvent->modifiers());

  m_chessBoard->mousePressEvent(&event);
}

BoardViewManager::BoardViewManager()
{
  m_mode = EditMode::Standard;
  m_currentScene = new QGraphicsScene();
  m_chessBoard = new BoardChess();

  FiguresManager* figures = &FiguresManager::getInstance();
  m_currentScene->addItem(m_chessBoard);
  m_currentScene->addItem(figures);


  connect(this, &BoardViewManager::updateFromJson, this, &BoardViewManager::onUpdateFromJson);

  connect(m_chessBoard, &BoardChess::cellName, this, &BoardViewManager::cellName);
  connect(m_chessBoard, &BoardChess::cellName, figures, &FiguresManager::onMoveCellClicked);
  connect(figures, &FiguresManager::updateScene, this, &BoardViewManager::updateScene);
}

QSize BoardViewManager::getBoardSize() const {
  return m_chessBoard->size();
}

void BoardViewManager::updateScene()
{
  m_currentScene->update();
}

void BoardViewManager::setEditMode(EditMode mode)
{
  m_mode = mode;
  FiguresManager::getInstance().setEditMode(m_mode);
}

EditMode BoardViewManager::editMode() const
{
  return m_mode;
}

QSize BoardViewManager::getSizeBoard() const
{
  return m_chessBoard->size();
}


void BoardViewManager::onUpdateFromJson(const QJsonObject& data) {
  m_chessBoard->update(data);
  FiguresManager::getInstance().onUpdateFromJson(data);
  m_currentScene->update();
}

BoardViewManager& BoardViewManager::getInstance()
{
  static BoardViewManager instance;
  return instance;
}

QGraphicsScene* BoardViewManager::getScene()
{
  return m_currentScene;
}

BoardViewManager::~BoardViewManager() {
}
