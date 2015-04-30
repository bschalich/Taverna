#include "StartScreen.h"

StartScreen::StartScreen() : EventHandler() {
   isStart = false;
   gameData = GameData::getInstance();

   startButton = new MenuItem(gameData, "Assets/Images/startButton.png", 350, 150);
   startButton->setPosition(-(startButton->getWidth() / 2), -250, 0);
   startButton->addEventListener(this, UIEvent::CLICK_EVENT);
   gameData->getScene2D()->addChild(startButton);

   title = new MenuImage("Assets/Images/titleTaverna.png", 600, 300);
   title->setPosition(-(title->getWidth() / 2), 0, 0);
   gameData->getScene2D()->addChild(title);
}

StartScreen::~StartScreen() {
}

bool StartScreen::getIsStart() {
	return isStart;
}

void StartScreen::handleEvent(Event *e) {
	if(e->getDispatcher() == startButton) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
            gameData->clickSound->Play(false);
				isStart = true;	
				gameData->getScene2D()->removeEntity(startButton);
				gameData->getScene2D()->removeEntity(title);
            break;
			}
		}
	}
}