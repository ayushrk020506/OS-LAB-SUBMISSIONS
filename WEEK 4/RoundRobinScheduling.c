#include <stdio.h>

int main()
{
    int n,i,time=0,quantum;
    int at[20],bt[20],rt[20],ct[20],wt[20],tat[20];
    int rq[100];
    int front=0,rear=0;
    int visited[20]={0};
    int completed=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("AT P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("BT P%d: ",i+1);
        scanf("%d",&bt[i]);

        rt[i]=bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&quantum);

    /* Move first arriving processes to Ready Queue */
    for(i=0;i<n;i++)
    {
        if(at[i]==0)
        {
            rq[rear++]=i;
            visited[i]=1;
        }
    }
    printf("\nGantt Chart:\n| ");

    while(completed<n)
    {
        if(front==rear)
        {
            time++;
            for(i=0;i<n;i++)
            {
                if(at[i]<=time && visited[i]==0)
                {
                    rq[rear++]=i;
                    visited[i]=1;
                }
            }
            continue;
        }

        int p=rq[front++];

        printf("P%d | ",p+1);

        int exec;

        if(rt[p]>quantum)
            exec=quantum;
        else
            exec=rt[p];

        time+=exec;
        rt[p]-=exec;

        /* Check new arrivals */
        for(i=0;i<n;i++)
        {
            if(at[i]<=time && visited[i]==0)
            {
                rq[rear++]=i;
                visited[i]=1;
            }
        }

        if(rt[p]>0)
        {
            rq[rear++]=p;
        }
        else
        {
            completed++;
            ct[p]=time;
        }
    }

    printf("\n");

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }

    printf("\nP\tAT\tBT\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
    }

    float awt=0,atat=0;

    for(i=0;i<n;i++)
    {
        awt+=wt[i];
        atat+=tat[i];
    }

    printf("\nAverage Waiting Time: %.2f",awt/n);
    printf("\nAverage Turnaround Time: %.2f\n",atat/n);
}
