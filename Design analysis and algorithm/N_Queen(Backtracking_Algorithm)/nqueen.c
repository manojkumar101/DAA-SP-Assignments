#include<stdio.h>
#include<stdlib.h>

int placequeen(int r2,int c2,int *ptr)
{
	int r1,c1;
	for(r1=0;r1<r2;r1++)
	{
		c1=ptr[r1];
		if(c1==c2 || abs(r1-r2)==abs(c1-c2)) //same column or diagonally adjacent
			return 0; //queen cannot be placed
	}
	return 1;
}

void print(int n,int *ptr)
{
	int i,j,k;
	for(i=0;i<=2*n+1;i++)
		printf("-");
	printf("\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("|");
			if(j==ptr[i])
				printf("Q");
			else
				printf(" ");
	    }
		printf("|\n");
		for(k=0;k<=2*n+1;k++)
			printf("-");
		printf("\n");
	}
}

int iterative(int n,int sol)
{
	int *ptr;
	ptr=(int*)malloc(n*sizeof(int));
	int i,j,r=0,cnt=0,ch;

	for(i=0;i<n;i++)
		ptr[i]=-1;

	while(r!=-1)
	{
		ptr[r]++;
		if(ptr[r]<n)
		{
			if(placequeen(r,ptr[r],ptr))
			{
				if(r==n-1)
				{
					printf("\nSolution number %d for %d-Queen Problem ->\n",++cnt,n);
					print(n,ptr);
					if(sol==1)
						return 0;
				}
				else
					r++;
			}
		}
		else
		{
			ptr[r]=-1;
			r--;
		}
	}
	free(ptr);
	return cnt;
}

void recursive(int n,int sol,int *ptr,int *pt,int r)
{
	int i,j,c;
	static int d;

	for(c=0;c<n;c++)
	{
		if(placequeen(r,c,ptr))
		{
			ptr[r]=c;
			if(r==n-1)
			{
				(*pt)++;
				printf("\nSolution number %d for %d-Queen Problem ->\n",*pt,n);
				print(n,ptr);
				if(sol==1)
				{
					d=1;
					return;
				}
			}
			else
			{
				recursive(n,sol,ptr,pt,r+1);
			}
		}
		if(d==1)
			return;
	}
}

int main()
{
	int choice1,choice2,n,count,p;
	int *ptr;
	do
	{
		printf("\nN-Queen Problem using Backtracking");
		printf("\n1.Iterative Solution");
		printf("\n2.Recursive Solution");
		printf("\n3.Exit");
		printf("\n\nEnter your choice::");
		scanf("%d",&choice1);
		switch(choice1)
		{
			case 1:
				do
				{
					printf("\nN-Queen Problem using Iterative Algorithm");
					printf("\n1.Print All Solutions");
					printf("\n2.Print Single Solution");
					printf("\n3.Return to main menu");
					printf("\n\nEnter your choice::");
					scanf("%d",&choice2);
					switch(choice2)
					{
						case 1:
							printf("\nEnter the number of queens::");
							scanf("%d",&n);
							if(n<4)
								printf("\nSolution not possible!!!");
							else
							{
								count=iterative(n,0);
								printf("\nThe total number of solutions in %d-Queen Problem is %d\n",n,count);
							}
							break;
						case 2:
							printf("\nEnter the number of queens::");
							scanf("%d",&n);
							if(n<4)
								printf("\nSolution not possible!!!");
							else
								iterative(n,1);
							break;
					}
				}while(choice2!=3);
				break;
			case 2:
				do
				{
					printf("\nN-Queen Problem using Recursive Algorithm");
					printf("\n1.Print All Solutions");
					printf("\n2.Print Single Solution");
					printf("\n3.Return to main menu");
					printf("\n\nEnter your choice::");
					scanf("%d",&choice2);
					switch(choice2)
					{
						case 1:
							printf("\nEnter the number of queens::");
							scanf("%d",&n);
							if(n<4)
								printf("\nSolution not possible!!!");
							else
							{
								p=0;
								ptr=(int*)malloc(n*sizeof(int));
								recursive(n,0,ptr,&p,0);
								printf("\nThe total number of solutions in %d-Queen Problem is %d\n",n,p);
								free(ptr);
							}
							break;
						case 2:
							printf("\nEnter the number of queens::");
							scanf("%d",&n);
							if(n<4)
								printf("\nSolution not possible!!!");
							else
							{
								p=0;
								ptr=(int*)malloc(n*sizeof(int));
								recursive(n,1,ptr,&p,0);
								free(ptr);
							}
							break;
					}
				}while(choice2!=3);
				break;
			case 3 :
				break;
		}
	}while(choice1!=3);
}
