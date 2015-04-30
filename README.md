Taverna
=======

Cal Poly Senior Project

Authors: Kevin Weber, Olin Olmstead, Bennett Schalich

A tavern management game with rogue-like elements.

The source code can be viewed under Windows/Template/Windows/Source.
The reason it is there is our partner had some issues using Windows 7 
and putting the source there fixed it.

Note: Unfortunately certain code in this game has been deprecated, so there 
   are some bugs present that were not present prior. One specifically nasty
   bug occurs if you click the end of the month menu without clicking a 
   specific button. The tavern will disappear in certain instances. 
   If this happens restarting is the only option.

Bennett Schalich: I created the entire building system, not all of
   which is featured in the final build sadly, but the code is there 
   and it does work. Unfortunately was buggy for those deleting tavern expansions, 
   making individualized rooms such as kitchens, bathrooms, etc, and a smart system 
   used to add and remove doors. It took me a good six weeks to get expansions to work 
   building from basically the ground up. I also worked on the the attributes of 
   the status menu and the data behind the AI. If you are looking at the source code
   I created just about everything in the "Map" folder, namely, Deleter, RoomNode, GameMap,
   Room, Door, TavernExpansion. Every other class in "Map" I contributed to in some way. 
   In the AI folder I contributed to GameController, Staff, and Person.


Note: The goal of this project was to create the beginnings 
   of a highly dynamic simulation game. Given 6 months time 
   we did what we could but many features could not be completed.
   The ability to delete expansions and individual rooms is programmed, 
   but not in the game due to UI issues. This game was built using Polycode, 
   an open source independent graphics engine. All of the game functionality 
   of this game is made from scratch.

You control what goes on in the tower. 
From pricing drinks to hiring and firing staff 
and even expanding your tavern. 

Movement - To move around the screen click the left mouse button and drag. 
   To zoom in and out use the scroll wheel.

Setting prices - you can set the price of your drinks by
   clicking the green tab in the main menu. 

Buying - at the end of each month you are allowed to buy more drinks
   of varying types. Click on the stock button on the end of the month 
   menu to both buy and set prices for varying drinks

Hiring and firing - you can fire the bartender (The man in green) or waiters 
   (wearing dark brown) at any time by clicking them and selecting "Fire". To
   hire waiters you have to wait until the end of the month menu appears and click  
   the staff tab. 

Building - At the end of the month menu click build to open the build menu, from that menu 
   click on any one of the build dimensions to select what type of expansion to make. Move the 
   mouse to the tile you want to build on and right click when the green circle appears. Rules: There are
   specific rules on where you can build expansions. They must have one wall completely flush against a wall of 
   the tavern. There can be no not empty tiles (non black tiles) in the area of the expansion. If this is 
   confusing to you, move your mouse near the tavern on the black tiles. A green circle indicates a valid 
   square to build on for thatexpansion. A red X indicated an invalid square to build that specific expansion 
   on. Tables can also be built by clicking the table button on the build menu. They can be placed in the 
   tavern anywhere a green circle appears. Right click to place. Expansions allow your bar to hold more people
   (increase capacity), allowing you to make money and increase your repuation faster.

People - Each person in the tavern can be clicked on to view information about them. Your waiter and bartender will automatically wait on people and serve drinks. Each customer has multiple attributes including level, health, happiness, thirst, hunger, and max purchase. These can be viewed by clicking on a particular person. Your goal as a player is to make the customers as happy as possible. Each persons happiness number is influenced by there thirst and hunger value. The max purchase of each customer is the max price they are willing to pay for a drink. Try to set prices as high as possible without turning away to many customers. 
    You will notice that customers will seat themselves, emote there opinions or feelings, and even group
    together.

Status Information - Your taverns status information is in the gray box on the bottom right. It displays how much gold you have to make purchases, your repuation/score, the capacity of the bar, and the current date.

The rest I leave for you to discover.

