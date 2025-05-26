#include "Figure.h"
#include "../Common.h"
#include "../managers/TextureManager.h"
#include "../managers/FiguresManager.h"

#include <QPainter>
#include <QJsonArray>

Figure::Figure(QString player, QJsonObject data) : m_infoFigure(data)
{
  m_player = player;
  m_pixmap = TextureManager::instance().getTexture(data[TYPE_FIGURE].toString());
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
  painter->setBrush(Qt::green);
  painter->drawPixmap(boundingRect().toRect(), m_pixmap);
}
