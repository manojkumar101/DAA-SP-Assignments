/*
E -> E*T | T
T -> T+F | F
F -> (E) | id

->removing left recursion
E -> TE'
E' -> *TE' | ε
T -> FT'
T' -> +FT' | ε
F -> (E) | id

*/

#include<bits/stdc++.h>
using namespace std;
void E();
void T();
void Eprime();
void Tprime();
void F();
int i=0,error=0;
char input[50];
int main()
{
    cout<<"Enter the string for validation"<<endl;
    cin>>input;
    E();
    if(strlen(input)==i&&error==0)
    cout<<"Accepted"<<endl;
    else
    cout<<"Rejected"<<endl;
}
void E()
{cout<<"E->TE'\n";
    T();
    Eprime();
}
void Eprime()
{
    if(input[i]=='*')
    {cout<<"E'->*TE'\n";
        i++;
        T();
        Eprime();

    }
    else
    cout<<"E'->epsilon\n";

}
void T()
{
    cout<<"T -> FT'\n";
    F();
    Tprime();

}
void Tprime()
{
    if(input[i]=='+')
    {
        cout<<"T'->+FT'\n";
        i++;
        F();
        Tprime();

    }
    else
    cout<<"T'->epsilon\n";

}
void F()
{
    if(isalnum(input[i]))
    {
        i++;
        cout<<"F->id\n";
    }
    else if(input[i]=='(')
            {
                i++;
                E();
                i++;
                if(input[i]==')')
                   {
                     i++;
                     cout<<"F->(E)\n";
                   }
                else
                    error=1;
            }
    else
    error=1;

}
