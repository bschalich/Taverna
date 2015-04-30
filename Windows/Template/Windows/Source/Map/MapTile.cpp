#include "MapTile.h"

MapTile::MapTile(int tileType, int i, int j, Core *polycore, CollisionScene *polyscene, int roomID, bool te) {
   core = polycore;
   scene = polyscene;
   this->tileType = tileType;
   posX = i;
   posZ = j;
   occupied = false;
   mouseOver = false;
   this->roomID = roomID;
   hasWall = 0;
   
   //whether or not this is a tavern expansion (true if TavernExpansion)
   this->te = te;
   object = NULL;
   
   if (tileType == INVIS_TILE) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 5, 5);
      tile[0]->setMaterialByName("InvisGridMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      occupied = true;
      tile[1] = NULL;
      tile[2] = NULL;
   }
   else if (tileType == TILE) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      occupied = false;
      tile[1] = NULL;
      tile[2] = NULL;
   }
   else if (tileType == FRONT_DOOR) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 8, 1);
      tile[0]->setMaterialByName("WallMaterial");
      //tile[0]->setColor(1, 1, 1, 0.2);
      tile[0]->setPosition(i*5 - 2, 12, j*5);
      //scene->addCollisionChild(tile[0]);
      occupied = false;
      tile[1] = NULL;
      tile[2] = NULL;
   }
   else if (tileType == LEFT_DOOR_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("DoorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(i*5 - 2, 2, j*5);
      scene->addChild(tile[1]);
      occupied = false;
      tile[2] = NULL;
   }
   else if (tileType == RIGHT_DOOR_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(i*5, 2, j*5 - 2);
      scene->addChild(tile[1]);
      tile[2] = NULL;
      occupied = false;
   }
   else if (tileType == LEFT_DOOR_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(i*5, 2, j*5 + 2);
      scene->addChild(tile[1]);
      tile[2] = NULL;
      occupied = false;
   }
   else if (tileType == RIGHT_DOOR_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(i*5 + 2, 2, j*5);
      scene->addChild(tile[1]);
      tile[2] = NULL;
      occupied = false;
   }
   
   //else if (tileType == C)
   else if (tileType == LEFT_WALL_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5 - 2, 1, j*5);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      
      hasWall = 1;
      occupied = false;
   }
   else if (tileType == RIGHT_WALL_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5, 1, j*5 - 2);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      
      hasWall = 1;
      occupied = false;
   }
   else if (tileType == RIGHT_WALL_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5, 1, j*5 + 2);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      
      hasWall = 1;
      occupied = false;
   }
   else if (tileType == LEFT_WALL_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5 + 2, 1, j*5);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      
      hasWall = 1;
      occupied = false;
   }
   else if (tileType == CORNER_BOT) {
      //left wall
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(i*5, 1, j*5 + 2);
      scene->addChild(tile[0]);
      
      //right wall
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5 + 2, 1, j*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[2]);
      
      hasWall = 2;
      occupied = false;
   }
   else if (tileType == CORNER_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(i*5, 1, j*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5 - 2, 1, j*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[2]);
      
      hasWall = 2;
      occupied = false;
   }
   else if (tileType == CORNER_RIGHT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(i*5, 1, j*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5 + 2, 1, j*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[2]);
      
      hasWall = 2;
      occupied = false;
   }
   else if (tileType == CORNER_LEFT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(i*5, 1, j*5 + 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(i*5 - 2, 1, j*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(i*5, 0, j*5);
      scene->addChild(tile[2]);
      
      hasWall = 2;
      occupied = false;
   }
   
   for (int i = 0; i < 3; i++) {
      if (tile[i]) {
         tile[i]->depthTest = true;
         tile[i]->depthWrite = true;
      }
   }
}

MapTile::~MapTile() {
   for (int i = 0; i < 3; i++) {
      if (tile[i] != NULL) {
         scene->removeEntity(tile[i]);
         delete tile[i];
         tile[i] = NULL;
      }
   }
}

bool MapTile::checkOccupied() {
   return occupied;
}

void MapTile::setOccupied(bool occ)
{
    occupied = occ;
}

int MapTile::getRoomID()
{
   return roomID;
}

void MapTile::setRoomID(int roomID)
{
   this->roomID = roomID;
}

void MapTile::setTE(bool te)
{
   this->te = te;
}

bool MapTile::getTE()
{
   return this->te;
}

void MapTile::setPrimitive(ScenePrimitive *prim, String mat, Number shadowSize, bool occupy) {
   if (object != NULL) {
      scene->removeEntity(object);
      scene->removeEntity(objectShadow);
      delete(object);
      delete(objectShadow);
      object = prim;
   }
   else {
      object = prim;
   }
   object->depthTest = true;
   object->depthWrite = true;
   object->setPosition(posX*5, 0.5, posZ*5);
   object->setMaterialByName(mat);
   scene->addChild(object);
   
   objectShadow = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, shadowSize, shadowSize, 20);
   objectShadow->setPitch(-90);
   objectShadow->depthTest = true;
   objectShadow->depthWrite = true;
   objectShadow->setPosition(posX*5, 0.6, posZ*5);
   objectShadow->setMaterialByName("SolidMaterial");
   objectShadow->setColor(1, 1, 1, 0.3);
   scene->addChild(objectShadow);
   
   this->occupied = occupy;
}

