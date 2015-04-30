//
//  Staff.h
//  Taverna
//
//  Created by Kevin Weber on 3/19/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#ifndef __Taverna__Staff__
#define __Taverna__Staff__

#include <iostream>
#include "Person.h"
#include "Polycode.h"
#include "FSM.h"

using namespace Polycode;

class Staff : public Person {
public:
   Staff(String name, Person::Intent intent, String file, Number width, Number height, int level);
   ~Staff();
   
   String type;
   void giveDrink();
   void reset();
   int getPay();
   int getLevel();
   
private:
   int pay;
   int level;

   void setPay(int level);
};

#endif /* defined(__Taverna__Staff__) */
