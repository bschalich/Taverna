#include "MenuStaff.h"

MenuStaff::MenuStaff() : EventHandler() {
   gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   scene3D = gameData->getScene3D();
   isActive = false;
   
   scene2D->setActiveCamera(scene2D->getDefaultCamera());
   
   staffBox = new MenuImage("Assets/Images/staffBox.png", 900, 250);
   staffBox->setPosition(0, 0, 0);
   staffBox->setPositions(0, 0);
   //buildBox->setPosition(-340, -610, 0);
   //buildBox->setPositions(-340, -610);
   //scene2D->addChild(buildBox);
   
  /* menuItems[0] = new UIImageButton("Assets/Images/3x3.png", 1, 291, 200);
   menuItems[0]->setPosition(-320, 0, 0);
   scene2D->addChild(menuItems[0]);
   
   menuItems[1] = new UIImageButton("Assets/Images/4x4.png", 1, 291, 200);
   menuItems[1]->setPosition(40, 0, 0);
   scene2D->addChild(menuItems[1]);
   */
   //Keyboard shortcut
   core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void MenuStaff::handleEvent(Event *e) {
	
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

MenuStaff::~MenuStaff() {
   
}