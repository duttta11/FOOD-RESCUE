#ifndef URGENCY_MANAGER_H
#define URGENCY_MANAGER_H

#include <iostream>
#include <string>
#include <ctime>
#include <set>
#include "DONOR.h"
#include "PriorityQueue.h"
#include "FoodDonationDeliverySystem.h"
#include <unordered_map>
#include <utility>

using namespace std;

class UrgencyManager
{
private:
    set<int> queuedIDs;

    bool parseDate(string date, tm& result)
    {
        if (date.length() != 10 ||
            date[2] != '-' || date[5] != '-')
        {
            return false;
        }

        try
        {
            int day = stoi(date.substr(0, 2));
            int month = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 4));

            if (year < 1900 || month < 1 || month > 12 ||
                day < 1 || day > 31)
            {
                return false;
            }

            result = {};
            result.tm_mday = day;
            result.tm_mon = month - 1;
            result.tm_year = year - 1900;
            result.tm_hour = 12;

            time_t value = mktime(&result);

            if (value == -1)
                return false;

            tm* checked = localtime(&value);

            return checked != nullptr &&
                   checked->tm_mday == day &&
                   checked->tm_mon == month - 1 &&
                   checked->tm_year == year - 1900;
        }
        catch (...)
        {
            return false;
        }
    }


    bool calculatePriority(string expiryDate, int& priority)
    {
        tm expiry = {};

        if (!parseDate(expiryDate, expiry))
        {
            cout << "Invalid expiry date. Use DD-MM-YYYY.\n";
            return false;
        }

        time_t now = time(0);
        tm* current = localtime(&now);

        if (current == nullptr)
            return false;

        tm today = {};
        today.tm_mday = current->tm_mday;
        today.tm_mon = current->tm_mon;
        today.tm_year = current->tm_year;
        today.tm_hour = 12;

        time_t todayTime = mktime(&today);
        time_t expiryTime = mktime(&expiry);

        int daysLeft = static_cast<int>(
            difftime(expiryTime, todayTime) / (60 * 60 * 24)
        );

        if (daysLeft < 0)
        {
            cout << "Expired food cannot be added to the queue.\n";
            return false;
        }
        else if (daysLeft == 0)
            priority = 1;
        else if (daysLeft == 1)
            priority = 2;
        else if (daysLeft <= 3)
            priority = 3;
        else
            priority = 4;

        return true;
    }

public:
    void addFoodToUrgentQueue(
        FoodDonation& donation,
        UrgentFoodQueue& queue)
    {
        if (!donation.available || donation.quantity <= 0)
        {
            cout << "Food is not available.\n";
            return;
        }

        if (queuedIDs.count(donation.id))
        {
            cout << "This donation is already queued or processed.\n";
            return;
        }

        int priority;

        if (!calculatePriority(donation.expiryDate, priority))
            return;

        queue.enqueue(
            donation.id,
            donation.foodName,
            donation.quantity,
            priority
        );

        queuedIDs.insert(donation.id);

        cout << "Automatic priority assigned: "
             << priority << endl;
    }

 
    
void addAllDonationsToQueue(
    Donor& donor,
    UrgentFoodQueue& queue)
{
    int added = 0;

    for (FoodDonation& donation : donor.donations)
    {
        if (!donation.available || donation.quantity <= 0)
            continue;

        if (queuedIDs.count(donation.id))
            continue;

        addFoodToUrgentQueue(donation, queue);

     
        if (queuedIDs.count(donation.id))
            added++;
    }

    cout << "New donations added to queue: "
         << added << endl;
}

  
    void runDonorMenu(Donor& donor, UrgentFoodQueue& queue,
                  DeliveryManager& deliveryManager,
                  VolunteerManager& volunteerManager,
                unordered_map<int, pair<int, int>>& donationIndex,
    int donorPosition)
    {
        int choice;

        do
        {
            cout << "\n===== DONOR & URGENCY MENU =====\n";
            cout << "1. Add food donation\n";
            cout << "2. Display donations\n";
            cout << "3. Add donations to priority queue\n";
            cout << "4. Display priority queue\n";
            cout << "5. Process most urgent food\n";
            cout << "0. Exit menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
{
    donor.addDonation();

    int donationPosition = donor.donations.size() - 1;

    donationIndex[donor.donations[donationPosition].id] =
        {donorPosition, donationPosition};

    break;
}

                case 2:
                    donor.displayDonations();
                    break;

                case 3:
                    addAllDonationsToQueue(donor, queue);
                    break;

                case 4:
                    queue.display();
                    break;

                
case 5:
{
    FoodTask task;

    if (queue.dequeue(task))
    {
        cout << "\nSelected food: "
             << task.foodName << endl;
        cout << "Donation ID: "
             << task.donationID << endl;
        cout << "Priority: "
             << task.priority << endl;

        string destination;

        cout << "Enter NGO delivery location: ";
        cin.ignore(10000, '\n');
        getline(cin, destination);

       
int deliveryID = deliveryManager.addDelivery(
    task.donationID,
    donor.address,
    destination,
    task.priority
);

Volunteer* volunteer = volunteerManager.findAvailable();

if (volunteer != nullptr)
{
    Delivery* delivery = deliveryManager.findByID(deliveryID);

    if (delivery != nullptr)
    {
       delivery->assignVolunteer(volunteer->getVolunteerID());
        volunteer->setAvailability(false);

        cout << "Volunteer assigned successfully!\n";
        cout << "Volunteer is now unavailable.\n";
    }
}
else
{
    cout << "No available volunteer right now.\n";
}

       
        for (FoodDonation& donation : donor.donations)
        {
            if (donation.id == task.donationID)
            {
                donation.available = false;
                break;
            }
        }

        cout << "Delivery request created successfully.\n";
        cout << "View the delivery list to check its status.\n";
    }

    break;
}

                case 0:
                    cout << "Exiting donor urgency menu.\n";
                    break;

                default:
                    cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 0);
    }
};

#endif
