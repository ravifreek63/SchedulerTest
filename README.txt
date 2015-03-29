Scheduling policy:
The project creates a scheduler framework. The scheduling policy used is earliest deadline first (deadline here being the sum of time at which the job was scheduled + number of steps in the task). The requests are sorted by the 
time at which they require to get completed. Those that have the earliest deadline are prioritized first. If two different requests
have same deadline then the request with lower resource requirements is prioritized. 


Example:
We measure the average waiting time. The input is the following job requests
(7,7), (7,7), (1,1), (1,1).
The cluster has two nodes with 7 resource units each.
With a first come first  serve the total waiting time is 7 seconds and job completion time of 8 seconds.
With earliest deadline first, the total running time is 8 seconds and total waiting time 1 second.
This is shown in the output also.
The output is as follows:
Dispatching request , Job id = 3, units required = 1, at time = 0, node Id = 1
Dispatching request , Job id = 4, units required = 1, at time = 0, node Id = 1
Dispatching request , Job id = 1, units required = 7, at time = 0, node Id = 2
Dispatching request , Job id = 2, units required = 7, at time = 1, node Id = 1
Cumulative Waiting Time = 1

The simulator contains:
1) A scheduler thread that checks a request queue(built as a priority queue) for any new requests that come in.
The scheduler takes a batch (currently = 1) of requests and iterates through a mapping of nodeIDs to resourcesUnits available.
If a node with sufficient resources is found then the job is allocated else the job is pushed to a pending queue of jobs. 
At the next iteration the scheduler first scans the pending queue then requests the next set of k jobs from the set of unscheduled jobs.   
2) Another thread (dispatcherThread) which is a dispatcher thread keeps track of when a job gets over and essentially simulates the job.
3) Another thread (timeClock) keeps track of the logical time.
4) A thread (not used in the example) creates a stream of random requests that is then monitored by the scheduler thread.


The config file contains the following order:
- total time for the simulation
- total number of nodes
- total resources per node