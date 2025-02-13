#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

#include <ESP8266WiFi.h>
#define WEBSERVER_H  // Prevents inclusion of ESP8266WebServer.h
#include <WiFiManager.h>

namespace Wifi {
  
  // Create a wrapper class or functions
  class WifiService {
  private:
      WiFiManager wifiManager;  // Actual WiFiManager object

  public:
      // Initialize WiFiManager
      void begin() {
          wifiManager.autoConnect("YourNetwork");
      }

      void initializeWifi() {
          Serial.println("Starting WiFiManager...");

          // If no WiFi credentials, start AP mode with "ESP-Setup"
          if (!wifiManager.autoConnect("ESP-Setup")) {
              Serial.println("Failed to connect. Restarting...");
              ESP.restart();
          }

          Serial.println("WiFi Connected!");
          Serial.print("ESP IP Address: ");
          Serial.println(WiFi.localIP());
          Serial.print("WiFi Mode: ");
          Serial.println(WiFi.getMode());

      }
  };
}

#endif // WIFI_SERVICE_H
