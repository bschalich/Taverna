#include "GameController.h"
#include <iostream>
#include <ctime>

GameController::GameController() {
   spawnTimer = new Timer(false, 20000);
   monthTimer = new Timer(false, 20000);
   groupTimer = new Timer(false, 20000);
   srand((unsigned)time(0));
   isMonthBreak = false;
   gameUI = GameUI::getInstance();
   monthDay = 0;
   Tween *monthDays = new Tween(&monthDay, Tween::EASE_NONE, 1, 31, MONTH_TIME_SECONDS);
   spawnTime = 8;
   
   maxInGroup = 4;
   spawnGroupToggle = false;
   table = NULL;
   tableList = TavernResources::getInstance()->tablesList;
   gameData = GameData::getInstance();
   spawnMC();
   spawnWaiter();
   //spawnWaiter();
}

GameController::~GameController() {
   
}

void GameController::spawnMC() {
   Staff *barKeepMC = new Staff("MC", Person::BARKEEP, "BarKeep.png", 90, 140, 1);
   GameData::getInstance()->personTable.insert(make_pair(barKeepMC->getID(), barKeepMC));
   GameData::getInstance()->getScene3D()->addCollisionChild(barKeepMC);
   barKeepMC->movePerson(TavernResources::getInstance()->barList.front()->barkeepTile.x*5, 3.5, TavernResources::getInstance()->barList.front()->barkeepTile.z*5);
   barKeepMC->playAnimation("botRight", 1, false);
   staff.push_back(barKeepMC);
}

void GameController::spawnWaiter() {
   Staff *waiter = new Staff(GameData::getInstance()->npcNames[rand() % GameData::getInstance()->npcNames.size()], Person::WAITER, "waiter.png", 90, 140, 1);
   GameData::getInstance()->personTable.insert(make_pair(waiter->getID(), waiter));
   GameData::getInstance()->getScene3D()->addCollisionChild(waiter);
   waiter->movePerson((TavernResources::getInstance()->barList.front()->barPos.x-1)*5, 3.5, TavernResources::getInstance()->barList.front()->barPos.z*5);
   waiter->playAnimation("botRight", 1, false);
   staff.push_back(waiter);
}

Person* GameController::spawnPatron(int x, int z, Person::Intent intent) {
   if (TavernResources::getInstance()->getCapacity() < TavernResources::getInstance()->maxCapacity) {
      Person* temp = new Person(GameData::getInstance()->npcNames[rand() % GameData::getInstance()->npcNames.size()], intent, "patron.png", 90, 140, false);
      //temp->setIntent(Person::HUNGRY);
      //temp->interruptIntent();
      GameData::getInstance()->personTable.insert(make_pair(temp->getID(), temp));
      GameData::getInstance()->getScene3D()->addCollisionChild(temp);
      temp->moveTo(x, z);
      patrons.push_back(temp);
      TavernResources::getInstance()->incrementCapacity();
      TavernResources::getInstance()->addPatron(temp);
      return temp;
      gameData->doorOpenSound->Play(false);
   }
   return NULL;
}

void GameController::spawnGroup(Table *table) {
   static vector<Person*> friends;
   static int numInGroup = 0;
   
   if (groupTimer->getElapsedf() > 0.5 && spawnGroupToggle) {
      if (numInGroup == 0) {
         maxInGroup = rand() % 3 + 2;
      }
      if (numInGroup < maxInGroup) {
         Person* newPerson = spawnPatron(20, 1, Person::GROUP);
         if (newPerson != NULL) {
            numInGroup++;
            newPerson->setTable(table);
            friends.push_back(newPerson);
            for (int i = 0; i < friends.size(); i++) {
               friends[i]->friendsList = friends;
            }
         }
      }
      else {
         numInGroup = 0;
         groupList.push_back(friends);
         friends.clear();
         groupTimers.push_back(new Timer(false, 200000));
         spawnGroupToggle = false;
      }
      groupTimer->Reset();
   }
   
   gameData->doorOpenSound->Play(false);
}

void GameController::manageGroups() {
   for (int i = 0; i < groupTimers.size(); i++) {
      if (groupTimers[i]->getElapsedf() > rand() % 30 + 120) {
      
         for (int j = 0; j < groupList[i].size(); j++) {
            if (groupList[i][j]->orderedFood == true) {
               groupList[i][j]->setIntent(Person::LEAVE);
               groupList[i][j]->interruptIntent();
            }
         }
         
         groupTimers[i]->Pause(true);
         groupTimers.erase(groupTimers.begin() + i);
      }
   }
}

