#include <stdio.h>

void display(int allocation[], int processSize[], int processes, char name[])
{
    int i;

    printf("\n%s\n", name);
    printf("Process\tSize\tBlock\n");

    for(i = 0; i < processes; i++)
    {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void firstFit(int blockSize[], int blocks,
              int processSize[], int processes)
{
    int allocation[20];
    int i, j;

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        for(j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    display(allocation, processSize, processes, "FIRST FIT");
}

void bestFit(int blockSize[], int blocks,
             int processSize[], int processes)
{
    int allocation[20];
    int i, j;

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        int best = -1;

        for(j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(best == -1 ||
                   blockSize[j] < blockSize[best])
                {
                    best = j;
                }
            }
        }

        if(best != -1)
        {
            allocation[i] = best;
            blockSize[best] -= processSize[i];
        }
    }

    display(allocation, processSize, processes, "BEST FIT");
}

void worstFit(int blockSize[], int blocks,
              int processSize[], int processes)
{
    int allocation[20];
    int i, j;

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        int worst = -1;

        for(j = 0; j < blocks; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(worst == -1 ||
                   blockSize[j] > blockSize[worst])
                {
                    worst = j;
                }
            }
        }

        if(worst != -1)
        {
            allocation[i] = worst;
            blockSize[worst] -= processSize[i];
        }
    }

    display(allocation, processSize, processes, "WORST FIT");
}

int main()
{
    int blocks, processes;
    int i;

    int blockSize[20];
    int blockCopy1[20];
    int blockCopy2[20];

    int processSize[20];

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);

    printf("Enter block sizes:\n");

    for(i = 0; i < blocks; i++)
    {
        scanf("%d", &blockSize[i]);

        blockCopy1[i] = blockSize[i];
        blockCopy2[i] = blockSize[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    printf("Enter process sizes:\n");

    for(i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    firstFit(blockSize, blocks,
             processSize, processes);

    bestFit(blockCopy1, blocks,
            processSize, processes);

    worstFit(blockCopy2, blocks,
             processSize, processes);

    return 0;
}