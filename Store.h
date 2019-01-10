//Giles Steiner
#include <iostream>
using namespace std;
#ifndef STORE_H
#define STORE_H

class Store{
    
    public:
        
        Store();
        
        void displayFirstStore();
        
        void firstStore(int visits);
        
        int getFood();
        
        int getBullets();
        
        int getMoney();
        
        int getOxen();
        
        int getWagonParts();
        
        int getMedicalKits();
        
        void setMoney(int new_amount);
        
        void setOxen(int new_amount);
        
        void setFood(int new_amount);
        
        void setBullets(int new_amount);
        
        void setWagonParts(int new_amount);
    
        void setMedicalKits(int new_amount);
        
    //holds all of our supplies
    private: 
    
        int amount_of_money;
        int amount_of_food;
        int number_of_oxen;
        int number_of_bullets;
        int number_of_wagon_parts;
        int number_of_medical_kits;
        
};
#endif 