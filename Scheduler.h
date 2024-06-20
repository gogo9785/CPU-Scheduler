// here we will define the data how the process looks like and write all the function declarations
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define MAX_PROCESSES 100

// now lets define the PCB

class Process {
public:
    int processID; // unique for every process
    int burstTime; // time req for execution
    int priority; // s1 means system process with 1st priority
    int arrivalTime; // time when process added in ready queue
    int remainingTime; // it is used for preemptive algos
    int waitingTime; // how much time process spend in ready queue
    int turnaroundTime; // updated once when the process gets completed


    // Default constructor
    Process(){
        processID=0 ; burstTime=0 ; priority=0 ; arrivalTime=0 ;remainingTime= 0 ; waitingTime=0 ; turnaroundTime=0 ;
    } 
        
    // Parameterized constructor
    Process( int id, int bt, int prio, int at){processID=id ;burstTime=bt ;priority=prio ;arrivalTime = at ;remainingTime = bt ;waitingTime=0 ;turnaroundTime=0 ;}


    // Member function to display process details 
    void display() const {
        std::cout << "Process ID: " << processID << std::endl;
        std::cout << "Burst Time: " << burstTime << std::endl;
        std::cout << "Priority: " << priority << std::endl;
        std::cout << "Arrival Time: " << arrivalTime << std::endl;
        std::cout << "Remaining Time: " << remainingTime << std::endl;
        std::cout << "Waiting Time: " << waitingTime << std::endl;
        std::cout << "Turnaround Time: " << turnaroundTime << std::endl;
    }
};


// Define Process Queue structure
class ProcessQueue {
public:
    vector<Process> processes;
    vector<Process> system_Processes;
    vector<Process> interactive_Processes;
    vector<Process> background_Processes;

    ProcessQueue(){} 



    

};


// Function declarations

// Function to read process details
void readInput(int &algo ,ProcessQueue &queue,string & filename,int & time_quantum,int &time_limit);


// Scheduling algorithm implementations
void FCFS(vector<Process> & processes);
void SJFNP(vector<Process> & processes);
void SJFP(vector<Process> & processes,int time_quantum);
void Priority_scheduling_np(vector<Process> & processes);
void Priority_scheduling_p(vector<Process> & processes,int time_quantum);
void RR(vector<Process> & processes,int time_quantum);
void MLQ(ProcessQueue &queue,int time_quantum) ;
void MLFQ(ProcessQueue &queue,int time_quantum,int time_limit) ;




#endif // SCHEDULER_H