#ifndef Order_Factory_h
#define Order_Factory_h
#include <bits/stdc++.h>
#include "../Models/Ipayment.h"
#include "../Payment_Strategy/Cash_On_Delivery.h"
#include "../Payment_Strategy/Net_Banking.h"
#include "../Payment_Strategy/UPI.h"
#include "../Models/IOrder.h"
#include "../Order_Strategy/Home_Delivery.h"
#include "../Order_Strategy/Pick_Up.h"
using namespace std;
#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id,quantity

// Factory Class for creating Payment Strategy objects & Order Strategy objects

// It should be singleton class
class OrderPaymentFactory
{
private:
    static OrderPaymentFactory *instance;
    static mutex mtx; // Mutex for thread safety

    OrderPaymentFactory()
    {
        // Private constructor to prevent instantiation
        cout << "Order_Payment_Factory Instance Created only once" << endl;
    }

public:
    // Get the singleton instance of OrderPaymentFactory
    static OrderPaymentFactory *getInstance()
    {
        if (instance == nullptr)
        {
            unique_lock<mutex> lock(mtx); // Ensure thread safety
            if (instance == nullptr)
            {
                instance = new OrderPaymentFactory();
            }
        }
        return instance;
    }

    // Factory Method to create proper order according to order type & payment type
    IOrder *createOrder(const string &order_type, const string &payment_type, int user_id, int order_id, const vector<order_key> &items)
    {
        Ipayment *payment_strategy = nullptr;

        if (payment_type == "UPI")
        {
            payment_strategy = new UPI(order_id, 0.0, user_id, "UPI");
        }
        else if (payment_type == "Net Banking")
        {
            payment_strategy = new NetBanking(order_id, 0.0, user_id, "Net Banking");
        }
        else if (payment_type == "Cash On Delivery")
        {
            payment_strategy = new CashOnDelivery(order_id, 0.0, user_id, "Cash On Delivery");
        }
        else
        {
            cout << "Invalid Payment Type" << endl;
            return nullptr;
        }

        IOrder *order = nullptr;
        if (order_type == "Home Delivery")
        {
            order = new HomeDelivery(user_id, order_id, payment_strategy, "Home Delivery");
        }
        else if (order_type == "Pick Up")
        {
            order = new PickUp(user_id, order_id, payment_strategy, "Pick Up");
        }
        else
        {
            cout << "Invalid Order Type" << endl; 
            return nullptr;
        }

        // Add items to the order
        for (const auto &item : items)
        {
            int location_id = get<0>(item);
            int hotel_id = get<1>(item);
            int item_id = get<2>(item);
            int quantity = get<3>(item);
            order->add_Item(location_id, hotel_id, item_id, quantity);
        }

        return order;
    }
};

OrderPaymentFactory *OrderPaymentFactory::instance = nullptr;
mutex OrderPaymentFactory::mtx;

#endif // Order_Factory_h