#include "GameUI.h"

GameUI *GameUI::gameUIInstance = 0;

GameUI::GameUI() : EventHandler() {
   gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   scene3D = gameData->getScene3D();
   toggle = false;
   moveMenu = false;
   menuToggle = false;
   menuMode = NONE;
   testTimer = new Timer(false, 5000);
   
   resources = TavernResources::getInstance();
   core->addEventListener(this, Event::RESOURCE_CHANGE_EVENT);

   buildUI();
   createBuildMenu();

   gold750 = false;

   //Keyboard shortcut
   core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

GameUI::~GameUI() {
}

GameUI* GameUI::getInstance()
{
	if (!gameUIInstance)
	{
		gameUIInstance = new GameUI();
	}

	return gameUIInstance;
}

void GameUI::buildUI() {
	//Main UI
   portrait = new MenuImage("Assets/Images/portrait.png", 300, 200);
   portrait->setPosition(-640, -360, 0);
   portrait->setPositions(-640, -360);
   menubar = new MenuImage("Assets/Images/menubar.png", 990, 275);
   menubar->setPosition(-340, -635, 0);
   menubar->setPositions(-340, -635);
   scene2D->addChild(menubar);
   scene2D->addChild(portrait);

   //Ticker *ticker = new Ticker(menubar);
   //resources->setTicker(ticker);
   buildTicker();
   buildBarInfo();

   //setPortraitPerson(new Person("John Terrowin", false, "patron.png", 90, 140));

   //Icons
   /*buildIcon = new MenuItem(gameData, "Assets/Images/buildIcon.png", 30, 30);
   buildIcon->setPosition(portrait->getWidth() - 30, 60, 0);
   buildIcon->setPositions(0, 0);
   buildIcon->addEventListener(this, UIEvent::CLICK_EVENT);
   portrait->addChild(buildIcon); */

   /*staffIcon = new MenuItem(gameData, "Assets/Images/staffIcon.png", 30, 30);
   staffIcon->setPosition(portrait->getWidth() - 30, 0, 0);
   staffIcon->setPositions(0, 0);
   staffIcon->addEventListener(this, UIEvent::CLICK_EVENT);
   portrait->addChild(staffIcon); */

   resourcesIcon = new MenuItem(gameData, "Assets/Images/resourcesIcon.png", 30, 30);
   resourcesIcon->setPosition(portrait->getWidth() - 30, 30, 0);
   resourcesIcon->setPositions(0, 0);
   resourcesIcon->addEventListener(this, UIEvent::CLICK_EVENT);
   portrait->addChild(resourcesIcon);
}

void GameUI::buildBarInfo()
{
	//Container
   barInfoBox = new MenuImage("Assets/Images/barInfoBox.png", 290, 100);
   barInfoBox->setPosition(menubar->getWidth() - barInfoBox->getWidth() - 10,
	   menubar->getHeight());
   menubar->addChild(barInfoBox);

   //Gold
   char* goldString = new char[10];
   sprintf(goldString, "%d", resources->getGold());
   gold = new SceneLabel(String("Gold: ") + goldString, 20, "sans");
   barInfoBox->addChild(gold);
      gold->depthTest = false;
   gold->depthWrite = false;
   gold->visible = true;
      gold->color = new Color(1, 1, 1, 250);
   gold->setPosition(20 + gold->getWidth() / 2, barInfoBox->getHeight() - 20);

   //Rep
   char* repString = new char[10];
   sprintf(repString, "%d", TavernResources::getInstance()->getRep());
   rep = new SceneLabel(String("Rep: ") + repString, 20, "sans");
   barInfoBox->addChild(rep);
   rep->setPosition(15 + rep->getWidth() / 2 + barInfoBox->getWidth() / 2, barInfoBox->getHeight() - 20);
   rep->depthTest = false;
   rep->depthWrite = false;
   rep->visible = true;
   rep->color = new Color(1, 1, 1, 250);

   //Capacity
   	char* curCap = new char[5];
	sprintf(curCap, "%d", resources->getCapacity());

	char* maxCap = new char[5];
	sprintf(maxCap, "%d", resources->maxCapacity);

	capacity = new SceneLabel(String("Capacity: ") + curCap + "/" + maxCap, 20, "sans");
	barInfoBox->addChild(capacity);
	capacity->visible = true;
	capacity->depthTest = false;
	capacity->depthWrite = false;
	capacity->color = new Color(0, 0, 0, 255);
	capacity->setPosition(capacity->getWidth() / 2 + 20, barInfoBox->getHeight() - 50);

	month = new SceneLabel(String("Date: ") + gameData->getMonth(), 20, "sans");
	barInfoBox->addChild(month);
	month->visible = true;
	month->depthTest = false;
	month->depthWrite = false;
	month->color = new Color(0, 0, 0, 255);
	month->setPosition(month->getWidth() / 2 + 20, barInfoBox->getHeight() - 80);

	day = new SceneLabel(String("") + gameData->getDay(), 20, "sans");
	barInfoBox->addChild(day);
	day->visible = true;
	day->depthTest = false;
	day->depthWrite = false;
	day->color = new Color(0, 0, 0, 255);
	day->setPosition( /*month->getPosition().x + month->getWidth() + day->getWidth() */0, barInfoBox->getHeight() - 80);

}

void GameUI::handleEvent(Event *e) {
   
	/*if(e->getDispatcher() == buildIcon) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
				openBuildMenu();
            break;
			}
		}
	}*/
	if(e->getDispatcher() == resourcesIcon) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
				gameData->clickSound->Play(false);
				openResourcesMenu();
            break;
			}
		}
	}
	/*else if(e->getDispatcher() == staffIcon) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
				openStaffMenu();
            break;
			}
		}
	}*/
	else if(e->getDispatcher() == fire) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
				gameData->clickSound->Play(false);
				gameData->firePE->setPosition(curPerson->getPosition().x, 0, curPerson->getPosition().z);
				gameData->firePE->setLoopParticles(true);
				gameData->firePE->setLoopParticles(false);
				TavernResources::getInstance()->removeStaff((Staff*)curPerson);
				//gameData->getScene3D()->removeEntity(curPerson);
				delete curPerson;
	    setPortraitPerson(NULL);
            break;
			}
		}
	}
	else {
		switch (e->getEventCode()) {
			case Event::RESOURCE_CHANGE_EVENT:
				char* resource = new char[10];
				char* resource2 = new char[10];

				//update gold
				/*sprintf(resource, "%d", resources->getCurrentGold());
				gold->setText(String("Gold: ") + resource); // = new SceneLabel(String("Gold: ") + resource, 20, "sans");
				gold->setPosition(20 + gold->getWidth() / 2, barInfoBox->getHeight() - 20);
				*/
				//update capacity
				sprintf(resource, "%d", resources->getCapacity());
				sprintf(resource2, "%d", resources->getMaxCapacity());
				capacity->setText(String("Capacity: ") + resource + "/" + resource2);
				capacity->setPosition(capacity->getWidth() / 2 + 20, barInfoBox->getHeight() - 50);

				//update reputation
				sprintf(resource, "%d", resources->getCurrentRep());
				rep->setText(String("Rep: ") + resource);
				rep->setPosition(15 + rep->getWidth() / 2 + barInfoBox->getWidth() / 2, barInfoBox->getHeight() - 20);

				month->setText(String("Date: ") + gameData->getMonth());
				month->setPosition(month->getWidth() / 2 + 20, barInfoBox->getHeight() - 80);
				
				day->setText(gameData->getDayString());
				day->setPositionX(month->getPosition().x + month->getWidth() / 2 + day->getWidth());
			break;
		}
	}
   
	InputEvent *inputEvent = (InputEvent*)e;
	if(e->getDispatcher() == core->getInput()) {
		switch(e->getEventCode()) {
         case InputEvent::EVENT_KEYDOWN:
            switch (inputEvent->keyCode()) {
				case KEY_d:
				   if (gameData->getGameMode() == DELETE_MODE) {
					   gameData->setGameMode(GAME_MODE);
				   }
				   else {
					   gameData->setGameMode(DELETE_MODE);
				   }
                   break;
			   case KEY_r:
				   openResourcesMenu();
                   break;
            }
		}
	}
}

