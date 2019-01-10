//Giles Steiner
#include <iostream>
#include "Game.h"
#include "Store.h"
#include "Time.h"
#include "Random.h"
#include <string>
#include <vector>
using namespace std;


//modified split to work with vectors for the group members
vector<string> stringSplit(string my_string, char delimiter){
    
    int i = 0;
    vector<string> words; 
    string word = "";
    
    while(i < my_string.length()){
        if(my_string[i] == delimiter){
            words.push_back(word);
            word = "";
        }
        else{
            word += my_string[i];
        }
        i += 1;
    }
    if(word != ""){
        words.push_back(word);
    }
    return words; 
    
}


//modified split to work with vectors for the date
vector<int> intSplit(string my_string, char delimiter){
    
    int i = 0;
    vector<int> numbers;
    string word = "";
    
    while(i < my_string.length()){
        if(my_string[i] == delimiter){
            numbers.push_back(stoi(word));
            word = "";
        }
        else{
            word += my_string[i];
        }
        i += 1;
    }
    
    if(word != ""){
        numbers.push_back(stoi(word));
    }
    return numbers; 
    
}


//converts a string to all uppercase
string toUppercase(string my_string){
    
    for(int i = 0; i < my_string.length(); i++){
        my_string[i] = toupper(my_string[i]);
    }
    return my_string;
    
}


//displays the main menu 
void displayMenu(){
    
    cout << "======MAIN MENU=====" << endl;
    cout << "1. REST" << endl;
    cout << "2. CONTINUE ON TRAIL" << endl;
    cout << "3. HUNT" << endl;
    cout << "4. QUIT" << endl;
    
}


/*
main driver functiom
inputs the desired start date and fellow group members
contains the game loop
*/
int main(){
    
    string leader_name = "";
    string companion = "";
    bool end_game = false;
    string start_date = ""; 
    vector<string> vector_of_companions;
    vector<int> date = {3,28,1847}; //default start date - 3/28/1847

    cout << "PLEASE ENTER YOUR NAME: ";
    cin >> leader_name;
    leader_name = toUppercase(leader_name);
    
    //creates a vector of companions 
    cout << "WELCOME TO OREGON TRAIL, " << leader_name << endl;
    cout << "PLEASE ENTER THE NAME OF THREE OTHER TRAVELING COMPANIONS." << endl;
    cout << "COMPANION ONE: ";
    cin >> companion;
    companion = toUppercase(companion);
    vector_of_companions.push_back(companion);
    cout << "COMPANION TWO: ";
    cin >> companion;
    companion = toUppercase(companion);
    vector_of_companions.push_back(companion);
    cout << "COMPANION THREE: ";
    cin >> companion;
    companion = toUppercase(companion);
    vector_of_companions.push_back(companion);
    
    cout << "THE DEFAULT START DATE IS 3/28/1847. ENTER Y TO START ON THE DEFAULT START DATA OR ENTER IN A DATE IN BETWEEN 3/01/1847 AND 5/01/1847" << endl;
    cout << "THE FORMAT OF THE DATE NEEDS TO BE XX/XX/XXXX" << endl;
    cin >> start_date;
    
    //only runs if the user does not want to start on 3/28/1847
    while(start_date != "Y" && start_date != "y"){ 
        vector<int> temp_date = intSplit(start_date,'/');
        if(temp_date[0] < 3 || temp_date[0] > 5){
            cout << "YOU ENTERED AN INCORRECT MONTH. PLEASE TRY AGAIN" << endl;
        }
        else if(temp_date[1] < 1 || temp_date[1] > 31 || (temp_date[0] == 5 && temp_date[1]>1)){
            cout << "YOU ENTERED AN INCORRECT DATE. PLEASE TRY AGAIN" << endl;
        }
        else if(temp_date[2] != 1847){
            cout << "YOU ENTERED AN INCORRECT YEAR. PLEASE TRY AGAIN" << endl;
        }
        else{
            date.swap(temp_date);
            break;
        }
        cin >> start_date; 
    }
    
    Game my_game(leader_name,vector_of_companions,date);
    my_game.Shop(0);
    string choice1 = "";

    while(choice1 != "4" && end_game == false){
        displayMenu();
        cin >> choice1;
        if(choice1[0] < '0' || choice1[0] > '5'){
            cout << "INVALID INPUT. PLEASE ENTER A NUMBER 1-4" << endl << endl; //handles if the user doesn't enter a number. avoids stoi error 
        }
        else{
            switch(stoi(choice1)){
      
                //rest 
                case 1: 
                    cout << endl;
                    my_game.Rest();
                    
                    if(my_game.randomEvent() == true || my_game.playerWon() == true || my_game.playerLoses() == true){
                        my_game.printResultsToFile("results.txt");
                        end_game = true;
                    }
                    else{
                        my_game.statusUpdate();
                    }
                    break;
            
                //continue on Trail    
                case 2:
                    cout << endl;
                    my_game.Continue();
                
                    if(my_game.randomEvent() == true || my_game.playerWon() == true || my_game.playerLoses() == true){
                        my_game.printResultsToFile("results.txt");
                        end_game = true;  
                    }
                    else{
                        my_game.statusUpdate();
                    }
                    break;
            
                //hunt    
                case 3:
                    cout << endl;
                    my_game.Hunt();
            
                    if(my_game.randomEvent() == true || my_game.playerWon() == true || my_game.playerLoses() == true){
                        my_game.printResultsToFile("results.txt");
                        end_game = true;
                    }   
                    else{
                        my_game.statusUpdate();
                    }
                    break;
            
                //quit     
                case 4:
                    cout << endl;
                    cout << "THANK YOU FOR PLAYING OREGON TRAIL." << endl;
                    my_game.printResultsToFile("results.txt");
                    break;
                 
                default:
                    cout << "INVALID INPUT. PLEASE ENTER A NUMBER 1-4" << endl;
                    break;
            }
        }
    }
    
}