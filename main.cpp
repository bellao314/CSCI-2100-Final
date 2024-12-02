#include <iostream>
#include "speed.hpp"
#include "speed.cpp"
using namespace std;


int main(){
  speed trip;
  int speedInput, timeInput, choice;

  cout<<"Would you (1) like to search for a certain speed, or (2) search by a specific time? Input 1 or 2 or other number to exit. ";
  cin>>choice;

  while(choice == 1 || choice == 2){
    if(choice == 1){
      cout<<"What speed would you like to find? Input a whole number. ";
      cin>>speedInput;
      trip.searchByGPSSpeed(speedInput);
      trip.searchByWatchSpeed(speedInput);
    }else if(choice == 2){
      cout<<"What time would you like to search for? Input a whole number. ";
      cin>>timeInput;
      trip.searchByTime(timeInput);
    }

    cout<<"Would you (1) like to search for a certain speed, or (2) search by a specific time? Input 1 or 2 or other number to exit. ";
    cin>>choice;
  }

  return 0;
}