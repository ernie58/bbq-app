#ifndef SERVO_SERVICE_H
#define SERVO_SERVICE_H

#include <Servo.h>
#include "EventBus.h"

class ServoService {
private:
    Servo servo;
    int pin;
    int currentAngle;

public:
    ServoService(int pin);
    void initializeServo();
    void handleAngleEvent(int angle); // Method to handle angle events
    void subscribeToEventBus(EventBus* eventBus);
    void loop();
};

#endif
