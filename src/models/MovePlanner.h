#ifndef MOVEPLANNER_H
#define MOVEPLANNER_H

#include "Move.h"

#include <QList>
#include <QColor>

class Figure;


class MovePlanner
{
public:
  MovePlanner(QList<Figure*> figures);
  std::vector<Move> filterAvailableMoves(const Figure* figure, const std::vector<Move> allMoves);

private:
  QList<Figure*> m_figures;

};

#endif // MOVEPLANNER_H
