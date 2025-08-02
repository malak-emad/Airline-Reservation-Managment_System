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
static std::string path = "data/users_log.json"; ///< Path to the JSON user log file

/// List of all users loaded from JSON at startup
std::vector<std::shared_ptr<User>> User::userList = JsonPersistence<User>::loadFromJson("data/users_log.json");

/// In-memory log of user activities for the current session
std::vector<std::pair<std::string,std::string>> User::activityLogs;


// =====================================================================
//                        Menu Functions
// =====================================================================

/**
 * @brief Display the Admin/User Management menu.
 */
void User::showMenu() {
    cout <<"---Manage Users---\n";
    cout << "1. View Users\n"
         << "2. Add User\n"
         << "3. Update User\n"
         << "4. Delete user\n"
         << "5. Logout\n";
    processChoice();
}

/**
 * @brief Process the user's menu selection and execute the corresponding action.
 */
void User::processChoice() {
    int role;
    string id;

    cout << "Enter choice:\n";
    cin >> role;

    switch(role) {
        case(1):
            cout << "--- All Users ---\n";
            get_allUsers();
            break;

        case(2):
            cout << "--- Add User ---\n";
            setUser();
            break;

        case(3):
            cout << "--- Update User ---\n";
            cout << "Enter User ID\n";
            cin >> id;
            updateUser(id);
            break;

        case(4):
            cout << "--- Delete User ---\n";
            cout << "Enter User ID\n";
            cin >> id;
            deleteUser(id);
            break;

        case(5):
            cout << "--- Logging out ---\n";
            User::logActivity(getID(), "Logged Out");
            return;

        default:
            cerr << "Invalid input\n";
            break;
    }
}


// =====================================================================
//                        User Management
// =====================================================================

/**
 * @brief Display all registered users.
 */
void User::get_allUsers() {
    loadUsers(); // Reload from JSON

    if (userList.empty()) {
        cout << "No users available.\n";
        return;
    }

    for (const auto& userPtr : userList) {
        if (!userPtr) continue; // Safety check

        cout << "Username: " << userPtr->username << "\n"
             << "User ID: " << userPtr->ID << "\n"
             << "Role: " << userPtr->role << "\n"
             << "-----------------------------\n";
    }
}

/**
 * @brief Add a new user and save it to the JSON file.
 */
void User::setUser() {
    int inputID;
    auto newUser = std::make_shared<User>();

    cout << "Enter Username: \n";
    cin >> newUser->username;

    cout << "Enter password: \n";
    cin >> newUser->password;

    cout << "Enter ID: \n";
    cin >> inputID;
    newUser->ID = std::to_string(inputID);

    cout << "Enter Role: \n";
    cin >> newUser->role;

    // Add to list and save
    userList.push_back(newUser);
    cout << "User added successfully!\n";

    saveUsers(); // Persist to JSON
}

/**
 * @brief Update a user's password and role by their ID.
 * @param id ID of the user to update
 */
void User::updateUser(const std::string& id) {
    for (auto& userPtr : userList) {
        if (userPtr && userPtr->ID == id) {

            cout << "Enter new password: ";
            cin >> userPtr->password;

            cout << "Enter new role (current: " << userPtr->role << "): ";
            cin >> userPtr->role;

            cout << "User " << id << " updated successfully!\n";

            saveUsers(); // Persist changes
            return;
        }
    }
    cout << "No user with ID: " << id << " was found\n";
}

/**
 * @brief Delete a user from the system by their ID.
 * @param id ID of the user to delete
 */
void User::deleteUser(const std::string& id) {
    for (auto it = userList.begin(); it != userList.end(); ++it) {
        if (*it && (*it)->ID == id) {
            userList.erase(it);
            cout << "User " << id << " deleted successfully!\n";

            saveUsers(); // Persist changes
            return;
        }
    }
    cout << "No User with ID: " << id << " to delete.\n";
}

/**
 * @brief Equality operator. Users are equal if their IDs match.
 */
bool User::operator==(const User& other) const {
    return (ID == other.ID);
}


// =====================================================================
//                   JSON Serialization / Deserialization
// =====================================================================

/**
 * @brief Convert the user object to a JSON object.
 * @return JSON object representing the user
 */
json User::toJson() const {
    return {
        {"username", username},
        {"password", password},
        {"role", role},
        {"id", ID}
    };
}

/**
 * @brief Load user data from a JSON object.
 * @param j JSON object containing the user data
 */
void User::fromJson(const json& j) {
    username = j.value("username", "");
    password = j.value("password", "");
    role     = j.value("role", "");

    // Handle ID as string or number
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

/**
 * @brief Save all users to the JSON file.
 */
void User::saveUsers() {
    JsonPersistence<User>::saveToJson("data/users_log.json", userList);
}

/**
 * @brief Load all users from the JSON file.
 */
void User::loadUsers() {
    userList = JsonPersistence<User>::loadFromJson("data/users_log.json");
}


// =====================================================================
//                        Utility Functions
// =====================================================================

/**
 * @brief Check if a given user ID belongs to a passenger.
 * @param pID ID to check
 * @return True if the ID belongs to a passenger, false otherwise
 */
bool User::isPassenger(const string& pID) {
    for (auto& userPtr : userList) {
        if (userPtr && userPtr->ID == pID) {
            return true;
        }
    }
    return false;
}


// =====================================================================
//                        User Activity Logs
// =====================================================================

/**
 * @brief Generate a user activity report from the JSON file.
 */
void User::generateUserActivityReport() {
    std::cout << "\n--- User Activity Report ---\n";

    std::ifstream file("data/users_log.json");
    if (!file.is_open()) {
        std::cout << "No user activity logs found.\n";
        return;
    }

    json j;
    file >> j;

    int i = 1;
    for (auto& item : j) {
        std::cout << i++ << ". UserID: " << item.value("userID", "")
                  << " | Action: " << item.value("action", "")
                  << " | Time: " << item.value("time", "") << "\n";
    }
}

/**
 * @brief Log a user activity in the current session (in-memory).
 * @param userID ID of the user
 * @param action Description of the action
 */
void User::logActivity(const std::string& userID, const std::string& action) {
    activityLogs.push_back({userID, action});
}

/**
 * @brief Show the in-memory session user activity report.
 */
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
