/**
 * @file main.cpp
 * @brief Entry point for the Airline Reservation and Management System.
 *
 * This file contains the main function, which initializes and runs
 * the dashboard for the Airline Reservation and Management System.
 */

#include <iostream>
#include <string>
#include "Dashboard.hpp"

/**
 * @brief Main entry point of the program.
 *
 * Initializes the DashBoard application and starts its execution loop.
 *
 * @return int Returns 0 on successful execution.
 */
int main(void) {
    DashBoard app;  ///< Main dashboard application object
    app.run();      ///< Start the application

    return 0;
}
