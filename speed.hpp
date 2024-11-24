#ifndef speed_hpp
#define speed_hpp


class speed{
private:
  double gpsSpeed[100]; // Holds the values for both position and time for each of the 99 entries.
  double watchSpeed[100];
  double actualSpeedArr[100];
  double gpsAcc;
  double watchAcc;
  double avgAcc;
public:
  speed();
  ~speed();

  void openFiles();
  double findGPSAcc();
  double findWatchAcc();
  double actualSpeed();
  void searchByTime(int);
  void searchByGPSSpeed(int);
  void searchByWatchSpeed(int);
  void display();
};


#endif /* speed_hpp */