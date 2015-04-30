#include "UIMover.h"

UIMover::UIMover()
{

}

UIMover::~UIMover() {
}

Vector3 UIMover::moveIn3DLurp(Vector3 current, Vector3 desired) {
	GameData *gameData = GameData::getInstance();
	Core *core = gameData->getCore();

	float newX = current.x;
	float newY = current.y;
	float newZ = current.z;

	float lurp = 1;

	if (desired.x > current.x)
	{
		newX = current.x;
		newX += ((desired.x - current.x) * lurp) * core->getElapsed();
	}
	else if (desired.x < current.x)
	{
		newX = current.x;
		newX -= ((desired.x - current.x) * lurp) * core->getElapsed();
	}
	if (desired.y > current.y)
	{
		newY = current.y;
		newY += ((desired.y - current.y) * lurp) * core->getElapsed();
	}
	else if (desired.y < current.y)
	{
		newY = current.y;
		newY -= ((desired.y - current.y) * lurp) * core->getElapsed();
	}

	if (desired.z > current.z)
	{
		newZ = current.z;
		newZ += ((desired.z - current.z) * lurp) * core->getElapsed();
	}
	else if (desired.z < current.z)
	{
		newZ = current.z;
		newZ -= ((desired.z - current.z) * lurp) * core->getElapsed();
	}

	return Vector3(newX, newY, newZ);
}

Vector3 UIMover::moveIn3DLinear(Vector3 current, Vector3 desired, int speed) {
	GameData *gameData = GameData::getInstance();
	Core *core = gameData->getCore();

	float newX = current.x;
	float newY = current.y;
	float newZ = current.z;

	if (desired.x > current.x)
	{
		if (abs(speed * core->getElapsed()) < abs(current.x - desired.x)) {
			newX = current.x + (speed * core->getElapsed());
		}
		else {
			newX = desired.x;
		}
	}
	else if (desired.x < current.x)
	{
		if (abs(speed * core->getElapsed()) < abs(current.x - desired.x)) {
			newX = current.x - (speed * core->getElapsed());
		}
		else {
			newX = desired.x;
		}
	}
	if (desired.y > current.y)
	{
		if (abs(speed * core->getElapsed()) < abs(current.y - current.y)) {
			newY = current.y + (speed * core->getElapsed());
		}
		else {
			newY = current.y;
		}
	}
	else if (desired.y < current.y)
	{
		if (abs(speed * core->getElapsed()) < abs(current.y - current.y)) {
			newY = current.y - (speed * core->getElapsed());
		}
		else {
			newY = current.y;
		}
	}

	/*if (desired.z > current.z)
	{
		newZ = current.z;
		newZ += ((desired.z - current.z) * lurp) * core->getElapsed();
	}
	else if (desired.z < current.z)
	{
		newZ = current.z;
		newZ -= ((desired.z - current.z) * lurp) * core->getElapsed();
	} */

	return Vector3(newX, newY, newZ);
}