void GameUI::buildTicker()
{
	ticker  = new Ticker(menubar);
}

void GameUI::setPortraitPerson(Person *person)
{
	portrait->removeChild(sprite);
	portrait->removeChild(name);
	portrait->removeChild(level);
	portrait->removeChild(health);
	portrait->removeChild(fire);
    portrait->removeChild(happiness);
    portrait->removeChild(thirst);
    portrait->removeChild(hunger);
    portrait->removeChild(maxPurchase);

	if (person != NULL)
	{
		curPerson = person;

	   sprite = new MenuSprite(gameData, person->getFileName(), person->getWidth(), person->getHeight());
	   sprite->setPosition(75, 90, 0);
	   sprite->setScale(1.3, 1.3);
	   sprite->addAnimation("portrait", "7", 1);
	   sprite->playAnimation("portrait", 0, false);
	   portrait->addChild(sprite);

   
	   name = new SceneLabel(String("Name: ") + person->getName(), 16, "sans");
	   name->setPosition(120 + name->getWidth() / 2, 170, 0);
	   name->color = new Color(0, 0, 0, 255);
	   name->depthTest = false;
	   name->depthWrite = false;
	   portrait->addChild(name);

   
	   char* levelString = new char[2];
	   sprintf(levelString, "%d", person->getLevel());
	   level = new SceneLabel(String("Level: ") + levelString, 16, "sans");
	   level->setPosition(120 + level->getWidth() / 2, 150, 0);
	   level->color = new Color(0, 0, 0, 255);
	   level->depthTest = false;
	   level->depthWrite = false;
	   portrait->addChild(level);

   
	   char* healthString = new char[4];
	   sprintf(healthString, "%d", person->getHealth());
	   health = new SceneLabel(String("Health: ") + healthString, 16, "sans");
	   health->setPosition(120 + health->getWidth() / 2, 130, 0);
	   health->color = new Color(0, 0, 0, 255);
	   health->depthTest = false;
	   health->depthWrite = false;
	   portrait->addChild(health);

   
		if (dynamic_cast<Staff*>(person)) {
			fire = new MenuItem(gameData, "Assets/Images/fireButton.png", 75, 50);
			fire->setPosition(120, 30, 0);
			fire->addEventListener(this, UIEvent::CLICK_EVENT);
			portrait->addChild(fire);
		}
		else {
		   char* happinessString = new char[4];
		   sprintf(happinessString, "%d", person->getHappiness());
		   happiness = new SceneLabel(String("Happiness: ") + happinessString, 16, "sans");
		   happiness->setPosition(120 + happiness->getWidth() / 2, 110, 0);
		   happiness->color = new Color(0, 0, 0, 255);
		   happiness->depthTest = false;
		   happiness->depthWrite = false;
		   portrait->addChild(happiness);
   
		   char* thirstString = new char[4];
		   sprintf(thirstString, "%d", person->getThirst());
		   thirst = new SceneLabel(String("Thirst: ") + thirstString, 16, "sans");
		   thirst->setPosition(120 + thirst->getWidth() / 2, 90, 0);
		   thirst->color = new Color(0, 0, 0, 255);
		   thirst->depthTest = false;
		   thirst->depthWrite = false;
		   portrait->addChild(thirst);

		   char* hungerString = new char[4];
		   sprintf(hungerString, "%d", person->getHunger());
		   hunger = new SceneLabel(String("Hunger: ") + hungerString, 16, "sans");
		   hunger->setPosition(120 + hunger->getWidth() / 2, 70, 0);
		   hunger->color = new Color(0, 0, 0, 255);
		   hunger->depthTest = false;
		   hunger->depthWrite = false;
		   portrait->addChild(hunger);

		   char* maxPString = new char[4];
		   sprintf(maxPString, "%d", person->getMaxPurchase());
		   maxPurchase = new SceneLabel(String("Max Purchase: ") + maxPString, 16, "sans");
		   maxPurchase->setPosition(120 + maxPurchase->getWidth() / 2, 50, 0);
		   maxPurchase->color = new Color(0, 0, 0, 255);
		   maxPurchase->depthTest = false;
		   maxPurchase->depthWrite = false;
		   portrait->addChild(maxPurchase);
		}
	}
}

