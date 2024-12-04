#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "speed.hpp"
using namespace std;


speed::speed(){
  gpsSpeed[0] = 0;
  watchSpeed[0] = 0;
  openFiles(); // Input all data.

  calcAcc(); // Calculate average acceleration.
  findErrors(); // Find outliers of the data and replace with expected value (based on average acceleration)

  actualSpeed(); // Calculate actual speed for each second.
}


speed::~speed(){
  cout << "Destructor called." << endl;
}


void speed::openFiles(){
  ifstream gps("RTK_GPS.txt");
  ifstream watch("SmartWatch.txt");

  if (!gps || !watch) { // If either file does not open successfully.
      cerr << "Error opening file(s)." << endl;
      return;
  }

  for(int time = 1; time < 100; time++) { // Copy data into array memory.
      gps >> gpsSpeed[time];
      watch >> watchSpeed[time];
  }
  gps.close(); // Discontinue using the file, it is now in our array. Saves memory.
  watch.close(); // Ditto

  return;
}


void speed::calcAcc(){
  double sumDiff = 0; 
  for(int time = 0; time < 99; time++) { // For all values in between each of the 100 entries
      sumDiff += watchSpeed[time + 1] - watchSpeed[time]; // Add the difference between all watch times.
      sumDiff += gpsSpeed[time + 1] - gpsSpeed[time]; // Add the difference between all gps times.
  }

  avgAcc = sumDiff / (99 * 2); // Average of all differences of both datasets, and there are 99 differences each.
  cout << "Average Acceleration is " << avgAcc << endl;
  cout << endl;

  return;
}

void speed::findErrors() {
  double stdDev = sqrt(0.1); // Variance is given as 0.1, standard deviation is sqrt(variance).
  double range = 3 * stdDev; // 3 standard deviations accounts for 99.7% of all cases. It should be extremely unlikely to be in the 0.3% of data, especially for such a small dataset.
  for(int time = 1; time < 100; time++){
    double estimatedSpeed = time * avgAcc; // seconds * meters/second^2 = meters/sec
    double upperBound = estimatedSpeed + range; // Upper boundary for realistic values
    double lowerBound = estimatedSpeed - range; // Lower boundary for realistic values

    if(gpsSpeed[time] > upperBound || gpsSpeed[time] < lowerBound){ // If above or below 3 standard deviations away from average, it is anomalous.
      cout << "The GPS data " << gpsSpeed[time] << " at the time " << time << " seconds is wrong." << endl;
    }
    
    if(watchSpeed[time] > upperBound || watchSpeed[time] < lowerBound){// If above or below 3 standard deviations away from average, it is anomalous.
      cout << "The watch data " << watchSpeed[time] << " at the time " << time << " seconds is wrong." << endl;
    }
  }
  cout << endl;

  return;
}


void speed::actualSpeed(){
  actualSpeedArr[0] = 0; // Speed is assumed to begin at 0
  for(int time = 1; time < 100; time++){
    actualSpeedArr[time] = avgAcc * time; // m/s^2 * s = m/s
  }

  return;
}


void speed::searchByTime(int time){ // Retrieve stored data at time requested
  cout << "GPS Speed: " << gpsSpeed[time] << endl;
  cout << "Watch Speed: " << watchSpeed[time] << endl;
  cout << "Estimated Actual Speed: " << actualSpeedArr[time] << endl;
  
  return;
}


void speed::searchByGPSSpeed(int target){
  cout << "GPS: ";
  for(int time = 0; time < 100; time++) {
    int nearest = round(gpsSpeed[time]); // The value that is closest to the current speed
    if(target == nearest) { // If the target is close to the current speed
      cout << "Found it! The corresponding time is " << time << " for a recorded speed of " << gpsSpeed[time] << endl;
      return;
    }
  }
  cout << "Cannot find record." << endl;

  return;
}

void speed::searchByWatchSpeed(int target){
  cout << "Watch: ";
  for(int time = 0; time < 100; time++) {
    int nearest = round(watchSpeed[time]); // The value that is closest to the current speed
    if(target == nearest) { // If the target is close to the current speed
      cout << "Found it! The corresponding time is " << time << " for a recorded speed of " << watchSpeed[time] << endl;
      return;
    }
  }
  cout << "Cannot find record." << endl;

  return;
}

void speed::display(){
  for(int time = 1; time < 100; time++){
    cout << "The estimated actual data at time " << time << " seconds is " << actualSpeedArr[time] << "." << endl; // Retrieve stored data for each time
  }

  return;
}