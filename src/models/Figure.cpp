#include "Figure.h"
#include "MovePlanner.h"

#include "../Common.h"
#include "../managers/TextureManager.h"
#include "../managers/FiguresManager.h"

#include <QPainter>
#include <QJsonArray>


Figure::Figure(QString player, QJsonObject data) : m_infoFigure(data)
{
  m_player = player;
  QPixmap base = TextureManager::instance().getTexture(data[TYPE_FIGURE].toString());

  QColor color = Qt::white;
  if(m_player == PLAYER.arg(0))
  {}
  else if(m_player == PLAYER.arg(1))
  {
   color = QColor(60, 70, 54);
  }
  m_pixmap = colorizedPixmap(base, color);
}

QPixmap Figure::colorizedPixmap(const QPixmap &base, const QColor &color)
{
  QPixmap colored(base.size());
  colored.fill(Qt::transparent);
  // colored

  QPainter painter(&colored);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.drawPixmap(0, 0, base);

  painter.setCompositionMode(QPainter::CompositionMode_Multiply);
  painter.fillRect(colored.rect(), color); // нужный цвет

  painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
  painter.drawPixmap(0, 0, base); // применяем альфа-канал от оригинала

  painter.end();

  return colored;
}

void Figure::setPosition(QString pos)
{
  if(pos.size() < 2)
    pos = "A1";

  m_boardPos = pos;

  QChar colChar = pos[0].toUpper();
  QChar rowChar = pos[1];

  QPointF posPintF = QPointF((colChar.toLatin1() - 'A') * 40,
                             (rowChar.toLatin1() - '1') * 40);

  setPos(posPintF);
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  FiguresManager::getInstance().onFigureClicked(this);
}

std::vector<Move> Figure::movePatterns()
{
  m_highlightMoves.clear();

  QJsonObject patterns = m_infoFigure[MOVE_PATTERNS].toObject();
  QJsonObject dimensions = patterns[DIMENSIONS].toObject();
  QJsonArray dirs = dimensions[m_player].toArray();

  int countMove = patterns[STROKE_LENGTH].toInt();

  for(const auto& dirVal :dirs)
  {
    QString dir = dirVal.toString();
    int dx = 0;
    int dy = 0;

    if (dir == "U")      dy = -1;
    else if (dir == "D") dy = +1;
    else if (dir == "L") dx = -1;
    else if (dir == "R") dx = +1;
    else if (dir == "UL") { dx = -1; dy = -1; }
    else if (dir == "UR") { dx = +1; dy = -1; }
    else if (dir == "DL") { dx = -1; dy = +1; }
    else if (dir == "DR") { dx = +1; dy = +1; }

    for(int i = 1; i <= countMove; i++)
    {
      Move m;
      m.x = dx * i;
      m.y = dy * i;
      m.color = Qt::white;
      m.direction = dir;
      m_highlightMoves.push_back(m);
    }
  }
  return m_highlightMoves;
}

QRectF Figure::boundingRect() const
{
  return QRectF(0, 0, 40, 40);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawPixmap(boundingRect().toRect(), m_pixmap);
}
