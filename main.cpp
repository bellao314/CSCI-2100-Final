#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    double record[99][2]; // Holds the values for both position and time for each of the 99 entries.

    ifstream gps("RTK_GPS.txt");
    ifstream watch("SmartWatch.txt");

    if (!gps || !watch) { // If either file does not open successfully.
        cerr << "Error opening file(s)." << endl;
        return 1;
    }
    
    for(int i = 0; i < 99; i++) { // Copy data into array memory.
        gps >> record[i][0];
        watch >> record[i][1];
    }
    gps.close(); // Discontinue using the file, it is now in our array.
    watch.close(); // Ditto
    
    double differences[98][2]; // Stores {Position Difference, Time Difference}
    double sumDifferences[2] = {0,0}; // Holds the sum of all position and time differences
    double acceleration[98]; // Stores the acceleration for each step
    for(int i = 0; i < 98; i++) {
        differences[i][0] = record[i+1][0] - record[i][0]; // Position difference = next recorded position - this recorded position
        sumDifferences[0] += differences[i][0]; // Sum of position differences
        differences[i][1] = record[i+1][1] - record[i][1]; // Time difference = next recorded time - this recorded time
        sumDifferences[1] += differences[i][1]; // Sum of time differences
    }
    double averageDifference[2] = {sumDifferences[0] / 98, sumDifferences[1] / 98}; // Average difference for position and time
    cout << "Average GPS Difference: " << averageDifference[0] << endl;
    cout << "Average Time Difference: " << averageDifference[1] << endl;

    // Average difference will be our slope. Slope intercept is known to be 1 for both records. We know the variance is 0.1, so the standard deviation is = sqrt(0.1).
    double standardDev = sqrt(0.1);

    for(int i = 0; i < 99; i++) {
        double expectedGPSValue = i * averageDifference[0] + 1; // y = mx + b -> expected = averageDiff*i + 1
        double expectedTimeValue = i * averageDifference[1] + 1; // Ditto
        if((record[i][0] > expectedGPSValue + 3 * standardDev) || (record[i][0] < expectedGPSValue - 3 * standardDev)) { // If the record is more than 3 standard deviations above or below the expected, it is anomalous.
            cout << "Anomalous GPS Entry: " << record[i][0] << " Expected: " << expectedGPSValue << endl;
            record[i][0] = expectedGPSValue; // Replace the erroneous record with a more realistic one.

            if(i > 0) { // If the previous record is within the array
                differences[i - 1][0] = record[i][0] - record[i - 1][0]; // The difference before this record must be fixed.
            }
            if(i < 98) { // If the next record is within the array
                differences[i][0] = record[i + 1][0] - record[i][0]; // The difference after this record must be fixed.
            }
        }
        if((record[i][1] > expectedTimeValue + 3 * standardDev) || (record[i][1] < expectedTimeValue - 3 * standardDev)) { // Ditto
            cout << "Anomalous Time Entry: " << record[i][1] << " Expected: " << expectedTimeValue << endl;
            record[i][1] = expectedTimeValue; // Replace the erroneous record with a more realistic one.

            if(i > 0) { // If the previous record is within the array
                differences[i - 1][1] = record[i][1] - record[i - 1][1]; // The difference before this record must be fixed.
            }
            if(i < 98) { // If the next record is within the array
                differences[i][1] = record[i + 1][1] - record[i][1]; // The difference after this record must be fixed.
            }
        }

    }
    
    double speed = 0; // Speed is assumed to start at 0.
    for(int i = 0; i < 98; i++) { // Now that the records and differences are fixed, we calculate acceleration.
        acceleration[i] = differences[i][0] / differences[i][1]; // Acceleration = change in position / change in time
        speed = speed + acceleration[i]; // Speed increases after every acceleration step.
        cout << "Speed at time " << record[i][1] << " seconds is " << speed << " m/s." << endl;
    }
    cout << "Final Speed: " << speed << endl;

    return 0;
}
