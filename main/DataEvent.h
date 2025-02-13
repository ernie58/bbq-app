#include <map>
#include <string>
#include <variant>
#include <optional>

using PropertyValue = std::variant<int, float, std::string>;

struct DataEvent {
    std::map<std::string, PropertyValue> properties;

    template <typename T>
    std::optional<T> getProperty(const std::string& key) const {
        auto it = properties.find(key);
        if (it != properties.end() && std::holds_alternative<T>(it->second)) {
            return std::get<T>(it->second);
        }
        return std::nullopt;
    }
};
