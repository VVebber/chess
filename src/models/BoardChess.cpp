#include "BoardChess.h"
#include "../Common.h"

#include <QGraphicsSceneMouseEvent>
#include <QJsonArray>
#include <QPainter>
#include <QDebug>

BoardChess::BoardChess(QJsonObject data) : m_infoBoard(data)
{
  m_sizeBoard = QSize(8,8);
}

void BoardChess::update(QJsonObject data)
{
  qDebug() << Q_FUNC_INFO;
  m_noShowCells.clear();

  m_infoBoard = data[BOARD].toObject();

  // Загружаем список скрытых клеток
  QJsonArray noShowCells = m_infoBoard.value(NO_SHOW_CELLS).toArray();
  for (int i = 0; i < noShowCells.size(); ++i)
  {
    m_noShowCells.insert(noShowCells.at(i).toString());
  }

  // Получаем тип доски
  QString typeGame = m_infoBoard.value(TYPE_CHESS).toString().toLower();

  // Размеры доски
  QJsonArray dimensions = m_infoBoard.value(DIMENSIONS).toArray();

<<<<<<< HEAD
  if (dimensions.size() >= 2) {
      x = dimensions.at(0).toString().toInt();
      y = dimensions.at(1).toString().toInt();
=======
  if (typeGame == "circle" && dimensions.size() >= 1) {
    int radius = dimensions.at(0).toString().toInt();
    // храним как (2R+1, 2R+1), для использования в других местах
    m_sizeBoard = QSize(2 * radius + 1, 2 * radius + 1);
  }
  else if (typeGame == "square" && dimensions.size() >= 2) {
    int width = dimensions.at(0).toString().toInt();
    int height = dimensions.at(1).toString().toInt();
    m_sizeBoard = QSize(width, height);
  }
  else {
    // По умолчанию
    m_sizeBoard = QSize(8, 8);
>>>>>>> 191d2fa (Попытка сделать из sfml Qt)
  }
}

void BoardChess::setup(QJsonObject data)
{
}

QRectF BoardChess::boundingRect() const
{
  QString typeGame = "";
  if (m_infoBoard.contains(TYPE_CHESS))
    typeGame = m_infoBoard[TYPE_CHESS].toString();

  if (typeGame == CIRCLE && m_infoBoard.contains("RADIUS")) {
    int radius = m_infoBoard["RADIUS"].toInt(3);
    int cellSize = 40;
    int diameter = (radius * 2 + 1) * cellSize;
    return QRectF(0, 0, diameter, diameter);
  }

  // По умолчанию квадратная доска
  int x = 40 * (m_sizeBoard.width() + 1);
  int y = 40 * (m_sizeBoard.height() + 1);
  return QRectF(0, 0, x, y);
}

void BoardChess::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if(!m_infoBoard.empty())
  {
    QString typeGame = "";
    if(m_infoBoard.contains(TYPE_CHESS))
    {
      typeGame = m_infoBoard[TYPE_CHESS].toString();
    }

    if(typeGame == SQUARE)
    {
      squareBoard(painter);
    }
    else if(typeGame == CIRCLE)
    {
      circleBoard(painter);
    }
  }
}

QString BoardChess::getPos(int x, int y)
{
  QChar posX = QChar('1' + x);
  QChar posY = QChar('A' + y);

  qDebug()<<QString(posY) + QString(posX);
  return QString(posY) + QString(posX);
}

void BoardChess::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QPoint posPressed = event->pos().toPoint();
  int x = posPressed.x() / 40;
  int y = posPressed.y() / 40;

  emit cellName(getPos(y, x));
}

void BoardChess::squareBoard(QPainter *painter)
{
  QFont font;
  font.setPointSize(40);
  painter->setFont(font);

  QChar charX;
  QChar charY;

  for(int i = 0; i < m_sizeBoard.height()  + 1; i++)
  {
    int x = 40 * 0;
    int y = 40 * i;

    charY = QChar('1' + i);

    if(i < m_sizeBoard.height())
      painter->drawText(x - 40, y + 40, charY);

    for(int j = 0; j < m_sizeBoard.width(); j++)
    {
      x = 40 * j;
      y = 40 * i;
      charX = QChar('A' + j);

      QString cellName = QString("%1%2").arg(charX).arg(charY);

      if (m_noShowCells.contains(cellName))
        continue;

      if(i == m_sizeBoard.height())
      {
        painter->drawText(x, y + 40, charX);
      }
      else
      {
        painter->setBrush((i + j) % 2 == 0 ? Qt::white : Qt::black);
        painter->drawRect(x, y, 40, 40);
      }
    }
  }
}

void BoardChess::circleBoard(QPainter* painter)
{
  int boardSize = m_sizeBoard.width(); // = 2*radius + 1
  if (boardSize % 2 == 0) return;

  int radius = (boardSize - 1) / 2;
  int cellSize = 40; // базовый размер кольца

  QPoint center((radius + 1) * cellSize, (radius + 1) * cellSize);
  int ringCount = radius;  // количество колец

  QFont font;
  font.setPointSize(8);
  painter->setFont(font);

  for (int r = 0; r < ringCount; ++r) {
    int sectors = 8 + r * 4; // Чем дальше, тем больше секторов
    qreal angleStep = 360.0 / sectors;

    for (int s = 0; s < sectors; ++s) {
      qreal startAngle = s * angleStep;
      QRectF outerRect(center.x() - (r + 1) * cellSize,
                       center.y() - (r + 1) * cellSize,
                       2 * (r + 1) * cellSize,
                       2 * (r + 1) * cellSize);

      QRectF innerRect(center.x() - r * cellSize,
                       center.y() - r * cellSize,
                       2 * r * cellSize,
                       2 * r * cellSize);

      // Создаём кольцевой сектор
      QPainterPath path;
      path.moveTo(center);
      path.arcTo(outerRect, startAngle, angleStep);
      path.lineTo(center);
      path.arcTo(innerRect, startAngle + angleStep, -angleStep);
      path.closeSubpath();

      // Цвет по шахматному принципу
      bool isBlack = (r + s) % 2 == 0;
      painter->setBrush(isBlack ? Qt::black : Qt::white);
      painter->setPen(Qt::NoPen);
      painter->drawPath(path);
    }
  }
}
