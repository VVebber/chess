#include "Figure.h"
#include "../Common.h"
#include "../managers/TextureManager.h"

#include <QPainter>

Figure::Figure(QJsonObject data) : m_infoFigure(data)
{
  m_pixmap = TextureManager::instance().getTexture(data[TYPE_FIGURE].toString());
  m_pos = QPointF(0,0);
}

void Figure::setPosition(QString pos)
{
  if(pos.size() < 2)
    return;

  QChar colChar = pos[0].toUpper();
  QChar rowChar = pos[1];

  m_pos = QPointF((rowChar.toLatin1() - '1') * 40,
                  (colChar.toLatin1() - 'A') * 40);

  setPos(m_pos);
}

QRectF Figure::boundingRect() const
{
  return QRectF(0, 0, 40, 40);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setBrush(Qt::green);
  painter->drawPixmap(boundingRect().toRect(), m_pixmap);
}
