#include "MenuPatron.h"

MenuPatron::MenuPatron() : EventHandler() {
	gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   scene3D = gameData->getScene3D();
   isActive = false;
   
   scene2D->setActiveCamera(scene2D->getDefaultCamera());
   
   patronBox = new MenuImage("Assets/Images/patronsBox.png", 990, 250);
   patronBox->setPosition(0, 25, 0);
   patronBox->setPositions(0, 25);
   //buildBox->setPosition(-340, -610, 0);
   //buildBox->setPositions(-340, -610);
   //scene2D->addChild(buildBox);
   
  /* menuItems[0] = new UIImageButton("Assets/Images/3x3.png", 1, 291, 200);
   menuItems[0]->setPosition(-320, 0, 0);
   scene2D->addChild(menuItems[0]);
   
   menuItems[1] = new UIImageButton("Assets/Images/3x5.png", 1, 291, 200);
   menuItems[1]->setPosition(40, 0, 0);
   scene2D->addChild(menuItems[1]);
   */
   //Keyboard shortcut
   core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void MenuPatron::handleEvent(Event *e) {
	
	//Keyboard
	if (isActive) {
		InputEvent *inputEvent = (InputEvent*)e;
		if(e->getDispatcher() == core->getInput()) {
			switch(e->getEventCode()) {
			 case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
				}
			}
		}
	}
}

MenuPatron::~MenuPatron() {
   
}