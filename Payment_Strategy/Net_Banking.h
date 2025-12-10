#ifndef Net_Banking_h
#define Net_Banking_h
#include <bits/stdc++.h>
#include "../Models/Ipayment.h"
using namespace std;

// Concrete Strategy for Net Banking Payment
class NetBanking : public Ipayment
{ 
public:
    NetBanking(int p_id, double amt, int u_id,string p_type)
        : Ipayment(p_id, amt, u_id,p_type) {}

    void processPayment() override {
        cout << "Processing Net Banking Payment for Payment ID: " << getPaymentId()
             << ", Amount: " << getAmount() << ", User ID: " << getUserId() << endl;

        // payment processing logic
        double amount = getAmount() + 2.0; // $2 additional fees for Net Banking
        cout << "Total Amount to be paid via Net Banking: " << amount << endl;
        
        bool payment_status = true; // Assume payment is always successful for Net Banking
        
        //Order id can be fetched from payment id because we are using same id for both payment & order.
        notify_user(getUserId(), getPaymentId(), payment_status);
    }
  };
#endif // Net_Banking_h