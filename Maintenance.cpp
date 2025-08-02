#include "Maintenance.hpp"

// --- MaintenanceLog Serialization ---
json MaintenanceLog::toJson() const {
    return {
        {"aircraftID", aircraftID},
        {"date", date},
        {"description", description},
        {"status", status}
    };
}

void MaintenanceLog::fromJson(const json& j) {
    aircraftID   = j.value("aircraftID", "");
    date         = j.value("date", "");
    description  = j.value("description", "");
    status       = j.value("status", "");
}

// --- Maintenance Class Implementation ---
Maintenance::Maintenance() {
    loadLogs();  // Automatically load logs from JSON
}

void Maintenance::addMaintenance(const std::string& aircraftID, const std::string& date,
                                 const std::string& description, const std::string& status) {
    MaintenanceLog log{aircraftID, date, description, status};
    logs.push_back(log);
    saveLogs();  // Save to JSON immediately
}

void Maintenance::loadLogs() {
    logs.clear();
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filePath << ". Starting with empty logs.\n";
        return;
    }

    json j;
    try {
        file >> j;
    } catch (...) {
        std::cerr << "Error: Failed to parse " << filePath << ".\n";
        return;
    }

    for (auto& item : j) {
        MaintenanceLog log;
        log.fromJson(item);
        logs.push_back(log);
    }
}

void Maintenance::saveLogs() {
    json j = json::array();
    for (auto& log : logs)
        j.push_back(log.toJson());

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not save to " << filePath << "\n";
        return;
    }
    file << j.dump(4);
}

void Maintenance::generateMaintenanceReport() {
    std::cout << "\n--- Maintenance Report ---\n";
    if (logs.empty()) {
        std::cout << "No maintenance logs available.\n";
        return;
    }

    for (size_t i = 0; i < logs.size(); ++i) {
        const auto& log = logs[i];
        std::cout << i + 1 << ". Aircraft ID: " << log.aircraftID
                  << "\n   Date: " << log.date
                  << "\n   Task: " << log.description
                  << "\n   Status: " << log.status
                  << "\n-------------------------\n";
    }
}
