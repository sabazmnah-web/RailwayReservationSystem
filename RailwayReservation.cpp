#include "RailwayReservation.h"

WaitingQueue::WaitingQueue()
{
    front = NULL;
    rear = NULL;
}

bool WaitingQueue::isEmpty()
{
    return front == NULL;
}

void WaitingQueue::enqueue(Passenger p)
{
    QueueNode* n = new QueueNode(p);

    if (rear == NULL)
        front = rear = n;
    else
    {
        rear->next = n;
        rear = n;
    }
}

Passenger WaitingQueue::dequeue()
{
    Passenger p = {};

    if (isEmpty())
        return p;

    QueueNode* temp = front;
    p = temp->passenger;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    delete temp;
    return p;
}

void WaitingQueue::display()
{
    QueueNode* temp = front;

    if (temp == NULL)
    {
        cout << "Waiting list is empty.\n";
        return;
    }

    while (temp != NULL)
    {
        cout << "Ticket ID: " << temp->passenger.ticketID << endl;
        cout << "Name: " << temp->passenger.name << endl;
        cout << "Passenger ID: " << temp->passenger.passengerID << endl;
        cout << "-\n";
        temp = temp->next;
    }
}

RailwaySystem::RailwaySystem()
{
    head = NULL;
    nextTicketID = 1001;
}

TrainNode* RailwaySystem::findTrain(int id)
{
    TrainNode* temp = head;

    while (temp != NULL)
    {
        if (temp->trainID == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

void RailwaySystem::addTrain()
{
    int id, seats;
    char destination[50], time[20];

    cout << "Train ID: ";
    cin >> id;

    if (findTrain(id) != NULL)
    {
        cout << "Train already exists.\n";
        return;
    }

    cout << "Destination: ";
    cin.ignore();
    cin.getline(destination, 50);

    cout << "Departure Time: ";
    cin.getline(time, 20);

    cout << "Total Seats: ";
    cin >> seats;

    TrainNode* n = new TrainNode(id, destination, time, seats);

    if (head == NULL)
        head = n;
    else
    {
        TrainNode* temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = n;
    }

    cout << "Train added.\n";
}

void RailwaySystem::displayTrains()
{
    TrainNode* temp = head;

    if (temp == NULL)
    {
        cout << "No trains available.\n";
        return;
    }

    while (temp != NULL)
    {
        cout << "\nTrain ID: " << temp->trainID << endl;
        cout << "Destination: " << temp->destination << endl;
        cout << "Departure: " << temp->departureTime << endl;
        cout << "Total Seats: " << temp->totalSeats << endl;
        cout << "Available Seats: " << temp->availableSeats << endl;

        temp = temp->next;
    }
}

void RailwaySystem::searchTrainByID()
{
    int id;

    cout << "Train ID: ";
    cin >> id;

    TrainNode* temp = findTrain(id);

    if (temp == NULL)
    {
        cout << "Train not found.\n";
        return;
    }

    cout << "Train ID: " << temp->trainID << endl;
    cout << "Destination: " << temp->destination << endl;
    cout << "Departure: " << temp->departureTime << endl;
    cout << "Available Seats: " << temp->availableSeats << endl;
}

void RailwaySystem::searchTrainByDestination()
{
    char destination[50];

    cout << "Destination: ";
    cin.ignore();
    cin.getline(destination, 50);

    TrainNode* temp = head;
    bool found = false;

    while (temp != NULL)
    {
        if (strcmp(temp->destination, destination) == 0)
        {
            cout << "\nTrain ID: " << temp->trainID << endl;
            cout << "Destination: " << temp->destination << endl;
            cout << "Departure: " << temp->departureTime << endl;
            cout << "Available Seats: " << temp->availableSeats << endl;
            found = true;
        }

        temp = temp->next;
    }

    if (!found)
        cout << "Train not found.\n";
}

void RailwaySystem::addPassenger(TrainNode* train, Passenger p)
{
    PassengerNode* n = new PassengerNode(p);

    if (train->passengers == NULL)
        train->passengers = n;
    else
    {
        PassengerNode* temp = train->passengers;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = n;
    }
}

void RailwaySystem::reserveTicket()
{
    int id;

    cout << "Train ID: ";
    cin >> id;

    TrainNode* train = findTrain(id);

    if (train == NULL)
    {
        cout << "Train not found.\n";
        return;
    }

    Passenger p;

    p.ticketID = nextTicketID++;

    cout << "Passenger ID: ";
    cin >> p.passengerID;

    cout << "Name: ";
    cin.ignore();
    cin.getline(p.name, 50);

    cout << "Age: ";
    cin >> p.age;

    if (train->availableSeats > 0)
    {
        p.seatNumber =
            train->totalSeats - train->availableSeats + 1;

        addPassenger(train, p);
        train->availableSeats--;

        cout << "\nTicket ID: " << p.ticketID << endl;
        cout << "Seat Number: " << p.seatNumber << endl;
        cout << "Reservation successful.\n";
    }
    else
    {
        p.seatNumber = 0;
        train->waitingList.enqueue(p);

        cout << "No seats available.\n";
        cout << "Added to waiting list.\n";
    }
}

void RailwaySystem::cancelTicket()
{
    int trainID, ticketID;

    cout << "Train ID: ";
    cin >> trainID;

    TrainNode* train = findTrain(trainID);

    if (train == NULL)
    {
        cout << "Train not found.\n";
        return;
    }

    cout << "Ticket ID: ";
    cin >> ticketID;

    PassengerNode* current = train->passengers;
    PassengerNode* previous = NULL;

    while (current != NULL &&
            current->passenger.ticketID != ticketID)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Ticket not found.\n";
        return;
    }

    if (previous == NULL)
        train->passengers = current->next;
    else
        previous->next = current->next;

    delete current;

    cout << "Ticket cancelled.\n";

    if (!train->waitingList.isEmpty())
    {
        Passenger p = train->waitingList.dequeue();

        p.seatNumber =
            train->totalSeats - train->availableSeats;

        addPassenger(train, p);

        cout << "Seat given to waiting passenger.\n";
        cout << "Passenger: " << p.name << endl;
        cout << "Seat: " << p.seatNumber << endl;
    }
    else
    {
        train->availableSeats++;
    }
}

void RailwaySystem::displayWaitingList()
{
    int id;

    cout << "Train ID: ";
    cin >> id;

    TrainNode* train = findTrain(id);

    if (train == NULL)
    {
        cout << "Train not found.\n";
        return;
    }

    train->waitingList.display();
}

void RailwaySystem::displayPassengers()
{
    int id;

    cout << "Train ID: ";
    cin >> id;

    TrainNode* train = findTrain(id);

    if (train == NULL)
    {
        cout << "Train not found.\n";
        return;
    }

    PassengerNode* temp = train->passengers;

    if (temp == NULL)
    {
        cout << "No passengers.\n";
        return;
    }

    while (temp != NULL)
    {
        cout << "\nTicket ID: "
             << temp->passenger.ticketID << endl;

        cout << "Passenger ID: "
             << temp->passenger.passengerID << endl;

        cout << "Name: "
             << temp->passenger.name << endl;

        cout << "Age: "
             << temp->passenger.age << endl;

        cout << "Seat: "
             << temp->passenger.seatNumber << endl;

        temp = temp->next;
    }
}

void RailwaySystem::sortByDestination()
{
    if (head == NULL)
        return;

    for (TrainNode* i = head; i->next != NULL; i = i->next)
    {
        for (TrainNode* j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->destination, j->destination) > 0)
            {
                swap(i->trainID, j->trainID);
                swap(i->totalSeats, j->totalSeats);
                swap(i->availableSeats, j->availableSeats);

                char temp[50];
                strcpy(temp, i->destination);
                strcpy(i->destination, j->destination);
                strcpy(j->destination, temp);

                char time[20];
                strcpy(time, i->departureTime);
                strcpy(i->departureTime, j->departureTime);
                strcpy(j->departureTime, time);
            }
        }
    }

    cout << "Sorted by destination.\n";
}

