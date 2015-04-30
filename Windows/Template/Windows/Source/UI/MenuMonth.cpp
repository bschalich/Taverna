#include "MenuMonth.h"

MenuMonth::MenuMonth() : EventHandler() {
   gameData = GameData::getInstance();
   resources = TavernResources::getInstance();
   isDone = false;

   bg = new MenuImage("Assets/Images/monthBG.png", 900, 500);
   bg->setPosition(-(bg->getWidth() / 2), -(bg->getHeight() / 2), 0);
   gameData->getScene2D()->addChild(bg);

   month = new MenuLabel(gameData->getMonth(), 30, "sans");
   month->setPosition(Vector3((month->getWidth() / 2) + 45,
	   bg->getHeight() - month->getHeight() / 2 - 30, 0));
   bg->addChild(month);

   char* goldString = new char[10];
   sprintf(goldString, "Gold: %d", TavernResources::getInstance()->getGold());
   gold = new MenuLabel(goldString, 30, "sans");
   gold->setPosition(Vector3(bg->getWidth() - (gold->getWidth() / 2) - 45,
	   bg->getHeight() - gold->getHeight() / 2 - 30, 0));
   bg->addChild(gold);

   startButton = new MenuItem(gameData, "Assets/Images/startButton.png", 105, 70);
   startButton->setPosition((bg->getWidth() / 2) - startButton->getWidth() / 2, startButton->getHeight() / 2 + 20, 0);
   startButton->addEventListener(this, UIEvent::CLICK_EVENT);
   bg->addChild(startButton);

   infoButton = new MenuItem(gameData, "Assets/Images/infoTab.png", 105, 70);
   infoButton->setPosition(60, bg->getHeight() - infoButton->getHeight() - 70, 0);
   infoButton->addEventListener(this, UIEvent::CLICK_EVENT);
   bg->addChild(infoButton);

   stockButton = new MenuItem(gameData, "Assets/Images/stockTab.png", 105, 70);
   stockButton->setPosition(infoButton->getPosition().x + stockButton->getWidth() + 20, infoButton->getPosition().y, 0);
   stockButton->addEventListener(this, UIEvent::CLICK_EVENT);
   bg->addChild(stockButton);

   staffButton = new MenuItem(gameData, "Assets/Images/staffTab.png", 105, 70);
   staffButton->setPosition(stockButton->getPosition().x + staffButton->getWidth() + 20, infoButton->getPosition().y, 0);
   staffButton->addEventListener(this, UIEvent::CLICK_EVENT);
   bg->addChild(staffButton);

   buildButton = new MenuItem(gameData, "Assets/Images/buildTab.png", 105, 70);
   buildButton->setPosition(staffButton->getPosition().x + buildButton->getWidth() + 20, infoButton->getPosition().y, 0);
   buildButton->addEventListener(this, UIEvent::CLICK_EVENT);
   bg->addChild(buildButton);

   doneButton = new MenuItem(gameData, "Assets/Images/doneTab.png", 150, 100);
   doneButton->setPosition(-doneButton->getWidth() - 100, GameUI::getInstance()->menubar->getHeight() / 2 - doneButton->getHeight() / 2, 0);
   doneButton->addEventListener(this, UIEvent::CLICK_EVENT);
   //GameUI::getInstance()->menubar->addChild(doneButton);

   createInfo();
   createStock();
   createStaff();
   clear();
   bg->addChild(infoContainer);
}

MenuMonth::~MenuMonth() {
}

void MenuMonth::createStaff() {
	staffContainer = new MenuImage("", 0, 0);
	staffContainer->setPosition(60, infoButton->getPosition().y - infoButton->getHeight() - 70);
	bg->addChild(staffContainer);

	MenuImage *sContainer1 = new MenuImage("", 0, 0);
	staffContainer->addChild(sContainer1);

	MenuImage *sContainer2 = new MenuImage("", 0, 0);
	sContainer2->setPosition(270, 0);
	staffContainer->addChild(sContainer2);

	MenuImage *sContainer3 = new MenuImage("", 0, 0);
	sContainer3->setPosition(540, 0);
	staffContainer->addChild(sContainer3);

	createStaffItem(1, sContainer1);
	createStaffItem(2, sContainer2);
	createStaffItem(3, sContainer3);
}

void MenuMonth::fireStaff(int level)
{

}

