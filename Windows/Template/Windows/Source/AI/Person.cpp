
#include "Person.h"
#include "FSM.h"
#include <iostream>
#include <random>
//#include <chrono>

Person::Person(String name, Person::Intent intent, String file, Number width, Number height, bool merchant) : SceneSprite(file, width, height) {
   
   core = GameData::getInstance()->getCore();
   scene = GameData::getInstance()->getScene3D();
   moved = false;
   takeNextStep = false;
   paused = false;
   id = GameData::getInstance()->getNextPersonID();
   map = GameData::getInstance()->getGameMap();
   this->name = name;
   fileName = file;
   health = 100;
   level = 1;
   walkSpeed = 7;
   table = NULL;
   isMoving = false;
   drink = TavernResources::EMPTY;
   isHighlighted = false;
   orderedFood = false;
   currentTable = -1;
   this->intent = intent;
   this->merchant = merchant;
   
   if (merchant)
   {
      this->setColor(0, .9, 1, 1);
   }
   
   srand(unsigned(time(0)));
   
   std::random_device rd;
   
   //textBubble = 0;
   //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine generator(rd.operator()());
   
   std::normal_distribution<double> hungerDist(50, 20);
   std::normal_distribution<double> thirstDist(50, 20);
   std::normal_distribution<double> maxPurchaseDist(0, 0);
   
   std::normal_distribution<double> maxPurchaseDistPoor(8, 1);
   std::normal_distribution<double> maxPurchaseDistCommon(12, 2);
   std::normal_distribution<double> maxPurchaseDistRich(20, 2);
   int status = rand() % 100;
   
   if(status >= 0 && status <= 15)
      maxPurchaseDist = maxPurchaseDistRich;
   else if (status > 15 && status <= 50)
      maxPurchaseDist = maxPurchaseDistCommon;
   else
      maxPurchaseDist = maxPurchaseDistPoor;
   
   hunger = hungerDist(generator);
   if (hunger < 0)
      hunger = 0;
   if (hunger > 100)
      hunger = 100;
   
   thirst = thirstDist(generator);
   if (thirst < 0)
      thirst = 0;
   if (thirst > 100)
      thirst = 100;
   
   //maxPurchase = (rand() % 2 + 6) + (100 - thirst)/20;
   maxPurchase = maxPurchaseDist(generator);
   
   happiness = (thirst + hunger) / VAR_NUM;
   
   if (intent == EMPTY)
   {
      findIntent();
   }
   
   pathfinder = new AStar(map, 40, false);
   brain = new FSM(this);
   this->setMaterialByName(file);
   this->setScale(0.05, 0.05);
   this->billboardMode = true;
   this->setPosition(20 * 5, 3.5, 0 * 5);
   this->alphaTest = true;
   this->depthTest = true;
   this->depthWrite = true;
   
   box = new Box(id, ScenePrimitive::TYPE_BOX, 3, 5.5, 3);
   box->depthTest = false;
   box->depthWrite = true;
   box->setPosition(this->getPosition().x, 3.5, this->getPosition().z);
   box->setColor(1, 1, 1, 0);
   box->billboardMode = true;
   scene->addCollisionChild(box);
   
   shadow = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 2.5, 2.5, 20);
   shadow->setPitch(-90);
   shadow->depthTest = true;
   shadow->depthWrite = true;
   shadow->setPosition(this->getPosition().x, 0.6, this->getPosition().z);
   shadow->setMaterialByName("SolidMaterial");
   shadow->setColor(1, 1, 1, 0.3);
   scene->addChild(shadow);
   
   //This needs to be moved to person type classes
   this->addAnimation("spin", "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15", 0.5);
   //this->playAnimation("spin", 0, false);
   this->addAnimation("botLeft", "1", 0.5);
   this->addAnimation("topLeft", "3", 0.5);
   this->addAnimation("topRight", "5", 0.5);
   this->addAnimation("botRight", "7", 0.5);
   
   this->addAnimation("hBotLeft", "9", 0.5);
   this->addAnimation("hTopLeft", "11", 0.5);
   this->addAnimation("hTopRight", "13", 0.5);
   this->addAnimation("hBotRight", "15", 0.5);
   
   this->addAnimation("portrait", "7", 1);
   
   this->playAnimation("botLeft", 1, false);
   
   leaveTimer = new Timer(false, 10000000);
   repTimer = new Timer(false, 100000000000);

   TavernResources::getInstance()->addPerson(this);
}

