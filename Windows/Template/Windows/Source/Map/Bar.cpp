//
//  Bar.cpp
//  Taverna
//
//  Created by Kevin Weber on 6/2/14.
//  Copyright (c) 2014 Tomatogon. All rights reserved.
//

#include "Bar.h"

Bar::Bar(int i, int j, int xSize, int zSize) {
   this->i = i;
   this->j = j;
   barPos = Vector3(i, 0, j);
   barkeepTile = Vector3(i + 1, 0 , j + 1);

   for (int index = i; index < i + xSize; index++) {
      for (int index2 = j; index2 < j + zSize; index2++) {

	 if (index == i) {
	    patronTiles.push_back(Vector3(index - 1, 0, index2));
	 }
	 if (index2 == j) {
	    patronTiles.push_back(Vector3(index, 0, index2 - 1));
	 }
	 if (index == i + xSize  -1) {
	    patronTiles.push_back(Vector3(index + 1, 0, index2));
	 }
	 if (index2 == j + zSize - 1) {
	    patronTiles.push_back(Vector3(index, 0, index2 + 1));
	 }
	 MapTile *barTile = GameData::getInstance()->getGameMap()->getMapTile(index, index2);
	 barTile->setPrimitive(new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 8, 5), "WoodMaterial", 6, true);
      }
   }

   for (int index = i + 1; index < i - 1 + xSize; index++) {
      for (int index2 = j + 1; index2 < j - 1 + zSize; index2++) {
	 MapTile *barTile = GameData::getInstance()->getGameMap()->getMapTile(index, index2);
	 barTile->removeObject(index, index2);
      }
   }
   
   MapTile * temp = GameData::getInstance()->getGameMap()->getMapTile(i + xSize - 2, j + 1);
   temp->setObject("barrel_03.mesh", "BitgemMaterial", 4, true);
   temp->getObject()->setScale(0.1, 0.1, 0.1);

   
   SceneMesh *object = new SceneMesh("barrel_01.mesh");
   object->depthTest = true;
   object->depthWrite = true;
   object->setPosition(i*5, 4.5, j*5);
   object->setMaterialByName("BitgemMaterial");
   object->setScale(0.06, 0.06, 0.06);
   GameData::getInstance()->getScene3D()->addChild(object);
   
   
   
   /*ScenePrimitive *objectShadow;
   objectShadow = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 5, 5, 20);
   objectShadow->setPitch(-90);
   objectShadow->depthTest = true;
   objectShadow->depthWrite = true;
   objectShadow->setPosition(i*5, 6, i*5);
   objectShadow->setMaterialByName("SolidMaterial");
   objectShadow->setColor(1, 1, 1, 0.3);
   GameData::getInstance()->getScene3D()->addChild(objectShadow);
   */
   TavernResources::getInstance()->barList.push_back(this);
}

Bar::~Bar() {

}

String Bar::getBarDir(Vector3 personDir) {
   String dir = "topRight";
   if (personDir.z > j && personDir.x >= i) {
      dir = "topRight";
   }
   else if (personDir.x <= i) {
      dir = "botRight";
   }
   else if (personDir.x >= i && personDir.z <= j) {
      dir = "topLeft";
   }
   return dir;
}