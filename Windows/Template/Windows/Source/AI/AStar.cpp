#include "AStar.h"
#include <iostream>
AStar::AStar(GameMap *map, int maxSearch, bool allowDiag) {
   gameMap = map;
   this->maxSearch = maxSearch;
   this->allowDiag = allowDiag;
   this->heuristic = 0;
   
   for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
         nodes[i][j] = new Node(i, j);
	 nodes[i][j]->parent = NULL;
	 nodes[i][j]->cost = 0;
	 nodes[i][j]->heuristic = 0;
      }
   }
}

AStar::~AStar() {
   for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
         delete nodes[i][j];
      }
   }
}

bool compareCost(AStar::Node *n1, AStar::Node *n2) {
   int thisCost = n1->heuristic + n1->cost;
   int otherCost = n2->heuristic + n2->cost;
   
   if (thisCost < otherCost) {
      return true;
   }
   return false;
}

list<Vector3> AStar::findPath(int startX, int startZ, int endX, int endZ) {
   if ((endX < DIM && endZ < DIM) && (endX >= 0 && endZ >= 0)) {
      nodes[startX][startZ]->cost = 0;
      nodes[startX][startZ]->depth = 0;
      nodes[startX][startZ]->parent = NULL;
      closedList.clear();
      openList.clear();
      openList.push_back(nodes[startX][startZ]);
      
      int maxDepth = 0;
      while ((maxDepth < maxSearch) && (openList.size() != 0)) {
         Node *current = openList.front();
         if (current == nodes[endX][endZ]) {
            break;
         }
         
         openList.remove(current);
         closedList.push_back(current);
         
         for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
               if ((i == 0) && (j == 0)) {
                  continue;
               }
               if (!allowDiag) {
                  if ((i != 0) && (j != 0)) {
                     continue;
                  }
               }
               int xp = i + current->x;
               int zp = j + current->z;
               
               if (checkForValidLocation(startX, startZ, xp, zp)) {
                  float nextStepCost = current->cost; //+ map->getCost();
                  Node *neighbor = nodes[xp][zp];
                  //map->pathFinderVisited(xp, zp);
                  
                  if (nextStepCost < neighbor->cost) {
                     openList.remove(neighbor);
                     closedList.remove(neighbor);
                  }
                  
                  if (!isInOpenList(neighbor) && !(isInClosedList(neighbor))) {
                     neighbor->cost = nextStepCost + getCost(current->x, current->z, endX, endZ);
                     neighbor->heuristic = getCost(startX, startZ, endX, endZ);
                     maxDepth = max(maxDepth, neighbor->setParent(current));
                     openList.push_back(neighbor);
                  }
               }
            }
         }
         openList.sort(compareCost);
      }
      
      if (nodes[endX][endZ]->parent != NULL) {
         steps.clear();
         Node *target = nodes[endX][endZ];
	 while (target != NULL && target != nodes[startX][startZ]) {
            steps.push_front(Vector3(target->x, 0, target->z));
            target = target->parent;
         }
      }
      steps.push_front(Vector3(startX, 0, startZ));
   }
   else {
      steps.clear();
   }
   return steps;
}

bool AStar::isInClosedList(Node *neighbor) {
   for (list<Node*>::iterator it = closedList.begin(); it != closedList.end(); ++it) {
      if (neighbor == *it) {
         return true;
      }
   }
   return false;
}

bool AStar::isInOpenList(Node *neighbor) {
   for (list<Node*>::iterator it = openList.begin(); it != openList.end(); ++it) {
      if (neighbor == *it) {
         return true;
      }
   }
   return false;
}

bool AStar::checkForValidLocation(int startX, int startZ, int otherX, int otherZ) {
   bool invalid = otherX < 0 || otherZ < 0 || otherX >= DIM || otherZ >= DIM;
   if (!invalid && (startX != otherX || startZ != otherZ)) {
      invalid = gameMap->isOccupied(otherX, otherZ);
   }
   /*if (abs(startX - otherX) => 1 && abs(startZ - otherZ) > 1) {
      invalid = true;
   }*/
   return !invalid;
}

Number AStar::getCost(int x, int z, int tx, int tz)
{
 
   Number dx;
   Number dz;
   
   /*if (getType(x, z) == LEFT_WALL_BOT || getType(x, z) == LEFT_WALL_TOP || getType(x, z) == RIGHT_WALL_BOT || getType(x, z) == RIGHT_WALL_TOP)
   {
      dx = 0;
      dz = 0;
   }*/
   
   //else
   //{
      dx = tx - x;
      dz = tz - z;
   //}
   
   return sqrt(dx*dx + dz*dz);
}

int AStar::getType(int x, int z)
{
   return gameMap->getMapTile(x, z)->getType();
}



