#include <stdio.h>
#include <stdlib.h>

int fillchildpool(int **graph , int *parents , int &parentidx , int *childpool , int &childidx , int nodes)
{
	int i = 0;
	int j = (nodes + 2);
	int idx = 1;
	int start;
	int end;
	for(idx ; idx<nodes ; idx++)
	{
		if(parents[i+idx] != parents[j+idx])
		{
			int dist1 = graph[parents [i+idx-1]] [ parents[i+idx]];
			int dist2 = graph[parents [j+idx-1]] [ parents[j+idx]];


			if(dist1 <= dist2)
			{
				start = i;
				end = (i+idx);
			}
			else if(dist2 < dist1)
			{
				start = j;
				end = (j+idx);
			}
			break;
		}
	}
	for(int k = start;k<=end;k++)
	{
		childpool[childidx] = parents[k];
		++childidx;
	}

	// remaining child elements to be filled
	if(start == i)
	{
		for(int k=j+end+1 ; k<parentidx-1;k++)
		{
			childpool[childidx] = parents[k];
			++childidx;
		}
	}	
	else if(start == j)
	{
		for(int k=i+idx+1 ; k< nodes+1 ; k++)
		{
			childpool[childidx] = parents[k];
			++childidx;
		}
	}


	//Improving the child
	int count[nodes] = {};
	for(int check = 0; check<childidx ; check++)
	{
		++count[childpool[check]];
	}

	//checkidx is that which is repeated twice
	int checkidx;
	if(count[0] > 2)
	{
		checkidx = 0;
	}
	else
	{
		for(int i=0;i<nodes;i++)
		{
			if(i!=0)
			{
				if(count[i] == 2)
				{
					checkidx = i;
				}
			}
		}
	}
	

	//replace is the one whose occurence is zero.
	int replace;
	for(int i=0;i<nodes;i++)
	{
		if(count[i] == 0)
		{
			replace = i;
			
		}
	}

	int dbocc = 0;

	int dbidx;
	

	for(int j=0;j<childidx;j++)
	{
		if(childpool[j] == checkidx)
		{
			++dbocc;
			if(dbocc == 2)
			{
				dbidx = j;
			}
		}
	}

	// //Now improving child by replacing
	childpool[dbidx] = replace;

	//Calculating the weight of the formed child
	int childwt = 0;

	for(int i=0;i<childidx;i++)
	{
		childwt = childwt + graph[childpool[i]][childpool[i+1]];
	}

	//printing the child
	printf("\n");
	printf("Child path formed is: \n"); 
	for(int l = 0;l<childidx;l++)
	{
		printf("%d ",childpool[l]);
	}
	printf("%d \n",childwt);
	return childwt;




}