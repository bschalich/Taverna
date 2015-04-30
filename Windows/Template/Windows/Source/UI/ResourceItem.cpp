#include "ResourceItem.h"

ResourceItem::ResourceItem(GameUI *gameUI, int x, int y, TavernResources::Items type, String title, String image) : EventHandler() {

	this->title = title;
	this->type = type;
	this->gameData = GameData::getInstance();
	this->gameUI = gameUI;
	this->x = x;
	this->y = y;
	this->image = image;

	resources = TavernResources::getInstance();
	
   build();

   sellPriceArrowUp->addEventListener(this, UIEvent::CLICK_EVENT);
   sellPriceArrowDown->addEventListener(this, UIEvent::CLICK_EVENT);
   stockArrowUp->addEventListener(this, UIEvent::CLICK_EVENT);
   stockPlusFive->addEventListener(this, UIEvent::CLICK_EVENT);
}

ResourceItem::~ResourceItem() {
}

void ResourceItem::build() {
	transparentBox = new MenuImage("Assets/Images/transparent.png", 250, 110);
	transparentBox->setPosition(x, y);

	SceneLabel *title = new SceneLabel(this->title, 16, "sans");
	title->color = new Color(0, 0, 0, 255);
    title->depthTest = false;
    title->depthWrite = false;
	title->setPosition(title->getWidth() / 2 + 10, transparentBox->getHeight() - title->getHeight() / 2 - 10);
	transparentBox->addChild(title);
	
	MenuImage *icon = new MenuImage(image, 65, 65);
	icon->setPosition(5, transparentBox->getHeight() - icon->getHeight() - 30);
	transparentBox->addChild(icon);

	SceneLabel *stock = new SceneLabel("Stock", 16, "sans");
	stock->color = new Color(0, 0, 0, 255);
    stock->depthTest = false;
    stock->depthWrite = false;
	stock->setPosition(stock->getWidth() / 2 + 75, title->getPosition().y - title->getHeight() - 5);
	transparentBox->addChild(stock);

	char* stockValueString = new char[5];
	sprintf(stockValueString, "%d", resources->getAmnt(type));
	stockValue = new SceneLabel(stockValueString, 16, "sans");
	stockValue->color = new Color(0, 0, 0, 255);
    stockValue->depthTest = false;
    stockValue->depthWrite = false;
	stockValue->setPosition((stock->getWidth() / 2) + (stockValue->getWidth() / 2) + 40, 0);
	stock->addChild(stockValue);

	stockArrowUp = new MenuItem(gameData, "Assets/Images/plus1.png", 30, 14);
	stockArrowUp->setPosition(stock->getPosition().x + stock->getWidth() / 2 + stockValue->getWidth() + 50, stock->getPosition().y - 7);
	transparentBox->addChild(stockArrowUp);

	stockPlusFive = new MenuItem(gameData, "Assets/Images/plus5.png", 30, 14);
	stockPlusFive->setPosition(stock->getPosition().x + stock->getWidth() / 2 + stockValue->getWidth() + 90, stock->getPosition().y - 7);
	transparentBox->addChild(stockPlusFive);

	SceneLabel *buyPrice = new SceneLabel("Buy Price ", 16, "sans");
	buyPrice->color = new Color(0, 0, 0, 255);
    buyPrice->depthTest = false;
    buyPrice->depthWrite = false;
	buyPrice->setPosition(buyPrice->getWidth() / 2 + 75, stock->getPosition().y - stock->getHeight() - 10);
	transparentBox->addChild(buyPrice);

	char* buyPriceString = new char[5];
	sprintf(buyPriceString, "%d", resources->getBuyPrice(type));
	SceneLabel *buyPriceValue = new SceneLabel(buyPriceString, 16, "sans");
	buyPriceValue->color = new Color(0, 0, 0, 255);
    buyPriceValue->depthTest = false;
    buyPriceValue->depthWrite = false;
	buyPriceValue->setPosition((buyPrice->getWidth() / 2) + (buyPriceValue->getWidth() / 2) + 16, 0);
	buyPrice->addChild(buyPriceValue);

	SceneLabel *sellPrice = new SceneLabel("Sell Price ", 16, "sans");
	sellPrice->color = new Color(0, 0, 0, 255);
    sellPrice->depthTest = false;
    sellPrice->depthWrite = false;
	sellPrice->setPosition(sellPrice->getWidth() / 2 + 75, buyPrice->getPosition().y - buyPrice->getHeight() - 10);
	transparentBox->addChild(sellPrice);

	char* valueString = new char[5];
	sprintf(valueString, "%d", resources->getSellPrice(type));
	sellPriceValue = new SceneLabel(valueString, 16, "sans");
	sellPriceValue->color = new Color(0, 0, 0, 255);
    sellPriceValue->depthTest = false;
    sellPriceValue->depthWrite = false;
	sellPriceValue->setPosition((sellPrice->getWidth() / 2) + (sellPriceValue->getWidth() / 2) + 18, 0);
	sellPrice->addChild(sellPriceValue);

	sellPriceArrowUp = new MenuItem(gameData, "Assets/Images/plus1.png", 30, 14);
	sellPriceArrowUp->setPosition(sellPrice->getPosition().x + sellPrice->getWidth() / 2 + sellPriceValue->getWidth() + 28, sellPrice->getPosition().y - 7);
	transparentBox->addChild(sellPriceArrowUp);
	
	sellPriceArrowDown = new MenuItem(gameData, "Assets/Images/minus1.png", 30, 14);
	sellPriceArrowDown->setPosition(sellPrice->getPosition().x + sellPrice->getWidth() / 2 + sellPriceValue->getWidth() + 68, sellPrice->getPosition().y - 7);
	transparentBox->addChild(sellPriceArrowDown);
}

void ResourceItem::deactivateStocks() {
	stockArrowUp->visible = false;
	stockPlusFive->visible = false;
	stockArrowUp->removeAllHandlers();
	stockPlusFive->removeAllHandlers();
}

void ResourceItem::handleEvent(Event *e) {

	 if(e->getDispatcher() == sellPriceArrowUp) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			gameData->clickSound->Play(false);
			char* valueString = new char[5];
			resources->addToSellPrice(type, 1);
			sprintf(valueString, "%d", resources->getSellPrice(type));
			sellPriceValue->setText(valueString);
			break;
			}
		}
	}
	else if(e->getDispatcher() == sellPriceArrowDown) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			gameData->clickSound->Play(false);
			char* valueString = new char[5];
			resources->addToSellPrice(type, -1);
			sprintf(valueString, "%d", resources->getSellPrice(type));
			sellPriceValue->setText(valueString);
			break;
			}
		}
	}
	else if(e->getDispatcher() == stockArrowUp) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			if (resources->getGold() >= resources->getBuyPrice(type))
			{
				gameData->buyStockSound->Play(false);
				char* valueString = new char[5];
				resources->addToAmnt(type, 1);
				sprintf(valueString, "%d", resources->getAmnt(type));
				stockValue->setText(valueString);
				resources->removeGold(resources->getBuyPrice(type));
			}
			break;
			}
		}
	}
	else if(e->getDispatcher() == stockPlusFive) {
		switch (e->getEventCode()) {
			{case UIEvent::CLICK_EVENT:
			if (resources->getGold() >= resources->getBuyPrice(type) * 5)
			{
				gameData->buyStockSound->Play(false);
				char* valueString = new char[5];
				resources->addToAmnt(type, 5);
				sprintf(valueString, "%d", resources->getAmnt(type));
				stockValue->setText(valueString);
				resources->removeGold(5 * resources->getBuyPrice(type));
			}
			break;
			}
		}
	}
}