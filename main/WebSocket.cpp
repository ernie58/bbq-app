#include "WebSocket.h"
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ArduinoJson.h>
#include "DataEvent.h"
#include "EventBus.h"

AsyncWebServer* WebSocketService::server = nullptr;
AsyncWebSocket* WebSocketService::ws = nullptr;
EventBus* WebSocketService::eventBus = nullptr;

WebSocketService::WebSocketService(const int port, const char* uri, EventBus* eventBus)
    : port(port), uri(uri) {
      WebSocketService::eventBus = eventBus;
    }

void WebSocketService::initializeWebSocketServer() {
    Serial.println("Initializing WebSocket...");
    server = new AsyncWebServer(port);
    ws = new AsyncWebSocket(uri);

    ws->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        onWebSocketEvent(server, client, type, arg, data, len);
    });

    server->addHandler(ws);
    server->begin();
    Serial.println("WebSocket server started");
}

void WebSocketService::onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
    if (type == WS_EVT_DATA) {
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, data, len);

        if (error) {
            Serial.println("JSON deserialization failed: " + String(error.c_str()));
            return;
        }

        // Create a DataEvent
        DataEvent event;

        // Loop through all key-value pairs in the JSON object
        JsonObject obj = doc.as<JsonObject>();
        for (JsonPair kv : obj) {
            String key = kv.key().c_str();

            // Dynamically add properties to the DataEvent
            if (kv.value().is<int>()) {
                event.properties[key.c_str()] = kv.value().as<int>();
            } else if (kv.value().is<float>()) {
                event.properties[key.c_str()] = kv.value().as<float>();
            } else if (kv.value().is<const char*>()) {
                event.properties[key.c_str()] = std::string(kv.value().as<const char*>());
            }
        }

        // Emit the DataEvent
        if (eventBus) {
            eventBus->emit(event);
        }
    }
}
// Method to broadcast the JSON object to all clients
void WebSocketService::broadcastJsonObject(const JsonObject& data) {
    if (ws->count() > 0) {  // Only broadcast if clients are connected
        String output;
        serializeJson(data, output);  // Serialize JsonObject to a JSON string

        // Broadcast the serialized JSON to all connected clients
        ws->textAll(output);
    }
}

