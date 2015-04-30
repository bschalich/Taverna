#include "GameData.h"

GameData *GameData::gameDataInstance = 0;

GameData::GameData() {
	rep = 500;
	roomWidth = 1;
	roomHeight = 1;
	roomType = 0;
   personID = 0;
   day = 0;

   curMonth = JANUARY;
   
   initSound();
   year = 1099;
}

GameData* GameData::getInstance()
{
	if (!gameDataInstance)
	{
		gameDataInstance = new GameData();
	}
   
	return gameDataInstance;
}

void GameData::initSound()
{
   placeTileSound = new Sound("bookPlace1.ogg", false);
   placeTileSound->setVolume(.1);
   deleteTileSound = new Sound("chop.ogg", false);
   deleteTileSound->setVolume(.1);
   
   doorCloseSound = new Sound("doorClose_3.ogg");
   doorCloseSound->setVolume(.1);
   doorOpenSound = new Sound("doorOpen_2.ogg");
   doorOpenSound->setVolume(.1);
   
   //ask olin where this should go
   buyStockSound = new Sound("handleCoins.ogg");
   buyStockSound->setVolume(.1);
   
   //I've already put this in the month menu
   //ask olin where else it should go
   clickSound = new Sound("click3.ogg");
   clickSound->setVolume(.2);
   
   crowdNoiseSound = new Sound("crowdNoise.ogg");
   crowdNoiseSound->setVolume(1);
}

void GameData::Update() {
}

int GameData::getNextPersonID() {
   return ++personID;
}

void GameData::setCore(Core *core) {
	this->core = core;
}

void GameData::set3DScene(CollisionScene *scene3D) {
	this->scene3D = scene3D;
}

void GameData::set2DScene(Scene *scene2D) {
	this->scene2D = scene2D;
}

void GameData::setGameMap(GameMap *gameMap) {
	this->map = gameMap;
}

void GameData::setMode(int mode) {
	this->gameMode = mode;
}

GameMap* GameData::getGameMap() {
	return map;
}

int GameData::getRoomWidth() {
	return roomWidth;
}

void GameData::setRoomWidth(int width) {
	roomWidth = width;
}

int GameData::getRoomHeight() {
	return roomHeight;
}

void GameData::setRoomHeight(int height) {
	roomHeight = height;
}

/**
 * Gets the game mode
 */
int GameData::getGameMode() {
	return gameMode;
}

/**
 * Set game mode
 */
void GameData::setGameMode(int mode) {
	gameMode = mode;
}

/**
 * Gets the core
 */
Core* GameData::getCore() {
	return core;
}

/**
 * Gets the 3D Scene
 */
CollisionScene* GameData::getScene3D() {
	return scene3D;
}

/**
 * Gets the 2D Scene
 */
Scene* GameData::getScene2D() {
	return scene2D;
}

int GameData::getRep()
{
	return rep;
}

void GameData::setRoomType(int type)
{
	roomType = type;
}

int GameData::getRoomType()
{
	return roomType;
}

void GameData::setDoorSide(int side)
{
	doorSide = side;
}

int GameData::getDoorSide()
{
	return doorSide;
}

void GameData::setUpParticleEmitters()
{
   setUpAddPE();
   setUpDeletePE();
   setUpFirePE();
}

void GameData::setDay(Number day)
{
	this->day = day;
	dispatchResourcesEvent();
}

Number GameData::getDay()
{
	return day;
}

