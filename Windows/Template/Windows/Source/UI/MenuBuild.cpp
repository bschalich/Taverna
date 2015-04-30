#include "MenuBuild.h"

MenuBuild::MenuBuild() : EventHandler() {
	gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   scene3D = gameData->getScene3D();
   isActive = false;
   roomType = TAVERN_EXPANSION;
   srand((unsigned)time(0));
   
   scene2D->setActiveCamera(scene2D->getDefaultCamera());
   
   buildBox = new MenuImage("Assets/Images/buildBox.png", 990, 250);
   buildBox->setPosition(0, 25, 0);
   buildBox->setPositions(0, 25);
   
   expansionTab = new MenuItem(gameData, "Assets/Images/expansionButton.png", 150, 25);
   expansionTab->setPosition(30, buildBox->getHeight() - 50, 0);
   buildBox->addChild(expansionTab);
   expansionTab->addEventListener(this, UIEvent::CLICK_EVENT);
   expansionTab->visible = false;
   tab[0] = expansionTab;

   expansionTabActive = new MenuItem(gameData, "Assets/Images/expansionButtonActive.png", 150, 25);
   expansionTabActive->setPosition(30, buildBox->getHeight() - 50, 0);
   buildBox->addChild(expansionTabActive);
   expansionTabActive->addEventListener(this, UIEvent::CLICK_EVENT);
   expansionTabActive->visible = true;
   tab[4] = expansionTabActive;

   tableButton = new MenuItem(gameData, "Assets/Images/tableButton.png", 75, 50);
   tableButton->setPosition(expansionTab->getPosition().x + expansionTab->getWidth() + 30, buildBox->getHeight() - tableButton->getHeight() - 20, 0);
   buildBox->addChild(tableButton);
   tableButton->addEventListener(this, UIEvent::CLICK_EVENT);

/*   kitchenTab = new MenuItem(gameData, "Assets/Images/kitchenButton.png", 150, 25);
   kitchenTab->setPosition(expansionTab->getPosition().x + 160, expansionTab->getPosition().y, 0);
   buildBox->addChild(kitchenTab);
   kitchenTab->addEventListener(this, UIEvent::CLICK_EVENT);
   kitchenTab->visible = true;
   tab[1] = kitchenTab;

   kitchenTabActive = new MenuItem(gameData, "Assets/Images/kitchenButtonActive.png", 150, 25);
   kitchenTabActive->setPosition(expansionTab->getPosition().x + 160, expansionTab->getPosition().y, 0);
   buildBox->addChild(kitchenTabActive);
   kitchenTabActive->addEventListener(this, UIEvent::CLICK_EVENT);
   kitchenTabActive->visible = false;
   tab[5] = kitchenTabActive;

   restroomTab = new MenuItem(gameData, "Assets/Images/restroomButton.png", 150, 25);
   restroomTab->setPosition(kitchenTab->getPosition().x + 160, kitchenTab->getPosition().y, 0);
   buildBox->addChild(restroomTab);
   restroomTab->addEventListener(this, UIEvent::CLICK_EVENT);
   restroomTab->visible = true;
   tab[2] = restroomTab;

   restroomTabActive = new MenuItem(gameData, "Assets/Images/restroomButtonActive.png", 150, 25);
   restroomTabActive->setPosition(kitchenTab->getPosition().x + 160, kitchenTab->getPosition().y, 0);
   buildBox->addChild(restroomTabActive);
   restroomTabActive->addEventListener(this, UIEvent::CLICK_EVENT);
   restroomTabActive->visible = false;
   tab[6] = restroomTabActive;

   bedchambersTab = new MenuItem(gameData, "Assets/Images/bedchamberButton.png", 150, 25);
   bedchambersTab->setPosition(restroomTab->getPosition().x + 160, restroomTab->getPosition().y, 0);
   buildBox->addChild(bedchambersTab);
   bedchambersTab->addEventListener(this, UIEvent::CLICK_EVENT);
   bedchambersTab->visible = true;
   tab[3] = bedchambersTab;

   bedchambersTabActive = new MenuItem(gameData, "Assets/Images/bedchamberButtonActive.png", 150, 25);
   bedchambersTabActive->setPosition(restroomTab->getPosition().x + 160, restroomTab->getPosition().y, 0);
   buildBox->addChild(bedchambersTabActive);
   bedchambersTabActive->addEventListener(this, UIEvent::CLICK_EVENT);
   bedchambersTabActive->visible = false;
   tab[3] = bedchambersTabActive;
   */
  /* doorTab = new MenuItem(gameData, "Assets/Images/doorButton.png", 150, 25);
   doorTab->setPosition(expansionTab->getPosition().x + doorTab->getWidth() + 20, expansionTab->getPosition().y, 0);
   buildBox->addChild(doorTab);
   doorTab->addEventListener(this, UIEvent::CLICK_EVENT);
   doorTab->visible = true;
   tab[4] = doorTab;

   doorTabActive = new MenuItem(gameData, "Assets/Images/doorButtonActive.png", 150, 25);
   doorTabActive->setPosition(expansionTab->getPosition().x + doorTab->getWidth() + 20, expansionTab->getPosition().y, 0);
   buildBox->addChild(doorTabActive);
   doorTabActive->addEventListener(this, UIEvent::CLICK_EVENT);
   doorTabActive->visible = false;
   tab[7] = doorTabActive; */

   threeByThree = new MenuItem(gameData, "Assets/Images/3x3.png", 200, 140);
   threeByFive = new MenuItem(gameData, "Assets/Images/3x5.png", 200, 140);
   fiveByThree = new MenuItem(gameData, "Assets/Images/5x3.png", 200, 140);
   fiveByFive = new MenuItem(gameData, "Assets/Images/5x5.png", 200, 140);
   deleteButton = new MenuItem(gameData, "Assets/Images/d.png", 200, 140);
   sizeBank[0] = fiveByFive;
   sizeBank[1] = threeByThree;
   sizeBank[2] = threeByFive;
   sizeBank[3] = fiveByThree;
   threeByThree->addEventListener(this, UIEvent::CLICK_EVENT);
   threeByFive->addEventListener(this, UIEvent::CLICK_EVENT);
   fiveByThree->addEventListener(this, UIEvent::CLICK_EVENT);
   fiveByFive->addEventListener(this, UIEvent::CLICK_EVENT);

	/*deleteButton = new MenuItem(gameData, "Assets/Images/deleteButton.png", 50, 35);
	buildBox->addChild(deleteButton);
	deleteButton->setPosition(buildBox->getWidth() - deleteButton->getWidth() - 10, buildBox->getHeight() - deleteButton->getHeight() - 10);
	deleteButton->addEventListener(this, UIEvent::CLICK_EVENT);*/
   
	
   setMenuItems(0);

   //Keyboard shortcut
   core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

MenuBuild::~MenuBuild() {
   
}

void MenuBuild::setMenuItems(int mod)
{
	removeMenuDoors();

	for (int i = 0; i < 4; i++) {
		buildBox->removeChild(menuItems[i]);
		menuItems[i] = sizeBank[i];
		int x = i * 250;
		menuItems[i]->setPosition(30 + x, 50, 0);
		buildBox->addChild(menuItems[i]);

		int size = 0;
		if (i == 0)
		{
			size = 5 * 5;
		}
		else if (i == 1)
		{
			size = 3 * 3;
		}
		else
			size = 3 * 5;

		char *priceLabel = new char[10];
		sprintf(priceLabel, "$%d", TavernResources::getInstance()->getTilePrice() * size);
		MenuLabel *price = new MenuLabel(priceLabel, 30, "sans");
		price->setPosition(Vector3(70 + x, 50, 0));
		buildBox->addChild(price);
	}
}

void MenuBuild::removeMenuDoors()
{
	buildBox->removeChild(doorAdd);
	buildBox->removeChild(topLeftAddDoor);
	buildBox->removeChild(topRightAddDoor);
	buildBox->removeChild(lowerLeftAddDoor);
	buildBox->removeChild(lowerRightAddDoor);

	buildBox->removeChild(doorRemove);
	buildBox->removeChild(topLeftRemoveDoor);
	buildBox->removeChild(topRightRemoveDoor);
	buildBox->removeChild(lowerLeftRemoveDoor);
	buildBox->removeChild(lowerRightRemoveDoor);
}

void MenuBuild::setMenuDoors()
{
	for (int i = 0; i < 4; i++) {
		buildBox->removeChild(menuItems[i]);
	}
	removeMenuDoors();

   doorAdd = new SceneLabel(String("Add Door"), 26, "sans");
   buildBox->addChild(doorAdd);
   doorAdd->setPosition(120 + doorAdd->getWidth() / 2, buildBox->getHeight() - 50);
   doorAdd->depthTest = false;
   doorAdd->depthWrite = false;
   doorAdd->visible = true;
   doorAdd->color = new Color(1, 1, 1, 250);

   topLeftAddDoor = new MenuItem(gameData, "Assets/Images/topLeftDoor.png", 150, 60);
   topLeftAddDoor->setPosition(20, buildBox->getHeight() - topLeftAddDoor->getHeight() - 80, 0);
   buildBox->addChild(topLeftAddDoor);
   topLeftAddDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   topLeftAddDoor->visible = true;

   topRightAddDoor = new MenuItem(gameData, "Assets/Images/topRightDoor.png", 150, 60);
   topRightAddDoor->setPosition(topRightAddDoor->getWidth() + 40, buildBox->getHeight() - topRightAddDoor->getHeight() - 80, 0);
   buildBox->addChild(topRightAddDoor);
   topRightAddDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   topRightAddDoor->visible = true;

   lowerLeftAddDoor = new MenuItem(gameData, "Assets/Images/lowerLeftDoor.png", 150, 60);
   lowerLeftAddDoor->setPosition(20, buildBox->getHeight() - lowerLeftAddDoor->getHeight() - 80 - topLeftAddDoor->getHeight() - 20, 0);
   buildBox->addChild(lowerLeftAddDoor);
   lowerLeftAddDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   lowerLeftAddDoor->visible = true;

   lowerRightAddDoor = new MenuItem(gameData, "Assets/Images/lowerRightDoor.png", 150, 60);
   lowerRightAddDoor->setPosition(lowerRightAddDoor->getWidth() + 40, buildBox->getHeight() - lowerRightAddDoor->getHeight() - 80 - topRightAddDoor->getHeight() - 20, 0);
   buildBox->addChild(lowerRightAddDoor);
   lowerRightAddDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   lowerRightAddDoor->visible = true;

   //Remove Doors
   doorRemove = new SceneLabel(String("Remove Door"), 26, "sans");
   buildBox->addChild(doorRemove);
   doorRemove->setPosition(490 + doorRemove->getWidth() / 2, buildBox->getHeight() - 50);
   doorRemove->depthTest = false;
   doorRemove->depthWrite = false;
   doorRemove->visible = true;
   doorRemove->color = new Color(1, 1, 1, 250);

   topLeftRemoveDoor = new MenuItem(gameData, "Assets/Images/topLeftDoor.png", 150, 60);
   topLeftRemoveDoor->setPosition(420, buildBox->getHeight() - topLeftAddDoor->getHeight() - 80, 0);
   buildBox->addChild(topLeftRemoveDoor);
   topLeftRemoveDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   topLeftRemoveDoor->visible = true;

   topRightRemoveDoor = new MenuItem(gameData, "Assets/Images/topRightDoor.png", 150, 60);
   topRightRemoveDoor->setPosition(topRightRemoveDoor->getWidth() + 440, buildBox->getHeight() - topRightAddDoor->getHeight() - 80, 0);
   buildBox->addChild(topRightRemoveDoor);
   topRightRemoveDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   topRightRemoveDoor->visible = true;

   lowerLeftRemoveDoor = new MenuItem(gameData, "Assets/Images/lowerLeftDoor.png", 150, 60);
   lowerLeftRemoveDoor->setPosition(420, buildBox->getHeight() - lowerLeftAddDoor->getHeight() - 80 - topLeftAddDoor->getHeight() - 20, 0);
   buildBox->addChild(lowerLeftRemoveDoor);
   lowerLeftRemoveDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   lowerLeftRemoveDoor->visible = true;

   lowerRightRemoveDoor = new MenuItem(gameData, "Assets/Images/lowerRightDoor.png", 150, 60);
   lowerRightRemoveDoor->setPosition(lowerRightRemoveDoor->getWidth() + 440, buildBox->getHeight() - lowerRightAddDoor->getHeight() - 80 - topRightAddDoor->getHeight() - 20, 0);
   buildBox->addChild(lowerRightRemoveDoor);
   lowerRightRemoveDoor->addEventListener(this, UIEvent::CLICK_EVENT);
   lowerRightRemoveDoor->visible = true;
}

void MenuBuild::handleEvent(Event *e) {
	
	if (isActive) {
		if(e->getDispatcher() == threeByThree) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setBuildDimensions(3, 3);
				break;
				}
			}
		}
		else if(e->getDispatcher() == threeByFive) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setBuildDimensions(3, 5);
				break;
				}
			}
		}
		else if(e->getDispatcher() == fiveByThree) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setBuildDimensions(5, 3);
				break;
				}
			}
		}
		else if(e->getDispatcher() == fiveByFive) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setBuildDimensions(5, 5);
				break;
				}
			}
		}
		else if(e->getDispatcher() == tableButton) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					gameData->setGameMode(TABLE_MODE);
				break;
				}
			}
		}
		else if(e->getDispatcher() == expansionTab) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setMenuItems(0);
					roomType = TAVERN_EXPANSION;
					setActiveTab(expansionTab);
				break;
				}
			}
		}
		else if(e->getDispatcher() == kitchenTab) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setMenuItems(1);
					roomType = KITCHEN;
					setActiveTab(kitchenTab);
				break;
				}
			}
		}
		else if(e->getDispatcher() == restroomTab) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setMenuItems(2);
					roomType = RESTROOM;
					setActiveTab(restroomTab);
				break;
				}
			}
		}
		else if(e->getDispatcher() == bedchambersTab) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setMenuItems(3);
					roomType = BEDCHAMBER;
					setActiveTab(bedchambersTab);
				break;
				}
			}
		}
		else if(e->getDispatcher() == doorTab) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setMenuDoors();
					roomType = BEDCHAMBER;
					setActiveTab(doorTab);
				break;
				}
			}
		}
		else if(e->getDispatcher() == deleteButton) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					gameData->setGameMode(DELETE_MODE);
				break;
				}
			}
		}
		else if(e->getDispatcher() == topLeftAddDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(TOP_LEFT, ADD_DOOR);
				break;
				}
			}
		}
		else if(e->getDispatcher() == topRightAddDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(TOP_RIGHT, ADD_DOOR);
				break;
				}
			}
		}
		else if(e->getDispatcher() == lowerLeftAddDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(BOT_LEFT, ADD_DOOR);
				break;
				}
			}
		}
		else if(e->getDispatcher() == lowerRightAddDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(BOT_RIGHT, ADD_DOOR);
				break;
				}
			}
		}
				else if(e->getDispatcher() == topLeftRemoveDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(TOP_LEFT, REMOVE_DOOR);
				break;
				}
			}
		}
		else if(e->getDispatcher() == topRightRemoveDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(TOP_RIGHT, REMOVE_DOOR);
				break;
				}
			}
		}
		else if(e->getDispatcher() == lowerLeftRemoveDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(BOT_LEFT, REMOVE_DOOR);
				break;
				}
			}
		}
		else if(e->getDispatcher() == lowerRightRemoveDoor) {
			switch (e->getEventCode()) {
				{case UIEvent::CLICK_EVENT:
					setDoorEditing(BOT_RIGHT, REMOVE_DOOR);
				break;
				}
			}
		}

		InputEvent *inputEvent = (InputEvent*)e;
		if(e->getDispatcher() == core->getInput()) {
			switch(e->getEventCode()) {
			 case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
				   case KEY_1:
					  setBuildDimensions(3, 3);
					  break;
				   case KEY_2:
					   setBuildDimensions(3, 5);
					  break;
				}
			}
		}
	}
}

