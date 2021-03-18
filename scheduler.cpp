#include "data_structs.h"

using namespace std;

int main(int argc, char *argv[])//main with argument
{
    const char *file_name;//assigning the file name
    if(argc > 1)
    {
        file_name = argv[1];
    }
    else//if no argument entered
    {
        cout << "No arguments!" << '\n';
        return 0;
    }

    ifstream file(file_name);//reading file name

    MultiQueue sch;//declaring multiqueue
    sch.init();

    Queue process_queue;//declaring queue
    process_queue.init();

    string current_process_name;

    while(file >> current_process_name)//input reading section
    {
        Process *current_process = new Process;//to operate a process
        current_process->name = current_process_name;
        file >> current_process->priority;
        file >> current_process->arrival_time;
        file >> current_process->task_count;

        int total_subtask_duration = 0;//to determine i of loop

        for(int i=0; i<current_process->task_count; i++)//takes all subtasks from input text
        {
            Subtask *current_subtask = new Subtask;
            file >> current_subtask->name >> current_subtask->duration;
            total_subtask_duration += current_subtask->duration;
            current_process->task_stack.push(current_subtask);
        }

        current_process->deadline = current_process->arrival_time + total_subtask_duration;//calculates deadline

        process_queue.queue(current_process);//queues current process
    }


    int global_time = 0;//to count time
    int priority2_access_count = 0;//for special condition
    int cummulative_lateness = 0;//to count up lateness

    while(true)//output writing section
    {
        if(!sch.isEmpty(1))//if multiqueue is empty
        {
            Process *current_process = sch.front(1);//takes a process to operate
            if(!current_process->task_stack.isEmpty())
            {
                Subtask *current_subtask = current_process->task_stack.pop();
                global_time += current_subtask->duration;
                cout << current_process->name << " " << current_subtask->name << '\n';
                delete current_subtask;
                while(!process_queue.isEmpty() && process_queue.front()->arrival_time <= global_time)
                {
                    sch.queue(process_queue.dequeue());
                }
            }
            else
            {
                Process *temp = sch.dequeue(1);
                int lateness = global_time - temp->deadline;
                cummulative_lateness += lateness;
                delete temp;
            }
        }
        else if(!sch.isEmpty(2) && priority2_access_count != 2)//not special case
        {
            Process *current_process = sch.front(2);
            if(!current_process->task_stack.isEmpty())
            {
                Subtask *current_subtask = current_process->task_stack.pop();
                global_time += current_subtask->duration;
                cout << current_process->name << " " << current_subtask->name << '\n';
                delete current_subtask;
                while(!process_queue.isEmpty() && process_queue.front()->arrival_time <= global_time)
                {
                    sch.queue(process_queue.dequeue());
                }
                priority2_access_count++;
            }
            else
            {
                Process *temp = sch.dequeue(2);
                int lateness = global_time - temp->deadline;
                cummulative_lateness += lateness;
                delete temp;
            }
        }
        else if(!sch.isEmpty(3) || priority2_access_count == 2)//special case
        {
            if(priority2_access_count == 2)
            {
                priority2_access_count = 0;
            }

            Process *current_process = sch.front(3);
            if(!current_process->task_stack.isEmpty())
            {
                Subtask *current_subtask = current_process->task_stack.pop();
                global_time += current_subtask->duration;
                cout << current_process->name << " " << current_subtask->name << '\n';
                delete current_subtask;
                while(!process_queue.isEmpty() && process_queue.front()->arrival_time <= global_time)
                {
                    sch.queue(process_queue.dequeue());
                }
            }
            else
            {
                Process *temp = sch.dequeue(3);
                int lateness = global_time - temp->deadline;
                cummulative_lateness += lateness;
                delete temp;
            }
        }
        else
        {
            if(!process_queue.isEmpty())
            {
                sch.queue(process_queue.dequeue());
            }
            else
            {
                break;
            }
        }
    }

    cout << "Cumulative Lateness: " << cummulative_lateness << '\n';//prints cumulative lateness
    process_queue.close();//closes queue
    sch.close();//closes everything

    return 0;
}
