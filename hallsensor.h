#ifndef HALLSENSOR_H
#define HALLSENSOR_H


class hallsensor
{
private:
    const int sensorPin=8;
public:
    hallsensor();
    void initHall();
    bool triggerHall();
    bool stateHall;
};

#endif // HALLSENSOR_H
