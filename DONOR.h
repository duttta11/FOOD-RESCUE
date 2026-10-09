#ifndef FOODRESCUE_H
#define FOODRESCUE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class FoodDonation
{
public:
    int id;
    string foodName;
    int quantity;
    string expiryDate;
    bool available;

    FoodDonation(int i, string name, int q, string date)
    {
        id = i;
        foodName = name;
        quantity = q;
        expiryDate = date;
        available = true;
    }

    void display()
    {
        cout << "\nDonation ID: " << id;
        cout << "\nFood Name: " << foodName;
        cout << "\nQuantity: " << quantity;
        cout << "\nExpiry Date: " << expiryDate;

        if (available)
            cout << "\nStatus: Available";
        else
            cout << "\nStatus: Not Available";

        cout << endl;
    }
};

class Donor
{
public:
    int donorID;
    string name;
    string phone;
    string address;

    vector<FoodDonation> donations;

    Donor(int id, string n, string p, string a)
    {
        donorID = id;
        name = n;
        phone = p;
        address = a;
    }

    void displayDonor()
    {
        cout << "\n----- Donor Details -----";
        cout << "\nDonor ID: " << donorID;
        cout << "\nName: " << name;
        cout << "\nPhone: " << phone;
        cout << "\nAddress: " << address << endl;
    }

    void addDonation()
    {
        int id, quantity;
        string foodName, expiryDate;

        cout << "\nEnter Donation ID: ";
        cin >> id;

        cout << "Enter Food Name: ";
        cin >> foodName;

        cout << "Enter Quantity: ";
        cin >> quantity;

        cout << "Enter Expiry Date: ";
        cin >> expiryDate;

        FoodDonation d(id, foodName, quantity, expiryDate);

        donations.push_back(d);

        cout << "\nDonation added successfully.\n";
    }

    void displayDonations()
    {
        if (donations.empty())
        {
            cout << "\nNo donations available.\n";
            return;
        }

        cout << "\n----- All Donations -----\n";

        for (int i = 0; i < donations.size(); i++)
        {
            donations[i].display();
            cout << "----------------------\n";
        }
    }

    void updateDonation()
    {
        int id;

        cout << "\nEnter Donation ID to update: ";
        cin >> id;

        for (int i = 0; i < donations.size(); i++)
        {
            if (donations[i].id == id)
            {
                cout << "Enter new Food Name: ";
                cin >> donations[i].foodName;

                cout << "Enter new Quantity: ";
                cin >> donations[i].quantity;

                cout << "Enter new Expiry Date: ";
                cin >> donations[i].expiryDate;

                if (donations[i].quantity > 0)
                    donations[i].available = true;
                else
                    donations[i].available = false;

                cout << "\nDonation updated successfully.\n";
                return;
            }
        }

        cout << "\nDonation not found.\n";
    }

    void deleteDonation()
    {
        int id;

        cout << "\nEnter Donation ID to delete: ";
        cin >> id;

        for (int i = 0; i < donations.size(); i++)
        {
            if (donations[i].id == id)
            {
                donations[i].available = false;
                donations[i].quantity = 0;

                cout << "\nDonation deleted successfully.\n";
                return;
            }
        }

        cout << "\nDonation not found.\n";
    }

    void checkExpiry()
    {
        if (donations.empty())
        {
            cout << "\nNo donations available.\n";
            return;
        }

        cout << "\n----- Check Food Expiry -----\n";

        for (int i = 0; i < donations.size(); i++)
        {
            cout << "\nDonation ID: " << donations[i].id;
            cout << "\nExpiry Date: " << donations[i].expiryDate;

            int choice;

            cout << "\nIs this food expired? (1 = Yes, 0 = No): ";
            cin >> choice;

            if (choice == 1)
            {
                donations[i].available = false;
                cout << "Food marked as expired.\n";
            }
            else
            {
                donations[i].available = true;
                cout << "Food is still available.\n";
            }
        }
    }

    void showAvailableFood()
    {
        bool found = false;

        cout << "\n----- Available Food -----\n";

        for (int i = 0; i < donations.size(); i++)
        {
            if (donations[i].available == true)
            {
                donations[i].display();
                cout << "----------------------\n";
                found = true;
            }
        }

        if (found == false)
        {
            cout << "No food is available.\n";
        }
    }
};



#endif