void GameController::Update() {
   if (!isMonthBreak) {
		manageGroups();
		GameData::getInstance()->setDay(monthDay);

	   if (spawnGroupToggle == true) {
         spawnGroup(table);
	   }
   
   //FOR NOW if timer >10 seconds then spawnPatron();
   if (spawnTimer->getElapsedf() > spawnTime) {
      spawnTimer->Reset();
		  if (rand() % 20 == 0 && spawnGroupToggle == false) {
			 for (int i = 0; i < tableList.size(); i++) {
				if (TavernResources::getInstance()->tablesList[i]->openChairs.size() == 4 && TavernResources::getInstance()->getMaxCapacity() -TavernResources::getInstance()->getCapacity() >= 4) {
				   spawnGroupToggle = true;
				   table = tableList[i];
				   table->reserved = true;
				   break;
				}
			 }
		  }
		  else {
			 spawnPatron(20, 1, Person::WANDER);
		  }
	   }

	   //Month
	   if (monthTimer->getElapsedf() > MONTH_TIME_SECONDS) {
		   isMonthBreak = true;
		   menuMonth = new MenuMonth();
		   gameUI->menubar->visible = false;
		   gameUI->portrait->visible = false;
         
         if (spawnTime > 4) {
            spawnTime -= 0.5;
         }
         
		   //Remove all people
		   vector<Person*> patronList = TavernResources::getInstance()->getPatrons();

		   for (int i = 0; i < patronList.size(); i++)
		   {
			    Person *curPerson = patronList[i];
				//gameData->firePE->setPosition(curPerson->getPosition().x, 0, curPerson->getPosition().z);
				//gameData->firePE->setLoopParticles(true);
				//gameData->firePE->setLoopParticles(false);
				//patronList.erase(std::remove(patronList.begin(), patronList.end(), curPerson), patronList.end());
	    //patrons.erase(patrons.begin() + i);
	    gameData->getScene3D()->removeEntity(curPerson);
				gameData->getScene3D()->removeEntity(curPerson->shadow);
				gameData->getScene3D()->removeEntity(curPerson->box);
		   }

	 TavernResources::getInstance()->setCapacity(0);
	 TavernResources::getInstance()->openOrders.clear();
	 TavernResources::getInstance()->closedOrders.clear();
         
         //reset tables
         vector<Table*> tableList = TavernResources::getInstance()->tablesList;
      
         for (int i = 0; i < tableList.size(); i++) {
            tableList[i]->reset();
         }
         
		   vector<Staff*> staffList = TavernResources::getInstance()->getStaff();

		   for (int i = 0; i < staffList.size(); i++)
		   {
	    staffList[i]->reset();
			   staffList[i]->paused = true;
		   }
	   }
   }
   else if (menuMonth->getIsDone())
   {
		monthTimer->Reset();
		monthDay = 0;
		Tween *monthDays = new Tween(&monthDay, Tween::EASE_NONE, 1, 31, MONTH_TIME_SECONDS);
		GameData::getInstance()->incrementMonth();
		isMonthBreak = false;
		
		gameUI->menubar->visible = true;
		gameUI->portrait->visible = true;

		vector<Staff*> staffList = TavernResources::getInstance()->getStaff();

		for (int i = 0; i < staffList.size(); i++)
		{
			staffList[i]->paused = false;
		}

		//Pay staff
		//vector<Staff*> staffList = TavernResources::getInstance()->getStaff();

		for (int i = 0; i < staffList.size(); i++)
		{
			Staff *sPerson = staffList[i];
			char* pay = new char[5];
			sprintf(pay, "-$%d", sPerson->getPay());
			new TextBubble(Vector3(((Person*)sPerson)->getPosition().x, 0, ((Person*)sPerson)->getPosition().z), "", pay, 0, (Person*)sPerson);
			TavernResources::getInstance()->addGold(-sPerson->getPay());
		}
   }
   else
   {
	   menuMonth->Update();
   }
}

bool GameController::getIsMonthBreak()
{
	return isMonthBreak;
}