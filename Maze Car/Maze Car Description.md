# Description of the Maze Car 

The main goal of that school project is to programm a small robot called pololu to allow it to go out from a maze. 

The way to locate it is based on the used of ultra sound captor "SRF02". When the distance between the robot and an obstacle is lower than a treshold, the robot has to take a decision in funciton of the value returned by other sensor (if place at the left and obstacle forward => go left). 

In the first code called "Introducing & Calibrating ... " we determine the value of the parameters in function of the environment. The value of them has to be modify if the maze changed. 
