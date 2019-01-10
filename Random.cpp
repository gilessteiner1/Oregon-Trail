//Giles Steiner
#include <iostream>
#include "Random.h"
using namespace std;


Random::Random(){
    srand(time(0)); //seeds the random numbers
}


int Random::Generate(int min, int max){
   
   return (rand() % (max-min+1)) + min;
    
}