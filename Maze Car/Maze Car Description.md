# Description of the Maze Car 

The main goal of this project is to program the ESP connected to a small robot called Pololu and sensors so it is able to get out from a maze. 

The way to locate it is based on the use of ultra-sound sensor "SRF02". When the distance between the robot and an obstacle is lower than a threshold, the robot has to take a decision according to the value returned by other sensors (e.g. : If there's a wall ahead and to the right but the sensor doesn't detect any obstacle on the left, the robot will take the decision to move to the left). 

In the first code called "Introducing & Calibrating ... " we determine the value of the parameters in function of the environment. The value of these has to be modified if the size of the maze changed (e.g. : distance between the walls). 
