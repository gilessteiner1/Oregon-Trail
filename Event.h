//Giles Steiner
#include <iostream>
#include <vector>
#include <string>
#include "Random.h"
#include "Store.h"
#include "Time.h"
using namespace std;
#ifndef EVENT_H
#define EVENT_H

class Event{
    
    public:
    
        Event();
        
        int getCompanionIndex(string player_name, vector<string> group_members);
        
        bool randomEvent(Store &my_store, Time &my_time, vector<string> &group_members, string leader_name);
        
        bool getSick(Store &my_store, Time &my_time, vector<string> &group_members, string leader_name);
    
        bool oxenDies(Store &my_store);
        
        bool wagonBreaks(Store &my_store);
        
        bool findMoney(Store &my_store);
        
        bool kindStranger(Store &my_store);
    
    private:
        
        Random my_random; 
        vector<string> diseases;
    
};
#endif
