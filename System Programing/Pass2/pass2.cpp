#include<bits/stdc++.h>
using namespace std;

int literal_count;

struct symtab		//index		symbol		address
					//1			A			100
{
	int index;
	string symbol;
	int address;
}symtab[50];

struct littab		//index		value		address
					//1			='5'		xxxxxxx
{
	int index;
	string value; //literal
	int address;
	int pool;
}littab[50];

void initialize()
{
	for(int i=1;;i++)
	{
		cin>>symtab[i].index>>symtab[i].symbol>>symtab[i].address;
		if(symtab[i].index==-1)
			break;
	}
	for(int i=1;;i++)
	{
		cin>>littab[i].index>>littab[i].value>>littab[i].address>>littab[i].pool;
		if(littab[i].index==-1)
			break;
		literal_count++;
	}
}

int main()
{
	//PASS II
	freopen("pass2_input.txt","r+",stdin);
	initialize();
	cin.clear();
	freopen("pass1_output.txt","r+",stdin);
	freopen("pass2_output.txt","w",stdout);
	int addr=0,i,k=1;
	string read_each_line;
	while(getline(cin,read_each_line))
	{
		vector<string> v;
		int flag=0;
		istringstream iss(read_each_line);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(v));
		if(isdigit(v[0][0]))
		{
			char q[5]="";
			int addre,l=0;
			addre=stoi(v[0]);
			//cout<<"Address::"<<addre<<endl;
			while(addr<addre)
			{
				cout<<addr<<endl;
				addr++;
			}
		}
		for(i=0;i<v.size();i++)
		{
			if(isdigit(v[i][0]))
				cout<<v[i]<<" ";
			else if(v[i][1]=='D' || v[i][1]=='I')
			{
				cout<<v[i][4]<<v[i][5]<<" ";
				if(v[i+1][1]=='C' && v[i][5]=='1')
				{
					char p[5]="";
					int l=0;
					for(int j=3;v[i+1][j]!=')';j++)
						p[l++]=v[i+1][j];
					addr+=p[0]-'0'-1;
					//cout<<"Address::"<<p<<" "<<addr<<endl;
				}
			}
			else if(v[i][1]=='L')
				cout<<littab[v[i][3]-'0'].address<<" ";
			else if(v[i][1] == 'S')
				cout<<symtab[v[i][3] - '0'].address<<" ";
			else if(v[i][1]=='A' && i==0)
			{
				flag=1;
				if(i+1<v.size() && v[i+1][1]=='C')
				{
					char p[5]="";
					int l=0;
					for(int j=3;v[i+1][j]!=')';j++)
						p[l++]=v[i+1][j];
					addr=stoi(p);
					//cout<<"Address::"<<v[i+1]<<" "<<p<<" "<<addr<<endl;
				}
				break;
			}
			else if(v[i][1]=='C')
				continue;
			else
				cout<<"---"<<" ";
		}
		//cout<<"Lit::"<<littab[k].address<<" "<<addr<<endl;
		if(flag==0)
		{
			cout<<endl;
			addr++;
		}
	}
	int l=literal_count;
	while(addr<=littab[l].address)
	{
		cout<<addr<<endl;
		addr++;
	}
	return 0;
}
