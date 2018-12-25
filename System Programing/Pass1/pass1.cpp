#include<bits/stdc++.h>
using namespace std;

struct optab		//mnemonic opcode	class 	mnemonic info
					//START				AD   	01
{
	string operation;
	string cls; //class of operation (type)
	string opcode;
}optab[18];

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

struct reg //registers
{
	string register_type;
	int index;
}reg[5];

struct compare //comparison statements
{
	string compare_type;
	int index;
}compare[7];

int is_assembly_directive(vector<string> s)
{
	for(int i=0;i<s.size();i++)
		if(s[i]=="START" || s[i]=="END" || s[i]=="LTORG" || s[i]=="EQU" || s[i]=="ORIGIN")
			return 1;
	return 0;
}

int is_in_optab(string s)
{
	for(int i=1;i<18;i++)
		if(optab[i].operation==s)
			return i;
	return 0;
}

int is_register(string s)
{
	for(int i=1;i<5;i++)
		if(reg[i].register_type==s)
			return i;
	return 0;
}

int is_comparative(string s)
{
	for(int i=1;i<7;i++)
		if(compare[i].compare_type==s)
			return i;
	return 0;
}

int is_symbol(string s,int n)
{
	for(int i=1;i<n;i++)
		if(symtab[i].symbol==s)
			return i;
	return 0;
}

int is_literal(string s,int n,int cpool)
{
	for(int i=1;i<n;i++)
		if(littab[i].value==s && littab[i].pool==cpool)
			return i;
	return 0;
}

int stoi_ds(string s)
{
	int ans=0;
	ans=s[0]-'0';
	return ans;
}

void symbol_print(int n)
{
	for(int i=1;i<n;i++)
		cout<<symtab[i].index<<" "<<symtab[i].symbol<<" "<<symtab[i].address<<endl;
}

void literal_print(int n)
{
	for(int i=1;i<n;i++)
		cout<<littab[i].index<<" "<<littab[i].value<<" "<<littab[i].address<<" "<<littab[i].pool<<endl;
}

int main()
{
	//PASS I
	freopen("mot_input.txt","r",stdin);
	freopen("pass1_output.txt","w",stdout);
	int i;
	for(i=1;i<18;i++)
		cin>>optab[i].operation>>optab[i].opcode>>optab[i].cls;
	for(i=1;i<5;i++)
		cin>>reg[i].register_type>>reg[i].index;
	for(i=1;i<7;i++)
		cin>>compare[i].compare_type>>compare[i].index;
	cin.clear();
	freopen("pass1_input.txt","r",stdin);
	int location_counter=0,index=0,symbol_count=1,literal_count=1,current_pool=1;
	string read_each_line;
	while(getline(cin,read_each_line)) //read pass1_input.txt line by line
	{
		vector<string> v;
		istringstream iss(read_each_line);
		copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(v)); //insert every word of read_each_line in vector
		/*
		START 100						(AD,01) (C,100)
		A DS 3							100 (DL,01) (C,3)
		ADD CREG , ='5'					103 (IS,01) 3 (L,1)
		L1 : MOVER AREG , B 			104 (IS,04)	1 (S,3)
		ADD AREG , C 					105 (IS,01) 1 (S,5)
		MOVEM AREG , D 					106 (IS,05) 1 (S,5)
		LTORG 							(AD,05)
		D : SUB BREG , L1				108 (IS,02) 2 (S,2) 
		MOVEM AREG , ='10'				109 (IS,05) 1 (L,2)
		L2 EQU D 						(AD,03) (S,5)
		C DC '5'						110 (DL,02) (C,'5')
		B : MOVEM BREG , ='1'			111 (IS,05) 2 (L,3)
		MOVEM BREG , ='5'				112 (IS,05) 2 (L,4)
		END								(AD,02)
		*/
		if(!is_assembly_directive(v))
			cout<<++location_counter<<" ";
		for(i=0;i<v.size();i++)
		{
			if(v[i]!=",")
			{
				index=is_in_optab(v[i]);
				if(!index)
				{
					index=is_register(v[i]);
					if(!index)
					{
						index=is_comparative(v[i]);
						if(!index)
						{
							index=is_symbol(v[i],symbol_count);
							if(!index && isalpha(v[i][0]) && (i==0 || i==v.size()-1))
							{
								symtab[symbol_count].index=symbol_count;
								symtab[symbol_count].symbol=v[i];
								if(i==0)
									symtab[symbol_count].address=location_counter;
								else
									symtab[symbol_count].address=-1;
								symbol_count++;
							}
							index=is_literal(v[i],literal_count,current_pool);
							if(!index && v[i][0]=='=')
							{
								littab[literal_count].index=literal_count;
								littab[literal_count].value=v[i];
								littab[literal_count].address=-1;
								littab[literal_count].pool=current_pool;
								literal_count++;
							}
						}
						else
							cout<<compare[index].index<<" ";
					}
					else
						cout<<reg[index].index<<" ";
				}
				else
					cout<<"("<<optab[index].cls<<","<<optab[index].opcode<<") ";
				if(i>0 && v[i-1]=="START" && isdigit(v[i][0]))
				{
					cout<<"(C,"<<v[i]<<") ";
					location_counter=stoi(v[i])-1;
				}
				if(v[i]=="LTORG" || v[i]=="END")
				{
					for(int j=1;j<literal_count;j++)
						if(littab[j].address==-1)
							littab[j].address=++location_counter;
					current_pool++;
				}
				index=is_symbol(v[i],symbol_count);
				if(index)
				{
					if(i==0)
						symtab[index].address=location_counter;
					else
						cout<<"(S,"<<symtab[index].index<<") ";
				}
				index=is_literal(v[i],literal_count,current_pool);
				if(index)
					cout<<"(L,"<<littab[index].index<<") ";
				if(i>0 && v[i-1]=="DC" && isdigit(v[i][1]))
					cout<<"(C,"<<v[i]<<") ";
				if(i>0 && v[i-1]=="DS" && isdigit(v[i][0]))
				{
					cout<<"(C,"<<v[i]<<") ";
					location_counter+=stoi_ds(v[i])-1;
				}
				if(v[i]=="EQU")
				{
					int left=is_symbol(v[i-1],symbol_count),right=is_symbol(v[i+1],symbol_count);
					if(left && right)
						symtab[left].address=symtab[right].address;
				}
			}
		}
		cout<<endl;
	}
	cout.clear();
	freopen("table_output.txt","w",stdout);
	cout<<"----SYMBOL TABLE----"<<endl;
	cout<<"Index Symbol Address"<<endl;
	for(i=1;i<symbol_count;i++)
		cout<<symtab[i].index<<"\t\t"<<symtab[i].symbol<<"\t\t"<<symtab[i].address<<endl;
	cout<<"\n----LITERAL TABLE----"<<endl;
	cout<<"Index Value Address Pooltab"<<endl;
	for(i=1;i<literal_count;i++)
		cout<<littab[i].index<<"\t\t"<<littab[i].value<<"\t"<<littab[i].address<<"\t\t"<<littab[i].pool<<endl;

	cin.clear();
	cout.clear();
	freopen("pass2_input.txt","w",stdout);
	symbol_print(symbol_count);
	cout<<"-1 NULL -1"<<endl;
	literal_print(literal_count);
	cout<<"-1 NULL -1 -1"<<endl;

	return 0;
}
