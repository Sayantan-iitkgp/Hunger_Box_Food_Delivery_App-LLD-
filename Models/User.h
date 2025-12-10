#ifndef User_h
#define User_h
#include <bits/stdc++.h>
using namespace std;
#include "../Models/Cart.h"
#include "../Models/IOrder.h"
#include "../Service/Order_Sevice.h"

#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id, quantity

class User
{
private:
    int user_id;
    string name;
    Cart user_cart;
    // vector<IOrder *> order_history;
    // set<IOrder *> active_orders;
    // vector<string> notifications;

public:
    User(int id, const string &user_name)
        : user_id(id), name(user_name), user_cart(id) {}

    int getUserId() const
    {
        return user_id;
    }

    string getName() const
    {
        return name;
    }

    Cart &getCart()
    {
        return user_cart;
    }

    const Cart &getCart() const
    {
        return user_cart;
    }

    const set<order_key> &getCartItems() const
    {
        return user_cart.get_Cart_List();
    }

    // Convenience wrappers to modify the cart through User
    void addToCart(int location_id, int hotel_id, int item_id, int quantity)
    {
        user_cart.addToCart(location_id, hotel_id, item_id, quantity);
    }

    void removeFromCart(int location_id, int hotel_id, int item_id, int quantity)
    {
        user_cart.remove_From_Cart(location_id, hotel_id, item_id, quantity);
    }

    void changeCartQuantity(int location_id, int hotel_id, int item_id, int old_quantity, int new_quantity)
    {
        user_cart.change_quantity(location_id, hotel_id, item_id, old_quantity, new_quantity);
    }

    // void addOrderToHistory(IOrder *order)
    // {
    //     order_history.push_back(order);
    // }

    // const vector<IOrder *> &getOrderHistory() const
    // {
    //     return order_history;
    // }

    // void addNotification(string notification, int order_id, bool payment_status)
    // {
    //     for (auto &order : active_orders)
    //     {
    //         if (order->getOrderId() == order_id && order->getUserId() == user_id)
    //         {
    //             active_orders.erase(order);
    //             addOrderToHistory(order);
    //             break;
    //         }
    //     }
    //     notifications.push_back(notification);
    // }

    // const vector<string> getNotifications()
    // {
    //     return notifications;
    // }

    // int get_next_order_id()
    // {
    //     return order_history.size();
    // }

    // void make_and_place_order(string order_type, string payment_type, const vector<order_key> &items)
    // {

    //     // Create Order using Factory
    //     OrderPaymentFactory *factory = OrderPaymentFactory::getInstance();
    //     OrderService *order_service = OrderService::getInstance();
    //     IOrder *order = factory->createOrder(order_type, payment_type, user_id, order_service->get_next_order_id(user_id), items);

    //     if (order == nullptr)
    //     {
    //         cout << "Order creation failed." << endl;
    //         return;
    //     }

    //     // Place the order
    //     order_service->addActiveOrder(user_id, order);
    //     order->placeOrder();
    // }
};

#endif // "User_h"