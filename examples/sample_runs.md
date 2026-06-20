# Example Runs

All output below is real program output, captured from the compiled binary.

## Process set used in most examples

| PID | Priority | Arrival Time | Burst Time |
|-----|----------|--------------|------------|
| 1   | 3        | 0            | 6          |
| 2   | 1        | 1            | 4          |
| 3   | 4        | 2            | 2          |
| 4   | 2        | 3            | 1          |

(Lower priority number = higher priority.)

---

## FCFS (First-Come, First-Served)

Input order doesn't have to match arrival order — FCFS sorts by `arrival_time`
internally. Here Process 2 (entered second) actually arrives first and is
correctly scheduled first:

```
$ ./scheduler
Enter the number of processes: 3
Enter details for Process 1 (Priority Arrival Time Burst Time): 0 2 5
Enter details for Process 2 (Priority Arrival Time Burst Time): 0 0 3
Enter details for Process 3 (Priority Arrival Time Burst Time): 0 4 2
Choose scheduling option (...): 1
Process 2 is executing from 0 to 3
Process 1 is executing from 3 to 8
Process 3 is executing from 8 to 10
```

## Priority Scheduling (non-preemptive)

```
$ ./scheduler
Enter the number of processes: 4
Enter details for Process 1 (Priority Arrival Time Burst Time): 3 0 6
Enter details for Process 2 (Priority Arrival Time Burst Time): 1 1 4
Enter details for Process 3 (Priority Arrival Time Burst Time): 4 2 2
Enter details for Process 4 (Priority Arrival Time Burst Time): 2 3 1
Choose scheduling option (...): 3
Process 1 is executing from 0 to 6
Process 2 is executing from 6 to 10
Process 4 is executing from 10 to 11
Process 3 is executing from 11 to 13
```

## Round Robin (time quantum = 2)

Same 4-process set. Each process gets a fair 2-unit slice, cycling back
through the ready queue until everyone finishes:

```
$ ./scheduler
Enter the number of processes: 4
Enter details for Process 1 (Priority Arrival Time Burst Time): 3 0 6
Enter details for Process 2 (Priority Arrival Time Burst Time): 1 1 4
Enter details for Process 3 (Priority Arrival Time Burst Time): 4 2 2
Enter details for Process 4 (Priority Arrival Time Burst Time): 2 3 1
Choose scheduling option (...): 4
Enter time quantum for Round Robin: 2
Process 1 is executing from 0 to 2
Process 2 is executing from 2 to 4
Process 3 is executing from 4 to 6
Process 3 completed at time 6
Process 1 is executing from 6 to 8
Process 4 is executing from 8 to 9
Process 4 completed at time 9
Process 2 is executing from 9 to 11
Process 2 completed at time 11
Process 1 is executing from 11 to 13
Process 1 completed at time 13
```

## Preemptive Shortest Job First (SRTF)

Two processes — P2 arrives later but has a shorter burst, so it preempts P1:

```
$ ./scheduler
Enter the number of processes: 2
Enter details for Process 1 (Priority Arrival Time Burst Time): 0 0 6
Enter details for Process 2 (Priority Arrival Time Burst Time): 0 2 2
Choose scheduling option (...): 5
Process 1 is executing till time 1
Process 1 is executing till time 2
Process 2 is executing till time 3
Process 2 is executing till time 4
Process 2 completed at time 4
Process 1 is executing till time 5
Process 1 is executing till time 6
Process 1 is executing till time 7
Process 1 is executing till time 8
Process 1 completed at time 8
```
