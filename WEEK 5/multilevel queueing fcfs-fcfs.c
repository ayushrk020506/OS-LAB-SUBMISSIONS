#include <stdio.h>

int main()
{
    int n, i, j;

    int pid[20], at[20], bt[20], type[20];
    int ct[20], tat[20], wt[20];

    int sys[20], user[20];
    int sysCount = 0, userCount = 0;

    int time = 0;

    // Gantt Chart
    int ganttP[50];   // store PID (use -1 for Idle)
    int ganttT[50];   // store time
    int g = 0;

    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("PID: ");
        scanf("%d", &pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &type[i]);
    }

    // Separate queues
    for(i = 0; i < n; i++)
    {
        if(type[i] == 0)
            sys[sysCount++] = i;
        else
            user[userCount++] = i;
    }

    // Sort System Queue (by AT)
    for(i = 0; i < sysCount - 1; i++)
    {
        for(j = i + 1; j < sysCount; j++)
        {
            if(at[sys[i]] > at[sys[j]])
            {
                int temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }

    // Sort User Queue (by AT)
    for(i = 0; i < userCount - 1; i++)
    {
        for(j = i + 1; j < userCount; j++)
        {
            if(at[user[i]] > at[user[j]])
            {
                int temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }

    // ---- Execute System Queue ----
    for(i = 0; i < sysCount; i++)
    {
        int p = sys[i];

        if(time < at[p])
        {
            // Idle time
            ganttP[g] = -1;
            ganttT[g++] = time;

            time = at[p];
        }

        ganttP[g] = pid[p];
        ganttT[g++] = time;

        time += bt[p];
        ct[p] = time;

        tat[p] = ct[p] - at[p];
        wt[p] = tat[p] - bt[p];
    }

    // ---- Execute User Queue ----
    for(i = 0; i < userCount; i++)
    {
        int p = user[i];

        if(time < at[p])
        {
            // Idle time
            ganttP[g] = -1;
            ganttT[g++] = time;

            time = at[p];
        }

        ganttP[g] = pid[p];
        ganttT[g++] = time;

        time += bt[p];
        ct[p] = time;

        tat[p] = ct[p] - at[p];
        wt[p] = tat[p] - bt[p];
    }

    ganttT[g] = time;

    // ---- Display Table ----
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], type[i],
               ct[i], tat[i], wt[i]);

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    // ---- Averages ----
    printf("\nAverage Waiting Time: %.2f", avgWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);

    // ---- Gantt Chart ----
    printf("\nGantt Chart:\n| ");
    for(i = 0; i < g; i++)
    {
        if(ganttP[i] == -1)
            printf("Idle | ");
        else
            printf("P%d | ", ganttP[i]);
    }

    printf("\n");

    for(i = 0; i < g; i++)
    {
        printf("%d   ", ganttT[i]);
    }
    printf("%d\n", ganttT[g]);

    return 0;
}
