#ifndef MENUITEM
#define MENUITEM
#include "Polycode.h"
#include "PolycodeUI.h"
#include "GameData.h"
#include "UIMover.h"
#include <list>
#include <iostream>

using namespace Polycode;
using namespace std;

class MenuItem : public UIImageButton {
public:
   MenuItem(GameData *game, String file, Number width, Number height);
   ~MenuItem();
   
   GameData *gameData;

   void moveFromCurrent(Number x, Number y, Number speed);
   void setPositions(int x, int y);
   void Update();
   
protected:
   Number id;
   Timer *moveTimer;
   list<Vector3> steps;
   Core *core;
   Scene *scene2D;
   
private:
	int positionX;
	int positionY;
	int speed;
};

#endif