#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "crossover.h"
#include "mutation.h"
#include "finalpath.h"


void fillcost(int *randompop , int &rdx , int nodes , int *cost , int &cdx)
{

	cost[cdx] = randompop[rdx-1];
	++cdx; 

}

void printcost(int **graph , int *population , int &pdx , int *cost , int &cdx , int *selectedcost , int scdx , int *randompop , int &rdx , int nodes)
{
	//I am not printing the all random paths cost
	// for(int i=0;i<cdx;i++)
	// {
	// 	printf("%d \n" , cost[i]);	
	// }

	printf("\n");
	int total = 0;
	for(int i=0;i<cdx;i++)
	{
		total = total + cost[i];

	}
	int thres = total / cdx;
	printf("Threshold value till now : %d \n " , thres);

	//now selecting on basis of threshold value;
	//and filling the selected cost array
	for(int i=0;i<cdx;i++)
	{
		if(cost[i] <= total/cdx)
		{
			selectedcost[scdx] = cost[i];
			++scdx;
		}
	}
	

	int iterator  = 0;
	int min3 = 0;
	while(iterator < 3)
	{
			for(int i=0;i<cdx;i++)
			{
				total = total + cost[i];

			}

			int min1 = 100;
			int min2 = 100;
			//find two selected parents
			
			for(int i=0;i<scdx;i++)
			{
				if(selectedcost[i] < min1)
				{
					min1 = selectedcost[i];
				}
			}


			//check count
			int cnt = 0;
			for(int i=0;i<scdx;i++)
			{
				if(selectedcost[i] == min1) ++cnt;
			}
			if(cnt>1)
			{
				min2 = min1;
			}
			else
			{
				for(int i=0;i<scdx;i++)
				{
					if(selectedcost[i]<min2 && selectedcost[i] != min1)
					{
						min2 = selectedcost[i];
					}
				}
			}

			if(min3 != 0)
			{
				if(min1 <= min2)
				{
					int minimum = 100;
					for(int l = 0 ; l<scdx ; l++)
					{
						if(selectedcost[l] < minimum && selectedcost[l] != min1 && selectedcost[l] != min2 )
						{
							minimum = selectedcost[l];
						}
					}
					min2 = minimum;

				}
				else
				{
					int minimum = 100;
					for(int l = 0 ; l<scdx ; l++)
					{
						if(selectedcost[l] < minimum && selectedcost[l] != min1 && selectedcost[l] != min2 )
						{
							minimum = selectedcost[l];
						}
					}
					min1 = minimum;
				}
			}
			printf("\n");
			printf("first parent cost: %d" , min1);
			printf("\n");
			printf("second parent cost: %d", min2);
			printf("\n");
			//int parentsize = (2 * (nodes+ 2)) + 1;
			int *parents = (int *) malloc( 500 * sizeof *parents);
			int parentidx = 0;


			//Child Pool
			int *childpool = (int*) malloc(2500 * sizeof *childpool);
			int childidx = 0;
			//parent count to check that whether i have found both parents in selected pop or not.

			int parentcnt = 0;
			bool check1 = false; // check1 for min1
			bool check2 = false;  //check2 for min2

			for(int i=0 ; i<rdx; i++)
			{
				if(randompop[i] == min1 || randompop[i] == min2)
				{

					++parentcnt;
					if(parentcnt > 2)
					{
						break;
					}
					if(randompop[i] == min1)
					{
						check1 = true;
					}
					else if(randompop[i] == min2)
					{
						check2 = true;
					}

					for(int j=i-(nodes+1); j<=i ; j++)
					{
						parents[parentidx] = randompop[j];
						++parentidx;
					}
				}
			}



			if(parentcnt < 2)
			{
				for(int i=0;i<pdx;i++)
				{

					if(check1 == false)
					{
						if(population[i] == min1)
						{
							for(int j=i-(nodes+1); j<=i ; j++)
							{
								parents[parentidx] = population[j];
								++parentidx;
							}
						}
					}
					else if(check2 == false)
					{
						if(population[i] == min2)
						{
							for(int j=i-(nodes+1); j<=i ; j++)
							{
								parents[parentidx] = population[j];
								++parentidx;
							}
						}
					}

				}
			}
			printf("\n");
			printf("Selected parents for crossover are:");
			printf("\n");
			for(int i=0;i<parentidx;i++)
			{
				if(i == (nodes + 2))
				{
					printf("\n");
				}
				printf("%d ",parents[i]);

			}

			//now filling the child pool by finding new child.
			int childwt = fillchildpool(graph,parents,parentidx,childpool,childidx,nodes);
			if(childwt  <= thres)
			{
				bool flag = false;
				printf("Child is fit to add in the popualtion");
				printf("\n");
				for(int i=0;i<scdx;i++)
				{
					if(selectedcost[i] == childwt)
					{
						flag = true;
					}
				}
				if(flag == false)
				{

					
					cost[cdx] = childwt;
					++cdx;
					selectedcost[scdx] = childwt;
					++scdx;

					//now filling the child formed in random population
					bool flag1 = false;
					for(int idx = 0;idx<rdx;idx++)
					{
						if(randompop[idx] == childwt)
						{
							flag1 = true;
						}
					}
					if(flag1 == false)
					{
						for(int i=0;i<childidx;i++)
						{
							randompop[rdx] = childpool[i];
							++rdx;
						}
						randompop[rdx] = childwt;
						++rdx;
					}

					//now printing the new selected population
					printf("\n");
					// printf("Updated selected cost are: \n");

					// for(int i=0;i<scdx;i++)
					// {
					// 	printf("%d \n", selectedcost[i]);
					// }



				}
				else
				{

					//child is already there in the selected pool
					//we need to mutate
					printf("\n");
					printf("Child is already present in the population. Need to mutate !! \n");
					mutatechild(childpool,childidx, randompop , rdx, nodes,total,cdx,cost,graph,scdx,selectedcost,min1,min2,min3,thres);
					// printf("\n");
					// printf("Updated selected cost are: \n");
					// for(int idx=0;idx<scdx;idx++)
					// {
					// 	printf("%d \n", selectedcost[idx]);
					// }
				}
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

			++iterator;
		}
		
		printfinalpath(randompop,rdx,nodes);
		

}

