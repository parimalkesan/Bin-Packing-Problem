#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define init_no_of_solutions 10
#define no_of_bins 10
#define no_of_objects 10
#define bin_weight 50
#define crossover_no_of_solutions 90
#define totalsolutions 100
#define mutationprobability 5

int item_weights[no_of_objects]={5,10,15,20,25,30,35,40,45,50};//weight of each item
int Initial_Population[init_no_of_solutions][no_of_bins][no_of_objects];//stores the initial solutions
int initialpopulation_bin_weights[init_no_of_solutions][no_of_bins];//stores the left capacity of initial populations in all cycles
int initialpopulation_bin_weightsone[init_no_of_solutions][no_of_bins];//stores the left capacity of initial solutions in 1st cycle
int solution1[10][10];//stores one of the solution for crossover
int solution2[10][10];//stores another solution for crossover
int crossover_solution_matrix[crossover_no_of_solutions][no_of_bins][no_of_objects];//stores the solutions geenrated after crossover
int crossoversolutions_bin_weights[crossover_no_of_solutions][no_of_bins];//stores the left capacity of crossover solutions
int total_no_of_solutions[totalsolutions][no_of_bins][no_of_objects];//stores initial+crossover solutions
int fitness[totalsolutions][2];//stores the fitness value of each solution.


void item_weights_display();
void population_generation();
void initialization();
void initpopulationleftcapacity();
void hor_crossover(int [10][10],int [10][10]);
void crossover();
void mutation();
void repairfunction();
void storeunplacedobject(int,int);
void deleteextraobject(int,int,int[2]);
void totalsolutionsfunction();
void fitness_function();
void copy_into_initial();

//display weight of each item to be placed in bins
void item_weights_display()
{
	int i=0;
	
	//item weigths display
	printf("\t\t\t  Fixed Weights of Items\n");
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
			initialpopulation_bin_weights[i][j]=50;
		}
	}
		
	//initialize the bin weights in crossover population
    for(i=0;i<crossover_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			crossoversolutions_bin_weights[i][j]=50;
		}
	}
}

//generate initial solutions.
void population_generation()
{
	int i=0,j=0,k=0,x=0;
	srand(time(NULL));
	
	for(i=0;i<init_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			initialpopulation_bin_weightsone[i][j]=50;
		}
	}
	
	//intial population generation
    for(i=0;i<init_no_of_solutions;i++)
    {
    	for(j=0;j<no_of_objects;j++)
    	{
    		x=rand()%10;
    		if(item_weights[j]<=initialpopulation_bin_weightsone[i][x])
    		{
    			Initial_Population[i][x][j]=1;
    			initialpopulation_bin_weightsone[i][x]-=item_weights[j];
			}
			else
			{
				j--;
			}
		}
	}
	
	//intial population display
	printf("\t\t\t\tINITIAL POPULATION\n");
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
}
	
void initpopulationleftcapacity()
{
	int i=0,j=0,k=0;
	//Calculate left capacity of each bin in initial solutions
	for(i=0;i<init_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			for(k=0;k<no_of_objects;k++)
			{
				if(Initial_Population[i][j][k]==1)
				{
					initialpopulation_bin_weights[i][j]-=item_weights[k];
				}
			}
		}
	}	
}

void hor_crossover(int array1[10][10],int array2[10][10])
{
	int array3[10][10];
	int array4[10][10];
	int i=0,j=0;
	
	//randomly generate a row and a column from the solution
	int rr=rand()%10;
	int rc=rand()%10;
	
	//initialize both the arrays to 0
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			array3[i][j]=0;
			array4[i][j]=0;
		}
	}
	
	//perform crossover on the given two arrays and store them in other two arrays.
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
	//store the values back to the original arrays.
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
			for(k=0;k<no_of_bins;k++)
			{
				for(l=0;l<no_of_objects;l++)
				{
					solution1[k][l]=Initial_Population[i][k][l];
					solution2[k][l]=Initial_Population[j][k][l];
				}
			}
			//call to the hor_crossover function
			hor_crossover(solution1,solution2);
					
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
	
	//Calculate left capacity of each bin in crossover solutions
	for(i=0;i<crossover_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			for(k=0;k<no_of_objects;k++)
			{
				if(crossover_solution_matrix[i][j][k]==1)
				{
					crossoversolutions_bin_weights[i][j]-=item_weights[k];
				}
			}
		}
	}
}

