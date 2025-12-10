// All 6 Model classes, 3 Payment strategy classes , 2 Order strategy classes and Factory & Manger & Service classes have been made properly to support the whole Food Delivery LLD design.
//  I have used still now Strategy Pattern for Payment and Order types, Singleton pattern for Notification Service & Hotel_Manager and Factory pattern for creating Orders and Payments based on user choice.
// Now we need to connect all these classes properly in main function to demonstrate the working of the complete system.
// Here is the HungerBox.h file which includes all necessary headers. It will be the Orchestrator file to connect all components together.

#ifndef HUNGERBOX_H
#define HUNGERBOX_H
#include <bits/stdc++.h>
using namespace std;
#include "Models/Hotel.h"
#include "Models/Cart.h"
#include "Models/User.h"
#include "Models/Menu_Item.h"
#include "Models/IOrder.h"
#include "Factory/Order_Payment_Factory.h"
#include "Manager/Hotel_Manger.h"
#include "Service/Notification_Service.h"
#include "Service/Order_Sevice.h"
#define order_key tuple<int, int, int, int> // location_id, hotel_id, item_id, quantity

class HungerBox
{
private:
    NotificationService *notificationService;
    OrderService *orderService;
    HotelManager *hotelManager;
    OrderPaymentFactory *orderPaymentFactory;

public:
    // Constructor to initialize singleton instances
    HungerBox()
    {
        notificationService = NotificationService::getInstance();
        hotelManager = HotelManager::getInstance();
        orderService = OrderService::getInstance();
        orderPaymentFactory = OrderPaymentFactory::getInstance();
    }

    // Function to build and run the HungerBox system
    void Build_run_system()
    {
        // This function can be used to set up initial data or run the system
        cout << "HungerBox System is up and running!" << endl;

        // Adding some hotels for demonstration
        Hotel *hotel1 = new Hotel(hotelManager->getNextHotelId(1), "Pizza Place", 1);
        hotelManager->addHotel(hotel1);
        Hotel *hotel2 = new Hotel(hotelManager->getNextHotelId(1), "Burger Joint", 1);
        hotelManager->addHotel(hotel2);
        Hotel *hotel3 = new Hotel(hotelManager->getNextHotelId(2), "Sushi Spot", 2);
        hotelManager->addHotel(hotel3);

        // Adding Menu Items to Hotels
        hotel1->addMenuItem(new Menu_Item(hotel1->get_next_item_id(), "Margherita Pizza", "Classic cheese and tomato pizza", 8.99));
        hotel1->addMenuItem(new Menu_Item(hotel1->get_next_item_id(), "Pepperoni Pizza", "Pepperoni and cheese pizza", 9.99));
        hotel1->addMenuItem(new Menu_Item(hotel1->get_next_item_id(), "Veggie Pizza", "Pizza with assorted vegetables", 9.49));
        hotel2->addMenuItem(new Menu_Item(hotel2->get_next_item_id(), "Cheeseburger", "Beef patty with cheese", 10.99));
        hotel2->addMenuItem(new Menu_Item(hotel2->get_next_item_id(), "Veggie Burger", "Grilled veggie patty", 9.99));
        hotel2->addMenuItem(new Menu_Item(hotel2->get_next_item_id(), "Fries", "Crispy golden fries", 6.49));
        hotel3->addMenuItem(new Menu_Item(hotel3->get_next_item_id(), "California Roll", "Crab and avocado roll", 12.99));
        hotel3->addMenuItem(new Menu_Item(hotel3->get_next_item_id(), "Spicy Tuna Roll", "Tuna with spicy mayo", 13.49));
        hotel3->addMenuItem(new Menu_Item(hotel3->get_next_item_id(), "Miso Soup", "Traditional miso soup", 10.99));
    }

    // Search Hotels by Location
    void Search_Hotels_By_Location(int location_id)
    {
        vector<Hotel *> hotels = hotelManager->getHotelsByLocation(location_id);
        if (hotels.empty())
        {
            cout << "No hotels found at location ID: " << location_id << endl;
            return;
        }
        cout << "Hotels at Location ID " << location_id << ":" << endl;
        for (auto hotel : hotels)
        {
            cout << "Hotel ID: " << hotel->getHotelId() << ", Name: " << hotel->getName() << endl;
        }
    }