void MapTile::setObject(String mesh, String mat, Number shadowSize, bool occupy) {
   if (object != NULL) {
      scene->removeEntity(object);
      scene->removeEntity(objectShadow);
      delete(object);
      delete(objectShadow);
      object = new SceneMesh(mesh);
   }
   else {
      object = new SceneMesh(mesh);
   }
   object->depthTest = true;
   object->depthWrite = true;
   object->setPosition(posX*5, 0.5, posZ*5);
   object->setMaterialByName(mat);
   scene->addChild(object);
   
   objectShadow = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, shadowSize, shadowSize, 20);
   objectShadow->setPitch(-90);
   objectShadow->depthTest = true;
   objectShadow->depthWrite = true;
   objectShadow->setPosition(posX*5, 0.6, posZ*5);
   objectShadow->setMaterialByName("SolidMaterial");
   objectShadow->setColor(1, 1, 1, 0.3);
   scene->addChild(objectShadow);
   
   this->occupied = occupy;
   
}

SceneMesh *MapTile::getObject() {
   return object;
}

void MapTile::removeObject(int row, int col)
{
    scene->removeEntity(object);
    scene->removeEntity(objectShadow);
   this->occupied = false;
    //delete(object);
    //delete(objectShadow);
}

void MapTile::setType(int tileType) {
   this->tileType = tileType;
}

int MapTile::getType() {
   return tileType;
}

ScenePrimitive* MapTile::getScenePrimitive(int which) {
   return tile[which];
}

void MapTile::setScenePrimitive(int which, ScenePrimitive *newPrim) {
   scene->removeEntity(tile[which]);
   
   if (tile[which])
      delete(tile[which]);
   
   tile[which] = newPrim;
   scene->addChild(tile[which]);
}

void MapTile::setMaterial(int which, String mat) {
   tile[which]->setMaterialByName(mat);
}

