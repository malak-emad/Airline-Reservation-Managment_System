Here’s a complete **README.md** that you can copy and paste directly:

---

# Airline Reservation and Management System

## Overview

The **Airline Reservation and Management System** is a modern, console-based C++ application that simulates the operations of an airline. It leverages **Object-Oriented Programming (OOP)** principles and **modern C++ features** to manage flights, bookings, users, payments, and reporting. The system supports multiple **user roles**:

* **Administrators** – Manage users, flights, aircraft, and crew assignments.
* **Booking Agents** – Handle flight reservations, seat selections, and payment processing.
* **Passengers** – Search for flights, book tickets, manage profiles, and check in.

Data persistence is achieved via **JSON files** using the `nlohmann/json` library.

---

## Features

### 1. User Roles and Authentication

* Role-based access control for **Admin**, **Booking Agent**, and **Passenger**.
* Secure login and user management (create, update, delete users).
* User activity logging and reporting.

### 2. Flight Management

* Add, update, and delete flights with full details (number, origin, destination, departure, arrival, aircraft).
* Search flights by **date, origin, destination, or price**.
* Aircraft and crew assignment management (future expansion).

### 3. Booking and Reservation System

* Search and view available flights.
* Reserve seats and process **simulated payments**.
* Create, modify, and cancel bookings.
* Automatic **payment recording** in JSON files.

### 4. Passenger Management

* Manage passenger profiles and travel history.
* View all reservations linked to a passenger.
* Future: Loyalty points system for frequent flyers.

### 5. Check-In System

* Simulated online and airport check-in.
* Generate and manage boarding pass data.

### 6. Reporting & Analytics

* User activity logs.
* Flight and booking summaries.
* Payments and reservation history.

### 7. Data Persistence

* JSON-based storage for all modules:

  * Users
  * Flights
  * Reservations
  * Payments
  * User Activity Logs

---

## Project Structure

```
AirlineReservationSystem/
│
├── src/
│   ├── main.cpp
│   ├── User.cpp / User.hpp
│   ├── Passenger.cpp / Passenger.hpp
│   ├── Flight.cpp / Flight.hpp
│   ├── Reservation.cpp / Reservation.hpp
│   ├── Payment.cpp / Payment.hpp
│   ├── MenuInterface.hpp
│   ├── jsonpersistence.hpp
│   └── Dashboard.hpp
│
├── data/
│   ├── users_log.json
│   ├── flights.json
│   ├── reservations.json
│   └── payments.json
│
├── UML_Diagram.png
└── README.md
```

---

## Requirements

* **C++17** or later
* **nlohmann/json** library for JSON handling
* **Filesystem** library for file operations

Install JSON library via vcpkg or include the single-header file:

```bash
vcpkg install nlohmann-json
```

---

## Compilation & Execution

### Using G++

```bash
g++ -std=c++17 src/*.cpp -I./include -o AirlineSystem
./AirlineSystem
```

### Using CMake

Create a simple `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(AirlineReservationSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(AirlineSystem
    src/main.cpp
    src/User.cpp
    src/Passenger.cpp
    src/Flight.cpp
    src/Reservation.cpp
    src/Payment.cpp
)
```

Then:

```bash
mkdir build
cd build
cmake ..
make
./AirlineSystem
```

---

## UML Diagram

<img width="1024" height="1024" alt="UML Diagram of Airline Reservation System" src="https://github.com/user-attachments/assets/4b2fa508-4c0e-49f8-bb3b-88c9c6076e82" />


---

## Future Enhancements

* Implement **loyalty program** with redeemable points.
* Add **seat maps** for interactive seat selection.
* Integrate **email notifications** for booking confirmations.
* Add **multi-threading** for handling concurrent booking agents.
* Migrate to **GUI** using Qt for improved user experience.

---

## Authors

Developed as part of **C++ OOP Project – Airline Reservation and Management System**.

---
