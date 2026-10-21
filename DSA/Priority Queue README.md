## Priority Queue

The `UrgentFoodQueue` manages food donations using a priority queue implemented with a binary heap. It ensures that food with a higher urgency level is selected before food that can remain available for longer.

### Features

- **Priority-Based Ordering:** Stores food donations according to their assigned priority.
- **Binary Heap:** Uses a vector to implement a binary heap for efficient insertion and removal.
- **Add Food Task:** Adds a food donation to the queue with its ID, name, quantity and priority.
- **Automatic Reordering:** Rearranges the heap whenever a task is added or removed.
- **Process Urgent Food:** Removes and returns the most urgent food donation.
- **Display Queue:** Displays the food tasks currently stored in the queue.
- **Empty Queue Handling:** Checks whether the queue is empty before processing or displaying tasks.

### How Priority Works

The queue uses a **min-heap**, meaning the smaller priority number comes first.

| Priority | Meaning |
|---|---|
| 1 | Highest urgency |
| 2 | High urgency |
| 3 | Moderate urgency |
| 4 | Lowest urgency |

For example, if three donations have priorities 4, 1 and 3, the donation with priority 1 will be processed first.

### How It Works

1. A food donation is received with its ID, name, quantity and priority.
2. The `enqueue()` function adds the donation to the heap.
3. The `heapifyUp()` function moves the new task upward if it has a higher priority than its parent.
4. The `dequeue()` function removes the task at the root, which contains the highest-priority donation.
5. The last task replaces the removed task, and `heapifyDown()` restores the heap structure.
6. The `display()` function shows the tasks currently in the queue.

### Main Functions

- `enqueue()` — Adds a new food task to the priority queue.
- `dequeue()` — Removes and returns the most urgent food task.
- `heapifyUp()` — Maintains the heap structure after insertion.
- `heapifyDown()` — Maintains the heap structure after removal.
- `higherPriority()` — Compares two tasks to determine which has greater urgency.
- `display()` — Displays all food tasks currently in the heap.
- `isEmpty()` — Checks whether the queue contains any tasks.

### Data Structure Used

- **Vector:** Stores the food tasks dynamically.
- **Binary Min-Heap:** Keeps the task with the smallest priority number at the root.

### Time Complexity

| Operation | Time Complexity |
|---|---|
| Enqueue | O(log n) |
| Dequeue | O(log n) |
| Check if empty | O(1) |
| Display | O(n) |

### Purpose

The main purpose of the Priority Queue is to help the Food Rescue System process the most urgent food donations first, reducing food wastage and supporting timely delivery to NGOs.
