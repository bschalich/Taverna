#ifndef __Taverna__AStar__
#define __Taverna__AStar__

#include "Polycode.h"
#include "GameMap.h"
#include "Polycode3DPhysics.h"
#include <list>

using namespace Polycode;
using namespace std;

class AStar {
   
public:
   AStar(GameMap *map, int maxSearch, bool allowDiag);
   ~AStar();
   list<Vector3> findPath(int startX, int startZ, int endX, int endY);
   Number getCost(int x, int z, int tx, int tz);
   
   class Node {
      
   public:
      Number cost;
      Number heuristic;
      Number depth;
      Node *parent;
      int x;
      int z;
      
      Node(int x, int z) {
         this->x = x;
         this->z = z;
      }
      
      int setParent(Node *parent) {
         depth = parent->depth + 1;
         this->parent = parent;
         return depth;
      }
      
      
   };
   
private:
   int getType(int x, int z);
   
   list<Node*> closedList;
   list<Node*> openList;
   list<Vector3> steps;
   GameMap *gameMap;
   int maxSearch;
   Node *nodes[DIM][DIM];
   bool allowDiag;
   Number heuristic;
   
protected:
   bool isInOpenList(Node *node);
   bool isInClosedList(Node *node);
   bool checkForValidLocation(int startX, int startY, int curX, int curZ);

};

#endif