//
//  Door.cpp
//  Taverna
//
//  Created by Bennett Schalich on 4/4/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "Door.h"

Door::Door(GameMap *map)
{
   this->map = map;
   centerPos = Vector2(0, 0);
   ltDoor = rtDoor = rbDoor = lbDoor = false;
}

Door::~Door()
{
   
}

void Door::addDoor(list<RoomNode*> rnList, Vector2 clickPos, int whichWall)
{
   RoomNode *rn = lookUpRoom(rnList, clickPos);
   
   if (rn)
   {
      setCenterPos(rn);
      getDoorCount(rn);
      makeDoor(rn, whichWall);
   }
   
   else
      printf("ERROR\n");
}

void Door::removeDoor(list<RoomNode*> rnList, Vector2 clickPos, int whichWall)
{
   RoomNode *rn = lookUpRoom(rnList, clickPos);
   int doorCount = 0;
   
   if (rn)
   {
      setCenterPos(rn);
      doorCount = getDoorCount(rn);
      
      if (doorCount > 0)
      {
         deleteDoor(rn, whichWall);
      }
   }
   
   else
      printf("Error\n");
}

//return value corresponds if a door was deleted
void Door::deleteDoor(RoomNode *rn, int whichWall)
{
   int rowChange = rn->rowLen / 2;
   int colChange = rn->colLen / 2;
   
   if (whichWall == TOP_RIGHT)
      deleteRightTopDoor(rowChange, colChange);
   
   else if (whichWall == TOP_LEFT)
      deleteLeftTopDoor(rowChange, colChange);
   
   else if (whichWall == BOT_RIGHT)
      deleteRightBotDoor(rowChange, colChange);
   
   else if (whichWall == BOT_LEFT)
      deleteLeftBotDoor(rowChange, colChange);
}

void Door::makeDoor(RoomNode *rn, int whichWall)
{
   int row = rn->rowLen;
   int col = rn->colLen;
   
   if (whichWall == TOP_LEFT && !ltDoor && getType(-(row/2 + 1), 0) != INVIS_TILE)
   {
      //printf("centerPos(%0f, %0f)\n", centerPos.x, centerPos.y);
      setTileDoor(centerPos.x - (row/2), centerPos.y, LEFT_DOOR_TOP);
      
      if (getType(-(row/2 + 1), 0) == CORNER_BOT)
      {
         setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, CORNER_BOT_RIGHT_DOOR);
      }
      else if (getType(-(row/2 + 1), 0) == CORNER_RIGHT)
      {
         setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, CORNER_RIGHT_RIGHT_BOT_DOOR);
      }
      else
      {
         setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, RIGHT_DOOR_BOT);
      }
   }
   
   else if (whichWall == TOP_RIGHT && !rtDoor && getType(0, -(col/2 + 1)) != INVIS_TILE)
   {
      setTileDoor(centerPos.x, centerPos.y - (col/2), RIGHT_DOOR_TOP);
      
      if (getType(0, -(col/2 + 1)) == CORNER_BOT)
      {
         //printf("\nCORNER_BOT_LEFT_DOOR\n");
         setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), CORNER_BOT_LEFT_DOOR);
      }
      else if (getType(0, -(col/2 + 1)) == CORNER_LEFT)
      {
         //printf("\nCORNER_LEFT_LEFT_BOT_DOOR\n");
         setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), CORNER_LEFT_LEFT_BOT_DOOR);
      }
      else
      {
         //printf("\nELSE\n");
         setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), LEFT_DOOR_BOT);
      }
   }
   
   else if (whichWall == BOT_RIGHT && !rbDoor && getType(row/2 + 1, 0) != INVIS_TILE)
   {
      setTileDoor(centerPos.x + (row/2), centerPos.y, RIGHT_DOOR_BOT);
      
      if (getType((row/2 + 1), 0) == CORNER_LEFT)
      {
         //printf("\nCORNER_LEFT_LEFT_TOP_DOOR\n");
         setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, CORNER_LEFT_LEFT_TOP_DOOR);
      }
      else if (getType((row/2 + 1), 0) == CORNER_TOP)
      {
         //printf("\nCORNER_TOP_LEFT_DOOR\n");
         setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, CORNER_TOP_LEFT_DOOR);
      }
      else
      {
         //printf("\nELSE\n");
         setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, LEFT_DOOR_TOP);
      }
   }
   
   else if (whichWall == BOT_LEFT && !lbDoor && getType(0, col/2 + 1) != INVIS_TILE)
   {
      setTileDoor(centerPos.x, centerPos.y + (col/2), LEFT_DOOR_BOT);
      
      if (getType(0, col/2 + 1) == CORNER_TOP)
      {
         //printf("\nCORNER_TOP_RIGHT_DOOR\n");
         setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), CORNER_TOP_RIGHT_DOOR);
      }
      else if (getType(0, col/2 + 1) == CORNER_RIGHT)
      {
         //printf("\nCORNER_RIGHT_RIGHT_TOP_DOOR\n");
         setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), CORNER_RIGHT_RIGHT_TOP_DOOR);
      }
      else
      {
         //printf("\nELSE\n");
         setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), RIGHT_DOOR_TOP);
      }
   }
}

