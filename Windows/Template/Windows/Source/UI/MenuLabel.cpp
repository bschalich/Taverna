#include "MenuLabel.h"
#include <cmath>

MenuLabel::MenuLabel(String text, int size, String font) : SceneLabel(text, size, font) {
   gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   this->depthTest = false;
   this->depthWrite = false;
   this->billboardMode = true;
   this->visible = true;
   this->setPosition(Vector3(0, 0, 0));
   positionX = 0;
   positionY = 0;
   positionZ = 0;
   speed = 0;
}

MenuLabel::~MenuLabel() {
   scene2D->removeEntity(this);
   gameData->getScene3D()->removeEntity(this);
}

void MenuLabel::moveFromCurrent(Number x, Number y, Number z, Number speed) {
	
	positionX = this->getPosition().x + x;
	positionY = this->getPosition().y + y;
	positionZ = this->getPosition().z + z;
	this->speed = speed;

	Tween *tween = new Tween(&curX, Tween::EASE_IN_SINE, this->getPosition().x, positionX, 1);
	Tween *tween2 = new Tween(&curY, Tween::EASE_IN_SINE, this->getPosition().y, positionY, 1);
	Tween *tween3 = new Tween(&curZ, Tween::EASE_IN_SINE, this->getPosition().z, positionZ, 1);
}

void MenuLabel::setPosition(Vector3 pos)
{
	curX = pos.x;
	curY = pos.y;
	curZ = pos.z;
	SceneLabel::setPosition(pos);
}

void MenuLabel::Update() {

	//Vector3 move = UIMover::moveIn3DLurp(this->getPosition(), Vector3(positionX, positionY, positionZ));
	//this->setPosition(move);

	this->setPosition(Vector3(curX, curY, curZ));

	/*aliveTimer -= core->getElapsed();
	if (aliveTimer < 0)
	{
		delete(this);
	}*/

	SceneLabel::Update();
}

void MenuLabel::setAliveTimer(float num)
{
	aliveTimer = num;
}