void GameUI::openBuildMenu()
{
	if (menubar->isStationary()) {
		if (menuMode == NONE) {
			menubar->moveFromCurrent(0, 240, 1000);
		}
		if (menuMode != BUILD) {
			setActiveMenu(BUILD);
		}
		else {
			deactivateMenu();
			gameData->getGameMap()->raiseWalls();
		}
	}
}

void GameUI::openResourcesMenu()
{
	if (menubar->isStationary()) {
		if (menuMode == NONE) {
			menubar->moveFromCurrent(0, 240, 1000);
		}
		if (menuMode != RESOURCES) {
			setActiveMenu(RESOURCES);
		}
		else {
			deactivateMenu();
		}
	}
}

void GameUI::openPatronMenu()
{
	if (menubar->isStationary()) {
		if (menuMode == NONE) {
			menubar->moveFromCurrent(0, 240, 1000);
		}
		if (menuMode != PATRON) {
			setActiveMenu(PATRON);
		}
		else {
			deactivateMenu();
		}
	}
}

void GameUI::openStaffMenu()
{
	if (menubar->isStationary()) {
		if (menuMode == NONE) {
			menubar->moveFromCurrent(0, 240, 1000);
		}
		if (menuMode != STAFF) {
			setActiveMenu(STAFF);
		}
		else {
			deactivateMenu();
		}
	}
}

