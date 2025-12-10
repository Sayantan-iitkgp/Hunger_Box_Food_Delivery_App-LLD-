#ifndef Hotel_h
#define Hotel_h

#include <bits/stdc++.h>
#include "Menu_Item.h"
using namespace std;

class Hotel
{
private:
    int hotel_id;
    string name;
    int location_id;
    vector<Menu_Item *> menu_items;

public:
    Hotel(int id, string hotel_name, int loc_id)
        : hotel_id(id), name(hotel_name), location_id(loc_id) {}

    int getHotelId()
    {
        return hotel_id;
    }

    string getName()
    {
        return name;
    }

    int getLocationId()
    {
        return location_id;
    }
    void addMenuItem(Menu_Item *item)
    {
        menu_items.push_back(item);
    }

    vector<Menu_Item *> &getMenuItems()
    {
        return menu_items;
    }

    void removeMenuItem(int item_id)
    {
        menu_items.erase(
            remove_if(menu_items.begin(), menu_items.end(),
                      [item_id](Menu_Item *item)
                      { return item->getItemId() == item_id; }),
            menu_items.end());
    }

    double get_item_price(int item_id)
    {
        if (item_id >= 0 && static_cast<size_t>(item_id) < menu_items.size())
        {
            return menu_items[item_id]->getPrice();
        }

        cout << "Item not found in hotel menu.\n";
        return 0.0; // Item not found
    }

    int get_next_item_id()
    {
        return menu_items.size();
    }
};

#endif // Hotel_h
