//
//  TavernResources.cpp
//  Taverna
//
//  Created by Bennett Schalich on 2/27/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "TavernResources.h"

TavernResources *TavernResources::tavResInstance = 0;

TavernResources::TavernResources()
{
   meadSellPrice = 6;
	meadBuyPrice = 5;
	wineSellPrice = 8;
	wineBuyPrice = 7;
	aleSellPrice = 10;
	aleBuyPrice = 9;

   tilePrice = 5;
    
	meadAmnt = 25;
	wineAmnt = 30;
	aleAmnt = 35;

	meadAmnt = 20;
	wineAmnt = 20;
	aleAmnt = 10;

	monthMeadSold = 0;
	monthWineSold = 0;
	monthGoldMade = 0;

	Number temp = 0;
	goldTween = new Tween(&temp, Tween::EASE_NONE, temp, 0, 1, false);

	currentGold = gold = 1000;
   capacity = 0;
   maxCapacity = 25;
   reputation = 0;
   happinessRep = 0;
   buildRep = 0;
   currentRep = 1000;
}

TavernResources* TavernResources::getInstance()
{
    if (!tavResInstance)
    {
        tavResInstance = new TavernResources;
    }
    
    return tavResInstance;
}

int TavernResources::getTilePrice()
{
    return tilePrice;
}

void TavernResources::incrementTilePrice()
{
    tilePrice++;
}

void TavernResources::decrementTilePrice()
{
    tilePrice--;
}

void TavernResources::setMeadStockLabel(SceneLabel *label)
{
	this->meadStockLabel = label;
}

void TavernResources::setWineStockLabel(SceneLabel *label) {
	this->wineStockLabel = label;

}

void TavernResources::setSellPrice(Items type, int price)
{
    if (type == MEAD)
        meadSellPrice = price;
    
    else if (type == WINE)
        wineSellPrice = price;
    
    else if (type == ALE)
        aleSellPrice = price;
}

int TavernResources::getSellPrice(Items type)
{
    if (type == MEAD)
        return meadSellPrice;
    
    else if (type == WINE)
        return wineSellPrice;
    
    else if (type == ALE)
        return aleSellPrice;
    
    return -1;
}

void TavernResources::addToSellPrice(Items type, int amnt)
{
    if (type == MEAD)
        meadSellPrice += amnt;
    
    else if (type == WINE)
        wineSellPrice += amnt;
    
    else if (type == ALE)
        aleSellPrice += amnt;
}

void TavernResources::setBuyPrice(Items type, int price)
{
    if (type == MEAD)
        meadBuyPrice = price;
    
    else if (type == WINE)
        wineBuyPrice = price;
    
    else if (type == ALE)
        aleBuyPrice = price;
}

int TavernResources::getBuyPrice(Items type)
{
    if (type == MEAD)
        return meadBuyPrice;
    
    else if (type == WINE)
        return wineBuyPrice;
    
    else if (type == ALE)
        return aleBuyPrice;
    
    return -1;
}

void TavernResources::addToBuyPrice(Items type, int amnt)
{
    if (type == MEAD)
        meadBuyPrice += amnt;
    
    else if (type == WINE)
        wineBuyPrice += amnt;
    
    else if (type == ALE)
        aleBuyPrice += amnt;
}

int TavernResources::getAmnt(Items type)
{
    if (type == MEAD)
        return meadAmnt;
    
    else if (type == WINE)
        return wineAmnt;
    
    else if (type == ALE)
        return aleAmnt;
    
    return -1;
}

void TavernResources::setAmnt(Items type, int amnt)
{
    if (type == MEAD)
	{
        meadAmnt = amnt;
		char* value = new char[5];
		sprintf(value, "%d", this->meadAmnt);
		meadStockLabel->setText(value);
	}
    
    else if (type == WINE)
	{
        wineAmnt = amnt;
		char* value = new char[5];
		sprintf(value, "%d", this->wineAmnt);
		wineStockLabel->setText(value);
	}
    
    else if (type == ALE)
        aleAmnt = amnt;
}

void TavernResources::addToAmnt(Items type, int amnt)
{
    if (type == MEAD)
	{
		monthMeadSold -= amnt;
        meadAmnt += amnt;
		char* value = new char[5];
		sprintf(value, "%d", this->meadAmnt);
		meadStockLabel->setText(value);

		if (meadAmnt < 1)
			dispatchResourcesEvent();
	}
    
    else if (type == WINE)
	{
		monthWineSold -= amnt;
        wineAmnt += amnt;
		char* value = new char[5];
		sprintf(value, "%d", this->wineAmnt);
		wineStockLabel->setText(value);
		
		if (wineAmnt < 1)
			dispatchResourcesEvent();
	}
    
    else if (type == ALE)
        aleAmnt += amnt;
}

