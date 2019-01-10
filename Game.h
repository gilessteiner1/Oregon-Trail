//Giles Steiner
#include <iostream>
#include <vector>
#include "Store.h"
#include "Event.h"
#include "Time.h"
#include "Random.h"
using namespace std;
#ifndef GAME_H
#define GAME_H

class Game{
    
    public:
    
        Game();
        
        Game(string name, vector<string> companion_names, vector<int> start_date);
        
        int findDelimiterPosition(string my_string);
        
        int getMilestoneIndex(string filename, int milestone_distance);
        
        string getMilestoneName(string filename, int milestone_distance);
        
        int distanceUntilNextMilestone(string filename);
        
        string nextMilestoneName(string filename);
        
        void Shop(int visits);
        
        bool randomEvent();
        
        void statusUpdate();
        
        void Milestone(string filename, int milestone_index);
   
        void Rest();
        
        void Continue();
        
        bool Hunt();
        
        bool Puzzle(); 
        
        void raiderAttack();
        
        bool playerLoses();
        
        bool playerWon();
        
        void printResultsToFile(string filename);

    private:
    
        string leader_name;
        int miles_traveled;
        int number_of_players; 
        int number_of_store_visits;
        int health;
        vector<string> group_members;
        vector<int> date; 
        Store my_store;
        Event my_event;
        Time my_time;
        Random my_random;

};
#endif 