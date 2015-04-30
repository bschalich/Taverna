#include "GameOver.h"

GameOver::GameOver() : EventHandler() {
   gameData = GameData::getInstance();
   resources = TavernResources::getInstance();

   bg = new MenuImage("Assets/Images/monthBG.png", 900, 500);
   bg->setPosition(-(bg->getWidth() / 2), -(bg->getHeight() / 2), 0);
   gameData->getScene2D()->addChild(bg);

   gameOver = new MenuLabel("Game Over", 50, "sans");
   gameOver->setPosition(Vector3(bg->getHeight() - gameOver->getHeight() / 2 - 30,
	   bg->getWidth() / 2, 0));
   bg->addChild(gameOver);

   /*month = new MenuLabel(gameData->getMonth(), 30, "sans");
   month->setPosition(Vector3((month->getWidth() / 2) + 45,
	   bg->getHeight() - month->getHeight() / 2 - 30, 0));
   bg->addChild(month);

   doneButton = new MenuItem(gameData, "Assets/Images/doneTab.png", 150, 100);
   doneButton->setPosition(-doneButton->getWidth() - 100, GameUI::getInstance()->menubar->getHeight() / 2 - doneButton->getHeight() / 2, 0);
   doneButton->addEventListener(this, UIEvent::CLICK_EVENT);
   //GameUI::getInstance()->menubar->addChild(doneButton);

   bg->addChild(infoContainer);*/
}

GameOver::~GameOver() {
}

void GameOver::Update() {

}

void GameOver::handleEvent(Event *e) {

}