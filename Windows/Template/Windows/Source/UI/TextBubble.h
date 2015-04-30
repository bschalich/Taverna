#ifndef BUBBLE
#define BUBBLE

#include "Polycode.h"
#include "PolycodeUI.h"
#include "MenuLabel.h"
#include "define.h"
#include "MenuImage.h" 
#include "MenuItem.h"
#include "GameData.h"
#include "Person.h"
#include "UIMover.h"

#include <vector>

using namespace Polycode;

class TextBubble : public MenuLabel {

public:
	TextBubble(Vector3 position, String image, String text, int velocity, Person *person);
	~TextBubble();

private:
	GameData *gameData;

	String image;
	String text;
	int velocity;
	Person *person;

	void buildBubble();
	void Update();
};

#endif