void MenuMonth::createStaffItem(int level, MenuImage *parent) {
	String title;
	String file;
	int speed;
	int cost;
	int owned;
	MenuItem *buyButton;
	MenuLabel *ownedLabel;
	
	if (level == 1) {
		title = "Level 1";
		file = "Assets/Sprites/waiterlvl1.png";
		speed = STAFF_LVL1_SPEED;
		cost = STAFF_LVL1_PAY;
		lvl1Buy = new MenuItem(gameData, "Assets/Images/buyButton.png", 117, 50);
		buyButton = lvl1Buy;

		owned = getOwned(1) - 1;
		char *ownedS = new char[10];
		sprintf(ownedS, "Owned: %d", owned);
		ownedLabel = lvl1Owned = new MenuLabel(ownedS, 20, "sans");
	}
	else if (level == 2) {
		title = "Level 2";
		file = "Assets/Sprites/waiterlvl2.png";
		speed = STAFF_LVL2_SPEED;
		cost = STAFF_LVL2_PAY;
		owned = getOwned(2);
		buyButton = new MenuItem(gameData, "Assets/Images/buyButton.png", 117, 50);
		lvl2Buy = buyButton;

		char *ownedS = new char[10];
		sprintf(ownedS, "Owned: %d", owned);
		ownedLabel = lvl2Owned = new MenuLabel(ownedS, 20, "sans");
	}
	else if (level == 3) {
		title = "Level 3";
		file = "Assets/Sprites/waiterlvl3.png";
		speed = STAFF_LVL3_SPEED;
		cost = STAFF_LVL3_PAY;
		owned = getOwned(3);
		buyButton = new MenuItem(gameData, "Assets/Images/buyButton.png", 117, 50);
		lvl3Buy = buyButton;

		char *ownedS = new char[10];
		sprintf(ownedS, "Owned: %d", owned);
		ownedLabel = lvl3Owned = new MenuLabel(ownedS, 20, "sans");
	}

	MenuLabel *lvl1Title = new MenuLabel(title, 30, "sans");
	lvl1Title->setPosition(Vector3(100, 80, 0));
	parent->addChild(lvl1Title);

	MenuSprite *lvl1Image = new MenuSprite(gameData, file, 90, 140);
	lvl1Image->addAnimation("portrait", "7", 1);
    lvl1Image->playAnimation("portrait", 0, false);
	lvl1Image->setScale(1.5, 1.5);
	lvl1Image->setPosition(50, -40, 0);
	parent->addChild(lvl1Image);

	char *speedS = new char[10];
	sprintf(speedS, "Speed: %d", speed);
	MenuLabel *lvl1Speed = new MenuLabel(speedS, 20, "sans");
	lvl1Speed->setPosition(Vector3(lvl1Image->getWidth() + lvl1Speed->getWidth() / 2 + 20, 20, 0));
	parent->addChild(lvl1Speed);

	char *costS = new char[10];
	sprintf(costS, "Cost: %d", cost);
	MenuLabel *lvl1Cost = new MenuLabel(costS, 20, "sans");
	lvl1Cost->setPosition(Vector3(lvl1Image->getWidth() + lvl1Cost->getWidth() / 2 + 20, -10, 0));
	parent->addChild(lvl1Cost);

	ownedLabel->setPosition(Vector3(lvl1Image->getWidth() + ownedLabel->getWidth() / 2 + 20, -40, 0));
	parent->addChild(ownedLabel);

	//buyButton = new MenuItem(gameData, "Assets/Images/buyButton.png", 117, 50);
	buyButton->setPosition(Vector3(lvl1Image->getWidth() + 20, -120, 0));
	buyButton->addEventListener(this, UIEvent::CLICK_EVENT);
	parent->addChild(buyButton);
}

int MenuMonth::getOwned(int level) {
	vector<Staff*> staffList = TavernResources::getInstance()->getStaff();
	int count = 0;

	for (int i = 0; i < staffList.size(); i++)
	{
		if (staffList[i]->getLevel() == level)
			count++;
	}
	return count;
}

void MenuMonth::createStock() {

	stockContainer = new MenuImage("", 0, 0);
	stockContainer->setPosition(80, infoButton->getPosition().y - infoButton->getHeight() - 70);
	bg->addChild(stockContainer);

	ResourceItem *mead = new ResourceItem(GameUI::getInstance(), 0, 0,
		resources->MEAD, "Mead", "Assets/Images/mug.png");
	stockContainer->addChild(mead->transparentBox);

	ResourceItem *wine = new ResourceItem(GameUI::getInstance(),
		mead->transparentBox->getPosition().x + mead->transparentBox->getWidth() + 30,
		0, resources->WINE, "Wine", "Assets/Images/wine.png"); 
	stockContainer->addChild(wine->transparentBox);
}

void MenuMonth::createInfo() {
   
	infoContainer = new MenuImage("", 0, 0);
	infoContainer->setPosition(80, infoButton->getPosition().y - infoButton->getHeight() - 10);
	bg->addChild(infoContainer);

	char* goldString = new char[5];
	sprintf(goldString, "Gold Made: %d", resources->getMonthGoldMade());
	MenuLabel *gold = new MenuLabel(goldString, 30, "sans");
    gold->setPosition(Vector3(gold->getWidth() / 2, 0, 0));
    infoContainer->addChild(gold);

	char* meadString = new char[5];
	sprintf(meadString, "Mead Sold: %d", resources->getMonthSold(resources->MEAD));
	MenuLabel *mead = new MenuLabel(meadString, 30, "sans");
	mead->setPosition(Vector3(mead->getWidth() / 2, gold->getPosition().y - gold->getHeight() - 15, 0));
    infoContainer->addChild(mead);

	char* wineString = new char[5];
	sprintf(wineString, "Wine Sold: %d", resources->getMonthSold(resources->WINE));
	MenuLabel *wine = new MenuLabel(wineString, 30, "sans");
	wine->setPosition(Vector3(wine->getWidth() / 2, mead->getPosition().y - mead->getHeight() - 15, 0));
    infoContainer->addChild(wine);
}

