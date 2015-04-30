#ifndef MENUPATRON
#define MENUPATRON

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "GameData.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include <iostream>

using namespace Polycode;

class MenuPatron : public EventHandler {
   
public:
   MenuPatron();
   ~MenuPatron();
   
   void handleEvent(Event *e);
   void Update();
   
   GameData *gameData;
   Core *core;
   Scene *scene2D;
   Scene *scene3D;
   bool isActive;

   MenuImage *patronBox;
   
private:
   UIImageButton *button;
   UIImageButton *menuItems[4];
   
};

#endif