#ifndef MENUSPRITE
#define MENUSPRITE

#include "Polycode.h"
#include "PolycodeUI.h"
#include "GameData.h"
#include <list>
#include <iostream>

using namespace Polycode;
using namespace std;

class MenuSprite : public SceneSprite {
public:
   MenuSprite(GameData *game, String file, Number width, Number height);
   ~MenuSprite();
   
   GameData *gameData;

   void setData();

   void moveFromCurrent(Number x, Number y, Number speed);
   void setPositions(int x, int y);
   void Update();
   bool isStationary();
   
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