#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Selection.h"

void storerandompop(int *population , int &pdx , int *randompop , int &rdx , int nodes , int &power ,int *cost , int &cdx )
{

	//To store the random population in randompop array
	if(pdx == (nodes+2)*power)
	{
		//pdx is at index (nodes+2)*power
		if(power%2 == 0)
		{
			//power is even
			++power;
		}
		else
		{
			//power is odd
			++power;
			for(int i=pdx-(nodes+2) ; i<pdx; i++)
			{
				//Copy the random path of population to randompop array
				randompop[rdx] = population[i];
				++rdx;
			}
			//storing the random popualtion
			fillcost(randompop,rdx,nodes,cost,cdx);
			

		}
		
	}
		
	

}

void printrandompop(int *randompop , int &rdx , int nodes)
{   
	//To print the random population
	printf("Random population till now: \n");
	int idx = 0;
	for(int i=0;i<rdx;i++)
	{
		//Giving new line after each path in population.
		if(i == idx + nodes + 2)
		{
			printf("\n");
			idx = i;
		}
		printf("%d ",randompop[i]);
	}
	printf("\n");
	printf("\n");
}
