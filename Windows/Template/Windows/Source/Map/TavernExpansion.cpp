//
//  Room.cpp
//  Taverna
//
//  Created by Bennett Schalich on 1/22/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "TavernExpansion.h"

//i and j are dimensions
//centerPos is the position of the center tile
TavernExpansion::TavernExpansion(int row, int col, Vector2 centerPos, Core *core, CollisionScene *scene, GameMap *map, int ID)
{
    this->row = row;
    this->col = col;
    this->centerPos = centerPos;
    this->core = core;
    this->scene = scene;
    this->map = map;

	this->lWall = 0;
	this->rWall = 0;
	this->lWallBot = 0;
	this->rWallBot = 0;
    this->ID = ID;
}

TavernExpansion::~TavernExpansion()
{
    
}

//t is for type
bool TavernExpansion::makeExpansion(String tileMat, int t)
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    String tMat = "GridMaterial";
    
    getBorders();
    
    if (this->viableExpansion() == true)
    {
        TavernResources::getInstance()->removeGold(row * col * TavernResources::getInstance()->getTilePrice());
        TavernResources::getInstance()->incrementTilePrice();
        TavernResources::getInstance()->addBuildRep(row * col * 20);
       TavernResources::getInstance()->calcRep();
       
        for (int dRow = -rowChange; dRow <= rowChange; dRow++)
        {
            for (int dCol = -colChange; dCol <= colChange; dCol++)
            {
                if (centerPos.x + dRow > 0 && centerPos.x + dRow < DIM - 1 && centerPos.y + dCol > 0 && centerPos.y + dCol < DIM - 1)
                {
                    setTile(dRow, dCol, tMat, TILE, true);
                    setTE(dRow, dCol, true);
                }
            }
        }
        
        configureTiles(tMat);
        //redoBotWalls();
       return true;
    }
   return false;
}


