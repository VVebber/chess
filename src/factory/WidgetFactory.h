#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <QString>

class BaseWidget;
class QWidget;

class WidgetFactory
{
public:
    static BaseWidget* createWidget(QString name, QWidget* parant);
};

#endif // WIDGETFACTORY_H
