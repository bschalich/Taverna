//
//  Door.h
//  Taverna
//
//  Created by Bennett Schalich on 4/4/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#ifndef DOOR
#define DOOR

#include "PolyCode.h"
#include "define.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"
#include "RoomNode.h"
#include <list>

class Door
{
public:
   Door(GameMap *map);
   ~Door();
   void addDoor(list<RoomNode*> rnList, Vector2 pos, int whichWall);
   void removeDoor(list<RoomNode*> rnList, Vector2 pos, int whichWall);
   
private:
   RoomNode* lookUpRoom(list <RoomNode*> rnList, Vector2 pos);
   int getID(Vector2 pos);
   int getDoorCount(RoomNode *rn);
   int getType(int dRow, int dCol);
   void setCenterPos(RoomNode *rn);
   void makeDoor(RoomNode *rn, int whichWall);
   void setTileDoor(int row, int col, int type);
   void setTile(int dRow, int dCol, int type);
   void deleteDoor(RoomNode *rn, int whichWall);
   void deleteRightTopDoor(int rowChange, int colChange);
   void deleteLeftTopDoor(int rowChange, int colChange);
   void deleteRightBotDoor(int rowChange, int colChange);
   void deleteLeftBotDoor(int rowChange, int colChange);
   
   //instance variables
   GameMap *map;
   Vector2 centerPos;
      //rt == right_top ; lt == left_top ; rb == right_bot ; lb == left_bot
   bool rtDoor, ltDoor, rbDoor, lbDoor;
};

#endif