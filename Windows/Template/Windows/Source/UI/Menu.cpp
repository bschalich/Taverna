#include "Menu.h"

Menu::Menu(GameData *game) : EventHandler() {
   gameData = game;
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   scene3D = gameData->getScene3D();
   
   menuBox = new UIBox("Assets/Images/buildMenu.png", 0, 1, 1, 1, 720, 470);
   menuBox->setPosition(-350, -200, 0);
   scene2D->addChild(menuBox);
   
   menuItems[0] = new UIImageButton("Assets/Images/3x3.png", 1, 291, 200);
   menuItems[0]->setPosition(-320, 0, 0);
   scene2D->addChild(menuItems[0]);
   
   menuItems[1] = new UIImageButton("Assets/Images/4x4.png", 1, 291, 200);
   menuItems[1]->setPosition(40, 0, 0);
   scene2D->addChild(menuItems[1]);
   
   //Keyboard shortcut
   core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void Menu::handleEvent(Event *e) {
	
	//Keyboard
	InputEvent *inputEvent = (InputEvent*)e;
	if(e->getDispatcher() == core->getInput()) {
		switch(e->getEventCode()) {
         case InputEvent::EVENT_KEYDOWN:
            switch (inputEvent->keyCode()) {
               case KEY_1:
                  scene2D->removeEntity(menuBox);
                  scene2D->removeEntity(menuItems[0]);
                  scene2D->removeEntity(menuItems[1]);
                  gameData->setGameMode(MAP_MODE);
                  gameData->setRoomWidth(3);
                  gameData->setRoomHeight(3);
                  scene2D->setActiveCamera(scene3D->getDefaultCamera());
                  break;
               case KEY_2:
                  scene2D->removeEntity(menuBox);
                  scene2D->removeEntity(menuItems[0]);
                  scene2D->removeEntity(menuItems[1]);
                  gameData->setGameMode(MAP_MODE);
                  gameData->setRoomWidth(4);
                  gameData->setRoomHeight(4);
                  scene2D->setActiveCamera(scene3D->getDefaultCamera());
                  break;
            }
		}
	}
}

Menu::~Menu() {
   
}