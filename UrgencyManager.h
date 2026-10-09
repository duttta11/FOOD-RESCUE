#ifndef URGENCY_MANAGER_H
#define URGENCY_MANAGER_H

#include <iostream>
#include <string>
#include "DONOR.h"
#include "PriorityQueue.h"

using namespace std;

class UrgencyManager
{
private:


    int calculatePriority(string expiryDate)
    {
        int choice;

        cout << "\nFood expiry date: " << expiryDate << endl;

        cout << "Select urgency:\n";
        cout << "1. Expires very soon\n";
        cout << "2. Expires soon\n";
        cout << "3. Expires later\n";
        cout << "Enter priority: ";

        cin >> choice;

        if (choice < 1 || choice > 3)
        {
            cout << "Invalid priority. Setting priority 3.\n";
            choice = 3;
        }

        return choice;
    }

public:

    
    void addFoodToUrgentQueue(
        FoodDonation& donation,
        UrgentFoodQueue& queue)
    {
        if (!donation.available)
        {
            cout << "Food is not available.\n";
            return;
        }

        int priority = calculatePriority(donation.expiryDate);

        queue.enqueue(
            donation.id,
            donation.foodName,
            donation.quantity,
            priority
        );

        cout << "Food successfully added to urgent queue.\n";
    }
};

#endif