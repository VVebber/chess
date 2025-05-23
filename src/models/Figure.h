#ifndef FIGURE_H
#define FIGURE_H

#include <QJsonObject>
#include <QGraphicsObject>

class Figure : public QGraphicsObject
{
  Q_OBJECT
public:
  Figure(QJsonObject data = QJsonObject());
  void setPosition(QString pos);

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
  QJsonObject m_infoFigure;
  QPixmap m_pixmap;
  QPointF m_pos;

  friend class FiguresManager;
};

#endif // FIGURE_H
