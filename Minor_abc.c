#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define init_no_of_solutions 10
#define no_of_bins 10
#define no_of_objects 10
#define bin_weight 50
#define new_solutions 90
#define totalsolutions 100
#define triallimit 3

int item_weights[no_of_objects]={5,10,15,20,25,30,35,40,45,50};//weight of each item
int Initial_Population[init_no_of_solutions][no_of_bins][no_of_objects];//stores the initial solutions
int initialpopulation_bin_weights[init_no_of_solutions][no_of_bins];//stores the left capacity of initial solutions in all cycles
int initialpopulation_bin_weightsone[init_no_of_solutions][no_of_bins];//stores the left capacity of initial solutions in 1st cycle
int initialpopulation_bin_weightstwo[no_of_bins];//stores the left capacity of bins in a solution for scout phase
int fitness[init_no_of_solutions][2];//stores the fitness value of each solution.
int solution1[10][10];//used to perform mutation
int solution2[10][10];//used to perform mutation
int leftcapacityofnewsol[10];//stores left capacity of each bin of a newly solution
int fitnessofnewsol;//stores a single fitness value of newly generated solutions
float selectionprob[10];//stores selection probability value of each solution
int trial[init_no_of_solutions];//keeps a record of number of cycles in which a solution remains unupdated


void item_weights_display();
void population_generation();
void initpopulationleftcapacity();
void sendemployedbees();
void mutatefunction();
void leftcapacityofnewsolution();
void repairfunction();
void storeunplacedobject(int);
void deleteextraobject(int,int[2]); 
void fitnessofnewsolution();
void calculateprob();
void sendonlookerbees();
void sendscoutbees(int);
void fitness_function();

//display weight of each item to be placed in bins
void item_weights_display()
{
	int i=0,j=0;
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

//generate initial solutions
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

//calculate left capacity of all solutions
void initpopulationleftcapacity()
{
	int i=0,j=0,k=0;
	
	 //initialize the bin weights in initial population
    for(i=0;i<init_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			initialpopulation_bin_weights[i][j]=50;
		}
	}
	
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

//send employee bees to generate new solutions.
void sendemployedbees()
{
	int i=0,j=0,k=0,l=0,m=0,x=0;
	srand(time(NULL));
	for(i=0;i<init_no_of_solutions;i++)
	{
		re:
		x=rand()%10;
		if(x==i)
		{
			goto re;
		}
		else
		{
			for(j=0;j<no_of_bins;j++)
			{
				for(k=0;k<no_of_objects;k++)
				{
					solution1[j][k]=Initial_Population[i][j][k];
					solution2[j][k]=Initial_Population[x][j][k];
				}
			}
			mutatefunction(solution1,solution2);
			leftcapacityofnewsolution();
		    repairfunction();
		    fitnessofnewsolution();
			if(fitnessofnewsol>fitness[i][1])
			{
				for(l=0;l<no_of_bins;l++)
				{
					for(m=0;m<no_of_objects;m++)
					{
						Initial_Population[i][l][m]=solution1[l][m];
					}
				}
			}
		}
	}	
}

//perform mutation to generate new solutions
void mutatefunction(int array1[10][10],int array2[10][10])
{
	int array3[10][10];
	int i=0,j=0;
	
	//randomly generate a row and a column from the solution
	int rr=rand()%10;
	int rc=rand()%10;
	
	//initialize the array to 0
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			array3[i][j]=0;
		}
	}
	
	//generate a new solution by combining the elements of both the solutions
	int rand1=rand()%10;
	if(rand<5)
	{
		for(i=0;i<no_of_bins;i++)
      	{
		    for(j=0;j<no_of_objects;j++)
		    {
			    if(i<rr)
			    {
				    array3[i][j]=array1[i][j];
			    }
			    if(i==rr)
			    {
				    if(j<=rc)
				    {
					    array3[i][j]=array1[i][j];
				    }
				    if(j>rc)
				    {
					    array3[i][j]=array2[i][j];
				    }   
			    }
			    if(i>rr)
			    {
				    array3[i][j]=array2[i][j];
			    }
		    }
	    } 
	
	}
	else
	{
		for(i=0;i<no_of_bins;i++)
	    {
		    for(j=0;j<no_of_objects;j++)
		    {
			    if(i<rr)
			    {
				    array3[i][j]=array2[i][j];
			    }
			    if(i==rr)
			    {
				    if(j<=rc)
				    {
					    array3[i][j]=array2[i][j];
				    }
				    if(j>rc)
				    {
					    array3[i][j]=array1[i][j];
				    }
			    }
			    if(i>rr)
			    {
				    array3[i][j]=array1[i][j];
			    }      
		    }
	    }
	}
	//store the values back in a array which denotes a new solution
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			array1[i][j]=array3[i][j];
		}
	}		
}