int TavernResources::getGold()
{
    return this->gold;
}

void TavernResources::setGold(int gold)
{
    this->gold = gold;
	dispatchResourcesEvent();
}

void TavernResources::addGold(int gold)
{
    this->gold += gold;
	monthGoldMade += gold;

	TweenManager *tweenMan = CoreServices::getInstance()->getTweenManager();
	goldTween->Pause(true);
	tweenMan->removeTween(goldTween);
	goldTween = new Tween(&currentGold, Tween::EASE_OUT_SINE, currentGold, this->gold, 3, false);
	dispatchResourcesEvent();
}

void TavernResources::removeGold(int gold)
{
    this->gold -= gold;
	monthGoldMade -= gold;

	TweenManager *tweenMan = CoreServices::getInstance()->getTweenManager();
	goldTween->Pause(true);
	tweenMan->removeTween(goldTween);
	goldTween = new Tween(&currentGold, Tween::EASE_OUT_SINE, currentGold, this->gold, 2, false);
	dispatchResourcesEvent();
}

void TavernResources::incrementCapacity()
{
   capacity++;
   dispatchResourcesEvent();
}

void TavernResources::decrementCapacity()
{
   capacity--;
   dispatchResourcesEvent();
}

void TavernResources::setCapacity(int cap) {
   capacity = cap;
   dispatchResourcesEvent();
}

int TavernResources::getCapacity()
{
   return capacity;
}

void TavernResources::setMaxCapacity(int cap) {
   maxCapacity = cap;
   dispatchResourcesEvent();
}

void TavernResources::decrementMaxCapacity(int maxCapMinus)
{
    maxCapacity -= maxCapMinus;
	dispatchResourcesEvent();
}

void TavernResources::addToMaxCapacity(int add)
{
   maxCapacity += add;
   dispatchResourcesEvent();
}

int TavernResources::getMaxCapacity()
{
    return maxCapacity;
}

void TavernResources::calcRep()
{
   if (gold < 0)
	   reputation += gold;
   else
	   reputation = 1000 + happinessRep + buildRep;

   dispatchResourcesEvent();
}

void TavernResources::addBuildRep(int addRep)
{
   buildRep += addRep;
   dispatchResourcesEvent();
}

void TavernResources::removeBuildRep(int removeRep)
{
   printf("remove brep:%d\n", buildRep);
   buildRep -= removeRep;
   dispatchResourcesEvent();
   printf("remove A brep:%d\n", buildRep);
}

std::vector<Person*> TavernResources::getPatrons()
{
   return patrons;
}

void TavernResources::addPatron(Person *person)
{
   patrons.push_back(person);
}

std::vector<Person*> TavernResources::getPeople()
{
   return allPeople;
}

void TavernResources::addPerson(Person *person)
{
   allPeople.push_back(person);
}

std::vector<Staff*> TavernResources::getStaff()
{
   return staff;
}

void TavernResources::addStaff(Staff *person)
{
   staff.push_back(person);
}

void TavernResources::removeStaff(Staff *person)
{
	staff.erase(std::remove(staff.begin(), staff.end(), person), staff.end());
}

void TavernResources::changeHappinessRep(int rep)
{
   happinessRep += rep;
}

int TavernResources::getRep()
{
   return reputation;
}

void TavernResources::incrementCurrentRep()
{
   currentRep++;
   dispatchResourcesEvent();
}

void TavernResources::decrementCurrentRep()
{
   currentRep--;
   dispatchResourcesEvent();
}

int TavernResources::getCurrentRep()
{
   return currentRep;
}

void TavernResources::incrementCurrentGold()
{
   currentGold++;
   dispatchResourcesEvent();
}

void TavernResources::decrementCurrentGold()
{
   currentGold--;
   dispatchResourcesEvent();
}

int TavernResources::getCurrentGold()
{
   return currentGold;
}

void TavernResources::resetMonthStats()
{
	monthMeadSold = 0;
	monthWineSold = 0;
	monthGoldMade = 0;
}

int TavernResources::getMonthSold(Items type)
{
	switch (type) {
	case MEAD:
		return monthMeadSold;
		break;
	case WINE:
		return monthWineSold;
		break;
	default:
		return 0;
		break;
	}
}

int TavernResources::getMonthGoldMade()
{
	return monthGoldMade;
}

void TavernResources::setCore(Core *core)
{
	this->core = core;
}

void TavernResources::dispatchResourcesEvent()
{
	core->dispatchEvent(new Event(Event::RESOURCE_CHANGE_EVENT), Event::RESOURCE_CHANGE_EVENT);
}