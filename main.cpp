#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    double record[99][2]; 

    ifstream gps("RTK_GPS.txt");
    ifstream watch("SmartWatch.txt");

    if (!gps || !watch) {
        cerr << "Error opening file(s)." << endl;
        return 1;
    }
    
    for(int i = 0; i < 99; i++) {
        gps >> record[i][0];
        watch >> record[i][1];
    }
    gps.close();
    watch.close();
    
    double differences[98][2];
    double sumDifferences[2] = {0,0};
    for(int i = 0; i < 98; i++) {
        differences[i][0] = record[i+1][0] - record[i][0];
        sumDifferences[0] += differences[i][0];
        differences[i][1] = record[i+1][1] - record[i][1];
        sumDifferences[1] += differences[i][1];
    }
    double averageDifference[2] = {sumDifferences[0] / 98, sumDifferences[1] / 98};
    cout << "Average GPS Difference: " << averageDifference[0] << endl;
    cout << "Average Time Difference: " << averageDifference[1] << endl;

    double sumDiffFromAverage[2] = {0,0};
    for(int i = 0; i < 98; i++) {
        sumDiffFromAverage[0] += pow(averageDifference[0] - differences[i][0], 2);
        sumDiffFromAverage[1] += pow(averageDifference[1] - differences[i][1], 2);
    }
    double standardDev[2] = {pow(sumDiffFromAverage[0] / 98, 0.5), pow(sumDiffFromAverage[1] / 98, 0.5)};
    cout << "GPS Standard Deviation: " << standardDev[0] << endl;
    cout << "Time Standard Deviation: " << standardDev[1] << endl;

    return 0;
}
