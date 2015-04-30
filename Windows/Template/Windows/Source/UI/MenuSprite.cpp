#include "MenuSprite.h"
#include <cmath>

MenuSprite::MenuSprite(GameData *game, String file, Number width, Number height) : SceneSprite(file, width, height) {
   gameData = game;
   core = gameData->getCore();
   scene2D = gameData->getScene2D();

   this->depthTest = false;
   this->depthWrite = false;
   this->setPosition(0, 0, 0);

   //scene2D->addChild(this);
   positionX = 0;
   positionY = 0;
   speed = 0;
}

MenuSprite::~MenuSprite() {
   scene2D->removeEntity(this);
}

void MenuSprite::moveFromCurrent(Number x, Number y, Number speed) {
	
	positionX = this->getPosition().x + x;
	positionY = this->getPosition().y + y;
	this->speed = speed;
}

void MenuSprite::setPositions(int x, int y) {
	positionX = x;
	positionY = y;
}

bool MenuSprite::isStationary() {
	return positionX == this->getPosition().x && positionY == this->getPosition().y;
}

void MenuSprite::Update() {
	int newX = this->getPosition().x;
	int newY = this->getPosition().y;

	if (positionX > this->getPosition().x)
	{
		if (abs(speed * core->getElapsed()) < abs(this->getPosition().x - positionX)) {
			newX = this->getPosition().x + (speed * core->getElapsed());
		}
		else {
			newX = positionX;
		}
	}
	else if (positionX < this->getPosition().x)
	{
		if (abs(speed * core->getElapsed()) < abs(this->getPosition().x - positionX)) {
			newX = this->getPosition().x - (speed * core->getElapsed());
		}
		else {
			newX = positionX;
		}
	}
	if (positionY > this->getPosition().y)
	{
		if (abs(speed * core->getElapsed()) < abs(this->getPosition().y - positionY)) {
			newY = this->getPosition().y + (speed * core->getElapsed());
		}
		else {
			newY = positionY;
		}
	}
	else if (positionY < this->getPosition().y)
	{
		if (abs(speed * core->getElapsed()) < abs(this->getPosition().y - positionY)) {
			newY = this->getPosition().y - (speed * core->getElapsed());
		}
		else {
			newY = positionY;
		}
	}

	this->setPosition(newX, newY, 0);

	SceneSprite::Update();
}