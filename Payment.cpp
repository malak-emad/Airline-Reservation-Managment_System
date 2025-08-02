#include "Payment.hpp"
std::string Payment::paymentPath = "data/payments.json";
std::vector<std::shared_ptr<Payment>> Payment::paymentList =
    JsonPersistence<Payment>::loadFromJson(paymentPath);


json Payment :: toJson() const {
    return {
        {"paymentID", paymentID},
        {"passengerID", passengerID},
        {"flightNumber", flightNumber},
        {"seatNumber", seatNumber},
        {"method", method},
        {"amount", amount},
        {"status", status}
    };
}

void Payment :: fromJson(const json& j) {
    paymentID   = j.value("paymentID", "");
    passengerID = j.value("passengerID", "");
    flightNumber= j.value("flightNumber", "");
    seatNumber  = j.value("seatNumber", "");
    method      = j.value("method", "");
    amount      = j.value("amount", 0.0);
    status      = j.value("status", false);
}

// --- Payment Processing & Persistence ---
bool Payment :: processPayment(const std::string& pID,
                    const std::string& fNumber,
                    const std::string& seat) 
{
    passengerID = pID;
    flightNumber = fNumber;
    seatNumber = seat;

    // Generate unique payment ID
    paymentID = "PAY" + std::to_string(rand() % 10000 + 1000);
    status = true; // Simulated success

    // Save to payment.json
    savePayment();
    return status;
}

void Payment :: savePayment() {
    // Load existing payments
    paymentList = JsonPersistence<Payment>::loadFromJson(paymentPath);

    // Add new payment
    auto newPayment = std::make_shared<Payment>(*this);
    paymentList.push_back(newPayment);

    // Save all payments
    JsonPersistence<Payment>::saveToJson(paymentPath, paymentList);
}

void Payment :: loadPayments() {
    paymentList = JsonPersistence<Payment>::loadFromJson(paymentPath);
}

void Payment::printAllPayments() {
    // Reload payments to ensure we have the latest data
    loadPayments();

    if (paymentList.empty()) {
        std::cout << "No payments found.\n";
        return;
    }

    std::cout << "--- All Payments ---\n";
    int count = 1;
    for (const auto& payment : paymentList) {
        if (!payment) continue;
        std::cout << count++ << ". Payment ID: " << payment->paymentID << "\n"
                  << "   Passenger ID: " << payment->passengerID << "\n"
                  << "   Flight Number: " << payment->flightNumber << "\n"
                  << "   Seat Number: " << payment->seatNumber << "\n"
                  << "   Method: " << payment->method << "\n"
                  << "   Amount: $" << payment->amount << "\n"
                  << "   Status: " << (payment->status ? "Successful" : "Failed") << "\n\n";
    }
}
bool Payment :: operator==(const Payment& other) const {
    return method == other.method && amount == other.amount;
}
