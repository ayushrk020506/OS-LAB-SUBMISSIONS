#include <stdio.h>

void printFrames(int f[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(f[i] == -1)
            printf("- ");
        else
            printf("%d ", f[i]);
    }

    printf("\n");
}

void FIFO(int ref[], int n, int frames)
{
    int f[20];
    int i, j;

    int pos = 0;
    int pf = 0;

    for(i = 0; i < frames; i++)
        f[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for(i = 0; i < n; i++)
    {
        int hit = 0;

        for(j = 0; j < frames; j++)
        {
            if(f[j] == ref[i])
            {
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            f[pos] = ref[i];
            pos = (pos + 1) % frames;

            pf++;

            printFrames(f, frames);
        }
    }

    printf("FIFO Page Faults = %d\n", pf);
}

void LRU(int ref[], int n, int frames)
{
    int f[20];
    int recent[20];

    int i, j;
    int time = 0;
    int pf = 0;

    for(i = 0; i < frames; i++)
    {
        f[i] = -1;
        recent[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for(i = 0; i < n; i++)
    {
        int hit = 0;

        for(j = 0; j < frames; j++)
        {
            if(f[j] == ref[i])
            {
                hit = 1;
                recent[j] = ++time;
                break;
            }
        }

        if(!hit)
        {
            int pos = 0;

            for(j = 1; j < frames; j++)
            {
                if(recent[j] < recent[pos])
                    pos = j;
            }

            f[pos] = ref[i];
            recent[pos] = ++time;

            pf++;

            printFrames(f, frames);
        }
    }

    printf("LRU Page Faults = %d\n", pf);
}

void Optimal(int ref[], int n, int frames)
{
    int f[20];
    int i, j;

    int pf = 0;

    for(i = 0; i < frames; i++)
        f[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for(i = 0; i < n; i++)
    {
        int hit = 0;

        for(j = 0; j < frames; j++)
        {
            if(f[j] == ref[i])
            {
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            int pos = 0;
            int farthest = -1;

            for(j = 0; j < frames; j++)
            {
                int k;

                for(k = i + 1; k < n; k++)
                {
                    if(f[j] == ref[k])
                        break;
                }

                if(k > farthest)
                {
                    farthest = k;
                    pos = j;
                }
            }

            f[pos] = ref[i];

            pf++;

            printFrames(f, frames);
        }
    }

    printf("Optimal Page Faults = %d\n", pf);
}

int main()
{
    int n, frames;
    int ref[50];

    int i;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    printf("Enter reference string: ");

    for(i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    FIFO(ref, n, frames);

    LRU(ref, n, frames);

    Optimal(ref, n, frames);

    return 0;
}