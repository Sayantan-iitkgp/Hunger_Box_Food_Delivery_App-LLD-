#ifndef CART_H
#define CART_H

#include <bits/stdc++.h>
using namespace std;
#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id, quantity

class Cart
{
private:
    int user_id; // tuple<Location_id, hotel_id, item_id, quantity>
    set<order_key> Cart_Set;

public:
    Cart(int uid) : user_id(uid) {}
    int getUserId() const
    {
        return user_id;
    }

    void addToCart(int location_id, int hotel_id, int item_id, int quantity)
    {
        order_key item = make_tuple(location_id, hotel_id, item_id, quantity);
        Cart_Set.insert(item);
    }

    const set<order_key> &get_Cart_List() const
    {
        return Cart_Set;
    }

    void remove_From_Cart(int location_id, int hotel_id, int item_id, int quantity)
    {
        order_key item = make_tuple(location_id, hotel_id, item_id, quantity);
        auto it = Cart_Set.find(item);
        if (it != Cart_Set.end())
        {
            Cart_Set.erase(it);
        }
    }

    void change_quantity(int location_id, int hotel_id, int item_id, int old_quantity, int new_quantity)
    {
        order_key old_item = make_tuple(location_id, hotel_id, item_id, old_quantity);
        auto it = Cart_Set.find(old_item);
        if (it != Cart_Set.end())
        {
            Cart_Set.erase(it);
            order_key new_item = make_tuple(location_id, hotel_id, item_id, new_quantity);
            Cart_Set.insert(new_item);
        }
    }
};

#endif // CART_HART_H