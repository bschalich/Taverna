#ifndef __Taverna__TavneraEventHandler__
#define __Taverna__TavneraEventHandler__

class GameData;
class GameUI;

#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"
#include "define.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "PolycodeUI.h"
#include "GameData.h"
#include "GameUI.h"
#include "TavernExpansion.h"
#include "Room.h"
#include "Deleter.h"
#include "GameData.h"
#include "Person.h"
#include "Staff.h"
#include <list>
#include "RoomNode.h"
#include "Door.h"
#include "TextBubble.h"

using namespace Polycode;

class TavernaEventHandler : public EventHandler{
public:
   TavernaEventHandler();
   ~TavernaEventHandler();
   
   void handleEvent(Event *e);
   void Update();
   void moveCameraTo(Number x, Number z, Number lerp);
   
   GameData *gameData;
   PolycodeData *polycodeData;
   Core *core;
   CollisionScene *scene;
   Scene *scene2D;
   bool cameraEvent;
   bool cameraZoomEvent;
   bool mouseDown;
   bool gameStart;
   int mode;
   GameMap* map;
    
   Vector2 *saveTile;
   
private:
   Renderer *rend;
   Vector3 cameraMove;
   Vector2 zoomDelta;
   Vector2 newZoom;
   Vector2 mousePos;
   Vector2 mousePosDelta;
   Number maxZoomIn;
   Number maxZoomOut;
    Deleter *deleter;
    Room *room;
    TavernExpansion *te;
    Door *door;
    int ID;
	Person *hoverPerson;
	Table *hoverTable;

   void cameraMoveEvent(InputEvent *inputEvent);
   void hoverTileEvent(InputEvent *inputEvent);
   void mouseDownEvent(InputEvent *inputEvent);
   void mouseOverEvent(InputEvent *inputEvent);
   void clickObject(InputEvent *inputEvent);
   void hoverPersonEvent(InputEvent *inputEvent);
   void hoverTableEvent(InputEvent *inputEvent);
   
   list<RoomNode *> rnList;
   
};

#endif
