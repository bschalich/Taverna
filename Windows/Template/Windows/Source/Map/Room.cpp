#include "Room.h"

//centerPos is only for building
Room::Room(int row, int col, Vector2 centerPos, Core *core, CollisionScene *scene, GameMap *map, int ID)
{
    this->row = row;
    this->col = col;
    this->centerPos = centerPos;
    this->core = core;
    this->scene = scene;
    this->map = map;
    
    this->lWall = 0;
    this->lWallBot = 0;
    this->rWall = 0;
    this->rWallBot = 0;
    
    this->ID = ID;
}

Room::~Room()
{
    
}

bool Room::makeRoom(int roomType)
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    String tMat = "GridMaterial";
    
    getBorders();
    getExpansionBorders();
    
    if (viableRoom())
    {
        TavernResources::getInstance()->removeGold(row * col * TavernResources::getInstance()->getTilePrice());
        TavernResources::getInstance()->incrementTilePrice();
       TavernResources::getInstance()->addBuildRep((int)(20 * (double)row * (double)col));
       
        for (int dRow = -rowChange ; dRow <= rowChange; dRow++)
        {
            for (int dCol = -colChange; dCol <= colChange; dCol++)
            {
                if (centerPos.x + dRow > 0 && centerPos.x + dRow < DIM - 1 && centerPos.y + dCol > 0 && centerPos.y + dCol < DIM - 1)
                {
                    if (dRow == -rowChange && dCol == -colChange)
                    {
                        setTile(dRow, dCol, tMat, CORNER_TOP);
                    }
                    
                    else if (dRow == -rowChange && dCol == colChange)
                    {
                        setTile(dRow, dCol, tMat, CORNER_LEFT);
                    }
                    
                    else if (dRow == rowChange && dCol == -colChange)
                    {
                        setTile(dRow, dCol, tMat, CORNER_RIGHT);
                    }
                    
                    else if (dRow == rowChange && dCol == colChange)
                    {
                        setTile(dRow, dCol, tMat, CORNER_BOT);
                    }
                    
                    else if (dRow == -rowChange)
                    {
                        setTile(dRow, dCol, tMat, LEFT_WALL_TOP);
                    }
                    
                    else if (dRow == rowChange)
                    {
                        setTile(dRow, dCol, tMat, LEFT_WALL_BOT);
                    }
                    
                    else if (dCol == -colChange)
                    {
                        setTile(dRow, dCol, tMat, RIGHT_WALL_TOP);
                    }
                    
                    else if (dCol == colChange)
                    {
                        setTile(dRow, dCol, tMat, RIGHT_WALL_BOT);
                    }
                    
                    else
                    {
                        setTile(dRow, dCol, tMat, TILE);
                    }
                    
                    map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setTE(false);
                }
            }
        }
        
        makeDoor();
        placeObjects(roomType);

       return true;
    }
   return false;
}

