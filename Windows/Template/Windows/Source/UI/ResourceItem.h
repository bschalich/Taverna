#ifndef __Taverna__Resource__
#define __Taverna__Resource__

class TavernResources;
class GameUI;

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "GameData.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include "TavernResources.h"
#include "GameUI.h"
#include <iostream>

using namespace Polycode;

class ResourceItem : public EventHandler {

public:
	ResourceItem(GameUI *gameUI, int x, int y, TavernResources::Items type, String title, String image);
   ~ResourceItem();
   
   void handleEvent(Event *e);
   
   GameData *gameData;
   GameUI *gameUI;
   
   MenuImage *transparentBox;
   SceneLabel *stockValue;

   void deactivateStocks();
private:
	int x;
	int y;
   TavernResources *resources;
   String title;
   String image;
   TavernResources::Items type;
   SceneLabel *buyPriceValue;
   SceneLabel *sellPriceValue;
  
   MenuItem *sellPriceArrowUp;
   MenuItem *sellPriceArrowDown;
   MenuItem *stockArrowUp;
   MenuItem *stockPlusFive;

   void build();
};

#endif