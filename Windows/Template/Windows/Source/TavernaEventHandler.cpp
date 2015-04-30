#include "TavernaEventHandler.h"
#include <iostream>

/****
 * This class handles all events for the game.  When mode is true, game events will be handled.
 * When mode is false, menu events will be handled.
 */
TavernaEventHandler::TavernaEventHandler() : EventHandler() {
   gameData = GameData::getInstance();
   map = gameData->getGameMap();
   core = gameData->getCore();
   scene = gameData->getScene3D();
   scene2D = gameData->getScene2D();
   mode = gameData->getGameMode();
   maxZoomIn = 30;
   maxZoomOut = 125;
   ID = 1;
   hoverPerson = NULL;
   
   gameStart = true;
   cameraEvent = true;
   cameraZoomEvent = false;
   mouseDown = false;
   saveTile = NULL;
   rend = CoreServices::getInstance()->getRenderer();
   
   scene->getDefaultCamera()->setOrthoMode(true);
   scene->getDefaultCamera()->setOrthoSize(50, 50); //125, 125
   scene->getDefaultCamera()->setPosition(150, 150, 150);
   scene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));
   
   core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
   //core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
   core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
   core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
   core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
   core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
   
   ID = 0;
   deleter = new Deleter();
   door = new Door(gameData->getGameMap());
   //core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
   //core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
}

TavernaEventHandler::~TavernaEventHandler() {
   
}

void TavernaEventHandler::handleEvent(Event *e) {
   
   if(e->getDispatcher() == core->getInput()) {
      //Use this for key events
      InputEvent *inputEvent = (InputEvent*)e;
      int mouseButton = inputEvent->mouseButton;
      int mode = gameData->getGameMode();
      
      switch(e->getEventCode()) {
            //MOUSE DRAG CAMERA
         {case InputEvent::EVENT_MOUSEMOVE:
				if (mode == GAME_MODE || mode == DELETE_MODE || mode == ADD_DOOR || mode == REMOVE_DOOR) {
					TavernaEventHandler::cameraMoveEvent(inputEvent);
					TavernaEventHandler::hoverPersonEvent(inputEvent);
				}
				else if (mode == MAP_MODE) {
					TavernaEventHandler::cameraMoveEvent(inputEvent);
					TavernaEventHandler::hoverTileEvent(inputEvent);
				}
				else if (mode == TABLE_MODE) {
					TavernaEventHandler::hoverTableEvent(inputEvent);
				}
            break;
         }
         {case InputEvent::EVENT_MOUSEDOWN:
				if (mode == GAME_MODE || mode == MAP_MODE || mode == DELETE_MODE || mode == ADD_DOOR || mode == REMOVE_DOOR || mode == TABLE_MODE) {
					TavernaEventHandler::mouseDownEvent(inputEvent);
				}
            break;
         }
            
         {case InputEvent::EVENT_MOUSEOVER:
				if (mode == GAME_MODE || mode == MAP_MODE || mode == DELETE_MODE || mode == ADD_DOOR || mode == REMOVE_DOOR || mode == TABLE_MODE) {
					TavernaEventHandler::mouseOverEvent(inputEvent);
				}
            break;
			}
            
         {case InputEvent::EVENT_MOUSEUP:
            mouseDown = false;
            break;
         }
         {case InputEvent::EVENT_MOUSEWHEEL_DOWN:
            cameraZoomEvent = true;
            zoomDelta = Vector2(2, 2);
            break;
         }
         {case InputEvent::EVENT_MOUSEWHEEL_UP:
            cameraZoomEvent = true;
            zoomDelta = Vector2(-2, -2);
            break;
         }
            break;
      }
   }
}

