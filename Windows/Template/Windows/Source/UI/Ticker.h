#ifndef __Taverna__Ticker__
#define __Taverna__Ticker__

class MenuLabel;

#include "Polycode.h"
#include "PolycodeUI.h"
#include "MenuImage.h"
#include "MenuLabel.h"
#include "TavernResources.h"
#include "GameData.h"

#include <iostream>
#include <vector>

using namespace Polycode;

class Ticker : public EventHandler {
public:
   Ticker(MenuImage *parent);
   ~Ticker();

   void handleEvent(Event *e);
   
   void updateTickerGold();
   void checkOutOfStock();
   void checkCapacity();
   void setVisible(bool val);
   
private:

	TavernResources *resources;

   bool gold750;
   bool gold1000;
   bool outOfMead;
   bool outOfWine;
   bool atMaxCap;

   vector<MenuLabel*> tickers;
   void shiftTicker();
   MenuLabel* createTickerItem(String s, int size, String font);
   MenuImage *tickerBar;
};

#endif