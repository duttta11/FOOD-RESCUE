# FoodRescue – Donor & Food Donation Module

## About
The module, which is part of the FoodRescue project, has been developed using C++ and is used for managing donors and their food donations. It enables users to add donations, view them, update them, delete them and to check the availability and expiry status of the food.

## Header File
`FoodRescue.h`

### Libraries Used
The iostream facility is used for input and output.
– In order to have a number of food donations.
- `string` stores text data.

## Classes and Properties

### 1. FoodDonation Class
The class includes information about one food donation.

**Properties:**
- id, the unique identifier for the donation.
The name of the food item that has been donated.
The quantity of food.
- expiryDate – the date beyond which the food is no longer suitable for consumption.
– Indicates whether or not the food is available.

**Function:**
- `display()` – This function provides all the details about a food donation.

### 2. Donor Class
The class is responsible for storing information about donors and for handling their food donations.

**Properties:**
The donorID is the unique ID for the donor.
The donor's name.
- `phone` means the donor’s contact number.
The donor's address.
- `donations` – a vector consisting of several `FoodDonation` objects.

**Functions:**
The function displayDonor() shows the donor's details.
addDonation() adds a new food donation.
– the function displayDonations() displays all the donations.
- `updateDonation()` updates current donation details.
- `deleteDonation()` marks a donation as unavailable.
– checkExpiry() – this function is used for manually verifying and updating the expiry status of food.
– The function showAvailableFood shows only the food donations that are available.

## C++ Concepts Used
- Classes and Objects
- Constructors
- Vectors
- Functions
- Loops and Conditional Statements

## Working
1. Store donor details.
2. The food donations should also state the quantity and the expiry date.
3. Check the donation records, alter them, or delete them.
Make sure that the food has not expired.
5. State the type of food that is available for redistribution.

## Note
The user has to check manually whether the food has expired; at present, the system retains the data in memory and does not automatically save it to a file or database.

## Conclusion
The module enables efficient management of donors and food donations and includes the fundamental features required for organizing surplus food and for allowing its redistribution via the FoodRescue project.