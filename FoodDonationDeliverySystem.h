#ifndef FOOD_DONATION_DELIVERY_SYSTEM_H
#define FOOD_DONATION_DELIVERY_SYSTEM_H


#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// ================= UTILITY: INPUT HELPERS =================
// Keeps main() clean and avoids repeating validation logic

int getIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

string getStringInput(const string &prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}


// ================= VOLUNTEER CLASS =================

class Volunteer
{
private:
    int volunteerID;
    string name;
    string phone;
    string location;
    bool available;

public:
    Volunteer()
        : volunteerID(0), name(""), phone(""), location(""), available(true) {}

    Volunteer(int id, const string &n, const string &p, const string &loc)
        : volunteerID(id), name(n), phone(p), location(loc), available(true) {}

    // Setters
    void setName(const string &n)          { name = n; }
    void setPhone(const string &p)         { phone = p; }
    void setLocation(const string &loc)    { location = loc; }
    void setAvailability(bool status)      { available = status; }

    // Getters (const-correct: these don't modify the object)
    int getVolunteerID() const   { return volunteerID; }
    string getName() const       { return name; }
    string getPhone() const      { return phone; }
    string getLocation() const   { return location; }
    bool isAvailable() const     { return available; }

    void displayVolunteer() const
    {
        cout << "\n-----------------------------";
        cout << "\nVolunteer ID : " << volunteerID;
        cout << "\nName         : " << name;
        cout << "\nPhone        : " << phone;
        cout << "\nLocation     : " << location;
        cout << "\nStatus       : " << (available ? "Available" : "Busy");
        cout << "\n-----------------------------\n";
    }
};


// ================= DELIVERY CLASS =================

class Delivery
{
public:
    enum Status
    {
        PENDING,
        ASSIGNED,
        PICKED_UP,
        IN_TRANSIT,
        DELIVERED,
        CANCELLED
    };

private:
    int deliveryID;
    int donationID;
    int volunteerID;

    string pickupLocation;
    string deliveryLocation;

    Status deliveryStatus;
    int priority;

public:
    Delivery()
        : deliveryID(0), donationID(0), volunteerID(-1),
          pickupLocation(""), deliveryLocation(""),
          deliveryStatus(PENDING), priority(0) {}

    Delivery(int dID, int donID, const string &pickup,
             const string &delivery, int p)
        : deliveryID(dID), donationID(donID), volunteerID(-1),
          pickupLocation(pickup), deliveryLocation(delivery),
          deliveryStatus(PENDING), priority(p) {}

    // Setters
    void setPickupLocation(const string &location)   { pickupLocation = location; }
    void setDeliveryLocation(const string &location) { deliveryLocation = location; }
    void setPriority(int p)                          { priority = p; }

    void assignVolunteer(int id)
    {
        volunteerID = id;
        deliveryStatus = ASSIGNED;
    }

    void updateStatus(Status newStatus) { deliveryStatus = newStatus; }

    // Getters
    int getDeliveryID() const        { return deliveryID; }
    int getDonationID() const        { return donationID; }
    int getVolunteerID() const       { return volunteerID; }
    string getPickupLocation() const { return pickupLocation; }
    string getDeliveryLocation() const { return deliveryLocation; }
    int getPriority() const          { return priority; }
    Status getStatusCode() const     { return deliveryStatus; }

    string getStatus() const
    {
        switch (deliveryStatus)
        {
            case PENDING:     return "Pending";
            case ASSIGNED:    return "Assigned";
            case PICKED_UP:   return "Picked Up";
            case IN_TRANSIT:  return "In Transit";
            case DELIVERED:   return "Delivered";
            case CANCELLED:   return "Cancelled";
            default:          return "Unknown";
        }
    }

    void displayDelivery() const
    {
        cout << "\n================================";
        cout << "\nDelivery ID       : " << deliveryID;
        cout << "\nDonation ID       : " << donationID;
        cout << "\nVolunteer ID      : "
             << (volunteerID == -1 ? "Not Assigned" : to_string(volunteerID));
        cout << "\nPickup Location   : " << pickupLocation;
        cout << "\nDelivery Location : " << deliveryLocation;
        cout << "\nPriority          : " << priority;
        cout << "\nStatus            : " << getStatus();
        cout << "\n================================\n";
    }
};


// ================= VOLUNTEER MANAGER =================
// Owns the collection of volunteers and all operations on it

class VolunteerManager
{
private:
    vector<Volunteer> volunteers;
    int nextID;

public:
    VolunteerManager() : nextID(101) {}

    int addVolunteer(const string &name, const string &phone, const string &location)
    {
        int id = nextID++;
        volunteers.push_back(Volunteer(id, name, phone, location));
        return id;
    }

    Volunteer *findByID(int id)
    {
        for (auto &v : volunteers)
            if (v.getVolunteerID() == id)
                return &v;
        return nullptr;
    }

    // Returns the first available volunteer, or nullptr if none free
    Volunteer *findAvailable()
    {
        for (auto &v : volunteers)
            if (v.isAvailable())
                return &v;
        return nullptr;
    }

    void displayAll() const
    {
        if (volunteers.empty())
        {
            cout << "\nNo volunteers registered yet.\n";
            return;
        }
        for (const auto &v : volunteers)
            v.displayVolunteer();
    }

    bool isEmpty() const { return volunteers.empty(); }
};


// ================= DELIVERY MANAGER =================

class DeliveryManager
{
private:
    vector<Delivery> deliveries;
    int nextID;

public:
    DeliveryManager() : nextID(501) {}

    int addDelivery(int donationID, const string &pickup,
                     const string &drop, int priority)
    {
        int id = nextID++;
        deliveries.push_back(Delivery(id, donationID, pickup, drop, priority));
        return id;
    }

    Delivery *findByID(int id)
    {
        for (auto &d : deliveries)
            if (d.getDeliveryID() == id)
                return &d;
        return nullptr;
    }

    void displayAll() const
    {
        if (deliveries.empty())
        {
            cout << "\nNo deliveries recorded yet.\n";
            return;
        }
        for (const auto &d : deliveries)
            d.displayDelivery();
    }

    bool isEmpty() const { return deliveries.empty(); }
};


// ================= MENU-DRIVEN INTERFACE =================

void printMenu()
{
    cout << "\n========== FOOD DONATION DELIVERY SYSTEM ==========\n";
    cout << "1. Register Volunteer\n";
    cout << "2. View All Volunteers\n";
    cout << "3. Create Delivery Request\n";
    cout << "4. View All Deliveries\n";
    cout << "5. Assign Volunteer to Delivery\n";
    cout << "6. Update Delivery Status\n";
    cout << "7. Exit\n";
    cout << "=====================================================\n";
}

#endif // FOOD_DONATION_DELIVERY_SYSTEM_H
