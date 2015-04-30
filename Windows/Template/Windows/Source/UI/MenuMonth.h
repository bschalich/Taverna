#ifndef __Taverna__MenuMonth__
#define __Taverna__MenuMonth__

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

class MenuMonth : EventHandler{
public:
   MenuMonth();
   ~MenuMonth();

   void handleEvent(Event *e);

   bool getIsDone();
   void Update();
private:

   MenuImage *bg;
   MenuLabel *month;
   MenuLabel *gold;

   MenuItem *startButton;
   MenuItem *infoButton;
   MenuItem *stockButton;
   MenuItem *staffButton;
   MenuItem *buildButton;
   MenuItem *doneButton;

   MenuResources *resourcesMenu;
   MenuBuild *buildMenu;
   MenuStaff *staffMenu;

   MenuImage *infoContainer;
   MenuImage *stockContainer;
   MenuImage *staffContainer;

   MenuItem *lvl1Buy;
   MenuItem *lvl2Buy;
   MenuItem *lvl3Buy;

   MenuLabel *lvl1Owned;
   MenuLabel *lvl2Owned;
   MenuLabel *lvl3Owned;

   GameData *gameData;
   TavernResources *resources;

   bool isDone;

   void clear();

   void createInfo();
   void createStock();
   void createStaff();
   void fireStaff(int level);

   void createStaffItem(int level, MenuImage *parent);
   int getOwned(int level);
};

#endif