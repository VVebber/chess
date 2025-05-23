#include "ChessBoardManager.h"
#include "FiguresManager.h"
#include "../models/BoardChess.h"

#include <QGraphicsScene>
#include <QObject>

ChessBoardManager::ChessBoardManager()
{
  m_currentScene = new QGraphicsScene();
  BoardChess* chessBoard = new BoardChess();
  FiguresManager* figures = &FiguresManager::getInstance();

  connect(this, &ChessBoardManager::update,
          this,[this, chessBoard, figures](QJsonObject data){

    chessBoard->update(data);
    figures->update(data);

    m_currentScene->update();
  });

  connect(chessBoard, &BoardChess::cellName, this, &ChessBoardManager::cellName);

  m_currentScene->addItem(chessBoard);
  m_currentScene->addItem(figures);
}

void ChessBoardManager::setTypeChess(QJsonObject data)
{
  emit update(data);
}

ChessBoardManager& ChessBoardManager::getInstance()
{
  static ChessBoardManager instans;
  return instans;
}

QGraphicsScene* ChessBoardManager::getChessBoard()
{
  return m_currentScene;
}