void GameData::setUpAddPE()
{
   //Adding
   addPE = new SceneParticleEmitter(200, 2, 20);
   addPE->depthTest = true;
   addPE->depthWrite = true;
   addPE->setEmitterSize(Vector3(10, 10, 10));
   addPE->setDirectionDeviation(Vector3(10, 4, 10));
   addPE->setParticleDirection(Vector3(0, 1, 0));
   addPE->setGravity(Vector3(0, -1, 0));
   addPE->setParticleType(SceneParticleEmitter::PARTICLE_TYPE_QUAD);
   addPE->setParticleSize(1);
   
   addPE->useScaleCurve = true;
   addPE->scaleCurve.addControlPoint2d(0, 0.1);
   addPE->scaleCurve.addControlPoint2d(0.5, 0.3);
   addPE->scaleCurve.addControlPoint2d(1, 0);
   
   addPE->useColorCurves = true;
   addPE->colorCurveR.addControlPoint2d(0, 0.3);
   addPE->colorCurveR.addControlPoint2d(0.1, 1);
   addPE->colorCurveR.addControlPoint2d(0.4, 1);
   addPE->colorCurveR.addControlPoint2d(0.5, 0);
   addPE->colorCurveR.addControlPoint2d(1, 0);
   
   addPE->colorCurveG.addControlPoint2d(0, 0.3);
   addPE->colorCurveG.addControlPoint2d(0.1, 0.6);
   addPE->colorCurveG.addControlPoint2d(0.4, 0.6);
   addPE->colorCurveG.addControlPoint2d(0.5, 0);
   addPE->colorCurveG.addControlPoint2d(1, 0.0);
   
   addPE->colorCurveB.addControlPoint2d(0, 1);
   addPE->colorCurveB.addControlPoint2d(0.1, 0);
   addPE->colorCurveB.addControlPoint2d(1, 0);
   
   addPE->colorCurveA.addControlPoint2d(0, 0);
   addPE->colorCurveA.addControlPoint2d(0.05, 1);
   addPE->colorCurveA.addControlPoint2d(0.6, 1);
   addPE->colorCurveA.addControlPoint2d(1, 0);
   
   addPE->setLoopParticles(false);
   addPE->setPosition(-100, 0, -100);
   scene3D->addChild(addPE);
}

void GameData::setUpDeletePE()
{
   deletePE = new SceneParticleEmitter(200, 2, 20);
   deletePE->depthTest = true;
   deletePE->depthWrite = true;
   deletePE->setEmitterSize(Vector3(10, 10, 10));
   deletePE->setDirectionDeviation(Vector3(10, 4, 10));
   deletePE->setParticleDirection(Vector3(0, 1, 0));
   deletePE->setGravity(Vector3(0, -1, 0));
   deletePE->setParticleType(SceneParticleEmitter::PARTICLE_TYPE_QUAD);
   deletePE->setParticleSize(1);
   
   deletePE->useScaleCurve = true;
   deletePE->scaleCurve.addControlPoint2d(0, 0.1);
   deletePE->scaleCurve.addControlPoint2d(0.5, 0.3);
   deletePE->scaleCurve.addControlPoint2d(1, 0);
   
   deletePE->useColorCurves = true;
   deletePE->colorCurveR.addControlPoint2d(0, 0.3);
   deletePE->colorCurveR.addControlPoint2d(0.1, 1);
   deletePE->colorCurveR.addControlPoint2d(0.4, 1);
   deletePE->colorCurveR.addControlPoint2d(0.5, 0);
   deletePE->colorCurveR.addControlPoint2d(1, 0);
   
   deletePE->colorCurveG.addControlPoint2d(0, 0.0);
   deletePE->colorCurveG.addControlPoint2d(0.0, 0.0);
   deletePE->colorCurveG.addControlPoint2d(0.0, 0.0);
   deletePE->colorCurveG.addControlPoint2d(0.0, 0);
   deletePE->colorCurveG.addControlPoint2d(0, 0.0);
   
   deletePE->colorCurveB.addControlPoint2d(1, 1);
   deletePE->colorCurveB.addControlPoint2d(1, 0);
   deletePE->colorCurveB.addControlPoint2d(1, 0);
   
   deletePE->colorCurveA.addControlPoint2d(0, 0);
   deletePE->colorCurveA.addControlPoint2d(0.05, 1);
   deletePE->colorCurveA.addControlPoint2d(0.6, 1);
   deletePE->colorCurveA.addControlPoint2d(1, 0);
   
   deletePE->setLoopParticles(false);
   deletePE->setPosition(-100, 0, -100);
   scene3D->addChild(deletePE);
}

