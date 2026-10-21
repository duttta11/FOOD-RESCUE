#include <iostream>
#include "../include:/DONOR.h"
#include "../include:/FoodDonationDeliverySystem.h"
#include "../include:/NGO_FINAL.h"
#include "../include:/PriorityQueue.h"
#include "../include:/UrgencyManager.h"
using namespace std;

int main()
{
    cout << "=====================================\n";
    cout << "          FOOD RESCUE SYSTEM         \n";
    cout << "=====================================\n";

    // ==========================================
    // TEST 1: DONOR MODULE
    // ==========================================

    Donor donor(101, "Raghav", "9876543210", "Dehradun");

    cout << "\n----- Donor Details -----\n";
    donor.displayDonor();


    // ==========================================
    // TEST 2: VOLUNTEER MODULE
    // ==========================================

    VolunteerManager volunteerManager;

    volunteerManager.addVolunteer(
        "Aman",
        "9876543211",
        "Dehradun"
    );

    cout << "\n----- Registered Volunteers -----\n";
    volunteerManager.displayAll();


    // ==========================================
    // TEST 3: DELIVERY MODULE
    // ==========================================

    DeliveryManager deliveryManager;

    deliveryManager.addDelivery(
        401,
        "Dehradun Food Bank",
        "Local NGO",
        1
    );

    cout << "\n----- Deliveries -----\n";
    deliveryManager.displayAll();


    // ==========================================
    // ASSIGN VOLUNTEER TO DELIVERY
    // ==========================================

    cout << "\n----- Assigning Volunteer -----\n";

    Delivery* delivery = deliveryManager.findByID(501);
    Volunteer* volunteer = volunteerManager.findByID(101);

    if (delivery != nullptr && volunteer != nullptr)
    {
        delivery->assignVolunteer(volunteer->getVolunteerID());

        cout << "Volunteer assigned successfully!\n";
    }


    cout << "\n----- Updated Deliveries -----\n";
    deliveryManager.displayAll();


    // ==========================================
    // TEST 4: NGO MODULE
    // ==========================================

    cout << "\n=====================================\n";
    cout << "           NGO MODULE TEST            \n";
    cout << "=====================================\n";

    NGOManager ngoManager;
    RequirementManager requirementManager;
    DonationManager donationManager;


    // ---------- Register NGO ----------

    cout << "\n----- Registering NGO -----\n";

    ngoManager.registerNGO(
        "Helping Hands",
        "help@ngo.com",
        "1234",
        "Dehradun",
        100
    );


    // ---------- Display NGOs ----------

    cout << "\n----- Registered NGOs -----\n";
    ngoManager.displayAll();


    // ---------- Add Requirement ----------

    cout << "\n----- Adding Food Requirement -----\n";

    requirementManager.addRequirement(
        301,
        "Rice",
        20,
        5
    );


    // ---------- Add Donation ----------

    cout << "\n----- Adding Food Donation -----\n";

    donationManager.addDonation(
        "Rice",
        20
    );


    // ---------- Display Donations ----------

    cout << "\n----- Available Donations -----\n";
    donationManager.displayAll();


    // ---------- Match Donation with Requirement ----------

    cout << "\n----- Matching Donation with Requirement -----\n";

    requirementManager.matchWithDonations(
        donationManager.getAll()
    );


    // ---------- Display Remaining Requirements ----------

    cout << "\n----- Pending Requirements -----\n";

    requirementManager.displayPending();


    // ---------- Display Fulfilled Requirements ----------

    cout << "\n----- Fulfilled Requirements -----\n";

    requirementManager.displayFulfilled();


    cout << "\n=====================================\n";
    cout << "       ALL MODULES TESTED            \n";
    cout << "=====================================\n";

    // TEST 5: PRIORITY QUEUE

cout << "\n----- PRIORITY QUEUE TEST -----\n";

UrgentFoodQueue urgentQueue;

urgentQueue.enqueue(401, "Rice", 20, 3);
urgentQueue.enqueue(402, "Milk", 10, 1);
urgentQueue.enqueue(403, "Bread", 15, 2);

urgentQueue.display();

cout << "\n----- Processing Most Urgent Food -----\n";

FoodTask urgentTask;

if (urgentQueue.dequeue(urgentTask))
{
    cout << "Processing Donation ID: "
         << urgentTask.donationID << endl;

    cout << "Food: " << urgentTask.foodName << endl;
    cout << "Priority: " << urgentTask.priority << endl;
}

cout << "\n----- Queue After Processing -----\n";
urgentQueue.display();
// TEST 6: URGENCY MANAGER

cout << "\n----- URGENCY MANAGER TEST -----\n";

cout << "\n----- ACTUAL DONATIONS PRIORITY TEST -----\n";

Donor testDonor(102, "Rahul", "9876543212", "Dehradun");

// Add three actual donations to the donor
testDonor.donations.push_back(
    FoodDonation(601, "Milk", 10, "11-10-2026"));

testDonor.donations.push_back(
    FoodDonation(602, "Rice", 20, "20-10-2026"));

testDonor.donations.push_back(
    FoodDonation(603, "Bread", 15, "12-10-2026"));

UrgentFoodQueue actualQueue;
UrgencyManager actualUrgencyManager;

// Add every eligible donation automatically
actualUrgencyManager.addAllDonationsToQueue(
    testDonor, actualQueue);

cout << "\n----- FINAL PRIORITY QUEUE -----\n";
actualQueue.display();

cout << "\n----- PROCESSING MOST URGENT FOOD -----\n";

FoodTask task;

if (actualQueue.dequeue(task))
{
    cout << "Food selected: " << task.foodName << endl;
    cout << "Donation ID: " << task.donationID << endl;
    cout << "Priority: " << task.priority << endl;
}cout << "\n===== LIVE DONOR PRIORITY SYSTEM =====\n";

UrgentFoodQueue liveQueue;
UrgencyManager liveUrgencyManager;

liveUrgencyManager.runDonorMenu(
    donor, liveQueue, deliveryManager, volunteerManager
);
cout << "\n===== VERIFYING ALL DELIVERIES =====\n";
deliveryManager.displayAll();

cout << "\n===== VERIFYING ALL VOLUNTEERS =====\n";
volunteerManager.displayAll();
return 0;
}
