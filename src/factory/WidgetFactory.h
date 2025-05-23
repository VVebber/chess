#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <QString>

class BaseWidget;

class WidgetFactory
{
public:
    static BaseWidget* createWidget(QString name);
};

#endif // WIDGETFACTORY_H
