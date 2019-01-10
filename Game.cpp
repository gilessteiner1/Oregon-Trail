//Giles Steiner
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Game.h"
#include "Store.h"
#include "Event.h"
#include "Time.h"
#include "Random.h"
using namespace std;



/*
default Constructor 
resets all crucial data members including vectors
*/
Game::Game(){
    
        //these lines make sure the vectors used to set the date at the beginning of the game and hold the name of our group_members are reset and empty 
        vector<string> blank_string_vector = {"","","",""};
        vector<int> blank_int_vector = {0,0,0};
        group_members.swap(blank_string_vector); 
        date.swap(blank_int_vector); 
        my_time.setDate(date); 
        
        //resets crucial data members
        leader_name = "";
        number_of_players = 0;
        miles_traveled = 0;
        number_of_store_visits = 0;
        health = 0;

}



/*
parameterized Constructor 
sets all crucial data members including the vectors for date and group_members
*/
Game::Game(string name,vector<string> companion_names,vector<int> start_date){

    leader_name = name;
    bool leader_status;
    miles_traveled = 0;
    number_of_store_visits = 0;
    health = 100;
    
    group_members.swap(companion_names);
    group_members.insert(group_members.begin(),leader_name);
    number_of_players = group_members.size();
    date.swap(start_date);
    my_time.setDate(date);

}



/*
returns the position where a ',' is. used as a helper function when parsing .txt files
*/
int Game::findDelimiterPosition(string my_string){
    
    char my_delimiter = ',';
    int delimiter_position = 0;

    for(int i = 0; i < my_string.length(); i++){
        if(my_string[i] == my_delimiter){
            delimiter_position = i;
        }
    }
    return delimiter_position;
    
}



/*
returns the line number (index) of the milestone 
*/
int Game::getMilestoneIndex(string filename, int milestone_distance){
    
    int next_milestone_index = 0;
    string line = "";
    vector<int> milestone_distances;
    ifstream myfilestream;
    
    myfilestream.open(filename);
    if(myfilestream.is_open() == true){
        while(getline(myfilestream,line)){
            if(line != ""){
                milestone_distances.push_back(stoi(line.substr(findDelimiterPosition(line)+1)));
            }
            else{
                break;
            }
        }
        
        //finds the index of the next milestone
        for(int i = 0; i < milestone_distances.size(); i++){
            if(milestone_distances.at(i) == milestone_distance){
                next_milestone_index = i;
            }
        }
    }
    else{   
        next_milestone_index = -1;
    }
    return next_milestone_index;
    
}



/*
returns the name of the milestone at a specific distance
*/
string Game::getMilestoneName(string filename, int milestone_distance){
    
    int milestone_index = 0;
    string milestone_name;
    string line = "";
    vector<string> milestone_names;
    vector<int> milestone_distances;
    ifstream myfilestream;
    
    myfilestream.open(filename);
    if(myfilestream.is_open() == true){
        while(getline(myfilestream,line)){
            if(line != ""){
                milestone_names.push_back(line.substr(1,findDelimiterPosition(line)-1)); 
            }
        }
         milestone_name = milestone_names.at(getMilestoneIndex("milestones.txt",milestone_distance));
    }
    else{
        milestone_name = "";
    }
    return milestone_name;
    
}
    
    
    
/*
inputs a file containing milestone and their distances 
creates a vector of milestone distances and milestone names
loops through all the milestone distances in the vector and finds the index of the next one based on the players' miles_traveled
returns the value of the milestone distance vector at that index
*/
int Game::distanceUntilNextMilestone(string filename){
    
    int next_milestone_index = 0;
    int distance_until_next_milestone;
    string line = "";
    vector<int> milestone_distances;
    ifstream myfilestream;
    
    myfilestream.open(filename);
    if(myfilestream.is_open() == true){
        while(getline(myfilestream,line)){
            if(line != ""){
                milestone_distances.push_back(stoi(line.substr(findDelimiterPosition(line)+1)));
            }
            else{
                break;
            }
        }
        
        //finds the index of the next milestone
        for(int i = 0; i < milestone_distances.size()-1; i++){
            if(miles_traveled >= milestone_distances.at(i) && miles_traveled < milestone_distances.at(i+1)){
                next_milestone_index = i+1;
            }
        }
        distance_until_next_milestone = milestone_distances.at(next_milestone_index) - miles_traveled;
    }
    else{   
        distance_until_next_milestone = -1;
    }
    return distance_until_next_milestone;
    
}



