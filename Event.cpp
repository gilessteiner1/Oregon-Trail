//Giles Steiner
#include <iostream>
#include <vector>
#include "Event.h"
#include "Random.h"
#include "Store.h"
#include "Time.h"
using namespace std;


//default contructor
Event::Event(){
   diseases = {"TYPHOID","CHOLERA","DIARRHEA","MEASLES","DYSETERY","FEVER"};
}


//returns the index of a certain string inside a vector
int stringIndex(string my_string, vector<string> words){
    
    int string_index = -1;
    
    for(int i = 0; i < words.size(); i++){
        if(words.at(i) == my_string){
            string_index = i;
        }
    }
    return string_index;
    
}


/*
chooses a random event to happen to the player 
calls another function in class to execute event 
returns whether the game ends
*/
bool Event::randomEvent(Store &my_store,Time &my_time, vector<string> &group_members, string leader_name){
    
    bool end_game;
    int random_number = my_random.Generate(1,5);
    
    switch(random_number){
        
        //a group member gets sick
        case 1:
            end_game = getSick(my_store,my_time,group_members,leader_name);
            return end_game;
            break;
            
        //an oxen dies
        case 2:
            end_game = oxenDies(my_store);
            return end_game;
            break;
            
        //the wagon breaks
        case 3:
            end_game = wagonBreaks(my_store);
            return end_game;
            break;
        
        //the player finds in between 1-500$
        case 4:
            end_game = findMoney(my_store);
            return end_game;
            break;
        
        //a stranger gives the player in between 1 and 200 lbs of food
        case 5:
            end_game = kindStranger(my_store);
            return end_game;
            break;
        
        //included for correct syntax but will never be called since random_number will always be in between 1 and 6
        default:
            return false;
            break;
    }
    
}


/*
a random group member gets sick with a random disease
if they have a medical kit they use it but still have a 50% chance of dying
if they do not have a medical kit they can rest or press on 
if they rest they still have a 30% chance of dying
if they press on they still have 70% chance of dying 
if the leader dies the function returns true and the game ends
if a group member dies the fucntion returns false and the game continue 
*/
bool Event::getSick(Store &my_store, Time &my_time, vector<string> &group_members, string leader_name){

    bool player_dies;
    bool end_game;
    int random_number;
    int chance_of_dying;
    int days_of_rest;
    int food_consumed;
    int number_of_players;
    int infected_member_index;
    string disease;
    string infected_member_name;
    string decision = "";

    //selects a group member at random to get sick. calls stringIndex() helper function to find index of that member inside group_members vector
    infected_member_name = group_members.at(my_random.Generate(0,group_members.size()-1)); 
    infected_member_index = stringIndex(infected_member_name,group_members);
    
    //selects a disease at random
    disease = diseases.at(my_random.Generate(0,5));
    cout << "OH NO. " << infected_member_name << " HAS " << disease << "." << endl;

    //now I test to see if i have any medical kits and give them different options based on that
    if(my_store.getMedicalKits() > 0){
        my_store.setMedicalKits(my_store.getMedicalKits() - 1);
        if(my_store.getMedicalKits() == 0){
            cout << "YOUR LAST MEDICAL KIT WILL BE USED." << endl;
            chance_of_dying = my_random.Generate(1,10);
            if(chance_of_dying < 6){
                player_dies = true;
            }
            else{
                player_dies = false; 
                cout << "THE MEDICAL KIT WORKED. " << infected_member_name << " WILL LIVE." << endl << endl;
            }
        }
        else{
            cout << "A MEDICAL KIT WILL BE USED.. YOU HAVE " << my_store.getMedicalKits() << " MEDICAL KITS LEFT." << endl;
            chance_of_dying = my_random.Generate(1,10);
            if(chance_of_dying < 6){
                player_dies = true;
            }
            else{
                player_dies = false; 
            }
        }
    }
    else{
        cout << "YOU DO NOT HAVE ANY MEDICAL KITS." << endl;
        cout << "WOULD YOU LIKE TO REST OR PRESS ON?" << endl;
        
        /*
        these next lines are used to input whether the player wants to rest or press on
        since cin only inputs the first word, i compare to press instead of press on
        */
        while(decision != "PRESS" && decision != "press" && decision != "REST" && decision != "rest"){
            cin >> decision;
            if(decision == "PRESS" || decision == "press" || decision == "REST" || decision == "rest"){
                break;
            }
            else{
                cout << "INVALID INPUT. PLEASE ENTER REST OR PRESS ON." << endl;
            }
        }
        
        /*
        if the player chooses press on the sick player has a 70% chance of dying
        the player chooses rest, they must rest for 3 days, but the sick player has a 30% chance of dying
        */
        if(decision == "PRESS" || decision == "press"){
            chance_of_dying = my_random.Generate(1,10);
            if(chance_of_dying < 8){
                player_dies = true;
            }
            else{
                player_dies = false; 
            }
        }
        else if(decision == "REST" || decision == "rest"){
            number_of_players = group_members.size();
            days_of_rest = 3;
            food_consumed = number_of_players*3*days_of_rest;
            my_store.setFood(my_store.getFood()-food_consumed); 
            my_time.Travel(days_of_rest);
            chance_of_dying = my_random.Generate(1,10);
            if(chance_of_dying < 4){
                player_dies = true;
            }
            else{
                player_dies = false; 
            }
        }
    }
    
    if(infected_member_name == leader_name && player_dies == true){
        cout << "YOU HAVE DIED. THE GAME IS OVER." << endl;
        end_game = true;
    }
    else if(infected_member_name != leader_name && player_dies == true){
        cout << infected_member_name << " HAS DIED. YET YOU MUST CONTINUE." << endl << endl;
        group_members.erase(group_members.begin()+infected_member_index);
        end_game = false;
    }
    else if(player_dies == false){
        cout << "A MIRACLE OCCURED. " << infected_member_name << " WILL LIVE." << endl << endl;
        end_game = false;
    }
    else{
        end_game = false;
    }
    return end_game;
    
}