RoomNode* Door::lookUpRoom(list <RoomNode*> rnList, Vector2 clickPos)
{
   int ID = getID(clickPos);
   
   /*printf("ID: %d\n", ID);
   printf("size: %d\n", rnList.size());*/
   for (std::list<RoomNode*>::iterator it = rnList.begin(); it != rnList.end(); ++it)
   {
      printf("it ID: %d\n", (*it)->getID());
      if ((*it)->getID() == ID)
      {
         return *it;
      }
   }
   
   return NULL;
}

//look at borders or room and checks if
int Door::getDoorCount(RoomNode *rn)
{
   int rowChange = rn->rowLen / 2;
   int colChange = rn->colLen / 2;
   
   int count = 0;
   rtDoor = false;
   rbDoor = false;
   ltDoor = false;
   lbDoor = false;
   
   for (int dRow = -rowChange; dRow <= rowChange; dRow++)
   {
      if (this->getType(dRow, -colChange) == RIGHT_DOOR_TOP || this->getType(dRow, -colChange) == CORNER_TOP_RIGHT_DOOR || this->getType(dRow, -colChange) == CORNER_RIGHT_RIGHT_TOP_DOOR)
      {
         rtDoor = true;
         count++;
      }
   }
   
   for (int dCol = -colChange; dCol <= colChange; dCol++)
   {
      if (this->getType(-rowChange, dCol) == LEFT_DOOR_TOP || this->getType(-rowChange, dCol) == CORNER_TOP_LEFT_DOOR || this->getType(-rowChange, dCol) == CORNER_LEFT_LEFT_TOP_DOOR)
      {
         ltDoor = true;
         count++;
      }
   }
   
   for (int dCol = -colChange; dCol <= colChange; dCol++)
   {
      if (this->getType(rowChange, dCol) == RIGHT_DOOR_BOT || this->getType(rowChange, dCol) == CORNER_RIGHT_RIGHT_BOT_DOOR || this->getType(rowChange, dCol) == CORNER_BOT_RIGHT_DOOR)
      {
         rbDoor = true;
         count++;
      }
   }
   
   for (int dRow = -rowChange; dRow <= rowChange; dRow++)
   {
      if (this->getType(dRow, colChange) == LEFT_DOOR_BOT || this->getType(dRow, colChange) == CORNER_LEFT_LEFT_BOT_DOOR || this->getType(dRow, colChange) == CORNER_BOT_LEFT_DOOR)
      {
         lbDoor = true;
         count++;
      }
   }
   
   /*printf("rtDoor: %d\n", rtDoor);
   printf("ltDoor: %d\n", ltDoor);
   printf("rbDoor: %d\n", rbDoor);
   printf("lbDoor: %d\n", lbDoor);
   
   printf("\ncount: %d\n", count);*/
   
   return count;
}

void Door::deleteRightTopDoor(int rowChange, int colChange)
{
   for (int dRow = -rowChange; dRow <= rowChange; dRow++)
   {
      if (getType(dRow, -colChange) == RIGHT_DOOR_TOP)
      {
         setTile(dRow, -colChange, RIGHT_WALL_TOP);
      }
      
      else if (getType(dRow, -colChange) == CORNER_TOP_RIGHT_DOOR)
      {
         setTile(dRow, -colChange, CORNER_TOP);
      }
      
      else if (getType(dRow, -colChange) == CORNER_RIGHT_RIGHT_TOP_DOOR)
      {
         setTile(dRow, -colChange - 1, CORNER_RIGHT);
      }
      
      if (getType(dRow, -colChange - 1) == LEFT_DOOR_BOT)
      {
         //printf("A\n");
         setTile(dRow, -colChange - 1, RIGHT_WALL_BOT);
      }
      
      else if (getType(dRow, -colChange - 1) == CORNER_LEFT_LEFT_BOT_DOOR)
      {
         //printf("B\n");
         setTile(dRow, -colChange - 1, CORNER_LEFT);
      }
      
      else if (getType(dRow, -colChange - 1) == CORNER_BOT_LEFT_DOOR)
      {
         //printf("C\n");
         setTile(dRow, -colChange - 1, CORNER_BOT);
      }
   }
}

