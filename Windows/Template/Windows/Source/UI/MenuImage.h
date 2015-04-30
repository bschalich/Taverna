#ifndef MENUIMAGE
#define MENUIMAGE

class UIMover;

#include "UIMover.h"
#include "Polycode.h"
#include "PolycodeUI.h"
#include "GameData.h"
#include <list>
#include <iostream>

using namespace Polycode;
using namespace std;

class MenuImage : public UIImage {
public:
   MenuImage(String file, Number width, Number height);
   ~MenuImage();
   
   GameData *gameData;

   void moveFromCurrent(Number x, Number y, Number speed);
   void setPositions(int x, int y);
   void Update();
   bool isStationary();

   bool lurp;
   
protected:
   Number id;
   Timer *moveTimer;
   list<Vector3> steps;
   Core *core;
   Scene *scene2D;
   
private:
	float positionX;
	float positionY;
	float speed;
};

#endif