#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct MaintenanceLog {
    std::string aircraftID;
    std::string date;         // YYYY-MM-DD
    std::string description;  // e.g., "Engine Check"
    std::string status;       // e.g., "Completed", "Scheduled"

    json toJson() const;
    void fromJson(const json& j);
};

class Maintenance {
private:
    std::vector<MaintenanceLog> logs;
    const std::string filePath = "data/maintenance.json";

public:
    Maintenance();

    void addMaintenance(const std::string& aircraftID, const std::string& date,
                        const std::string& description, const std::string& status);

    void loadLogs();
    void saveLogs();

    void generateMaintenanceReport();
};

#endif
