#ifndef Notification_Service_h
#define Notification_Service_h
#include <bits/stdc++.h>
#include "../Models/Notification_Box.h"
using namespace std;

// Singleton Notification Service Class

class NotificationService
{
private:
    vector<NotificationBox *> notification_boxes; // Notification service needs access to users notification boxes to send notifications. So All users should be registered here.
    static NotificationService *instance;
    static mutex mtx; // Mutex for thread safety

    NotificationService()
    {
        // Private constructor to prevent instantiation
        cout << "NotificationService Instance Created only once" << endl;
    }

public:
    // Get the singleton instance of NotificationService
    static NotificationService *getInstance()
    {
        if (instance == nullptr)
        {
            unique_lock<mutex> lock(mtx); // Ensure thread safety
            if (instance == nullptr)
            {
                instance = new NotificationService();
            }
        }
        return instance;
    }

    // Method to send notification to user
    void sendNotification(int user_id, int order_id, bool payment_status)
    {
        string message;
        if (payment_status)
        {
            message = "Payment Successful for User ID: " + to_string(user_id) + ", Order ID: " + to_string(order_id);
        }
        else
        {
            message = "Payment Failed for User ID: " + to_string(user_id) + ", Order ID: " + to_string(order_id);
        }
        // Here we can integrate with actual notification service (like email/SMS)
        cout << "Notification sent to User ID: " << user_id << " - Message: " << message << endl;
        
        // Add notification to user's NotificationBox
        NotificationBox *box = notification_boxes[user_id];
        box->addNotification(message);
    }

    // Insert user's notification_box into the notification service
    void registerUser(int id)
    {
        NotificationBox *box = new NotificationBox(id);
        notification_boxes.push_back(box);
    }

    // Get next user id
    int get_next_user_id()
    {
        return notification_boxes.size();
    }

    // get Notification Box for a user
    void show_NotificationBox(int user_id)
    {
        NotificationBox *box = notification_boxes[user_id];
        box->displayNotifications();
    }

    //get number of notifications for a user
    int get_notification_count(int user_id)
    {
        NotificationBox *box = notification_boxes[user_id];
        return box->getNotificationCount();
    }
};

mutex NotificationService::mtx;
NotificationService *NotificationService::instance = nullptr;
#endif // Notification_Service_h