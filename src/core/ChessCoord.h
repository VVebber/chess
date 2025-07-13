#ifndef CHESSCOORD_H
#define CHESSCOORD_H

#include <QPoint>
#include <QString>

class ChessCoord
{
public:
  ChessCoord(int x = 0, int y = 0);
  ChessCoord(const QString& notation);

  static QPoint dirToPoint(const QString& dir);

  static QPoint fromPoint(const QString& notation);
  static QPoint fromIndex(const QString& notation);

  static QString fromStr(const QPoint& pos);
  static QString fromStr(const int& x, const int& y);

  static QPoint offsetPoint(const QString& pos, int dx, int dy);
  static QString offsetStr(const QString& pos, int dx, int dy);
  static QString offsetStr(const QString& pos, const QString& dir);

  void setCoord(const QPoint& pos);
  void setCoord(const QString& pos);

  QPoint point() const;
  QString string() const;

private:
  static QPoint offsetPoint(const QPoint& pos, int dx, int dy);

private:
  QPoint m_pos;
};

#endif // CHESSCOORD_H
