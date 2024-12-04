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
  fixErrors(); // Find outliers of the data and replace with expected value (based on average acceleration)

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
  gpsSpeed[0] = watchSpeed[0] = 0; // Speed is known to start at 1.
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

void speed::fixErrors() {
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
  actualSpeedArr[0] = 0;
  for(int time = 1; time < 100; time++){
    actualSpeedArr[time] = avgAcc * time;
  }

  return;
}


void speed::searchByTime(int time){
  cout << "GPS Speed: " << gpsSpeed[time] << endl;
  cout << "Watch Speed: " << watchSpeed[time] << endl;
  cout << "Estimated Actual Speed: " << actualSpeedArr[time] << endl;
  cout << endl;
  
  return;
}


void speed::searchByGPSSpeed(int target){
  cout << "GPS: ";
  search(target, gpsSpeed, 0, 99);

  return;
}

void speed::searchByWatchSpeed(int target){
  cout << "Watch: ";
  search(target, watchSpeed, 0, 99);

  return;
}

void speed::search(int target, double arr[100], int left, int right) {
 int middle = (left + right) / 2;

 int closest = round(middle); // Find the closest whole number

 if(left > right) {
    cout << "Cannot find record." << endl;
 } else if(target == closest) { // If arr[middle] is the closest data point to the target. You would never find anything if you had to type a super specific number like 3.98272382, so do a rough search.
    cout << "Found it! The corresponding index is " << middle << " for a recorded speed of " << arr[middle] << "." << endl;
 } else if(target > arr[middle]) {
    search(target, arr, middle + 1, right);
 } else if(target < arr[middle]) {
    search(target, arr, left, middle - 1);
 }
 return;
}

void speed::display(){
  for(int time = 1; time < 100; time++){
    cout << "The estimated actual data at time " << time << " seconds is " << actualSpeedArr[time] << "." << endl;
  }
  cout << endl;

  return;
}