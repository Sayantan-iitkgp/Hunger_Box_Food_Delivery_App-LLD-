#ifndef IOrder_h
#define IOrder_h
#include <bits/stdc++.h>
#include "Ipayment.h"
#include "../Models/Hotel.h"
#include "../Manager/Hotel_Manger.h"
#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id, quantity

using namespace std;
class IOrder
{
private:
    int user_id;
    int order_id;
    string order_type;          // e.g., "Home Delivery", "Pickup"
    vector<order_key> items;    // list of items in the order
    Ipayment *payment_strategy; // Payment strategy for the order
    double total_amount = 0.0;
    double delivery_fee = 0.0;
    bool active = true;
    bool status = false; // Order status: placed or not

public:
    IOrder(int u_id, int o_id, Ipayment *payment, const string &o_type)
        : user_id(u_id), order_id(o_id), payment_strategy(payment), order_type(o_type) {}

    void add_Item(int location_id, int hotel_id, int item_id, int quantity)
    {
        if (active == false)
        {
            cout << "Cannot add item to inactive order" << endl;
            return;
        }
        items.emplace_back(location_id, hotel_id, item_id, quantity);

        // Fetch item price from HotelManager
        HotelManager *manager = HotelManager::getInstance();
        vector<Hotel *> hotels = manager->getHotelsByLocation(location_id);
        Hotel *target_hotel = hotels[hotel_id]; //  hotel_id is index in vector
        double price = target_hotel->get_item_price(item_id);
        total_amount += (price * quantity);
    }

    void remove_Item(int location_id, int hotel_id, int item_id, int quantity)
    {
        if (active == false)
        {
            cout << "Cannot remove item from inactive order" << endl;
            return;
        }
        items.erase(
            remove_if(items.begin(), items.end(),
                      [location_id, hotel_id, item_id, quantity](const order_key &key)
                      {
                          return key == make_tuple(location_id, hotel_id, item_id, quantity);
                      }),
            items.end());

        // Fetch item price from HotelManager
        HotelManager *manager = HotelManager::getInstance();
        vector<Hotel *> hotels = manager->getHotelsByLocation(location_id);
        Hotel *target_hotel = hotels[hotel_id]; //  hotel_id is index in vector
        double price = target_hotel->get_item_price(item_id);
        total_amount -= (price * quantity);
    }

    void setDeliveryFee(double fee)
    {
        if (active == false)
        {
            cout << "Cannot set delivery fee for inactive order" << endl;
            return;
        }
        delivery_fee = fee;
    }

     string get_order_type() const
    {
        return order_type;
    }

     vector<order_key> get_order_details() const
    {
        return items;
    }

    int getOrderId() const
    {
        return order_id;
    }

    int getUserId() const
    {
        return user_id;
    }

    double getTotalAmount() const
    {
        return total_amount;
    }

    double getDeliveryFee() const
    {
        return delivery_fee;
    }

    void make_payment()
    {
        if (active == false)
        {
            cout << "Cannot make payment for inactive order" << endl;
            return;
        }
        // Update total amount with delivery fee
        double final_amount = total_amount + delivery_fee;
        payment_strategy->set_final_amount(final_amount);
        payment_strategy->processPayment();
    }

    string get_payment_strategy_type() const
    {
        return payment_strategy->getPaymentType();
    }

    void set_order_status(bool stat)
    {
        active = false;
        status = stat;
    }

    bool order_status() const
    {
        return status;
    }

    virtual ~IOrder() = default;

    virtual void placeOrder() = 0; // Pure virtual function
};

#endif // IOrder_h