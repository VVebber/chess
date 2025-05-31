#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BaseWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();

public slots:
    void setWidget(QString name);

// private:
  // void initStyle();

private:
  BaseWidget* m_currentWidget;
};

#endif // MAINWINDOW_H
