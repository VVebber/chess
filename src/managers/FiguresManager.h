
#ifndef FIGURESMANAGER_H
#define FIGURESMANAGER_H

#include "../core/EditMode.h"
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

public slots:
  void onUpdateFromJson(QJsonObject data);
  void onMoveCellClicked(const QString targetPos);

signals:
  void updateScene();

private:
  FiguresManager();
  ~FiguresManager();
  FiguresManager(const FiguresManager&) = delete;
  FiguresManager& operator=(const FiguresManager&) = delete;

  void clearFigures();
private:
  void highlightMoves(QPainter *painter);

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
