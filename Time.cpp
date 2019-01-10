//Giles Steiner
#include <iostream>
#include <vector>
#include "Time.h"
using namespace std;


/*
default constructor 
resets the date vector 
*/
Time::Time(){
    
    date = {0,0,0};
    
}


//sets the date in vector form <month,date,year>
void Time::setDate(vector<int> start_date){ 
    
    date.swap(start_date);
    
}


//returns the date in vector form <month,date,year>
vector<int> Time::getDate(){
    
    return date;
    
}


/*
hands down the best code I have ever written. this is the peak...
time travels for however many days are inputted using information in the month_and_date 2d array to know when to go to the next month
*/
void Time::Travel(int days){
  
    bool new_month = false;
    vector<int> new_date;
    
    for(int i = 0; i < 9; i++){
        //if the current date + the number of days you want to travel is greater than the number of days in the month you are in you travel until the end of the month, then increase the month by 1 and let the date equal the remaining days left 
        if((date[0] == month_and_date[0][i]) && (date[1]+days > month_and_date[1][i])){
            new_date = {date[0]+1,days-(month_and_date[1][i]-(date[1])),1847};
            date.swap(new_date);
            new_month = true;
        }
    }
    if(new_month == false){
        new_date = {date[0],date[1]+days,date[2]};
        date.swap(new_date);
    }
 
}