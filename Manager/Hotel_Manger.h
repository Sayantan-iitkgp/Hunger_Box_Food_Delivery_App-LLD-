#ifndef HOTEL_MANAGER_H
#define HOTEL_MANAGER_H
#include <bits/stdc++.h>
#include "../Models/Hotel.h"
#include "../Models/Menu_Item.h"
using namespace std;

// It a Singleton Class

class HotelManager
{
private:
    static HotelManager *instance;
    static mutex mtx;                           // Mutex for thread safety
    map<int, vector<Hotel *>> HotelsByLocation; // Maps location_id to list of hotels

    HotelManager()
    {
        // Private constructor to prevent instantiation
        cout << "HotelManager Instance Created only once" << endl;
    }

public:
// Get the singleton instance of HotelManager
    static HotelManager *getInstance()
    {
        if (instance == nullptr)
        {
            unique_lock<mutex> lock(mtx); // Ensure thread safety
            if (instance == nullptr)
            {
                instance = new HotelManager();
            }
        }
        return instance;
    }

    //Adding New Hotel in the Hotel Manager
    void addHotel(Hotel *hotel)
    {
        HotelsByLocation[hotel->getLocationId()].push_back(hotel);
    }

    //Removing Hotel from the Hotel Manager
    void removeHotel(int location_id, int hotel_id)
    {
        auto &hotels = HotelsByLocation[location_id];
        hotels.erase(
            remove_if(hotels.begin(), hotels.end(),
                      [hotel_id](Hotel *hotel) { return hotel->getHotelId() == hotel_id; }),
            hotels.end());
    }   

    //Get Hotels by Location ID
    vector<Hotel *> getHotelsByLocation(int location_id)
    {
        vector<Hotel *> Empty; // To return if no hotels found
        auto it = HotelsByLocation.find(location_id);
        if (it != HotelsByLocation.end())
        {
            return ((*it).second);
        }
        return Empty;
    }

    //Get Next Hotel ID for a given Location
    int getNextHotelId(int location_id)
    {
        auto hotels = HotelsByLocation[location_id];
        return hotels.size() ; // Simple incrementing ID based on count
    }

    //Get Hotel Menu
    vector<Menu_Item *> getHotelMenu(int location_id, int hotel_id)
    {
        auto hotels = HotelsByLocation[location_id];
        for (auto hotel : hotels)
        {
            if (hotel->getHotelId() == hotel_id)
            {
                return hotel->getMenuItems();
            }
        }
        return {}; // Return empty vector if hotel not found
    }   


};

HotelManager* HotelManager::instance = nullptr;
mutex HotelManager::mtx;

#endif // HOTEL_MANAGER_H