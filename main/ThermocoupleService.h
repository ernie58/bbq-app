#ifndef THERMOCOUPLE_SERVICE_H
#define THERMOCOUPLE_SERVICE_H

#include "EventBus.h"
#include <max6675.h>

class ThermocoupleService {
private:
    int csPin;
    int sckPin;
    int soPin;
    MAX6675 thermocouple;
    EventBus* eventBus; 


public:
    ThermocoupleService(int sckPin, int csPin, int soPin);
    void initializeThermocouple();
    void readTemperature();
    void subscribeToEventBus(EventBus* eventBus);
};

#endif