void Door::deleteLeftTopDoor(int rowChange, int colChange)
{
   for (int dCol = -colChange; dCol <= colChange; dCol++)
   {
      if (getType(-rowChange, dCol) == LEFT_DOOR_TOP)
      {
         setTile(-rowChange, dCol, LEFT_WALL_TOP);
      }
      
      else if (getType(-rowChange, dCol) == CORNER_LEFT_LEFT_TOP_DOOR)
      {
         setTile(-rowChange, dCol, CORNER_LEFT);
      }
      
      else if (getType(-rowChange, dCol) == CORNER_TOP_LEFT_DOOR)
      {
         setTile(-rowChange, dCol, CORNER_TOP);
      }
      
      if (getType(-rowChange - 1, dCol) == RIGHT_DOOR_BOT)
      {
         setTile(-rowChange - 1, dCol, LEFT_WALL_BOT);
      }
      
      else if (getType(-rowChange - 1, dCol) == CORNER_BOT_RIGHT_DOOR)
      {
         setTile(-rowChange - 1, dCol, CORNER_BOT);
      }
      
      else if (getType(-rowChange - 1, dCol) == CORNER_RIGHT_RIGHT_BOT_DOOR)
      {
         setTile(-rowChange - 1, dCol, CORNER_RIGHT);
      }
   }
}

void Door::deleteRightBotDoor(int rowChange, int colChange)
{
   for (int dCol = -colChange; dCol <= colChange; dCol++)
   {
      if (getType(rowChange, dCol) == RIGHT_DOOR_BOT)
      {
         setTile(rowChange, dCol, LEFT_WALL_BOT);
      }
      
      else if (getType(rowChange, dCol) == CORNER_RIGHT_RIGHT_BOT_DOOR)
      {
         setTile(rowChange, dCol, CORNER_RIGHT);
      }
      
      else if (getType(rowChange, dCol) == CORNER_BOT_RIGHT_DOOR)
      {
         setTile(rowChange, dCol, CORNER_BOT);
      }
      
      if (getType(rowChange + 1, dCol) == LEFT_DOOR_TOP)
      {
         setTile(rowChange + 1, dCol, LEFT_WALL_TOP);
      }
      
      else if (getType(rowChange + 1, dCol) == CORNER_LEFT_LEFT_TOP_DOOR)
      {
         setTile(rowChange + 1, dCol, CORNER_LEFT);
      }
      
      else if (getType(rowChange + 1, dCol) == CORNER_RIGHT_RIGHT_TOP_DOOR)
      {
         setTile(rowChange + 1, dCol, CORNER_RIGHT);
      }
   }
}

void Door::deleteLeftBotDoor(int rowChange, int colChange)
{
   printf("\n\nHERE\n\n");
   for (int dRow = -rowChange; dRow <= rowChange; dRow++)
   {
      if (getType(dRow, colChange) == LEFT_DOOR_BOT)
      {
         printf("A\n");
         setTile(dRow, colChange, RIGHT_WALL_BOT);
      }
      
      else if (getType(dRow, colChange) == CORNER_LEFT_LEFT_BOT_DOOR)
      {
         setTile(dRow, colChange, CORNER_LEFT);
      }
      
      else if (getType(dRow, colChange) == CORNER_BOT_LEFT_DOOR)
      {
         setTile(dRow, colChange, CORNER_BOT);
      }
      
      if (getType(dRow, colChange + 1) == RIGHT_DOOR_TOP)
      {
         printf("B\n");
         setTile(dRow, colChange + 1, RIGHT_WALL_TOP);
      }
      
      else if (getType(dRow, colChange + 1) == CORNER_RIGHT_RIGHT_TOP_DOOR)
      {
         setTile(dRow, colChange + 1, CORNER_RIGHT);
      }
      
      else if (getType(dRow, colChange + 1) == CORNER_TOP_RIGHT_DOOR)
      {
         setTile(dRow, colChange + 1, CORNER_TOP);
      }
   }
}

void Door::setCenterPos(RoomNode *rn)
{
   centerPos = rn->centerPos;
}

int Door::getType(int dRow, int dCol)
{
   return map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->getType();
}

int Door::getID(Vector2 clickPos)
{
   return map->getMapTile(clickPos.x, clickPos.y)->getRoomID();
}

void Door::setTileDoor(int row, int col, int type)
{
   map->getMapTile(row, col)->setTile(type);
}

void Door::setTile(int dRow, int dCol, int type)
{
   map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setTile(type);
}



