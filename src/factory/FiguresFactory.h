#ifndef FIGURESFACTORY_H
#define FIGURESFACTORY_H

#include "../core/EditMode.h"

#include <QList>
#include <QJsonObject>

class Figure;

class FiguresFactory
{
public:
  static QList<Figure*> createFigures(const QJsonObject& data, const EditMode& mode);

private:
  static Figure* createFigure(const QString& playerKey, const QJsonObject& figureInfo, const QString& pos);

  static QList<Figure*> createDefaultFigures(const QJsonObject& data);
  static QList<Figure*> createEditorFigure(const QJsonObject& data);

};

#endif // FIGURESFACTORY_H
