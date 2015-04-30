#ifndef __Taverna__GameController__
#define __Taverna__GameController__

#include <iostream>
#include "define.h"
#include "Polycode.h"
#include "Person.h"
#include "Staff.h"
#include "GameData.h"
#include "MenuMonth.h"
#include "GameUI.h"
#include "TextBubble.h"

using namespace Polycode;

class GameController {
public:
   GameController();
   ~GameController();
   void Update();

   bool getIsMonthBreak();

private:
   Timer *spawnTimer;
   Timer *monthTimer;
   Timer *groupTimer;
   Person* spawnPatron(int x, int z, Person::Intent);
   void spawnGroup(Table*);
   void spawnMC();
   void spawnWaiter();
   vector<Person*> patrons;
   vector<Staff*> staff;
   int maxCapacity;
   bool isMonthBreak;
   MenuMonth *menuMonth;
   GameUI *gameUI;
   void manageGroups();
   GameData *gameData;
   Number spawnTime;
   
   vector<vector<Person*> > groupList;
   vector<Timer*> groupTimers;
   int maxInGroup;
   bool spawnGroupToggle;
   Table* table;
   vector<Table*> tableList;
   Number monthDay;
};

#endif