/*
inputs a file containing milestone and their distances 
creates a vector of milestone distances and milestone names
loops through all the milestone distances in the vector and finds the index of the next one based on the players' miles_traveled
returns the value of the milestone name vector at that index
*/
string Game::nextMilestoneName(string filename){
    
    int next_milestone_index = 0;
    string next_milestone_name;
    string line = "";
    vector<string> milestone_names;
    vector<int> milestone_distances;
    ifstream myfilestream;
    
    myfilestream.open(filename);
    if(myfilestream.is_open() == true){
        while(getline(myfilestream,line)){
            if(line != ""){
                milestone_distances.push_back(stoi(line.substr(findDelimiterPosition(line)+1))); 
                milestone_names.push_back(line.substr(1,findDelimiterPosition(line)-1)); 
            }
        }
        
        //finds the index of the next milestone
        for(int i = 0; i < milestone_distances.size()-1; i++){
            if(miles_traveled >= milestone_distances.at(i) && miles_traveled < milestone_distances.at(i+1)){
                next_milestone_index = i+1;
            }
        }
        next_milestone_name = milestone_names.at(next_milestone_index);
    }
    else{
        next_milestone_name = "";
    }
    return next_milestone_name;
    
}



/*
proxy function. uses my_store object to call a function of the store class 
first visit is consider the 0 visit
*/
void Game::Shop(int visits){
    
    my_store.firstStore(visits);
    number_of_store_visits += 1;
    
}



/*
proxy function. uses my_event object to call a function of the event class passing the store object by reference
there is a 40% chance of a misfortune occuring every turn
this also calls the raiderAttack() function which has its own probability of occuring
*/
bool Game::randomEvent(){
    
    bool end_game;
    int chance_of_misfortune;
    
    chance_of_misfortune = my_random.Generate(1,10);
    if(chance_of_misfortune < 5){
        end_game = my_event.randomEvent(my_store,my_time,group_members,leader_name);
        if(end_game == true){
            return end_game;
        }
    }
    else{
        end_game = false;
    }
    raiderAttack();
    return end_game;
    
}



//prints out important data memebers every turn to show the player how they are doing
void Game::statusUpdate(){
    
    vector<int> date = my_time.getDate();
    
    cout << "CURRENT DATE: " << date[0] << "/" << date[1] << "/" << date[2] << endl;
    cout << "MILES TRAVELED: " << miles_traveled << " MILES "<< endl;
    cout << "DISTANCE TO NEXT MILESTONE: " << distanceUntilNextMilestone("milestones.txt")  << " MILES"<< endl;
    cout << "FOOD AVAILABLE: " << my_store.getFood() << " LBS" << endl;
    cout << "NUMBER OF BULLETS: " << my_store.getBullets() << " BULLETS" << endl;
    cout << "CASH AVAILABLE: $" << my_store.getMoney() << endl;
    cout << "HEALTH: " << health << endl << endl;
    
}



