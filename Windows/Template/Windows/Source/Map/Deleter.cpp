//
//  RoomDeleter.cpp
//  Taverna
//
//  Created by Bennett Schalich on 2/20/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "Deleter.h"
//Deletes rooms or expansions AND rearranges attached rooms or expansions to fit restrictions and/or rules

Deleter::Deleter()
{
    this->pos = Vector2(-1 , -1);
   this->map = GameData::getInstance()->getGameMap();
}

Deleter::~Deleter()
{
    
}


//Does not work 100% when interacting with Rooms. Try only altering TavernExpansion tiles.
bool Deleter::deleteExpansion(std::list<RoomNode*> *rnList)
{
    int count = 0;
    int id = getID(pos.x, pos.y);
    int maxRow = -1;
    int maxCol = -1;
   int minRow = 100;
   int minCol = 100;
   
    //printf("\n\nDELETE STRUCTURE\n\n");
    
    if (id >= 0)
    {
       for (std::list<RoomNode*>::iterator it = rnList->begin(); it != rnList->end(); it++)
       {
          if ((*it)->ID == id)
          {
             printf("DELETE\n");
             rnList->erase(it);
             break;
          }
       }
       
        for (int row = 0; row < DIM; row++)
        {
            for (int col = 0; col < DIM; col++)
            {
                if (getID(row, col) == id)
                {
                    if (getObject(row, col))
                        removeObject(row, col);
                    
                    count++;
                    makeInvisTile(row, col);
                    map->getMapTile(row, col)->setTE(false);
                    map->getMapTile(row, col)->setOccupied(true);
                   
                   if (maxRow < row)
                      maxRow = row;
                   if (minRow > row)
                      minRow = row;
                   if (maxCol < col)
                      maxCol = col;
                   if (minRow < row)
                      minRow = row;
                }
            }
        }
       
        movePeople(maxRow, minRow, maxCol, minCol);
        configureTiles();
        changeDoors();
        TavernResources::getInstance()->decrementMaxCapacity(count / 9);
        TavernResources::getInstance()->decrementTilePrice();
       //printf("buildrep: %d\n", TavernResources::getInstance()->buildRep);
       TavernResources::getInstance()->removeBuildRep(count * 20);
       //printf("A buildrep: %d\n", TavernResources::getInstance()->buildRep);
       
       return true;
    }
   return false;
}

void Deleter::configureTiles()
{
   
    for (int dRow = pos.x - MAX_DIM; dRow <= pos.x + MAX_DIM; dRow++)
    {
        for (int dCol = pos.y - MAX_DIM; dCol <= pos.y + MAX_DIM; dCol++)
        {
                //add conditionals for boundaries of GameMap
            if (dRow > 0 && dRow + 1 < DIM && dCol > 0 && dCol + 1 < DIM)
            {
                //if (getType(dRow, dCol) != INVIS_TILE)
                  //  printf("[%0f][%0f]--- type: %d TE: %d\n", pos.x + dRow, pos.y + dCol, getType(dRow, dCol), getTE(dRow, dCol));
                //change this so it only check TavernExpansionTiles
                if (getType(dRow, dCol) != INVIS_TILE && (getTE(dRow, dCol) || getID(dRow, dCol) == INITIAL_STRUCTURE))
                {
                    //for each case make sure the corners don't get deleted on TavExps in certain instances. This is done by the !getTE(...) statments
                    if ((dRow - 1 < 0 || getType(dRow - 1, dCol) == INVIS_TILE || !getTE(dRow - 1, dCol)) && (dCol - 1 < 0 || getType(dRow, dCol - 1) == INVIS_TILE || !getTE(dRow, dCol - 1)))
                    {
                        printf("\n\nTOP\n\n");
                        setTile(dRow, dCol, "GridMaterial", CORNER_TOP);
                    }
                    
                    else if ((getType(dRow - 1, dCol) == INVIS_TILE || !getTE(dRow - 1, dCol)) && (getType(dRow, dCol + 1) == INVIS_TILE || !getTE(dRow, dCol + 1)))
                    {
                        setTile(dRow, dCol, "GridMaterial", CORNER_LEFT);
                    }
                    
                    else if ((getType(dRow + 1, dCol) == INVIS_TILE || !getTE(dRow + 1, dCol)) && (getType(dRow, dCol - 1) == INVIS_TILE || !getTE(dRow, dCol - 1)))
                    {
                        setTile(dRow, dCol, "GridMaterial", CORNER_RIGHT);
                    }
                    
                    else if ((getType(dRow + 1, dCol) == INVIS_TILE || !getTE(dRow + 1, dCol)) && (getType(dRow, dCol + 1) == INVIS_TILE || !getTE(dRow, dCol + 1)))
                    {
                        setTile(dRow, dCol, "GridMaterial", CORNER_BOT);
                    }
                    
                    else if (getType(dRow - 1, dCol) == INVIS_TILE)
                    {
                        setTile(dRow, dCol, "GridMaterial", LEFT_WALL_TOP);
                    }
                    
                    else if (getType(dRow + 1, dCol) == INVIS_TILE)
                    {
                        setTile(dRow, dCol, "GridMaterial", LEFT_WALL_BOT);
                    }
                    
                    else if (getType(dRow, dCol - 1) == INVIS_TILE)
                    {
                        setTile(dRow, dCol, "GridMaterial", RIGHT_WALL_TOP);
                    }
                    
                    else if (getType(dRow, dCol + 1) == INVIS_TILE)
                    {
                        setTile(dRow, dCol, "GridMaterial", RIGHT_WALL_BOT);
                    }
                }
            }
        }
    }
}

