#ifndef CHESSMENU_H
#define CHESSMENU_H

#include "../base/BaseWidget.h"

class QGraphicsView;

class ChessMenu : public BaseWidget
{
    Q_OBJECT
public:
  ChessMenu();

private:
  void setup();
  void setupStyleSheet();
  QWidget* setupBtn();


private:
  QGraphicsView* m_display;
};

#endif // CHESSMENU_H
