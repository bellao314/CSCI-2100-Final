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
  }
  gps.close(); // Discontinue using the file, it is now in our array.
  watch.close(); // Ditto

  return;
}


double speed::findGPSAcc(){
  gpsAcc = (gpsSpeed[99] - gpsSpeed[0])/100;

  return gpsAcc;
}


double speed::findWatchAcc(){
  watchAcc = (watchSpeed[99] - watchSpeed[0])/100;

  return watchAcc;
}


double speed::actualSpeed(){
  avgAcc = (findGPSAcc() + findWatchAcc())/2;
  actualSpeedArr[0] = 0;
  for(int i=1; i<100; i++){
    actualSpeedArr[i] = avgAcc * i;
    // cout<<"The estimated actual speed at time "<<i<<" is "<<actualSpeedArr[i]<<"."<<endl;
  }
  return avgAcc;
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
    if(gpsSpeed[i] <= i + 0.5 && gpsSpeed[i] >= i - 0.5){
      cout<<"The speed at time "<<i<<" seconds is "<<gpsSpeed[i]<<"."<<endl;
    }else{
      cout<<"The data "<<gpsSpeed[i]<<" at the time "<<i<<" seconds is wrong."<<endl;
    }

    if(watchSpeed[i] <= i + 0.5 && watchSpeed[i] >= i - 0.5){
      cout<<"The speed at time "<<i<<" seconds is "<<watchSpeed[i]<<"."<<endl;
    }else{
      cout<<"The data "<<watchSpeed[i]<<" at the time "<<i<<" seconds is wrong."<<endl;
    }

    cout<<endl;
  }

  return;
}