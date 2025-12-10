#ifndef Upi_h
#define Upi_h
#include <bits/stdc++.h>
#include "../Models/Ipayment.h"
using namespace std;

// Concrete Strategy for UPI Payment
class UPI : public Ipayment
{
public:
    UPI(int p_id, double amt, int u_id, string p_type)
        : Ipayment(p_id, amt, u_id, p_type) {}

    void processPayment() override
    {
        cout << "Processing UPI Payment for Payment ID: " << getPaymentId()
             << ", Amount: " << getAmount() << ", User ID: " << getUserId() << endl;

        // payment processing logic
        double amount = getAmount(); // No additional fees for UPI
        cout << "Total Amount to be paid via UPI: " << amount << endl;

        bool payment_status = true; // Assume payment is always successful for UPI

         //Order id can be fetched from payment id because we are using same id for both payment & order.
        notify_user(getUserId(), getPaymentId(), payment_status);
    }
};
#endif // Upi_h