# Ultra-Sound-Sensor-Project---H-S
Project done in the context of the lesson of Hardware &amp; Software Platforms (2 ECTS) given by Pr. Valderrama at Polytechnical Faculty of Mons.

We started from a tutorial proposed on the website "Instructables", called "Ultra-sound car parking sensor" (http://www.instructables.com/id/Arduino-Parking-Sensor/).

Once the tutorial has been achieved, we then must innovate and bring our personal touch, make an improvement. 

From using one I²C ultra-sound sensor (SRF-02) and a buzzer connected to an ESP8266, we added two similar ultra-sound sensor. We are aiming to create an autonomous car able to get out of a maze, so the buzzer is not useful anymore. The ESP and sensors were connected on a platform/robot called "Pololu" created by Daniel Binon, technician in the SEMi of UMons (datasheets will be joined on this github to have a better understanding of the project).

Here's the pinout of our project, including the ESP, 3 SRF-02 sensors & the Pololu robot.

![maze_car_pinout_final](https://user-images.githubusercontent.com/39089674/39775119-3added92-52fd-11e8-963f-2799ac275f6b.png)

PS : Note that the code imported on the ESP (= MAZE_CAR_main.ino) is adapted to a specific situation, distances and delays are important parameters to properly calibrate our car.
