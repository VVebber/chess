#include "MovePlanner.h"
#include "Figure.h"

#include "../core/ChessCoord.h"

#include "../Common.h"

#include <vector>

#include <QPoint>
#include <QString>
#include <QJsonArray>

MovePlanner::MovePlanner(QList<Figure*> figures, QSize boardSize):
  m_figures(figures), m_BoardSize(boardSize){}

std::vector<Move> MovePlanner::filterAvailableMoves(const Figure* figure,
                                                    std::vector<Move> allMoves)
{
  std::vector<Move> filteredMoves;

  QJsonObject movePatterns = figure->m_infoFigure.value(MOVE_PATTERNS).toObject();
  QString start = figure->m_boardPos;

  bool requireEmptyCell = movePatterns.value(IS_CELL_EMPTY).toBool();

  QMap<QString, Figure*> figuresPos;
  for(auto& figurePos : m_figures)
  {
    figuresPos.insert(figurePos->m_boardPos, figurePos);
  }

  QChar posFigure_X = start[0].toUpper();
  QChar posFigure_Y = start[1];

  injectInitialConditions(figure, allMoves, figuresPos, movePatterns.value(INITIAL_CONDIYIONS).toObject());

  bool addFigure = true;
  QString dir;
  for(auto& move : allMoves)
  {
    QChar newX = QChar(posFigure_X.unicode() + move.x);
    QChar newY = QChar(posFigure_Y.unicode() + move.y);

    QString posMove = QString(newX) + QString(newY);

    QPoint pos = ChessCoord::fromPoint(posMove);
    bool inBounds = (pos.x() >= 0 && pos.x() <= m_BoardSize.width() &&
                     pos.y() >= 0 && pos.y() <= m_BoardSize.height());


    if (!inBounds)
      continue;

    if(move.direction != dir)
      addFigure = true;

    if(!addFigure)
      continue;

    if(figuresPos.contains(posMove))
    {
      QString player = figuresPos[posMove]->m_player;
      move.color = figure->m_player == player? Qt::green: Qt::red;

      if (requireEmptyCell)
        continue;

      addFigure = false;
      if(move.direction != "JUMP")
        dir = move.direction;
    }

    filteredMoves.push_back(move);
  }
  applyMoveRules(figure, filteredMoves, figuresPos, movePatterns.value(MOVE_RULES).toObject());
  return filteredMoves;
}

void MovePlanner::injectInitialConditions(const Figure* figure, std::vector<Move>& moves,
                                          const QMap<QString, Figure*>& figuresPos, const QJsonObject& initCondition)
{
  if(!figure->m_hasMoved)
    return;

  QString playerFigure = figure->m_player;

  if (figure->m_type == KING && figure->m_hasMoved) {
    // Пример короткой рокировки
    bool isWhite = figure->m_player == PLAYER_EN.arg(0);
    QString rookPos = isWhite ? "H1" : "H8";
    QString empty1 = isWhite ? "F1" : "F8";
    QString empty2 = isWhite ? "G1" : "G8";

    if (figuresPos.contains(rookPos) && figuresPos[rookPos]->m_hasMoved &&
        !figuresPos.contains(empty1) && !figuresPos.contains(empty2)) {
      Move castleMove;
      castleMove.x = 2;
      castleMove.y = 0;
      castleMove.color = Qt::blue;
      castleMove.direction = "CASTLE";
      moves.push_back(castleMove);
    }
    return;
  }

  QJsonObject initConditionList = initCondition.value(STROKE_LENGTH).toObject();

  if(initConditionList.empty())
    return;

  QJsonObject directions = figure->m_infoFigure[MOVE_PATTERNS].toObject();
  QJsonObject patterns = directions[DIRECTIONS].toObject();
  QJsonObject steps = patterns.value(STEPS).toObject();
  QJsonArray dirs = steps.value(playerFigure).toArray();

  int count = initCondition[STROKE_LENGTH].toObject().value(playerFigure).toInt();
  QString posMove = ChessCoord::fromStr(QPoint(0,0));

  for (const auto& dirVal : dirs)
  {
    for(int i = 1; i <= count; i++)
    {
      Move move;
      posMove = ChessCoord::offsetStr(posMove, dirVal.toString());

      QPoint posPoint = ChessCoord::fromIndex(posMove);
      move.x = posPoint.x();
      move.y = posPoint.y();
      move.direction = dirVal.toString();
      move.color = Qt::white;

      moves.push_back(move);
    }
  }
}

void MovePlanner::applyMoveRules(const Figure* figure, std::vector<Move>& moves,
                                 const QMap<QString, Figure*>& figuresPos,
                                 const QJsonObject& moveRules)
{
  QString playerFigure = figure->m_player;

  QJsonObject moveRulesList = moveRules.value(figure->m_player).toObject();

  if(moveRulesList.empty())
    return;

  QString figurePos = figure->m_boardPos;

  for (const auto& move : moveRulesList)
  {
    QJsonObject data = move.toObject();

    if(data.value(ACTION) == EVENT_ADD_MOVE)
    {
      QString posMoveStr = ChessCoord::offsetStr(figurePos, data.value(DIRECTIONS).toString());
      QPoint posMovePoint = ChessCoord::dirToPoint(data.value(DIRECTIONS).toString());

      bool isAdd = true;
      for(const Move move : moves)
      {
        QPoint posMove = QPoint(move.x, move.y);
        if(posMove == posMovePoint)
        {
          isAdd = false;
          break;
        }
      }

      if(!isAdd)
        continue;

      Move move;
      move.x = posMovePoint.x();
      move.y = posMovePoint.y();

      if(figuresPos.contains(posMoveStr))
      {
        QString player = figuresPos[posMoveStr]->m_player;
        QString typeFigure = data[TYPE_FIGURE].toString();

        if(player != playerFigure && typeFigure == ENEMIES || typeFigure == ALL)
          move.color = Qt::red;
        else if(player == playerFigure && typeFigure == ALLIES || typeFigure == ALL)
          move.color = Qt::green;
        else continue;
        moves.push_back(move);
      }
      continue;
    }
    else if(data.value(ACTION) == EVENT_CANCEL_MOVE)
    {
      QString posMoveStr = ChessCoord::offsetStr(figurePos, data.value(DIRECTIONS).toString());
      QPoint posMovePoint = ChessCoord::dirToPoint(data.value(DIRECTIONS).toString());

      if (figuresPos.contains(posMoveStr))
      {
        QString player = figuresPos[posMoveStr]->m_player;
        QString typeFigure = data[TYPE_FIGURE].toString();

        if(player != playerFigure && typeFigure == ENEMIES || typeFigure == ALL)
          for(int i = 0; i < moves.size(); i++)
          {
            if(moves[i].x == posMovePoint.x() && moves[i].y == posMovePoint.y())
            {
              moves.erase(moves.begin() + i);
            }
          }
        else if(player == playerFigure && typeFigure == ALLIES || typeFigure == ALL)
          for(int i = 0; i < moves.size(); i++)
          {
            if(moves[i].x == posMovePoint.x() && moves[i].y == posMovePoint.y())
            {
              moves.erase(moves.begin() + i);
            }
          }
      }
    }
  }
}


