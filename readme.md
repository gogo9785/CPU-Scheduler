# CPU scheduler

## Time Definitions

1. **Throughput**: Number of processes completed per unit time.
2. **Arrival Time (AT)**: Time when a process arrives at the ready queue.
3. **Burst Time (BT)**: The time required by the process for its execution.
4. **Completion Time (CT)**: Time at which the process completes its execution.
5. **Turnaround Time (TAT)**: Time taken from the first time a process enters the ready state until it terminates.
   - Formula: `TAT = CT - AT`
6. **Wait Time (WT)**: Time a process spends waiting in the ready queue.
   - Formula: `WT = TAT - BT`
7. **Response Time**: Time duration between the process entering the ready queue and getting the CPU for the first time.

## Goals of Scheduling Algorithms

1. **Minimum Turnaround Time**: Reduce the time from when a process enters the ready queue until it terminates.
2. **Minimum Wait Time**: Reduce the time a process spends waiting in the ready queue.
3. **Minimum Response Time**: Reduce the time from when a process enters the ready queue to when it first gets CPU time.
4. **Maximum Throughput**: Increase the number of processes completed per unit time.

## Scheduling Algorithms

1. **First-Come, First-Served (FCFS)**: `input code: 1`
   - The process which arrives first will execute first and complete its execution.
   - It is a non-preemptive scheduling algorithm.

2. **Shortest Job First (SJF)**: `input code: 2 (preemptive), 3 (non-preemptive)`
   - Processes are sorted based on their burst time. The process with the shortest burst time executes first.
   - It can be either preemptive or non-preemptive. In the preemptive version, it's called Shortest Remaining Time First (SRTF).

3. **Priority Scheduling**: `input code: 4 (preemptive), 5 (non-preemptive)`
   - Processes are scheduled based on their priority. Higher priority processes execute first.
   - It can be either preemptive or non-preemptive.

4. **Round Robin Scheduling (RR)**: `input code: 6`
   - A preemptive version of FCFS where each process gets executed for a fixed time slice (quantum). After the time slice, the process is moved to the back of the queue if it's not completed.
   - The time quantum is a crucial parameter that affects the performance of the scheduler.

5. **Multi-Level Queue Scheduling (MLQ)**: `input code: 7`
   - Processes are divided into multiple ready queues based on their type:
     1. System Processes
     2. Interactive Processes (I/O bound)
     3. Background Processes
   - Each queue follows its own scheduling algorithm.
   - Processes are permanently assigned to a queue based on some property of the process.
   - The ready queues are:
     - **SP Queue**: System processes queue
     - **IP Queue**: Interactive processes queue
     - **BP Queue**: Background processes queue

6. **Multi-Level Feedback Queue Scheduling (MLFQ)**: `input code: 8`
   - Processes can move between queues based on their behavior. The aim is to separate processes according to the characteristics of their burst time.
   - If a process uses too much CPU time, it will be moved to a lower priority queue.
   - I/O bound and interactive processes remain in higher-priority queues.
   - A process that waits too long in a lower-priority queue may be moved to a higher-priority queue. This form of aging prevents starvation.

## Project Requirement

1. The scheduling of processes is done by 3 algorithms in MLQ and MLFQ:
   - For system processes, implement preemptive priority scheduling.
   - For interactive processes, implement Round Robin scheduling.
   - For background processes, implement FCFS scheduling.

2. If a user wants to schedule the process with a particular algorithm, refer to the corresponding sample input file.

## Directions to Run the Code

1. Clone this repo.
2. Open the `testcases` directory and copy the absolute path of `testcase.txt`.
3. Paste it in the `main.cpp`.
4. Write your custom test case or copy any sample test case in `testcases/testcase.txt`.
5. Run `g++ main.cpp Algos.cpp readProcess.cpp` in the terminal.
6. If you run the MLQ algorithm, check the `_output_MLQ.txt` file inside the `output` directory.
