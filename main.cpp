#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

void fixAnomalies(double[], double[][99], double[][98], double);
int search(double, double[]);

int main() {
    double record[2][99]; // Holds the values for both position and time for each of the 99 entries.

    ifstream gps("C:/Users/Cole/csci2100final/CSCI-2100-Final/RTK_GPS.txt");
    ifstream watch("C:/Users/Cole/csci2100final/CSCI-2100-Final/SmartWatch.txt");

    if (!gps || !watch) { // If either file does not open successfully.
        cout << "Error opening file(s)." << endl;
        return 1;
    }
    for(int i = 0; i < 99; i++) { // Copy data into array memory.
        gps >> record[0][i];
        watch >> record[1][i];
    }
    gps.close(); // Discontinue using the file, it is now in memory.
    watch.close(); // Ditto
    
    double differences[2][98]; // Stores {Position Difference, Time Difference}
    double sumDifferences[2] = {0,0}; // Holds the sum of all position and time differences
    double acceleration[98]; // Stores the acceleration for each step
    for(int i = 0; i < 98; i++) {
        differences[0][i] = record[0][i+1] - record[0][i]; // Position difference = next recorded position - this recorded position
        sumDifferences[0] += differences[0][i]; // Sum of position differences
        differences[1][i] = record[1][i+1] - record[1][i]; // Time difference = next recorded time - this recorded time
        sumDifferences[1] += differences[1][i]; // Sum of time differences
    }
    double averageDifference[2] = {sumDifferences[0] / 98, sumDifferences[1] / 98}; // Average difference for position and time
    cout << "Average GPS Difference: " << averageDifference[0] << endl;
    cout << "Average Time Difference: " << averageDifference[1] << endl;

    // Average difference will be our "slope." Slope intercept is known to be 1 for both records. We know the variance is 0.1, so the standard deviation is = sqrt(0.1) ~ 0.316.
    fixAnomalies(averageDifference, record, differences, sqrt(0.1));
    
    double speed[99] = {0}; // Speed is assumed to start at 0.
    for(int i = 0; i < 98; i++) { // Now that the records and differences are fixed, we calculate acceleration.
        acceleration[i] = differences[0][i] / differences[1][i]; // Acceleration = change in position / change in time
        speed[i + 1] = speed[i] + acceleration[i]; // Speed increases after every acceleration step.
        cout << "Speed at time " << record[1][i] << " seconds is " << speed[i+1] << " m/s." << endl;
    }
    cout << "Final Speed: " << speed[98] << endl;

    int input1 = -2;
    double input2;
    while(input1 != -1) {
        input2 = -2;
        cout << "Specify data to search(0 for gps, 1 for watch, -1 to exit): ";
        cin >> input1;
        switch(input1) {
            case 0:
                while(input2 != -1) {
                    cout << "Enter gps value. -1 to exit: ";
                    cin >> input2;
                    if(input2 != -1) {
                        int result = search(input2, record[0]);
                        if(result == -1) {
                            cout << "Cannot find the data." << endl;
                        } else {
                            cout << "Found. The corresponding index is: " << result << endl;
                        }
                    }
                }
                break;
            case 1:
                while(input2 != -1) {
                    cout << "Enter watch value. -1 to exit: ";
                    cin >> input2;
                    if(input2 != -1) {
                        int result = search(input2, record[1]);
                        if(result == -1) {
                            cout << "Cannot find the data." << endl;
                        } else {
                            cout << "Found. The corresponding index is: " << result << endl;
                        }
                    }
                }
                break;
        }
    }

    return 0;
}

int search(double target, double record[]) {
    for(int i = 0 ; i < 99; i++) {
        if(record[i] == target) {
            return i;
        }
    }
    return -1;
}

void fixAnomalies(double averageDifference[], double record[][99], double differences[][98], double standardDev) {
    for(int i = 0; i < 99; i++) {
        double expectedGPSValue = i * averageDifference[0] + 1; // y = mx + b -> expected = averageDiff*i + 1
        double expectedTimeValue = i * averageDifference[1] + 1; // Ditto
        if((record[0][i] > expectedGPSValue + 3 * standardDev) || (record[0][i] < expectedGPSValue - 3 * standardDev)) { // If the record is more than 3 standard deviations above or below the expected, it is anomalous.
            cout << "Anomalous GPS Entry: " << record[0][i] << " Expected: " << expectedGPSValue << endl;
            record[0][i] = expectedGPSValue; // Replace the erroneous record with a more realistic one.

            if(i > 0) { // If the previous record is within the array
                differences[0][i - 1] = record[0][i] - record[0][i - 1]; // The difference before this record must be fixed.
            }
            if(i < 98) { // If the next record is within the array
                differences[0][i] = record[0][i + 1] - record[0][i]; // The difference after this record must be fixed.
            }
        }
        if((record[1][i] > expectedTimeValue + 3 * standardDev) || (record[1][i] < expectedTimeValue - 3 * standardDev)) { // Ditto
            cout << "Anomalous Time Entry: " << record[1][i] << " Expected: " << expectedTimeValue << endl;
            record[1][i] = expectedTimeValue; // Replace the erroneous record with a more realistic one.

            if(i > 0) { // If the previous record is within the array
                differences[1][i - 1] = record[1][i] - record[1][i - 1]; // The difference before this record must be fixed.
            }
            if(i < 98) { // If the next record is within the array
                differences[1][i] = record[1][i + 1] - record[1][i]; // The difference after this record must be fixed.
            }
        }
    }
    return;
}
