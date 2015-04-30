//
//  Staff.cpp
//  Taverna
//
//  Created by Kevin Weber on 3/19/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "Staff.h"

Staff::Staff(String name, Person::Intent intent, String file, Number width, Number height, int level) : Person(name, intent, file, width, height, false) {
	this->level = level;
	setPay(level);
	TavernResources::getInstance()->addStaff(this);
}

void Staff::reset() {
   brain = new FSM(this);
   moved = false;
   isMoving = false;
   steps.clear();
   if (getIntent() == Person::WAITER) {
      this->movePerson((TavernResources::getInstance()->barList.front()->barPos.x-1)*5, 3.5, TavernResources::getInstance()->barList.front()->barPos.z*5);
   }
}

void Staff::setPay(int level)
{
	switch (level) {
	case 1:
		pay = STAFF_LVL1_PAY;
		walkSpeed = STAFF_LVL1_SPEED;
		break;
	case 2:
		pay = STAFF_LVL2_PAY;
		walkSpeed = STAFF_LVL2_SPEED;
		break;
	case 3:
		pay = STAFF_LVL3_PAY;
		walkSpeed = STAFF_LVL3_SPEED;
		break;
	default:
		pay = 0;
		break;
	}
}

int Staff::getPay()
{
	return pay;
}

int Staff::getLevel()
{
	return level;
}

Staff::~Staff() {
   
}