#include <bits/stdc++.h>
using namespace std;

#define pb push_back

typedef vector<int> vi;
typedef map<int,vi> miv;

void tsp(int start,vi cities,int adjm[][25],map<miv,int> *dp,map<miv,miv> *path)
{
    vector<vi> subsets;
    int i,j,k;
    for(i=0;i<pow(2,cities.size());i++)
    {
        vi t;
        for(j=0;j<cities.size();j++)
        {
            if(i & (1<<j))
                t.pb(cities[j]);
        }
        subsets.pb(t);
    }

    //cout<<subsets.size()<<endl;

    sort(subsets.begin(), subsets.end(),
        [](const vector<int> &left,const vector<int> &right)
        {
            return left.size()<right.size();
        }
        );

    int x=-1;

    for(i=0;i<subsets.size();i++)
    {
        if(subsets[i].size()!=x)
        {
            x=subsets[i].size();
            cout<<endl<<"|S| = "<<x<<endl;
        }
        for(j=0;j<cities.size();j++)
        {
            int f=cities[j];
            vi ss=subsets[i]; //ss={2,3}
            if(subsets[i].size()==cities.size()) //reached {2,3,4,5}
            {
                f=start;
                if(j!=0)
                    break;
            }
            if(find(ss.begin(),ss.end(),f)==ss.end()) //f is not a part of the subset ss
            {
                miv cal;
                cal.insert({f,ss});
                miv::iterator it=cal.begin(); //cal=(4,{2,3})
                int st=it->first; //st=4
                vi s=it->second; //s={2,3}
                int cost=INT_MAX,tcost,t;
                int fst=st;
                vi fv;
                if(s.size()==0) //from a city to NULL set
                    cost=adjm[cities[j]][start];
                else
                {
                    for(k=0;k<s.size();k++)
                    {
                        vi p=s; //p={2,3}
                        t=p[k]; //t=2
                        p.erase(p.begin()+k); //p={3}

                        miv nss;
                        nss.insert({t,p}); //nss=(2,{3})

                        if(adjm[st][t]==INT_MAX  || dp->at(nss)==INT_MAX)
                            tcost=INT_MAX;
                        else
                            tcost=adjm[st][t]+dp->at(nss);
                        if(tcost<cost)
                        {
                            cost=tcost;
                            fst=t; //fst=2
                            fv=p; //fv={3}
                        }
                    }
                }
                cout<<"g("<<st<<",{ ";
                for(k=0;k<s.size();k++)
                    cout<<s[k]<<" ";
                if(cost==INT_MAX)
                    cout<<"}) = INF"<<endl;
                else
                    cout<<"}) = "<<cost<<endl;
                miv m;
                m.insert({fst,fv});
                path->insert({cal,m});
                dp->insert({cal,cost});
            }
        }
    }
}

void print(miv p,map<miv,miv> *path)
{
    miv::iterator i;
    for(i=p.begin();i!=p.end();i++)
    {
        int st=i->first;
        cout<<st<<"->";
        vi t=i->second;
        if(!t.size())
            return;
        miv tt=path->at(p);
        print(tt,path);
    }
}

int main()
{
    map<miv,int> dp; //cost from a vertex to a set of vertices
    map<miv,miv> path; //path --> from a city to other cities
                       //(1,{2,3,4,5})->(4,{2,3,5})->(2,{3,5})->(5,{3})->(3,{})
    vi cities;

    int ncities,start,i,j;

    cout<<"Enter the number of cities::";
    cin>>ncities;
    int adjm[25][25];

    cout<<"Enter the number adjacency matrix (-1 for INF)::"<<endl;

    for(i=1;i<=ncities;i++)
    {
        for(j=1;j<=ncities;j++)
        {
            cin>>adjm[i][j];
            if(adjm[i][j]==-1)
                adjm[i][j]=INT_MAX;
        }
    }

    cout<<"Enter the start city::";
    cin>>start;

    for(i=0;i<ncities;i++)
        cities.pb(i+1);

    cities.erase(cities.begin()+start-1);

    tsp(start,cities,adjm,&dp,&path);

    miv hh,hh1;
    hh.insert({start,cities}); //(1,{2,3,4,5})
    if(dp.at(hh)>=INT_MAX)
        cout<<endl<<"Tour not possible"<<endl;
    else
    {
        cout<<endl<<"Cost :: "<<dp.at(hh)<<endl;
        hh1=path.at(hh);
        cout<<endl<<"PATH"<<endl<<start<<"->";
        print(hh1,&path);
        cout<<start<<endl;
    }

    return cout<<endl,0;
}

/*
5
-1 20 30 10 11
15 -1 16 4 2
3 5 -1 2 4
19 6 18 -1 3
16 4 7 16 -1

*/
