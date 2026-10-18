Food Rescue --- Volunteer & Delivery Module
Project: Smart Food Rescue and Redistribution System
Course: Project-Based Learning (PBL), Phase II
Team ID: DSCPP-III-2026-T381
Institution: Graphic Era (Deemed to be University), Dehradun
1. Module Overview
The Volunteer & Delivery Module manages volunteer records and delivery
records in the Food Rescue system. It supports registering volunteers,
viewing registered volunteers, creating delivery records, viewing
deliveries, looking up records by ID, and assigning a volunteer to a
delivery.
This module connects to the wider workflow after a food donation has
been matched with an NGO. A volunteer can then be associated with the
delivery so the team can coordinate pickup and delivery.
2. Objectives
- Maintain volunteer information.
- Create and display delivery records.
- Find volunteers and deliveries using their IDs.
- Assign a volunteer to a delivery.
- Support coordination between food donation, NGO matching, and
  delivery operations.
3. Technology
- Language: C++
- Programming concepts: Classes, objects, member functions,
  pointers, and conditional checks
- Project structure: Header files and a console-based test program
- Related data-structure concepts: Record lookup and
  delivery/priority queue integration where used by the project
4. Main Classes
  Class                               Responsibility
  Volunteer                         Represents an individual volunteer
                                      and provides volunteer-related
                                      information/operations.
  VolunteerManager                  Registers volunteers, displays
                                      volunteer records, and looks up a
                                      volunteer by ID.
  Delivery                          Represents a delivery record and
                                      supports assigning a volunteer.
  DeliveryManager                   Adds deliveries, displays delivery
                                      records, and looks up a delivery by
                                  ID.
The test program also interacts with the UrgentFoodQueue and
UrgencyManager components to demonstrate food-priority processing and
the donor priority workflow.
5. Functionality Demonstrated in the Test Program
Volunteer management
- Creates a VolunteerManager.
- Registers a volunteer with a name, contact number, and location.
- Displays registered volunteers.
- Looks up a volunteer using findByID().
Delivery management
- Creates a DeliveryManager.
- Adds a delivery with an ID, destination/organisation details, and
  the supplied delivery parameter.
- Displays delivery records.
- Looks up a delivery using findByID().
- Assigns a volunteer ID through Delivery::assignVolunteer() when
  both lookups succeed.
Integration with the Food Rescue workflow
- Uses the donor and delivery managers in the live donor-priority
  workflow.
- Displays delivery and volunteer records after the workflow runs.
- Helps connect urgent food processing with delivery coordination.
6. High-Level Workflow
1. Register a volunteer.
2. Create a delivery record.
3. Retrieve the delivery and volunteer records using their IDs.
4. If both records are found, assign the volunteer to the delivery.
5. Display the updated delivery records.
6. Use the delivery manager during the donor-priority workflow and
   review the resulting records.
Volunteer Registration ──> VolunteerManager ──┐
                                              ├──> Assign Volunteer to Delivery
Delivery Creation ───────> DeliveryManager ───┘
                                                        |
                                                        v
                                             Updated Delivery Records
7. Important Test Note
In the supplied test code, delivery ID 401 is created, but the
assignment test searches for delivery ID 501:
deliveryManager.addDelivery(
    401,
    "Dehradun Food Bank",
    "Local NGO",
    1
);

Delivery* delivery = deliveryManager.findByID(501);
Because the IDs do not match, findByID(501) may return nullptr, and
the volunteer-assignment block will not execute. Use the same delivery
ID in both places (for example, 401) and rerun the test to verify
assignment.
The test code also looks up volunteer ID 101 after registering
volunteer Aman. Verify the ID generated/assigned by VolunteerManager
before relying on that lookup; the supplied snippet does not establish
that 101 belongs to Aman.
8. Build and Run
The project uses several project-specific header files. Compile the main
test program from the project directory where the include paths resolve
correctly.
Example with a typical compiler setup:
g++ main.cpp -o food_rescue
./food_rescue
If your source files are in separate .cpp files, include those files
in the compile command as well. Update the header include paths to match
your repository structure. The provided code uses paths such as
../include:/DONOR.h; confirm these paths are valid in your local
project.
9. Suggested Verification Checklist
- [ ] A volunteer can be registered and displayed.
- [ ] A delivery can be added and displayed.
- [ ] A valid volunteer ID can be found.
- [ ] A valid delivery ID can be found.
- [ ] Volunteer assignment succeeds when both IDs exist.
- [ ] Delivery records display the assigned volunteer correctly.
- [ ] The live donor-priority workflow runs and the resulting
  delivery/volunteer records can be reviewed.
Record test outcomes only after running the program. Do not mark a test
as passed based on code presence alone.
10. Current Scope and Future Improvements
The supplied test program demonstrates registration, display, ID lookup,
volunteer assignment logic, and integration with the donor-priority
workflow. The exact persistence mechanism and any full delivery-status
lifecycle are not established by the provided test snippet.
Possible future improvements, if not already implemented, include: -
Explicit delivery statuses such as PENDING, VOLUNTEER_ASSIGNED,
PICKED_UP, OUT_FOR_DELIVERY, and DELIVERED. - Delivery history
with timestamps. - Validation for duplicate or invalid IDs. - Clear
success/failure messages when an assignment cannot be completed. -
Persistent storage for volunteer and delivery records.
11. Team
- Aditya Dutta --- Team Lead
- Utsav Bajoria --- Volunteer & Delivery Module
- Vishwajeet Singh --- NGO & Requirement Module
- Raghav Pandey --- Donor & Food Donation Module
Module owner: Utsav Bajoria
Project: Food Rescue --- Smart Food Rescue and Redistribution System
