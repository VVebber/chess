#include "WidgetFactory.h"
#include "../Common.h"

#include "../ui/MainMenu.h"
#include "../ui/Chess/ChessMenu.h"
#include "../ui/Chess/ChessEditor.h"
#include "../ui/Chess/PlayMenu.h"

BaseWidget* WidgetFactory::createWidget(QString name, QWidget* parant)
{
  if(name == WIDGET_MAIN_MENU)
    return new MainMenu(parant);
  else if(name == WIDGET_CHESS_GAME)
    return new ChessMenu(parant);
  else if(name == WIDGET_CHESS_EDITOR)
    return new ChessEditor(parant);
  else if(name == WIDGET_PLAY_MENU)
    return new PlayMenu(parant);
  return nullptr;
}

