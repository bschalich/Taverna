#ifndef __Taverna__Room__
#define __Taverna__Room__

#include "PolyCode.h"
#include "define.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"
#include "RoomNode.h"
#include <list>

class Room
{
public:
    Room(int row, int col, Vector2 centerPos, Core *core, CollisionScene *scene, GameMap *map, int ID);
    ~Room();
    
   bool makeRoom(int type);
    bool enoughSpace();
    void getBorders();
    void getHandlerBorders();
    bool viableBorder();
    bool viableRoom();
    void setZeroWallCounters();

private:
    Vector2 taperRow(int rowChange);
    Vector2 taperCol(int colChange);
    void changeCenterPos();
    
    int whichSide();
    int betweenWhat();
    int getType(int row, int col);
    void getExpansionBorders();
    int getID(int dRow, int dCol);
    void setTileDoor(int row, int col, int type);
    bool getTe(int row, int col);
    int whichSideS();
    
    void setTile(int dRow, int dCol, String tileMat, int type);
    void makeLeftWallBorder(int m, int n, String tileMat);
    void makeRightWallBorder(int m, int n, String tileMat);
    void makeLeftWallBotBorder(int m, int n, String tileMat);
    void makeRightWallBotBorder(int m, int n, String tileMat);
    void makeRightWallTop(int m, int n, String tileMat);
    void makeRightWallBot(int m, int n, String tileMat);
    void makeLeftWallTop(int m, int n, String tileMat);
    void makeLeftWallBot(int m, int n, String tileMat);
    void makeTile(int m, int n, String tileMat);
    void makeCornerTop(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1);
    void makeCornerLeft(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1);
    void makeCornerRight(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1);
    void makeCornerBot(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1);
    
    void placeObjects(int roomType);
    void makeDoor();
   
   void setObject(int dRow, int dCol, String mesh, String mat, Number shadowSize, bool occupy);
   SceneMesh *getObject(int dRow, int dCol);
   
   void setOccupied(int dRow, int dCol, bool occ);
   
    int ID;
    int row, col, type;
    Vector2 centerPos;
    Core *core;
    CollisionScene *scene;
    GameMap *map;
    int lWall, rWall, lWallBot, rWallBot;
    int lWallS, rWallS, lWallBotS, rWallBotS;
};

#endif
