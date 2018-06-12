#include <stdio.h>
#include <stdlib.h>


void mutatechild(int *childpool , int &childidx , int *randompop , int &rdx , int nodes , int total , int &cdx , int *cost ,  int **graph , int &scdx , int *selectedcost , int min1 , int min2 , int min3 , int thres)
{
	int i = 0;
	int j = nodes;
	int tmp = childpool[i+1];
	childpool[i+1] = childpool[j-1];
	childpool[j-1] = tmp;

	int mutatechildwt = 0;

	for(int idx=0; idx<nodes ; idx++)
	{ 
		mutatechildwt = mutatechildwt + graph[childpool[idx]][childpool[idx+1]];
	}

	if(mutatechildwt <= thres)
	{
		
		
		cost[cdx] = mutatechildwt;
		++cdx;
		selectedcost[scdx] = mutatechildwt;
		++scdx;
		bool flag = false;
		for(int idx = 0;idx<rdx;idx++)
		{
			if(randompop[idx] == mutatechildwt)
			{
				flag = true;
			}
		}
		if(flag == false)
		{
			for(int index=0;index<childidx;++index)
			{
				randompop[rdx] = childpool[index];
				++rdx;
			}
			randompop[rdx] = mutatechildwt;
			++rdx;
		
		}
		printf("\n Child mutated with cost: %d",mutatechildwt);
		printf("\n");

	

		
		
	}
	else
	{
		
		printf("Child is not fit after 1st mutation \n");

		//Child is not fit after mutation 
		//Weight of child is more than threshold
		//again restore the original child;
		int tmp = childpool[i+1];
		childpool[i+1] = childpool[j-1];
		childpool[j-1] = tmp;
		++i;
		--j;
		int tmp1 = childpool[i+1];
		childpool[i+1] = childpool[j-1];
		childpool[j-1] = tmp1;


		
		int secondmutatewt = 0;
		for(int idx=0; idx<nodes ; idx++)
		{ 
			secondmutatewt = secondmutatewt + graph[childpool[idx]][childpool[idx+1]];
		}
		if(secondmutatewt <= total/cdx)
		{
			
			cost[cdx] = secondmutatewt;
			++cdx;
			selectedcost[scdx] = secondmutatewt;
			++scdx;
			bool flag = false;
			for(int idx = 0;idx<rdx;idx++)
			{
				if(randompop[idx] == secondmutatewt)
				{
					flag = true;
				}
			}
			if(flag == false)
			{
				for(int index=0;index<childidx;++index)
				{
					randompop[rdx] = childpool[index];
					++rdx;
				}
				randompop[rdx] = secondmutatewt;
				++rdx;
			
			}
			printf(" \n Child after 2nd mutation mutated with cost: %d",secondmutatewt);
			printf("\n");
		}

		else
		{
				printf("Child is not fit to add in popualtion \n");
				
				int costcnt = 0;
				for(int i=0;i<scdx;i++)
				{
					++costcnt;
				}
				if(costcnt  > 2)
				{
					printf("Choosing new set of parents \n");
					if(min1 < min2)
					{
						min3 = min2;
					}
					else
					{
						min3 = min1;
					}
				}
		}




	}




}