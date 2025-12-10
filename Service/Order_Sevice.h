#ifndef Order_Service_h
#define Order_Service_h
#include <bits/stdc++.h>
using namespace std;
#include "../Models/IOrder.h"
#include "../Models/Order_box.h"
#include "../Factory/Order_Payment_Factory.h"

// Singleton Order Service Class
class OrderService
{
private:
    static OrderService *instance;
    static mutex mtx;               // Mutex for thread safety
    vector<OrderBox *> order_boxes; // Order service needs access to users order boxes to store orders. So All users should be registered here.

    OrderService()
    {
        // Private constructor to prevent instantiation
        cout << "OrderService Instance Created only once" << endl;
    }

public:
    // Get the singleton instance of OrderService
    static OrderService *getInstance()
    {
        if (instance == nullptr)
        {
            unique_lock<mutex> lock(mtx); // Ensure thread safety
            if (instance == nullptr)
            {
                instance = new OrderService();
            }
        }
        return instance;
    }

    // Insert user's order_box into the order service
    void registerUser(int id)
    {
        OrderBox *box = new OrderBox(id);
        order_boxes.push_back(box);
    }

    // add order to active orders
    void addActiveOrder(int user_id, IOrder *order)
    {
        OrderBox *box = order_boxes[user_id];
        box->addActiveOrder(order);
    }

    // add order to order history
    void addOrder(int user_id, int order_id)
    {
        OrderBox *box = order_boxes[user_id];
        box->addOrder(order_id);
    }

    // Show user's order history
    void showUserOrderHistory(int user_id)
    {
        OrderBox *box = order_boxes[user_id];
        box->show_Orders();
    }

    // Get next order id for the user
    int get_next_order_id(int user_id)
    {
        OrderBox *box = order_boxes[user_id];
        return box->get_next_order_id();
    }

    // Make and place order function can be added here
    void make_and_place_order(int user_id, string order_type, string payment_type, const vector<order_key> &items)
    {

        // Create Order using Factory
        OrderPaymentFactory *factory = OrderPaymentFactory::getInstance();
        IOrder *order = factory->createOrder(order_type, payment_type, user_id, get_next_order_id(user_id), items);

        if (order == nullptr)
        {
            cout << "Order creation failed." << endl;
            return;
        }

        // Place the order
        addActiveOrder(user_id, order);
        order->placeOrder();
    }
};

OrderService *OrderService::instance = nullptr;
mutex OrderService::mtx;
#endif // Order_Service_h