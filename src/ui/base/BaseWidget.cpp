#include "BaseWidget.h"

#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QDialog>
#include <QLayout>
#include <QPushButton>

BaseWidget::BaseWidget(QWidget *parent) : QWidget{parent}
{

}

BaseWidget::~BaseWidget() {}

void BaseWidget::onSetWidgetClicked()
{
  QPushButton* btn = qobject_cast<QPushButton*>(sender());
  qDebug()<<Q_FUNC_INFO<< "Btn name:" << btn->objectName();
  emit setWidget(btn->objectName());
}
