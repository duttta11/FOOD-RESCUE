## Urgency Manager

The `UrgencyManager` manages food donations based on their expiry dates. It helps ensure that food that will expire soon is given higher priority for delivery.

### Features

- **Expiry Date Validation:** Checks that expiry dates are entered in `DD-MM-YYYY` format and represent valid dates.
- **Automatic Priority Assignment:** Assigns priority according to the number of days remaining before expiry.
- **Priority Queue:** Adds available food donations to the queue so that urgent food can be processed first.
- **Duplicate Prevention:** Prevents the same donation from being added to the queue more than once.
- **Donation Management:** Allows users to add new food donations and display existing donations.
- **Delivery Creation:** Creates a delivery request when the most urgent food is selected.
- **Volunteer Assignment:** Assigns an available volunteer to the delivery, if one is available.
- **Availability Update:** Marks the selected donation as unavailable after processing so it cannot be donated again accidentally.

### Priority System

| Days Until Expiry | Priority |
|---|---|
| Expires today | 1 — Highest |
| Expires tomorrow | 2 |
| Expires in 2–3 days | 3 |
| Expires in more than 3 days | 4 — Lowest |
| Already expired | Rejected |

A lower priority number represents greater urgency.

### How It Works

1. The donor adds food donations with details such as food name, quantity and expiry date.
2. The urgency manager checks whether the food is available and whether its expiry date is valid.
3. The system calculates the priority based on the remaining days until expiry.
4. Available donations are added to the priority queue.
5. When the user selects the processing option, the queue returns the most urgent food.
6. The system creates a delivery request and assigns an available volunteer, if possible.
7. The selected donation is marked as unavailable.

### Main Functions

- `addFoodToUrgentQueue()` — Validates and adds an individual donation to the priority queue.
- `addAllDonationsToQueue()` — Adds eligible donations from a donor.
- `runDonorMenu()` — Provides the menu for managing donations, viewing the queue and processing urgent food.
- `parseDate()` — Validates expiry dates.
- `calculatePriority()` — Calculates the priority using the expiry date.

### Purpose

The main purpose of the Urgency Manager is to reduce food wastage by prioritizing donations that are closer to their expiry dates and helping coordinate their delivery to NGOs.
