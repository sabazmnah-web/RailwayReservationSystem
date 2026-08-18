#ifndef RAILWAYRESERVATION_H
#define RAILWAYRESERVATION_H

#include <iostream>
#include <cstring>
using namespace std;

struct Passenger
{
    int ticketID;
    int passengerID;
    char name[50];
    int age;
    int seatNumber;
};

struct QueueNode
{
    Passenger passenger;
    QueueNode* next;

    QueueNode(Passenger p)
    {
        passenger = p;
        next = NULL;
    }
};

class WaitingQueue
{
private:
    QueueNode* front;
    QueueNode* rear;

public:
    WaitingQueue();
    bool isEmpty();
    void enqueue(Passenger p);
    Passenger dequeue();
    void display();
};

struct PassengerNode
{
    Passenger passenger;
    PassengerNode* next;

    PassengerNode(Passenger p)
    {
        passenger = p;
        next = NULL;
    }
};

struct TrainNode
{
    int trainID;
    char destination[50];
    char departureTime[20];
    int totalSeats;
    int availableSeats;
    PassengerNode* passengers;
    WaitingQueue waitingList;
    TrainNode* next;

    TrainNode(int id, const char dest[], const char time[], int seats)
    {
        trainID = id;
        strcpy(destination, dest);
        strcpy(departureTime, time);
        totalSeats = seats;
        availableSeats = seats;
        passengers = NULL;
        next = NULL;
    }
};

class RailwaySystem
{
private:
    TrainNode* head;
    int nextTicketID;

public:
    RailwaySystem();

    void addTrain();
    void displayTrains();
    void searchTrainByID();
    void searchTrainByDestination();
    void reserveTicket();
    void cancelTicket();
    void displayWaitingList();
    void displayPassengers();
    void sortByDestination();
    void sortByDepartureTime();

    TrainNode* findTrain(int id);
    void addPassenger(TrainNode* train, Passenger p);
    void menu();
};

#endif
