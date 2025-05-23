#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QJsonObject>

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
};

#endif // BASEWIDGET_H
