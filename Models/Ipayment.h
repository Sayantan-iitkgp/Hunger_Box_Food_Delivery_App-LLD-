#ifndef Ipayment_h
#define Ipayment_h

#include <bits/stdc++.h>
#include "Menu_Item.h"
#include "../Service/Notification_Service.h"
using namespace std;

// Abstract Payment Interface
class Ipayment
{
private:
    int payment_id;
    double amount = 0.0;
    int user_id;
    string payment_type;

public:
    Ipayment(int p_id, double amt, int u_id, string p_type)
        : payment_id(p_id), amount(amt), user_id(u_id), payment_type(p_type) {}

    virtual void processPayment() = 0; // Pure virtual function

    int getPaymentId() 
    {
        return payment_id;
    }

    string getPaymentType() 
    {
        return payment_type;
    }

    double getAmount() 
    {
        return amount;
    }

    int getUserId() 
    {
        return user_id;
    }

    void set_final_amount(double amt)
    {
        amount += amt;
    }

    // Order id can be fetched from payment id because we are using same id for both payment & order.
    void notify_user(int user_id, int order_id, bool payment_status)
    {
        NotificationService *Notification_service = NotificationService::getInstance();
        Notification_service->sendNotification(user_id, order_id, payment_status);
    }
};

#endif // Ipayment_h