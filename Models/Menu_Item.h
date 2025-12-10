#ifndef Menu_Item_h
#define Menu_Item_h

#include<bits/stdc++.h>
using namespace std;

class Menu_Item {
private:
    int item_id;
    string name;
    string description;
    double price;

public:
    Menu_Item(int id,  string item_name,  string item_description, double item_price)
        : item_id(id), name(item_name), description(item_description), price(item_price) {}

    int getItemId()  {
        return item_id;
    }

    string getName()  {
        return name;
    }

    string getDescription()  {
        return description;
    }

    double getPrice()  {
        return price;
    }
};

#endif // Menu_Item_h