Person::~Person() {
   scene->removeEntity(this);
   scene->removeEntity(shadow);
   scene->removeEntity(box);
   TavernResources::getInstance()->decrementCapacity();
}

int Person::getID() {
   return id;
}

void Person::movePerson(Number x, Number y, Number z) {
   this->setPosition(x, y, z);
   box->setPosition(x, 3.5, z);
   shadow->setPosition(x, 0.6, z);
   
   //if (textBubble)
   //textBubble->setPosition(x + 4, textBubble->getPosition().y, z);
}

/*void Person::setTextBubble(MenuLabel *label)
 {
 this->textBubble = label;
 }*/

bool Person::getMerchant()
{
   return merchant;
}

void Person::findIntent() {
   if (intent != GROUP) {
      if (thirst < 25) { //hunger >= thirst
         intent = HUNGRY;
      }
      else if (thirst < 99) {
         intent = THIRSTY;
      }
      else if (thirst >= 99) { //hunger > 70 && thirst > 70
         intent = LEAVE;
      }
      else {
         intent = WANDER;
      }
   }
   else {
      intent = EMPTY;
   }
}

void Person::setHunger(int h) {
   if (h > 100) {
      hunger = 100;
   }
   else if (h < 0) {
      hunger = 0;
   }
   else {
      hunger = h;
   }
}
int Person::getHunger() {
   return hunger;
}
void Person::setThirst(int t) {
   if (t > 100) {
      thirst = 100;
   }
   else if (t < 0) {
      thirst = 0;
   }
   else {
      thirst = t;
   }
}
int Person::getThirst() {
   return thirst;
}

int Person::getFun()
{
   return fun;
}

void Person::addFun(int addFun)
{
   if (fun + addFun > 100)
      fun = 100;
   
   else
      fun += addFun;
}

void Person::removeFun(int removeFun)
{
   if (fun - removeFun < 0)
      fun = 0;
   
   else
      fun -= removeFun;
}

int Person::getAnger()
{
   return anger;
}

void Person::addAnger(int addAnger)
{
   if (anger + addAnger > 100)
      anger = 100;
   
   else
      anger += addAnger;
}

void Person::removeAnger(int removeAnger)
{
   if (anger - removeAnger < 0)
      anger = 0;
   
   else
      anger -= removeAnger;
}

bool Person::moveTo(int tx, int tz) {
   if (!moved) {
      //cout << "MOVING TO: " << tx << " " << tz << endl;
      steps = pathfinder->findPath(this->getPosition().x/5, this->getPosition().z/5, tx, tz);
      if (!steps.empty()) {
         dest = steps.back();
         moved = true;
         takeNextStep = true;
         isMoving = true;
      }
   }
   return moved;
}

bool Person::hasDrink() {
   if (drink != TavernResources::EMPTY) {
      return true;
   }
   return false;
}

void Person::giveDrink(TavernResources::Items dr) {
   drink = dr;
}

int Person::getIntent() {
   return intent;
}

void Person::setIntent(Intent intention) {
   intent = intention;
}

void Person::getNextDir() {
	String temp;
   if (st.x*5 < this->getPosition().x) {
      dir.x = -1;
      (isHighlighted) ? temp = "hTopLeft" : temp = "topLeft";
      this->playAnimation(temp, 0, false);
   }
   else if (st.x*5 > this->getPosition().x) {
      dir.x = 1;
      (isHighlighted) ? temp = "hBotRight" : temp = "botRight";
      this->playAnimation(temp, 0, false);
   }
   else {
      dir.x = 0;
   }
   
   if (st.z*5 < this->getPosition().z) {
      dir.z = -1;
      (isHighlighted) ? temp = "hTopRight" : temp = "topRight";
      this->playAnimation(temp, 0, false);
   }
   else if (st.z*5 > this->getPosition().z) {
      dir.z = 1;
      (isHighlighted) ? temp = "hBotLeft" : temp = "botLeft";
      this->playAnimation(temp, 0, false);
   }
   else {
      dir.z = 0;
   }
   
}

