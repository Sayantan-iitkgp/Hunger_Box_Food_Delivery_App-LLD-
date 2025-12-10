#ifndef Notification_Box_h
#define Notification_Box_h
#include <bits/stdc++.h>
using namespace std;

// Notification Box Class to store and display notifications for a user
class NotificationBox
{
private:
    int user_id;
    vector<string> notifications;

public:
    NotificationBox(int u_id) : user_id(u_id) {}

    // Add notification to the box
    void addNotification(string notification)
    {
        notifications.push_back(notification);
    }

    // Display all notifications
    void displayNotifications()
    {
        if (notifications.empty())
        {
            cout << "No notifications for User ID: " << user_id << endl;
            return;
        }
        cout << "Notifications for User ID: " << user_id << endl;
        for (auto note : notifications)
        {
            cout << "- " << note << endl;
        }
    }

    //get the number of notifications
    int getNotificationCount() const
    {
        return notifications.size();
    }
};

#endif // Notification_Box_h