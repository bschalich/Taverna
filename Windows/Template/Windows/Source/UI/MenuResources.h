#ifndef __Taverna__MenuResources__
#define __Taverna__MenuResources__

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "GameData.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include "TavernResources.h"
#include "GameUI.h"
#include "ResourceItem.h"
#include <iostream>

using namespace Polycode;
class GameUI;
class MenuResources : public EventHandler {

public:
   MenuResources(GameUI *gameUI);
   ~MenuResources();
   
   void handleEvent(Event *e);
   void Update();
   
   GameData *gameData;
   GameUI *gameUI;
   Core *core;
   Scene *scene2D;
   Scene *scene3D;
   bool isActive;

   MenuImage *resourcesBox;
   
private:
   UIImageButton *button;
   UIImageButton *menuItems[4];
   TavernResources *resources;
   SceneLabel *sellPriceValue;
   SceneLabel *stockValue;
   //SceneLabel *gold;
   MenuItem *sellPriceArrowUp;
   MenuItem *sellPriceArrowDown;
   MenuItem *stockArrowUp;

   void prepResources();
   void buildResource();
   MenuImage *transparentBox;
};

#endif