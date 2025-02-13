#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <map>
#include <vector>
#include <functional>

// TypeID function using unique static addresses
template <typename T>
const void* TypeID() {
    static const char id = 0;  // Static variable with unique address
    return &id;
}

class EventBus {
private:
    // Map of type IDs to handlers
    std::map<const void*, std::vector<std::function<void(const void*)>>> handlers;

public:
    // Subscribe to an event type
    template <typename T, typename Handler>
    void subscribe(Handler&& handler) {
        auto& typeHandlers = handlers[TypeID<T>()];
        typeHandlers.push_back([h = std::forward<Handler>(handler)](const void* event) {
            h(*static_cast<const T*>(event));
        });
    }

    // Emit an event type
    template <typename T>
    void emit(const T& event) {
        auto it = handlers.find(TypeID<T>());
        if (it != handlers.end()) {
            for (auto& handler : it->second) {
                handler(&event);
            }
        }
    }
};

#endif