/*
this function handles when the player arrives at a milestone
it parses the milestones.txt file to see if the milestone is a river or a fort 
if the milestone is a river is parses rivers.txt to check how deep the river is and gives player option to rest or cross the river
if the miletsone is a fort the player can rest, go to the store, or continue 
*/
void Game::Milestone(string filename, int milestone_index){

    int food_consumed;
    int river_depth;
    int crossing_price;
    string choice1 = "";
    string choice2 = "";
    string line = "";
    string line2= "";
    string milestone_type;
    ifstream myfilestream;
    
    myfilestream.open(filename);
    if(myfilestream.is_open() == true){
        int i = 0; //keeps track of the line numbers in the milestones.txt file
        int j = 0; //keeps track of the line numebers in the rivers.txt file
        while(getline(myfilestream,line)){
            if(line != ""){
                if(milestone_index == i){
                    milestone_type = line.substr(0,1); //if confusing check formatting in milestones.txt 
                    
                    //crossing a river
                    if(milestone_type == "r"){
                        cout << "WOULD YOU LIKE TO REST OR CROSS THE RIVER." << endl;
                        cout << "ENTER REST OR CROSS THE RIVER" << endl;
                        
                        //inputs whether the user wants to rest or cross the river 
                        while(choice1 != "REST" && choice1 != "rest" && choice1 != "CROSS" && choice1 != "cross"){
                            cin >> choice1;
                            if(choice1 == "REST" || choice1 == "rest" || choice1 == "CROSS" || choice1 == "cross"){
                                break;
                            }
                            else{
                                cout << "INVALID INPUT. PLEASE ENTER REST OR CROSS THE RIVER"<< endl;
                            }
                        }
                        
                        //handles when the player decides to rest. keeps looping until they decide to cross the river
                        if(choice1 == "REST" || choice1 == "rest"){
                            while(choice2 != "CROSS" && choice2 != "cross"){
                                if(choice2 == "CROSS" || choice2 == "cross"){
                                        break;
                                }
                                else{
                                    food_consumed = 3*number_of_players;
                                    my_time.Travel(1);
                                    my_store.setFood(my_store.getFood()-food_consumed);
                                    if(health + 5 > 100){
                                        health = 100;
                                    }
                                    else{
                                        health += 5;
                                    }
                                    cout << "YOU REST FOR A DAY CONSUMING " << food_consumed << " POUNDS OF FOOD." << endl << endl;
                                    while(choice2 != "CROSS" && choice2 != "cross"){
                                        cout << "WOULD YOU LIKE TO REST AGAIN OR CROSS THE RIVER?" << endl;
                                        cout << "ENTER REST OR CROSS THE RIVER." << endl;
                                        cin >> choice2;
                                        if(choice2 == "CROSS" || choice2 == "cross"){
                                            choice1 = choice2;
                                            break;
                                        }
                                        else if(choice2 == "REST" || choice2 == "rest"){
                                            choice1 = choice2;
                                            break;
                                        }
                                        else{
                                            cout << "INVALID INPUT." << endl;
                                            cout << "PLEASE ENTER REST OR CROSS THE RIVER." << endl;
                                            cin >> choice2;
                                        }
                                    }
                                }
                                
                            }
                        }
                        
                        //handles when the player decides to cross the river
                        if(choice1 == "CROSS" || choice1 == "cross"){
                            ifstream myfilestream2;
                            myfilestream2.open("rivers.txt");
                            while(getline(myfilestream2,line2)){
                                if(line != ""){
                                    if(milestone_index == j){
                                        river_depth = stoi(line2.substr(findDelimiterPosition(line2)+1));
                                        if(river_depth > 3){
                                            crossing_price = 10*number_of_players;
                                            cout << "THE RIVER IS DEEP AND YOU NEED TO BUY A FERRY." << endl;
                                            cout << "THE FERRY COSTED YOU $" << crossing_price << " BUT YOU HAVE CROSSED THE RIVER." << endl << endl;
                                            my_store.setMoney(my_store.getMoney()-crossing_price);
                                            break;
                                        }
                                        else{
                                            cout << "THE RIVER WAS SHALLOW AND YOU WERE ABLE TO CROSS WITHOUT A FERRY." << endl << endl;
                                            break;
                                        }
                                    }
                                    j += 1;
                                }
                            }
                        }
                    }
            
                    //crossing a fort
                    if(milestone_type == "f"){
                        cout << "WOULD YOU LIKE TO REST, VISIT THE STORE, OR CONTINUE?" << endl;
                        cout << "PLEASE ENTER REST, STORE, OR CONTINUE." << endl;
                        
                        //inputs whether the player decides to rest, visit the store, or continue on their journey
                        while(choice1 != "REST" && choice1 != "rest" && choice1 != "STORE" && choice1 != "store" && choice1 != "CONTINUE" && choice1 != "continue"){
                            cin >> choice1;
                            if(choice1 == "REST" || choice1 == "rest" || choice1 == "STORE" || choice1 == "store" || choice1 == "CONTINUE" || choice1 == "continue"){
                                break;
                            }
                            else{
                                cout << "INVALID INPUT. PLEASE ENTER REST, STORE, OR, CONTINUE?"<< endl;
                            }
                        }
                        //keeps looping until the player decides to continue on their journey
                        while(choice1 == "REST" || choice1 == "rest" || choice1 == "STORE" || choice1 == "store"){
                            if(choice1 == "REST" || choice1 == "rest"){
                                food_consumed = 3*number_of_players;
                                my_time.Travel(1);
                                my_store.setFood(my_store.getFood()-food_consumed);
                                if(health + 5 > 100){
                                    health = 100;
                                }
                                else{
                                health += 5;
                                }
                                cout << "YOU REST FOR A DAY CONSUMING " << food_consumed << " POUNDS OF FOOD." << endl << endl;
                                cout << "WOULD YOU LIKE TO REST, VISIT THE STORE, OR CONTINU?!" << endl;
                                cout << "PLEASE ENTER REST, STORE, OR CONTINUE." << endl;
                                cin >> choice1;
                            }
                            else if(choice1 == "STORE" || choice1 == "store"){
                                Shop(number_of_store_visits);
                                cout << endl;
                                cout << "WOULD YOU LIKE TO REST, VISIT THE STORE, OR CONTINUE?" << endl;
                                cout << "PLEASE ENTER REST, STORE, OR CONTINUE." << endl;
                                cin >> choice1;
                                cout << endl << endl;
                            }
                            else if(choice1 == "CONTINUE" || choice1 =="continue"){
                                break;
                            }    
                        }
                    }
                }
                i += 1;
            }
        }
    }
    else{
        cout << "ERROR: FILE COULD NOT BE LOADED" << endl; 
    }
    
}



