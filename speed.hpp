#ifndef speed_hpp
#define speed_hpp

class speed{
private:
  double gpsSpeed[100]; // Holds the values of speed for time 0 + all 99 pieces of gps data
  double watchSpeed[100]; // Holds the value of speed for time 0 + all 99 pieces of watch data
  double actualSpeedArr[100]; // Holds the estimated value of speed based on the two datasets.
  double avgAcc;

  void openFiles(); // Retrieves both data files and stores them in gpsSpeed and watchSpeed
  void calcAcc(); // Calculates the avgAcc based on the average difference between each data point.
  void findErrors(); // Reads each data point in each speed array, and reports them as an anomaly if they are outside of a 3 standard deviation range.
  void actualSpeed(); // Based on avgAcc, generates an estimated speed for each time.
public:
  speed(); // Constructs the speed object, doing all the above private functions.
  ~speed(); // No pointers or heap objects, so this simply reports the deconstruct.

  void searchByTime(int); // Given a time, prints all data at that time.
  void searchByGPSSpeed(int); // Given a speed, finds the closest value in the dataset.
  void searchByWatchSpeed(int); // Ditto.
  void display(); // Prints all times and estimated speeds for each time.
};


#endif /* speed_hpp */