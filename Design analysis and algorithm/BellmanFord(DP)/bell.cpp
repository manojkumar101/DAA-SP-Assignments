#include<bits/stdc++.h>
using namespace std;
typedef struct graph
{
  int s;
  int d;
  int w;
};
int checkvalidation(struct graph *arr,int size,int s,int d)
{
    for(int i=0;i<size;i++)
    {
        //cout<<arr[i][0]<<" "<<arr[i][1]<<"      "<<s<<" "<<d<<endl;
        if((arr[i].s==s) && (arr[i].d==d) )
        return 0;
    }
    return 1;
}
int checknegativecyle(struct graph *gr,int *arr,int t)
{
    int flag=0,temp;
    for(int i=0;i<t;i++)
        {   if(arr[gr[i].s-1]!=INT_MAX){
            temp=arr[gr[i].s-1]+gr[i].w;
                if(arr[gr[i].d-1]>temp)
                    {
                        arr[gr[i].d-1]=temp;flag=1;
                    }
        }
        }
       // cout<<"flag="<<flag<<endl;
    if(flag==1)
    {
        cout<<"Negative Cycle Exists"<<endl;
        return 1;
    }
    return 0;
}
int main()
{
    int n=0,s,t=0;
    while(n<=3)
    {
      cout<<"Enter the the no of Vertices"<<endl;
      cin>>n;
      if(n<=3)
      cout<<"Enter valid no vertices"<<endl;
    }
    int *arr=(int*)malloc((n)*sizeof(int));
    for(int i=0;i<n;i++)
    arr[i]=INT_MAX;
   while(t<n-1)
   {
      cout<<"Enter the the no of edges in the graph"<<endl;
      cin>>t;
      if(t<n-1)
      cout<<"Enter valid no of edges"<<endl;
    }

    graph *gr = (graph*)malloc(t*sizeof(graph));
    cout<<"Enter Edge from source->distination =weight"<<endl;
    for(int i=0;i<t;i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        if(s!=d && (s>n || d>n || s<1 || d<1))
        {
            cout<<"RE-ENTER THE Edge"<<endl<<endl;
            i--;
        }
        else
        {
        if(checkvalidation(gr,i,s,d))
        {
            gr[i].s=s;gr[i].d=d;gr[i].w=w;
        }
        else
        {
            cout<<"RE-ENTER THE Edge"<<endl<<endl;
            i--;
        }
        }
    }
    s=-1;
    while(s<1 || s >n){
    cout<<"Enter the source vertex"<<endl;
    cin>>s;
        }
    arr[s-1]=0;
    long int temp;
    int flag=0,f=0;
    for(int j=1;j<n;j++)
    {
        flag=0;
        for(int i=0;i<t;i++)
        {
                if(arr[gr[i].s-1]!=INT_MAX){
                temp=arr[gr[i].s-1]+gr[i].w;
                if(arr[gr[i].d-1]>temp)
                    {
                        arr[gr[i].d-1]=temp;flag=1;
                    }
                }
                else
                f=1;
        }
        if(flag==0)break;
    }
   if(f!=1)
   if(checknegativecyle(gr,arr,t))
        {free(arr);free(gr);
            return 0;
        }

    cout<<"Final result"<<endl;
    cout<<"Source   Destination   Distance"<<endl;
    for(int i=0;i<n;i++)
    {
            if(i!=s-1){
                if(arr[i]==INT_MAX)
                cout<<s<<"            "<<i+1<<"         INFINITY";
                else
                cout<<s<<"            "<<i+1<<"         "<<arr[i];
            cout<<endl;
            }
    }

}