/*
the player rests for in between 1 and 3 days and consumes 3 lbs of food per group member per day 
the players health increases by 5
*/
void Game::Rest(){
    
    int days_of_rest;
    int food_consumed;
    
    days_of_rest = my_random.Generate(1,3);
    food_consumed = number_of_players*3*days_of_rest;
    my_store.setFood(my_store.getFood()-food_consumed); 
    my_time.Travel(days_of_rest);
    if(health + 5 > 100){
        health = 100;
    }
    else{
        health += 5;
    }
    
}



/*
the player continues on their journey for 14 days 
the player travels in between 70 and 140 miles
the player consumes 3 lbs of food per group member per day 
if the player will surpass the milestone the game has them stop at the milestone and then calls the Milestone() function to give the player options based on if the milestone is a river or a fort 
*/
void Game::Continue(){
    
    int days_on_trail = 14;
    int food_consumed;
    int random_distance;
    
    food_consumed = number_of_players*3*days_on_trail;
    my_store.setFood(my_store.getFood()-food_consumed);
    random_distance = my_random.Generate(70,140);
    my_time.Travel(days_on_trail);
    health -= 10;
    
    if(random_distance > distanceUntilNextMilestone("milestones.txt") && miles_traveled < 1863){
        miles_traveled += distanceUntilNextMilestone("milestones.txt");
        cout << "YOU WERE PREPARED TO TRAVEL " << random_distance << " MILES BUT ARRIVED AT " << getMilestoneName("milestones.txt",miles_traveled) << endl << endl;
        Milestone("milestones.txt",getMilestoneIndex("milestones.txt",miles_traveled));
    }
    
    else{
        miles_traveled += random_distance;
    }
    
}



