# Introduction

Healthcare is given the extreme importance now a- days by each country with the advent of the novel corona virus. <br/>
So in this aspect, an IoT based health monitoring system as a solution for such an epidemic. <br/>
Internet of Things (IoT) is the new revolution of internet which is the growing research area especially in the health care. <br/>
With the increase in use of wearable sensors and the smart phones, these remote health care monitoring has evolved in such a pace. <br/>
IoT monitoring of health helps in preventing the spread of disease as well as to get a proper diagnosis of the state of health, even if the doctor is at far distance. <br/>
In this project, a portable physiological checking framework is displayed, which can continuously screen the patient’s heartbeat, temperature and other basic parameters of the room. <br/>
We proposed a nonstop checking and control instrument to screen the patient condition and store the patient information’s in server utilising Wi-Fi Module (ESP8266) based remote correspondence. <br/>
A remote health monitoring system using IoT is proposed where the authorised personal can access these data stored using an IoT platform (ThinkSpeak) and based on these values received, the diseases are diagnosed by the doctors from a distance.<br/>

# Objectives

The core objective of this project is the design and implementation of a smart patient health tracking system that uses Sensors to track patient health and uses internet to inform their loved ones in case of any issues. <br/>
The objective of developing monitoring systems is to reduce health care costs by reducing physical office visits, hospitalisations, and diagnostic testing procedure. <br/>
Each of our bodies utilises temperature and also pulse acknowledging to peruse understanding wellbeing. The sensors are linked to a microcontroller to track the status which is thus interfaced to a LCD screen and additionally remote association with the capacity to alert the concerned. <br/>
If framework finds any sudden changes in understanding heart beat or body temperature, the framework can consequently alarms the client about the patients status over IOT and furthermore indicates subtle elements of pulse and temperature of patient live on the web. <br/>

![1]()

## Fig. : IoT Based Patient Health Monitoring System using ESP8266 & Anduino

![2]()

## Fig. : Basic Sensor Monitoring

# Working Principle

The Arduino Sketch running over the device implements the various functionalities of the health care system. <br/>
Functions like reading sensor data <br/>
Converting them into strings <br/>
Passing them to the IoT platform (ThinkSpeak) <br/>
Displaying measured pulse rate and temperature on character LCD & hosted IoT platform (ThinkSpeak) <br/>

# Expected Results

The body temperature sensor, pulse rate sensor, room temperature and humidity sensor values are calibrated using the microcontroller and displayed on the LED board.

![3]()

## Fig. : Working Prototype

These sensor values are then sent to the database server. These data can be accessed from cloud by the authorised users using the IoT application platform. The sensor values of the patient is displayed in the application as shown in Fig.

![4]()

## Fig. : ThinkSpeak IoT Portal’s Widget Panel

# Advantages and Applications

Advantages :

Portable pocket sized health monitoring system.

Real time health care data logging/ storing (can be used for analytics purposes)

Easily accessible ThinkSpeak E-Portal / Monitoring system, which can be accessed anywhere around the world, to keep check on your loved one.

Less intrusive hardware, highly user friendly targeting a broader age group.

Applications :

Remote areas which are inaccessible to health care facilities, if educated can take care of their health with this tool.

Health monitoring/ logging purposes for analytics.

# Conclusion and Reference

The Internet of Things is considered now as one of the feasible solutions for any remote value tracking especially in the field of health monitoring.
It facilitates that the individual prosperity parameter data is secured inside the cloud, stays in the hospital are reduced for conventional routine examinations and most important that the health can be monitored and disease diagnosed by any doctor at any distance.
In this project, an IoT based health monitoring system was developed. The system monitored body temperature, pulse rate and room humidity and temperature using sensors, which are also displayed on a LCD.
These sensor values can then be sent to a medical server using wireless communication. These data are then received in an authorised personals smart phone with IoT platform.
With the values received the doctor then diagnose the disease and the state of health of the patient.

References :

Research Paper : “An IoT based Patient Health Monitoring System”
Publisher : IEEE
Authors : D. Shiva Rama Krishnan, Subhash Chand Gupta, Tanupriya Choudhury
