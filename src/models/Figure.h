#ifndef FIGURE_H
#define FIGURE_H

#include "Move.h"

#include <QJsonObject>
#include <QGraphicsObject>

class MovePlanner;

class Figure : public QGraphicsObject
{
  Q_OBJECT
public:
  Figure(QString player, QJsonObject data = QJsonObject());
  virtual ~Figure();
  void setPosition(QString pos);

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
  std::vector<Move> movePatterns();

public slots:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
  QPixmap colorizedPixmap(const QPixmap &source, const QColor &color);

  std::vector<Move> stepMoves(const QJsonObject& movePatterns);
  std::vector<Move> jumpMoves(const QJsonObject& movePatterns);

private:
  QJsonObject m_infoFigure;
  QPixmap m_pixmap;

  QString m_boardPos;
  QString m_player;
  QString m_type;

  bool m_hasMoved;

  friend class FiguresManager;
  friend class MovePlanner;
  friend class GameManager;
};

#endif // FIGURE_H
