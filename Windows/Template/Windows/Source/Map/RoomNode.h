#ifndef __Taverna__ExpansionNode__
#define __Taverna__ExpansionNode__

#include "PolyCode.h"
#include "define.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"

class RoomNode
{
public:
    RoomNode(Vector2 centerPos, int rowLen, int colLen, int ID);
    ~RoomNode();
   
   int getID();
   Vector2 getDims();
   Vector2 getCenterPos();
   Vector2 centerPos;
    int rowLen, colLen, ID;
private:
   
   
};

#endif