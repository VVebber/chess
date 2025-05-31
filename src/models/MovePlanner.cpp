#include "MovePlanner.h"
#include "BoardChess.h"
#include "Figure.h"

#include "../Common.h"

#include <vector>

#include <QPoint>
#include <QString>
#include <QJsonObject>


MovePlanner::MovePlanner(QList<Figure*> figures): m_figures(figures)
{}

std::vector<Move> MovePlanner::filterAvailableMoves(const Figure* figure,
                                                    std::vector<Move> allMoves)
{
  std::vector<Move> filteredMoves;

  QJsonObject movePatterns = figure->m_infoFigure.value(MOVE_PATTERNS).toObject();
  QString start = figure->m_boardPos;

  QMap<QString, Figure*> figuresPos;
  for(auto& figurePos : m_figures)
  {
    figuresPos.insert(figurePos->m_boardPos, figurePos);
  }

  QChar posFigure_X = start[0].toUpper();
  QChar posFigure_Y = start[1];

  bool addFigure = true;
  QString dir;
  for(auto& move : allMoves)
  {
    QChar newX = QChar(posFigure_X.unicode() + move.x);
    QChar newY = QChar(posFigure_Y.unicode() + move.y);

    QString posMove = QString(newX) + QString(newY);

    if(move.direction != dir)
      addFigure = true;

    if(!addFigure)
      continue;

    if(figuresPos.contains(posMove))
    {
      QString player = figuresPos[posMove]->m_player;
      move.color = figure->m_player == player? Qt::green: Qt::red;
      addFigure = false;
      dir = move.direction;
    }



    filteredMoves.push_back(move);
  }
  return filteredMoves;
}
