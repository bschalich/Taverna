//
//  Bar.h
//  Taverna
//
//  Created by Kevin Weber on 6/2/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#ifndef __Taverna__Bar__
#define __Taverna__Bar__

#include "Polycode.h"
#include "GameData.h"
#include "MapTile.h"
#include "TavernResources.h"

using namespace Polycode;

class Bar {
public:
   Bar(int i, int j, int xSize, int zSize);
   ~Bar();

   Vector3 barkeepTile;
   Vector3 barPos;
   std::vector<Vector3> patronTiles;

   String getBarDir(Vector3);

private:
   int i;
   int j;
};

#endif /* defined(__Taverna__Bar__) */
