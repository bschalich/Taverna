//
//  TavernResources.h
//  Taverna
//
//  Created by Bennett Schalich on 2/27/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#ifndef __Taverna__Resources__
#define __Taverna__Resources__

class Person;
class Table;
class Staff;
class Bar;

#include "Polycode.h"
#include "define.h"
#include <list>
#include <vector>

using namespace std;
using namespace Polycode;

class TavernResources
{
    
public:
    
    enum Items {EMPTY, MEAD, WINE, ALE};
    
    static TavernResources *getInstance();
    
    void setSellPrice(Items type, int price);
    int getSellPrice(Items type);
	void addToSellPrice(Items type, int amntToAdd);
    void setBuyPrice(Items type, int price);
    int getBuyPrice(Items type);
	void addToBuyPrice(Items type, int amntToAdd);
	int getAmnt(Items type);
    void setAmnt(Items type, int amnt);
    void addToAmnt(Items type, int amntToAdd);
    
    void setGold(int gold);
    int getGold();
    void addGold(int gold);
    void removeGold(int gold);
    void addToMaxCapacity(int add);
    
    void incrementCapacity();
   void decrementCapacity();
   int getCapacity();
   void setCapacity(int cap);
   void setMaxCapacity(int cap);
    int getMaxCapacity();
    void decrementMaxCapacity(int capMinus);
    int getTilePrice();
    void incrementTilePrice();
    void decrementTilePrice();

	void setMeadStockLabel(SceneLabel *label);
	void setWineStockLabel(SceneLabel *label);

	void setCore(Core *core);
   
   void calcRep();
   int getRep();
   
   void addBuildRep(int addRep);
   void removeBuildRep(int removeRep);
   
   void changeHappinessRep(int rep);
   
   void addPatron(Person *person);
   std::vector<Person*> getPatrons();

   void addPerson(Person *person);
   std::vector<Person*> getPeople();

   void addStaff(Staff *person);
   void removeStaff(Staff *person);
   std::vector<Staff*> getStaff();
   
   void incrementCurrentRep();
   void decrementCurrentRep();
   int getCurrentRep();
   
   void incrementCurrentGold();
   void decrementCurrentGold();
   int getCurrentGold();

   void resetMonthStats();
   int getMonthSold(Items type);
   int getMonthGoldMade();
   
   int maxCapacity;
   list<Bar*> barList;
   list<Person*> openOrders;
   vector<Table*> tablesList;
   list<Person*> closedOrders;
   int numTables, buildRep;
   

private:
   TavernResources();
    static TavernResources *tavResInstance;
	void dispatchResourcesEvent();

    //drink amounts
    int meadAmnt, wineAmnt, aleAmnt;

	int monthMeadSold;
	int monthWineSold;
	int monthGoldMade;
    
    //drink prices
    int meadSellPrice, wineSellPrice, aleSellPrice;
    int meadBuyPrice, wineBuyPrice, aleBuyPrice;

    //tile price
    int tilePrice;
    
    int gold, capacity, happinessRep, reputation, currentRep;

	Number currentGold;

	Tween *goldTween;

	SceneLabel *meadStockLabel;
	SceneLabel *wineStockLabel;
   
   //peope lists
   std::vector<Person *> patrons;
   std::vector<Person *> allPeople;
   std::vector<Staff *> staff;
	Core *core;
};
#endif