//calculate left capacity of each new solution to check its fitness
void leftcapacityofnewsolution()
{
	int i=0,j=0;
	
	for(i=0;i<no_of_bins;i++)
	{
		leftcapacityofnewsol[i]=50;
	}
	
	for(i=0;i<no_of_bins;i++)
	{
		for(j=0;j<no_of_objects;j++)
		{
			if(solution1[i][j]==1)
			{
				leftcapacityofnewsol[i]-=item_weights[j];
			}
		}
	}
}

//repair the newly generated solutions.
void repairfunction()
{
	int i=0,j=0,k=0,count=0,l=0,m=0;
	int storegreaterthanone[2];
	
	//find out the duplicate objects in each bin.
	for(i=0;i<no_of_objects;i++)
	{
		m=0;
		for(j=0;j<2;j++)
		{
			storegreaterthanone[j]=0;
		}
			
		for(k=0;k<no_of_bins;k++)
		{
			if(solution1[k][i]==1)
			{
				count++;	
				storegreaterthanone[m++]=k;
			}
		}
		if(count==0)
		{
			//identify bin with weight which makes the bin full or approx full.
			storeunplacedobject(i);
		}
		else if(count>1)
		{
			//delete the item from bin with more left capacity
			deleteextraobject(i,storegreaterthanone);
		}
		
		count=0;
	}
}

void storeunplacedobject(int objectno)
{
	int i=0,j=0,rbin=0;
	srand(time(NULL));
	re:
		//randomly generate a bin in the solution.
		rbin=rand()%10;
		if(leftcapacityofnewsol[rbin]>=item_weights[objectno])
		{
			//place the onject in the particular bin.
			solution1[rbin][objectno]=1;
			//update the left capacity of selected bin.
			leftcapacityofnewsol[rbin]-=item_weights[objectno];
		}    
		else
		{
			//reselect a bin from the solution.
			goto re;
		}	
}

void deleteextraobject(int objectno,int binarray[2])
{
	int weight1=0,weight2=0,i=0,j=0;
	
	//left capacity of first bin
	weight1=leftcapacityofnewsol[binarray[0]];
	//left capacity of second bin
	weight2=leftcapacityofnewsol[binarray[1]];
	
	if((weight1>=weight2) &&weight2>0)
	{
		//delete the object from first bin.
		solution1[binarray[0]][objectno]=0;
		//update the left capacity of first bin.
		if(leftcapacityofnewsol[binarray[0]]!=50)
		{
			leftcapacityofnewsol[binarray[0]]+=item_weights[objectno];
		}
	}
	
	else if((weight1>=weight2) &&weight2<0)
	{
		//delete the object from 2nd bin.
		solution1[binarray[1]][objectno]=0;
		//update the left capacity of 2nd bin. 
		if(leftcapacityofnewsol[binarray[1]]!=50)
		{
			leftcapacityofnewsol[binarray[1]]+=item_weights[objectno];
		}
	}
	
	else if((weight2>=weight1) &&weight1>0)
	{
		//delete the object from 2nd bin.
		solution1[binarray[1]][objectno]=0;
		//update the left capacity of 2nd bin. 
		if(leftcapacityofnewsol[binarray[1]]!=50)
		{
			leftcapacityofnewsol[binarray[1]]+=item_weights[objectno];
		}
	}
	
	else if((weight2>=weight1) &&weight1<0)
	{
	    //delete the object from first bin.
		solution1[binarray[0]][objectno]=0;
		//update the left capacity of first bin.
		if(leftcapacityofnewsol[binarray[0]]!=50)
		{
			leftcapacityofnewsol[binarray[0]]+=item_weights[objectno];
		}
	}	
}

