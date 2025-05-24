#include "FiguresManager.h"
#include "../Common.h"
#include "../models/Figure.h"

#include <QJsonArray>

FiguresManager& FiguresManager::getInstance()
{
  static FiguresManager instans;
  return instans;
}

FiguresManager::FiguresManager()
{

}

QRectF FiguresManager::boundingRect() const
{
  return QRectF(0, 0, 40, 40);
}

void FiguresManager::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void FiguresManager::update(QJsonObject data)
{
  for(int i = 0; i < m_figures.size(); i++)
    delete m_figures[i];

  m_figures.clear();

  QJsonArray figures = data[FIGURES].toArray();

  for(int i = 0; i < figures.size(); i++)
  {
    QJsonObject data = figures[i].toObject();
    QJsonObject posPlayer = data[START_POSITIONS].toObject();
    for(auto key : posPlayer.keys())
    {
      QJsonArray arrow = posPlayer[key].toArray();
      for(int j = 0; j < arrow.size(); j++)
      {

        Figure* figure = new Figure(data);
        figure->setPosition(arrow.at(j).toString());
        figure->setParentItem(this);
        m_figures.push_back(figure);
      }
    }
  }
}
