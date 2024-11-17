CSCI 2100: Data Structures
Saint Louis University
Prof. Wei Wang

Final Project
by Bella Ott and Cole Patrick

Bill is taking a road trip again, but his car's default speed sensor is broken again. He is unable to determine the vehicle's current speed now. Fortunately, he has a sports watch and a wheel speed sensor that provide an estimate of the speed, though both are imprecise. Additionally, some data from these sensors is completely erroneous due to environmental interference (e.g., wireless multipath effects, manufacturing defects). Assume that sensor noise, which reduces accuracy, follows a normal distribution, while erroneous data is randomly distributed and may vary significantly (showing either extremely high or low values). Please design and implement a C++ program to estimate the vehicle's actual speed.


Some Allowed Assumptions:

1) You can assume the sensor starts to sense the speed at time 1s. The sensor stops sensing the speed at time 99s. 

2) You can assume the vehicle accelerates on a straight road with a constant but unknown acceleration.

3) You can assume the vehicle's speed at time 0s is 0m/s.

4) Acceleration a is defined as the rate of change of velocity (Δv) over the change in time (Δt), represented by the equation a = Δv/Δt. This allows you to measure how fast velocity changes in meters per second squared (m/s^2).

5) You can assume that the variance of the data gathered from these sensors is 0.1. (This may or may not be useful to you.)

6) You may make additional assumptions, but keep in mind that sensor data may be inaccurate or erroneous, and multiple data points could be incorrect.

7) It is OK if your program cannot find the accurate speed of the vehicle. The closer to the actual speed, the better. 
