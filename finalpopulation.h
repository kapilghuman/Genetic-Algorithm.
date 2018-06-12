#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "randompopulation.h"


void fillpopulation(int *path , int nodes , int *population , int &pdx , int wt )
{
		//Filling the population array for the current path.
		if(pdx<5000)
		{
			for(int i=0;i<nodes;i++)
			{
				population[pdx] = path[i];
				++pdx;
			}

			//After filling the path in population array fill the last element with 0.
			population[pdx] = 0;
			++pdx;

			//Filling the weight of respective path in population array.
			population[pdx] = wt;
			++pdx;
			
		}
}


int safetoadd(int v , int **graph , int *path , int pos , int nodes)
{
	//check if it is adjacent to previous vertex or not
	if(graph[path[pos-1]][v] == 0)
	{
		return 0;
	}
	
	//check if it is already present or not in the path
	for(int i=0;i<pos;i++)
	{
		if(path[i] == v)
		{
			//0 should be returned as v is already present in the path.
			return 0;
		}
	}
	
	return 1;
}


void printpath(int **graph , int *path , int nodes , int *population , int &pdx , int *randompop , int &rdx , int &power , int *cost , int &cdx , int *selectedcost , int &scdx)
{
	
	//Printing the path.
	for(int i=0;i<nodes;i++)
	{
		printf("%d->",path[i]);
	}
	printf("%d",path[0]);

	int wt = 0;
	for(int i=0;i<nodes-1;i++)
	{
		wt = wt + graph[path[i]][path[i+1]];
	}
	wt = wt + graph[path[nodes-1]][path[0]];

	//Printing the cost of path along with path.
	printf(" Cost of the Path => %d",wt);
	printf("\n");
	printf("\n");

	//Filling the path in population along with weight.
	fillpopulation(path,nodes,population,pdx,wt);

	//store random population
	storerandompop(population , pdx , randompop , rdx , nodes , power ,cost , cdx);

	//now printing the random printpopulation
	printrandompop(randompop,rdx,nodes);

	printcost(graph , population , pdx ,  cost,cdx,selectedcost,scdx,randompop,rdx,nodes);





	
}


int checkpath(int **graph , int *path , int pos , int nodes , int *population , int &pdx ,  int *randompop , int &rdx , int &power , int *cost , int &cdx , int *selectedcost , int &scdx)
{
	
	//base condition for recursive call.
	if(pos == nodes)
	{
		//Check whether last node in the path is same as the first one.
		if(graph[path[pos-1]] [path[0]] != 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	for(int v=1;v<nodes;v++)
	{

		//Call safetoadd() to check whether 'v' node can be added in path or not.
		if(safetoadd(v,graph,path,pos,nodes) == 1)
		{
			//node v can be added to path at position pos.
			path[pos] = v;

			//now recurssive call to check from position pos+1
			if(checkpath(graph,path,pos+1,nodes,population,pdx,randompop,rdx,power,cost,cdx,selectedcost,scdx) == 1)
			{
				//Call printpath() to print the current route.
				printpath(graph,path,nodes,population,pdx,randompop,rdx,power,cost,cdx,selectedcost,scdx);
				
			}
			else
			{
				//we need to backtrack and path[pos] is set to -1.
				path[pos] = -1;
			}
		}
	}
	
	return 0;
}

void printpopulation(int nodes , int** graph)
{
	//To print all the routes and maintain the population.
	printf("\nVarious paths of shipment are: \n");

	//Dynamic population array to store all the routes.
	int *population = (int*) malloc(5000 * sizeof *population);
	int pdx = 0;
	int *randompop = (int*) malloc(2500 * sizeof *randompop);
	int rdx = 0;
	int power = 1;

	//Selection Process.
	int *cost = (int*) malloc(2500 * sizeof *cost);
	//index to traverse the cost.
	int cdx = 0;


	//selected cost array
	int *selectedcost = (int*) malloc(2000 * sizeof *selectedcost);
	//index to traverse selected cost;
	int scdx = 0;

	//Dynamic path array to store a single route.
	int *path = (int*) malloc(nodes * sizeof *path);



	//Setting each element of path to -1.
	for(int i=0;i<nodes;i++)
	{
		path[nodes] = -1;
	}

	//Setting first node of path to be 0.
	path[0] = 0;

	//Calling checkpath() to check whether there exists a route or not.
	if(checkpath(graph,path,1,nodes , population , pdx , randompop , rdx , power , cost , cdx , selectedcost , scdx) == 0)
	{
		return;
	}
	
}