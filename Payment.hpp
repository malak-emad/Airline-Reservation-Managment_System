#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include "JsonPersistence.hpp"
#include <iostream>

using json = nlohmann::json;

class Payment : public JsonPersistence<Payment>{
private:
    std::string paymentID;
    std::string passengerID;
    std::string flightNumber;
    std::string seatNumber;
    std::string method;
    double amount;
    bool status;

    static std::string paymentPath;


public:
    Payment(std::string method = "", double amount = 0.0)
        : method(method), amount(amount), status(false) {}

    // --- JSON conversion ---
    json toJson() const override;

    void fromJson(const json& j) override;

    // --- Payment Processing & Persistence ---
    bool processPayment(const std::string& pID, const std::string& fNumber, const std::string& seat);

    static std::vector<std::shared_ptr<Payment>> paymentList;

    void savePayment();

    static void loadPayments();
    static void printAllPayments();
    bool operator==(const Payment& other) const;
    double getAmount() const { return amount; }
    std::string getMethod() const { return method; }

};

#endif