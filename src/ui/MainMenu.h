#ifndef MAINMENU_H
#define MAINMENU_H

#include "base/BaseWidget.h"

class QLabel;

class MainMenu : public BaseWidget
{
  Q_OBJECT
public:
  MainMenu(QWidget* parent = nullptr);

private:
  void setup();

  QWidget* setupGameFormStart(QString name, QString link);
  QLabel* setupImage(QString link);
};

#endif // MAINMENU_H
