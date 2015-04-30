#ifndef __Taverna__Menu__
#define __Taverna__Menu__

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "GameData.h"
#include <iostream>

using namespace Polycode;

class Menu : public EventHandler {
   
public:
   Menu(GameData *game);
   ~Menu();
   
   void handleEvent(Event *e);
   void Update();
   
   GameData *gameData;
   Core *core;
   Scene *scene2D;
   Scene *scene3D;
   
private:
   UIImageButton *button;
   UIBox *menuBox;
   UIImageButton *menuItems[4];
   
};

#endif