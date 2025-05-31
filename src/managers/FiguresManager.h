#ifndef FIGURESMANAGER_H
#define FIGURESMANAGER_H

#include "../core/Enums.h"
#include "../models/Figure.h"

#include <QJsonObject>
#include <QGraphicsItem>

class FiguresManager : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  static FiguresManager& getInstance();

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

  void onFigureClicked(Figure* fig);

  void setEditMode(EditMode mode);

private:
  FiguresManager();
  FiguresManager(const FiguresManager&) = delete;
  FiguresManager& operator=(const FiguresManager&) = delete;

private:
  void highlightMoves(QPainter *painter);

public slots:
  void update(QJsonObject data);

private:
  QList<Figure*> m_figures;
  Figure* m_selectedFigure;

  std::vector<Move> m_availableMoves;
  EditMode m_mode;
};

/*
MovePlanner	Планирует ходы, фильтрует по условиям (isCellEmpty, isEnemy, пешка не ходила и т.п.).
MoveResolver	Распознаёт допустимые ходы на основе текущего положения и типа фигуры.
MoveGenerator	Генератор всех потенциальных ходов, включая цвет и координаты.
MoveHandler	Более общий обработчик хода, может вызывать другие классы.
MoveAnalyzer	Анализирует, какие ходы допустимы по правилам.
MoveController	Управляет и фильтрует ходы — удобно, если тебе нужна логика отмен/переходов.
*/
#endif // FIGURESMANAGER_H
