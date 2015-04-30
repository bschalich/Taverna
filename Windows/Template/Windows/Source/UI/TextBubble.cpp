#include "TextBubble.h"

TextBubble::TextBubble(Vector3 position, String image, String text, int velocity, Person *person) : MenuLabel (text, 16, "sans")
{
	this->position = position;
	this->image = image;
	this->text = text;
	this->velocity = velocity;
	this->person = person;
	gameData = GameData::getInstance();

	buildBubble();
}

TextBubble::~TextBubble()
{

}

void TextBubble::buildBubble()
{
	this->Scale(0.08, 0.08, 0.08);
	this->color = new Color(255, 255, 255, 255);
	this->setPosition(Vector3(position.x + 4, 9, position.z));
	positionX = position.x + 4;
    positionY = 9;
    positionZ = position.z;
	gameData->getScene3D()->addChild(this);

	if (image.size() > 0) {
		MenuImage *icon = new MenuImage(image, 4, 4);
		icon->billboardMode = true;
		icon->Scale(10, 10, 10);
		icon->setPosition(0 - this->getWidth() / 2 - icon->getWidth() - 40, 0 - icon->getHeight() / 2 - 20, 0);
		this->addChild(icon);
	}

	moveFromCurrent(0, 10, 0, 50);
	Tween *tween2 = new Tween(&curY, Tween::EASE_OUT_SINE, this->getPosition().y, positionY, 1);
	setAliveTimer(2.5);

}

void TextBubble::Update()
{
	//Vector3 move = UIMover::moveIn3DLurp(this->getPosition(), Vector3(positionX, positionY, positionZ));
	Vector3 move;
	move.y = curY;

	if (person)
	{
		move.x = person->getPosition().x;
		move.z = person->getPosition().z;
	}

	this->setPosition(move);
	aliveTimer -= core->getElapsed();
	if (aliveTimer < 0)
	{
		delete(this);
	}

	SceneLabel::Update();
}