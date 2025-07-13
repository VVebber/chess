#include "Figure.h"

#include "../Common.h"
#include "../core/ChessCoord.h"
#include "../managers/TextureManager.h"
#include "../managers/FiguresManager.h"
#include "../managers/BoardViewManager.h"

#include <QPainter>
#include <QJsonArray>
#include <QGraphicsSceneMouseEvent>


Figure::Figure(QString player, QJsonObject data) : m_infoFigure(data)
{
  m_player = player;
  m_type = data[TYPE_FIGURE].toString();

  m_hasMoved = true;

  QPixmap base = TextureManager::instance().getTexture(data[TYPE_FIGURE].toString());

  QColor color = (m_player == PLAYER_EN.arg(1)) ? QColor(60, 70, 54) : Qt::white;
  m_pixmap = colorizedPixmap(base, color);
}

Figure::~Figure(){}

QPixmap Figure::colorizedPixmap(const QPixmap &base, const QColor &color)
{
  QPixmap colored(base.size());
  colored.fill(Qt::transparent);

  QPainter painter(&colored);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.drawPixmap(0, 0, base);

  painter.setCompositionMode(QPainter::CompositionMode_Multiply);
  painter.fillRect(colored.rect(), color);

  painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
  painter.drawPixmap(0, 0, base);

  painter.end();

  return colored;
}

void Figure::setPosition(QString pos)
{
  if(pos.size() < 2)
    pos = "A1";

  m_boardPos = pos;
  QPoint posPintF(ChessCoord::fromPoint(pos));
  setPos(posPintF);
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  FiguresManager::getInstance().onFigureClicked(this);

  BoardViewManager::getInstance().forwardMousePressToBoard(event->scenePos(), event);
}

std::vector<Move> Figure::movePatterns()
{
  std::vector<Move> highlightMoves;

  QJsonObject patterns = m_infoFigure[MOVE_PATTERNS].toObject();
  QJsonObject directions = patterns[DIRECTIONS].toObject();

  if(directions.contains(STEPS))
  {
    highlightMoves = stepMoves(patterns);
  }
  else if(directions.contains(JUMPS))
  {
    highlightMoves = jumpMoves(patterns);
  }
  return highlightMoves;
}

std::vector<Move> Figure::stepMoves(const QJsonObject& movePatterns)
{
    std::vector<Move> highlightMoves;

    QJsonObject directions = movePatterns[DIRECTIONS].toObject();
    QJsonObject steps = directions.value(STEPS).toObject();
    QJsonArray dirs = steps.value(m_player).toArray();
    int countMove = movePatterns.value(STROKE_LENGTH).toInt();

    for (const auto& dirVal : dirs)
    {
        QString dir = dirVal.toString();
        int dx = 0, dy = 0;

        if (dir == "U") dy = -1;
        else if (dir == "D") dy = 1;
        else if (dir == "L") dx = -1;
        else if (dir == "R") dx = 1;
        else if (dir == "UL") { dx = -1; dy = -1; }
        else if (dir == "UR") { dx = 1; dy = -1; }
        else if (dir == "DL") { dx = -1; dy = 1; }
        else if (dir == "DR") { dx = 1; dy = 1; }

        for (int i = 1; i <= countMove; ++i)
        {
            Move m;
            m.x = dx * i;
            m.y = dy * i;
            m.color = Qt::white;
            m.direction = dir;
            highlightMoves.push_back(m);
        }
    }

    return highlightMoves;
}

std::vector<Move> Figure::jumpMoves(const QJsonObject& movePatterns)
{
    std::vector<Move> jumps;
    QJsonObject directions = movePatterns[DIRECTIONS].toObject();
    QJsonObject jump = directions.value(JUMPS).toObject();

    QJsonArray jumpArray = jump.value(m_player).toArray();

    for (const auto& jumpVal : jumpArray)
    {
        QJsonObject move = jumpVal.toObject();

        Move m;
        m.x = move.value("x").toInt();
        m.y = move.value("y").toInt();
        m.color = Qt::white; // отличить прыжок, если нужно
        m.direction = "JUMP";
        jumps.push_back(m);
    }

    return jumps;
}


QRectF Figure::boundingRect() const
{
  return QRectF(0, 0, 40, 40);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawPixmap(boundingRect().toRect(), m_pixmap);
}
