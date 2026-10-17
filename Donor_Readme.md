# FoodRescue – Donor & Food Donation Module

## About
The Donor and Food Donation Module is a part of the FoodRescue project, developed using C++. It helps manage donors and the food they donate. Users can add new donations, view existing records, update details, mark donations as unavailable, and check food availability and expiry status.

## Header File
`FoodRescue.h`

### Libraries Used
- `iostream` – Used to take input from the user and display output.
- `vector` – Used to store multiple food donation records.
- `string` – Used to store text, such as names, addresses, and expiry dates.

## Classes and Properties

### 1. FoodDonation Class
The `FoodDonation` class stores the details of a food item donated to the system.

**Properties:**
- `id` – A unique ID assigned to each donation.
- `foodName` – The name of the donated food.
- `quantity` – The amount of food available.
- `expiryDate` – The date until which the food is considered suitable for use.
- `available` – Shows whether the food is currently marked as available.

**Function:**
- `display()` – Displays all the details of a particular food donation.

### 2. Donor Class
The `Donor` class keeps the donor's information and manages the food donations made by them.

**Properties:**
- `donorID` – A unique ID for each donor.
- `name` – The name of the donor.
- `phone` – The donor's contact number.
- `address` – The donor's address.
- `donations` – A vector that stores the donor's food donation records.

**Functions:**
- `displayDonor()` – Shows the donor's information.
- `addDonation()` – Allows the user to add a new food donation.
- `displayDonations()` – Displays all the donations stored in the system.
- `updateDonation()` – Allows the user to change the details of an existing donation.
- `deleteDonation()` – Marks a donation as unavailable and sets its quantity to zero.
- `checkExpiry()` – Asks the user to check whether the food has expired and updates its availability status.
- `showAvailableFood()` – Displays only the donations currently marked as available.

## C++ Concepts Used
- Classes and Objects
- Constructors
- Vectors
- Functions
- Loops and Conditional Statements

## How It Works
1. The donor's basic details are stored in the system.
2. The donor can add food donations along with their quantity and expiry date.
3. Existing donation records can be viewed, updated, or marked as unavailable.
4. The user can manually check whether the donated food has expired.
5. The system displays the food that is marked as available for redistribution.

## Note
At present, food expiry is checked manually by the user. The donation records are stored in memory, so the data is not automatically saved to a file or database. The data will be lost when the program ends unless it is saved separately.

## Conclusion
This module provides the basic features needed to manage donors and their food donations. It helps keep donation records organized and makes it easier to identify available food for redistribution as part of the FoodRescue project.