void Room::makeDoor()
{
   //make doors
   if (whichSideS() == -1)
   {
      if (whichSide() == LEFT_BOT_SIDE)
      {
         setTileDoor(centerPos.x, centerPos.y - (col/2), RIGHT_DOOR_TOP);
         
         if (getType(0, -(col/2 + 1)) == CORNER_BOT)
         {
            printf("\nCORNER_BOT_LEFT_DOOR\n");
             setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), CORNER_BOT_LEFT_DOOR);
         }
         else if (getType(0, -(col/2 + 1)) == CORNER_LEFT)
         {
            printf("\nCORNER_LEFT_LEFT_BOT_DOOR\n");
             setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), CORNER_LEFT_LEFT_BOT_DOOR);
         }
         else
         {
            printf("\nELSE\n");
            setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), LEFT_DOOR_BOT);
         }
         
      }
      
      else if (whichSide() == RIGHT_BOT_SIDE)
      {
         setTileDoor(centerPos.x - (row/2), centerPos.y, LEFT_DOOR_TOP);
         
         printf("\ntype: %d\n", getType(-(row/2 + 1), 0));
         if (getType(-(row/2 + 1), 0) == CORNER_BOT)
         {
            printf("\nCORNER_BOT_RIGHT_DOOR\n");
            setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, CORNER_BOT_RIGHT_DOOR);
         }
         else if (getType(-(row/2 + 1), 0) == CORNER_RIGHT)
         {
            printf("\nCORNER_RIGHT_RIGHT_BOT_DOOR\n");
            setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, CORNER_RIGHT_RIGHT_BOT_DOOR);
         }
         else
         {
            printf("ELSE\n");
            setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, RIGHT_DOOR_BOT);
         }
      }
      
      else if (whichSide() == LEFT_TOP_SIDE)
      {
         setTileDoor(centerPos.x + (row/2), centerPos.y, RIGHT_DOOR_BOT);
         
         if (getType((row/2 + 1), 0) == CORNER_LEFT)
         {
            printf("\nCORNER_LEFT_LEFT_TOP_DOOR\n");
            setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, CORNER_LEFT_LEFT_TOP_DOOR);
         }
         else if (getType((row/2 + 1), 0) == CORNER_TOP)
         {
            printf("\nCORNER_TOP_LEFT_DOOR\n");
            setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, CORNER_TOP_LEFT_DOOR);
         }
         else
         {
            printf("\nELSE\n");
            setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, LEFT_DOOR_TOP);
         }
      }
      
      else if (RIGHT_TOP_SIDE)
      {
         setTileDoor(centerPos.x, centerPos.y + (col/2), LEFT_DOOR_BOT);
         
         if (getType(0, col/2 + 1) == CORNER_TOP)
         {
            printf("\nCORNER_TOP_RIGHT_DOOR\n");
            setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), CORNER_TOP_RIGHT_DOOR);
         }
         else if (getType(0, col/2 + 1) == CORNER_RIGHT)
         {
            printf("\nCORNER_RIGHT_RIGHT_TOP_DOOR\n");
            setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), CORNER_RIGHT_RIGHT_TOP_DOOR);
         }
         else
         {
            printf("\nELSE\n");
            setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), RIGHT_DOOR_TOP);
         }
      }
   }
   
   else
   {
      if (whichSideS() == LEFT_BOT_SIDE)
      {
         setTileDoor(centerPos.x, centerPos.y - (col/2), RIGHT_DOOR_TOP);
         
         if (getType(0, -(col/2 + 1)) == CORNER_BOT)
         {
            printf("\nCORNER_BOT_LEFT_DOOR\n");
            setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), CORNER_BOT_LEFT_DOOR);
         }
         else if (getType(0, -(col/2 + 1)) == CORNER_LEFT)
         {
            printf("\nCORNER_LEFT_LEFT_BOT_DOOR\n");
            setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), CORNER_LEFT_LEFT_BOT_DOOR);
         }
         else
         {
            printf("\nELSE\n");
            setTileDoor(centerPos.x, centerPos.y - (col/2 + 1), LEFT_DOOR_BOT);
         }
      }
      
      else if (whichSideS() == RIGHT_BOT_SIDE)
      {
         setTileDoor(centerPos.x - (row/2), centerPos.y, LEFT_DOOR_TOP);
         
         printf("\ntype: %d\n", getType(-(row/2 + 1), 0));
         if (getType(-(row/2 + 1), 0) == CORNER_BOT)
         {
            printf("\nCORNER_BOT_RIGHT_DOOR\n");
            setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, CORNER_BOT_RIGHT_DOOR);
         }
         else if (getType(-(row/2 + 1), 0) == CORNER_RIGHT)
         {
            printf("\nCORNER_RIGHT_RIGHT_BOT_DOOR\n");
            setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, CORNER_RIGHT_RIGHT_BOT_DOOR);
         }
         else
         {
            printf("ELSE\n");
            setTileDoor(centerPos.x - (row/2 + 1), centerPos.y, RIGHT_DOOR_BOT);
         }
      }
      
      else if (whichSideS() == LEFT_TOP_SIDE)
      {
         setTileDoor(centerPos.x + (row/2), centerPos.y, RIGHT_DOOR_BOT);
         
         if (getType((row/2 + 1), 0) == CORNER_LEFT)
         {
            printf("\nCORNER_LEFT_LEFT_TOP_DOOR\n");
            setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, CORNER_LEFT_LEFT_TOP_DOOR);
         }
         else if (getType((row/2 + 1), 0) == CORNER_TOP)
         {
            printf("\nCORNER_TOP_LEFT_DOOR\n");
            setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, CORNER_TOP_LEFT_DOOR);
         }
         else
         {
            printf("\nELSE\n");
            setTileDoor(centerPos.x + (row/2 + 1), centerPos.y, LEFT_DOOR_TOP);
         }
      }
      
      else if (RIGHT_TOP_SIDE)
      {
         setTileDoor(centerPos.x, centerPos.y + (col/2), LEFT_DOOR_BOT);
         
         if (getType(0, col/2 + 1) == CORNER_TOP)
         {
            printf("\nCORNER_TOP_RIGHT_DOOR\n");
            setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), CORNER_TOP_RIGHT_DOOR);
         }
         else if (getType(0, col/2 + 1) == CORNER_RIGHT)
         {
            printf("\nCORNER_RIGHT_RIGHT_TOP_DOOR\n");
            setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), CORNER_RIGHT_RIGHT_TOP_DOOR);
         }
         else
         {
            printf("\nELSE\n");
            setTileDoor(centerPos.x, centerPos.y + (col/2 + 1), RIGHT_DOOR_TOP);
         }
      }
   }
}