void TavernaEventHandler::mouseOverEvent(InputEvent *inputEvent) {
	/*Number mouseX = inputEvent->mousePosition.x;
   Number mouseY = inputEvent->mousePosition.y;
   
   //get stuff needed to get 3D mouse coordinat
   Matrix4 projMatrix = rend->getProjectionMatrix(); //rend->getProjectionMatrix();
   Matrix4 camMatrix =  rend->getCameraMatrix();
   Polycode::Rectangle viewPort = rend->getViewport(); //rend->getViewport();
   
   Vector3 rayOrigin = rend->Unproject(mouseX, mouseY, scene->getDefaultCamera()->getConcatenatedMatrix(), scene->getDefaultCamera()->getProjectionMatrix(), scene->getDefaultCamera()->getViewport());
   
   //Vector3 rayDest = rend->projectRayFrom2DCoordinate(mouseX, mouseY, camMatrix, projMatrix, viewPort);
   //std::cout << "Ray End: " << rayOrigin.x << " " << rayOrigin.y << " " << rayOrigin.z << std::endl;
   //std::cout << "Ray Start: " << scene->getDefaultCamera()->getPosition().x << " " << scene->getDefaultCamera()->getPosition().y << " " << scene->getDefaultCamera()->getPosition().z << std::endl;
   Entity *test = scene->getFirstEntityInRay(scene->getDefaultCamera()->getPosition(), rayOrigin).entity;
   
   
   if (test) {
      //std::cout << "Object Position: " << test->getPosition().x << " " << test->getPosition().z << std::endl;
      //test->setColor(0, 0, 0, 0.2);
      SceneSprite * testSprite = GameData::getInstance()->personTable[((Box *) test)->id];
      Person *testPerson = (Person *)testSprite;
      std::cout << testPerson->getName().contents << std::endl;
	  gameData->getUI()->setPortraitPerson(testPerson);
   }	*/
}

void TavernaEventHandler::clickObject(InputEvent *inputEvent) {
   Number mouseX = inputEvent->mousePosition.x;
   Number mouseY = inputEvent->mousePosition.y;
   
   //get stuff needed to get 3D mouse coordinat
   Matrix4 projMatrix = rend->getProjectionMatrix(); //rend->getProjectionMatrix();
   Matrix4 camMatrix =  rend->getCameraMatrix();
   Polycode::Rectangle viewPort = rend->getViewport(); //rend->getViewport();
   
   Vector3 rayOrigin = rend->Unproject(mouseX, mouseY, scene->getDefaultCamera()->getConcatenatedMatrix(), scene->getDefaultCamera()->getProjectionMatrix(), scene->getDefaultCamera()->getViewport());
   
   //Vector3 rayDest = rend->projectRayFrom2DCoordinate(mouseX, mouseY, camMatrix, projMatrix, viewPort);
   //std::cout << "Ray End: " << rayOrigin.x << " " << rayOrigin.y << " " << rayOrigin.z << std::endl;
   //std::cout << "Ray Start: " << scene->getDefaultCamera()->getPosition().x << " " << scene->getDefaultCamera()->getPosition().y << " " << scene->getDefaultCamera()->getPosition().z << std::endl;
   Entity *test = scene->getFirstEntityInRay(scene->getDefaultCamera()->getPosition(), rayOrigin).entity;
   
   
   if (test) {
      //std::cout << "Object Position: " << test->getPosition().x << " " << test->getPosition().z << std::endl;
      //test->setColor(0, 0, 0, 0.2);
      SceneSprite * testSprite = GameData::getInstance()->personTable[((Box *) test)->id];
      Person *testPerson = (Person *)testSprite;
      
      //check if merchant
      if (testPerson->getMerchant())
      {
         printf("Merchant clicked\n");
      }
      std::cout << testPerson->getName().contents << std::endl;
	  GameUI::getInstance()->setPortraitPerson(testPerson);
   }
}
void TavernaEventHandler::hoverPersonEvent(InputEvent *inputEvent) {
   Number mouseX = inputEvent->mousePosition.x;
   Number mouseY = inputEvent->mousePosition.y;
   
   //get stuff needed to get 3D mouse coordinat
   Matrix4 projMatrix = rend->getProjectionMatrix(); //rend->getProjectionMatrix();
   Matrix4 camMatrix =  rend->getCameraMatrix();
   Polycode::Rectangle viewPort = rend->getViewport(); //rend->getViewport();
   
   Vector3 rayOrigin = rend->Unproject(mouseX, mouseY, scene->getDefaultCamera()->getConcatenatedMatrix(), scene->getDefaultCamera()->getProjectionMatrix(), scene->getDefaultCamera()->getViewport());
   
   //Vector3 rayDest = rend->projectRayFrom2DCoordinate(mouseX, mouseY, camMatrix, projMatrix, viewPort);
   //std::cout << "Ray End: " << rayOrigin.x << " " << rayOrigin.y << " " << rayOrigin.z << std::endl;
   //std::cout << "Ray Start: " << scene->getDefaultCamera()->getPosition().x << " " << scene->getDefaultCamera()->getPosition().y << " " << scene->getDefaultCamera()->getPosition().z << std::endl;
   Entity *test = scene->getFirstEntityInRay(scene->getDefaultCamera()->getPosition(), rayOrigin).entity;
   
   if (hoverPerson)
   {
	   hoverPerson->isHighlighted = false;
   }
   if (test) {
      //std::cout << "Object Position: " << test->getPosition().x << " " << test->getPosition().z << std::endl;
      //test->setColor(0, 0, 0, 0.2);
      SceneSprite * testSprite = GameData::getInstance()->personTable[((Box *) test)->id];
	  hoverPerson = (Person *)testSprite;
	  hoverPerson->isHighlighted = true;
	  
	  //Alternative highlighting; current is in Person.cpp
	  /*String aniName = hoverPerson->getCurrentAnimation()->name;
	  hoverPerson->playAnimation("h" + aniName, 0, false);*/
   }
}

