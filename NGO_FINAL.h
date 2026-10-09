#ifndef NGO_REQUIREMENT_H
#define NGO_REQUIREMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

inline int ngoGetIntInput(const string &prompt)
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

inline string ngoGetStringInput(const string &prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

class NGO
{
private:
    int ngoID;
    string name;
    string email;
    string password;
    string location;
    int capacity;
    bool loggedIn;

public:
    NGO()
        : ngoID(0), name(""), email(""), password(""), location(""),
          capacity(0), loggedIn(false) {}

    NGO(int id, const string &n, const string &e, const string &pw,
        const string &loc, int cap)
        : ngoID(id), name(n), email(e), password(pw), location(loc),
          capacity(cap), loggedIn(false) {}

    void setCapacity(int cap)           { capacity = cap; }
    void setLocation(const string &loc) { location = loc; }
    void setLoggedIn(bool status)       { loggedIn = status; }

    int getNgoID() const         { return ngoID; }
    string getName() const       { return name; }
    string getEmail() const      { return email; }
    string getLocation() const   { return location; }
    int getCapacity() const      { return capacity; }
    bool isLoggedIn() const      { return loggedIn; }

    bool checkPassword(const string &pw) const { return password == pw; }

    void reduceCapacity(int qty) { capacity = max(0, capacity - qty); }

    void displayNGO() const
    {
        cout << "\n-----------------------------";
        cout << "\nNGO ID       : " << ngoID;
        cout << "\nName         : " << name;
        cout << "\nEmail        : " << email;
        cout << "\nLocation     : " << location;
        cout << "\nCapacity     : " << capacity;
        cout << "\nStatus       : " << (loggedIn ? "Logged In" : "Logged Out");
        cout << "\n-----------------------------\n";
    }
};

class Requirement
{
public:
    enum Status
    {
        PENDING,
        FULFILLED
    };

private:
    int requirementID;
    int ngoID;
    string foodType;
    int quantityNeeded;
    int urgency;
    Status reqStatus;

public:
    Requirement()
        : requirementID(0), ngoID(0), foodType(""), quantityNeeded(0),
          urgency(0), reqStatus(PENDING) {}

    Requirement(int rID, int nID, const string &food, int qty, int urg)
        : requirementID(rID), ngoID(nID), foodType(food),
          quantityNeeded(qty), urgency(urg), reqStatus(PENDING) {}

    void reduceQuantity(int qty)
    {
        quantityNeeded = max(0, quantityNeeded - qty);
        if (quantityNeeded == 0)
            reqStatus = FULFILLED;
    }
    void markFulfilled() { reqStatus = FULFILLED; }

    int getRequirementID() const  { return requirementID; }
    int getNgoID() const          { return ngoID; }
    string getFoodType() const    { return foodType; }
    int getQuantityNeeded() const { return quantityNeeded; }
    int getUrgency() const        { return urgency; }
    Status getStatusCode() const  { return reqStatus; }

    string getStatus() const
    {
        return (reqStatus == FULFILLED) ? "Fulfilled" : "Pending";
    }

    void displayRequirement() const
    {
        cout << "\n================================";
        cout << "\nRequirement ID    : " << requirementID;
        cout << "\nNGO ID            : " << ngoID;
        cout << "\nFood Type         : " << foodType;
        cout << "\nQuantity Needed   : " << quantityNeeded;
        cout << "\nUrgency (1-5)     : " << urgency;
        cout << "\nStatus            : " << getStatus();
        cout << "\n================================\n";
    }
};

class NGODonation
{
private:
    int donationID;
    string foodType;
    int quantity;
    bool matched;

public:
    NGODonation()
        : donationID(0), foodType(""), quantity(0), matched(false) {}

    NGODonation(int id, const string &food, int qty)
        : donationID(id), foodType(food), quantity(qty), matched(false) {}

    int getDonationID() const  { return donationID; }
    string getFoodType() const { return foodType; }
    int getQuantity() const    { return quantity; }
    bool isMatched() const     { return matched; }

    void reduceQuantity(int qty)
    {
        quantity = max(0, quantity - qty);
        if (quantity == 0)
            matched = true;
    }

    void displayDonation() const
    {
        cout << "\n-----------------------------";
        cout << "\nDonation ID  : " << donationID;
        cout << "\nFood Type    : " << foodType;
        cout << "\nQuantity     : " << quantity;
        cout << "\nStatus       : " << (matched ? "Matched/Closed" : "Available");
        cout << "\n-----------------------------\n";
    }
};

class NGOManager
{
private:
    vector<NGO> ngos;
    int nextID;

public:
    NGOManager() : nextID(301) {}

    int registerNGO(const string &name, const string &email,
                    const string &password, const string &location, int capacity)
    {
        int id = nextID++;
        ngos.push_back(NGO(id, name, email, password, location, capacity));
        return id;
    }

    NGO *findByID(int id)
    {
        for (auto &n : ngos)
            if (n.getNgoID() == id)
                return &n;
        return nullptr;
    }

    NGO *login(const string &email, const string &password)
    {
        for (auto &n : ngos)
        {
            if (n.getEmail() == email && n.checkPassword(password))
            {
                n.setLoggedIn(true);
                return &n;
            }
        }
        return nullptr;
    }

    void displayAll() const
    {
        if (ngos.empty())
        {
            cout << "\nNo NGOs registered yet.\n";
            return;
        }
        for (const auto &n : ngos)
            n.displayNGO();
    }

    bool isEmpty() const { return ngos.empty(); }
};

class RequirementManager
{
private:
    queue<Requirement> pendingQueue;
    vector<Requirement> fulfilledLog;
    int nextID;

public:
    RequirementManager() : nextID(701) {}

    int addRequirement(int ngoID, const string &foodType, int qty, int urgency)
    {
        int id = nextID++;
        pendingQueue.push(Requirement(id, ngoID, foodType, qty, urgency));
        return id;
    }

    bool isEmpty() const { return pendingQueue.empty(); }

    void displayPending()
    {
        if (pendingQueue.empty())
        {
            cout << "\nNo pending food requirements.\n";
            return;
        }
        queue<Requirement> temp = pendingQueue;
        while (!temp.empty())
        {
            temp.front().displayRequirement();
            temp.pop();
        }
    }

    void displayFulfilled() const
    {
        if (fulfilledLog.empty())
        {
            cout << "\nNo fulfilled requirements yet.\n";
            return;
        }
        for (const auto &r : fulfilledLog)
            r.displayRequirement();
    }

    void matchWithDonations(vector<NGODonation> &donations)
    {
        if (pendingQueue.empty())
        {
            cout << "\nNo pending requirements to match.\n";
            return;
        }

        int matchesMade = 0;
        int rounds = pendingQueue.size();

        for (int i = 0; i < rounds; i++)
        {
            Requirement req = pendingQueue.front();
            pendingQueue.pop();

            for (auto &don : donations)
            {
                if (don.isMatched() || req.getStatusCode() == Requirement::FULFILLED)
                    continue;

                if (don.getFoodType() == req.getFoodType() && don.getQuantity() > 0)
                {
                    int qtyToMatch = min(don.getQuantity(), req.getQuantityNeeded());
                    don.reduceQuantity(qtyToMatch);
                    req.reduceQuantity(qtyToMatch);
                    matchesMade++;

                    cout << "MATCHED -> Requirement " << req.getRequirementID()
                         << " (" << req.getFoodType() << ") with Donation "
                         << don.getDonationID() << ", qty " << qtyToMatch << "\n";
                }
            }

            if (req.getStatusCode() == Requirement::FULFILLED)
                fulfilledLog.push_back(req);
            else
                pendingQueue.push(req);
        }

        cout << (matchesMade > 0
                     ? "\nMatching complete. " + to_string(matchesMade) + " match(es) made.\n"
                     : "\nNo matching donations found this round.\n");
    }
};

class DonationManager
{
private:
   vector<NGODonation> donations;
    int nextID;

public:
    DonationManager() : nextID(401) {}

    int addDonation(const string &foodType, int qty)
    {
        int id = nextID++;
        donations.push_back(NGODonation(id, foodType, qty));
        return id;
    }

    void displayAll() const
    {
        if (donations.empty())
        {
            cout << "\nNo donations available.\n";
            return;
        }
        for (const auto &d : donations)
            d.displayDonation();
    }

    vector<NGODonation> &getAll() { return donations; }
    bool isEmpty() const { return donations.empty(); }
};

inline void ngoPrintMenu()
{
    cout << "\n========== NGO & REQUIREMENT MODULE ==========\n";
    cout << "1. Register NGO\n";
    cout << "2. NGO Login\n";
    cout << "3. View All NGOs\n";
    cout << "4. Add Food Requirement\n";
    cout << "5. View Pending Requirements\n";
    cout << "6. Add Available Donation (for matching demo)\n";
    cout << "7. View Available Donations\n";
    cout << "8. Match Donations with Requirements\n";
    cout << "9. View Fulfilled Requirements\n";
    cout << "10. Exit\n";
    cout << "================================================\n";
}

inline void runNGOModule()
{
    NGOManager ngoManager;
    RequirementManager requirementManager;
    DonationManager donationManager;

    int choice;

    do
    {
        ngoPrintMenu();
        choice = ngoGetIntInput("Enter your choice: ");

        switch (choice)
        {
            case 1:
            {
                string name = ngoGetStringInput("Enter NGO name: ");
                string email = ngoGetStringInput("Enter email: ");
                string password = ngoGetStringInput("Enter password: ");
                string location = ngoGetStringInput("Enter location: ");
                int capacity = ngoGetIntInput("Enter capacity (meals): ");

                int id = ngoManager.registerNGO(name, email, password, location, capacity);
                cout << "NGO registered successfully with ID: " << id << "\n";
                break;
            }

            case 2:
            {
                string email = ngoGetStringInput("Enter email: ");
                string password = ngoGetStringInput("Enter password: ");

                NGO *ngo = ngoManager.login(email, password);
                if (ngo)
                    cout << "Login successful. Welcome, " << ngo->getName() << "!\n";
                else
                    cout << "Login failed. Invalid email or password.\n";
                break;
            }

            case 3:
                ngoManager.displayAll();
                break;

            case 4:
            {
                if (ngoManager.isEmpty())
                {
                    cout << "Register at least one NGO first.\n";
                    break;
                }

                int ngoID = ngoGetIntInput("Enter NGO ID: ");
                if (!ngoManager.findByID(ngoID))
                {
                    cout << "NGO not found.\n";
                    break;
                }

                string foodType = ngoGetStringInput("Enter food type needed: ");
                int qty = ngoGetIntInput("Enter quantity needed: ");
                int urgency = ngoGetIntInput("Enter urgency (1-5): ");

                int id = requirementManager.addRequirement(ngoID, foodType, qty, urgency);
                cout << "Requirement added successfully with ID: " << id << "\n";
                break;
            }

            case 5:
                requirementManager.displayPending();
                break;

            case 6:
            {
                string foodType = ngoGetStringInput("Enter food type donated: ");
                int qty = ngoGetIntInput("Enter quantity: ");

                int id = donationManager.addDonation(foodType, qty);
                cout << "Donation added successfully with ID: " << id << "\n";
                break;
            }

            case 7:
                donationManager.displayAll();
                break;

            case 8:
            {
                if (donationManager.isEmpty() || requirementManager.isEmpty())
                {
                    cout << "Need at least one donation and one requirement first.\n";
                    break;
                }
                requirementManager.matchWithDonations(donationManager.getAll());
                break;
            }

            case 9:
                requirementManager.displayFulfilled();
                break;

            case 10:
                cout << "Exiting system. Thank you!\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }

    } while (choice != 10);
}

#endif