void mutation()
{
	int i=0,j=0,k=0;
	int mprob=0;
	int r1=0,r2=0,c1=0,c2=0;
	srand(time(NULL));
	
	//initialize the bin weights in crossover population
    for(i=0;i<crossover_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			crossoversolutions_bin_weights[i][j]=50;
		}
	}
	
	for(i=0;i<crossover_no_of_solutions;i++)
	{
		//randomly generate the mutation probability for each solution
		mprob=rand()%10;
		if(mprob<=mutationprobability)
		{
			//generate a pair of row and columr from the solution
			r1=rand()%10;
			c1=rand()%10;
			re:
			//generate another pair of row and column from the solution	
			r2=rand()%10;
			c2=rand()%10;
			if(r1==r2&&c1==c2)
			{
				goto re;
			}
			else
			{
				//interchange the value of both the pairs in the particular solution
				int x=crossover_solution_matrix[i][r1][c1];
				crossover_solution_matrix[i][r1][c1]=crossover_solution_matrix[i][r2][c2];
				crossover_solution_matrix[i][r2][c2]=x;
			}
		}	
	}	
	
		//Calculate left capacity of each bin in crossover solutions after mutation
	for(i=0;i<crossover_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			for(k=0;k<no_of_objects;k++)
			{
				if(crossover_solution_matrix[i][j][k]==1)
				{
					crossoversolutions_bin_weights[i][j]-=item_weights[k];
				}
			}
		}
	}
	
}

void repairfunction()
{
	int i=0,j=0,k=0,count=0,l=0,m=0;
	int storegreaterthanone[2];
	
	//find out the duplicate objects in each bin.
	for(i=0;i<crossover_no_of_solutions;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			m=0;
			for(k=0;k<2;k++)
			{
				storegreaterthanone[k]=0;
			}
			
			for(l=0;l<no_of_bins;l++)
			{
				if(crossover_solution_matrix[i][l][j]==1)
				{
					count++;
					
					storegreaterthanone[m++]=l;
				}
			}
			if(count==0)
			{
				//identify bin with weight which makes the bin full or approx full.
				storeunplacedobject(i,j);
			}
			else if(count>1)
			{
				//delete the item from bin with more left capacity
				deleteextraobject(i,j,storegreaterthanone);
			}
		    count=0;
		}
	}
}

void storeunplacedobject(int solutionno,int objectno)
{
	int i=0,j=0,rbin=0;
	srand(time(NULL));
	re:
		//randomly generate a bin in the solution.
		rbin=rand()%10;
		if(crossoversolutions_bin_weights[solutionno][rbin]>=item_weights[objectno])
		{
			//place the object in the particular bin.
			crossover_solution_matrix[solutionno][rbin][objectno]=1;
			//update the left capacity of selected bin.
			crossoversolutions_bin_weights[solutionno][rbin]-=item_weights[objectno];
		}    
		else
		{
			//reselect a bin from the solution.
			goto re;
		}	
}

