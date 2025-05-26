#ifndef FIGURE_H
#define FIGURE_H

#include <QJsonObject>
#include <QGraphicsObject>

struct Move {
  int x, y;
  QColor color;
};

class Figure : public QGraphicsObject
{
  Q_OBJECT
public:
  Figure(QString player, QJsonObject data = QJsonObject());
  void setPosition(QString pos);

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
  std::vector<Move> movePatterns();

public slots:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
  QJsonObject m_infoFigure;
  QPixmap m_pixmap;

  QString m_boardPos;
  QString m_player;

  std::vector<Move> m_highlightMoves;

  friend class FiguresManager;
};

#endif // FIGURE_H