/*
if the last oxen dies the function returns true and the game ends
if the player has more than 1 oxen left the function returns true and the game continue 
*/
bool Event::oxenDies(Store &my_store){
    
    bool end_game;
    
    if(my_store.getOxen()-1 <= 0){
        cout << "YOUR LAST OXEN HAS DIED. YOU ARE UNABLE TO CONTINUE ON YOUR JOURNEY." << endl;
        end_game = true;
    }
    else{
        my_store.setOxen(my_store.getOxen()-1);
        cout << "AN OXEN DIED. YOU HAVE " << my_store.getOxen() << " OXEN LEFT." << endl << endl;
        end_game = false;
    }
    return end_game;
    
}



/*
if the player does not have any wagon parts the function returns true and the game ends
if the player has 1 or more wagon parts they use one wagon part, the function returns false, and the game continue 
*/
bool Event::wagonBreaks(Store &my_store){
    
    bool end_game;
    
    if(my_store.getWagonParts() == 0){
        cout << "THE WAGON IS BROKEN. YOU ARE UNABLE TO CONTINUE ON YOUR JOURNEY." << endl;
        end_game = true;
    }
    else{
        my_store.setWagonParts(my_store.getWagonParts()-1);
        cout << "THE WAGON BROKE BUT YOU HAD A SPARE PART TO FIX IT." << endl;
        if(my_store.getWagonParts() == 0){
            cout << "YOU HAVE NO MORE WAGON PARTS LEFT." << endl << endl;
        }
        else if(my_store.getWagonParts() == 1){
            cout << "YOU HAVE " << my_store.getWagonParts() << " WAGON PART LEFT." << endl << endl;
        }
        else{
            cout << "YOU HAVE " << my_store.getWagonParts() << " WAGON PARTS LEFT." << endl << endl;
        }
        end_game = false;
    }
    return end_game;
    
}



/*
the player finds a treasure chest containing 1-500$
the player can choose to open it or to continue on their journey
the function always returns false and the game continues
*/
bool Event::findMoney(Store &my_store){
    
    bool end_game = false;
    string decision = "";
    int money_found;
    
    money_found = my_random.Generate(1,500);
    cout << "IT IS YOUR LUCKY DAY. ALONG THE TRAIL YOU FOUND A TREASURE CHEST." << endl;
    cout << "ENTER WOULD YOU LIKE TO OPEN THE CHEST OR CONTINUE ON YOUR JOURNEY? ENTER OPEN OR CONTINUE." << endl;
   
   //keeps asking the user what they would like to do until they enter stop or continue. inputs answer and stores as a string named decision
    while(decision != "OPEN" && decision != "open" && decision != "CONTINUE" && decision != "continue"){
        cin >> decision;
        if(decision == "OPEN" || decision == "open" || decision == "CONTINUE" || decision == "continue"){
            break;
        }
        else{
            cout << "INVALID INPUT. PLEASE ENTER OPEN OR CONTINUE." << endl;
        }
    }
   
   if(decision == "OPEN" || decision == "open"){
        cout << "YOU OPEN THE CHEST AND FIND OUT THAT IT HAS MONEY IN IT!" << endl;
        cout << "THE TREASURE CHEST CONTAINED $" << money_found << endl << endl;
        my_store.setMoney(my_store.getMoney()+money_found);
    }
    else if(decision == "CONTINUE" || decision == "continue"){
        cout << "YOU DECIDE AGAINST OPENING THE CHEST AND CONTINUE ON YOUR JOURNEY." << endl << endl;
    }
    return end_game;
    
}



/*
the player is approached by a stranger 
the player can choose to stop or ignore the stranger and continue 
if the player stops the stranger gives the player in between 1-200 lbs of food 
if the player continues nothing happens 
the function always returns false and the game continues
*/
bool Event::kindStranger(Store &my_store){
    
    bool end_game = false;
    string decision = "";
    int food_donated;
    
    food_donated = my_random.Generate(1,200);
    cout << "WHILE TRAVELING A STRANGER RUNS IN FRONT OF YOU AND ASKS YOU TO STOP." << endl;
    cout << "WOULD YOU LIKE TO STOP OR CONTINUE ON YOUR JOURNEY? ENTER STOP OR CONTINUE." << endl;
    
    //keeps asking the user what they would like to do until they enter stop or continue. inputs answer and stores as a string named decision
    while(decision != "STOP" && decision != "stop" && decision != "CONTINUE" && decision != "continue"){
        cin >> decision;
        if(decision == "STOP" || decision == "stop" || decision == "CONTINUE" || decision == "continue"){
            break;
        }
        else{
            cout << "INVALID INPUT. PLEASE ENTER STOP OR CONTINUE." << endl;
        }
    }
    
    if(decision == "STOP" || decision == "stop"){
        cout << "YOU PULL OVER AND GET A CLOSER LOOK AT THE STRANGER. HE EXPLAINS THAT HE IS ABOUT TO GO TO JAIL AND WANTS YOU TO HAVE THE REST OF HIS FOOD." << endl;
        cout << "YOU THANK HIM AS HE PUTS " << food_donated << " LBS OF FOOD IN YOUR WAGON." << endl << endl;
        my_store.setFood(my_store.getFood()+food_donated);
    }
    else if(decision == "CONTINUE" || decision == "continue"){
        cout << "YOU SPEED PAST THE STRANGER AND CONTINUE WITHOUT STOPPING." << endl << endl;
    }
    return end_game;
    
}
