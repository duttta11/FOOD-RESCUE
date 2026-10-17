# FoodRescue – Donor & Food Donation Module

## About
The module, belonging to the FoodRescue project, has been written in C++ and carries out the function of managing donors and their food donations. It allows users to add donations, see them, update them, delete them and to check the availability and expiry status of the food.

## Header File
`FoodRescue.h`

### Libraries Used
- `iostream` is used for input and output.
– To keep a number of food donations.
- `string` holds text data.

## Classes and Properties

### 1. FoodDonation Class
The class has details concerning a single food donation.

**Properties:**
- id, the unique identifier of the donation.
The name of the food item which has been donated.
The quantity of food.
- expiryDate – the date after which the food is no longer fit to be eaten.
– Shows whether or not the food is available.

**Function:**
- `display()` – It shows all the details regarding a food donation.

### 2. Donor Class
The class handles the storage of information on donors and is in charge of their food donations.

**Properties:**
The donorID is the unique identifier for the donor.
The donor's name.
- `phone` – the donor’s contact number.
The donor's address.
- `donations` – a vector that contains multiple `FoodDonation` objects.

**Functions:**
The function `displayDonor()` displays the donor's details.
addDonation() adds a new food donation.
– the function displayDonations() shows all the donations.
- `updateDonation()` updates current donation details.
- `deleteDonation()` marks a donation as unavailable.
– checkExpiry() – this function serves the purpose of manually checking and updating the expiry status of food.
– the function showAvailableFood displays only those food donations which are available.

## C++ Concepts Used
- Classes and Objects
- Constructors
- Vectors
- Functions
- Loops and Conditional Statements

## Working
1. Store donor details.
2. The food donations should also include the amount and the expiry date.
3. Look at the donation records, make changes to them, or delete them.
4. Check whether the food has expired.
5. Indicate the food that is available for redistribution.

## Note
The user must manually check the food's expiry date; currently, the system keeps the data in memory and does not automatically save it to a file or database.

## Conclusion
The module allows for efficient management of donors and food donations and has the basic features needed for organizing surplus food and for enabling its redistribution through the FoodRescue project.
