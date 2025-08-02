/**
 * @file User.hpp
 * @brief Defines the User class and user management functionalities.
 *
 * This class represents a system user in the Airline Reservation and Management System.
 * It supports:
 * - User authentication and role management
 * - Adding, updating, and deleting users
 * - Logging and reporting user activity
 */


#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <functional>
#include <memory>

#include "MenuInterface.hpp"
#include "jsonpersistence.hpp"
#include "Dashboard.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

/**
 * @class User
 * @brief Base class for all system users (Admin, BookingAgent, Passenger).
 *
 * Implements core user management and authentication functionalities.
 * Supports JSON-based persistence and activity logging.
 */
class User : public MenuInterface, public JsonPersistence<User>, public DashBoard {
private:
    int choice; ///< Stores menu choice for user interactions
    string username; ///< User's login name
    string password; ///< User's password
    string role; ///< Role of the user (Admin/BookingAgent/Passenger)

    static std::vector<std::shared_ptr<User>> userList; ///< List of all users in the system
    static std::vector<std::pair<std::string,std::string>> activityLogs; ///< Activity logs

    /**
     * @brief Show the menu for the user.
     */
    void showMenu() override;

    /**
     * @brief Handle menu choice and execute the corresponding action.
     */
    void processChoice() override;

protected:
    std::string ID; ///< Unique identifier for the user

public:
    /**
     * @brief Default constructor.
     */
    User() {};

    /**
     * @brief Parameterized constructor for initializing a user.
     * @param u Username
     * @param p Password
     * @param id User ID
     * @param r User role
     */
    User(string u, string p, string id, string r) : username(u), password(p), ID(id), role(r) {};

    /// Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getID() const { return ID; }

    /// Setters
    void setUsername(const std::string& u) { username = u; }
    void setPassword(const std::string& p) { password = p; }
    void setID(const std::string& id) { ID = id; }

    /**
     * @brief Retrieve the static list of users.
     * @return Reference to the vector of users
     */
    static std::vector<std::shared_ptr<User>>& getUserList() { return userList; }

    /**
     * @brief Equality operator for comparing users by ID.
     * @param other Another user
     * @return True if IDs match, otherwise false
     */
    bool operator==(const User& other) const;

    /**
     * @brief Generate a user activity report.
     */
    static void generateUserActivityReport();

    /**
     * @brief Log a user action into the activity log.
     * @param userID ID of the user performing the action
     * @param action Description of the action
     */
    static void logActivity(const std::string& userID, const std::string& action);

    /**
     * @brief Print the in-memory user activity report.
     */
    static void showUserActivityReport();

    /**
     * @brief Check if a given ID belongs to a passenger.
     * @param pID Passenger ID
     * @return True if the user is a passenger
     */
    bool isPassenger(const string& pID);

    /**
     * @brief Display all users in the system.
     */
    void get_allUsers();

    /**
     * @brief Add a new user to the system.
     */
    void setUser();

    /**
     * @brief Save users to the JSON file.
     */
    static void saveUsers();

    /**
     * @brief Load users from the JSON file.
     */
    void loadUsers();

    /**
     * @brief Update an existing user's information.
     * @param id ID of the user to update
     */
    static void updateUser(const std::string& id);

    /**
     * @brief Delete a user by ID.
     * @param id ID of the user to delete
     */
    static void deleteUser(const std::string& id);

    /**
     * @brief Serialize the user to JSON.
     * @return JSON object representing the user
     */
    json toJson() const override;

    /**
     * @brief Deserialize a user from JSON.
     * @param j JSON object containing the user data
     */
    void fromJson(const json& j);

    /**
     * @brief Destructor.
     */
    virtual ~User() = default;
};

#endif
