#pragma once

#ifndef UIMOVER
#define UIMOVER

class PolycodeData;

#include "Polycode.h"
#include "GameData.h"
#include "PolycodeUI.h"
#include <list>
#include <iostream>
#include <cmath>

using namespace Polycode;
using namespace std;

class UIMover {
public:
	UIMover();
   ~UIMover();

   static Vector3 moveIn3DLurp(Vector3 current, Vector3 desired);
   static Vector3 moveIn3DLinear(Vector3 current, Vector3 desired, int speed);
   
protected:
    
private:
	float speed;
};

#endif