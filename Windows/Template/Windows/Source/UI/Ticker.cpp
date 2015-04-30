#include "Ticker.h"
#define TICKERFONTSIZE 18

Ticker::Ticker(MenuImage *parent) : EventHandler() {

   gold750 = false;
   gold1000 = false;
   outOfMead = false;
   outOfWine = false;
   atMaxCap = false;

   GameData::getInstance()->getCore()->addEventListener(this, Event::RESOURCE_CHANGE_EVENT);

   resources = TavernResources::getInstance();

    tickerBar = new MenuImage("Assets/Images/tickerbg.png", 690, 100);
	tickerBar->setPosition(0, parent->getHeight(), 0);
    tickerBar->setPositions(0, parent->getHeight());
	parent->addChild(tickerBar);

	tickers.push_back(new MenuLabel("Welcome to Taverna", TICKERFONTSIZE, "sans"));
	tickers.push_back(new MenuLabel("This is a ticker", TICKERFONTSIZE, "sans"));
	tickers.push_back(new MenuLabel("that will display important information", TICKERFONTSIZE, "sans"));
	
	for (int i = 0; i < tickers.size(); i++) {
		tickerBar->addChild(tickers[i]);
		tickers[i]->setPosition(Vector3((tickers[i]->getWidth() / 2) + 17, tickerBar->getHeight() - (26 * i) - 25 ,0));
		tickers[i]->color = new Color(0, 0, 0, 255);
		//tickers[i]->visible = true;
		//tickers[i]->depthTest = false;
		//tickers[i]->depthWrite = false;
	}
}

Ticker::~Ticker() {
}

void Ticker::handleEvent(Event *e) {
	if (e->getEventCode() == Event::RESOURCE_CHANGE_EVENT) {
		updateTickerGold();
		checkOutOfStock();
		checkCapacity();
	}
}

void Ticker::checkCapacity()
{
	if (!atMaxCap && resources->getCapacity() >= resources->getMaxCapacity())
	{
		createTickerItem("Tavern at Max Capacity", TICKERFONTSIZE, "sans");
		atMaxCap = true;
	}
	else if (atMaxCap && resources->getCapacity() < resources->getMaxCapacity())
	{
		atMaxCap = false;
	}
}

void Ticker::checkOutOfStock()
{
	if (!outOfMead && resources->getAmnt(resources->MEAD) < 1) {
		createTickerItem("Out of Mead", TICKERFONTSIZE, "sans");
		outOfMead = true;
	}
	else if (outOfMead && resources->getAmnt(resources->MEAD) > 0) {
		outOfMead = false;
	}

	if (!outOfWine && resources->getAmnt(resources->WINE) < 1) {
		createTickerItem("Out of Wine", TICKERFONTSIZE, "sans");
		outOfWine = true;
	}
	else if (outOfWine && resources->getAmnt(resources->WINE) > 0) {
		outOfWine = false;
	}
}

void Ticker::updateTickerGold()
{
	/*int gold = resources->getGold();
	if (!gold750 && gold >= 750)
	{
		createTickerItem("Gold supply has surpassed 750!", TICKERFONTSIZE, "sans");
		gold750 = true;
	}
	else if (!gold1000 && gold >= 1000)
	{
		createTickerItem("Gold supply has surpassed 1000!", TICKERFONTSIZE, "sans");
		gold1000 = true;
	}*/
}

MenuLabel* Ticker::createTickerItem(String s, int size, String font)
{
	MenuLabel *newTicker = new MenuLabel(s, size, font);
	tickers.push_back(newTicker);
	tickerBar->addChild(newTicker);
	Number x = newTicker->getWidth() / 2 + 17;
	Number y = tickers[tickers.size() - 2]->getPosition().y - 26;
	newTicker->setPosition(Vector3(x, y, 0));
	newTicker->color = new Color(0, 0, 0, 255);
	shiftTicker();
	return newTicker;
}

void Ticker::shiftTicker()
{
	tickerBar->removeChild(tickers[tickers.size() - 4]);
	for (int i = tickers.size() - 3; i < tickers.size(); i++)
	{
		tickers[i]->moveFromCurrent(0, 26, 0, 1);
	}
}

void Ticker::setVisible(bool val)
{
	tickerBar->visible = val;
}