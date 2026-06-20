# CPU Scheduling Algorithms Simulator

A C implementation of six classic CPU scheduling algorithms, built around a shared `Process` model and an interactive command-line menu.

Given a set of processes (priority, arrival time, burst time), the program simulates and prints the exact execution timeline produced by each algorithm — useful for visualizing how scheduling decisions change process wait/turnaround time.

## Algorithms implemented

| # | Algorithm | Type | Selection rule |
|---|---|---|---|
| 1 | First-Come, First-Served (FCFS) | Non-preemptive | Earliest arrival time |
| 2 | Shortest Job First (SJF) | Non-preemptive | Shortest burst time among arrived processes |
| 3 | Priority Scheduling | Non-preemptive | Lowest priority value among arrived processes |
| 4 | Round Robin | Preemptive | FIFO ready queue, fixed time quantum per turn |
| 5 | Shortest Remaining Time First (SRTF) | Preemptive | Shortest *remaining* burst time, re-evaluated every time unit |
| 6 | Preemptive Priority | Preemptive | Lowest priority value, re-evaluated every time unit |

## Build & run

Requires `gcc` (or any C99 compiler).

```bash
make          # builds ./scheduler
make run      # builds and runs in one step
make clean    # removes the binary
```

Or compile directly:

```bash
gcc -Wall -Wextra -std=c99 -o scheduler src/scheduling_algorithms.c
./scheduler
```

## Usage

The program prompts for the number of processes, then for each process's **priority, arrival time, and burst time** (in that order — priority is ignored by algorithms that don't use it, but the prompt still asks for it to keep input format consistent across all six modes). It then asks which algorithm to run.

```
Enter the number of processes: 3
Enter details for Process 1 (Priority Arrival Time Burst Time): 2 0 5
Enter details for Process 2 (Priority Arrival Time Burst Time): 1 1 3
Enter details for Process 3 (Priority Arrival Time Burst Time): 3 2 8
Choose scheduling option (1 for FCFS, 2 for SJF, 3 for Priority, 4 for Round Robin, 5 for Preemptive SJF, 6 for Preemptive Priority): 3
Process 1 is executing from 0 to 5
Process 2 is executing from 5 to 8
Process 3 is executing from 8 to 16
```

More worked examples for every algorithm (including Round Robin and preemptive SRTF) are in [`examples/sample_runs.md`](examples/sample_runs.md).

## Design notes

- All six algorithms operate on the same `Process` struct, so adding a new policy just means writing one more function with the same `(Process[], int)` signature.
- **FCFS** sorts processes by `arrival_time` internally (stable sort, so ties keep input order) rather than assuming the input is pre-sorted.
- **Round Robin** is implemented with a real FIFO ready queue: processes only enter the queue once their `arrival_time` has passed, newly-arrived processes are enqueued before a process is re-queued after its slice, and the CPU idles forward to the next arrival if the queue empties early. Verified leak-free under `valgrind --leak-check=full`.
- **SRTF** and **Preemptive Priority** re-evaluate the ready set every single time unit, which is the simplest correct way to model preemption at this scale (fine for small process counts; a real OS would use an event-driven approach).

## Project structure

```
.
├── src/
│   └── scheduling_algorithms.c   # all six algorithms + interactive CLI
├── examples/
│   └── sample_runs.md            # real captured output for every algorithm
└── Makefile
```

## Possible extensions

- Compute and print average waiting time / turnaround time per algorithm
- Add a Gantt-chart style visual output
- Support multilevel feedback queues
- Take input from a file/CLI args instead of interactive `scanf`

## License

[MIT](LICENSE)
