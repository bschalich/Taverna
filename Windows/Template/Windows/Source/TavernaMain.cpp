#include "TavernaMain.h"
#include <iostream>
#include <fstream>
#include "Staff.h"

TavernaMain::TavernaMain(Core *polycore) {
   core = polycore;
   gameMode = GAME_MODE;
   intro = true;
   gameOver = false;
   lightFlicker = true;
   crowdNoise = false;
   tavRes = TavernResources::getInstance();

   //Folder locations, default.pak and default needed
   CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
   
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Textures");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Textures", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Meshes");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Meshes", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Sprites");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Sprites", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Files");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Files", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Audio");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Audio", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Audio/UI");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Audio/UI", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Audio/Game");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Audio/Game", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/Audio/Music");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/Audio/Music", true);
   CoreServices::getInstance()->getResourceManager()->addArchive("Assets/UI");
   CoreServices::getInstance()->getResourceManager()->addDirResource("Assets/UI", true);
   
   CoreServices::getInstance()->getRenderer()->alphaTestValue = 0.5;
   
   core->warpCursor(core->getXRes()/2, core->getYRes()/2);
   //Set up 3D scene
   scene3D = new CollisionScene();//new Scene(Scene::SCENE_3D);
   scene3D->rootEntity.processInputEvents = true;
   //2D scene for UI
   scene2D = new Scene(Scene::SCENE_2D);
   scene2D->rootEntity.processInputEvents = true;

   //Change scene background color
   scene3D->clearColor = new Color(15, 15, 15, 0);
   scene3D->useClearColor = true;
   


   GameMap *map = new GameMap(core, scene3D);
   map->initMap();
   
   gameData = GameData::getInstance();
   gameData->setCore(core);
   gameData->set2DScene(scene2D);
   gameData->set3DScene(scene3D);
   gameData->setGameMap(map);
   gameData->setGameMode(gameMode);
   gameData->setUpParticleEmitters();

   TavernResources *resources = TavernResources::getInstance();
   resources->setCore(polycore);
   
   map->setUpTables();
   map->setUpBars();
   map->raiseWalls();
   //Initialize files
   string line;
   ifstream namesFile("Assets/Files/NPC_NAMES.txt");
   if (namesFile.is_open()) {
      while (getline(namesFile, line)) {
         gameData->npcNames.push_back(line);
      }
      namesFile.close();
   }
   else {
      cout << "Error opening NPC_NAMES.txt\n";
   }
   
   gameUI = GameUI::getInstance();
   //gameData->setUI(gameUI);
   
   SceneLight *lightA = new SceneLight(SceneLight::POINT_LIGHT, scene3D, 50000);
   lightA->setPosition(30*5, 180, 20*5);
   lightA->setLightColor(1, 0.7, 0.5);
   lightA->setDiffuseLightColor(1.0, 0.6, 0.3);
   scene3D->addLight(lightA);

   //Event listeners
   inputHandler = new TavernaEventHandler();
   gameController = new GameController();

   startScreen = new StartScreen();
   //swarm test
   /*for (int i = 0; i < 200; i++) {
      scene3D->addChild(new Person("bob", false, "patron.png", 90, 140));
   }*/
}

/** Destroy app... if not needed leave empty. */
TavernaMain::~TavernaMain() {
   delete gameController;
   delete inputHandler;
   delete gameUI;
   delete scene2D;
   delete scene3D;
   rep = 1000;
}

/**
 * Update the game every frame, must put all updating actions in this method
 * for the game to look right.
 */
void TavernaMain::Update() {
	for (int i = 0; i < scene3D->getNumLights(); i++) {
      if (scene3D->getLight(i)->getIntensity() > 5 && lightFlicker) {
         scene3D->getLight(i)->setIntensity(scene3D->getLight(i)->getIntensity()-(rand() % 30) * core->getElapsed());
      }
      else {
         lightFlicker = false;
      }
      
      if (scene3D->getLight(i)->getIntensity() < 10 && !lightFlicker) {
         scene3D->getLight(i)->setIntensity(scene3D->getLight(i)->getIntensity()+(rand() % 30) * core->getElapsed());
         lightFlicker = true;
      }
   }
   
   if (tavRes->getCapacity() >= 5 && !crowdNoise)
   {
      gameData->crowdNoiseSound->Play(true);
      crowdNoise = true;
   }
   
   else if (crowdNoise && tavRes->getCapacity() < 5)
   {
      gameData->crowdNoiseSound->Stop();
      crowdNoise = false;
   }
   
   gameData->crowdNoiseSound->setVolume(.04 * tavRes->getCapacity());
   
   if (!startScreen->getIsStart())
   {
	   gameUI->menubar->visible = false;
	   gameUI->portrait->visible = false;
   }
   else if (gameController->getIsMonthBreak())
   {
	   inputHandler->Update();
	   gameController->Update();
	   gameUI->Update();
       gameData->crowdNoiseSound->Stop();
       crowdNoise = false;
   }
   else if (tavRes->getCurrentRep() <= 0)
   {
		if (!gameOver)
		{
			gameOver = true;
			GameOver *gameOverScreen = new GameOver();
		}
   }
   else
   {
	   gameUI->menubar->visible = true;
	   gameUI->portrait->visible = true;

	   //cout << core->getFPS() << endl;
	   inputHandler->Update();
	   gameData->Update();
	   gameController->Update();
	   gameUI->Update();
	   TavernResources::getInstance()->calcRep();
	   //printf("REP: %d\n", TavernResources::getInstance()->getRep());
   
	   if (tavRes->getCurrentRep() < tavRes->getRep())
		  tavRes->incrementCurrentRep();
   
	   else if (tavRes->getCurrentRep() > tavRes->getRep())
		  TavernResources::getInstance()->decrementCurrentRep();
   }
}