//the player spends a day hunting
bool Game::Hunt(){
    
    int random_number;
    int food_gained = 0;
    int food_consumed = 0;
    bool correct_puzzle;
    bool successful_hunt = false;
    bool keep_running = true; //boolean used to stay in a while loop to keep asking the user to enter input if they enter something invalid;
    
    string decision = ""; //stores if the player wants to hunt
    string dinner = ""; //stores how well the player wants to eat if they choose to hunt 
    string animals[5] = {"RABBIT","FOX","DEER","BEAR","MOOSE"}; //stores the different animals the player could encounter
    my_time.Travel(1); //Hunting takes 1 day
    
    //traverses array of animals and hunts each
    for(int i = 0; i < 5; i++){
        
        switch(i){
            
            //rabbit: %50 chance of encountering
            case 0:
            
                random_number = my_random.Generate(1,100);
                if(random_number < 51){
                    cout << "YOU GOT LUCKY! YOU ENCOUNTERED A " << animals[i] << "! DO YOU WANT TO HUNT?" << endl;
                    cout << "ENTER Y FOR YES AND N FOR NO : " << endl;
                    while(keep_running == true){
                        cin >> decision;
                        if(decision == "N" || decision == "n"){
                            cout << "THERE IS ALWAYS NEXT TIME. GOOD LUCK WITH THE REST OF THE JOURNEY." << endl << endl;
                            keep_running = false;
                        }
                        else if(decision == "Y" || decision == "y"){
                            if(my_store.getBullets() < 12){
                                cout << "YOU DO NOT HAVE ENOUGH BULLETS TO GO HUNTING" << endl << endl;
                                keep_running = false;
                            }
                            else{
                                correct_puzzle = Puzzle();
                                if(correct_puzzle == true){
                                    food_gained += 2;
                                    cout << "CONGRATS, YOU KILLED A RABBIT. YOU USED 10 BULLETS BUT GAINED " << food_gained << " POUNDS OF FOOD." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-10);
                                    keep_running = false;
                                    successful_hunt = true;
                                }
                                else{
                                    cout << "YOU BULLETS MISSED AND THE RABBIT GOT AWAY." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-10);
                                    keep_running = false;
                                }
                            }
                        }
                        else{
                            cout << "YOU ENTERED AN INVALID INPUT PLEASE ENTER Y FOR YES OR N NO" << endl;
                        }
                    }
                    keep_running = true; //once i exit the while loop I set this equal to true in case the player encounters another animal
                }
                break;
            
             //fox: 26% chance of encountering    
            case 1:
            
                random_number = my_random.Generate(1,100);
                if(random_number < 26){
                    cout << "YOU GOT LUCKY! YOU ENCOUNTERED A " << animals[i] << "! DO YOU WANT TO HUNT?" << endl;
                    cout << "ENTER Y FOR YES AND N FOR NO : " << endl;
                    while(keep_running == true){
                        cin >> decision;
                        if(decision == "N" || decision == "n"){
                            cout << "THERE IS ALWAYS NEXT TIME. GOOD LUCK WITH THE REST OF THE JOURNEY." << endl << endl;
                            keep_running = false;
                        }
                        else if(decision == "Y" || decision == "y"){
                            if(my_store.getBullets() < 12){
                                cout << "YOU DO NOT HAVE ENOUGH BULLETS TO GO HUNTING" << endl << endl;
                                keep_running = false;
                            }
                            else{
                                correct_puzzle = Puzzle();
                                if(correct_puzzle == true){
                                    food_gained += 5;
                                    cout << "CONGRATS, YOU KILLED A FOX. YOU USED 8 BULLETS BUT GAINED " << food_gained << " POUNDS OF FOOD." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-8);
                                    keep_running = false;
                                    successful_hunt = true;
                                }
                                else{
                                    cout << "YOU BULLETS MISSED AND THE FOX GOT AWAY." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-8);
                                    keep_running = false;
                                }
                            }
                        }
                        else{
                            cout << "YOU ENTERED AN INVALID INPUT PLEASE ENTER Y FOR YES OR N NO" << endl;
                        }
                    }
                    keep_running = true; //once i exit the while loop I set this equal to true in case the player encounters another animal
                }
                     
                break;
                
            //deer: 15% chance of encountering
            case 2:
            
                random_number = my_random.Generate(1,100);
                if(random_number < 16){
                    cout << "YOU GOT LUCKY! YOU ENCOUNTERED A " << animals[i] << "! DO YOU WANT TO HUNT?" << endl;
                    cout << "ENTER Y FOR YES AND N FOR NO : " << endl;
                    while(keep_running == true){
                        cin >> decision;
                        if(decision == "N" || decision == "n"){
                            cout << "THERE IS ALWAYS NEXT TIME. GOOD LUCK WITH THE REST OF THE JOURNEY." << endl << endl;
                            keep_running = false;
                        }
                        else if(decision == "Y" || decision == "y"){
                            if(my_store.getBullets() < 12){
                                cout << "YOU DO NOT HAVE ENOUGH BULLETS TO GO HUNTING" << endl << endl;
                                keep_running = false;
                            }
                            else{
                                correct_puzzle = Puzzle();
                                if(correct_puzzle == true){
                                    food_gained += my_random.Generate(30,55);
                                    cout << "CONGRATS, YOU KILLED A DEER. YOU USED 5 BULLETS BUT GAINED " << food_gained << " POUNDS OF FOOD." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-5);
                                    keep_running = false;
                                    successful_hunt = true;
                                }
                                else{
                                    cout << "YOU BULLETS MISSED AND THE DEER GOT AWAY." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-5);
                                    keep_running = false;
                                }
                            }
                        }
                        else{
                            cout << "YOU ENTERED AN INVALID INPUT PLEASE ENTER Y FOR YES OR N NO" << endl;
                        }
                    }
                    keep_running = true; //once i exit the while loop I set this equal to true in case the player encounters another animal
                }
                
                break;
             
            //bear: 7% chance of encountering   
            case 3:
                
                random_number = my_random.Generate(1,100);
                if(random_number < 8){
                    cout << "YOU GOT LUCKY! YOU ENCOUNTERED A " << animals[i] << "! DO YOU WANT TO HUNT?" << endl;
                    cout << "ENTER Y FOR YES AND N FOR NO : " << endl;
                    while(keep_running == true){
                        cin >> decision;
                        if(decision == "N" || decision == "n"){
                            cout << "THERE IS ALWAYS NEXT TIME. GOOD LUCK WITH THE REST OF THE JOURNEY." << endl << endl;
                            keep_running = false;
                        }
                        else if(decision == "Y" || decision == "y"){
                            if(my_store.getBullets() < 12){
                                cout << "YOU DO NOT HAVE ENOUGH BULLETS TO GO HUNTING" << endl << endl;
                                keep_running = false;
                            }
                            else{
                                correct_puzzle = Puzzle();
                                if(correct_puzzle == true){
                                    food_gained += my_random.Generate(100,350);
                                    cout << "CONGRATS, YOU KILLED A BEAR. YOU USED 10 BULLETS BUT GAINED " << food_gained << " POUNDS OF FOOD." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-10);
                                    keep_running = false;
                                    successful_hunt = true;
                                }
                                else{
                                    cout << "YOU BULLETS MISSED AND THE BEAR GOT AWAY." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-10);
                                    keep_running = false;
                                }
                            }
                        }
                        else{
                            cout << "YOU ENTERED AN INVALID INPUT PLEASE ENTER Y FOR YES OR N NO" << endl;
                        }
                    }
                    keep_running = true; //once i exit the while loop I set this equal to true in case the player encounters another animal
                }
                break;
              
            //moose: 5% chance of encountering     
            case 4:
            
                random_number = my_random.Generate(1,100);
                if(random_number < 6){
                    cout << "YOU GOT LUCKY! YOU ENCOUNTERED A " << animals[i] << "! DO YOU WANT TO HUNT?" << endl;
                    cout << "ENTER Y FOR YES AND N FOR NO : " << endl;
                    while(keep_running == true){
                        cin >> decision;
                        if(decision == "N" || decision == "n"){
                            cout << "THERE IS ALWAYS NEXT TIME. GOOD LUCK WITH THE REST OF THE JOURNEY." << endl << endl;
                            keep_running = false;
                        }
                        else if(decision == "Y" || decision == "y"){
                            if(my_store.getBullets() < 12){
                                cout << "YOU DO NOT HAVE ENOUGH BULLETS TO GO HUNTING" << endl << endl;
                                keep_running = false;
                            }
                            else{
                                correct_puzzle = Puzzle();
                                if(correct_puzzle == true){
                                    food_gained += my_random.Generate(300,600);
                                    cout << "CONGRATS, YOU KILLED A MOOSE. YOU USED 12 BULLETS BUT GAINED " << food_gained << " POUNDS OF FOOD." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-12);
                                    keep_running = false;
                                    successful_hunt = true;
                                }
                                else{
                                    cout << "YOU BULLETS MISSED AND THE MOOSE GOT AWAY." << endl << endl;
                                    my_store.setBullets(my_store.getBullets()-12);
                                    keep_running = false;
                                }
                            }
                        }
                        else{
                            cout << "YOU ENTERED AN INVALID INPUT PLEASE ENTER Y FOR YES OR N NO." << endl;
                        }
                    }
                    keep_running = true; //once i exit the while loop I set this equal to true in case the player encounters another animal
                }
                
                break;
                
            default:
                //
                break;
        }
    }
    keep_running = true;
        
    //No animals are encountered 
    if(decision == ""){
        cout << "THE HUNT WAS NOT SUCCESFUL. NO ANIMALS WERE ENCOUNTERED." << endl << endl;
    }
    //the player encounters an animal but decides against hunting it
    else if(decision == "N" || decision == "n"){
            
    }
    //one ore more animals are encountered and the player decides to hunt
    else{
        cout << "HOW WELL DO YOU WANT TO EAT TONIGHT." << endl;
        cout << "ENTER POORLY, MODERATELY, OR WELL." << endl;
        cin >> dinner;
            
        //the player decides how well they want to eat
        while(keep_running == true){
            if(dinner == "POORLY" || dinner == "poorly"){
                food_consumed = 2*number_of_players;
                food_gained -= food_consumed;
                health -= 5;
                cout << endl;
                if(my_store.getFood()+food_gained > 1000){
                    cout << "THE WAGON ONLY COULD ONLY HOLD 1000 LBS OF FOOD. YOU LEFT THE REST BEHIND" << endl;
                    my_store.setFood(1000);
                }
                else{
                    my_store.setFood(my_store.getFood()+food_gained);
                }
                keep_running = false;
                break;
            }
            else if(dinner == "MODERATELY" || dinner == "moderately"){
                food_consumed = 3*number_of_players;
                food_gained -= food_consumed;
                cout << endl;
                if(my_store.getFood()+food_gained > 1000){
                    cout << "THE WAGON ONLY COULD ONLY HOLD 1000 LBS OF FOOD. YOU LEFT THE REST BEHIND" << endl;
                    my_store.setFood(1000);
                }
                else{
                    my_store.setFood(my_store.getFood()+food_gained);
                }
                keep_running = false;
                break;
            }
            else if(dinner == "WELL" || dinner == "well"){
                food_consumed = 5*number_of_players;
                food_gained -= food_consumed;
                health += 5;
                cout << endl;
                if(my_store.getFood()+food_gained > 1000){
                    cout << "THE WAGON ONLY COULD ONLY HOLD 1000 LBS OF FOOD. YOU LEFT THE REST BEHIND" << endl;
                    my_store.setFood(1000);
                }
                else{
                    my_store.setFood(my_store.getFood()+food_gained);
                }
                keep_running = false;
                break;
            }
            else{
                cout << "YOU ENTERED INVALID INPUT. PLEASE ENTER POORLY, MODERATLY, OR WELL" << endl;
                cin >> dinner;
            }
        }
    }
    return successful_hunt;

}



