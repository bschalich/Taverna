#ifndef __Taverna__FSM__
#define __Taverna__FSM__

#include "Polycode.h"
#include <list>
#include "Person.h"
#include "FSM.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "TavernResources.h"
#include "TextBubble.h"
#include "Dialogue.h"

using namespace Polycode;
using namespace std;

class FSM {
public:
   FSM(Person* person);
   ~FSM();
   void runActiveState();
   void interruptState();
   
private:
   enum State {WANDER, WANDER1, STOP, WAITORSTOP, MOVE_TO_BAR, ORDER_FROM_BAR, ORDER_FROM_KITCHEN, SIT_AT_TABLE, LEAVE,
   MOVE_TO_KITCHEN, MOVE_TO_PATRON, WAIT_FOR_FOOD, SERVE_PATRON, SIT_AT_DEFINED_TABLE, SELL_TO_BAR};
   
   int tableIndex;
   Vector3 chairPos;
   Person *currentOrderer;
   Person *person;
   Dialogue *dialogue;
   int dir[3];
   bool wanderMoving;
   bool interruptCurrentState;
   void createIntentLists();
   void setNextState();
   void setIntent(int intent);
   void resetTable();
   Timer *timer;
   Timer *waiterTimer;
   State currentState;
   bool runningState;
   TavernResources *tavRes;

   TavernResources::Items drinkList[3];
   
   list<State> stateList;
   list<State> barkeepIntent;
   list<State> wanderIntent;
   list<State> thirstyIntent;
   list<State> sitIntent;
   list<State> stopIntent;
   list<State> leaveIntent;
   list<State> waiterIntent;
   list<State> groupIntent;
   list<State> merchantIntent;
   
   GameData *gameData;

};

#endif