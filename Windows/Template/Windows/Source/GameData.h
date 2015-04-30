#ifndef __Taverna__GameData__
#define __Taverna__GameData__

class GameMap;
class GameUI;

#include "define.h"
#include "Polycode.h"
#include "Polycode3DPhysics.h"
#include "GameMap.h"
//#include "GameUI.h"
#include <vector>
#include <unordered_map>

using namespace Polycode;

class GameData {
   
public:
   
   static GameData *getInstance();
   void setCore(Core *core);
   void set3DScene(CollisionScene *polyscene3D);
   void set2DScene(Scene *polyscene2D);
   void setGameMap(GameMap *gameMap);
   void setMode(int mode);
   void setUpParticleEmitters();

   enum Month {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST,
			   SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

   Core *core;
   CollisionScene *scene3D;
   Scene *scene2D;
   GameMap *map;
   int gameMode;
   
   void setGameMode(int mode);
   int getGameMode();
   Core* getCore();
   CollisionScene* getScene3D();
   Scene* getScene2D();
   GameMap* getGameMap();

   //rooms
   int getRoomWidth();
   int getRoomHeight();
   void setRoomWidth(int width);
   void setRoomHeight(int height);
   int getRep();
   void setRoomType(int type);
   int getRoomType();

   //doors
   void setDoorSide(int side);
   int getDoorSide();
   
   String getMonth();
   void incrementMonth();

   int getNextPersonID();

   vector<String> npcNames;
   unordered_map<int, SceneSprite*> personTable;
   
   void setUI(GameUI *gameUI);
   //GameUI* getUI();

   Number getDay();
   String getDayString();
   void setDay(Number day);
   
   //sounds
   Sound *placeTileSound;
   Sound *deleteTileSound;
   Sound *tavernMusic;
   Sound *doorCloseSound;
   Sound *doorOpenSound;
   Sound *buyStockSound;
   Sound *clickSound;
   Sound *crowdNoiseSound;

   //particles emitters
   SceneParticleEmitter *addPE;
   SceneParticleEmitter *deletePE;
   SceneParticleEmitter *firePE;

   void Update();

private:
	GameData();
   void setUpAddPE();
   void setUpDeletePE();
   void setUpFirePE();
	static GameData *gameDataInstance;
   void initSound();
   
   int personID;
	int rep;
	int roomType;
	int roomWidth;
   int roomHeight;
	int doorSide;

	Month curMonth;
	Number day;
   Number year;

	//GameUI *gameUI;
	void dispatchResourcesEvent();
};



#endif