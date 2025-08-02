#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;

template<typename T>
class JsonPersistence {
public:
    // must be implemented in all classes that inherite from this class
    virtual json toJson() const = 0;
    virtual void fromJson(const json& j) = 0;

    // Save a vector of objects to a JSON file
    static void saveToJson(const std::string& filename, const std::vector<std::shared_ptr<T>>& items){
        // Load existing items to check duplicates
        std::vector<std::shared_ptr<T>> existingItems = loadFromJson(filename);

        // Merge new items, avoiding duplicates
        for (const auto& item : items) {
            if (!item) continue;
            bool exists = false;
            for (const auto& existing : existingItems) {
                if (*existing == *item) { // compare actual objects
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                existingItems.push_back(item);
            }
        }

        // Serialize to JSON
        json jArray;
        for (const auto& item : existingItems) {
            if (item) jArray.push_back(item->toJson()); // dereference shared_ptr
        }

        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        file << jArray.dump(4);
    }
        
    // Load a vector of objects from a JSON file
    static std::vector<std::shared_ptr<T>> loadFromJson(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return {};

        json jArray;
        file >> jArray;

        std::vector<std::shared_ptr<T>> items;
        for (const auto& jItem : jArray) {
            auto obj = std::make_shared<T>();
            obj->fromJson(jItem);
            items.push_back(obj);
        }
        return items;
    }

    virtual ~JsonPersistence() = default;
};

#endif
