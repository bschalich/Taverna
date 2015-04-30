#pragma once

#ifndef MENULABEL
#define MENULABEL

class UIMover;

#include "UIMover.h"
#include "Polycode.h"
#include "PolycodeUI.h"
#include "GameData.h"
#include <list>
#include <iostream>

using namespace Polycode;
using namespace std;

class MenuLabel : public SceneLabel {
public:
   MenuLabel(String text, int size, String font);
   ~MenuLabel();
   
   GameData *gameData;

   void moveFromCurrent(Number x, Number y, Number z, Number speed);
   void Update();
   void setPosition(Vector3 pos);
   void setPositions(int x, int y);
   void setAliveTimer(float num);
   
protected:
   Number id;
   Timer *moveTimer;
   list<Vector3> steps;
   Core *core;
   Scene *scene2D;

   Number curX;
   Number curY;
   Number curZ;

   	float positionX;
	float positionY;
	float positionZ;
	float speed;
	float aliveTimer;
   
private:

};

#endif