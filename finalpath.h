#include <stdio.h>
#include <stdlib.h>

void printfinalpath(int *randompop , int rdx , int nodes)
{
	int *finalcost = (int *) malloc(500 * sizeof *finalcost);
	int *finalpath = (int*) malloc(10 * sizeof *finalpath);
	int fdx = 0;
	int fpath = 0;
	int checkidx = 1;
	for(int i=0;i<rdx;i++)
	{
		if( i == checkidx + nodes)
		{
			finalcost[fdx] = randompop[i];
			++fdx;
			checkidx = i + 2;
		}
	}
	int mincost = 1000;
	for(int i=0 ;i<fdx;i++)
	{
		if(finalcost[i] < mincost)
		{
			mincost = finalcost[i];
		}
	}

	for(int i=0;i<rdx;i++)
	{
		if(randompop[i] == mincost)
		{
			for(int start = i - (nodes + 1) ; start < i ; ++start)
			{
				finalpath[fpath] = randompop[start];
				++fpath;
			}
			break;
		}
	}
	printf("\n\n");
	printf("After performing 3 iterations on the map for a random population :");
	printf("\n");
	printf("OPTIMAL ROUTE FOR SHIPMENT IS :  ");
	for(int i=0 ; i<fpath;i++)
	{
		printf("%d->",finalpath[i]);
	}
	printf("\n");
	printf("COST FOR ROUTE IS: ");
	printf("%d",mincost);
	printf("\n\n");

}