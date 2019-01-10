//Giles Steiner
#include <iostream>
#include "Store.h"
#include "Game.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;


//resets variables which keep track of the players inventory
Store::Store(){
  
        amount_of_money = 1000; 
        amount_of_food = 0;
        number_of_oxen = 0; 
        number_of_bullets = 0;
        number_of_wagon_parts = 0;
        number_of_medical_kits = 0;

}


//displays the menu of the store
void Store::displayFirstStore(){
    
    cout << "======General Store=====" << endl;
    cout << "1. BUY OXEN" << endl;
    cout << "2. BUY FOOD" << endl;
    cout << "3. BUY BULLETS" << endl;
    cout << "4. BUY MISCELLANEOUS SUPPLIES" << endl;
    cout << "5. CHECKOUT" << endl;
    
}


/*
this function allows the player to visit a virtual store where they can pruchase oxen, food, bullets, wagon parts, and medical kits 
the input of the function 'visits' is the number of times the player has visited the store (first visit is 0) 
since the prices of the store are 25% more expensive with every visit the price multiplier is based of off the visits input parameter
*/
void Store::firstStore(int visits){

        //These three arrays help me keep track about what has been purchased
        string item_names[5] = {"OXEN YOKE", "POUNDS OF FOOD", "BOXES OF BULLETS", "WAGON PARTS", "MEDICAL KITS"};
        double bill_items[5] = {0,0,0,0,0};
        double bill_prices[5] = {0,0,0,0,0};
        
        double current_bill = 0;
        double price_multiplier = 1 + .25*visits;
        string choice1 = "";
        string choice2 = ""; 
        string choice3 = "";
        ifstream myfilestream;
       
        cout << "YOU HAVE $" << amount_of_money << " TO SPEND ON THE FOLLOWING ITEMS" << endl;
        cout << "1 ~ OXEN. YOU CAN SPEND $100-$200 ON YOUR TEAM. THE MORE YOU SPEND, THE FASTER YOU'LL GO BECAUSE YOU'LL HAVE BETTER ANIMALS" << endl;
        cout << "2 ~ FOOD. THE MORE YOU HAVE, THE LESS CHANCE THERE IS OF GETTING SICK " << endl;
        cout << "3 ~ AMMUNITION - YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS AND BANDITS, AND FOR HUNTING FOOD" << endl;
        cout << "4 ~ MISCELLANEOUS SUPPLIES. THIS INCLUDES MEDICINE AND OTHER THINGS YOU WILL NEED FOR SICKNESS AND EMERGENCY REPAIRS" << endl;
        cout << "YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP, OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET MORE FOOD." << endl << endl;
       
        while(choice1 != "5"){
            displayFirstStore();
            cin >> choice1;
            if(choice1[0] < '0' || choice1[0] > '6'){
                cout << "INVALID INPUT. PLEASE ENTER A NUMBER 1-5" << endl << endl; //handles if the user doesn't enter a number. avoids stoi error 
            }
            else{
                switch(stoi(choice1)){
                    
                    //the player purchases oxen yoke
                    case 1:
                        
                        //prints some ascii art of an oxen
                        cout << endl;
                        myfilestream.open("ACII ART/oxen_ascii.txt");
                        if(myfilestream.is_open() == true){
                            string line = "";
                            while(getline(myfilestream,line)){
                                if(line != ""){
                                    cout << line << endl;
                                }
                            }
                        }
                        myfilestream.close();
                        cout << endl;
                    
                        cout << "YOU MAY SPEND BETWEEN $100 AND $200 DOLLARS ON OXEN. THERE ARE 2 OXEN IN A YOKE AND THE PRICE OF EACH YOKE IS $" << 40*price_multiplier << "." << endl;
                        cout << "PLEASE ENTER HOW MANY YOKE YOU WISH TO PURCHASE: " << endl;
                        cin >> choice2;
                        if(bill_prices[0] + 40*price_multiplier*stod(choice2) < 100){
                            cout << "YOU MUST SPEND MORE THAN $100, PLEASE TRY AGAIN WITH A DIFFERENT AMOUNT." << endl << endl;
                        }
                        else if(bill_prices[0] + 40*price_multiplier*stod(choice2) > 200){
                            cout << "YOU MUST SPEND LESS THAN $200, PLEASE TRY AGAIN WITH A DIFFERENT AMOUNT." << endl << endl;
                        }
                        else if(bill_items[0] + stod(choice2) > 5){
                            cout << "YOU CANNOT PURCHASE MORE THAN 5 OXEN YOKE." << endl << endl;
                        }
                        else{
                            if(40*price_multiplier*stod(choice2) > amount_of_money){
                                cout << "YOU DO NOT HAVE ENOUGH MONEY TO MAKE THAT PURCHASE." << endl;
                            }
                            else{
                                bill_items[0] += stod(choice2);
                                bill_prices[0] += stod(choice2)*40*price_multiplier;
                                current_bill += stod(choice2)*40*price_multiplier;
                                amount_of_money -= stod(choice2)*40*price_multiplier;
                                number_of_oxen += stod(choice2)*2;
                               
                                //this prints out the current bill after the purchase is made 
                                cout << "======CURRENT BILL=====" << endl;
                                for(int i = 0; i < 5; i++){
                                    if(bill_items[i] > 0){
                                        cout << item_names[i] << ": " << bill_items[i] << " || " << "PRICE: " << bill_prices[i] << endl;
                                    }
                                }
                                cout << "FINAL COST: $" << current_bill << endl;
                                cout << "MONEY LEFT: $" << amount_of_money << endl;
                                cout << endl;
                            }
                        }
                        break;
                    
                    //the player purhcases food 
                    case 2:
                        
                        //prints some ascii art of food
                        cout << endl;
                        myfilestream.open("ACII ART/food_ascii.txt");
                        if(myfilestream.is_open() == true){
                            string line = "";
                            while(getline(myfilestream,line)){
                                if(line != ""){
                                    cout << line << endl;
                                }
                            }
                        }
                        myfilestream.close();
                        cout << endl;
                    
                    
                        cout << "THE STORE OWNER RECCOMENDS BUYING AT LEAST 200 POUNDS OF FOOD PER PERSON. FOOD COSTS $" << .5*price_multiplier << " A POUND." << endl;
                        cout << "PLEASE ENTER HOW MANY FOUND OF FOOD YOU WOULD LIKE TO PURCHASE: " << endl;
                        cin >> choice2;
                        if(.5*price_multiplier*stod(choice2) > amount_of_money){
                            cout << "YOU DO NOT HAVE ENOUGH MONEY TO MAKE THAT PURCHASE." << endl << endl;
                        }
                        else if(bill_items[1] + stod(choice2) > 1000){
                            cout << "THE WAGON CAN ONLY HOLD 1000 LBS OF FOOD." << endl << endl;
                        }
                        else{
                            bill_items[1] += stod(choice2);
                            bill_prices[1] += stod(choice2)*.5*price_multiplier;
                            current_bill += stod(choice2)*.5*price_multiplier;
                            amount_of_money -= stod(choice2)*.5*price_multiplier;
                            amount_of_food += stod(choice2);
                            
                            //this prints out the current bill after the purchase is made 
                                cout << "======CURRENT BILL=====" << endl;
                                for(int i = 0; i < 5; i++){
                                    if(bill_items[i] > 0){
                                        cout << item_names[i] << ": " << bill_items[i] << " || " << "PRICE: " << bill_prices[i] << endl;
                                    }
                                }
                                cout << "FINAL COST: $" << current_bill << endl;
                                cout << "MONEY LEFT: $" << amount_of_money << endl;
                                cout << endl;
                        }
                        break;
                    
                    //the player purchases bullets
                    case 3:
                    
                        //prints some ascii art of bullets
                        cout << endl;
                        myfilestream.open("ACII ART/bullets_ascii.txt");
                        if(myfilestream.is_open() == true){
                            string line = "";
                            while(getline(myfilestream,line)){
                                if(line != ""){
                                    cout << line << endl;
                                }
                            }
                        }
                        myfilestream.close();
                        cout << endl;
                 
                        cout << "A BOX OF 20 BULLETS COSTS $" << 2*price_multiplier << "." << endl; 
                        cout << "PLEASE ENTER HOW MANY BOXES OF BULLETS YOU WISH TO PURCHASE." << endl;
                        cin >> choice2;
                        if(2*price_multiplier*stod(choice2) > amount_of_money){
                            cout << "YOU DO NOT HAVE ENOUGH MONEY TO MAKE THAT PURCHASE." << endl << endl;
                        }
                        else{
                        bill_items[2] += stod(choice2);
                        bill_prices[2] += stod(choice2)*2*price_multiplier;
                        current_bill += stod(choice2)*2*price_multiplier;
                        amount_of_money -= stod(choice2)*2*price_multiplier;
                        number_of_bullets += stod(choice2)*20;
                        
                        //this prints out the current bill after the purchase is made 
                            cout << "======CURRENT BILL=====" << endl;
                            for(int i = 0; i < 5; i++){
                                if(bill_items[i] > 0){
                                    cout << item_names[i] << ": " << bill_items[i] << " || " << "PRICE: " << bill_prices[i] << endl;
                                }
                            }
                            cout << "FINAL COST: $" << current_bill << endl;
                            cout << "MONEY LEFT: $" << amount_of_money << endl;
                            cout << endl;
                        }
                        break;
                       
                    //the player purchases medical kits and/or wagon parts  
                    case 4:
                    
                        //prints some ascii art of an oxen
                        cout << endl;
                        myfilestream.open("ACII ART/miscellaneous_ascii.txt");
                        if(myfilestream.is_open() == true){
                            string line = "";
                            while(getline(myfilestream,line)){
                                if(line != ""){
                                    cout << line << endl;
                                }
                            }
                        }
                        myfilestream.close();
                        cout << endl;
                    
                        cout << "WAGON PARTS AND MEDICAL KITS CAN COME IN HANDY LATER IN THE GAME." << endl;
                        cout << "WAGON PARTS COST $" << 20*price_multiplier<< " A POP. HOW MANY WAGON PARTS DO YOU WISH TO PURCHASE: " << endl;
                        cin >> choice2;
                       
                        //i check if the player has money for the wagon parts and medical kits seperatly and exit the program if they do not 
                        if(20*price_multiplier*stod(choice2) > amount_of_money){
                            cout << "YOU DO NOT HAVE ENOUGH MONEY TO MAKE THAT PURCHASE." << endl << endl;
                            break;
                        } 
                        cout << "MEDICAL KITS COST $" << 25*price_multiplier << " A POP. HOW MANY MEDICAL KITS DO YOU WISH TO PURCHASE:" << endl;
                        cin >> choice3;
                        if(25*price_multiplier*stod(choice3) > amount_of_money){
                            cout << "YOU DO NOT HAVE ENOUGH MONEY TO MAKE THAT PURCHASE." << endl << endl;
                            break;
                        }
                        else if(25*price_multiplier*stod(choice3) + 20*price_multiplier*stod(choice2) > amount_of_money){
                            cout << "YOU DO NOT HAVE ENOUGH MONEY TO MAKE THAT PURCHASE." << endl << endl;
                            break;
                        }
                        else{
                            bill_items[3] += stod(choice2);
                            bill_items[4] += stod(choice3);
                            bill_prices[3] += stod(choice2)*20*price_multiplier;
                            bill_prices[4] += stod(choice3)*25*price_multiplier;
                            amount_of_money -= (stod(choice2)*20*price_multiplier + stod(choice3)*25*price_multiplier);
                            current_bill += (stod(choice2)*20*price_multiplier + stod(choice3)*25*price_multiplier);
                            number_of_wagon_parts += stod(choice2);
                            number_of_medical_kits += stod(choice3);
                        
                            //this prints out the current bill after the purchase is made 
                            cout << "======CURRENT BILL=====" << endl;
                            for(int i = 0; i < 5; i++){
                                if(bill_items[i] > 0){
                                    cout << item_names[i] << ": " << bill_items[i] << " || " << "PRICE: " << bill_prices[i] << endl;
                                }
                            }
                            cout << "FINAL COST: $" << current_bill << endl;
                            cout << "MONEY LEFT: $" << amount_of_money << endl;
                            cout << endl;
                        }
                        break;
                      
                    //checkout. the final bill is printed
                    case 5:
                        cout << "======FINAL BILL=====" << endl;
                            for(int i = 0; i < 5; i++){
                                if(bill_items[i] > 0){
                                    cout << item_names[i] << ": " << bill_items[i] << " || " << "PRICE: " << bill_prices[i] << endl;
                                }
                            }
                            cout << "FINAL COST: $" << current_bill << endl;
                            cout << "MONEY LEFT: $" << amount_of_money << endl;
                            cout << endl;
                        cout << "THANKS FOR SHOPPING WITH US. GOOD LUCK WITH YOUR JOURNEY!" << endl << endl;
                        break;
                   
                    default:
                        cout << "INVALID INPUT. PLEASE ENTER A NUMBER 1-5" << endl << endl;
                }
            }
        }
        
}


