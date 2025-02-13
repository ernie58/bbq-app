#ifndef WSSERVICE_H
#define WSSERVICE_H

#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ArduinoJson.h>
#include "EventBus.h"

class WebSocketService {
private:
    const int port;
    const char* uri;
    static AsyncWebServer* server;
    static AsyncWebSocket* ws;

public:
    WebSocketService(const int port, const char* uri, EventBus* eventBus);
    void initializeWebSocketServer();
    static void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    static void broadcastJsonObject(const JsonObject& data);
    static EventBus* eventBus;
};

#endif // WSSERVICE_H