void MenuBuild::setDoorEditing(int doorSide, int gameMode) {
	gameData->setDoorSide(doorSide);
	gameData->setGameMode(gameMode);
}

void MenuBuild::setBuildDimensions(int width, int height) {
	scene2D->removeEntity(buildBox);
	scene2D->removeEntity(menuItems[0]);
	scene2D->removeEntity(menuItems[1]);
	gameData->setGameMode(MAP_MODE);
	gameData->setRoomWidth(width);
	gameData->setRoomHeight(height);
	gameData->setRoomType(roomType);
}

void MenuBuild::setActiveTab(MenuItem *tab)
{
	expansionTab->visible = true;
	expansionTabActive->visible = false;
/*	kitchenTab->visible = true;
	kitchenTabActive->visible = false;
	restroomTab->visible = true;
	restroomTabActive->visible = false;
	bedchambersTab->visible = true;
	bedchambersTabActive->visible = false;
	doorTab->visible = true;
	doorTabActive->visible = false;*/

	if (tab == expansionTab)
	{
		expansionTab->visible = false;
		expansionTabActive->visible = true;
	}
	else if (tab == kitchenTab)
	{
		kitchenTab->visible = false;
		kitchenTabActive->visible = true;
	}
	else if (tab == restroomTab)
	{
		restroomTab->visible = false;
		restroomTabActive->visible = true;
	}
	else if (tab == bedchambersTab)
	{
		bedchambersTab->visible = false;
		bedchambersTabActive->visible = true;
	}
	else if (tab == doorTab)
	{
		doorTab->visible = false;
		doorTabActive->visible = true;
	}
}