void TavernaEventHandler::mouseDownEvent(InputEvent *inputEvent) {
	int mouseButton = inputEvent->mouseButton;
   
	if (mouseButton == 0) {
      mouseDown = true;
      clickObject(inputEvent);
   }
   
	if ((gameData->getGameMode() == MAP_MODE || gameData->getGameMode() == TABLE_MODE) && mouseButton == 1) {
      Number mouseX = inputEvent->mousePosition.x;
      Number mouseY = inputEvent->mousePosition.y;
      
      //get 3D coordinate
      Vector3 rayOrigin = rend->Unproject(mouseX, mouseY, scene->getDefaultCamera()->getConcatenatedMatrix(), scene->getDefaultCamera()->getProjectionMatrix(), scene->getDefaultCamera()->getViewport());
      
      //adjust 3D coordinate to properly pick tile
      int xPos, zPos;
      if (rayOrigin.x > 1)
         xPos = ceil(rayOrigin.x/5 - 0.5);
      else
         xPos = -1;
      if (rayOrigin.z > 1)
         zPos = ceil(rayOrigin.z/5 - 0.5);
      else
         zPos = -1;
      
      if (xPos >= 0 && zPos >= 0 && xPos < DIM && zPos < DIM) { 
		  if (gameData->getGameMode() == MAP_MODE)
		  {
			  if (gameData->getRoomType() == TAVERN_EXPANSION) {
				  te = new TavernExpansion(gameData->getRoomWidth(), gameData->getRoomHeight(), Vector2(xPos, zPos), core, scene, map, ID++);
				  if (te->makeExpansion("GridMaterial", TILE)) {
				 gameData->placeTileSound->Play(false);

				 gameData->addPE->setPosition(xPos*5, 0, zPos*5);
				 gameData->addPE->setLoopParticles(true);
				 gameData->addPE->setLoopParticles(false);
				  }
					TavernResources::getInstance()->addToMaxCapacity((gameData->getRoomWidth() * gameData->getRoomHeight()) / 9);
			  }
			  else {
				   room = new Room(gameData->getRoomWidth(), gameData->getRoomHeight(), Vector2(xPos, zPos), core, scene, map, ID++);
				   printf("TAVERNEVENT: %d\n", ID - 1);
				  if (room->makeRoom(gameData->getRoomType())) {
				 gameData->placeTileSound->Play(false);

				 gameData->addPE->setPosition(xPos*5, 0, zPos*5);
				 gameData->addPE->setLoopParticles(true);
				 gameData->addPE->setLoopParticles(false);
	      }
				   RoomNode *node = new RoomNode(Vector2(xPos, zPos), gameData->getRoomWidth(), gameData->getRoomHeight(), ID - 1);
				   rnList.push_front(node);
				   printf("TAVERNEVENT size: %d\n", rnList.size());
				   TavernResources::getInstance()->addToMaxCapacity((gameData->getRoomWidth() * gameData->getRoomHeight()) / 9);
			  }
		  }
		  else if (gameData->getGameMode() == DELETE_MODE) {
           printf("Bsize: %lu\n", rnList.size());
           int rnID = map->getMapTile(xPos, zPos)->getRoomID();
			  deleter->setPos(xPos, zPos);
			  if (deleter->deleteExpansion(&rnList)) {
				  printf("size: %lu\n", rnList.size()); 
				  gameData->deleteTileSound->Play(false);

				  gameData->deletePE->setPosition(xPos*5, 0, zPos*5);
				  gameData->deletePE->setLoopParticles(true);
				  gameData->deletePE->setLoopParticles(false);
				}	  
		  }
		  else if (gameData->getGameMode() == ADD_DOOR) {
			  door->addDoor(rnList, Vector2(xPos, zPos), gameData->getDoorSide());
		  }
		  else if (gameData->getGameMode() == REMOVE_DOOR) {
			  door->removeDoor(rnList, Vector2(xPos, zPos), gameData->getDoorSide());
		  }
		  else if (gameData->getGameMode() == TABLE_MODE) {
			  bool isViable = true;
			  for (int x = xPos - 1; x < xPos + 1; x++) {
				for (int z = zPos - 1; z < zPos + 1; z++) {
					if (map->getMapTile(x, z)->getType() == TILE) {
						if (map->isOccupied(x, z))
							isViable = false;
					}
					else {
						isViable = false;
					}
				}
			}
			  if (isViable)
			  {
				  TavernResources::getInstance()->tablesList.push_back(new Table(xPos, zPos, 0));
			  }
		  }
         
         gameData->setGameMode(GAME_MODE);
         
         if (room)
         {
            delete(room);
            room = NULL;
         }
         
         if (te)
         {
            delete(te);
            te = NULL;
         }
         
         /*if (door)
         {
            delete(door);
            door = NULL;
         }*/
         
         //printf("TilePrice: %d\n", TavernResources::getInstance()->getTilePrice());
      }
   }
}