void TavernExpansion::configureTiles(String tMat)
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    //replace walls with tiles
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        for (int dCol = -colChange; dCol <= colChange; dCol++)
        {
            if (centerPos.x + dRow - 1 >= 0 && centerPos.x + dRow + 1 < DIM && centerPos.y + dCol - 1 >= 0 && centerPos.y + dCol + 1 < DIM)
            {
                //printf("type: %d\n", getType(dRow - 1, dCol));
                if (getType(dRow - 1, dCol) > TILE && getTE(dRow -1, dCol))
                {
                    setTile(dRow -1, dCol, tMat, TILE, false);
                }
                
                if (getType(dRow + 1, dCol) > TILE && getTE(dRow + 1, dCol))
                {
                    setTile(dRow + 1, dCol, tMat, TILE, false);
                }
                
                if (getType(dRow, dCol - 1) > TILE && getTE(dRow, dCol - 1))
                {
                    setTile(dRow, dCol - 1, tMat, TILE, false);
                }
                
                if (getType(dRow, dCol + 1) > TILE && getTE(dRow, dCol + 1))
                {
                    setTile(dRow, dCol + 1, tMat, TILE, false);
                }
                
                /*printf("CONFIG 1: [%.0f][%.0f]--- type: %d TE: %d\n", centerPos.x + dRow, centerPos.y + dCol, getType(dRow, dCol), getTE(dRow, dCol));*/
           }
        }
        
        for (int dRow = -rowChange - 1; dRow <= rowChange + 1; dRow++)
        {
            for (int dCol = -colChange - 1; dCol <= colChange + 1; dCol++)
            {
                if (centerPos.x + dRow - 1 >= 0 && centerPos.x + dRow + 1 < DIM && centerPos.y + dCol - 1 >= 0 && centerPos.y + dCol + 1 < DIM)
                {
                    if (getType(dRow, dCol) == TILE)
                    {
                        if ((getType(dRow - 1, dCol) == INVIS_TILE || !getTE(dRow - 1, dCol)) && (getType(dRow, dCol - 1) == INVIS_TILE || !getTE(dRow, dCol - 1)))
                        {
                            setTile(dRow, dCol, "GridMaterial", CORNER_TOP, false);
                        }
                        
                        else if ((getType(dRow - 1, dCol) == INVIS_TILE || !getTE(dRow - 1, dCol)) && (getType(dRow, dCol + 1) == INVIS_TILE || !getTE(dRow, dCol + 1)))
                        {
                            setTile(dRow, dCol, "GridMaterial", CORNER_LEFT, false);
                        }
                        
                        else if ((getType(dRow + 1, dCol) == INVIS_TILE || !getTE(dRow + 1, dCol)) && (getType(dRow, dCol - 1) == INVIS_TILE || !getTE(dRow, dCol - 1)))
                        {
                            setTile(dRow, dCol, "GridMaterial", CORNER_RIGHT, false);
                        }
                        
                        else if ((getType(dRow + 1, dCol) == INVIS_TILE || !getTE(dRow + 1, dCol)) && (getType(dRow, dCol + 1) == INVIS_TILE || !getTE(dRow, dCol + 1)))
                        {
                            setTile(dRow, dCol, "GridMaterial", CORNER_BOT, false);
                        }
                        
                        else if (getType(dRow - 1, dCol) == INVIS_TILE || !getTE(dRow - 1, dCol))
                        {
                            setTile(dRow, dCol, "GridMaterial", LEFT_WALL_TOP, false);
                        }
                        
                        else if (getType(dRow + 1, dCol) == INVIS_TILE || !getTE(dRow + 1, dCol))
                        {
                            setTile(dRow, dCol, "GridMaterial", LEFT_WALL_BOT, false);
                        }
                        
                        else if (getType(dRow, dCol - 1) == INVIS_TILE || !getTE(dRow, dCol - 1))
                        {
                            setTile(dRow, dCol, "GridMaterial", RIGHT_WALL_TOP, false);
                        }
                        
                        else if (getType(dRow, dCol + 1) == INVIS_TILE || !getTE(dRow, dCol + 1))
                        {
                            setTile(dRow, dCol, "GridMaterial", RIGHT_WALL_BOT, false);
                        }
                        
                        /*printf("CONFIG 2: [%.0f][%.0f]--- type: %d TE: %d\n", centerPos.x + dRow, centerPos.y + dCol, getType(dRow, dCol), getTE(dRow, dCol));*/
                    }
                }
            }
        }
    }
}

bool TavernExpansion::viableExpansion()
{
    if (this->viableBorder() == true && this->enoughSpace() == true
        && (TavernResources::getInstance()->getGold() -  (row * col * TavernResources::getInstance()->getTilePrice())) >= 0)
    {
        
        return true;
    }
    
    else
    {
        return false;
    }
}


int TavernExpansion::whichSide()
{
    if (rWallBot >= row)
    {
        return LEFT_BOT_SIDE;
    }
    
    else if (lWallBot >= col)
    {
        return RIGHT_BOT_SIDE;
    }
    
    else if (lWall >= row)
    {
        return LEFT_TOP_SIDE;
    }
    
    else if (rWall >= col)
    {
        return RIGHT_TOP_SIDE;
    }
    
    else
    {
        return -1;
    }
}