//makes doors wall/corner tiles if there is not corresponding door tile on a bordering wall.
//REVISE FOR CORNER TILES
void Deleter::changeDoors()
{
    for (int row = 1; row < DIM - 1; row ++)
    {
        for (int col = 1; col < DIM - 1; col++)
        {
            if (getType(row, col) == LEFT_DOOR_TOP && (getType(row - 1, col) != RIGHT_DOOR_BOT && getType(row - 1, col) != CORNER_BOT_RIGHT_DOOR && getType(row - 1, col) != CORNER_RIGHT_RIGHT_BOT_DOOR))
            {
               setTile(row, col, "GridMaterial", LEFT_WALL_TOP);
            }
            
            else if (getType(row, col) == RIGHT_DOOR_BOT && (getType(row + 1, col) != LEFT_DOOR_TOP && getType(row + 1, col) != CORNER_LEFT_LEFT_TOP_DOOR && getType(row + 1, col) != CORNER_TOP_LEFT_DOOR))
            {
               setTile(row, col, "GridMaterial", LEFT_WALL_BOT);
            }
            
            else if (getType(row, col) == LEFT_DOOR_BOT && (getType(row, col + 1) != RIGHT_DOOR_TOP && getType(row, col + 1) != CORNER_TOP_RIGHT_DOOR && getType(row, col + 1) != CORNER_RIGHT_RIGHT_TOP_DOOR))
            {
               setTile(row, col, "GridMaterial", RIGHT_WALL_BOT);
            }
            
            else if (getType(row, col) == RIGHT_DOOR_TOP && (getType(row, col - 1) != LEFT_DOOR_BOT && getType(row, col -1) != CORNER_LEFT_LEFT_BOT_DOOR && getType(row, col - 1) != CORNER_BOT_LEFT_DOOR))
            {
               setTile(row, col, "GridMaterial", RIGHT_WALL_TOP);
            }
           
           else if ((getType(row, col) == CORNER_BOT_LEFT_DOOR && getType(row, col + 1) != RIGHT_DOOR_TOP) || (getType(row, col) == CORNER_BOT_RIGHT_DOOR && getType(row + 1, col) != LEFT_DOOR_TOP))
           {
              setTile(row, col, "GridMaterial", CORNER_BOT);
           }
           
           else if ((getType(row, col) == CORNER_LEFT_LEFT_BOT_DOOR && getType(row, col + 1) != RIGHT_DOOR_TOP) || (getType(row, col) == CORNER_LEFT_LEFT_TOP_DOOR && getType(row - 1, col) != RIGHT_DOOR_BOT))
           {
              setTile(row, col, "GridMaterial", CORNER_LEFT);
           }
           
           else if ((getType(row, col) == CORNER_TOP_LEFT_DOOR && getType(row - 1, col) != RIGHT_DOOR_BOT) || (getType(row, col) == CORNER_TOP_RIGHT_DOOR && getType(row, col - 1) != LEFT_DOOR_BOT))
           {
              setTile(row, col, "GridMaterial", CORNER_TOP);
           }
           
           else if ((getType(row, col) == CORNER_RIGHT_RIGHT_TOP_DOOR && getType(row, col - 1) != LEFT_DOOR_BOT) || (getType(row, col) == CORNER_RIGHT_RIGHT_BOT_DOOR && getType(row + 1, col) != LEFT_DOOR_TOP))
           {
              setTile(row, col, "GridMaterial", CORNER_RIGHT);
           }
        }
    }
}

void Deleter::movePeople(int maxRow, int minRow, int maxCol, int minCol)
{
   std::list<Person *> patrons;
   
   /*for (std::iterator<Person*> it = patrons.begin(); it != patrons.end(); it++)
   {
      if ((*it)->get)
   }*/
}

void Deleter::setTile(int row, int col, String tilMat, int type)
{
   map->getMapTile(row, col)->setTile(type);
}

void Deleter::makeInvisTile(int row, int col)
{
   map->getMapTile(row, col)->setTile(INVIS_TILE);
   map->getMapTile(row, col)->setRoomID(NOTHING);
}

int Deleter::getID(int row, int col)
{
    return map->getMapTile(row, col)->getRoomID();
}

int Deleter::getType(int row, int col)
{
    return map->getMapTile(row, col)->getType();
}

void Deleter::setPos(int row, int col)
{
    pos = Vector2(row, col);
}

bool Deleter::getTE(int row, int col)
{
    return map->getMapTile(row, col)->getTE();
}

SceneMesh* Deleter::getObject(int row, int col)
{
    return map->getMapTile(row, col)->getObject();
}

void Deleter::removeObject(int row, int col)
{
    map->getMapTile(row, col)->removeObject(row, col);
}