//only places one object in the center of the room for now
void Room::placeObjects(int roomType)
{
    if (roomType == KITCHEN)
    {
        setObject(row/2, col/2, "barrel_01.mesh", "BitgemMaterial", 5, true);
        getObject(row/2, col/2)->setScale(0.04, 0.05, 0.04);
    }
    
    else if (roomType == RESTROOM)
    {
        /*map->getMapTile(centerPos.x, centerPos.y)->setObject("barrel_01.mesh", "BitgemMaterial", 10, true);
        map->getMapTile(centerPos.x, centerPos.y)->getObject()->setScale(0.05*1.4, 0.05*1.5, 0.05*2);*/
    }
    
    else if (roomType == BEDCHAMBER)
    {
       setObject(-(row/2), -(col/2), "candelabra_001_lit.mesh", "BitgemMaterial", 5, true);
       getObject(-(row/2), -(col/2))->setScale(.05, .05, .05);
    }
}

void Room::getExpansionBorders()
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        //printf("type: %d\n", this->getType(m, -nChange - 1));
        if (this->getType(dRow, -colChange - 1) == RIGHT_WALL_BOT || this->getType(dRow, -colChange - 1) == CORNER_LEFT || this->getType(dRow, -colChange - 1) == CORNER_BOT)
        {
            //printf("m: %d\n", m);
            if (getTe(dRow, -colChange - 1))
                rWallBotS++;
        }
    }
    
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        if (this->getType(-rowChange - 1, dCol) == LEFT_WALL_BOT || this->getType(-rowChange - 1, dCol) == CORNER_BOT || this->getType(-rowChange - 1, dCol) == CORNER_RIGHT)
        {
            if (getTe(-rowChange - 1, dCol))
            {
                lWallBotS++;
            }
        }
    }
    
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        if (this->getType(rowChange + 1, dCol) == LEFT_WALL_TOP || this->getType(rowChange + 1, dCol) == CORNER_LEFT || this->getType(rowChange + 1, dCol) == CORNER_TOP)
        {
            if (getTe(rowChange + 1, dCol))
                lWallS++;
        }
    }
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        if (this->getType(dRow, colChange + 1) == RIGHT_WALL_TOP || this->getType(dRow, colChange + 1) == CORNER_TOP || this->getType(dRow, colChange + 1) == CORNER_RIGHT)
        {
            if (getTe(dRow, colChange + 1))
                rWallS++;
        }
    }
    
    printf("lWallS : %d\n", lWallS);
    printf("rWallS: %d\n", rWallS);
    printf("lWallBotS: %d\n", lWallBotS);
    printf("rWallBotS: %d\n", rWallBotS);
}

