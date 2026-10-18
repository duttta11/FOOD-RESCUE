Volunteer & Delivery Module
Project: Food Rescue --- Smart Food Rescue and Redistribution
System
PBL Team ID: DSCPP-III-2026-T381
College: Graphic Era (Deemed to be University), Dehradun
About the Module
The Volunteer & Delivery Module is one part of our Food Rescue project.
It helps us keep track of volunteers and deliveries, and connects a
volunteer with a delivery when the required records are available.
The idea is straightforward: once food has been recorded and matched
with an NGO, a volunteer can be assigned to help with the delivery. This
module supports that process by letting us register volunteers, add
delivery records, view the records, and search for them using IDs.
What This Module Does
- Registers volunteers and displays their details.
- Creates delivery records and displays them.
- Searches for volunteers and deliveries by ID.
- Assigns a volunteer to a delivery when both records are found.
- Works with the wider Food Rescue workflow, including the
  donor-priority process.
Tools and Concepts Used
- Language: C++
- Concepts: Classes and objects, member functions, pointers,
  conditional checks, and record lookup.
- Project setup: Header files and a console-based test program.
- Related components: UrgentFoodQueue and UrgencyManager,
  which are used in the priority-processing workflow.
Main Classes
  Class                               What it is used for
  Volunteer                         Stores and provides access to a
                                      volunteer's details.
  VolunteerManager                  Adds volunteers, displays the list,
                                      and searches for a volunteer by ID.
  Delivery                          Represents a delivery and includes
                                      the operation used to assign a
                                      volunteer.
  DeliveryManager                   Adds deliveries, displays them, and
                                  searches for a delivery by ID.
How It Works
1. A volunteer is registered with details such as name, contact number,
   and location.
2. A delivery record is created.
3. The program searches for the volunteer and delivery using their IDs.
4. If both records are found, the volunteer's ID is assigned to the
   delivery.
5. The program displays the delivery records so the change can be
   checked.
6. The delivery manager is also used in the live donor-priority
   workflow.
Simple Workflow
Register Volunteer ──> VolunteerManager ──┐
                                          ├──> Assign Volunteer
Create Delivery ─────> DeliveryManager ───┘
                                                  |
                                                  v
                                        Display Delivery Records
What the Test Program Covers
The test program included with the project demonstrates these
operations:
- Registering and displaying a volunteer.
- Adding and displaying a delivery.
- Searching for a delivery and volunteer by ID.
- Assigning a volunteer if both records are found.
- Displaying the delivery and volunteer records after the workflow.
- Running the urgent-food queue and donor-priority workflow.
The program also tests the NGO and donation components, including adding
a food requirement, adding a donation, and matching the donation with
the requirement.
A Test Issue to Fix
There is an ID mismatch in the current test code. The program creates a
delivery with ID 401, but later searches for ID 501:
deliveryManager.addDelivery(
    401,
    "Dehradun Food Bank",
    "Local NGO",
    1
);

Delivery* delivery = deliveryManager.findByID(501);
Because these IDs are different, the delivery search may fail and the
volunteer assignment may not run. Use the same ID in both places---for
example, search for 401---and run the program again to check the
result.
The code also searches for volunteer ID 101 after registering Aman.
Check which ID the VolunteerManager actually assigns to Aman before
relying on this lookup.
Building and Running
Compile the main program from the project directory, making sure the
header paths match your folder structure.
g++ main.cpp -o food_rescue
./food_rescue
If the project has separate .cpp files, include them in the compile
command too. The include paths in the current code should be checked
against the actual repository folders before compiling.
Testing Checklist
Use this checklist when running the program:
- [ ] Register a volunteer and confirm that the details appear.
- [ ] Add a delivery and confirm that it appears.
- [ ] Search for an existing volunteer ID.
- [ ] Search for an existing delivery ID.
- [ ] Assign a volunteer when both records are found.
- [ ] Check that the updated delivery record shows the assignment.
- [ ] Run the donor-priority workflow and review the displayed
  records.
Only mark a test as successful after checking the program's actual
output.
Current Scope and Possible Improvements
The current test program demonstrates volunteer and delivery records, ID
lookups, the assignment logic, and links to the donor-priority workflow.
The supplied code does not confirm that a complete delivery-status
lifecycle or persistent storage has been implemented, so those features
should not be described as finished unless they exist elsewhere in the
project.
Possible next steps include:
- Adding clear delivery statuses such as PENDING,
  VOLUNTEER_ASSIGNED, PICKED_UP, and DELIVERED.
- Recording the time when a delivery status changes.
- Checking for invalid or duplicate IDs.
- Showing a clear message when a volunteer or delivery cannot be
  found.
- Saving records so they remain available after the program closes.
Team
- Aditya Dutta --- Team Lead
- Utsav Bajoria --- Volunteer & Delivery Module
- Vishwajeet Singh --- NGO & Requirement Module
- Raghav Pandey --- Donor & Food Donation Module
This README describes the Volunteer & Delivery part of our Food Rescue
project. Update it as the module develops and add test results once they
have been verified.
