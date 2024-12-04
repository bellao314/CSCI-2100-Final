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

  void openFiles();
  void calcAcc();
  void fixErrors();
  void actualSpeed();
  void search(int, double[100], int, int);
public:
  speed();
  ~speed();

  void searchByTime(int);
  void searchByGPSSpeed(int);
  void searchByWatchSpeed(int);
  void display();
};


#endif /* speed_hpp */