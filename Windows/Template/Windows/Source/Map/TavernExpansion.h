#ifndef __Taverna__TavenraExpansion__
#define __Taverna__TavernaExpansion__

#include "PolyCode.h"
#include "define.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"

class TavernExpansion
{
public:
    TavernExpansion(int row, int col, Vector2 centerPos, Core *core, CollisionScene *scene, GameMap *map, int ID);
    ~TavernExpansion();
    
    Vector2 getDim();
    Vector2 getPosCenter();
   bool makeExpansion(String material, int type);
    bool enoughSpace();
    bool viableBorder();
    bool viableExpansion();
    void getBorders();
    void setZeroWallCounters();
    
    void makeRightWallTop(int m, int n, String tileMat, bool changeID);
    void makeRightWallBot(int m, int n, String tileMat, bool changeID);
    void makeLeftWallTop(int m, int n, String tileMat, bool changeID);
    void makeLeftWallBot(int m, int n, String tileMat, bool changeID);
    void makeTile(int m, int n, String tileMat, bool changeID);
    void makeCornerTop(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1, bool changeID);
    void makeCornerLeft(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1, bool changeID);
    void makeCornerRight(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1, bool changeID);
    void makeCornerRightHere(int row, int col, String tileMat, bool tileInvis0, bool tileInvis1, bool changeID);
    void makeCornerBot(int m, int n, String tileMat, bool tileInvis0, bool tileInvis1, bool changeID);
    
    void setTile(int dRow, int dCol, String tileMat, int Type, bool changeID);
    void configureTiles(String tMat);
    void checkEdges();
    int whichSide();
    int betweenWhat();
    
    int getType(int m, int n);
    void types();
    
    void redoBotWalls();

private:
    int getRoomID(int row, int col);
    void setTE(int row, int col, bool te);
    bool getTE(int row, int col);
    bool thisGetTE(int row, int col);
    
    int row, col;
    Vector2 centerPos;
    Core *core;
    CollisionScene *scene;
    GameMap *map;
    int lWall, rWall, lWallBot, rWallBot;
    int ID;
};

#endif
