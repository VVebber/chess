#include "GameManager.h"
#include "../Common.h"

#include "../models/Figure.h"
#include "../models/BoardChess.h"

GameManager& GameManager::instance() {
  static GameManager inst;
  return inst;
}

GameManager::GameManager() {
}

bool GameManager::isCurrentPlayer(const QString& moveKey) const {
  if (m_players.isEmpty())
    return false;

  QString current = m_players[m_countMove % m_players.count()];
  return current == moveKey;
}

void GameManager::nextTurn() {
  m_friendFigures.clear();
  ++m_countMove;
}

void GameManager::initPlayer(const int& countPlayers) {
  for(int i = 0; i < countPlayers; i++)
    m_players.append(PLAYER_EN.arg(i));
}

void GameManager::clear() {
  m_players.clear();
  m_countMove = 0;
}

bool GameManager::isCheckFromFigure(Figure* king,   QList<Figure*> allFigures) {
  if (!king || king->m_type != KING)
    return false;

  const QMap<QString, QPoint> directions = {
    { "U",  {  0, -1 } },
    { "D",  {  0,  1 } },
    { "L",  { -1,  0 } },
    { "R",  {  1,  0 } },
    { "UL", { -1, -1 } },
    { "UR", {  1, -1 } },
    { "DL", { -1,  1 } },
    { "DR", {  1,  1 } }
  };

  QMap<QString, Figure*> figuresPos;
  for (auto* figure : allFigures)
    figuresPos[figure->m_boardPos] = figure;

  QChar posX = king->m_boardPos[0].toUpper();
  QChar posY = king->m_boardPos[1];

  const int countMove = 8;

  QList<QString> checkCells;
  for (const auto& [dirName, dir] : directions.toStdMap()) {
    QStringList tempCells;

    for (int i = 1; i <= countMove; ++i)
    {
      int dx = dir.x() * i;
      int dy = dir.y() * i;

      QChar newX = QChar(posX.unicode() + dx);
      QChar newY = QChar(posY.unicode() + dy);
      QString newPos = QString(newX) + QString(newY);

      tempCells.push_back(newPos);
      if (!figuresPos.contains(newPos))
        continue;

      Figure* f = figuresPos[newPos];

      if (f->m_player == king->m_player) {
        break;
      }

      if (
          (dirName.length() == 1 && (f->m_type == ROOK || f->m_type == QUEEN)) ||
          (dirName.length() == 2 && (f->m_type == BISHOP || f->m_type == QUEEN))
          )
      {
        checkCells.append(tempCells);
      }

      break;
    }
  }
  if(checkCells.size() != 0)
  {
    findFriendlyFiguresInCheckCells(checkCells, king, allFigures);
  }

  return false;
}

bool GameManager::isCheckShah(Figure* figure)
{
  if(m_friendFigures.size() == 0)
  {
    return false;
  }
  else
  {
    if(m_friendFigures.contains(figure))
      return false;
  }

  return true;
}

void GameManager::findFriendlyFiguresInCheckCells(const QList<QString>& checkCells, Figure* king, const QList<Figure*>& allFigures) {
  if (!king) return;

  m_friendFigures.clear();
  m_friendFigures.push_back(king);

  const QMap<QString, QPoint> directions = {
    { "U",  {  0, -1 } },
    { "D",  {  0,  1 } },
    { "L",  { -1,  0 } },
    { "R",  {  1,  0 } },
    { "UL", { -1, -1 } },
    { "UR", {  1, -1 } },
    { "DL", { -1,  1 } },
    { "DR", {  1,  1 } }
  };

  QMap<QString, Figure*> figuresPos;
  for (auto* figure : allFigures)
    figuresPos[figure->m_boardPos] = figure;

  const int countMove = 8;

  for (const QString& cell : checkCells) {
    QChar posX = cell[0].toUpper();
    QChar posY = cell[1];

    for (const auto& dir : directions) {
      int dx = dir.x();
      int dy = dir.y();

      for (int i = 1; i <= countMove; ++i) {
        QChar newX = QChar(posX.unicode() + dx * i);
        QChar newY = QChar(posY.unicode() + dy * i);

        QString newPos = QString(newX) + QString(newY);
        if (!figuresPos.contains(newPos))
          continue;

        Figure* f = figuresPos[newPos];

        if (f->m_player == king->m_player && f->m_type != KING) {
          m_friendFigures.push_back(f);  // 👈 сюда сохраняешь
          break;
        } else {
          break; // враг или король — стоп
        }
      }
    }
  }
}
