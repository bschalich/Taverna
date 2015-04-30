#ifndef __Taverna__define__
#define __Taverna__define__

//structure types
#define INVIS_TILE 0
#define TILE 1
#define MOUSE_OVER_TILE 2
#define LEFT_WALL_TOP 3
#define RIGHT_WALL_TOP 4
#define CORNER_TOP 5
#define CORNER_BOT 6
#define CORNER_LEFT 7
#define CORNER_RIGHT 8
#define CORNER_BEAM_BOT 9
#define CORNER_BEAM_TOP 10
#define CORNER_BEAM_LEFT 11
#define CORNER_BEAM_RIGHT 12
#define FRONT_DOOR 13
#define LEFT_WALL_BOT 14
#define RIGHT_WALL_BOT 15
#define LEFT_DOOR_TOP 16
#define RIGHT_DOOR_TOP 17
#define LEFT_DOOR_BOT 18
#define RIGHT_DOOR_BOT 19
#define CORNER_BOT_RIGHT_DOOR 20
#define CORNER_BOT_LEFT_DOOR 21
#define CORNER_LEFT_LEFT_TOP_DOOR 22
#define CORNER_LEFT_LEFT_BOT_DOOR 23
#define CORNER_RIGHT_RIGHT_TOP_DOOR 24
#define CORNER_RIGHT_RIGHT_BOT_DOOR 25
#define CORNER_TOP_RIGHT_DOOR 26
#define CORNER_TOP_LEFT_DOOR 27
#define CANT_BUILD_TILE 28

//building sides
#define LEFT_BOT_SIDE 21
#define RIGHT_BOT_SIDE 22
#define LEFT_TOP_SIDE 23
#define RIGHT_TOP_SIDE 24

//room IDs
#define NOTHING -3
#define INITIAL_STRUCTURE -2
#define TAVERN_EXPANSION -1

//building dimension
#define DIM 40
#define MAX_DIM 5

//Game modes
#define GAME_MODE 0
#define MENU_MODE 1
#define MAP_MODE 2
#define DELETE_MODE 3
#define ADD_DOOR 4
#define REMOVE_DOOR 5
#define TABLE_MODE 6

//Sides to remove doors
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOT_LEFT 2
#define BOT_RIGHT 3

//Rooms
#define KITCHEN 0
#define BEDCHAMBER 1
#define RESTROOM 2

//Person
#define VAR_NUM 2
#define NEUTRAL_HAPPINESS 40

//Staff
#define STAFF_LVL1_PAY 30
#define STAFF_LVL2_PAY 70
#define STAFF_LVL3_PAY 150

#define STAFF_LVL1_SPEED 10
#define STAFF_LVL2_SPEED 13
#define STAFF_LVL3_SPEED 16

//Month
#define MONTH_TIME_SECONDS 120

#endif
