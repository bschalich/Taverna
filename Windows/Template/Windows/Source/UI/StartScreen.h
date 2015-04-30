#ifndef __Taverna__StartScreen__
#define __Taverna__StartScreen__

#include "Polycode.h"
#include "PolycodeUI.h"
#include "define.h"
#include "MenuItem.h"
#include "MenuImage.h"
#include "MenuLabel.h"
#include "GameData.h"

#include <iostream>

using namespace Polycode;

class StartScreen : public EventHandler {
public:
   StartScreen();
   ~StartScreen();
   
   void handleEvent(Event *e);
   void Update();
   bool getIsStart();

private:

   MenuItem *startButton;
   MenuImage *title;

   GameData *gameData;

   bool isStart;
};

#endif