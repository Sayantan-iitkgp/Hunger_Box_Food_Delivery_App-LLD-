#ifndef Order_box_h
#define Order_box_h
#include <bits/stdc++.h>
using namespace std;
#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id, quantity
#include "../Models/IOrder.h"

class OrderBox
{
private:
    int user_id;
    vector<IOrder *> orders;
    set<IOrder *> active_orders;

public:
    OrderBox(int u_id) : user_id(u_id) {}

    // Add order to the box
    void addOrder(int order_id)
    {
         //find in active orders
        auto it = find_if(active_orders.begin(), active_orders.end(),
                          [order_id](IOrder *order) { return order->getOrderId() == order_id; });
        if (it != active_orders.end())
        {
            IOrder *order = *it;
            orders.push_back(order);
            // set order status to placed
            order->set_order_status(true);
            // remove from active orders
            active_orders.erase(it);
        }
    }

    //Add active order to the box
    void addActiveOrder(IOrder *order)
    {
        active_orders.insert(order);
    }

    // Display all orders of the user
    void show_Orders() const
    {
        if (orders.empty())
        {
            cout << "No orders for User ID: " << user_id << endl;
            return;
        }
        cout << "Orders for User ID: " << user_id << endl;
        for (auto order : orders)
        {
            cout << "Order ID: " << order->getOrderId() << ", Order Type: " << order->get_order_type() << endl;
            if (order->order_status())
            {
                cout << "Order Status: Placed" << endl;
            }
            else
            {
                cout << "Order Status: Not Placed" << endl;
                continue;
            }

            string payment_type = order->get_payment_strategy_type();
            cout << "payment Type: " << payment_type << endl;
            // print order details
            const vector<order_key> &order_details = order->get_order_details();
            for (const auto &item : order_details)
            {
                cout << "  Location ID: " << get<0>(item) << ", Hotel ID: " << get<1>(item) << ", Item ID: " << get<2>(item) << ", Quantity: " << get<3>(item) << endl;
            }
            cout << "------------------------" << endl;
            cout << "All items total amount: " << order->getTotalAmount() << endl;
            cout << "Delivery Fee: " << order->getDeliveryFee() << endl;
            double payment_service_charge = 0.0;
            if (payment_type == "Net Banking")
            {
                payment_service_charge = 2.00; // Flat $2 Net Banking charge
            }
            else if (payment_type == "Cash On Delivery")
            {
                payment_service_charge = 5.0; // Flat $5 COD charge
            }

            cout << "Payment Service Charge: " << payment_service_charge << endl;
            cout << "Final Amount Paid: " << order->getTotalAmount() + order->getDeliveryFee() + payment_service_charge << endl;
        }
    }

    //Next order id for the user
    int get_next_order_id() const
    {
        return orders.size();
    }
};

#endif // Order_box_h