    // Show Hotel Menu
    void Show_Hotel_Menu(int location_id, int hotel_id)
    {
        vector<Menu_Item *> menu_items = hotelManager->getHotelMenu(location_id, hotel_id);
        if (menu_items.empty())
        {
            cout << "No menu items found for Hotel ID: " << hotel_id << " at Location ID: " << location_id << endl;
            return;
        }
        cout << "location ID: " << location_id << ", ";
        cout << "Menu for Hotel ID " << hotel_id << ":" << endl;
        for (auto item : menu_items)
        {
            cout << "Item ID: " << item->getItemId() << ", Name: " << item->getName() << ", Description: " << item->getDescription() << ", Price: $" << item->getPrice() << endl;
        }
    }

    // Create a new User
    User *Create_User(const string &user_name)
    {
        int user_id = notificationService->get_next_user_id();
        User *new_user = new User(user_id, user_name);
        notificationService->registerUser(user_id);
        orderService->registerUser(user_id);
        return new_user;
    }

    // Add items to User's Cart
    void Add_Items_To_Cart(User *user, int location_id, int hotel_id, int item_id, int quantity)
    {
        user->getCart().addToCart(location_id, hotel_id, item_id, quantity);
    }

    // remove items from User's Cart
    void Remove_Items_From_Cart(User *user, int location_id, int hotel_id, int item_id, int quantity)
    {
        user->getCart().remove_From_Cart(location_id, hotel_id, item_id, quantity);
    }

    // Change quantity of items in User's Cart
    void Change_Item_Quantity_In_Cart(User *user, int location_id, int hotel_id, int item_id, int old_quantity, int new_quantity)
    {
        user->getCart().change_quantity(location_id, hotel_id, item_id, old_quantity, new_quantity);
    }

    // Place Order for User
    void Place_Order(User *user, const string &order_type, const string &payment_type, const vector<order_key> &items)
    {
        // Erase items from cart before placing order
        for (auto &item : items)
        {
            int location_id = get<0>(item);
            int hotel_id = get<1>(item);
            int item_id = get<2>(item);
            int quantity = get<3>(item);
            Remove_Items_From_Cart(user, location_id, hotel_id, item_id, quantity);
        }

        // Place the order
        int previous_notification_count = notificationService->get_notification_count(user->getUserId());
        orderService->make_and_place_order(user->getUserId(), order_type, payment_type, items);
        int new_notification_count = notificationService->get_notification_count(user->getUserId());

        if (new_notification_count == (previous_notification_count + 1))
        {
            orderService->addOrder(user->getUserId(), (orderService->get_next_order_id(user->getUserId())));
            cout << "Order placed successfully for User ID: " << user->getUserId() << endl;
        }
        else
        {
            cout << "Order placement failed for User ID: " << user->getUserId() << endl;
        }
    }

    // Show User's Cart Items
    void Show_User_Cart_Items(User *user)
    {
        set<order_key> cart_items = user->getCartItems();
        if (cart_items.empty())
        {
            cout << "Cart is empty for User ID: " << user->getUserId() << endl;
            return;
        }
        cout << "Cart Items for User ID " << user->getUserId() << " (" << user->getName() << "):" << endl;
        for (const auto &item : cart_items)
        {
            cout << "Location ID: " << get<0>(item) << ", Hotel ID: " << get<1>(item) << ", Item ID: " << get<2>(item) << ", Quantity: " << get<3>(item) << endl;
        }
    }

    // Show User's Order History
    void Show_User_Order_History(User *user)
    {
        orderService->showUserOrderHistory(user->getUserId());
    }

    // Display Notifications for User
    void Display_User_Notifications(User *user)
    {
        notificationService->show_NotificationBox(user->getUserId());
    }

    // Delete User
    void Delete_User(User *user)
    {
        // In a real system, we would also need to remove the user from NotificationService and free memory
        delete user;
        cout << "User deleted successfully." << endl;
    }
};

#endif // HUNGERBOX_H