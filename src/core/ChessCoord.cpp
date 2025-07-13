#include "ChessCoord.h"


ChessCoord::ChessCoord(int x, int y) : m_pos(QPoint(x,y)) {}

ChessCoord::ChessCoord(const QString& notation)
{

}

QPoint ChessCoord::offsetPoint(const QString& pos, int dx, int dy)
{
  QPoint point = fromIndex(pos);
  return offsetPoint(point, dx, dy);
}

QString ChessCoord::offsetStr(const QString& pos, int dx, int dy)
{
  QPoint point = fromIndex(pos);
  point = offsetPoint(point, dx, dy);

  return fromStr(point);
}

QString ChessCoord::offsetStr(const QString& pos, const QString& dir)
{
  QPoint coord = dirToPoint(dir);
  return offsetStr(pos, coord.x(), coord.y());
}

QPoint ChessCoord::dirToPoint(const QString& dir)
{
  int dx = 0;
  int dy = 0;

  if (dir == "U")      dy = -1;
  else if (dir == "D") dy = 1;
  else if (dir == "L") dx = -1;
  else if (dir == "R") dx = 1;
  else if (dir == "UL") { dx = -1; dy = -1; }
  else if (dir == "UR") { dx = 1; dy = -1; }
  else if (dir == "DL") { dx = -1; dy = 1; }
  else if (dir == "DR") { dx = 1; dy = 1; }

  return QPoint(dx, dy);
}

QPoint ChessCoord::offsetPoint(const QPoint& pos, int dx, int dy)
{
  return QPoint(pos.x() + dx, pos.y() + dy);
}

QPoint ChessCoord::fromPoint(const QString& str)
{
  if (str.size() < 2)
    return QPoint(-1, -1);
  int col = str[0].toUpper().toLatin1() - 'A';
  int row = str[1].toLatin1() - '1';
  return QPoint(col * 40, row * 40);
}

QPoint ChessCoord::fromIndex(const QString& str)
{
  if (str.size() < 2)
    return QPoint(-1, -1);
  int col = str[0].toUpper().toLatin1() - 'A';
  int row = str[1].toLatin1() - '1';
  return QPoint(col, row);
}

QString ChessCoord::fromStr(const QPoint& pos)
{
  return QString(QChar('A' + pos.x())) + QString(QChar('1' + pos.y()));
}

QString ChessCoord::fromStr(const int& x, const int& y)
{
  return QString(QChar('A' + x)) + QString(QChar('1' + y));
}
void ChessCoord::setCoord(const QPoint& pos)
{
  m_pos = pos;
}

void ChessCoord::setCoord(const QString& pos)
{
  m_pos = fromPoint(pos);
}

QPoint ChessCoord::point() const
{
  return m_pos;
}

QString ChessCoord::string() const
{
  return fromStr(m_pos);
}


