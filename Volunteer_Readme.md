# FoodRescue – Volunteer & Delivery Module

## About

The Volunteer & Delivery Module is a part of the FoodRescue project, developed using C++. It helps manage volunteers and food deliveries by maintaining volunteer records, creating delivery requests, assigning volunteers to deliveries, and coordinating the delivery process. This module connects with the donor and NGO modules to support the smooth redistribution of surplus food to people in need.

## Header Files

- `FoodDonationDeliverySystem.h`
- `UrgencyManager.h`
- `PriorityQueue.h`

## Libraries Used

- `iostream` – Used to take input from the user and display output.
- `vector` – Used to store multiple volunteer and delivery records.
- `string` – Used to store text, such as names, phone numbers, and locations.

## Classes and Properties

### 1. Volunteer Class

The `Volunteer` class stores the details of a volunteer registered in the system.

**Properties:**

- `volunteerID` – A unique ID assigned to each volunteer.
- `name` – The name of the volunteer.
- `phone` – The volunteer's contact number.
- `location` – The location from which the volunteer can help with deliveries.
- `availability` – Represents whether the volunteer is available for assignment, if implemented.

### 2. VolunteerManager Class

The `VolunteerManager` class manages volunteer records and provides functions to register, display, and search for volunteers.

**Main Functions:**

- `addVolunteer()` – Registers a new volunteer.
- `findByID()` – Searches for a volunteer using their ID.
- `findAvailable()` – Searches for an available volunteer, if supported by the implementation.
- `displayAll()` – Displays all registered volunteers.
- `isEmpty()` – Checks whether any volunteer records exist.

### 3. Delivery Class

The `Delivery` class represents a food delivery record and supports assigning a volunteer to the delivery.

**Properties:**

- `deliveryID` – A unique ID assigned to each delivery.
- `donationID` – Identifies the food donation associated with the delivery.
- `pickup` – The pickup location.
- `drop` – The destination where the food needs to be delivered.
- `priority` – Represents the priority assigned to the delivery.
- `volunteerID` – Stores the assigned volunteer's ID, where implemented.

### 4. DeliveryManager Class

The `DeliveryManager` class manages delivery records and provides functions to create, display, and search for deliveries.

**Main Functions:**

- `addDelivery()` – Creates a new delivery record.
- `findByID()` – Searches for a delivery using its ID.
- `displayAll()` – Displays all delivery records.
- `isEmpty()` – Checks whether any delivery records exist.

## How the Module Works

1. A volunteer registers with their name, contact number, and location.
2. A delivery record is created for a food donation.
3. The system searches for the required volunteer and delivery using their IDs.
4. If both records are found, the volunteer can be assigned to the delivery.
5. The updated delivery records are displayed for verification.
6. The module works alongside the donor-priority workflow to support food redistribution.

## Workflow

```text
Volunteer Registration
         |
         v
 VolunteerManager
         |
         v
 Create Delivery Request
         |
         v
 DeliveryManager
         |
         v
 Find Volunteer and Delivery
         |
         v
 Assign Volunteer
         |
         v
 Display Updated Delivery Records
```

## Integration with Other Modules

The Volunteer & Delivery Module works with the other components of FoodRescue:

- **Donor & Food Donation Module** – Provides food donation records.
- **NGO & Requirement Module** – Helps match available food with NGO requirements.
- **Priority Queue** – Supports processing urgent food-related tasks.
- **UrgencyManager** – Connects priority processing with the broader delivery workflow.

## Technologies