void TavernaEventHandler::hoverTableEvent(InputEvent *inputEvent) {
	Number mouseX = inputEvent->mousePosition.x;
	Number mouseY = inputEvent->mousePosition.y;

	Matrix4 projMatrix = rend->getProjectionMatrix();
   Matrix4 camMatrix = rend->getCameraMatrix();
   Polycode::Rectangle viewPort = rend->getViewport();
   
   Vector3 rayOrigin = rend->Unproject(mouseX, mouseY, scene->getDefaultCamera()->getConcatenatedMatrix(), scene->getDefaultCamera()->getProjectionMatrix(), scene->getDefaultCamera()->getViewport());
   
   int xPos, zPos;
   if (rayOrigin.x > 1)
      xPos = ceil(rayOrigin.x/5 - 0.5);
   else
      xPos = -1;
   if (rayOrigin.z > 1)
      zPos = ceil(rayOrigin.z/5 - 0.5);
   else
      zPos = -1;

   if (xPos >= 0 && zPos >= 0 && xPos < DIM && zPos < DIM) {
      if (map->getMapTile(xPos, zPos) != NULL) {
         if (map->getMapTile(xPos, zPos)->getType() != INVIS_TILE) {
			 if (saveTile) {
               
               map->getMapTile(saveTile->x, saveTile->y)->setMaterial(0, "FloorMaterial");
               //map->getMapTile(saveTile->x, saveTile->y)->setType(TILE);
               map->getMapTile(saveTile->x, saveTile->y)->mouseOver = false;
               
               saveTile = new Vector2(xPos, zPos);
            }

			 bool isViable = true;
			for (int x = xPos - 1; x < xPos + 1; x++) {
				for (int z = zPos - 1; z < zPos + 1; z++) {
					if (map->getMapTile(x, z)->getType() == TILE) {
						if (map->isOccupied(x, z))
							isViable = false;
					}
					else {
						isViable = false;
					}
				}
			}

			if (isViable)
				map->getMapTile(xPos, zPos)->setMaterial(0, "GreenOMaterial");
			else
				map->getMapTile(xPos, zPos)->setMaterial(0, "RedXMaterial");

			saveTile = new Vector2(xPos, zPos);
		 }
	  }
   }
}

