//Giles Steiner
#include <iostream>
#include <vector>
using namespace std;
#ifndef Time_H
#define Time_H

class Time{
    
    public:

        Time();

        void setDate(vector<int> start_date);
        
        vector<int> getDate();
        
        void Travel(int days);
    
    private:
        
        int month_and_date[2][9]  = {{3,4,5,6,7,8,9,10,11},{31,30,31,30,31,31,30,31,30}}; //2d array of the months and how many days said month contains
        vector<int> date;

};
#endif 