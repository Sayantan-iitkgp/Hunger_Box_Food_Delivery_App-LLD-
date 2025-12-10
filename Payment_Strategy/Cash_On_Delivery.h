#ifndef Cash_On_Delivery_h
#define Cash_On_Delivery_h
#include <bits/stdc++.h>
#include "../Models/Ipayment.h"
using namespace std;

// Concrete Strategy for Cash On Delivery Payment
class CashOnDelivery : public Ipayment
{
public:
    CashOnDelivery(int p_id, double amt, int u_id,string p_type)
        : Ipayment(p_id, amt, u_id, p_type) {}

    void processPayment() override {
        cout << "Processing Cash On Delivery Payment for Payment ID: " << getPaymentId()
             << ", Amount: " << getAmount() << ", User ID: " << getUserId() << endl;

        // payment processing logic
        double amount = getAmount() + 5.0; // Adding COD fee of $5.0
        cout << "Total Amount to be paid on delivery (including COD fee): " << amount << endl;
        
        bool payment_status = true; // Assume payment is always successful for COD

         //Order id can be fetched from payment id because we are using same id for both payment & order.
        notify_user(getUserId(), getPaymentId(), payment_status);
    }
};

#endif // Cash_On_Delivery_h