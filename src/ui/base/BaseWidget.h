#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "../../core/AppVariables.h"

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    BaseWidget(QWidget *parent = nullptr);
    virtual ~BaseWidget();


public slots:
    virtual void onSetWidgetClicked();

signals:
    void setWidget(QString name);


protected:
    void setBackground(QString type);

protected:
    AppVariables m_variabels;
};

#endif // BASEWIDGET_H
