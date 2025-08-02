/**
 * @file User.cpp
 * @brief Implements the User class methods for the Airline Reservation and Management System.
 *
 * This file provides:
 * - User management (add, update, delete)
 * - Menu-driven interface for administrators
 * - JSON-based persistence for storing users
 * - User activity logging and reporting
 */

#include "User.hpp"

// --- Static Members ---
std::vector<std::shared_ptr<User>> User::userList = {};
std::vector<std::pair<std::string,std::string>> User::activityLogs;

static std::string filePath = "data/users_log.json"; ///< Path to the JSON user log file


// =====================================================================
//                        Menu Functions
// =====================================================================

void User::showMenu() {
    std::cout <<"--- Manage Users ---\n";
    std::cout << "1. View Users\n"
              << "2. Add User\n"
              << "3. Update User\n"
              << "4. Delete User\n"
              << "5. Logout\n";
    processChoice();
}

void User::processChoice() {
    int choice;
    std::string id;

    std::cout << "Enter choice:\n";
    std::cin >> choice;

    switch(choice) {
        case 1:
            std::cout << "--- All Users ---\n";
            get_allUsers();
            break;

        case 2:
            std::cout << "--- Add User ---\n";
            setUser();
            break;

        case 3:
            std::cout << "--- Update User ---\n";
            std::cout << "Enter User ID: ";
            std::cin >> id;
            updateUser(id);
            break;

        case 4:
            std::cout << "--- Delete User ---\n";
            std::cout << "Enter User ID: ";
            std::cin >> id;
            deleteUser(id);
            break;

        case 5:
            std::cout << "--- Logging out ---\n";
            User::logActivity(getID(), "Logged Out");
            return;

        default:
            std::cerr << "Invalid input\n";
            break;
    }
}


// =====================================================================
//                        User Management
// =====================================================================

void User::get_allUsers() {
    loadUsers(); // Reload from JSON

    if (userList.empty()) {
        std::cout << "No users available.\n";
        return;
    }

    for (const auto& userPtr : userList) {
        if (!userPtr) continue;

        std::cout << "Username: " << userPtr->username << "\n"
                  << "User ID: " << userPtr->ID << "\n"
                  << "Role: " << userPtr->role << "\n"
                  << "-----------------------------\n";
    }
}

void User::setUser() {
    int inputID;
    auto newUser = std::make_shared<User>();

    std::cout << "Enter Username: ";
    std::cin >> newUser->username;

    std::cout << "Enter Password: ";
    std::cin >> newUser->password;

    std::cout << "Enter ID: ";
    std::cin >> inputID;
    newUser->ID = std::to_string(inputID);

    std::cout << "Enter Role: ";
    std::cin >> newUser->role;

    // Add to list
    userList.push_back(newUser);
    std::cout << "User added successfully!\n";

    // Save to JSON
    saveUsers();
}

/**
 * @brief Update a user's password and role directly in the JSON file by their ID.
 */
void User::updateUser(const std::string& id) {
    json j;
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cout << "No users found.\n";
        return;
    }
    inFile >> j;
    inFile.close();

    bool found = false;
    for (auto& item : j) {
        if (item["id"] == id) {
            std::string newPassword, newRole;

            std::cout << "Enter new password: ";
            std::cin >> newPassword;

            std::cout << "Enter new role (current: " << item["role"] << "): ";
            std::cin >> newRole;

            item["password"] = newPassword;
            item["role"] = newRole;

            found = true;
            break;
        }
    }

    if (found) {
        std::ofstream outFile(filePath, std::ios::trunc);
        outFile << std::setw(4) << j;
        outFile.close();
        std::cout << "User " << id << " updated successfully!\n";

        loadUsers(); // Refresh in-memory list
    } else {
        std::cout << "No user with ID: " << id << " was found\n";
    }
}


/**
 * @brief Delete a user from the JSON file by their ID.
 */
void User::deleteUser(const std::string& id) {
    json j;
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cout << "No users found.\n";
        return;
    }
    inFile >> j;
    inFile.close();

    size_t beforeSize = j.size();
    j.erase(std::remove_if(j.begin(), j.end(),
                           [&](const json& item) {
                               return item["id"] == id;
                           }),
            j.end());

    if (j.size() < beforeSize) {
        std::ofstream outFile(filePath, std::ios::trunc);
        outFile << std::setw(4) << j;
        outFile.close();
        std::cout << "User " << id << " deleted successfully!\n";

        loadUsers(); // Refresh in-memory list
    } else {
        std::cout << "No User with ID: " << id << " to delete.\n";
    }
}

bool User::operator==(const User& other) const {
    return (ID == other.ID);
}


// =====================================================================
//                   JSON Serialization / Deserialization
// =====================================================================

json User::toJson() const {
    return {
        {"username", username},
        {"password", password},
        {"role", role},
        {"id", ID}
    };
}

void User::fromJson(const json& j) {
    username = j.value("username", "");
    password = j.value("password", "");
    role     = j.value("role", "");

    if (j.contains("id")) {
        if (j["id"].is_number()) {
            ID = std::to_string(j["id"].get<int>());
        } else if (j["id"].is_string()) {
            ID = j["id"].get<std::string>();
        }
    } else {
        ID = "";
    }
}

void User::saveUsers() {
    // Load existing users
    json j;
    std::ifstream inFile(filePath);
    if (inFile.is_open()) inFile >> j;
    inFile.close();

    // Append or rewrite
    j.clear();
    for (const auto& userPtr : userList) {
        if (userPtr) j.push_back(userPtr->toJson());
    }

    std::ofstream outFile(filePath, std::ios::trunc);
    outFile << std::setw(4) << j;
    outFile.close();
}

void User::loadUsers() {
    userList.clear();
    json j;
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) return;

    inFile >> j;
    inFile.close();

    for (auto& item : j) {
        auto user = std::make_shared<User>();
        user->fromJson(item);
        userList.push_back(user);
    }
}


// =====================================================================
//                        User Activity Logs
// =====================================================================

void User::generateUserActivityReport() {
    std::cout << "\n--- User Activity Report ---\n";

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "No user activity logs found.\n";
        return;
    }

    json j;
    file >> j;

    int i = 1;
    for (auto& item : j) {
        std::cout << i++ << ". Username: " << item.value("username", "")
                  << " | Role: " << item.value("role", "")
                  << " | ID: " << item.value("id", "") << "\n";
    }
}

void User::logActivity(const std::string& userID, const std::string& action) {
    activityLogs.push_back({userID, action});
}

void User::showUserActivityReport() {
    std::cout << "\n--- User Activity Report ---\n";

    if (activityLogs.empty()) {
        std::cout << "No user activity logs found.\n";
        return;
    }

    for (size_t i = 0; i < activityLogs.size(); ++i) {
        std::cout << i + 1 << ". UserID: " << activityLogs[i].first
                  << " | Action: " << activityLogs[i].second << "\n";
    }
}
