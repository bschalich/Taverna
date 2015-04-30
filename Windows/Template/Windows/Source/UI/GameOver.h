#ifndef __Taverna__GameOver__
#define __Taverna__GameOver__

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include "MenuLabel.h"
#include "GameData.h"
#include "TavernResources.h"
#include "ResourceItem.h"
#include "Staff.h"

#include <iostream>

using namespace Polycode;

class GameOver : EventHandler {
public:
   GameOver();
   ~GameOver();

   void handleEvent(Event *e);

   void Update();
private:

   MenuImage *bg;
   MenuLabel *gameOver;
   MenuLabel *month;
   MenuLabel *gold;

   MenuItem *doneButton;

   MenuImage *infoContainer;

   GameData *gameData;
   TavernResources *resources;
};

#endif