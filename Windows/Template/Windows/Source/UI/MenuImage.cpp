#include "MenuImage.h"
#include <cmath>
MenuImage::MenuImage(String file, Number width, Number height) : UIImage(file, width, height) {
   gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   this->depthTest = false;
   this->depthWrite = false;
   this->setPosition(0, 0, 0);
   positionX = 0;
   positionY = 0;
   speed = 0;
   lurp = false;
}

MenuImage::~MenuImage() {
   scene2D->removeEntity(this);
}

void MenuImage::moveFromCurrent(Number x, Number y, Number speed) {
	
	positionX = this->getPosition().x + x;
	positionY = this->getPosition().y + y;
	this->speed = speed;
}

void MenuImage::setPositions(int x, int y) {
	positionX = x;
	positionY = y;
}

bool MenuImage::isStationary() {
	return positionX == this->getPosition().x && positionY == this->getPosition().y;
}

void MenuImage::Update() {
	float newX = this->getPosition().x;
	float newY = this->getPosition().y;
	float newZ = this->getPosition().z;

	Vector3 move;

	if (lurp)
	{
		move = UIMover::moveIn3DLurp(this->getPosition(), Vector3(positionX, positionY, 0));
		
		newX = move.x;
		newY = move.y;
		newZ = move.z;
	}
	else
	{
		/*move = UIMover::moveIn3DLinear(this->getPosition(), Vector3(positionX, positionY, 0), speed);

		newX = move.x;
		newY = move.y;
		newZ = 0; */

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
	}

	this->setPosition(Vector3(newX, newY, newZ));

	UIImage::Update();
}