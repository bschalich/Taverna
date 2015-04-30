#ifndef __Taverna__GameUI__
#define __Taverna__GameUI__

class GameData;
class TavernResources;
class MenuResources;
class MenuBuild;
class MenuImage;
class MenuItem;
class MenuPatron;
class MenuResources;
class MenuSprite;
class MenuStaff;
class Person;
class Staff;

#include "Polycode.h"
#include "PolycodeUI.h"
#include "Person.h"
#include "Staff.h"
#include "define.h"
#include "MenuBuild.h"
#include "MenuPatron.h"
#include "MenuStaff.h"
#include "MenuResources.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include "MenuLabel.h"
#include "MenuSprite.h"
#include "TavernResources.h"
#include "GameData.h"
#include "Ticker.h"

#include <iostream>

#define NONE 0
#define BUILD 1
#define PATRON 2
#define STAFF 3
#define RESOURCES 4

using namespace Polycode;

class GameUI : public EventHandler {
public:
   ~GameUI();
   
   static GameUI *getInstance();
   void handleEvent(Event *e);
   void Update();
   
   void setPortraitPerson(Person *person);
   void openBuildMenu();
   
   GameData *gameData;
   Core *core;
   Scene *scene2D;
   Scene *scene3D;
   
   SceneLabel *gold;
   SceneLabel *capacity;
   SceneLabel *month;
   SceneLabel *day;

   Timer *testTimer;
   Ticker *ticker;

   MenuImage *portrait;
   MenuImage *menubar;
   
private:
	GameUI();
	static GameUI *gameUIInstance;
	TavernResources *resources;

   UIImageButton *button;
   MenuImage *barInfoBox;
   SceneLabel *rep;

   SceneLabel *tickers[5];
   SceneLabel *health;
   SceneLabel *level;
   SceneLabel *name;
   SceneLabel *happiness;
   SceneLabel *thirst;
   SceneLabel *hunger;
   SceneLabel *maxPurchase;
   MenuItem *fire;

   Person *curPerson;

   MenuItem *buildButton;
   MenuItem *staffButton;
   MenuItem *patronsButton;

   MenuItem *buildIcon;
   MenuItem *staffIcon;
   MenuItem *resourcesIcon;

   MenuSprite *sprite;
   MenuBuild *menuBuild;
   MenuPatron *menuPatron;
   MenuStaff *menuStaff;
   MenuResources *menuResources;

   bool menuToggle;
   bool toggle;
   bool moveMenu;
   int menuMode;

   bool gold750;
   
   void buildUI();
   void buildTicker();
   void buildBarInfo();
   void createBuildMenu();
   void openPatronMenu();
   void openStaffMenu();
   void openResourcesMenu();
   void animateMenubar();
   void mySleep(int milliseconds);
   void setActiveMenu(int mode);
   void deactivateMenu();
};

#endif