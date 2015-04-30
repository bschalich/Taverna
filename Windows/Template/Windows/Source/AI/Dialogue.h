#ifndef __Dialogue__
#define __Dialogue__

#include "Polycode.h"
#include "define.h"
#include "TextBubble.h"
#include <list>
#include <vector>

using namespace Polycode;

class Dialogue {
public:
   ~Dialogue();

   static Dialogue* getInstance();

   String getThirstyDialogue();
   String getHungryDialogue();
   String getTakeOrderDialogue();
   String getGiveOrderDialogue();
   String getLeaveDialogue();
   String getWaitorWorkingDialogue();

private:
	Dialogue();

	static Dialogue *dialogueInstance;
	std::vector<String> thirsty;
	std::vector<String> hungry;
	std::vector<String> takeOrder;
	std::vector<String> giveOrder;
	std::vector<String> leave;
	std::vector<String> waitorWorking;
};

#endif