void MapTile::raiseWalls() {
   int tempType;
   tempType = this->getType();
   if (tempType == LEFT_WALL_TOP || tempType == LEFT_WALL_BOT) {
      scene->removeEntity(tile[1]);
      delete(tile[1]);
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 10, 5);
      if (tempType == LEFT_WALL_TOP) {
         tile[1]->setPosition(posX*5 - 2, 5, posZ*5);
      }
      if (tempType == LEFT_WALL_BOT) {
         tile[1]->setColor(1, 1, 1, 0.1);
         tile[1]->setPosition(posX*5 + 2, 5, posZ*5);
      }
      tile[1]->setMaterialByName("WallMaterial");
      scene->addChild(tile[1]);
   }
   else if (tempType == RIGHT_WALL_TOP || tempType == RIGHT_WALL_BOT) {
      scene->removeEntity(tile[1]);
      delete(tile[1]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 10, 1);
      if (tempType == RIGHT_WALL_TOP) {
         tile[1]->setPosition(posX*5, 5, posZ*5 - 2);
      }
      if (tempType == RIGHT_WALL_BOT) {
         tile[1]->setColor(1, 1, 1, 0.1);
         tile[1]->setPosition(posX*5, 5, posZ*5 + 2);
      }
      tile[1]->setMaterialByName("WallMaterial");
      scene->addChild(tile[1]);
   }
   else if (tempType == CORNER_BOT || tempType == CORNER_TOP
            || tempType == CORNER_LEFT || tempType == CORNER_RIGHT) {
      scene->removeEntity(tile[0]);
      delete(tile[0]);
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 10, 1);
      tile[0]->setMaterialByName("WallMaterial");
      scene->addChild(tile[0]);
      
      scene->removeEntity(tile[1]);
      delete(tile[1]);
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 10, 5);
      tile[1]->setMaterialByName("WallMaterial");
      scene->addChild(tile[1]);
      
      if (tempType == CORNER_BOT) {
         tile[0]->setColor(1, 1, 1, 0.1);
         tile[1]->setColor(1, 1, 1, 0.1);
         tile[0]->setPosition(posX*5, 5, posZ*5 + 2);
         tile[1]->setPosition(posX*5 + 2, 5, posZ*5);
      }
      else if (tempType == CORNER_TOP) {
         tile[0]->setPosition(posX*5, 5, posZ*5 - 2);
         tile[1]->setPosition(posX*5 - 2, 5, posZ*5);
      }
      else if (tempType == CORNER_RIGHT) {
         tile[0]->setPosition(posX*5, 5, posZ*5 - 2);
         tile[1]->setPosition(posX*5 + 2, 5, posZ*5);
      }
      else if (tempType == CORNER_LEFT) {
         tile[0]->setPosition(posX*5, 5, posZ*5 + 2);
         tile[1]->setPosition(posX*5 - 2, 5, posZ*5);
      }
   }
}

void MapTile::lowerWalls() {
   int tempType;
   tempType = this->getType();
   if (tempType == LEFT_WALL_TOP || tempType == LEFT_WALL_BOT) {
      scene->removeEntity(tile[1]);
      delete(tile[1]);
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      if (tempType == LEFT_WALL_TOP) {
	 tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      }
      if (tempType == LEFT_WALL_BOT) {
	 tile[1]->setColor(1, 1, 1, 0.1);
	 tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      }
      tile[1]->setMaterialByName("WallMaterial");
      scene->addChild(tile[1]);
   }
   else if (tempType == RIGHT_WALL_TOP || tempType == RIGHT_WALL_BOT) {
      scene->removeEntity(tile[1]);
      delete(tile[1]);

      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      if (tempType == RIGHT_WALL_TOP) {
	 tile[1]->setPosition(posX*5, 1, posZ*5 - 2);
      }
      if (tempType == RIGHT_WALL_BOT) {
	 tile[1]->setColor(1, 1, 1, 0.1);
	 tile[1]->setPosition(posX*5, 1, posZ*5 + 2);
      }
      tile[1]->setMaterialByName("WallMaterial");
      scene->addChild(tile[1]);
   }
   else if (tempType == CORNER_BOT || tempType == CORNER_TOP
	    || tempType == CORNER_LEFT || tempType == CORNER_RIGHT) {
      scene->removeEntity(tile[0]);
      delete(tile[0]);
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      scene->addChild(tile[0]);

      scene->removeEntity(tile[1]);
      delete(tile[1]);
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      scene->addChild(tile[1]);

      if (tempType == CORNER_BOT) {
	 tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
	 tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      }
      else if (tempType == CORNER_TOP) {
	 tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
	 tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      }
      else if (tempType == CORNER_RIGHT) {
	 tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
	 tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      }
      else if (tempType == CORNER_LEFT) {
	 tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
	 tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      }
   }
}

