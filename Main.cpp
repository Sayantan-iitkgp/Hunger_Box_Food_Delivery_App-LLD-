#include<bits/stdc++.h>
#include "HungerBox.h"
#include "Models/User.h"
using namespace std;
#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id, quantity

int main(){
    HungerBox* hungerBox = new HungerBox();
    hungerBox->Build_run_system();

    // Create Users and register with Notification Service
    User* user1 = hungerBox->Create_User("Alice");
    User* user2 = hungerBox->Create_User("Bob");

    //show hotels by location
    hungerBox->Search_Hotels_By_Location(1);
    hungerBox->Search_Hotels_By_Location(2);

    // Show Hotel Menus
    hungerBox->Show_Hotel_Menu(1, 0); // Pizza Place
    hungerBox->Show_Hotel_Menu(1, 1); // Burger Joint
    hungerBox->Show_Hotel_Menu(2, 0); // Sushi Spot
    
    // Add items to User1's Cart
    user1->getCart().addToCart(1, 0, 0, 2); // 2 Margherita Pizzas from Pizza Place
    user1->getCart().addToCart(1, 1, 2, 1); // 1 Fries from Burger Joint
    user1->getCart().addToCart(2, 0, 1, 3); // 3 Spicy Tuna Rolls from Sushi Spot

    //Add items to User2's Cart
    user2->getCart().addToCart(1, 0, 1, 1); // 1 Pepperoni Pizza from Pizza Place
    user2->getCart().addToCart(2, 0, 0, 2); // 2 California Rolls from Sushi Spot
    user2->getCart().addToCart(2, 0, 2, 1); // 1 Miso Soup from Sushi Spot

    // Show User1's Cart Items
    hungerBox->Show_User_Cart_Items(user1);

    //Change quantity of an item in User2's Cart
    hungerBox->Change_Item_Quantity_In_Cart(user2, 2, 0, 0, 2, 4); // Change California Rolls quantity from 2 to 3

    // Show User2's Cart Items
    hungerBox->Show_User_Cart_Items(user2);

    // Place Order for User1
    vector<order_key> user1_items(user1->getCartItems().begin(), user1->getCartItems().end());
    hungerBox->Place_Order(user1, "Home Delivery", "Net Banking", user1_items);

    //remove an item from User2's Cart
    hungerBox->Remove_Items_From_Cart(user2, 1, 0, 1, 1); // Remove Pepperoni Pizza from Burger Joint

    // Place Order for User2
    vector<order_key> user2_items(user2->getCartItems().begin(), user2->getCartItems().end());
    hungerBox->Place_Order(user2, "Pick Up", "Cash On Delivery", user2_items);

    // Show User1's Order History
    hungerBox->Show_User_Order_History(user1);
    // Show User2's Order History
    hungerBox->Show_User_Order_History(user2);

    // Display Notifications for User1
    hungerBox->Display_User_Notifications(user1);
    // Display Notifications for User2
    hungerBox->Display_User_Notifications(user2);

    //show cart items after order placement
    hungerBox->Show_User_Cart_Items(user1);
    hungerBox->Show_User_Cart_Items(user2);

    // Delete Users
    hungerBox->Delete_User(user1);
    hungerBox->Delete_User(user2);

    return 0;
}