void TavernExpansion::getBorders()
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        if ((centerPos.x + dRow >= 0 && centerPos.x + dRow < DIM && centerPos.y + (-colChange - 1) >= 0 && centerPos.y + (-colChange - 1) < DIM) && (this->getType(dRow, -colChange - 1) == RIGHT_WALL_BOT || this->getType(dRow, -colChange - 1) == CORNER_LEFT || this->getType(dRow, -colChange - 1) == CORNER_BOT))
        {
            //printf("here\n");
            if (getTE(dRow, -colChange - 1) == true)
                rWallBot++;
        }
    }
    
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        if ((centerPos.x + (-rowChange - 1) >= 0 && centerPos.x + (-rowChange - 1) < DIM && centerPos.y + dCol >= 0 && centerPos.y + dCol < DIM) && (this->getType(-rowChange - 1, dCol) == LEFT_WALL_BOT || this->getType(-rowChange - 1, dCol) == CORNER_BOT || this->getType(-rowChange - 1, dCol) == CORNER_RIGHT))
        {
            if (getTE(-rowChange - 1, dCol) == true)
                lWallBot++;
        }
    }
    
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        if ((centerPos.x + rowChange + 1 >= 0 && centerPos.x + rowChange + 1 < DIM && centerPos.y + dCol >= 0 && centerPos.y + dCol < DIM) && (this->getType(rowChange + 1, dCol) == LEFT_WALL_TOP || this->getType(rowChange + 1, dCol) == CORNER_LEFT || this->getType(rowChange + 1, dCol) == CORNER_TOP))
        {
            if (getTE(rowChange + 1, dCol))
                lWall++;
        }
    }
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        if ((centerPos.x + dRow >= 0 && centerPos.x + dRow < DIM && centerPos.y + colChange + 1 < DIM && centerPos.y + colChange + 1 >= 0) && (this->getType(dRow, colChange + 1) == RIGHT_WALL_TOP || this->getType(dRow, colChange + 1) == CORNER_TOP || this->getType(dRow, colChange + 1) == CORNER_RIGHT))
        {
            if (getTE(dRow, colChange + 1))
                rWall++;
        }
    }
    
    printf("lWall : %d\n", lWall);
    printf("rWall: %d\n", rWall);
    printf("lWallBot: %d\n", lWallBot);
    printf("rWallBot: %d\n", rWallBot);
}

bool TavernExpansion::viableBorder()
{
    if (lWall >= col)
        return true;
    
    if (rWall >= row)
        return true;
    
    if (lWallBot >= col)
        return true;
    
    if (rWallBot >= row)
        return true;
    
    return false;
}

bool TavernExpansion::enoughSpace()
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        for (int dCol = -colChange; dCol <= colChange; dCol++)
        {
            if (centerPos.x + dRow < 0 || centerPos.y + dCol < 0 || centerPos.x + dRow >= DIM || centerPos.y + dCol >= DIM)
            {
                return false;
            }

            if (getType(dRow, dCol) == INVIS_TILE || getType(dRow, dCol) == MOUSE_OVER_TILE)
            {
                //do nothing
            }
            
            else
            {
                return false;
            }
            
        }
    }
    
    return true;
}

//te decides whether or not to change the ID of the room. If false don't change the ID.
//You dont want to change the ID if you are altering walls of another TavernExpansion

//TO DO: change (te) to (changeID)

void TavernExpansion::setTile(int dRow, int dCol, String tileMat, int type, bool changeID)
{
    map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setTile(type);
    
    if (changeID)
        map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setRoomID(ID);
}

int TavernExpansion::getRoomID(int row, int col)
{
    return map->getMapTile(centerPos.x + row, centerPos.y + col)->getRoomID();
}


Vector2 TavernExpansion::getDim()
{
    return Vector2(row, col);
}
                                
int TavernExpansion::getType(int m, int n)
{
    return map->getMapTile(centerPos.x + m, centerPos.y + n)->getType();
}

Vector2 TavernExpansion::getPosCenter()
{
    return centerPos;
}

void TavernExpansion::setTE(int row, int col, bool te)
{
    map->getMapTile(centerPos.x + row, centerPos.y + col)->setTE(te);
}

bool TavernExpansion::getTE(int row, int col)
{
    return map->getMapTile(centerPos.x + row, centerPos.y + col)->getTE();
}

bool TavernExpansion::thisGetTE(int row, int col)
{
    return map->getMapTile(row, col)->getTE();
}

void TavernExpansion::setZeroWallCounters()
{
    lWall = 0;
    rWall = 0;
    lWallBot = 0;
    rWallBot = 0;
}