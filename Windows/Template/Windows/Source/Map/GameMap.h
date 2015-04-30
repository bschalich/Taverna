#ifndef __Taverna__GameMap__
#define __Taverna__GameMap__

#include "PolyCode.h"
#include "MapTile.h"
#include "define.h"
#include "Polycode3DPhysics.h"
#include "TavernResources.h"
#include "Table.h"
#include "Bar.h"

using namespace Polycode;

class GameMap {
public:
   GameMap(Core *polycore, CollisionScene *polyScene);
   ~GameMap();

   void initMap();
   MapTile* getMapTile(int i, int j);
    
    int getType(int row, int col);
   bool isOccupied(int row, int col);
   void raiseWalls();
   void lowerWalls();
   void setUpTables();
   void setUpBars();
   
   // global variables
   MapTile *tile[DIM][DIM];
   CollisionScene *scene;
   Core *core;
   
};

#endif