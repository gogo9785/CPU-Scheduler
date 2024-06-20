#include <iostream>
#include "Scheduler.h"
using namespace std ;



// REPLACE THE FILE PATH
string input_file="C:/Users/HP/programming/3 c++ notes/core c++ concept/lect8 OS/projrct/CPU scheduler/testcases/testcase.txt" ;


int main() {
    ProcessQueue queue = ProcessQueue() ;
    int algo=1 ; 
    int time_quantum=1,time_limit=10  ;

    readInput(algo ,queue,input_file,time_quantum,time_limit);

    switch (algo) {
        case 1:
            FCFS(queue.processes) ;
            break;
        case 2:
            SJFNP(queue.processes) ;
            break;
        case 3:
            SJFP(queue.processes,time_quantum) ;
            break;
        case 4:
            Priority_scheduling_np(queue.processes) ;
            break;
        case 5:
            Priority_scheduling_p(queue.processes,time_quantum) ;
            break;
        case 6:
            RR(queue.processes,time_quantum) ;
            break;
        case 7:
            MLQ(queue,time_quantum) ;
            break;
        case 8:
            MLFQ(queue,time_quantum,time_limit) ;
            break;
        default:
            MLFQ(queue,time_quantum,time_limit) ;
            break;
    }
    return 0;
}