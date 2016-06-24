#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <math.h>


int x , n , h = 0;
int start;
int end;
MPI_Status status;
int rank, size;


void generate(int,int); // generate prime numbers less than given number
void value_format();

int main (argc, argv)
     int argc;
     char *argv[];
{

    MPI_Init (&argc, &argv);        /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);  /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size);  /* get number of processes */

    value_format();
    generate(start,end);
    //show();
    MPI_Finalize();
    return 0;
}

void value_format()
{
    int i;
    if (rank==0)
    {
        printf("Enter A Number ! \n");
        scanf("%d" , &n);
        int j;
        for(j=1; j<size; j++)
        {
            MPI_Send(&n,1,MPI_INT,j,1,MPI_COMM_WORLD);
        }
        start = (n/size);
        start = start*rank;
        end = start + (n/size)-1;
        printf("Rank = %d where range from %d to %d \n",rank,start,end);

    }
    else

    {
        MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        start = (n/size);
        start = start*rank;
        if(rank==size-1)
            end = n;
        else
            end = start + (n/size)-1;
        printf("Rank = %d where range from %d to %d \n",rank,start,end);
    }
}


void generate(int x,int y)
{
    int *ptr;
    int i,j;
    ptr = (int*) malloc(n * sizeof(int));

    for (i = x ; i < y ; i++)
    {
        for (j = 2 ; j < i ; j++)
        {
            if (i % j == 0){ break; }
            else if (i == j+1)
            {
                ptr[h] = i;
                h++;
            }
        }
    }

    for(i = 0 ; i < h ; i++)
    {
        printf("%d \n" , ptr[i]);
    }
}

