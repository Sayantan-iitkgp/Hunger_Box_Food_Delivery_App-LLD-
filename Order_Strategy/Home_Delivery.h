#ifndef Home_Delivery_h
#define Home_Delivery_h
#include <bits/stdc++.h>
#include "../Models/Iorder.h"
using namespace std;

// Concrete Order Class for Home Delivery
class HomeDelivery : public IOrder
{
public:
//IMPORTANT NOTE:
// If the Parent class(Like Iorder) has no default constructor, and only parameterized constructors,
// then we MUST call it explicitly in the derived class constructor.
    HomeDelivery(int u_id, int o_id, Ipayment *payment,string o_type)
        : IOrder(u_id, o_id, payment,o_type) {}

    void placeOrder() override {
        cout << "Placing Home Delivery Order" << endl;
        // Logic for placing home delivery order

        double delivery_fee = 2.0; // Flat delivery fee in $
        setDeliveryFee(delivery_fee);

        //After setting delivery fee proceed to make payment
        make_payment();
    }
};
#endif // Home_Delivery_h