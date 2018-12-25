#include<stdio.h>

void maxmin(int arr[],int i,int j,int *max,int *min)
{
	 int temp_max,temp_min,mid;

	 if(i==j)
	  *max=*min=arr[i];
	 else
	 {
	  if(i==j-1)
	  {
		   if(arr[i]<arr[j])
		   {
			    *max=arr[j];
			    *min=arr[i];
		   }
		   else
		   {
			    *max=arr[i];
			    *min=arr[j];
		   }
	  }
	  else
	  {
		   mid=(i+j)/2;
		   printf("i= %d   mid=%d\n",i,mid);
		   maxmin(arr,i,mid,max,min); // recursively calling left array
		   temp_max=*max;
		   temp_min=*min;
		   printf("temp_max= %d   temp_min=%d\n",temp_max,temp_min);
		   printf("mid= %d   j=%d\n",mid,j);
		   maxmin(arr,mid+1,j,max,min); // recursively calling right array
		   if(*max<temp_max)  //comparing right left max
		    *max=temp_max;
		   if(*min>temp_min) //comparing the right left min
		    *min=temp_min;
	  }
	 }
}
int main()
{
	int max,min;
	int i, num;
	printf ("\nSize of array : ");
	scanf ("%d",&num);
	int *ptr;
	ptr=(int*)malloc(num*sizeof(int));
	for(i=0;i<num;i++)
	{
	    printf ("Enter the %d number  :- ",i+1);
	    scanf("%d",ptr+i);
	}

	max=ptr[0];
	min=ptr[0];
	maxmin(ptr,0,num-1,&max,&min);
	printf ("\n\nMinimum element in an array : %d\n", min);
	printf ("Maximum element in an array : %d\n", max);
	free(ptr);
	return 0;
}
