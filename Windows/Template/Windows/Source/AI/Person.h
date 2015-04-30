#ifndef __Taverna__Person__
#define __Taverna__Person__

class TavernResources;
class FSM;
class AStar;

#include "Polycode.h"
#include <list>
#include "AStar.h"
#include <iostream>
#include "GameData.h"
#include "TavernResources.h"
#include "MenuImage.h"
#include <ctime>

using namespace Polycode;
using namespace std;

class Box : public ScenePrimitive {
public:
   Box(int id, int type, Number x, Number y, Number z) : ScenePrimitive(type, x, y, z) {
      this->id = id;
   }
   ~Box() {
      
   };

   int id;
};

class Person : public SceneSprite {
public:
   enum Intent {EMPTY, WANDER, THIRSTY, HUNGRY, BARKEEP, LEAVE, WAITER, GROUP};
   Person(String name, Intent intent, String file, Number width, Number height, bool merchant);
   ~Person();
   
   bool isMoving;
   
   bool moveTo(int x, int z);
   Number attack(Person opponent);
   void idle();
   void Update();
   int getIntent();
   void setIntent(Intent i);
   String getFileName();
   int getID();
   int getHealth();
   int getLevel();
   String getName();
   MapTile *getTileOn();
   void interruptIntent();
   bool hasDrink();
   void giveDrink(TavernResources::Items dr);
   void findIntent();
   
   void setHunger(int h);
   int getHunger();
   void setThirst(int t);
   int getThirst();
   void movePerson(Number x, Number y, Number z);
   int getMaxPurchase();
   int getHappiness();
   void calcHappiness();
   void lowerThirst(int val);
   void setTable(Table*);
   Table* getTable();
   int getFun();
   void addFun(int addFun);
   void removeFun(int removeFun);
   int getAnger();
   void addAnger(int addAnger);
   void removeAnger(int removeAnger);
   void setDir(String newDir);
   bool getMerchant();
   
   vector<Person*> friendsList;


   bool orderedFood;
   int currentTable;
   Number walkSpeed;

   ScenePrimitive *shadow;
   ScenePrimitive *box;
   bool isHighlighted;

   bool paused;
   
protected:
   bool moved, takeNextStep, enteringTavern;

   int id;
   String name;
   int health;
   int level;
   int hunger;
   int thirst;
   int fun;
   int anger;
   String fileName;
   Timer *moveTimer;
   Timer *leaveTimer;
   Timer *repTimer;
   list<Vector3> steps;
   AStar *pathfinder;
   Core *core;
   CollisionScene *scene;
   FSM *brain;
   GameMap *map;
   Table *table;
   
   Vector3 st;
   Vector3 dir;
   Intent intent;
   Vector3 dest;
   TavernResources::Items drink;
   int maxPurchase;
   int happiness;
   bool merchant;
   
   //MenuLabel *textBubble;
   
   void getNextDir();
   void useStep();
   bool isOnDest();
   
};

#endif