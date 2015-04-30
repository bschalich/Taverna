#include "GameMap.h"
#include "define.h"
#include <ctime>

GameMap::GameMap(Core *polycore, CollisionScene *polyScene) {
   scene = polyScene;
   core = polycore;
   srand((unsigned)time(0));
}

GameMap::~GameMap() {
   for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
         delete tile[i][j];
      }
   }
}

void GameMap::initMap() {
   int yawRands[4] = {0, 90, 180, 270};
   
   for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
         if (i == DIM/2 && j == 0) {
            tile[i][j] = new MapTile(FRONT_DOOR, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if ((i >= 13 && i < DIM - 13) && ((j >= 2) && (j < DIM/2 - 5))) {
            tile[i][j] = new MapTile(TILE, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (i == 12 && ((j >= 2) && j < DIM/2 - 5)) {
            tile[i][j] = new MapTile(LEFT_WALL_TOP, i, j, core, scene, INITIAL_STRUCTURE, true);
	    /*if ((j % 5) == 0) {
	       SceneMesh *lantern = new SceneMesh("lantern_03_lit.mesh");
	       lantern->setMaterialByName("BitgemMaterial");
	       lantern->setPosition(i*5 - 1, 3, j*5 + 2.5);
	       lantern->setScale(0.05);
	       lantern->Yaw(90);
	       scene->addChild(lantern);

	       SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, scene, 10);
	       light->setPosition(i*5 + 1, 7, j*5);
	       light->setLightColor(1, 0.7, 0.5);
	       light->setDiffuseLightColor(1.0, 0.6, 0.3);
	       scene->addLight(light);
	    }*/
         }
         else if (i == 12 && j == 1) {
            tile[i][j] = new MapTile(CORNER_TOP, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (j == 1 && (i >= 13 && i <= 19)) {
            tile[i][j] = new MapTile(RIGHT_WALL_TOP, i, j, core, scene, INITIAL_STRUCTURE, true);

	    /*if ((i % 6) == 0) {
	       SceneMesh *lantern = new SceneMesh("lantern_03_lit.mesh");
	       lantern->setMaterialByName("BitgemMaterial");
	       lantern->setPosition(i*5 + 2, 3, j*5 - 1);
	       lantern->setScale(0.05);
	       scene->addChild(lantern);

	       SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, scene, 10);
	       light->setPosition(i*5, 7, j*5 + 1);
	       light->setLightColor(1, 0.7, 0.5);
	       light->setDiffuseLightColor(1.0, 0.6, 0.3);
	       scene->addLight(light);
	    }*/
         }
         else if (j == 1 && i == 20) {
            tile[i][j] = new MapTile(TILE, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (j == 1 && (i >= 21 && i < DIM - 13)) {
            tile[i][j] = new MapTile(RIGHT_WALL_TOP, i, j, core, scene, INITIAL_STRUCTURE, true);

	    /*if ((i % 23) == 0) {
	       SceneMesh *lantern = new SceneMesh("lantern_03_lit.mesh");
	       lantern->setMaterialByName("BitgemMaterial");
	       lantern->setPosition(i*5, 4, j*5);
	       lantern->setScale(0.05);
	       scene->addChild(lantern);

	       SceneLight *light = new SceneLight(SceneLight::POINT_LIGHT, scene, 10);
	       light->setPosition(i*5 - 3, 7, j*5 + 1);
	       light->setLightColor(1, 0.7, 0.5);
	       light->setDiffuseLightColor(1.0, 0.6, 0.3);
	       scene->addLight(light);
	    }*/
         }
         else if (i == 27 && j == 1) {
            tile[i][j] = new MapTile(CORNER_RIGHT, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (j == DIM/2 - 5 && (i >= 13 && i < DIM - 13)) {
            tile[i][j] = new MapTile(RIGHT_WALL_BOT, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (j == DIM/2 - 5 && i == DIM - 13 ) {
            tile[i][j] = new MapTile(CORNER_BOT, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (i == DIM - 13 && ((j >= 1) && j < DIM/2 - 5)) {
            tile[i][j] = new MapTile(LEFT_WALL_BOT, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else if (j == DIM/2 - 5 && i == 12 ) {
            tile[i][j] = new MapTile(CORNER_LEFT, i, j, core, scene, INITIAL_STRUCTURE, true);
         }
         else {
            tile[i][j] = new MapTile(INVIS_TILE, i, j, core, scene, NOTHING, false);
         }
          
          if (i == 0 || i == DIM - 1 || j == 0|| j == DIM - 1)
          {
             tile[i][j]->getScenePrimitive(0)->setColor(1, 0, 0, 1);
          }
      }
   }
   //BAR LOL
   /*for (int i = 15; i > 8; i--) {
      tile[14][i]->setPrimitive(new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 8, 5), "WoodMaterial", 6, true);
   }

   tile[13][9]->setPrimitive(new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 8, 5), "WoodMaterial", 6, true);
   tile[12][9]->setPrimitive(new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 8, 5), "WoodMaterial", 6, true);
   
   tile[12][14]->setObject("barrel_02.mesh", "BitgemMaterial", 6, true);
   tile[12][14]->getObject()->setScale(.05*1.5, .05*1.5, .05*1.5);
   */
   //raiseWalls();
}

void GameMap::setUpBars() {
   Bar *bar = new Bar(13, 1, 6, 4);
}

MapTile* GameMap::getMapTile(int i, int j) {
   return tile[i][j];
}

void GameMap::raiseWalls() {
   for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
		  if (tile[i][j]->getType() == INVIS_TILE)
		  {
			  tile[i][j]->getScenePrimitive(0)->setColor(1, 1, 1, 0);
		  }
         if (tile[i][j] != NULL && tile[i][j]->hasWall > 0) {
            if (tile[i-1][j]->getType() == INVIS_TILE
                //|| tile[i+1][j]->getType() == INVIS_TILE
                || tile[i][j-1]->getType() == INVIS_TILE
                //|| tile[i][j+1]->getType() == INVIS_TILE
                ) {
               tile[i][j]->raiseWalls();
            }
         }
      }
   }
}

void GameMap::lowerWalls() {
   for (int i = 0; i < DIM; i++) {
      for (int j = 0; j < DIM; j++) {
		  if (tile[i][j]->getType() == INVIS_TILE)
		  {
			  if (i == 0 || i == DIM - 1 || j == 0|| j == DIM - 1)
			  {
                 tile[i][j]->getScenePrimitive(0)->setColor(1, 0, 0, 1);
			  }
			  else
			  {
				tile[i][j]->getScenePrimitive(0)->setColor(1, 1, 1, 1);
			  }
		  }
	 if (tile[i][j] != NULL && tile[i][j]->hasWall > 0) {
	    if (tile[i-1][j]->getType() == INVIS_TILE
           //|| tile[i+1][j]->getType() == INVIS_TILE
           || tile[i][j-1]->getType() == INVIS_TILE
           //|| tile[i][j+1]->getType() == INVIS_TILE
           ) {
	       tile[i][j]->lowerWalls();
	    }
	 }
      }
   }
}

int GameMap::getType(int row, int col) {
   return tile[row][col]->getType();
}

bool GameMap::isOccupied(int row, int col) {
   return tile[row][col]->checkOccupied();
}

void GameMap::setUpTables() {
   TavernResources::getInstance()->tablesList.push_back(new Table(24, 3, 0));
   TavernResources::getInstance()->tablesList.push_back(new Table(24, 8, 1));
   TavernResources::getInstance()->tablesList.push_back(new Table(24, 13, 2));
   TavernResources::getInstance()->tablesList.push_back(new Table(19, 13, 3));
   TavernResources::getInstance()->tablesList.push_back(new Table(14, 13, 4));
   TavernResources::getInstance()->numTables = 4;
}


