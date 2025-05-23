#ifndef FIGURESMANAGER_H
#define FIGURESMANAGER_H

#include <QJsonObject>
#include <QGraphicsItem>

class Figure;

class FiguresManager : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  static FiguresManager& getInstance();

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
  FiguresManager();
  FiguresManager(const FiguresManager&) = delete;
  FiguresManager& operator=(const FiguresManager&) = delete;

public slots:
  void update(QJsonObject data);

private:
  QList<Figure*> m_figures;

};

#endif // FIGURESMANAGER_H
