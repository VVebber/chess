#ifndef CHESSBOARDMANAGER_H
#define CHESSBOARDMANAGER_H

#include <QObject>
#include <QJsonObject>

#include "../core/Enums.h"

class QGraphicsScene;

class ChessBoardManager : public QObject
{
  Q_OBJECT


public:
  static ChessBoardManager& getInstance();

  QGraphicsScene* getChessBoard();
  void setTypeChess(QJsonObject data);

  void setEditMode(EditMode mode);
  EditMode editMode() const;
  void setIdFigure(int idFigure);

private:
  ChessBoardManager();
  ChessBoardManager(const ChessBoardManager&) = delete;
  ChessBoardManager& operator=(const ChessBoardManager&) = delete;

signals:
  void update(QJsonObject data);
  void cellName(const QString pos);

private:
  QGraphicsScene* m_currentScene;

  EditMode m_mode;
  int m_idFigure;

  friend class FiguresManager;
  friend class ChessEditor;
};

#endif // CHESSBOARDMANAGER_H