void MapTile::setTile(int type) {
   for (int k = 0; k < 3; k++) {
      if (tile[k]) {
         scene->removeEntity(tile[k]);
         delete(tile[k]);
      }
   }
   this->tileType = type;
   
   if (tileType == INVIS_TILE) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 5, 5);
      tile[0]->setMaterialByName("InvisGridMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      occupied = true;
      tile[1] = NULL;
      tile[2] = NULL;
   }
   else if (tileType == TILE) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;
      
      tile[1] = NULL;
      tile[2] = NULL;
   }
   else if (tileType == LEFT_WALL_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == RIGHT_WALL_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == RIGHT_WALL_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5, 1, posZ*5 + 2);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == LEFT_WALL_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = NULL;
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == CORNER_BOT) {
      //left wall
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
      scene->addChild(tile[0]);
      
      //right wall
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == CORNER_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == CORNER_RIGHT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == CORNER_LEFT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      hasWall = 1;

      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == LEFT_DOOR_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5 - 2, 2, posZ*5);
      scene->addChild(tile[1]);
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == RIGHT_DOOR_TOP) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5, 2, posZ*5 - 2);
      scene->addChild(tile[1]);
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == LEFT_DOOR_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5, 2, posZ*5 + 2);
      scene->addChild(tile[1]);
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   else if (tileType == RIGHT_DOOR_BOT) {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[0]->setMaterialByName("FloorMaterial");
      tile[0]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5 + 2, 2, posZ*5);
      scene->addChild(tile[1]);
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   

   else if (tileType == CORNER_TOP_RIGHT_DOOR)
   {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("GreenMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   
   else if (tileType == CORNER_TOP_LEFT_DOOR)
   {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   
   else if (tileType == CORNER_LEFT_LEFT_TOP_DOOR)
   {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   
   else if (tileType == CORNER_LEFT_LEFT_BOT_DOOR)
   {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("GreenMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 - 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;

   }
   
   else if (tileType == CORNER_RIGHT_RIGHT_TOP_DOOR)
   {
      
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("GreenMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   
   else if (tileType == CORNER_RIGHT_RIGHT_BOT_DOOR)
   {
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 - 2);
      scene->addChild(tile[0]);
      
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;
   }
   
   else if (tileType == CORNER_BOT_RIGHT_DOOR)
   {
      //left wall
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("WallMaterial");
      tile[0]->setPosition(posX*5, 1, posZ*5 + 2);
      scene->addChild(tile[0]);
      
      //right wall
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("GreenMaterial");
      tile[1]->setPosition(posX*5 + 2, 2, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;

   }
   
   else if (tileType == CORNER_BOT_LEFT_DOOR)
   {
      //left wall
      tile[0] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 3, 1);
      tile[0]->setMaterialByName("GreenMaterial");
      tile[0]->setPosition(posX*5, 2, posZ*5 + 2);
      scene->addChild(tile[0]);
      
      //right wall
      tile[1] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 3, 5);
      tile[1]->setMaterialByName("WallMaterial");
      tile[1]->setPosition(posX*5 + 2, 1, posZ*5);
      scene->addChild(tile[1]);
      
      tile[2] = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 5, 1, 5);
      tile[2]->setMaterialByName("FloorMaterial");
      tile[2]->setPosition(posX*5, 0, posZ*5);
      scene->addChild(tile[2]);
      
      if (getObject())
         occupied = true;
      else
         occupied = false;

   }

   
   for (int i = 0; i < 3; i++) {
      if (tile[i]) {
         tile[i]->depthTest = true;
         tile[i]->depthWrite = true;
      }
   }
}


