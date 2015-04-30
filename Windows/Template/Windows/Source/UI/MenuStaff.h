#ifndef MENUSTAFF
#define MENUSTAFF

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "GameData.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include <iostream>

using namespace Polycode;

class MenuStaff : public EventHandler {
   
public:
   MenuStaff();
   ~MenuStaff();
   
   void handleEvent(Event *e);
   void Update();
   
   GameData *gameData;
   Core *core;
   Scene *scene2D;
   Scene *scene3D;
   bool isActive;

   MenuImage *staffBox;
   
private:
   UIImageButton *button;
   UIImageButton *menuItems[4];
};

#endif