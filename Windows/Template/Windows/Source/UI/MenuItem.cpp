#include "MenuItem.h"
#include <cmath>

MenuItem::MenuItem(GameData *game, String file, Number width, Number height) : UIImageButton(file, 1.0, width, height) {
   gameData = game;
   core = gameData->getCore();
   scene2D = gameData->getScene2D();

   this->depthTest = false;
   this->depthWrite = false;
   this->setPosition(0, 0, 0);

   positionX = 0;
   positionY = 0;
   speed = 0;
   
   //Keyboard shortcut
   //core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

MenuItem::~MenuItem() {
   scene2D->removeEntity(this);
}

void MenuItem::moveFromCurrent(Number x, Number y, Number speed) {
	
	positionX = this->getPosition().x + x;
	positionY = this->getPosition().y + y;
	this->speed = speed;
}

void MenuItem::setPositions(int x, int y) {
	positionX = x;
	positionY = y;
}

void MenuItem::Update() {

	Vector3 move = UIMover::moveIn3DLinear(this->getPosition(), Vector3(positionX, positionY, 0), speed);

	this->setPosition(move);

	UIImageButton::Update();
}