bool MenuMonth::getIsDone() {
	return isDone;
}

void MenuMonth::clear() {
	bg->removeChild(infoContainer);
	bg->removeChild(stockContainer);
	bg->removeChild(staffContainer);
}

void MenuMonth::Update() {
	char* goldString = new char[10];
	sprintf(goldString, "Gold: %d", TavernResources::getInstance()->getCurrentGold());
	gold->setText(goldString);
	gold->setPosition(Vector3(bg->getWidth() - (gold->getWidth() / 2) - 45,
	   bg->getHeight() - gold->getHeight() / 2 - 30, 0));
}

void MenuMonth::handleEvent(Event *e) {
	if(e->getDispatcher() == startButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
            gameData->clickSound->Play(false);
				isDone = true;
				resources->resetMonthStats();
				GameData::getInstance()->getScene2D()->removeEntity(bg);
            break;
			}
		}
	}
	else if(e->getDispatcher() == infoButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
            gameData->clickSound->Play(false);
				clear();
				bg->addChild(infoContainer);
            break;
			}
		}
	}
	else if(e->getDispatcher() == stockButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
            gameData->clickSound->Play(false);
				clear();
				bg->addChild(stockContainer);
            break;
			}
		}
	}
	else if(e->getDispatcher() == staffButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
            gameData->clickSound->Play(false);
				clear();
				bg->addChild(staffContainer);
            break;
			}
		}
	}
	else if(e->getDispatcher() == buildButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
				GameData::getInstance()->getScene2D()->removeEntity(bg);
				GameUI::getInstance()->menubar->addChild(doneButton);
				gameData->clickSound->Play(false);
				GameUI::getInstance()->ticker->setVisible(false);
				GameUI::getInstance()->menubar->visible = true;
				GameUI::getInstance()->openBuildMenu();
            break;
			}
		}
	}
	else if(e->getDispatcher() == doneButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
				GameData::getInstance()->getScene2D()->addEntity(bg);
				GameUI::getInstance()->menubar->removeChild(doneButton);
				gameData->clickSound->Play(false);
				GameUI::getInstance()->ticker->setVisible(true);
				GameUI::getInstance()->menubar->visible = false;
				GameUI::getInstance()->openBuildMenu();
				GameData::getInstance()->setGameMode(GAME_MODE);
            break;
			}
		}
	}
	else if(e->getDispatcher() == lvl1Buy) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			if (staffContainer->visible) {
				gameData->clickSound->Play(false);
				Staff *waiter = new Staff("Walter", Person::WAITER, "waiterlvl1.png", 90, 140, 1);
			    GameData::getInstance()->personTable.insert(make_pair(waiter->getID(), waiter));
			    GameData::getInstance()->getScene3D()->addCollisionChild(waiter);
			    waiter->movePerson(12*5, 3.5, 7*5);
			    waiter->playAnimation("botRight", 7, false);
				waiter->paused = true;

				int owned = getOwned(1) - 1;
				char *ownedS = new char[10];
				sprintf(ownedS, "Owned: %d", owned);
				lvl1Owned->setText(ownedS);
			}
            break;
			}
		}
	}
	else if(e->getDispatcher() == lvl2Buy) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			if (staffContainer->visible) {
				gameData->clickSound->Play(false);
				Staff *waiter = new Staff(GameData::getInstance()->npcNames[rand() % GameData::getInstance()->npcNames.size()], Person::WAITER, "waiterlvl2.png", 90, 140, 2);
			    GameData::getInstance()->personTable.insert(make_pair(waiter->getID(), waiter));
			    GameData::getInstance()->getScene3D()->addCollisionChild(waiter);
			    waiter->movePerson(12*5, 3.5, 7*5);
			    waiter->playAnimation("botRight", 7, false);
				waiter->paused = true;

				int owned = getOwned(2);
				char *ownedS = new char[10];
				sprintf(ownedS, "Owned: %d", owned);
				lvl2Owned->setText(ownedS);
			}
            break;
			}
		}
	}
	else if(e->getDispatcher() == lvl3Buy) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			if (staffContainer->visible) {
				gameData->clickSound->Play(false);
				Staff *waiter = new Staff("Walter", Person::WAITER, "waiterlvl3.png", 90, 140, 3);
			    GameData::getInstance()->personTable.insert(make_pair(waiter->getID(), waiter));
			    GameData::getInstance()->getScene3D()->addCollisionChild(waiter);
			    waiter->movePerson(12*5, 3.5, 7*5);
			    waiter->playAnimation("botRight", 7, false);
				waiter->paused = true;

				int owned = getOwned(3);
				char *ownedS = new char[10];
				sprintf(ownedS, "Owned: %d", owned);
				lvl3Owned->setText(ownedS);
			}
            break;
			}
		}
	}
}