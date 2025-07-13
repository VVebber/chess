#ifndef BOARDCHESS_H
#define BOARDCHESS_H

#include <QSet>
#include <QJsonObject>
#include <QGraphicsObject>

class BoardChess : public QGraphicsObject
{
  Q_OBJECT
public:
  BoardChess(QJsonObject data = QJsonObject());

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

  static QString getPos(int x, int y);

public slots:
  void update(QJsonObject data);
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

signals:
  void cellName(const QString pos);

private:
  void setup(QJsonObject data);
  void squareBoard(QPainter *painter);
  void circleBoard(QPainter* painter);

private:
  QJsonObject m_infoBoard;

  QSet<QString> m_noShowCells;
  QSet<QString> m_specialCells;
  QHash<QString, QString> m_wrapCells;

  QSize m_sizeBoard;    //TODO: заменить на другой size
};

#endif // BOARDCHESS_H
