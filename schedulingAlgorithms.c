#include <stdio.h>
#include <stdbool.h>


typedef struct Process {
    int pid;         // Process ID
    int priority;    // Priority (Lower value indicates higher priority)
    int burst_time;  // Burst time
    int arrival_time; // Arrival time
    int remaining_burst_time; // Remaining burst time
} Process;

void fcfs(Process processes[], int num_processes) {
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) {
        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }


        current_time += processes[i].burst_time;

        // Print the execution
        printf("Process %d is executing from %d to %d\n", processes[i].pid, current_time - processes[i].burst_time, current_time);
    }
}

void sjf(Process processes[], int num_processes) {
    int current_time = 0;
    int completed_processes = 0;
    int selected_process = -1;

    while (completed_processes < num_processes) {
        int shortest_burst_time = 9999; // Initialize with a high value

        // Find the process with shortest burst time and is ready to execute
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
                if (processes[i].remaining_burst_time < shortest_burst_time) {
                    shortest_burst_time = processes[i].remaining_burst_time;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue; // No process is ready to execute, move to next time unit
        }

        current_time += processes[selected_process].burst_time;
        processes[selected_process].remaining_burst_time=0;
        completed_processes++;

        // Print the execution
        printf("Process %d is executing from %d to %d\n", processes[selected_process].pid, current_time - processes[selected_process].burst_time, current_time);
    }
}

void priority(Process processes[], int num_processes) {
   int current_time = 0;
    int completed_processes = 0;
    int selected_process = -1;

    while (completed_processes < num_processes) {
        int highest_priority = 9999; // Initialize with a high value

        // Find the process with shortest burst time and is ready to execute
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
                 if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue; // No process is ready to execute, move to next time unit
        }

        current_time += processes[selected_process].burst_time;
        processes[selected_process].remaining_burst_time=0;
        completed_processes++;

        // Print the execution
        printf("Process %d is executing from %d to %d\n", processes[selected_process].pid, current_time - processes[selected_process].burst_time, current_time);
    }
}

void round_robin(Process processes[], int num_processes, int time_quantum) {
    int remaining_burst_time[num_processes];
    for (int i = 0; i < num_processes; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (remaining_burst_time[i] > 0) {
                if (remaining_burst_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                } else {
                    current_time += remaining_burst_time[i];
                    remaining_burst_time[i] = 0;
                    completed_processes++;
                }

                // Print the execution
                printf("Process %d is executing from %d to %d\n", processes[i].pid, current_time - time_quantum, current_time);
            }
        }
    }
}
void preemptivePriority(Process processes[], int num_processes){

    int current_time = 0;

    while (true) {
        int highest_priority = 9999; // Initialize with a high value
        int selected_process = -1;

        // Find the process with highest priority and is ready to execute
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }

            }

        }

        if (selected_process == -1)
            break;

        // Execute the selected process for 1 unit of time
        processes[selected_process].remaining_burst_time--;
        current_time++;

        // Print the execution
        printf("Process %d is executing till time %d\n", processes[selected_process].pid, current_time);

        // Check if process is completed
        if (processes[selected_process].remaining_burst_time == 0) {
            printf("Process %d completed at time %d\n", processes[selected_process].pid, current_time);
        }
    }
}

void preemptiveSJF(Process processes[], int num_processes){

    int current_time = 0;
    int completed_processes = 0;
    int selected_process = -1;

    while (completed_processes < num_processes) {
        int shortest_burst_time = 9999; // Initialize with a high value

        // Find the process with shortest burst time and is ready to execute
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
                if (processes[i].remaining_burst_time < shortest_burst_time) {
                    shortest_burst_time = processes[i].remaining_burst_time;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue; // No process is ready to execute, move to next time unit
        }

        // Execute the selected process for 1 unit of time
        processes[selected_process].remaining_burst_time--;
        current_time++;

        // Print the execution
        printf("Process %d is executing till time %d\n", processes[selected_process].pid, current_time);

        // Check if process is completed
        if (processes[selected_process].remaining_burst_time == 0) {
            completed_processes++;
            printf("Process %d completed at time %d\n", processes[selected_process].pid, current_time);
        }
    }
}


int main() {
    int num_processes;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process processes[num_processes];

    // Input process details
    for (int i = 0; i < num_processes; i++) {
        printf("Enter details for Process %d (Priority Arrival Time Burst Time): ", i + 1);
        scanf("%d %d %d", &processes[i].priority, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_burst_time = processes[i].burst_time;
        processes[i].pid = i + 1; // Assign unique PID
    }

    int choice;

    printf("Choose scheduling option (1 for FCFS, 2 for SJF, 3 for Priority, 4 for Round Robin, 5 for Preemptive SJF, 6 for Preemptive Priority): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, num_processes);
            break;
        case 2:
            sjf(processes, num_processes);
            break;
        case 3:
            priority(processes, num_processes);
            break;
        case 4:
            {
                int time_quantum;
                printf("Enter time quantum for Round Robin: ");
                scanf("%d", &time_quantum);
                round_robin(processes, num_processes, time_quantum);
            }
            break;
        case 5:
            preemptiveSJF(processes, num_processes);
            break;
        case 6:
            preemptivePriority(processes, num_processes);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
