# Oregon-Trail
This is a clone of the 1985 text based adventure game, Oregon Trail.

## Overview
The first version of this game was initially developed by Don Rawitsch, Bill Heinemann, and Paul Dillenberger in 1971. It was used as a learning tool in Minnesota to teach young children about what a journey along the Oregon Trail was actually like. The player travels from Independance, Missouri to Oregon City , Oregon in 1847. The trip is 2040 miles and the player has until November 30th, 1847 to reach Oregon City.

## Features 

#### Initial Conditions
1. The player is asked to enter their name and up to four other traveling companions
2. The player starts the game with $1200 but has to spend $200 on a wagon 
3. The player can visit the store to purchase various items
4. The player is given the choice to start on the default start date of 03/28/1847 but has the ability to choose a different start date      between 03/01/1847 and 05/01/1847
5. The player must arrive in Oregon City by November 30th, 1847
 
#### Visiting the Store 
The player can visit the store at the start of the game as well as multiple times throughout the game. The price of each item at the store increase by 25% for every subsequent store the player goes to so the player is incentivized to buy most of his supplies at the start of the game. The items that the player can buy at the store are as follows:

Oxen:
- There are 2 oxen in a yoke
- The starting price of oxen is $40/yoke
- The player must purchase in between 3 and 5 oxen at the beginning of the game

Food:
- The starting price of food is $0.50/lb
- It is recommended that the player purchases at least 200lbs of food for every member in his traveling party
- The wagon cannot hold more than 1000lbs of food 

Bullets:
- There are 20 bullets in a box of bullets
- The starting price of bullets is $2/box 

Miscellaneous Supplies:
- The player can purchase wagon parts or medical kits
- The starting price of wagon parts is $20/part 
- The starting price of medical kits is $25/kit

#### Resting
- Resting takes in between 1 and 3 days
- The health of the player increases by 5
- The group consumes 3lbs of food per player per day

#### Traveling
- The group travels in between 70 and 140 miles
- Traveling takes 14 days
- The traveling party consumes 3lbs of food per player per day

#### Hunting
If the player has at least 12 bullets they can go hunting. Hunting takes one day and the player can encounter the following animals:
- Rabbit (50%)
- Fox (25%)
- Deer (15%)
- Bear (7%)
- Moose (5%)

#### Events
After every turn there is a 40% chance of an event happening. The possible events are as follows:

Get Sick:
- If a group member gets sick the player can use a medical kit (if they have one) or press on without using one
- The group member will either live or die 
- If the leader dies the player can not continue and loses the game 

Oxen Dies:
- If an oxen dies but it is not the last oxen the player will continue on their journey
- If the player's last oxen dies the player can not continue and loses the game 

Wagon Breaks:
- If the wagon break the player can use a wagon part and continue on their journey
- If the player does not have any wagon parts the player can not continue and loses the game

Find Money:
- The player is told that they have found a treasure chest and can decide to open it or not open it 
- If they open the chest they find money and then can continue on with their journey

Kind Stranger:
- The player is approached by a stranger and is given the option to talk to the stranger or ignore the stranger
- If the player talks to the stranger, the stranger tells the player that he cannot keep all of his food and gives the rest of it to the player

#### Raider Attacks
The chance of a raider attacking is based of the miles the player has traveled. The player is more likely to encounter raiders at the beginning of the game. The player has the choice to run from the raiders, attack the raiders, or surrender to the raiders with the following consequences. 

Run:
- The player lives but while fleeing they lose 1 oxen, 10 lbs of food, and 1 wagon part

Attack:
- The player has to solve a puzzle to win the battle 
- If the player wins the battle they gain 50 lbs of food and 50 bullet
- If the player loses the battle they lose 1/4 of their money and 50 bullets

Surrender: 
- If the player surrenders they lose 1/4 of their cash 

#### Milestones 
When the player arrives at a milestone they have multiple options based on which type of milestone they arrive at. The player can either arrive at a river or a fort. 

River:
- When the player arrives at a river they can either rest or cross the river 
- If the river is deeper than 3 feet the player has to pay $10 per group member to cross

Fort:
- When the player arrives at a fort they can choose to rest, visit the store, or continue on their journey
- If the player chooses to rest 1 day passes and the 3 lbs of food are consumed per group member per day 

### Player Wins/Loses

Wins:
- The player wins once they arrive at Oregon City, Oregon
- The results of the game are printed into the file 'results.txt'

Loses:
- The player runs out of food 
- The player's last oxen dies 
- The player's health drops to 0 
- The player does not reach Oregon City by November 30th, 1847
- The group leader gets sick and dies
- The wagon breaks and the player does not have any spare wagon parts 
