#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define init_no_of_solutions 10
#define no_of_bins 10
#define no_of_objects 10
#define bin_weight 50
#define crossover_no_of_solutions 90

int bin_weights[init_no_of_solutions][no_of_bins];
int Initial_Population[init_no_of_solutions][no_of_bins][no_of_objects];
int fitness[init_no_of_solutions];
int crossover_solution_matrix[crossover_no_of_solutions][no_of_bins][no_of_objects];
int solution1[10][10];
int solution2[10][10];
int item_weights[no_of_objects];

void weights_initialization();
void population_generation();
//void fitness_function(int);
void hor_crossover(int [10][10],int [10][10]);
void crossover();

void weights_initialization()
{
	int i=0,j=0;
	srand(time(NULL));
	//Item weights initialization..to be done just once
	for(i=0;i<no_of_objects;i++)
	{
		int x=rand()%20+1;
		item_weights[i]=x;		
	}
	
	//item weigths display
	printf("\t\t\t  Random Weights of Items\n");
	for(i=0;i<no_of_objects;i++)
	{
		printf("Item-%d  ",i+1);
	}
	printf("\n");
	
	for(i=0;i<no_of_objects;i++)
	{
		printf(" %d      ",item_weights[i]);			
	}
	printf("\n\n");
	
}


void initialization()
{
	int i=0,j=0;
    
    //initialize the bin weights in initial population
    for(i=0;i<init_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			bin_weights[i][j]=50;
		}
	}
}

void population_generation()
{
	int i=0,j=0,k=0,x=0;
	srand(time(NULL));
	
	//intial population generation
    for(i=0;i<init_no_of_solutions;i++)
    {
    	for(j=0;j<no_of_objects;j++)
    	{
    		x=rand()%10;
    		if(item_weights[j]<=bin_weights[i][x])
    		{
    			Initial_Population[i][x][j]=1;
    			bin_weights[i][x]-=item_weights[j];
			}
			else
			{
				j--;
			}
		}
	}
	
	//intial population display
	for(i=0;i<init_no_of_solutions;i++)
    {
    	printf("\t\t\t\t  Solution-%d\n",i+1);
    	printf("\t");
    	for(j=0;j<no_of_objects;j++)
    	{
    		printf("Item-%d ",j+1);
    	}
    	printf("\n");
    	
    	for(j=0;j<no_of_bins;j++)
    	{
    		printf("Bin-%d\t",j+1);
    		for(k=0;k<no_of_objects;k++)
    		{
    			printf("   %d   ",Initial_Population[i][j][k]);
    		}
			printf("\n");
		}
		printf("\n\n");
	}
	
	//Left capacity of bins in initial population
	printf("\t\t\tLeft capacity of bins\n");
	printf("\t");
	for(i=0;i<no_of_bins;i++)
	{
		printf("Bin-%d  ",i+1);
	}
	printf("\n");
		
	for(i=0;i<init_no_of_solutions;i++)
	{
		printf("Sol-%d\t",i+1);
		for(j=0;j<no_of_bins;j++)
		{
			printf(" %d    ",bin_weights[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
}

//void fitness_function(int n)
//{
//	int i,j,fitnessvalue=0;
//	for(i=0;i<n;i++)
//	{
//		for(j=0;j<no_of_bins;j++)
//		{
//			if(bin_weights[i][j]==50)
//			{
//				fitnessvalue++;
//			}
//		}
//		fitness[i]=fitnessvalue;
//		fitnessvalue=0;
//	}
//	for(i=1;i<=10;i++)
//	{
//		printf("fitness of solution-%d=%d\n",i,fitness[i]);
//	}
//}
//
void hor_crossover(int array1[10][10],int array2[10][10])
{
	int array3[10][10];
	int array4[10][10];
	int i=0,j=0;
	
	int rr=rand()%10;
	int rc=rand()%10;
	
	printf("\nrr is %d\n",rr+1);
	printf("rc is %d\n",rc+1);
	
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			array3[i][j]=0;
			array4[i][j]=0;
		}
	}
	
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			if(i<rr)
			{
				array3[i][j]=array1[i][j];
				array4[i][j]=array2[i][j];
			}
			if(i==rr)
			{
				if(j<=rc)
				{
					array3[i][j]=array1[i][j];
					array4[i][j]=array2[i][j];
				}
				if(j>rc)
				{
					array3[i][j]=array2[i][j];
					array4[i][j]=array1[i][j];
				}
			}
			if(i>rr)
			{
				array3[i][j]=array2[i][j];
				array4[i][j]=array1[i][j];
			}
		}
	}
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			array1[i][j]=array3[i][j];
			array2[i][j]=array4[i][j];
		}
	}	
}


void crossover()
{
	int v=0;
	int i=0,j=1,k=0,l=0;
	for(i=0;i<init_no_of_solutions;i++)
	{
		for(j=i+1;j<init_no_of_solutions;j++)
		{
			printf("i=%d",i+1);
			printf("j=%d",j+1);
			for(k=0;k<no_of_bins;k++)
			{
				for(l=0;l<no_of_objects;l++)
				{
					solution1[k][l]=Initial_Population[i][k][l];
					solution2[k][l]=Initial_Population[j][k][l];
				}
			}
			
			hor_crossover(solution1,solution2);
			
			//print solution-1
			printf("\t");
			for(k=0;k<no_of_objects;k++)
			{
				printf("Item-%d ",k+1);
    	    }
    	    printf("\n");
    	    
			for(k=0;k<no_of_bins;k++)
			{
				printf("Bin-%d\t",k+1);
				for(l=0;l<no_of_objects;l++)
				{
					printf("   %d   ",solution1[k][l]);
				}
				printf("\n");	
			}
			printf("\n\n");
			
			//print solution-2
			printf("\t");
			for(k=0;k<no_of_objects;k++)
			{
				printf("Item-%d ",k+1);
    	    }
    	    printf("\n");
					
			for(k=0;k<no_of_bins;k++)
			{
				printf("Bin-%d\t",k+1);
				for(l=0;l<no_of_objects;l++)
				{
					printf("   %d   ",solution2[k][l]);
				}
				printf("\n");	
			}
			printf("\n\n");
			
			//copy the generated solutions into crossover matrix
			for(k=0;k<no_of_bins;k++)
			{
				for(l=0;l<no_of_objects;l++)
				{
					crossover_solution_matrix[v][k][l]=solution1[k][l];
					crossover_solution_matrix[v+1][k][l]=solution2[k][l];
				}
			}
			v=v+2;			
		}
	}
	
	printf("\n");
	printf("Value of v=%d",v);
	printf("\n");
}



int main()
{
	int i=0,j=0,k=0;
	weights_initialization();
	initialization();
	population_generation();
	
//	fitness_function();
    crossover();
	
	for(i=0;i<90;i++)
    {
    	for(j=0;j<no_of_bins;j++)
    	{
    		for(k=0;k<no_of_objects;k++)
    		{
    			printf("%d   ",crossover_solution_matrix[i][j][k]);
    		}
			printf("\n");
		}
		printf("\n\n");
	}
	return 0;
}