void deleteextraobject(int solutionno,int objectno,int binarray[2])
{
	int weight1=0,weight2=0,i=0,j=0;
	
	//left capacity of first bin
	weight1=crossoversolutions_bin_weights[solutionno][binarray[0]];
	//left capacity of second bin
	weight2=crossoversolutions_bin_weights[solutionno][binarray[1]];
	
	if((weight1>=weight2) && weight2>0)
	{
		//delete the object from first bin.
		crossover_solution_matrix[solutionno][binarray[0]][objectno]=0;
		//update the left capacity of first bin.
		if(crossoversolutions_bin_weights[solutionno][binarray[0]]!=50)
		{
			crossoversolutions_bin_weights[solutionno][binarray[0]]+=item_weights[objectno];
		}
	}
	
	else if((weight1>=weight2) && weight2<0)
	{
		//delete the object from 2nd bin.
		crossover_solution_matrix[solutionno][binarray[1]][objectno]=0;
		//update the left capacity of 2nd bin. 
		if(crossoversolutions_bin_weights[solutionno][binarray[1]]!=50)
		{
			crossoversolutions_bin_weights[solutionno][binarray[1]]+=item_weights[objectno];
		}
	}
	
	else if((weight2>=weight1) && weight1>0)
	{
		//delete the object from 2nd bin.
		crossover_solution_matrix[solutionno][binarray[1]][objectno]=0;
		//update the left capacity of 2nd bin. 
		if(crossoversolutions_bin_weights[solutionno][binarray[1]]!=50)
		{
			crossoversolutions_bin_weights[solutionno][binarray[1]]+=item_weights[objectno];
		}
	}
	
	else if((weight2>=weight1) && weight1<0)
	{
	    //delete the object from first bin.
		crossover_solution_matrix[solutionno][binarray[0]][objectno]=0;
		//update the left capacity of first bin.
		if(crossoversolutions_bin_weights[solutionno][binarray[0]]!=50)
		{
			crossoversolutions_bin_weights[solutionno][binarray[0]]+=item_weights[objectno];
		}
	}	
}

//all solutions-initial+crossover solutions
void totalsolutionsfunction()
{
	int i=0,j=0,k=0;
	
	//copy the initial and crossover solutions in a single matrix
	for(i=0;i<totalsolutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			for(k=0;k<no_of_objects;k++)
			{
				total_no_of_solutions[i][j][k]=Initial_Population[i][j][k];
				if(i>=10)
				{
					total_no_of_solutions[i][j][k]=crossover_solution_matrix[i-10][j][k];
				}
			}
		}
	}	
}

void fitness_function()
{
	int i=0,j=0,count=0;
	//calculate the fitness by finding the empty bins
	for(i=0;i<totalsolutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			if(initialpopulation_bin_weights[i][j]==50)
			{
				count++;
			}
			if(i>=10)
			{
				if(crossoversolutions_bin_weights[i-10][j]==50)
				{
				    count++;
				}
			}
		}
		//store the fitness in a 2d array with solution number and fitness.
		fitness[i][0]=i;
		fitness[i][1]=count;
		count=0;
	}
}

//sort the fitness in decreasing order.
void bubble_sort( int A[100][2] )
 {
    int temp,temp1;
    int k=0,i=0,j=0,n=100;
    for(k=0;k<n-1;k++)
	 {
        for(i=0;i<n-k-1;i++) 
		{
            if(A[i][1]>A[i+1][1] )
			{
                temp=A[i][1];
                A[i][1]=A[i+1][1];
                A[i+1][1]=temp;
                
                temp1=A[i][0];
                A[i][0] = A[i+1][0];
                A[i+1][0]=temp1;
            }
        }
    }
}

//copy the top10 solution into initial population for next round
void copy_into_initial()
{
	int i=0,j=0,k=0,z=0,x=0;
	for(i=90;i<100;i++)
	{
		int x=fitness[i][0];
		for(j=0;j<no_of_bins;j++)
		{
			for(k=0;k<no_of_objects;k++)
			{
				Initial_Population[z][j][k]=total_no_of_solutions[x][j][k];
			}
		}
		z=z+1;
	}
}

int main()
{
	int i=0,j=0,k=0,z=0;
	item_weights_display();
	population_generation();
	for(i=0;i<5;i++)
	{
		initialization();
	    initpopulationleftcapacity();
	    crossover();
	    repairfunction();
	    mutation();
	    repairfunction();
        totalsolutionsfunction();
	    fitness_function();
	    bubble_sort(fitness);
	    copy_into_initial();   
	    
	    //solution after cycles
	    if(i<4)
	    {
	    	printf("\t\t\t  Solution after cycle-%d\n",i+1);
		}
		else
		{
			printf("\t\t\t\tFinal Solution\n",i+1);
		}
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
    			printf("   %d   ",Initial_Population[9][j][k]);
    		}
			printf("\n");
		}
		printf("\n\n");	 
	}	
	
	return 0;
}