void GameUI::animateMenubar() {
	moveMenu = true;
}

void GameUI::Update() {
	char* goldString = new char[10];
	sprintf(goldString, "%d", resources->getCurrentGold());
	gold->setText(String("Gold: ") + goldString); // = new SceneLabel(String("Gold: ") + resource, 20, "sans");
	gold->setPosition(20 + gold->getWidth() / 2, barInfoBox->getHeight() - 20);
	/*if (moveMenu && menubar->getPosition().y < -400)
	{
		int x = menubar->getPosition().x;
		int y = menubar->getPosition().y;
		menubar->setPosition(x + 1, y + 1, 0);
	}
	else if (moveMenu && menubar->getPosition().y >= -400)
	{
		moveMenu = false;
	}*/
}

void GameUI::createBuildMenu() {
	menuBuild = new MenuBuild();
	menubar->addChild(menuBuild->buildBox);
	
	menuPatron = new MenuPatron();
	menubar->addChild(menuPatron->patronBox);

	menuStaff = new MenuStaff();
	menubar->addChild(menuStaff->staffBox);

	menuResources = new MenuResources(this);
	menubar->addChild(menuResources->resourcesBox);
}

void GameUI::setActiveMenu(int mode)
{
	menuBuild->isActive = false;
	menuResources->isActive = false;
	menuPatron->isActive = false;
	menuStaff->isActive = false;
	menuResources->resourcesBox->visible = false;
	menuBuild->buildBox->visible = false;
	menuResources->resourcesBox->visible = false;
	menuPatron->patronBox->visible = false;
	menuStaff->staffBox->visible = false;
	menuToggle = true;
	gameData->getGameMap()->raiseWalls();

	switch (mode)
	{
		case BUILD:
		{
			menuBuild->isActive = true;
			menuBuild->buildBox->visible = true;
			menuMode = BUILD;
			gameData->getGameMap()->lowerWalls();
			break;
		}
		case RESOURCES:
		{
			menuResources->isActive = true;
			menuResources->resourcesBox->visible = true;
			menuMode = RESOURCES;
			break;
		}
		case PATRON:
		{
			menuPatron->isActive = true;
			menuPatron->patronBox->visible = true;
			menuMode = PATRON;
			break;
		}
		case STAFF:
		{
			menuStaff->isActive = true;
			menuStaff->staffBox->visible = true;
			menuMode = STAFF;
			break;
		}
	}

}

void GameUI::deactivateMenu()
{
	menuBuild->isActive = false;
	menuResources->isActive = false;
	menuPatron->isActive = false;
	menuStaff->isActive = false;
	menuMode = NONE;
	menubar->moveFromCurrent(0, -240, 1000);
	menuToggle = false;
}