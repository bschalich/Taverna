
#include "Dialogue.h"

Dialogue *Dialogue::dialogueInstance = 0;

Dialogue::Dialogue()
{
	thirsty.push_back("I could use a drink");
	thirsty.push_back("I need a drink");
	thirsty.push_back("Lets get drunk!!");

	hungry.push_back("I could use some grub");
	hungry.push_back("I am starving!");
	hungry.push_back("Lets feast!");

	takeOrder.push_back("May I take yee order?");
	takeOrder.push_back("What'll it be?");
	takeOrder.push_back("What ye be wantin?");

	giveOrder.push_back("Here is ye order");
	giveOrder.push_back("Take ye order");

	leave.push_back("I'm out of this dump");
	leave.push_back("I need to go home now");
	leave.push_back("I'll be back!");

	waitorWorking.push_back("Work work work");
	waitorWorking.push_back("Another damn customer");
}

Dialogue* Dialogue::getInstance()
{
    if (!dialogueInstance)
    {
        dialogueInstance = new Dialogue;
    }
    
    return dialogueInstance;
}

String Dialogue::getThirstyDialogue()
{
	return thirsty[rand() % thirsty.size()];
}

String Dialogue::getHungryDialogue()
{
	return hungry[rand() % hungry.size()];
}

String Dialogue::getTakeOrderDialogue()
{
	return takeOrder[rand() % takeOrder.size()];
}

String Dialogue::getGiveOrderDialogue()
{
	return giveOrder[rand() % giveOrder.size()];
}

String Dialogue::getLeaveDialogue()
{
	return leave[rand() % leave.size()];
}

String Dialogue::getWaitorWorkingDialogue()
{
	return waitorWorking[rand() % waitorWorking.size()];
}