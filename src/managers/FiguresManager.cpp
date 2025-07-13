#include "FiguresManager.h"
#include "BoardViewManager.h"
#include "GameManager.h"

#include "../Common.h"
#include "../core/ChessCoord.h"
#include "../models/MovePlanner.h"

#include "../factory/FiguresFactory.h"

#include <QGraphicsSceneMouseEvent>
#include <QJsonArray>
#include <QPainter>

FiguresManager& FiguresManager::getInstance()
{
  static FiguresManager instans;
  return instans;
}

FiguresManager::FiguresManager(){}

FiguresManager::~FiguresManager(){}

QRectF FiguresManager::boundingRect() const
{
  return QRectF(0, 0, 40, 40);
}

void FiguresManager::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  highlightMoves(painter);
}

void FiguresManager::setEditMode(EditMode mode)
{
  m_mode = mode;

  Qt::MouseButtons buttons = (m_mode == EditMode::Playing) ? Qt::LeftButton : Qt::NoButton;
  for(auto& figure : m_figures)
    figure->setAcceptedMouseButtons(buttons);
}

void FiguresManager::onFigureClicked(Figure* fig)
{
  qDebug()<<Q_FUNC_INFO;


  if(!GameManager::instance().isCurrentPlayer(fig->m_player))
  {
    qDebug() << "Not this player's turn!";
    return;
  }

  if(GameManager::instance().isCheckShah(fig))
  {
    return;
  }

  m_selectedFigure = fig;

  QSize boardSize = BoardViewManager::getInstance().getSizeBoard();
  MovePlanner planner(m_figures, boardSize);
  m_availableMoves = planner.filterAvailableMoves(m_selectedFigure, fig->movePatterns());

  emit updateScene();
}

void FiguresManager::onMoveCellClicked(const QString targetPos)
{
  if (!m_selectedFigure || m_availableMoves.empty())
    return;

  QString posFigure = m_selectedFigure->m_boardPos;

  bool isFound = false;
  Move move;
  for(auto& mov : m_availableMoves)
  {
    QString posMove = ChessCoord::offsetStr(posFigure, mov.x, mov.y);
    if(targetPos == posMove)
    {
      isFound = true;
      move = mov;
      break;
    }
  }

  if (!isFound)
    return;


  qDebug() << "move.color =" << move.color.name() << "<" << QColor(Qt::red).name();
  if (move.color == QColor(Qt::red))
  {
    for (int i = 0; i < m_figures.size(); ++i) {
      {
        if(m_figures[i]->m_boardPos == targetPos)
        {
          delete m_figures[i];
          m_figures.erase(m_figures.begin() + i);
        }
      }
    }
  }

  m_selectedFigure->setPosition(targetPos);
  m_selectedFigure->m_hasMoved = false;

  GameManager::instance().nextTurn();
  m_selectedFigure = nullptr;
  m_availableMoves.clear();

  for(auto& figure : m_figures)
    if(figure->m_type == KING)
    {
      GameManager::instance().isCheckFromFigure(figure, m_figures);
    }
  emit updateScene();
}


void FiguresManager::highlightMoves(QPainter *painter)
{
  if(m_availableMoves.empty())
    return;

  if(m_selectedFigure == nullptr)
    return;

  qDebug()<<"count move: "<<m_availableMoves.size();
  qDebug()<<Q_FUNC_INFO;
  QString posFigure = m_selectedFigure->m_boardPos;

  for(auto& move : m_availableMoves)
  {
    QPoint position = ChessCoord::offsetPoint(posFigure, move.x, move.y);

    QPointF posPointF = QPointF(position.x() * 40 + 20, position.y() * 40 + 20);
    painter->setBrush(move.color);
    painter->drawEllipse(posPointF, 20, 20);
  }
}

void FiguresManager::clearFigures()
{
  qDeleteAll(m_figures);
  m_figures.clear();
}

void FiguresManager::onUpdateFromJson(QJsonObject data)
{
  clearFigures();
  m_availableMoves.clear();
  m_selectedFigure = nullptr;

  if(!data.contains(COUNT_PLAYERS))
    return;

  if(!data.contains(FIGURES))
    return;

  GameManager& manage = GameManager::instance();
  manage.clear();
  manage.initPlayer(data[COUNT_PLAYERS].toInt());

  m_figures = FiguresFactory::createFigures(data, m_mode);
  for(Figure* figure : m_figures)
  {
    figure->setParentItem(this);
    Qt::MouseButtons buttons = (m_mode == EditMode::Playing) ? Qt::LeftButton : Qt::NoButton;
    figure->setAcceptedMouseButtons(buttons);
  }
}
