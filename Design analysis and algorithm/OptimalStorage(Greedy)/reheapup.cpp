#include<stdio.h>
#include<stdio.h>
struct job
{
	int index,val;
};

int main()
{
int n,i,sum=0,optimum=0;;
	printf("\nEnter the no. of elements: ");
	scanf("%d",&n);
	struct job j[n];
	printf("\n------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("\nEnter the length of job %d: ",i);
		scanf("%d",&j[i].val);
		j[i].index=i;
	}
		int t,c,p,t1;

	//----------------------------heap up ---------
    int high=n-1,l=n,temp;
    for(int i=1;i<n;i++)
        {
            t=j[i].val;
            t1=j[i].index;
            c=i;
            p=(c-1)/2;
            while(t>j[p].val && c>=1)
            {
                j[c].val=j[p].val;
                j[c].index=j[p].index;
                c=p;
                p=(c-1)/2;
            }
            j[c].val=t;
            j[c].index=t1;

        }

//----heap down
    for(int i=n-1;i>0;i--)
    {
        t=j[i].val;
        t1=j[i].index;
        j[i].val=j[0].val;
        j[i].index=j[0].index;
        j[0].val=t;
        j[0].index=t1;
        p=0;
        c=1;
        if(2<i && j[2].val>j[c].val)
            c=2;
        while(c<i && t<j[c].val)
        {
            j[p].val=j[c].val;
            j[p].index=j[c].index;
            p=c;
            c=p*2+1;
            if(p*2+2<i && j[p*2+1].val>j[c].val)
                c++;
        }
        j[p].val=t;
        j[p].index=t1;
    }


	printf("\n------------------------------------------------------");
	printf("\nS.No.\t\tJOB\t\tLength\t\tTime");
	printf("\n------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		sum+=j[i].val;
		optimum+=sum;
		printf("%d\t\t%d\t\t%d\t\t%d\n",i+1,j[i].index,j[i].val,sum);
	}
	printf("\nTotal optimul value is: %.02f ",(float)optimum/n);
}
