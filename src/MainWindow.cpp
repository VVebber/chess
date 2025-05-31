#include "MainWindow.h"

#include "Common.h"
#include "ui/base/BaseWidget.h"
#include "factory/WidgetFactory.h"

MainWindow::MainWindow()
{
  setObjectName("MainWindow");
  resize(1280,720);
  m_currentWidget = nullptr;
  setWidget(WIDGET_CHESS_GAME);
  setStyleSheet(R"(
     #MainWindow  {
          background-image: url(./img/backgrounds/1_background.png);     /* Путь к текстуре */
          background-repeat: no-repeat;
          background-position: center;
          background-origin: content;
      }
  )");
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
