#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BaseWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();

signals:
  void closeApp();

public slots:
    void setWidget(QString name);

private:
  BaseWidget* m_currentWidget;
};

#endif // MAINWINDOW_H