int Room::whichSide()
{
    if (rWallBot >= row)
    {
        return LEFT_BOT_SIDE;
    }
    
    else if (lWallBot >= col)
    {
        return RIGHT_BOT_SIDE;
    }
    
    else if (lWall >= col)
    {
        return LEFT_TOP_SIDE;
    }
    
    else if (rWall >= row)
    {
        return RIGHT_TOP_SIDE;
    }
    
    else
    {
        return -1;
    }
}

int Room::whichSideS()
{
    if (rWallBotS >= row)
    {
        return LEFT_BOT_SIDE;
    }
    
    else if (lWallBotS >= col)
    {
        return RIGHT_BOT_SIDE;
    }
    
    else if (lWallS >= col)
    {
        return LEFT_TOP_SIDE;
    }
    
    else if (rWallS >= row)
    {
        return RIGHT_TOP_SIDE;
    }
    
    else
    {
        return -1;
    }
}

bool Room::viableBorder()
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

bool Room::enoughSpace()
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        for (int dCol = -colChange; dCol <= colChange; dCol++)
        {
            if (centerPos.x + dRow > 0 && centerPos.x + dRow < DIM - 1 && centerPos.y + dCol > 0 && centerPos.y + dCol < DIM - 1)
            {
                if (getType(dRow, dCol) == INVIS_TILE || getType(dRow, dCol) == MOUSE_OVER_TILE)
                {
                    //do nothing
                }
                
                else
                {
                    return false;
                }
            }
            
            else
            {
                return false;
            }
        }
    }
    
    return true;
}


bool Room::viableRoom()
{
    if (viableBorder() == true && enoughSpace() == true
        && (TavernResources::getInstance()->getGold() - (row * col * TavernResources::getInstance()->getTilePrice())) >= 0)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

void Room::getHandlerBorders()
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    //printf("L\n");
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        //printf("[%.0f][%.0f]\n", centerPos.x + m, centerPos.y + (-nChange - 1));
        if (centerPos.x + dRow < DIM && centerPos.x + dRow >= 0 && centerPos.y + (-colChange - 1) >= 0 && centerPos.y + (-colChange - 1) < DIM)
        {
            //printf("i: %d\n", i++);
            
            //printf("GETHANDLERBORDERS---- type[%.0f][%.0f]: %d\n", centerPos.x + m, centerPos.y + (-nChange - 1), getType(m, -nChange - 1));
            //printf("getMapTile: %d\n", map->getMapTile(m, -nChange - 1));
            if (/*map->getMapTile(m, -nChange - 1) && */(this->getType(dRow, -colChange - 1) == RIGHT_WALL_BOT || this->getType(dRow, -colChange - 1) == CORNER_LEFT || this->getType(dRow, -colChange - 1) == CORNER_BOT))
            {
                //printf("j: %d\n", j++);
                rWallBot++;
            }
        }
    }
    
    //printf("M\n");
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        //printf("[%.0f][%.0f]\n", centerPos.x + (-mChange - 1), centerPos.y + n);
        
        if (centerPos.x + (-rowChange - 1) < DIM && centerPos.x + (-rowChange - 1) >= 0 && centerPos.y + dCol >= 0 && centerPos.y + dCol < DIM)
        {
            if (/*map->getMapTile(-mChange - 1, n) && */(this->getType(-rowChange - 1, dCol) == LEFT_WALL_BOT || this->getType(-rowChange - 1, dCol) == CORNER_BOT || this->getType(-rowChange - 1, dCol) == CORNER_RIGHT))
            {
                lWallBot++;
            }
        }
    }
    
    //printf("N\n");
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        //printf("[%.0f][%.0f]\n", centerPos.x + mChange + 1, centerPos.y + n);
        if (centerPos.x + (rowChange + 1) < DIM && centerPos.x + (rowChange + 1) >= 0 && centerPos.y + dCol >= 0 && centerPos.y + dCol < DIM)
        {
            printf("O\n");
            if (map->getMapTile(rowChange + 1, dCol) && (this->getType(rowChange + 1, dCol) == LEFT_WALL_TOP || this->getType(rowChange + 1, dCol) == CORNER_LEFT || this->getType(rowChange + 1, dCol) == CORNER_TOP))
            {
                lWall++;
            }
        }
    }
    
    //printf("P\n");
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        //printf("[%.0f][%.0f]\n", centerPos.x + m, centerPos.y + (nChange + 1));
        if (centerPos.x + dRow < DIM && centerPos.x + dRow >= 0 && centerPos.y + (colChange + 1) >= 0 && centerPos.y + (colChange + 1) < DIM)
        {
            if (map->getMapTile(dRow, colChange + 1) && (this->getType(dRow, colChange + 1) == RIGHT_WALL_TOP || this->getType(dRow, colChange + 1) == CORNER_TOP || this->getType(dRow, colChange + 1) == CORNER_RIGHT))
            {
                rWall++;
            }
        }
    }
    
    printf("lWall : %d\n", lWall);
    printf("rWall: %d\n", rWall);
    printf("lWallBot: %d\n", lWallBot);
    printf("rWallBot: %d\n", rWallBot);
}

