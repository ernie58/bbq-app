
// wiring inside unit
// servo bruin -> vol bruin -> GND
// servo geel -> bruin-wit -> PWM
// servo oranje -> blauw -> 5V

// fan geel -> oranje vol -> RPM
// fan zwart -> oranje-wit -> GND
// fan blauw -> groen vol -> PWM
// fan rood -> groen-wit -> 12V

#include "Wifi.h"
#include "WebSocket.h"
#include "ServoService.h"
#include "FanService.h"
#include "EventBus.h"
#include "DataEvent.h"
#include "ThermocoupleService.h"

// Components
Wifi::WifiService* wifiService;
WebSocketService* wsService;
ServoService* servoService;
FanService* fanService;
ThermocoupleService* thermocoupleService;
EventBus* eventBus;

// Declare the state as a JsonObject
StaticJsonDocument<200> doc;
JsonObject state = doc.to<JsonObject>();

void setup() {
    Serial.begin(74880);
    delay(500);
    setupEventBus();
    setupWifi();
    setupWebSocket();
    setupServo();
    setupFan();
    setupThermocouple();
}

void loop() {
    delay(1000); // WebSocket needs to be polled periodically
    thermocoupleService->readTemperature();
}

void setupWifi(){
  wifiService = new Wifi::WifiService();  // Use `new` to allocate memory for the pointer
  wifiService->initializeWifi();  // Call the method on the pointer
}

void setupEventBus() {
    eventBus = new EventBus(); // Initialize EventBus
    // Subscribe to the temperature event and update the state object
    eventBus->subscribe<DataEvent>([](const DataEvent& event) {
        if (auto tempOpt = event.getProperty<float>("temperature")) {
            state["temperature"] = *tempOpt;
            wsService->broadcastJsonObject(state);  // Call this to send the updated state
        }
    });
}

void setupServo() {
    servoService = new ServoService(5);
    servoService->initializeServo();
    servoService->subscribeToEventBus(eventBus); // Subscribe servo to EventBus
}

void setupWebSocket() {
    wsService = new WebSocketService(80, "/", eventBus);
    wsService->initializeWebSocketServer();
}

void setupFan(){
  fanService = new FanService(4);
  fanService->initializeFan();
  fanService->subscribeToEventBus(eventBus);
}

void setupThermocouple() {
    // Define pins for the MAX6675 (example: SCK = D5, CS = D6, SO = D7)
    const int sckPin = 14; // Replace with your actual pin numbers
    const int csPin = 12;
    const int soPin = 13;

    thermocoupleService = new ThermocoupleService(sckPin, csPin, soPin);
    thermocoupleService->initializeThermocouple();
    thermocoupleService->subscribeToEventBus(eventBus);
}