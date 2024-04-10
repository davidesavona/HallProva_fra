#include "hallsensor.h"
#include<wiringPi.h>
#include<iostream>

hallsensor::hallsensor()
{

};

void hallsensor::initHall(){
    if (wiringPiSetup () == -1) exit (1) ;
    pinMode(sensorPin,INPUT);
    stateHall=0;

}
bool hallsensor::triggerHall(){
    if(digitalRead(sensorPin)==HIGH){
        return 0;

    }else return 1;
}