void RailwaySystem::sortByDepartureTime()
{
    if (head == NULL)
        return;

    for (TrainNode* i = head; i->next != NULL; i = i->next)
    {
        for (TrainNode* j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->departureTime, j->departureTime) > 0)
            {
                swap(i->trainID, j->trainID);
                swap(i->totalSeats, j->totalSeats);
                swap(i->availableSeats, j->availableSeats);

                char temp[50];
                strcpy(temp, i->destination);
                strcpy(i->destination, j->destination);
                strcpy(j->destination, temp);

                char time[20];
                strcpy(time, i->departureTime);
                strcpy(i->departureTime, j->departureTime);
                strcpy(j->departureTime, time);
            }
        }
    }

    cout << "Sorted by departure time.\n";
}

void RailwaySystem::menu()
{
    int choice;

    do
    {
        cout << "\n===== RAILWAY RESERVATION =====\n";
        cout << "1. Add Train\n";
        cout << "2. Display Trains\n";
        cout << "3. Search Train by ID\n";
        cout << "4. Search Train by Destination\n";
        cout << "5. Reserve Ticket\n";
        cout << "6. Cancel Ticket\n";
        cout << "7. Display Passengers\n";
        cout << "8. Display Waiting List\n";
        cout << "9. Sort by Destination\n";
        cout << "10. Sort by Departure Time\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTrain();
            break;

        case 2:
            displayTrains();
            break;

        case 3:
            searchTrainByID();
            break;

        case 4:
            searchTrainByDestination();
            break;

        case 5:
            reserveTicket();
            break;

        case 6:
            cancelTicket();
            break;

        case 7:
            displayPassengers();
            break;

        case 8:
            displayWaitingList();
            break;

        case 9:
            sortByDestination();
            break;

        case 10:
            sortByDepartureTime();
            break;

        case 0:
            break;

        default:
            cout << "Invalid choice.\n";
        }

    }
    while (choice != 0);
}