void Room::getBorders()
{
    int rowChange = row / 2;
    int colChange = col / 2;
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        if (this->getType(dRow, -colChange - 1) == RIGHT_WALL_BOT || this->getType(dRow, -colChange - 1) == CORNER_LEFT || this->getType(dRow, -colChange - 1) == CORNER_BOT)
        {
            rWallBot++;
        }
    }
    
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        if (this->getType(-rowChange - 1, dCol) == LEFT_WALL_BOT || this->getType(-rowChange - 1, dCol) == CORNER_BOT || this->getType(-rowChange - 1, dCol) == CORNER_RIGHT)
        {
            lWallBot++;
        }
    }
    
    for (int dCol = -colChange; dCol <= colChange; dCol++)
    {
        if (this->getType(rowChange + 1, dCol) == LEFT_WALL_TOP || this->getType(rowChange + 1, dCol) == CORNER_LEFT || this->getType(rowChange + 1, dCol) == CORNER_TOP)
        {
            lWall++;
        }
    }
    
    for (int dRow = -rowChange; dRow <= rowChange; dRow++)
    {
        if (this->getType(dRow, colChange + 1) == RIGHT_WALL_TOP || this->getType(dRow, colChange + 1) == CORNER_TOP || this->getType(dRow, colChange + 1) == CORNER_RIGHT)
        {
            rWall++;
        }
    }
    
    printf("lWall : %d\n", lWall);
    printf("rWall: %d\n", rWall);
    printf("lWallBot: %d\n", lWallBot);
    printf("rWallBot: %d\n", rWallBot);
}

int Room::getType(int dRow, int dCol)
{
    return map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->getType();
}

int Room::getID(int dRow, int dCol)
{
    return map->getMapTile(dRow, dCol)->getRoomID();
}


void Room::setTile(int dRow, int dCol, String tileMat, int type)
{
    map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setTile(type);
    
    map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setRoomID(ID);
}

void Room::setTileDoor(int row, int col, int type)
{
    map->getMapTile(row, col)->setTile(type);
}

bool Room::getTe(int row, int col)
{
    return map->getMapTile(centerPos.x + row, centerPos.y + col)->getTE();
}

void Room::setZeroWallCounters()
{
    lWall = 0;
    rWall = 0;
    rWallBot = 0;
    lWallBot = 0;
}

void Room::setObject(int dRow, int dCol, String mesh, String mat, Number shadowSize, bool occupy)
{
   map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setObject(mesh, mat, shadowSize, occupy);
}

SceneMesh *Room::getObject(int dRow, int dCol)
{
   return map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->getObject();
}

void Room::setOccupied(int dRow, int dCol, bool occ)
{
   map->getMapTile(centerPos.x + dRow, centerPos.y + dCol)->setOccupied(occ);
}








