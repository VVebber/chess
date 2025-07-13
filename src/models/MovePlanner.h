#ifndef MOVEPLANNER_H
#define MOVEPLANNER_H

#include "Move.h"

#include <QList>
#include <QSize>
#include <QColor>
#include <QJsonObject>

class Figure;
class BoardChess;

class MovePlanner
{
public:
  MovePlanner(QList<Figure*> figures, QSize boardSize);
  std::vector<Move> filterAvailableMoves(const Figure* figure, const std::vector<Move> allMoves);
  void applyMoveRules(const Figure* figure, std::vector<Move>& moves,
                      const QMap<QString, Figure*>& figuresPos, const QJsonObject& moveRules);

  void injectInitialConditions(const Figure* figure, std::vector<Move>& moves,
                      const QMap<QString, Figure*>& figuresPos, const QJsonObject& moveRules);

private:
  QList<Figure*> m_figures;

  QSize m_BoardSize;
};

#endif // MOVEPLANNER_H
