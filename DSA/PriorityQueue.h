#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct FoodTask
{
    int donationID;
    string foodName;
    int quantity;
    int priority;
};

class UrgentFoodQueue
{
private:
    vector<FoodTask> heap;

    bool higherPriority(const FoodTask& a, const FoodTask& b)
    {
        return a.priority < b.priority;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (higherPriority(heap[index], heap[parent]))
            {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int index)
    {
        int size = heap.size();

        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int highest = index;

            if (left < size &&
                higherPriority(heap[left], heap[highest]))
            {
                highest = left;
            }

            if (right < size &&
                higherPriority(heap[right], heap[highest]))
            {
                highest = right;
            }

            if (highest == index)
                break;

            swap(heap[index], heap[highest]);
            index = highest;
        }
    }

public:
    void enqueue(int id, string name, int qty, int priority)
    {
        FoodTask task = {id, name, qty, priority};

        heap.push_back(task);
        heapifyUp(heap.size() - 1);

        cout << "Food task added to urgent queue.\n";
    }

   
    bool dequeue(FoodTask& task)
    {
        if (heap.empty())
        {
            cout << "Urgent queue is empty.\n";
            return false;
        }

        task = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return true;
    }

    
    void display()
    {
        if (heap.empty())
        {
            cout << "Urgent queue is empty.\n";
            return;
        }

        cout << "\n----- URGENT FOOD QUEUE -----\n";

        for (const FoodTask& task : heap)
        {
            cout << "Donation ID : " << task.donationID << endl;
            cout << "Food Name   : " << task.foodName << endl;
            cout << "Quantity    : " << task.quantity << endl;
            cout << "Priority    : " << task.priority << endl;
            cout << "-----------------------------\n";
        }
    }

    bool isEmpty()
    {
        return heap.empty();
    }
};

#endif
