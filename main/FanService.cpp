#include "FanService.h"
#include "DataEvent.h"
#include <Arduino.h>

FanService::FanService(int pin) : pin(pin) {

}

void FanService::initializeFan() {
  pinMode(pin, OUTPUT);
  analogWriteFreq(25000);
  analogWrite(pin, 0);
}

void FanService::handleSpeedEvent(int speed) {
    Serial.println("Fan speed set to: " + String(speed));
    int mappedSpeed = map(speed, 0,100,0,255);
    analogWrite(pin, mappedSpeed);
}

void FanService::subscribeToEventBus(EventBus* eventBus) {
    eventBus->subscribe<DataEvent>([this](const DataEvent& event) {
        if (auto fanSpeedOpt = event.getProperty<int>("speed")) {
            handleSpeedEvent(*fanSpeedOpt);
        }
    });
}