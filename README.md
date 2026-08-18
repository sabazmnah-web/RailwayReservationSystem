# Railway Reservation System

A lightweight, console-based **Railway Reservation System** written in **C++**. This project demonstrates core Data Structures and Algorithms (DSA) concepts such as **Singly Linked Lists**, **Custom Queue Data Structures**, and manual **Sorting Algorithms** without using standard library containers.

---

## Features

* **Train Management**
    * Add new trains with custom IDs, destinations, departure times, and total seating capacities.
    * Display a full list of registered trains and current seat availability.
    * Search trains by **Train ID** or **Destination**.
    * Sort train schedules by **Destination** or **Departure Time**.

* **Ticket Reservation & Seat Allocation**
    * Automatic generation of unique Ticket IDs starting from `1001`.
    * Dynamic seat number assignment for confirmed bookings.
    * Automatic queue management: If a train is fully booked, passengers are placed into a **Waiting List (FIFO Queue)**.

* **Ticket Cancellation & Automation**
    * Cancel reservations easily using Ticket IDs.
    * **Auto-reassignment**: When a confirmed passenger cancels, the top passenger from the waiting list is automatically dequeued and assigned the newly freed seat.

* **Passenger & Queue Monitoring**
    * Display confirmed passenger lists for individual trains.
    * Display current waiting lists per train.

---

## Data Structures Used

* **Singly Linked List (`TrainNode`)**: Maintains the dynamic list of trains in the system.
* **Singly Linked List (`PassengerNode`)**: Stores confirmed passengers under each train node.
* **FIFO Queue (`WaitingQueue`)**: Implemented using dynamic linked pointers (`front` and `rear`) to manage passengers on the waiting list.
* **Bubble/Selection Swap Logic**: Custom string-sorting algorithm using `strcmp` to reorder trains without C++ standard STL algorithms.

---

## Project Structure

```text
.
├── RailwayReservation.h   # Header file containing data structures, structs, and class declarations
├── RailwayReservation.cpp # Implementation of queue operations, train system methods, and menu logic
└── main.cpp              # Application entry point