void Person::setDir(String newDir) {
   String temp;
   
   if (newDir == "topLeft") {
      (isHighlighted) ? temp = "hTopLeft" : temp = "topLeft";
      this->playAnimation(temp, 0, false);
   }
   else if (newDir == "topRight") {
      (isHighlighted) ? temp = "hTopRight" : temp = "topRight";
      this->playAnimation(temp, 0, false);
   }
   else if (newDir == "bottomLeft") {
      (isHighlighted) ? temp = "hBotLeft" : temp = "botLeft";
      this->playAnimation(temp, 0, false);
   }
   else if (newDir == "bottomRight") {
      (isHighlighted) ? temp = "hBotRight" : temp = "botRight";
      this->playAnimation(temp, 0, false);
   }
}

void Person::interruptIntent() {
   brain->interruptState();
}

void Person::useStep() {
   getNextDir();
   
   this->movePerson(this->getPosition().x + (dir.x * walkSpeed) * core->getElapsed(), this->getPosition().y, this->getPosition().z + (dir.z * walkSpeed) * core->getElapsed());
   //cout << this->getPosition().x << " " << this->getPosition().z << endl;
   //cout << dir.x << " " << dir.z << endl;
   if (dir.x == -1 && this->getPosition().x <= st.x*5) {
      this->movePerson(st.x*5, this->getPosition().y, this->getPosition().z);
      takeNextStep = true;
   }
   else if (dir.x == 1 && this->getPosition().x >= st.x*5) {
      this->movePerson(st.x*5, this->getPosition().y, this->getPosition().z);
      takeNextStep = true;
   }
   
   if (dir.z == -1 && this->getPosition().z <= st.z*5) {
      this->movePerson(this->getPosition().x, this->getPosition().y, st.z*5);
      takeNextStep = true;
   }
   else if (dir.z == 1 && this->getPosition().z >= st.z*5) {
      this->movePerson(this->getPosition().x, this->getPosition().y, st.z*5);
      takeNextStep = true;
   }
   
   if (dir.x == 0 && dir.z == 0)
      takeNextStep = true;
}

void Person::setTable(Table* table) {
   this->table = table;
}

bool Person::isOnDest() {
   if (this->getPosition().x == dest.x*5
       && this->getPosition().z == dest.z*5) {
      return true;
   }
   return false;
}

void Person::Update() {
	if (!paused) {
		leaveTimer->Pause(false);
	   if (leaveTimer->getElapsedf() >= (rand() % 60 + 80))
		{
		if (intent != WAITER) {
		setIntent(LEAVE);
		interruptIntent();
		}
			leaveTimer->Reset();
		}
   
	   if (repTimer->getElapsedf() > 8)
	   {
		  TavernResources::getInstance()->changeHappinessRep(happiness - NEUTRAL_HAPPINESS);
		  repTimer->Reset();
	   }
   
	   if (moved) {
		  if (!isOnDest()) {
			 if (takeNextStep) {
				st = steps.front();
				//cout << "GRABBING: " << st.x << " " << st.z << endl;
				steps.pop_front();
				useStep();
				takeNextStep = false;
			 }
			 else {
				useStep();
			 }
		  }
		  else {
			 isMoving = false;
			 moved = false;
			 //CHECK HAPPINESS/ETC FOR NEW INTENT
			 //this->setIntent(THIRSTY);
		  }
	   }
	   brain->runActiveState();
	   SceneSprite::Update();
	}
	else
	{
		leaveTimer->Pause(true);
	}
}

MapTile *Person::getTileOn() {
   return map->getMapTile(st.x, st.z);
}

String Person::getFileName()
{
	return fileName;
}

int Person::getHealth()
{
	return health;
}

String Person::getName()
{
	return name;
}

int Person::getLevel()
{
	return level;
}

Table* Person::getTable() {
   return table;
}

int Person::getMaxPurchase()
{
   return maxPurchase;
}

int Person::getHappiness()
{
   return happiness;
}

void Person::calcHappiness()
{
   happiness = (thirst + hunger) / 2;
}

void Person::lowerThirst(int val)
{
   if (val > thirst)
      thirst = 0;
   
   else
      thirst -= val;
}