#include <iostream>
#include "speed.hpp"
#include "speed.cpp"
using namespace std;


int main(){
  speed trip;
  int speedInput, timeInput, choice;

  cout << "Would you like to search for a certain speed (1), search by a specific time (2), or display all data (3)? Input 1, 2, or 3. Any other number to exit. ";
  cin >> choice;

  while(choice == 1 || choice == 2 || choice == 3){ // If the previous answer was a menu option, continue looping.
    if(choice == 1){ // Search for specific speed
      cout << "What speed would you like to find? Input a whole number. ";
      cin >> speedInput;

      trip.searchByGPSSpeed(speedInput);
      trip.searchByWatchSpeed(speedInput);
    }else if(choice == 2){ // Search for specific time
      cout << "What time would you like to search for? Input a whole number. ";
      cin >> timeInput;

      trip.searchByTime(timeInput);
    } else if(choice == 3) { // Display all data
      trip.display();
    }
    cout << endl;

    cout << "Would you like to search for a certain speed (1), search by a specific time (2), or display all data (3)? Input 1, 2, or 3. Any other number to exit. ";
    cin >> choice;
  }

  return 0;
}