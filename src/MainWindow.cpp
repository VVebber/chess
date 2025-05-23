#include "MainWindow.h"

#include "Common.h"
#include "ui/base/BaseWidget.h"
#include "factory/WidgetFactory.h"

MainWindow::MainWindow()
{
  resize(1280,720);
  m_currentWidget = nullptr;
  setWidget(WIDGET_MAIN_MENU);
}

void MainWindow::setWidget(QString name)
{
  if(name.isEmpty())
    return;

  BaseWidget* newWidget = WidgetFactory::createWidget(name);
  if(newWidget != nullptr)
  {
    if(m_currentWidget != nullptr)
    {
      disconnect(m_currentWidget, &BaseWidget::setWidget, this, &MainWindow::setWidget);
      delete m_currentWidget;
      m_currentWidget = 0;
    }
    m_currentWidget = newWidget;
    m_currentWidget->resize(1280,720);
    connect(m_currentWidget, &BaseWidget::setWidget, this, &MainWindow::setWidget);
    m_currentWidget->setParent(this);
    m_currentWidget->show();
  }
}
