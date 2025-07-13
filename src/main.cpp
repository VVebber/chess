#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  QObject::connect(&w, &MainWindow::closeApp, &a, &QApplication::quit);

  return a.exec();
}
