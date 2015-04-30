#ifndef __Taverna__MapTile__
#define __Taverna__MapTile__

#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "define.h"
#include <string>

using namespace Polycode;

class MapTile {
public:
    MapTile(int tileType, int i, int j, Core *core, CollisionScene *scene, int roomIDs, bool te);
    ~MapTile();
   
   CollisionScene *scene;
   Core *core;
   
    void setType(int type);
    int getType();
   bool checkOccupied();
   void setScenePrimitive(int i, ScenePrimitive *);
   void setMaterial(int i, String mat);
   ScenePrimitive* getScenePrimitive(int i);
   void setTile(int type);
    int getRoomID();
    void setRoomID(int roomID);
    void setTE(bool te);
    bool getTE();
    void setOccupied(bool occ);
   void setObject(String mesh, String mat, Number shadowSize, bool occupy);
   void setPrimitive(ScenePrimitive *prim, String mat, Number shadowSize, bool occupy);
    void removeObject(int row, int col);
   SceneMesh *getObject();
   void raiseWalls();
   void lowerWalls();
   bool mouseOver;
   bool occupied;
   int hasWall;
   
    
private:
    
   ScenePrimitive *tile[3];
   SceneMesh *object;
   ScenePrimitive *objectShadow;
    int tileType;
   int posX;
   int posZ;
   int roomID;
    bool te;
};

#endif