//used when hunting and encountering raiders. the player has 3 tries to guess a number 1-10
bool Game::Puzzle(){
    
    int random_number;
    int number_of_guesses = 0;
    string user_input = "";
    bool correct = false;
    
    cout << "YOU HAVE 3 TRIES TO GUESS THE NUMBER AND SOLVE THE PUZZLE" << endl;
    cout << "ENTER A NUMBER 1-10:" << endl;
    while(number_of_guesses < 3){
        cin >> user_input;
        random_number = my_random.Generate(1,10);
        if(stoi(user_input) == random_number){
            cout << "YOU HAVE GUESSED CORRECTLY AND SOLVED THE PUZZLE" << endl;
            correct = true;
            break;
        }
        else{
            number_of_guesses += 1;
            if(number_of_guesses == 1){
                cout << "YOU ENTERD AN INCORRECT NUMBER. YOU STILL HAVE 2 GUESSES LEFT" << endl;
                cout << "ENTER A NUMBER 1-10:" << endl;
            }
            if(number_of_guesses == 2){
                cout << "YOU ENTERD AN INCORRECT NUMBER. YOU HAVE 1 GUESS LEFT" << endl;
                cout << "ENTER A NUMBER 1-10:" << endl;
            }
            if(number_of_guesses == 3){
                cout << "SORRY THAT WAS NOT RIGHT. YOU DID NOT SOLVE THE PUZZLE" << endl;
                break;
            }
        }
    }
    return correct;
    
}



