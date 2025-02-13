#ifndef MYWIFIMANAGER_H
#define MYWIFIMANAGER_H

// this file is a wrapper to wrap WifiManager in a separate namespace, because its dependencies define enums that conflict with asynwebserver
// Include the original WiFiManager library
#include <WiFiManager.h>

namespace MyWiFiManager {
  
  // Create a wrapper class or functions
  class Manager {
  private:
      WiFiManager wifiManager;  // Actual WiFiManager object

  public:
      // Initialize WiFiManager
      void begin() {
          wifiManager.autoConnect("YourNetwork");
      }

      // Add more methods that you need
      void resetSettings() {
          wifiManager.resetSettings();
      }

      // You can also forward WiFiManager methods if necessary
      void startAP(const char* ssid) {
          wifiManager.startConfigPortal(ssid);
      }

      // Optionally expose a method to check if connected
      bool isConnected() {
          return WiFi.isConnected();
      }
  };
}

#endif // MYWIFIMANAGER_H
