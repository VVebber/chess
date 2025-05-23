#ifndef CHESSBOARDMANAGER_H
#define CHESSBOARDMANAGER_H

#include <QObject>
#include <QJsonObject>

class QGraphicsScene;

class ChessBoardManager : public QObject
{
  Q_OBJECT
public:
  static ChessBoardManager& getInstance();

  QGraphicsScene* getChessBoard();
  void setTypeChess(QJsonObject data);

private:
  ChessBoardManager();
  ChessBoardManager(const ChessBoardManager&) = delete;
  ChessBoardManager& operator=(const ChessBoardManager&) = delete;

signals:
  void update(QJsonObject data);
  void cellName(const QString pos);

private:
  QGraphicsScene* m_currentScene;
};

#endif // CHESSBOARDMANAGER_H