//this function is called every turn. as the player travels further the chance of encountering a raider decreases 
void Game::raiderAttack(){
    
    int random_number;
    double attack_probability;
    string choice = "";
    bool solved_puzzle;
    
    random_number = my_random.Generate(1,100);
    attack_probability = (((pow(((miles_traveled/100)-4),2)+72)/(pow(((miles_traveled/100)-4),2)+12))-1)/10;
    attack_probability *= 100;
    
    if(random_number < attack_probability){
        cout << "RIDERS AHEAD! THEY LOOK HOSTILE." << endl;
        cout << "YOU CAN EITHER RUN, ATTACK, OR SURRENDER." << endl;
        cout << "PLEASE ENTER RUN, ATTACK, OR SURRENDER." << endl;
        
        //inputs how the player wants to respond to the situation
        while(choice != "RUN" && choice != "run" && choice != "ATTACK" && choice != "attack" && choice != "SURRENDER" && choice != "surrender"){
            cin >> choice;
            if(choice == "RUN" || choice == "run" || choice == "ATTACK" || choice == "attack" || choice == "SURRENDER" || choice == "surrender"){
                break;
            }
            else{
                cout << "INVALID INPUT. PLEASE ENTER RUN, ATTACK, OR SURRENDER." << endl;
            }
        }
        
        if(choice == "RUN" || choice == "run"){
            cout << "YOU BARELY ESCAPED BUT WHILE FLEEING YOU LOST ONE OXEN, 10 LBS OF FOOD, AND ONE WAGON PART." << endl << endl;
            my_store.setOxen(my_store.getOxen()-1);
            my_store.setFood(my_store.getFood()-10);
            my_store.setWagonParts(my_store.getWagonParts()-1);
        }
        else if(choice == "ATTACK" || choice == "attack"){
            cout << "YOU DECIDE TO ATTACK THE RAIDER." << endl;
            solved_puzzle = Puzzle();
            if(solved_puzzle == true){
                cout << "YOU WON THE BATTLE. YOU GAINED 50 LBS OF FOOD AND 50 BULLETS." << endl << endl;
                my_store.setFood(my_store.getFood()+50);
                my_store.setBullets(my_store.getBullets()+50);
            }
            else{
                cout << "THE RAIDERS WON. YOU USED 10 BULLETS AND THE RAIDERS STOLE 1/4 OF YOUR MONEY." << endl << endl;
                my_store.setBullets(my_store.getBullets()-10);
                my_store.setMoney(my_store.getMoney()-(my_store.getMoney()*.25));
                health -= 10;
            }
        }
        else if(choice == "SURRENDER" || choice == "surrender"){
            cout << "YOU GIVE THE RAIDERS 1/4 OF YOUR MONEY AND THEY LET YOU GO." << endl << endl;
            my_store.setMoney(my_store.getMoney()-(my_store.getMoney()*.25));
        }
    }
    
}



