#include "WidgetFactory.h"
#include "../Common.h"

#include "../ui/MainMenu.h"
#include "../ui/Chess/ChessMenu.h"
#include "../ui/Chess/ChessEditor.h"

BaseWidget* WidgetFactory::createWidget(QString name)
{
  if(name == WIDGET_MAIN_MENU)
    return new MainMenu;
  else if(name == WIDGET_CHESS_GAME)
  {
    return new ChessMenu;
  }
  else if(name == WIDGET_CHESS_EDITOR)
    return new ChessEditor;
  return nullptr;
}
