#include "FiguresFactory.h"

#include "../Common.h"
#include "../models/Figure.h"

#include <QJsonArray>

QList<Figure*> FiguresFactory::createFigures(const QJsonObject& data, const EditMode& mode)
{
  QList<Figure*> figures;

  switch (mode) {
  case EditMode::Standard:
   figures = createDefaultFigures(data);
    break;
  case EditMode::Playing:
    figures = createDefaultFigures(data);
    break;
  default:
    break;
  }

  return figures;
}

Figure* FiguresFactory::createFigure(const QString& playerKey, const QJsonObject& figureInfo, const QString& pos)
{
    Figure* figure = new Figure(playerKey, figureInfo);
    figure->setPosition(pos);
    return figure;
}

QList<Figure*> FiguresFactory::createDefaultFigures(const QJsonObject& data)
{
  QList<Figure*> figuresList;

  QJsonArray figures = data.value(FIGURES).toArray();

  if(figures.isEmpty())
    return figuresList;

  for(int i = 0; i < figures.size(); i++)
  {
    QJsonObject figureInfo = figures[i].toObject();
    QJsonObject startPositions = figureInfo.value(START_POSITIONS).toObject();

    for (const QString& playerKey : startPositions.keys())
    {
      QJsonArray positions = startPositions[playerKey].toArray();

      for(const auto& posValue : positions)
      {
        QString pos = posValue.toString();
        figuresList.append(createFigure(playerKey, figureInfo, pos));
      }
    }
  }

  return figuresList;
}

QList<Figure*> FiguresFactory::createEditorFigure(const QJsonObject& data)
{
  // int pos = arrow.size() / 2;
  // QJsonArray figuresInfo = data[FIGURES].toArray();
  // if (figuresInfo.isEmpty()) return;

  // int id = -1;// = ChessBoardManager::getInstance().m_idFigure;
  // if(id == -1)
  //   return;

  // QJsonArray posArray = data.value(BOARD).toObject().value(DIMENSIONS).toArray();
  // if(posArray.size() < 2)
  //   return;

  // QString pos;// = BoardChess::getPos(posArray.at(0).toString().toInt() / 2,
  // //                   posArray.at(1).toString().toInt() / 2);

  // QJsonObject figureInfo = figuresInfo[id].toObject();
  // Figure* figure = new Figure("", figureInfo);
  // figure->setPosition(pos);
  // figure->setParentItem(this);
  // m_figures.push_back(figure);
  // return;

  QList<Figure*> figuresList;
  return figuresList;
}
