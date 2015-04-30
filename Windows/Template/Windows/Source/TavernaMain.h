#ifndef __Taverna__TavernaMain__
#define __Taverna__TavernaMain__

#include "Polycode.h"
#include "TavernaEventHandler.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"
#include "GameUI.h"
#include "define.h"
#include "GameData.h"
#include "Person.h"
#include "GameController.h"
#include "StartScreen.h"
#include "MenuMonth.h"
#include "GameOver.h"
#include <vector>

using namespace Polycode;

class TavernaMain {
public:
   TavernaMain(Core *core);
   ~TavernaMain();

   GameData *gameData;
   Core *core;
   CollisionScene *scene3D;
   Scene *scene2D;
   GameUI *gameUI;
   TavernaEventHandler *inputHandler;
   GameController *gameController;
   int gameMode;
   int rep;
   bool intro;

   StartScreen *startScreen;
   MenuMonth *menuMonth;
   TavernResources *tavRes;

   void Update();
   bool crowdNoise;
   bool lightFlicker;
   bool gameOver;
};

#endif