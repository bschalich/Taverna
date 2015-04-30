#ifndef __Taverna__MenuBuild__
#define __Taverna__MenuBuild__

class GameData;

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "GameData.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include "MenuLabel.h"
#include <ctime>
#include <iostream>

using namespace Polycode;

class MenuBuild : public EventHandler {
   
public:
   MenuBuild();
   ~MenuBuild();
   
   void handleEvent(Event *e);
   void Update();
   
   GameData *gameData;
   Core *core;
   Scene *scene2D;
   Scene *scene3D;
   bool isActive;

   SceneLabel *doorAdd;
   SceneLabel *doorRemove;

   MenuImage *buildBox;
   
private:
   UIImageButton *button;
   MenuItem *tab[8];
   MenuItem *expansionTab;
   MenuItem *kitchenTab;
   MenuItem *restroomTab;
   MenuItem *bedchambersTab;
   MenuItem *doorTab;
   MenuItem *expansionTabActive;
   MenuItem *kitchenTabActive;
   MenuItem *restroomTabActive;
   MenuItem *bedchambersTabActive;
   MenuItem *doorTabActive;
   MenuItem *menuItems[4];

   MenuItem *sizeBank[4];
   MenuItem *threeByThree;
   MenuItem *threeByFive;
   MenuItem *fiveByThree;
   MenuItem *fiveByFive;
   MenuItem *deleteButton;

   MenuItem *topLeftAddDoor;
   MenuItem *topRightAddDoor;
   MenuItem *lowerLeftAddDoor;
   MenuItem *lowerRightAddDoor;

   MenuItem *topLeftRemoveDoor;
   MenuItem *topRightRemoveDoor;
   MenuItem *lowerLeftRemoveDoor;
   MenuItem *lowerRightRemoveDoor;

   MenuItem *tableButton;

   int roomType;
   
   void setBuildDimensions(int width, int height);
   void setDoorEditing(int doorSide, int gameMode);
   void setMenuItems(int mod);
   void setMenuDoors();
   void removeMenuDoors();
   void setActiveTab(MenuItem *tab);
};

#endif