void TavernaEventHandler::hoverTileEvent(InputEvent *inputEvent) {
   
	Number mouseX = inputEvent->mousePosition.x;
   Number mouseY = inputEvent->mousePosition.y;
   Number x = core->getInput()->getMouseDelta().x;
   Number y = core->getInput()->getMouseDelta().y;
   
   Matrix4 projMatrix = rend->getProjectionMatrix();
   Matrix4 camMatrix = rend->getCameraMatrix();
   Polycode::Rectangle viewPort = rend->getViewport();
   
   Vector3 rayOrigin = rend->Unproject(mouseX, mouseY, scene->getDefaultCamera()->getConcatenatedMatrix(), scene->getDefaultCamera()->getProjectionMatrix(), scene->getDefaultCamera()->getViewport());
   
   int xPos, zPos;
   if (rayOrigin.x > 1)
      xPos = ceil(rayOrigin.x/5 - 0.5);
   else
      xPos = -1;
   if (rayOrigin.z > 1)
      zPos = ceil(rayOrigin.z/5 - 0.5);
   else
      zPos = -1;
   
   //shaky stuff inside, may not work 100%
   if (xPos >= 0 && zPos >= 0 && xPos < DIM && zPos < DIM) {
      if (map->getMapTile(xPos, zPos) != NULL) {
         if (map->getMapTile(xPos, zPos)->getType() == INVIS_TILE) {
            if (saveTile && map->getMapTile(saveTile->x, saveTile->y)->getType() != TILE && map->getMapTile(saveTile->x, saveTile->y)->getType() != LEFT_WALL_TOP && map->getMapTile(saveTile->x, saveTile->y)->getType() != LEFT_WALL_BOT && map->getMapTile(saveTile->x, saveTile->y)->getType() != RIGHT_WALL_BOT && map->getMapTile(saveTile->x, saveTile->y)->getType() != RIGHT_WALL_TOP && map->getMapTile(saveTile->x, saveTile->y)->mouseOver) {
               
               map->getMapTile(saveTile->x, saveTile->y)->setMaterial(0, "InvisGridMaterial");
               map->getMapTile(saveTile->x, saveTile->y)->setType(INVIS_TILE);
               map->getMapTile(saveTile->x, saveTile->y)->mouseOver = false;
               
               saveTile = new Vector2(xPos, zPos);
            }
            
            te = new TavernExpansion(gameData->getRoomWidth(), gameData->getRoomHeight(), Vector2(xPos, zPos), core, scene, map, ID++);
            
            room = new Room(gameData->getRoomWidth(), gameData->getRoomHeight(), Vector2(xPos, zPos), core, scene, map, ID++);
            
            //printf("te: %d\n", te);
            if (te && gameData->getRoomType() == TAVERN_EXPANSION)
            {
               printf("A\n");
               te->getBorders();
               printf("B\n");
               if (!te->viableExpansion())
               {
                  printf("C\n");
		  map->getMapTile(xPos, zPos)->setMaterial(0, "RedXMaterial");
                  map->getMapTile(xPos, zPos)->setType(CANT_BUILD_TILE);
               }
               
               else
               {
		  map->getMapTile(xPos, zPos)->setMaterial(0, "GreenOMaterial");
                  map->getMapTile(xPos, zPos)->setType(MOUSE_OVER_TILE);
               }
               
               printf("D\n");
               te->setZeroWallCounters();
            }
            
            else if (room && gameData->getRoomType() != TAVERN_EXPANSION)
            {
               printf("E\n");
               room->getHandlerBorders();
               printf("viableBorder: %d\n", room->viableBorder());
               printf("enoughSpace: %d\n", room->enoughSpace());
               if (!room->viableRoom())
               {
                  printf("G\n");
		  map->getMapTile(xPos, zPos)->setMaterial(0, "RedXMaterial");
                  map->getMapTile(xPos, zPos)->setType(CANT_BUILD_TILE);
               }
               
               else
               {
                  printf("H\n");
		  map->getMapTile(xPos, zPos)->setMaterial(0, "GreenOMaterial");
                  map->getMapTile(xPos, zPos)->setType(MOUSE_OVER_TILE);
               }
               
               room->setZeroWallCounters();
            }
            
            else
            {
               printf("I\n");
	       map->getMapTile(xPos, zPos)->setMaterial(0, "GreenOMaterial");
               map->getMapTile(xPos, zPos)->setType(MOUSE_OVER_TILE);
            }
            
            
            saveTile = new Vector2(xPos, zPos);
            map->getMapTile(xPos, zPos)->mouseOver = true;
            
            if (te)
            {
               delete(te);
               te = NULL;
               ID--;
            }
            
            if (room)
            {
               delete(room);
               room = NULL;
               ID--;
            }
            printf("K\n");
         }
         
         else if (saveTile && map->getMapTile(saveTile->x, saveTile->y)->getType() != TILE && (map->getMapTile(xPos, zPos)->getType() == TILE || (map->getMapTile(xPos, zPos)->getType() == RIGHT_WALL_TOP || (map->getMapTile(xPos, zPos)->getType() == LEFT_WALL_TOP) || (map->getMapTile(xPos, zPos)->getType() == LEFT_WALL_BOT || (map->getMapTile(xPos, zPos)->getType() == RIGHT_WALL_BOT))))) {
            map->getMapTile(saveTile->x, saveTile->y)->setMaterial(0, "InvisGridMaterial");
            map->getMapTile(saveTile->x, saveTile->y)->setType(INVIS_TILE);
            map->getMapTile(saveTile->x, saveTile->y)->mouseOver = false;
         }
      }
   }
}

