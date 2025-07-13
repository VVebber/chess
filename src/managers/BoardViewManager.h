#ifndef BOARDVIEWMANAGER_H
#define BOARDVIEWMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QPointF>

#include "../core/EditMode.h"

class BoardChess;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;

class BoardViewManager : public QObject
{
  Q_OBJECT


public:
  static BoardViewManager& getInstance();

  QGraphicsScene* getScene();

  void setEditMode(EditMode mode);
  EditMode editMode() const;

  QSize getSizeBoard() const;

  void forwardMousePressToBoard(const QPointF& scenePos, QGraphicsSceneMouseEvent* event);

public slots:
  void updateScene();
  void onUpdateFromJson(const QJsonObject& json);

signals:
  void updateFromJson(const QJsonObject& json);
  void cellName(const QString pos);

private:
  BoardViewManager();
  ~BoardViewManager();
  BoardViewManager(const BoardViewManager&) = delete;
  BoardViewManager& operator=(const BoardViewManager&) = delete;
  QSize getBoardSize() const;

private:
  QGraphicsScene* m_currentScene;

  BoardChess* m_chessBoard;
  EditMode m_mode;

  friend class Figure;
};

#endif // BOARDVIEWMANAGER_H
