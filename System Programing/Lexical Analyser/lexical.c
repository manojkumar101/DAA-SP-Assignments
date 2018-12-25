#include<stdio.h>
#include<ctype.h>
#include<string.h>
void keyw(char *p);
int i=0,id=0,kw=0,num=0,op=0;
char keys[32][10]={"auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};
char seps[15]=" \t\n,;(){}[]#\"<>",oper[]="!%^&*-+=~|.<>/?";
typedef struct keywords
{
    char name[20];
    int index;
};
struct keywords key[50];
typedef struct literal
{
    char name[50];
    int index;
};
struct literal lit[50];
typedef struct identifier
{
    char name[20];
    int index;
};
struct identifier ident[50];
typedef struct operators
{
    char name;
    int index;
};
struct operators opp[50];


void keyw(char *p)
{
	int k,flag=0;
	for(k=0;k<=31;k++)
	{
		if(strcmp(keys[k],p)==0)
		{
            printf("%s          (Keyword %d)\n",p,k);
			strcpy(key[kw].name,p);
			key[kw++].index=k;
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
	    int z=0;
	    for(z=0;p[z]!='\0';z++)
	    if(!isdigit(p[z]))
            flag=1;

		if(flag==0 && isdigit(p[0]))
		{
            strcpy(lit[num].name,p);
			lit[num].index=num;
			num++;
			printf("%s          (Literal %d)\n",p,num-1);
		}
		else
		{
			if(p[0]!='\0' && (isalpha(p[0])|| p[0]=='_'))
			{
				strcpy(ident[id].name,p);
                ident[id].index=id;
				id++;
				printf("%s          (Identifier %d)\n",p,id-1);
			}
			else if(p[0]!='\0')
			printf("%s          Invalid identifier\n",p);
		}
	}
	i=-1;

}

int main()
{
	char ch,str[25];
	int j;
	char fname[50];
	FILE *f1;


	f1 = fopen("input.c","r");

	if(f1==NULL)
	{
		 printf("file not found");
		 exit(0);
	}
	while((ch=fgetc(f1))!=EOF)
	{
        	for(j=0;j<=14;j++)
		{
			if(ch==oper[j])
			{
			    str[i]='\0';
				keyw(str);
                printf("%c          (Operator %d)\n",ch,j);
                opp[op].name=ch;
                opp[op++].index=j;

			}
		}
		for(j=0;j<=14;j++)
		{
			if(i==-1)
			break;
			if(ch==seps[j])
			{
				if(ch=='"')
				{
					do
					{
						ch=fgetc(f1);
						printf("%c",ch);
					}while(ch!='"');
					printf("\t    argument\n");
					i=-1;
					break;
				}
				str[i]='\0';
				keyw(str);
				if(ch!=' ' && ch!='\n' && ch!='\t')
				printf("%c          (special character )\n",ch);
			}
		}
		if(i!=-1)
		{
			str[i]=ch;
			i++;
		}
		else
			i=0;
	}
        printf("\n---------------------------------------------------\n");
        printf("Keywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\n",kw,id,op,num);
        printf("\n----------------Printing Referernce Tables -----------\n");
    fclose(f1);
    return 0;
}