//handles when the player runs out of time or supplies
bool Game::playerLoses(){
    
    vector<int> date;
    bool player_loses = false;
    
    date = my_time.getDate();
    if(date[0] >= 12){
        cout << "YOU DID NOT REACH REACH OREGON CITY IN TIME." << endl;
        cout << "THANK YOU FOR PLAYING OREGON TRAIL." << endl;
        player_loses = true;
    }
    else if(my_store.getFood() <= 0){
        cout << "YOU HAVE RAN OUT OF FOOD AND YOU CAN NOT CONTINUE." << endl;
        cout << "THANK YOU FOR PLAYING OREGON TRAIL." << endl;
        player_loses = true;
    }
    else if(my_store.getOxen() <= 0){
        cout << "YOU DO NOT HAVE ANY OXEN AND YOU CAN NOT CONTINUE." << endl;
        cout << "THANK YOU FOR PLAYING OREGON TRAIL." << endl;
        player_loses = true;
    }
    else if(health <= 0){
        cout << "YOUR HEALTH HAS FALLEN TO ZERO AND YOU HAVE DIED." << endl;
        cout << "THANK YOU FOR PLAYING OREGON TRAIL." << endl;
        player_loses = true;
    }
    return player_loses;
    
}



//handles when the player arrives at oregon city
bool Game::playerWon(){
    
    bool player_won = false;
    if(miles_traveled >= 2040){
        cout << "CONGRATS YOU HAVE ARRIVED AT OREGON CITY AND BEAT THE GAME!" << endl;
        cout << "THANK YOU FOR PLAYING OREGON TRAIL." << endl;
        player_won = true;
    }
    
    return player_won;
    
}



/*
prints the results of the player to a file called results.txt
*/
void Game::printResultsToFile(string filename){
    
    ofstream myfilestream;
    string line = "";
    
    vector<int> date = my_time.getDate();
    myfilestream.open(filename);
    if(myfilestream.is_open() == true){
            myfilestream << "---GAME RESULTS---" << endl;
            myfilestream << "MILES TRAVELED: " << miles_traveled << endl;
            myfilestream << "HEALTH: " << health << endl;
            myfilestream << "DATE: " << date[0] << "/" << date[1] << "/" << date[2] << endl;
            myfilestream << "MONEY: $" << my_store.getMoney() << endl;
            myfilestream << "FOOD: " << my_store.getFood() << " LBS" << endl;
            myfilestream << "NUMBER OF OXEN: " << my_store.getOxen() << endl;
            myfilestream << "NUMBER OF BULLETS: " << my_store.getBullets() << endl;
            myfilestream << "NUMBER OF WAGON PARTS: " << my_store.getWagonParts() << endl;
            myfilestream << "NUMBER OF MEDICAL KITS: " << my_store.getMedicalKits() << endl;
    }
    else{
        cout << "FILE DID NOT OPEN" << endl;
    }

}