void GameData::setUpFirePE()
{
   firePE = new SceneParticleEmitter(100, 2, 20);
   firePE->depthTest = true;
   firePE->depthWrite = true;
   firePE->setEmitterSize(Vector3(3, 3, 3));
   firePE->setDirectionDeviation(Vector3(10, 4, 10));
   firePE->setParticleDirection(Vector3(0, 1, 0));
   firePE->setGravity(Vector3(0, -1, 0));
   firePE->setParticleType(SceneParticleEmitter::PARTICLE_TYPE_QUAD);
   firePE->setParticleSize(0.7);
   
   firePE->useScaleCurve = true;
   firePE->scaleCurve.addControlPoint2d(0, 0.1);
   firePE->scaleCurve.addControlPoint2d(0.5, 0.3);
   firePE->scaleCurve.addControlPoint2d(1, 0);
   
   firePE->useColorCurves = true;
   firePE->colorCurveR.addControlPoint2d(0, 0.3);
   firePE->colorCurveR.addControlPoint2d(0.3, 0.7);
   firePE->colorCurveR.addControlPoint2d(0.1, 1);
   firePE->colorCurveR.addControlPoint2d(0.4, 1);
   
   firePE->colorCurveG.addControlPoint2d(0.4, 0.0);
   firePE->colorCurveG.addControlPoint2d(0.2, 0.0);
   firePE->colorCurveG.addControlPoint2d(0.7, 0.2);
   firePE->colorCurveG.addControlPoint2d(0.6, 0.4);
   firePE->colorCurveG.addControlPoint2d(0, 0.0);
   
   firePE->colorCurveB.addControlPoint2d(0, 0);
   firePE->colorCurveB.addControlPoint2d(0, 0);
   firePE->colorCurveB.addControlPoint2d(0, 0);
   
   firePE->colorCurveA.addControlPoint2d(0, 0);
   firePE->colorCurveA.addControlPoint2d(0.05, 1);
   firePE->colorCurveA.addControlPoint2d(0.6, 1);
   firePE->colorCurveA.addControlPoint2d(1, 0);
   
   firePE->setLoopParticles(false);
   firePE->setPosition(-100, 0, -100);
   scene3D->addChild(firePE);
}

String GameData::getMonth()
{
	if (curMonth == JANUARY)
      return "January";
	else if (curMonth == FEBRUARY)
		return "February";
	else if (curMonth == MARCH)
		return "March";
	else if (curMonth == APRIL)
		return "April";
	else if (curMonth == MAY)
		return "May";
	else if (curMonth == JUNE)
		return "June";
	else if (curMonth == JULY)
		return "July";
	else if (curMonth == AUGUST)
		return "August";
	else if (curMonth == SEPTEMBER)
		return "September";
	else if (curMonth == OCTOBER)
		return "October";
	else if (curMonth == NOVEMBER)
		return "November";
	else if (curMonth == DECEMBER)
		return "December";
}

void GameData::incrementMonth()
{
	if (curMonth == JANUARY)
		curMonth = FEBRUARY;
	else if (curMonth == FEBRUARY)
		curMonth = MARCH;
	else if (curMonth == MARCH)
		curMonth = APRIL;
	else if (curMonth == APRIL)
		curMonth = MAY;
	else if (curMonth == MAY)
		curMonth = JUNE;
	else if (curMonth == JUNE)
		curMonth = JULY;
	else if (curMonth == JULY)
		curMonth = AUGUST;
	else if (curMonth == AUGUST)
		curMonth = SEPTEMBER;
	else if (curMonth == SEPTEMBER)
		curMonth = OCTOBER;
	else if (curMonth == OCTOBER)
		curMonth = NOVEMBER;
	else if (curMonth == NOVEMBER)
		curMonth = DECEMBER;
	else if (curMonth == DECEMBER)
   {
      year++;
		curMonth = JANUARY;
   }

	core->dispatchEvent(new Event(Event::RESOURCE_CHANGE_EVENT), Event::RESOURCE_CHANGE_EVENT);
}

String GameData::getDayString()
{
	switch ((int)day) {
	case 1: return "1"; break;
	case 2: return "2"; break;
	case 3: return "3"; break;
	case 4: return "4"; break;
	case 5: return "5"; break;
	case 6: return "6"; break;
	case 7: return "7"; break;
	case 8: return "8"; break;
	case 9: return "9"; break;
	case 10: return "10"; break;
	case 11: return "11"; break;
	case 12: return "12"; break;
	case 13: return "13"; break;
	case 14: return "14"; break;
	case 15: return "15"; break;
	case 16: return "16"; break;
	case 17: return "17"; break;
	case 18: return "18"; break;
	case 19: return "19"; break;
	case 20: return "20"; break;
	case 21: return "21"; break;
	case 22: return "22"; break;
	case 23: return "23"; break;
	case 24: return "24"; break;
	case 25: return "25"; break;
	case 26: return "26"; break;
	case 27: return "27"; break;
	case 28: return "28"; break;
	case 29: return "29"; break;
	case 30: return "30"; break;
	default: return "0"; break; 
	}
}

void GameData::dispatchResourcesEvent()
{
	core->dispatchEvent(new Event(Event::RESOURCE_CHANGE_EVENT), Event::RESOURCE_CHANGE_EVENT);
}