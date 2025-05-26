#include "FiguresManager.h"

#include "../Common.h"
#include "ChessBoardManager.h"
#include "../models/BoardChess.h"

#include <QJsonArray>
#include <QPainter>

FiguresManager& FiguresManager::getInstance()
{
  static FiguresManager instans;
  return instans;
}

FiguresManager::FiguresManager()
{

}

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
  m_selectedFigure = fig;
  m_availableMoves = fig->movePatterns();
}

void FiguresManager::MovePlanner()
{

}

void FiguresManager::highlightMoves(QPainter *painter)
{
  if(m_availableMoves.empty())
    return;

  if(m_selectedFigure == nullptr)
    return;

  qDebug()<<Q_FUNC_INFO;
  QString posFigure = m_selectedFigure->m_boardPos;

  QChar colChar = posFigure[0].toUpper();
  QChar rowChar = posFigure[1];


  int startCol = colChar.toLatin1() - 'A';
  int startRow = rowChar.toLatin1() - '1';

  for(auto& move : m_availableMoves)
  {
    int targetCol = startCol + move.x;
    int targetRow = startRow + move.y;

    QPointF posPointF = QPointF(targetCol * 40 + 20, targetRow * 40 + 20);
    painter->setBrush(Qt::green);
    painter->drawEllipse(posPointF, 20, 20);
  }
}

void FiguresManager::update(QJsonObject data)
{
  for(int i = 0; i < m_figures.size(); i++)
    delete m_figures[i];

  m_figures.clear();
  m_availableMoves.clear();
  m_selectedFigure = nullptr;

  if(m_mode == EditMode::FigureSettings)
  {
    // int pos = arrow.size() / 2;
    QJsonArray figuresInfo = data[FIGURES].toArray();
    if (figuresInfo.isEmpty()) return;

    int id = ChessBoardManager::getInstance().m_idFigure;
    if(id == -1)
      return;

    QJsonArray posArray = data.value(BOARD).toObject().value(DIMENSIONS).toArray();
    if(posArray.size() < 2)
      return;

    QString pos = BoardChess::getPos(posArray.at(0).toString().toInt() / 2,
                                     posArray.at(1).toString().toInt() / 2);

    QJsonObject figureInfo = figuresInfo[id].toObject();
    Figure* figure = new Figure("", figureInfo);
    figure->setPosition(pos);
    figure->setParentItem(this);
    m_figures.push_back(figure);
    return;
  }

  QJsonArray figures = data[FIGURES].toArray();
  
  for(int i = 0; i < figures.size(); i++)
  {
    QJsonObject figureInfo = figures[i].toObject();
    QJsonObject posPlayer = figureInfo[START_POSITIONS].toObject();

    for(auto key : posPlayer.keys())
    {
      QJsonArray arrow = posPlayer[key].toArray();

      for(int j = 0; j < arrow.size(); j++)
      {
        Figure* figure = new Figure(key, figureInfo);
        figure->setPosition(arrow.at(j).toString());
        figure->setParentItem(this);

        Qt::MouseButtons buttons = (m_mode == EditMode::Playing) ? Qt::LeftButton : Qt::NoButton;
        figure->setAcceptedMouseButtons(buttons);

        m_figures.push_back(figure);
      }
    }
  }
}
