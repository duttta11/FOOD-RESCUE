# **NGO & Requirement Module – README**

## **About**

The NGO and Requirement Module is a part of the FoodRescue project, developed using C++. It helps NGOs register themselves, log in, manage their food requirements, and view available food donations. The module also matches available food donations with NGO requirements based on food type and quantity.
Header File
ngo_requirement.h

## **Libraries Used**

- iostream – Used to take input from the user and display output.
- string – Used to store text, such as NGO names, email addresses, locations, and food types.
- vector – Used to store multiple NGO records, food requirements, and donation records.
- queue – Used to manage pending food requirements in the order they are added.
- limits – Used for handling invalid input in the input functions.
- algorithm – Used for operations such as finding the minimum value and reducing quantities safely.
  
## **Classes and Properties**

## **1. NGO Class**
The NGO class stores the details of a registered NGO.

### **Properties:**

- ngoID – A unique ID assigned to each NGO.
- name – The name of the NGO.
- email – The NGO's email address.
- password – The password used for login.
- location – The NGO's location.
- capacity – The number of meals the NGO can handle.
- loggedIn – Shows whether the NGO is logged in.
  
### **Functions:**

- displayNGO() – Displays the NGO's details.
- setCapacity() – Updates the NGO's capacity.
- setLocation() – Updates the NGO's location.
- setLoggedIn() – Updates the login status.
- Getter functions – Return NGO details when required.
- checkPassword() – Checks whether the entered password matches the stored password.
- reduceCapacity() – Reduces the NGO's capacity by a given quantity.
  
## **2. Requirement Class**

The Requirement class stores the food requirements submitted by NGOs.

### **Properties:**

- requirementID – A unique ID assigned to each requirement.
- ngoID – The ID of the NGO that submitted the requirement.
- foodType – The type of food required.
- quantityNeeded – The quantity of food needed.
- urgency – The urgency level, from 1 to 5.
- reqStatus – Shows whether the requirement is pending or fulfilled.
  
### **Functions:**

- displayRequirement() – Displays the requirement details.
- reduceQuantity() – Reduces the remaining quantity needed after matching a donation.
- markFulfilled() – Marks a requirement as fulfilled.
- Getter functions – Return requirement details and status.
- getStatus() – Returns whether the requirement is pending or fulfilled.
  
## **3. NGODonation Class**

The NGODonation class stores food donations that can be matched with NGO requirements.

### **Properties:**

- donationID – A unique ID assigned to each donation.
- foodType – The type of donated food.
- quantity – The quantity of food donated.
- matched – Shows whether the donation has been completely matched.
  
### **Functions:**

- displayDonation() – Displays the donation details.
- reduceQuantity() – Reduces the available quantity after matching.
- Getter functions – Return donation details and matching status.
Manager Classes

## **4. NGOManager Class**

The NGOManager class manages NGO registration and login.

### **Functions:**

- registerNGO() – Registers a new NGO and assigns it a unique ID.
- findByID() – Searches for an NGO using its ID.
- login() – Checks the entered email and password.
- displayAll() – Displays all registered NGOs.
- isEmpty() – Checks whether any NGOs are registered.
  
## **5. RequirementManager Class**

The RequirementManager class manages pending and fulfilled food requirements.

### **Functions:**

- addRequirement() – Adds a new food requirement.
- displayPending() – Displays all pending requirements.
- displayFulfilled() – Displays fulfilled requirements.
- matchWithDonations() – Matches food donations with requirements based on food type and available quantity.
- isEmpty() – Checks whether any pending requirements exist.
  
## **6. DonationManager Class**

The DonationManager class manages available food donations.

### **Functions:**

- addDonation() – Adds a new food donation and assigns it a unique ID.
- displayAll() – Displays all recorded donations.
- getAll() – Provides access to the donation records for matching.
- isEmpty() – Checks whether any donations are stored.
C++ Concepts and Data Structures Used
- Classes and Objects
- Constructors
- Encapsulation using private and public members
- Vectors
- Queue
- Functions
- Loops and Conditional Statements
- Getter and Setter Functions
- Pointers
- Enum for requirement status
- Header Guards using #ifndef, #define, and #endif
  
### **How It Works**

1. The NGO registers by entering its name, email, password, location, and capacity.
2. The system assigns a unique NGO ID.
3. The NGO can log in using its email and password.
4. A food requirement is added using the NGO ID, food type, required quantity, and urgency level.
5. Food donations are added with their food type and quantity.
6. The system matches donations with requirements that have the same food type.
7. The required and donated quantities are reduced according to the matched amount.
8. Fully satisfied requirements are moved to the fulfilled records, while partially satisfied requirements remain pending.
9. Users can view registered NGOs, pending requirements, available donations, and fulfilled requirements through the menu.
    
## **Note**

The module uses vectors and a queue to store records temporarily in memory. The data is not automatically saved to a file or database, so it will be lost when the program ends unless separate storage is implemented.

The login feature checks the NGO's email and password, but the module does not implement advanced authentication or persistent user accounts.

## **Conclusion**

This module provides the basic functionality required to connect NGOs with available food donations. It helps organize NGO information, record food requirements, track donation quantities, and match available food with the needs of NGOs. It supports the main objective of the FoodRescue project: reducing food wastage by helping redistribute surplus food to people in need.
