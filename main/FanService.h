#ifndef FAN_SERVICE_H
#define FAN_SERVICE_H

#include "EventBus.h"
#include <Arduino.h>

class FanService {
private:
    int pin;

public:
    FanService(int pin);
    void initializeFan();
    void handleSpeedEvent(int speed); // Method to handle speed events
    void subscribeToEventBus(EventBus* eventBus);
    void loop();
};

#endif
