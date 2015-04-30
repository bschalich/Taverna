#ifndef __Taverna__Table__
#define __Taverna__Table__

#include <iostream>
#include "Polycode.h"
#include "GameData.h"
#include "MapTile.h"
#include <vector>
#include <ctime>

using namespace std;
using namespace Polycode;

class Table {
public:
   Table(int i, int j, int id);
   ~Table();
   
   vector<Vector3> openChairs;
   Vector3 waiterTile;
   Vector3 tablePos;
   void reset();
   String getSitDir(Vector3 chairPos);
   int numChairs;
   bool reserved;
   int id;

private:
   int i;
   int j;
};

#endif
