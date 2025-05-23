#ifndef CHESSMENU_H
#define CHESSMENU_H

#include "../base/BaseWidget.h"

class ChessMenu : public BaseWidget
{
    Q_OBJECT
public:
  ChessMenu();

private:
  void setup();
  QWidget* setupBtn();

private:
};

#endif // CHESSMENU_H