//this allows other classes (mainly game class) to have access to the amount of money the player has
int Store::getMoney(){
    return amount_of_money;
}


//this allows other classes (mainly game class) to have access to the amount of food the player has
int Store::getFood(){
    return amount_of_food;
}


//this allows other classes (mainly game class) to have access to the number of oxen the player has
int Store::getOxen(){
    return number_of_oxen;
}


//this allows other classes (mainly game class) to have access to the number of bullets the player has
int Store::getBullets(){
    return number_of_bullets;
}


//this allows other classes (mainly game class) to have access to the amount of wagon parts the player has
int Store::getWagonParts(){
    return number_of_wagon_parts;
}


//this allows other classes (mainly game class) to have access to the amount of medical kits the player has
int Store::getMedicalKits(){
    return number_of_medical_kits;
}


//this allows other classes (mainly game class) to modify the amount of money the player has 
void Store::setMoney(int new_amount){
    
    if(new_amount > 0){
        amount_of_money = new_amount;
    }
    else{
        amount_of_money = 0;
    }
    
}


//this allows other classes (mainly game class) to modify the amount of food the player has 
void Store::setFood(int new_amount){
    
    if(new_amount < 1000){
        amount_of_food = new_amount;
    }
    else{
        amount_of_food = 1000;
    }

}


//this allows other classes (mainly game class) to modify the number of oxen the player has 
void Store::setOxen(int new_amount){
    
    if(new_amount > 0){
        number_of_oxen = new_amount;
    }
    else{
        number_of_oxen = 0;
    }
    
}


//this allows other classes (mainly game class) to modify the number of bullets the player has 
void Store::setBullets(int new_amount){
    
    if(new_amount > 0){
        number_of_bullets = new_amount;
    }
    else{
        number_of_bullets = 0;
    }
    
}


//this allows other classes (mainly game class) to modify the number of wagon parts the player has 
void Store::setWagonParts(int new_amount){
    
    if(new_amount > 0){
        number_of_wagon_parts = new_amount;
    }
    else{
        number_of_wagon_parts = 0;
    }
    
}


//this allows other classes (mainly game class) to modify the number of medical kits the player has 
void Store::setMedicalKits(int new_amount){
    
    if(new_amount > 0){
        number_of_medical_kits = new_amount;
    }
    else{
        number_of_medical_kits = 0;
    }
    
}











