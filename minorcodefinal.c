#include <stdio.h>
#include <stdlib.h>
#include "finalpopulation.h"

void addedge(int s , int d , int wt , int wt2 ,  int nodes ,  int **graph)
{
	//Adding a path between the two connected cities.
	graph[s][d] = wt;
	graph[d][s] = wt2;
}

void printgraph(int nodes , int **graph)
{
	//Printing the adjacency list of the graph
	for(int i=0;i<nodes;i++)
	{
		printf("%d->",i);
		for(int j=0;j<nodes;j++)
		{
			if(graph[i][j] != 0)
			{
				printf("%d(%d)->",j,graph[i][j]);
			}
		}
		printf("\n");
	}

	printf("\n");
}

void takeinput(int nodes , int **graph)
{
	//Taking information of cities and paths from the user.
	int ans = 1;
	while(ans)
	{
		int s,d,wt,wt2;
		printf("Enter FIRST of the TWO connected city in the map: ");
		scanf("%d",&s);
		printf("Enter SECOND of the TWO connected city in the map: ");
		scanf("%d",&d);
		printf("Enter distance between the two cities %d and %d: ",s,d);
		scanf("%d",&wt);
		printf("Enter distance between the two cities %d and %d: ",d,s);
		scanf("%d",&wt2);
		
		//addedge() is used to add the path in the respective citi3es.
		addedge(s,d,wt,wt2,nodes,graph);
		scanf("%d",&ans);
	}
	
}

int main()
{
	int nodes;
	printf("Enter total number of shipment cities: ");
	scanf("%d",&nodes);
	int **graph;
	printf("\n");

 	//creating the adjacency matrix for the graph
  	graph = (int**) malloc(nodes * sizeof *graph);
  	
  	for (int i=0; i<nodes; i++)
  	{
    	graph[i] = (int*) malloc(nodes * sizeof *graph[i]);
  	}
  	
  	for(int i=0;i<nodes;i++)
  	{
  		for(int j=0;j<nodes;j++)
  		{
  			graph[i][j] = 0;
  		}
  	}
	
	//takeinput() to take information of shipment cities from the user. 
 	takeinput(nodes , graph);
  	printf("\n");
  	printf("Adjacency Matrix of Map is:");
  	printf("\n");

  	//printing the adjacency matrix for the graph.
  	for(int i=0;i<nodes;i++)
  	{
  		for(int j=0;j<nodes;j++)
  		{
  			printf("%d ",graph[i][j]);
  		}
  		printf("\n");
  	}
  	printf("\n");

  	//printgraph() is used to print the adjacency list of the graph.
  	printgraph(nodes , graph);

  	//printpopulation() of "population.h" is used to print all paths along with their cost.
  	printpopulation(nodes, graph);
  	return 0;


}