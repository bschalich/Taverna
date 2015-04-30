#include "FSM.h"

FSM::FSM(Person *person) {
   tavRes = TavernResources::getInstance();
   this->person = person;
   this->dialogue = Dialogue::getInstance();
   interruptCurrentState = false;
   srand((unsigned)time(0));
   dir[0] = 1;
   dir[1] = -1;
   dir[2] = 0;
   chairPos = Vector3(-1, 0, -1);
   createIntentLists();
   setIntent(person->getIntent());
   timer = new Timer(false, 3000);
   timer->Pause(true);
   waiterTimer = new Timer(false, 3000);
   waiterTimer->Pause(true);
   wanderMoving = false;
   runningState = false;
   
   drinkList[0] = TavernResources::MEAD;
   drinkList[1] = TavernResources::WINE;
   drinkList[2] = TavernResources::ALE;
   
   gameData = GameData::getInstance();
}

FSM::~FSM() {
   delete timer;
}

void FSM::setIntent(int in) {
   chairPos = Vector3(-1, 0, -1);
   switch (in) {
      case Person::WANDER:
         stateList = wanderIntent;
         setNextState();
         break;
      case Person::BARKEEP:
         stateList = barkeepIntent;
         setNextState();
         break;
      case Person::THIRSTY:
         stateList = thirstyIntent;
         setNextState();
         break;
      case Person::HUNGRY:
         stateList = sitIntent;
         setNextState();
         break;
      case Person::LEAVE:
         stateList = leaveIntent;
         setNextState();
         break;
      case Person::WAITER:
         stateList = waiterIntent;
         setNextState();
         break;
      case Person::GROUP:
         stateList = groupIntent;
         setNextState();
         break;
      default:
         stateList = stopIntent;
         setNextState();
         break;
   }
}

void FSM::createIntentLists() {
   //State states[3] = {STOP, WANDER, BLANK};
   //states[rand() % 3]
   
   //WANDER INTENT
   wanderIntent.clear();
   wanderIntent.push_back(STOP);
   wanderIntent.push_back(WANDER);
   //wanderIntent.push_back(WANDER);
   //wanderIntent.push_back(LEAVE);
   
   barkeepIntent.clear();
   barkeepIntent.push_back(STOP);
   barkeepIntent.push_back(WANDER1);
   
   //STOP INTENT
   stopIntent.clear();
   stopIntent.push_front(STOP);
   
   //LEAVE INTENT
   leaveIntent.clear();
   leaveIntent.push_back(STOP);
   leaveIntent.push_back(WANDER);
   leaveIntent.push_front(LEAVE);
   
   //THIRSTY INTENT
   thirstyIntent.clear();
   thirstyIntent.push_back(STOP);
   thirstyIntent.push_back(WANDER);
   thirstyIntent.push_back(MOVE_TO_BAR);
   thirstyIntent.push_back(ORDER_FROM_BAR);
   thirstyIntent.push_back(WANDER);
   
   //SIT INTENT
   sitIntent.clear();
   sitIntent.push_back(STOP);
   sitIntent.push_back(SIT_AT_TABLE);
   sitIntent.push_back(STOP);
   sitIntent.push_back(ORDER_FROM_KITCHEN);
   //sitIntent.push_back(WAIT_FOR_FOOD);
   sitIntent.push_back(STOP);
   
   //WAITER INTENT
   waiterIntent.clear();
   waiterIntent.push_back(STOP);
   waiterIntent.push_back(MOVE_TO_PATRON);
   waiterIntent.push_back(WAITORSTOP);
   waiterIntent.push_back(MOVE_TO_KITCHEN);
   waiterIntent.push_back(STOP);
   waiterIntent.push_back(SERVE_PATRON);
   waiterIntent.push_back(WAITORSTOP);
   //waiterIntent.push_back(MOVE_TO_KITCHEN);
   
   //GROUP INTENT
   groupIntent.clear();
   groupIntent.push_back(STOP);
   groupIntent.push_back(SIT_AT_DEFINED_TABLE);
   groupIntent.push_back(STOP);
   groupIntent.push_back(ORDER_FROM_KITCHEN);
   groupIntent.push_back(STOP);
   
}

void FSM::setNextState() {
   if (!stateList.empty()) {
      currentState = stateList.front();
      stateList.pop_front();
   }
   else {
      createIntentLists();
      if (person->getIntent() != Person::BARKEEP && person->getIntent() != Person::WAITER && person->getIntent() != Person::GROUP) {
         person->findIntent();
      }
      setIntent(person->getIntent());
   }
   //std::cout << person->getName().c_str() << " " <<  currentState << std::endl;
}

