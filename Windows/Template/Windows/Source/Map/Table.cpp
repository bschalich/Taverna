#include "Table.h"

Table::Table(int i, int j, int id) {
   //srand((unsigned)time(0));
   int yawRands[4] = {0, 90, 180, 270};
   tablePos = Vector3(i, 0, j);
   this->id = id;
   numChairs = 4;
   reserved = false;
   this->i = i;
   this->j = j;
   
   waiterTile = Vector3(i - 1, 0, j + 1);
   
   MapTile *tableTile = GameData::getInstance()->getGameMap()->getMapTile(i, j);
   MapTile *chairTileUp = GameData::getInstance()->getGameMap()->getMapTile(i, j-1);
   MapTile *chairTileLeft = GameData::getInstance()->getGameMap()->getMapTile(i-1, j);
   MapTile *chairTileDown = GameData::getInstance()->getGameMap()->getMapTile(i, j+1);
   MapTile *chairTileRight = GameData::getInstance()->getGameMap()->getMapTile(i+1, j);
   
   tableTile->setObject("table_wood.mesh", "BitgemMaterial", 10, true);
   tableTile->getObject()->setScale(0.05*1.4, 0.05*1.5, 0.05*2);
   tableTile->getObject()->setYaw(yawRands[rand() % 4]);
   
   SceneMesh *candle = new SceneMesh("candle_01_lit.mesh");
   candle->setPosition(i*5, 4, j*5);
   candle->setScale(0.05*1.5, 0.05, 0.05*1.5);
   candle->setYaw(rand() % 360);
   candle->setMaterialByName("BitgemMaterial");
   GameData::getInstance()->getScene3D()->addChild(candle);
   
   SceneLight *candleLight = new SceneLight(SceneLight::POINT_LIGHT, GameData::getInstance()->getScene3D(), 50);
   candleLight->setPosition(i*5, 6, j*5);
   candleLight->setSpotlightProperties(100, 100);
   candleLight->setLightColor(1, 0.7, 0.5);
   candleLight->setIntensity(10);
   //light->enableShadows(true);
   candleLight->setDiffuseLightColor(1.0, 0.6, 0.3);
   GameData::getInstance()->getScene3D()->addLight(candleLight);
   
   //top right
   chairTileUp->setObject("chair_wood.mesh", "BitgemMaterial", 4, false);
   chairTileUp->getObject()->setScale(0.05*1.5, 0.05*1.5, 0.05*1.5);
   openChairs.push_back(Vector3(i, 0, j-1));
   
   //top left
   chairTileLeft->setObject("chair_wood.mesh", "BitgemMaterial", 4, false);
   chairTileLeft->getObject()->setScale(0.05*1.5, 0.05*1.5, 0.05*1.5);
   chairTileLeft->getObject()->setYaw(90);
   openChairs.push_back(Vector3(i-1, 0, j));
   
   //bottom left
   chairTileDown->setObject("chair_wood.mesh", "BitgemMaterial", 4, false);
   chairTileDown->getObject()->setScale(0.05*1.5, 0.05*1.5, 0.05*1.5);
   chairTileDown->getObject()->setYaw(180);
   openChairs.push_back(Vector3(i, 0, j+1));
   
   //bottom right
   chairTileRight->setObject("chair_wood.mesh", "BitgemMaterial", 4, false);
   chairTileRight->getObject()->setScale(0.05*1.5, 0.05*1.5, 0.05*1.5);
   chairTileRight->getObject()->setYaw(270);
   openChairs.push_back(Vector3(i+1, 0, j));
   
   //TavernResources::getInstance()->tablesList.push_back(this);
}

Table::~Table() {
   
}

void Table::reset() {
   openChairs.clear();
   openChairs.push_back(Vector3(i, 0, j-1));
   openChairs.push_back(Vector3(i-1, 0, j));
   openChairs.push_back(Vector3(i, 0, j+1));
   openChairs.push_back(Vector3(i+1, 0, j));
   
   numChairs = 4;
   
   reserved = false;
}

String Table::getSitDir(Vector3 chairPos) {
   Vector3 dif = tablePos - chairPos;
   if (dif.x == 0 && dif.z == 1) {
      //top right chair
      return "bottomLeft";
   }
   else if (dif.x == 1 && dif.z == 0) {
      //top left chair
      return "bottomRight";
   }
   else if (dif.x == 0 && dif.z == -1) {
      //bottom left chair
      return "topRight";
   }
   else if (dif.x == -1 && dif.z == 0) {
      //bottom right chair
      return "topLeft";
   }
   return "NONE";
}