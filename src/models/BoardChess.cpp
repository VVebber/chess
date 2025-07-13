#include "BoardChess.h"
#include "../Common.h"

#include "../core/ChessCoord.h"

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
  qDebug()<<Q_FUNC_INFO;
  m_noShowCells.clear();

  m_infoBoard = data[BOARD].toObject();

  QJsonArray noShowCells = m_infoBoard.value(NO_SHOW_CELLS).toArray();
  for(int i = 0; i < noShowCells.size(); i++)
  {
    m_noShowCells.insert(noShowCells.at(i).toString());
  }

  QJsonArray dimensions = m_infoBoard.value(DIMENSIONS).toArray();
  int x = 8, y = 8;

  if (dimensions.size() >= 2) {
    x = dimensions.at(0).toString().toInt();
    y = dimensions.at(1).toString().toInt();
  }

  m_sizeBoard = QSize(x,y);
}

void BoardChess::setup(QJsonObject data)
{}

QRectF BoardChess::boundingRect() const
{
  int x = 40 * (m_sizeBoard.width() + 1);
  int y = 40 * (m_sizeBoard.height() + 1);
  return QRectF(0, 0, x, y);
}


QSize BoardChess::size() const {
  return QSize(40 * m_sizeBoard.width() - 1,
               40 * m_sizeBoard.height() - 1);
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
      painter->setBrush(Qt::green);
      painter->drawEllipse(20, -40, 80, 80); // x = 20 (правый край), y = -40, радиус 80
    }
  }
}

void BoardChess::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QPoint posPressed = event->pos().toPoint();
  int x = posPressed.x() / 40;
  int y = posPressed.y() / 40;

  if (x < 0 || x >= m_sizeBoard.width() || y < 0 || y >= m_sizeBoard.height())
      return;

  emit cellName(ChessCoord::fromStr(x, y));
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
