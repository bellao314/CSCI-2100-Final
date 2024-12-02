#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "speed.hpp"
using namespace std;


speed::speed(){
  gpsSpeed[0] = 0;
  watchSpeed[0] = 0;
  openFiles();
  actualSpeed();
  display();
}


speed::~speed(){
  cout<<"Destructor called"<<endl;
}


void speed::openFiles(){
  ifstream gps("RTK_GPS.txt");
  ifstream watch("SmartWatch.txt");

  if (!gps || !watch) { // If either file does not open successfully.
      cerr << "Error opening file(s)." << endl;
      return;
  }

  for(int i = 1; i < 100; i++) { // Copy data into array memory.
      gps >> gpsSpeed[i];
      watch >> watchSpeed[i];

      if(gpsSpeed[i] >= i + 0.5 && gpsSpeed[i] <= i - 0.5){
          gpsSpeed[i] = actualSpeedArr[i];
          cout<<"Caught error."<<endl;
      }

      if(watchSpeed[i] >= i + 0.5 && watchSpeed[i] <= i - 0.5){
          watchSpeed[i] = actualSpeedArr[i];
          cout<<"Caught error."<<endl;
      }
  }
  gps.close(); // Discontinue using the file, it is now in our array.
  watch.close(); // Ditto

  return;
}


double speed::findAcc(){
  gpsAcc = (gpsSpeed[99] - gpsSpeed[0])/100;
  watchAcc = (watchSpeed[99] - watchSpeed[0])/100;
  avgAcc = (gpsAcc + watchAcc)/2;

  return avgAcc;
}


void speed::actualSpeed(){
  actualSpeedArr[0] = 0;
  for(int i=1; i<100; i++){
    actualSpeedArr[i] = findAcc() * i;
  }

  return;
}


void speed::searchByTime(int time){
  cout<<"GPS Speed: "<<gpsSpeed[time]<<endl;
  cout<<"Watch Speed: "<<watchSpeed[time]<<endl;
  cout<<"Estimated Actual Speed: "<<actualSpeedArr[time]<<endl;
  cout<<endl;
  
  return;
}


void speed::searchByGPSSpeed(int speed){
  for(int i=0; i<100; i++){
    int currentGPSSpeed = floor(gpsSpeed[i]);
    if(currentGPSSpeed == speed){
      cout<<"Found it! The corresponding index is "<<i<<" for a recorded GPS speed of "<<gpsSpeed[i]<<"."<<endl;
      cout<<endl;
      return;
    }
  }

  cout<<"Cannot find the data."<<endl;
  cout<<endl;
  return;
}


void speed::searchByWatchSpeed(int speed){
  for(int i=0; i<100; i++){
    int currentWatchSpeed = floor(watchSpeed[i]);
    if(currentWatchSpeed == speed){
      cout<<"Found it! The corresponding index is "<<i<<" for a recorded watch speed of "<<watchSpeed[i]<<"."<<endl;
      cout<<endl;
      return;
    }
  }
  
  cout<<"Cannot find the data."<<endl;
  cout<<endl;
  return;
}


void speed::display(){
  for(int i=1; i<100; i++){
    if(gpsSpeed[i] > i + 0.5 || gpsSpeed[i] < i - 0.5){
      cout<<"The GPS data "<<gpsSpeed[i]<<" at the time "<<i<<" seconds is wrong."<<endl;
      gpsSpeed[i] = actualSpeedArr[i];
    }
    
    if(watchSpeed[i] > i + 0.5 || watchSpeed[i] < i - 0.5){
      cout<<"The watch data "<<watchSpeed[i]<<" at the time "<<i<<" seconds is wrong."<<endl;
      watchSpeed[i] = actualSpeedArr[i];
    }
  }

  cout<<endl;

  for(int i=1; i<100; i++){
    cout<<"The estimated actual data at time "<<i<<" seconds is "<<actualSpeedArr[i]<<"."<<endl;
  }

  cout<<endl;

  return;
}