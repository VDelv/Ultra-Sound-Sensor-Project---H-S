# Ultra-Sound-Sensor-Project---H-S (DIY)
Project done in the context of the lesson of Hardware &amp; Software Platforms (2 ECTS) given by Pr. Valderrama at Polytechnical Faculty of Mons.

We started from a tutorial proposed on the website "Instructables", called "Ultra-sound car parking sensor" (http://www.instructables.com/id/Arduino-Parking-Sensor/).

Once the tutorial has been achieved, we then must innovate and bring our personal touch, make an improvement. 

From using one I²C ultra-sound sensor (SRF-02) and a buzzer connected to an ESP8266, we added two similar ultra-sound sensor. We are aiming to create an autonomous car able to get out of a maze, so the buzzer is not useful anymore. The ESP and sensors were connected on a platform/robot called "Pololu" created by Daniel Binon, technician in the SEMi of UMons (datasheets will be joined on this github to have a better understanding of the project).

Here's the pinout of our project, including the ESP, 3 SRF-02 sensors & the Pololu robot (see the pins & configuration of the platform Pololu in the "Documentation" file).

![maze_car_pinout_final](https://user-images.githubusercontent.com/39089674/39775119-3added92-52fd-11e8-963f-2799ac275f6b.png)

On the Pololu robot, we can find a H-bridge for DC motors. This component is very important to control each motor of the two wheels. We use PWM (https://en.wikipedia.org/wiki/Pulse-width_modulation) to control each motor. The H-bridge is simple to use and to understand, if you don't know yet how it works, take a look at : https://en.wikipedia.org/wiki/H_bridge. If you are working on a platform made by yourself, without H-bridge for DC motors, you can buy the L298 which is used to control the motors.

Our robot uses as said above the Pololu platform, an ESP (lolin NodeMCU) and 3 SRF-02 sensors -> These 3 sensors are placed in a particular way. One is looking at the left, one at the right and the other forward. Here's the picture of the "car" :

//PICTURE//

## Finally, what is contained in each file of this github :
- Car Park Sensor : contains the tutorial code
- Documentation : contains two datasheets for better understanding of components
- Introducing Ultra Sound Sensor : contains two codes, these are used to check if each device is well connected
- Maze Car : contains the code of calibration of the robot/car and the main code of it, + a description

PS : Note that the code imported on the ESP (= Maze_Car_Main.ino) is adapted to a specific situation, distances and delays are important parameters to properly calibrate our car.