//calculate fitness of each solution
void fitnessofnewsolution()
{
	int i=0,count=0;
	for(i=0;i<no_of_bins;i++)
	{
		if(leftcapacityofnewsol[i]==50)
		{
			count++;
		}
	}
	fitnessofnewsol=count;
	count=0;
}

//calculate the selection probability of each solution
void calculateprob()
{
	int i=0,j=0,sum=0;
	for(i=0;i<no_of_bins;i++)
	{
		sum=sum+fitness[i][1];
	}
	
	for(i=0;i<init_no_of_solutions;i++)
	{
		int x=fitness[i][1];
		selectionprob[i]=(float)x/(float)sum;
	}
}

//send onlooker bees to calculate the best fitness solution for the cycle
void sendonlookerbees()
{
	int i=0,j=0,k=0,l=0,m=0,x=0;
	float prob=0;
	srand(time(NULL));
	for(i=0;i<init_no_of_solutions;i++)
	{
		prob=(float)rand()/(float)(50000);
		if(prob<selectionprob[i])
		{
			re:
		    x=rand()%10;
		    if(x==i)
		    {
			    goto re;
	        }
		    else
		    {
			    for(j=0;j<no_of_bins;j++)
			    {
				    for(k=0;k<no_of_objects;k++)
				    {
					    solution1[j][k]=Initial_Population[i][j][k];
					    solution2[j][k]=Initial_Population[x][j][k];
				    }
		     	}
			    mutatefunction(solution1,solution2);
			    leftcapacityofnewsolution();
		        repairfunction();
		        fitnessofnewsolution();
			    if(fitnessofnewsol>fitness[i][1])
			    {
				    for(l=0;l<no_of_bins;l++)
				    {
					    for(m=0;m<no_of_objects;m++)
					    {
						    Initial_Population[i][l][m]=solution1[l][m];
					    }
				    }
			    }
			    else
			    {
			    	trial[i]=trial[i]+1;
			    	if(trial[i]>triallimit)
			    	{
			    		sendscoutbees(i);
					}
				}
		    }
		}
	}
}

//send scout bees to reinitialize the particular solution
void sendscoutbees(int solutionno)
{
	int i=0,j=0,x=0;
	srand(time(NULL));
	
	for(i=0;i<no_of_bins;i++)
	{
		initialpopulation_bin_weightstwo[i]=50;
	}
	
	for(i=0;i<no_of_objects;i++)
	{
    	x=rand()%10;
    	if(item_weights[i]<=initialpopulation_bin_weightstwo[i])
    	{
    			Initial_Population[solutionno][x][j]=1;
    			initialpopulation_bin_weightstwo[i]-=item_weights[i];
		}
		else
		{
				j--;
		}
	}
}

//calculate fitness of solutions
void fitness_function()
{
	int i=0,j=0,count=0;
	//calculate the fitness by finding the empty bins
	for(i=0;i<init_no_of_solutions;i++)
	{
		for(j=0;j<no_of_bins;j++)
		{
			if(initialpopulation_bin_weights[i][j]==50)
			{
				count++;
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
    int k=0,i=0,j=0,n=10;
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

int main()
{
	int i=0,j=0,k=0,z=0,sol=0;
	item_weights_display();
	population_generation();
    initpopulationleftcapacity();
	fitness_function();
	for(i=0;i<5;i++)
	{
		sendemployedbees();
	    initpopulationleftcapacity();
	    fitness_function();
        calculateprob();
        sendonlookerbees();
	    initpopulationleftcapacity();
	    fitness_function();
	    bubble_sort(fitness);
	    
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
		
		sol=fitness[9][0];
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
    			printf("   %d   ",Initial_Population[sol][j][k]);
    		}
			printf("\n");
		}
		printf("\n\n");	 
	}	
	return 0;
}
