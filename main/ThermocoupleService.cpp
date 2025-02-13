#include "ThermocoupleService.h"
#include "DataEvent.h"
#include <Arduino.h>

ThermocoupleService::ThermocoupleService(int sckPin, int csPin, int soPin)
    : csPin(csPin), sckPin(sckPin), soPin(soPin), thermocouple(sckPin, csPin, soPin), eventBus(nullptr) {}

void ThermocoupleService::initializeThermocouple() {
    Serial.println("Thermocouple initialized");
}

void ThermocoupleService::readTemperature() {
    double temperature = thermocouple.readCelsius();
    if (isnan(temperature)) {
        Serial.println("Error reading temperature from thermocouple");
        return;
    }

    Serial.println("Temperature: " + String(temperature) + " °C");

    // Emit temperature event to EventBus
    if (eventBus) {
        DataEvent event;
        event.properties["temperature"] = static_cast<float>(temperature);
        eventBus->emit(event);
    }
}

void ThermocoupleService::subscribeToEventBus(EventBus* eventBus) {
    this->eventBus = eventBus;  // Store reference to EventBus
}
