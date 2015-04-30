//
//  RoomDeleter.h
//  Taverna
//
//  Created by Bennett Schalich on 2/20/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#ifndef DELETER
#define DELETER

#include "PolyCode.h"
#include "define.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"
#include "GameData.h"
#include <list>
#include "RoomNode.h"

class Deleter
{
public:
    Deleter();
    ~Deleter();
    
   bool deleteExpansion(std::list<RoomNode*> *rnList);
    void setPos(int row, int col);
    
private:
    int getID(int row, int col);
    int getType(int row, int col);
    void configureTiles();
   void setTile(int row, int col, String tileMat, int type);
    bool getTE(int row, int col);
    void changeDoors();
    SceneMesh* getObject(int row, int col);
    void removeObject(int row, int col);
    void setMaxCapacity();
    
    void makeTile(int row, int col, bool te);
    void makeInvisTile(int row, int col);
   
   void movePeople(int, int, int, int);
   
   Vector2 pos;
    GameMap *map;
};

#endif