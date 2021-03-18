#include "data_structs.h"

/////////////// STACK
void Stack::init()
{
    head = nullptr; //initialize the stack
}

void Stack::close()
{
    Subtask *temp;
    while(head){
        temp = head;
        head = head->next;
        delete temp;
    }
}

void Stack::push(Subtask *in)   //pushes top element of stack
{
    if(isEmpty())      //if stack is empty push the element as only element
    {
        in->next = nullptr;
        head = in;
    }
    else    //if stack is not empty adds new element to the top
    {
        in->next = head;
        head = in;
    }
}

Subtask *Stack::pop()   //pops the top element of the stack
{
    if(isEmpty())   //if stack is empty returns null
    {
        // No Pop
        return nullptr;
    }
    else    //if stack is not empty pops the top element
    {
        Subtask *temp = new Subtask;
        temp->duration= head->duration;
        temp->name = head->name;
        Subtask *ptr = head;
        head = head->next;
        ptr->next = nullptr;

        delete ptr;
        return temp;
    }
}

bool Stack::isEmpty()   //checks if stack is empty or not
{
    return (head == nullptr);
}

/////////////// STACK

/////////////// QUEUE
void Queue::init()  //initialize the queue
{
    head = nullptr;
    tail = nullptr;
}

void Queue::close() //deletes the queue
{
    Process *temp;
    while(head){
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void Queue::queue(Process *in)  //adds new process to the queue
{
    if(isEmpty())   //if queue is empty makes it only element of the queue
    {
        head = in;
        tail = in;
        head->next = tail->next = nullptr;
    }
    else    //if queue is not empty adds new element to the end
    {
        tail->next = in;
        tail = in;
        tail->next = nullptr;
    }
}

Process *Queue::dequeue()   //takes the process out of the queue
{
    if(isEmpty())//if queue is empty returns null
    {
        // No dequeue
        return nullptr;
    }
    else//if queue is not empty dequeues the first entered element
    {
        Process *temp = new Process;
        temp->name = head->name;
        temp->arrival_time = head->arrival_time;
        temp->deadline = head->deadline;
        temp->priority = head->priority;
        temp->task_count = head->task_count;
        temp->task_stack= head->task_stack; //check
        Process *ptr = head;
        head = head->next;
        ptr->next = nullptr;

        if(head == nullptr) //just for security
        {
            tail = nullptr;
        }
        delete ptr;
        return temp;
    }
}

bool Queue::isEmpty()//checks if queue is empty or not
{
    return (head == nullptr && tail == nullptr);
}

Process *Queue::front()// returns the first element of the queue
{
    return head;
}

/////////////// QUEUE

/////////////// MULTI QUEUE
void MultiQueue::init() //initialize the multiqueue
{
    for(int i=0; i<3; i++)  //creates 3 queue element for 3 priority level
    {
        queues[i].init();
    }
}

void MultiQueue::close()    //deletes multiqueue
{
    for(int i=0; i<3; i++)
    {
        queues[i].close();
    }
}

void MultiQueue::queue(Process *in)
{
    queues[in->priority - 1].queue(in); //adds process to the proper queue for corresponding priority
}

Process *MultiQueue::dequeue(int priority)//takes the process out of queue
{
    return queues[priority-1].dequeue();
}

bool MultiQueue::isEmpty(int priority)//checks if proper queue is empty or not
{
    return queues[priority - 1].isEmpty();
}

Process *MultiQueue::front(int priority)//takes first element of the proper queue
{
    return queues[priority-1].front();
}

/////////////// MULTI QUEUE