void FSM::interruptState() {
   interruptCurrentState = true;
}

void FSM::runActiveState() {
   if (interruptCurrentState) {
      createIntentLists();
      setIntent(person->getIntent());
      interruptCurrentState = false;
      runningState = false;
   }
   else {
      switch (currentState) {
            
         {case WANDER:
            Number x = rand() % 5 + 1;
            Number z = rand() % 5 + 1;
            int xDir = dir[rand() % 3];
            int zDir = dir[rand() % 3];
            if (!person->isMoving) {
               resetTable();
               if (!wanderMoving) {
                  person->moveTo(person->getPosition().x/5 + xDir*x, person->getPosition().z/5 + zDir*z);
                  wanderMoving = true;
                  //person->setThirst(person->getThirst() - 10);
                  //person->setHunger(person->getHunger() - 5);
               }
               else if (wanderMoving && !person->isMoving) {
                  wanderMoving = false;
                  setNextState();
               }
            }
            break;}
            
         {case WANDER1:
            Number x = rand() % 2 + 1;
            Number z = rand() % 2 + 1;
            int xDir = dir[rand() % 3];
            int zDir = dir[rand() % 3];
            if (!person->isMoving) {
               if (!wanderMoving) {
                  person->moveTo(person->getPosition().x/5 + xDir*x, person->getPosition().z/5 + zDir*z);
                  wanderMoving = true;
               }
               else if (wanderMoving && !person->isMoving) {
                  wanderMoving = false;
                  setNextState();
               }
            }
            break;}
            
         {case STOP:
            if (timer->isPaused()) {
               timer->Pause(false);
            }
            if (timer->getElapsedf() >= rand() % 3 + 1) {
               timer->Reset();
               timer->Pause(true);
               setNextState();
            }
            break;}
            
         {case WAITORSTOP:
            if (waiterTimer->isPaused()) {
               waiterTimer->Pause(false);
            }
            if (waiterTimer->getElapsedf() >= rand() % 2 + 2) {
               waiterTimer->Reset();
               waiterTimer->Pause(true);
               setNextState();
            }
            break;}
            
         {case LEAVE:
            if (person->getPosition().z/5 != 0) { //Vector3(20, person->getPosition().y/5, 0)
               if (!runningState) {
                  std::cout << "LEAVING" << std::endl;
                  runningState = true;
                  person->moveTo(20, 0);
                  resetTable();
                  
                  //Display bubble information
                  if (rand() % 2 == 0)
                  {
                     new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", dialogue->getLeaveDialogue(), 0, person);
                  }
               }
            }
            else {
               //std::cout << "DELETE" << std::endl;
               //delete person pointer (UNLESS THEY'RE A REGULAR??? then keep them in the list)
               //delete person;
               GameData::getInstance()->getScene3D()->removeEntity(person);
               GameData::getInstance()->getScene3D()->removeEntity(person->shadow);
               TavernResources::getInstance()->decrementCapacity();
               gameData->doorCloseSound->Play(false);
            }
            break;}
            
         {case MOVE_TO_BAR:
            int patronTileSize = tavRes->barList.front()->patronTiles.size();
            int randomTile = rand() % patronTileSize;
            if (person->getPosition().x/5 != tavRes->barList.front()->patronTiles[randomTile].x || person->getPosition().z/5 != tavRes->barList.front()->patronTiles[randomTile].z) {
               if (!runningState) {
                  if (person->getTileOn()->getObject() != NULL && person->getTileOn()->getObject()->getFilename() == "chair_wood.mesh" && person->currentTable > -1) {
                     //person->getTileOn()->occupied = false;
                     /*tavRes->tablesList[person->currentTable]->openChairs.push_back(Vector3(person->getPosition().x/5, 0, person->getPosition().z/5));
                      tavRes->tablesList[person->currentTable]->numChairs++;*/
                     resetTable();
                  }
                  //std::cout << tavRes->barList.front()->patronTiles[randomTile].x << " " << tavRes->barList.front()->patronTiles[randomTile].z << std::endl;
                  if (tavRes->barList.front()->patronTiles[randomTile].z != 0) {
                     if (!person->moveTo(tavRes->barList.front()->patronTiles[randomTile].x , tavRes->barList.front()->patronTiles[randomTile].z )) {
                        std::cout << "FALSE" << std::endl;
                        runningState = false;
                     }
                     else {
                        runningState = true;
                        //Display bubble information
                        if (rand() % 3 == 0)
                        {
                           new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", dialogue->getThirstyDialogue(), 0, person);
                        }
                     }
                  }
               }
            }
            else {
               person->playAnimation(tavRes->barList.front()->getBarDir(person->getPosition()), 3, false);
               runningState = false;
               setNextState();
            }
            break;}
            
         {case MOVE_TO_KITCHEN:
            if (!runningState) {
               runningState = true;
               person->moveTo(tavRes->barList.front()->barPos.x - 1, tavRes->barList.front()->barPos.z);
            }
            else if (person->getPosition().x/5 == tavRes->barList.front()->barPos.x - 1 && person->getPosition().z/5 == tavRes->barList.front()->barPos.z) {
               person->playAnimation("botRight", 7, false);
               runningState = false;
               setNextState();
            }
            break;}
            
         {case MOVE_TO_PATRON:
            if (!runningState) {
               if (!tavRes->openOrders.empty()) {
                  currentOrderer = tavRes->openOrders.front();
                  if (currentOrderer->getTable() != NULL) {
                     tavRes->closedOrders.push_back(currentOrderer);
                     tavRes->openOrders.pop_front();
                     runningState = true;
                     //move to patrons table position
                     int xPos = currentOrderer->getTable()->waiterTile.x;
                     int zPos = currentOrderer->getTable()->waiterTile.z;
                     person->moveTo(xPos, zPos);
                  }
                  else {
                     interruptState();
                     if (tavRes->openOrders.empty()) {
                        stateList.push_back(MOVE_TO_KITCHEN);
                     }
                     else {
                        tavRes->openOrders.pop_front();
                     }
                     
                     break;
                  }
                  //Display bubble information
                  if (rand() % 3 == 0)
                  {
                     new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", dialogue->getWaitorWorkingDialogue(), 0, person);
                  }
               }
            }
            else if (currentOrderer != NULL && currentOrderer->getTable() != NULL) {
               if (person->getPosition().x/5 == currentOrderer->getTable()->waiterTile.x &&
                   person->getPosition().z/5 == currentOrderer->getTable()->waiterTile.z) {
                  person->playAnimation("botRight", 7, false);
                  runningState = false;
                  //place order in kitchen list
                  setNextState();
                  
                  //Display bubble information
                  new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", dialogue->getTakeOrderDialogue(), 0, person);
               }
            }
            else {
               interruptState();
               if (tavRes->openOrders.empty()) {
                  stateList.push_back(MOVE_TO_KITCHEN);
               }
               else {
                  tavRes->openOrders.pop_front();
               }
            }
            break;}
            
         {case SERVE_PATRON:
            if (!runningState) {
               if (!tavRes->closedOrders.empty()) {
                  currentOrderer = tavRes->closedOrders.front();
                  if (currentOrderer->getTable() != NULL) {
                     runningState = true;
                     int xPos = currentOrderer->getTable()->waiterTile.x;
                     int zPos = currentOrderer->getTable()->waiterTile.z;
                     person->moveTo(xPos, zPos);
                  }
                  else {
                     interruptState();
                     tavRes->closedOrders.pop_front();
                     if (tavRes->openOrders.empty()) {
                        stateList.push_back(MOVE_TO_KITCHEN);
                     }
                     
                     break;
                  }
               }
            }
            else if (currentOrderer != NULL && currentOrderer->getTable() != NULL) {
               if (person->getPosition().x/5 == currentOrderer->getTable()->waiterTile.x &&
                   person->getPosition().z/5 == currentOrderer->getTable()->waiterTile.z) {
                  person->playAnimation("botRight", 7, false);
                  runningState = false;
                  tavRes->closedOrders.pop_front();
                  TavernResources::Items drink = drinkList[rand() % 2];
                  String image;
                  
                  switch (drink)
                  {
                     case TavernResources::MEAD:
                        image = "Assets/Images/mug.png";
                        break;
                     case TavernResources::WINE:
                        image = "Assets/Images/wine.png";
                        break;
                     default:
                        image = "Assets/Images/mug.png";
                        break;
                  }
                  if (tavRes->getAmnt(drink) > 0) {
                     if (currentOrderer->getMaxPurchase() >= tavRes->getSellPrice(drink))
                     {
                        currentOrderer->giveDrink(drink);
                        tavRes->addToAmnt(drink, -1);
                        tavRes->addGold(tavRes->getSellPrice(drink));
                        currentOrderer->setThirst(currentOrderer->getThirst() + 40);
                        
                        char text[10];
                        sprintf(text, "-1   +$%d", tavRes->getSellPrice(drink));
                        new TextBubble(Vector3(currentOrderer->getPosition().x, 0, currentOrderer->getPosition().z), image, text, 0, currentOrderer);
                        
                        runningState = false;
                        currentOrderer->giveDrink(TavernResources::EMPTY);
                        sitIntent.push_front(ORDER_FROM_KITCHEN);
                        
                        //Display bubble information
                        new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", dialogue->getGiveOrderDialogue(), 0, person);
                     }
                     else
                     {
                        printf("REJECTED - To Expensive\n");
                        
                        char text[20];
                        sprintf(text, "Too Expensive");
                        new TextBubble(Vector3(currentOrderer->getPosition().x, 0, currentOrderer->getPosition().z), image, text, 0, currentOrderer);
                        currentOrderer->lowerThirst(20);
                        
                        runningState = false;
                        currentOrderer->giveDrink(TavernResources::EMPTY);
                        sitIntent.push_front(ORDER_FROM_KITCHEN);
                     }
                  }
                  else {
                     printf("REJECTED - Out of stock\n");
                     //printf("A\n");
                     
                     char text[20];
                     sprintf(text, "Out of Stock");
                     new TextBubble(Vector3(currentOrderer->getPosition().x, 0, currentOrderer->getPosition().z), image, text, 0, currentOrderer);
                     currentOrderer->lowerThirst(20);
                     
                     runningState = false;
                     currentOrderer->giveDrink(TavernResources::EMPTY);
                     sitIntent.push_front(ORDER_FROM_KITCHEN);
                  }
                  setNextState();
                  if (tavRes->openOrders.empty()) {
                     stateList.push_back(MOVE_TO_KITCHEN);
                  }
               }
            }
            else {
               interruptState();
               tavRes->closedOrders.pop_front();
               if (tavRes->openOrders.empty()) {
                  stateList.push_back(MOVE_TO_KITCHEN);
               }
               
            }
            break;}
            
         {case ORDER_FROM_BAR:
            if (!person->hasDrink()) {
               if (!runningState) {
                  TavernResources::Items drink = drinkList[rand() % 2];
                  String image;
                  switch (drink)
                  {
                     case TavernResources::MEAD:
                        image = "Assets/Images/mug.png";
                        break;
                     case TavernResources::WINE:
                        image = "Assets/Images/wine.png";
                        break;
                     default:
                        image = "Assets/Images/mug.png";
                        break;
                  }
                  
                  printf("maxPurchase: %d\n", person->getMaxPurchase());
                  printf("buyPrice: %d\n", tavRes->getSellPrice(drink));
                  if (tavRes->getAmnt(drink) > 0)
                  {
                     if (person->getMaxPurchase() >= tavRes->getSellPrice(drink))
                     {
                        printf("BOUGHT\n");
                        person->giveDrink(drink);
                        tavRes->addToAmnt(drink, -1);
                        tavRes->addGold(tavRes->getSellPrice(drink));
                        person->setThirst(person->getThirst() + 10);
                        person->calcHappiness();
                        
                        char text[20];
                        sprintf(text, "-1   +$%d", tavRes->getSellPrice(drink));
                        new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), image, text, 0, person);
                        
                        runningState = false;
                        person->giveDrink(TavernResources::EMPTY);
                        setNextState();
                     }
                     else
                     {
                        printf("REJECTED - Too Expensive\n");
                        //printf("A\n");
                        
                        char text[20];
                        sprintf(text, "Too Expensive");
                        new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), image, text, 0, person);
                        person->lowerThirst(20);
                        
                        runningState = false;
                        person->giveDrink(TavernResources::EMPTY);
                        setNextState();
                        
                     }
                  }
                  else {
                     printf("REJECTED - out of stock\n");
                     //printf("A\n");
                     
                     char text[20];
                     sprintf(text, "Out of Stock");
                     new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), image, text, 0, person);
                     person->lowerThirst(20);
                     
                     runningState = false;
                     person->giveDrink(TavernResources::EMPTY);
                     setNextState();
                     
                  }
               }
            }
            else {
               runningState = false;
               person->giveDrink(TavernResources::EMPTY);
               setNextState();
            }
            break;}
            
            //SIT AT A TABLE
         {case SIT_AT_TABLE:
            if (!runningState && !tavRes->tablesList.empty()) {
               tableIndex = (int)(rand() % tavRes->tablesList.size());
               std::cout << "SIZE: " << tavRes->tablesList.size() << std::endl;
               std::cout << person->getName().c_str() << " " << tableIndex << std::endl;
               if (!tavRes->tablesList[tableIndex]->openChairs.empty()) {
                  //GameData::getInstance()->getGameMap()->getMapTile(tavRes->openChairs.front().x, tavRes->openChairs.front().z)->occupied = false;
                  
                  runningState = true;
                  int chairIndex = (int) (rand() % tavRes->tablesList[tableIndex]->numChairs);
                  chairPos.x = tavRes->tablesList[tableIndex]->openChairs[chairIndex].x;
                  chairPos.z = tavRes->tablesList[tableIndex]->openChairs[chairIndex].z;
                  person->moveTo(chairPos.x,chairPos.z);
                  std::cout << "CHAIR POS: " << chairPos.x << " " << chairPos.z << std::endl;
                  //GameData::getInstance()->getGameMap()->getMapTile(tavRes->openChairs.front().x, tavRes->openChairs.front().z)->occupied = true;
                  tavRes->tablesList[tableIndex]->openChairs.erase(tavRes->tablesList[tableIndex]->openChairs.begin() + chairIndex);
                  tavRes->tablesList[tableIndex]->numChairs--;
                  person->currentTable = tableIndex;
                  person->setTable(tavRes->tablesList[tableIndex]);
                  tavRes->tablesList[tableIndex]->reserved = true;
                  
                  //Display bubble information
                  if (rand() % 3 == 0)
                  {
                     new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", "I'm hungry", 0, person);
                  }
               }
            }// && person->getTileOn()->getObject()->getFilename() == "chair_wood.mesh"
            else if (person->getPosition().x == chairPos.x*5 && person->getPosition().z == chairPos.z*5) {
               person->setTable(tavRes->tablesList[tableIndex]);
               String dir = tavRes->tablesList[tableIndex]->getSitDir(chairPos);
               person->setDir(dir);
               runningState = false;
               setNextState();
            }
            break;}
            
         {case SIT_AT_DEFINED_TABLE:
            if (!runningState && person->getTable() != NULL) {
               if (!person->getTable()->openChairs.empty()) {
                  //GameData::getInstance()->getGameMap()->getMapTile(tavRes->openChairs.front().x, tavRes->openChairs.front().z)->occupied = false;
                  
                  runningState = true;
                  int chairIndex = (int) (rand() % person->getTable()->numChairs);
                  chairPos.x = person->getTable()->openChairs[chairIndex].x;
                  chairPos.z = person->getTable()->openChairs[chairIndex].z;
                  person->moveTo(chairPos.x,chairPos.z);
                  
                  //GameData::getInstance()->getGameMap()->getMapTile(tavRes->openChairs.front().x, tavRes->openChairs.front().z)->occupied = true;
                  person->getTable()->openChairs.erase(person->getTable()->openChairs.begin() + chairIndex);
                  person->getTable()->numChairs--;
                  person->currentTable = tableIndex;
                  
                  //Display bubble information
                  if (rand() % 3 == 0)
                  {
                     new TextBubble(Vector3(person->getPosition().x, 0, person->getPosition().z), "", "Let's get a table", 0, person);
                  }
               }
            }// && person->getTileOn()->getObject()->getFilename() == "chair_wood.mesh"
            else if (person->getPosition().x == chairPos.x*5 && person->getPosition().z == chairPos.z*5) {
               String dir = person->getTable()->getSitDir(chairPos);
               person->setDir(dir);
               runningState = false;
               setNextState();
            }
            break;}
            
         {case ORDER_FROM_KITCHEN:
            if (!runningState && chairPos.x != -1 && (!person->hasDrink() || !person->orderedFood)) {
               tavRes->openOrders.push_back(person);
               person->orderedFood = true;
               runningState = true;
            }
            else if (person->hasDrink()) {
               runningState = false;
               setNextState();
            }
            break;}
            
         {case WAIT_FOR_FOOD:
            if (!runningState) {
               if (!person->hasDrink()) {
                  runningState = false;
               }
               else {
                  runningState = true;
                  setNextState();
               }
            }
            break;}
      }
   }
}

void FSM::resetTable() {
   if (person->getTable() != NULL) {
      person->currentTable = -1;
      person->getTable()->reset();
      person->getTable()->reserved = false;
      person->setTable(NULL);
   }
}