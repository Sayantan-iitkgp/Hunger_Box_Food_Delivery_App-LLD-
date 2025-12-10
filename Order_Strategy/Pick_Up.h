#ifndef Pick_Up_h
#define Pick_Up_h
#include <bits/stdc++.h>
#include "../Models/Iorder.h"
using namespace std;
// Concrete Order Class for Pick Up

class PickUp : public IOrder
{
public:
    // IMPORTANT NOTE:
    //  If the Parent class(Like Iorder) has no default constructor, and only parameterized constructors,
    //  then we MUST call it explicitly in the derived class constructor.
    PickUp(int u_id, int o_id, Ipayment *payment, string o_type)
        : IOrder(u_id, o_id, payment, o_type) {}

    void placeOrder() override
    {
        cout << "Placing Pick Up Order" << endl;
        // Logic for placing pick up order
        
        double delivery_fee = 0.0; // No delivery fee for pick up
        setDeliveryFee(delivery_fee);

        // After setting delivery fee proceed to make payment
        make_payment();
    }
};

#endif // Pick_Up_h