#include "MenuResources.h"

MenuResources::MenuResources(GameUI *gameUI) : EventHandler() {
   gameData = GameData::getInstance();
   core = gameData->getCore();
   scene2D = gameData->getScene2D();
   scene3D = gameData->getScene3D();
   isActive = false;
   resources = TavernResources::getInstance();

   this->gameUI = gameUI;
   
   scene2D->setActiveCamera(scene2D->getDefaultCamera());
   
   resourcesBox = new MenuImage("Assets/Images/buildBox.png", 990, 250);
   resourcesBox->setPosition(0, 25, 0);
   resourcesBox->setPositions(0, 25);

   //default
   prepResources();
}

void MenuResources::prepResources()
{
	ResourceItem *mead = new ResourceItem(gameUI, 25, 120, TavernResources::MEAD, "Mead", "Assets/Images/mug.png");
	resourcesBox->addChild(mead->transparentBox);
	resources->setMeadStockLabel(mead->stockValue);
	mead->deactivateStocks();

	ResourceItem *wine = new ResourceItem(gameUI, 305, 120, TavernResources::WINE, "Wine", "Assets/Images/wine.png");
	resourcesBox->addChild(wine->transparentBox);
	resources->setWineStockLabel(wine->stockValue);
	wine->deactivateStocks();
}

void MenuResources::handleEvent(Event *e) {
}

MenuResources::~MenuResources() {
}