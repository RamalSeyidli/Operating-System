#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Subtask{ //subtask of process
    string name;    //subtask's name
    int duration;   //subtask's duration
    Subtask *next;  //subtask's next pointer
};

struct Stack{   //stack structure
    Subtask *head;  //stack's top element

    void init();    //creates stack
    void close();   //deletes stack
    void push(Subtask *in); //pushes subtask, top of stack
    Subtask *pop(); //pops subtask, top of stack
    bool isEmpty(); // Check emptiness
};

struct Process{
    string name;    //porcess's name
    int arrival_time;   //porcess's arrival time
    int deadline;   //porcess's deadline
    int task_count; //number of subtasks of porcess
    int priority;   //priority level of porcess
    Stack task_stack;   //porcess's stack
    Process *next;  //next pointer of process
};

struct Queue{
    Process *head;
    Process *tail;

    void init(); // Create Queue
    void close(); // Close Queue
    void queue(Process *in); // Enqueue Process
    Process *dequeue(); // Dequeue Process
    bool isEmpty(); // Check emptiness
    Process *front(); // Check front (head) Process
};

struct MultiQueue{
    Queue queues[3];

    void init();    // Create Multi-Queue
    void close();   // Close Queue
    void queue(Process *in);    //adds process to the proper queue for corresponding priority
    Process *dequeue(int priority); //takes the process out of queue
    bool isEmpty(int priority); //checks if proper queue is empty or not
    Process *front(int priority); //takes the first element of the proper queue
};

#endif // DATA_STRUCTS_H
