#include "User.hpp"

// --- Static Members ---
static std::string path = "data/users_log.json"; 
// All users loaded from JSON at startup
std::vector<std::shared_ptr<User>> User::userList = JsonPersistence<User>::loadFromJson("data/users_log.json");
// In-memory log of user activities for the current session
std::vector<std::pair<std::string,std::string>> User::activityLogs;


// ------------------------------------------------------------
// Display the Admin/User Management menu
// ------------------------------------------------------------
void User::showMenu() {
    cout << "1. View Users\n"
         << "2. Add User\n"
         << "3. Update User\n"
         << "4. Delete user\n"
         << "5. Logout\n";
    processChoice();
}

// ------------------------------------------------------------
// Process menu input for user management
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// Display all registered users
// ------------------------------------------------------------
void User::get_allUsers() {
    loadUsers(); // reload from JSON

    if (userList.empty()) {
        cout << "No users available.\n";
        return;
    }

    cout << "--- Users ---\n";
    for (const auto& userPtr : userList) {
        if (!userPtr) continue; // safety check

        cout << "Username: " << userPtr->username << "\n"
             << "User ID: " << userPtr->ID << "\n"
             << "Role: " << userPtr->role << "\n"
             << "-----------------------------\n";
    }
}

// ------------------------------------------------------------
// Add a new user and persist to JSON
// ------------------------------------------------------------
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

    saveUsers(); // persist to JSON
}

// ------------------------------------------------------------
// Update user info (password and role) by ID
// ------------------------------------------------------------
void User::updateUser(const std::string& id) {
    for (auto& userPtr : userList) {
        if (userPtr && userPtr->ID == id) {
            cout << "--- Update User " << id << " ---\n";

            cout << "Enter new password: ";
            cin >> userPtr->password;

            cout << "Enter new role (current: " << userPtr->role << "): ";
            cin >> userPtr->role;

            cout << "User " << id << " updated successfully!\n";

            saveUsers(); // persist changes
            return;
        }
    }
    cout << "No user with ID: " << id << " was found\n";
}

// ------------------------------------------------------------
// Delete user by ID
// ------------------------------------------------------------
void User::deleteUser(const std::string& id) {
    for (auto it = userList.begin(); it != userList.end(); ++it) {
        if (*it && (*it)->ID == id) {
            userList.erase(it);
            cout << "User " << id << " deleted successfully!\n";

            saveUsers(); // persist changes
            return;
        }
    }
    cout << "No User with ID: " << id << " to delete.\n";
}

// ------------------------------------------------------------
// Equality operator (users considered equal if IDs match)
// ------------------------------------------------------------
bool User::operator==(const User& other) const {
    return (ID == other.ID);
}

// ------------------------------------------------------------
// JSON Serialization & Deserialization
// ------------------------------------------------------------
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

    // Handle id as string or int
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

// ------------------------------------------------------------
// Save and Load Users from JSON
// ------------------------------------------------------------
void User::saveUsers() {
    JsonPersistence<User>::saveToJson("data/users_log.json", userList);
}

void User::loadUsers() {
    userList = JsonPersistence<User>::loadFromJson("data/users_log.json");
}

// ------------------------------------------------------------
// Check if a user ID belongs to a passenger
// ------------------------------------------------------------
bool User::isPassenger(const string& pID) {
    for (auto& userPtr : userList) {
        if (userPtr && userPtr->ID == pID) {
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------------
// Generate user activity report from JSON file
// (Static log file report, not in-memory session log)
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// Log a user activity in memory (current session)
// ------------------------------------------------------------
void User::logActivity(const std::string& userID, const std::string& action) {
    activityLogs.push_back({userID, action});
}

// ------------------------------------------------------------
// Show the in-memory session activity log
// ------------------------------------------------------------
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