void TavernaEventHandler::moveCameraTo(Number x, Number z, Number lerp) {
   //std::cout << scene->getDefaultCamera()->getPosition().x << std::endl;
   Vector3 newPosition = scene->getDefaultCamera()->getPosition();
   newPosition.x += ((x - scene->getDefaultCamera()->getPosition().x) * lerp) * core->getElapsed();
   newPosition.z += ((z - scene->getDefaultCamera()->getPosition().z) * lerp) * core->getElapsed();
   scene->getDefaultCamera()->setPosition(newPosition);
}

void TavernaEventHandler::cameraMoveEvent(InputEvent *inputEvent) {
	Number mouseX = inputEvent->mousePosition.x;
   Number mouseY = inputEvent->mousePosition.y;
   Number x = core->getInput()->getMouseDelta().x;
   Number y = core->getInput()->getMouseDelta().y;
   
   if (mouseDown) {
      
      if (mouseX > 0 && mouseY > 0 && mouseX < core->getXRes() && mouseY < core->getYRes()) {
         cameraEvent = true;
         cameraMove = Vector3(-x, y, 0);
		}
   }
}

void TavernaEventHandler::Update() {
   if (gameStart) {
      if (scene->getDefaultCamera()->getPosition().x < 248) {
	 moveCameraTo(250, 170, 1);
         moveCameraTo(250, 170, 0.5);
         cameraEvent = false;
         cameraZoomEvent = false;
      }
      else {
         gameStart = false;
      }
   }
   if (cameraEvent) {
      Vector3 dirVector = cameraMove;
      dirVector = scene->getDefaultCamera()->getConcatenatedMatrix().rotateVector(dirVector);
      Vector3 newPosition = scene->getDefaultCamera()->getPosition() + (dirVector * 4 * core->getElapsed());
      scene->getDefaultCamera()->setPosition(newPosition);
      cameraEvent = false;
   }
   if (cameraZoomEvent) {
      newZoom = zoomDelta;
      newZoom.x += scene->getDefaultCamera()->getOrthoSizeX();
      newZoom.y += scene->getDefaultCamera()->getOrthoSizeY();
      if (newZoom.x > maxZoomIn && newZoom.x < maxZoomOut)
         scene->getDefaultCamera()->setOrthoSize(newZoom.x, newZoom.y);
      cameraZoomEvent = false;
   }
}