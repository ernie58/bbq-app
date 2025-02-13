#include "ServoService.h"
#include "DataEvent.h"


ServoService::ServoService(int pin) : pin(pin), currentAngle(1000) {

}

void ServoService::initializeServo() {
    servo.attach(pin, 1000, 2000);
    servo.writeMicroseconds(currentAngle); // Set initial position
}

void ServoService::handleAngleEvent(int angle) {
    // if (angle >= 0 && angle <= 180) { // Valid angle range
        currentAngle = angle;
        Serial.println("Servo angle set to: " + String(angle));
        servo.writeMicroseconds(currentAngle);
    // }
}

void ServoService::subscribeToEventBus(EventBus* eventBus) {
    eventBus->subscribe<DataEvent>([this](const DataEvent& event) {
        if (auto angleOpt = event.getProperty<int>("angle")) {
            handleAngleEvent(*angleOpt);
        }
    });
}