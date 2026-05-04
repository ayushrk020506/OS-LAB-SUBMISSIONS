#include <stdio.h>
#include <math.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    float Ci; // Execution time
    float Ti; // Period
    int priority;
} Task;

// Function to sort tasks by period (ascending)
void sortByPeriod(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].Ti > tasks[j].Ti) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

// Function to assign priorities
void assignPriorities(Task tasks[], int n) {
    sortByPeriod(tasks, n);
    for (int i = 0; i < n; i++) {
        tasks[i].priority = i + 1; // 1 = highest priority
    }
}

// Function to calculate CPU utilization
float calculateUtilization(Task tasks[], int n) {
    float U = 0.0;
    for (int i = 0; i < n; i++) {
        U += (tasks[i].Ci / tasks[i].Ti);
    }
    return U;
}

// Function to calculate RMS bound
float calculateBound(int n) {
    return n * (pow(2, 1.0 / n) - 1);
}

int main() {
    int n;
    Task tasks[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input tasks
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter Execution Time (C%d): ", i + 1);
        scanf("%f", &tasks[i].Ci);
        printf("Enter Period (T%d): ", i + 1);
        scanf("%f", &tasks[i].Ti);
    }

    // Step 1: Calculate CPU Utilization
    float U = calculateUtilization(tasks, n);

    // Step 2: Calculate RMS Bound
    float bound = calculateBound(n);

    // Step 3: Check Schedulability
    printf("\nCPU Utilization (U) = %.4f\n", U);
    printf("RMS Bound = %.4f\n", bound);

    if (U <= bound) {
        printf("Schedulable using RMS\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n");
    }

    // Step 4: Assign Priorities
    assignPriorities(tasks, n);

    printf("\nTask Priorities (Lower number = Higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d: Period = %.2f, Priority = %d\n",
               tasks[i].id, tasks[i].Ti, tasks[i].priority);
    }

    // Step 5: Simple Simulation (one cycle)
    printf("\nScheduling Order (Simulation):\n");
    printf("Executing tasks based on priority:\n");

    for (int i = 0; i < n; i++) {
        printf("Task %d (Priority %d) is executed\n",
               tasks[i].id, tasks[i].priority);
    }

    return 0;
}
