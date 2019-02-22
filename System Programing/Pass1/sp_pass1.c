#include<stdio.h>
#include<string.h>
#define MAX 20


int  LitCnt=1,PoolCnt ,TokCnt,LC,i,j,k,symcount=1,flag1=1,lctemp;
char Tok1[MAX],Tok2[MAX],Tok3[MAX],Tok4[MAX],Tok5[MAX],Buffer[80],temp[MAX];

struct mot
{
    char name[20];
    int value;
}mot[11];

struct ds
{
    char  name[10];
    int value;
}ds[5];
struct pot
{
    char name[20];
    int value;
}pot[5];

struct reg
{
    char name[20];
    int value;
}reg[4];

struct compare
{
    char name[20];
    int value;
}compare[6];

struct lt
{
    char name[20];
    int value;
    int flag;
}lt[10];

struct symbol
{
    char name[20];
    int value;
}symbol[10];

int searchmot(char *s,struct mot mot[])
{
    int i;
    for(i=0;i<10;i++)
    {
        if(strcmp(mot[i].name,s)==0)
            return i;
    }

    return -1;
}

int searchpot(char *s,struct pot pot[])
{
    int i;
    for(i=0;i<5;i++)
    {
        if(strcmp(pot[i].name,s)==0)
            return i+1;
    }

    return -1;
}

int searchcompare(char *s,struct compare compare[])
{
    int i;
    for(i=0;i<6;i++)
    {
        if(strcmp(compare[i].name,s)==0)
            return i+1;
    }

    return -1;
}
int searchreg(char *s,struct reg reg[])
{
    int i;
    for(i=0;i<4;i++)
    {
        if(strcmp(reg[i].name,s)==0)
            return i+1;
    }

    return -1;
}
int searchds(char *s,struct ds ds[])
{
    int i;
    for(i=0;i<2;i++)
    {
        if(strcmp(ds[i].name,s)==0)
            return i+1;
    }

    return -1;
}
int searchsym(char *s,struct symbol symbol[])
{
    int i;
    for(i=0;i<10;i++)
    {
        if(strcmp(symbol[i].name,s)==0)
            return i;
    }

    return -1;
}

int searchlt(char *s,struct lt lt[])
{
    int i;
    for(i=0;i<10;i++)
    {
        if(strcmp(lt[i].name,s)==0&&lt[i].flag==flag1)
            return i;
    }

    return -1;
}

int main()
{
	int nextLitCnt=1;


    strcpy(mot[0].name,"STOP");mot[0].value=0;
    strcpy(mot[1].name,"ADD");mot[1].value=1;
    strcpy(mot[2].name,"SUB");mot[2].value=2;
    strcpy(mot[3].name,"MULT");mot[3].value=3;
    strcpy(mot[4].name,"MOVER");mot[4].value=4;
    strcpy(mot[5].name,"MOVEM");mot[5].value=5;
    strcpy(mot[6].name,"COMP");mot[6].value=6;
    strcpy(mot[7].name,"BC");mot[7].value=7;
    strcpy(mot[8].name,"DIV");mot[8].value=8;
    strcpy(mot[9].name,"READ");mot[9].value=9;
    strcpy(mot[10].name,"PRINT");mot[10].value=10;

    strcpy(ds[0].name,"DC");ds[0].value=1;
    strcpy(ds[1].name,"DS");ds[1].value=2;

    strcpy(pot[0].name,"START");pot[0].value=1;
    strcpy(pot[1].name,"END");pot[1].value=2;
    strcpy(pot[2].name,"EQU");pot[2].value=3;
    strcpy(pot[3].name,"ORIGIN");pot[3].value=4;
    strcpy(pot[4].name,"LTORG");pot[4].value=5;

    strcpy(reg[0].name,"AREG");reg[0].value=1;
    strcpy(reg[1].name,"BREG");reg[1].value=2;
    strcpy(reg[2].name,"CREG");reg[2].value=3;
    strcpy(reg[3].name,"DREG");reg[3].value=4;

    strcpy(compare[0].name,"LT");compare[0].value=1;
    strcpy(compare[1].name,"LE");compare[1].value=2;
    strcpy(compare[2].name,"GT");compare[2].value=3;
    strcpy(compare[3].name,"GE");compare[3].value=4;
    strcpy(compare[4].name,"EQ");compare[4].value=5;
    strcpy(compare[5].name,"ANY");compare[5].value=6;

//----------------start of file handling------------------

       FILE *fp1=fopen("input.txt","r");

        if(fp1==NULL)
        {
            printf("\nCannot Open Input File\n");
            return 0;
        }

        FILE *fp2=fopen("output.txt","w");

        if(fp2==NULL)
        {
            printf("\nCannot Create File\n");
            return 0;
        }

        while(fgets(Buffer,50,fp1))
        {
            TokCnt=sscanf(Buffer,"%s%s%s%s",Tok1,Tok2,Tok3,Tok4);

            switch(TokCnt)
            {
                case 1: i=searchmot(Tok1,mot);
                        if(i==0)
                        {
                        	if(lctemp!=0)
                        	{
                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
                        		lctemp=0;
                        		break;
							}
                            fprintf(fp2,"(%03d) (IS %02d)\n",LC++,i);
                            break;
                        }

                       i=searchpot(Tok1,pot);
                       if(i==5)
                       {
                            int k;
                            for(k=1;k<LitCnt;k++)
                            {
                                lt[k].value=LC;
                                fprintf(fp2,"(%03d) (%s)\n ",LC++,lt[k].name);

                            }
                            nextLitCnt=LitCnt;
                            flag1++;
                       }

                       else if(i==2)
                       {
                            int k;
                            for(k=nextLitCnt;k<LitCnt;k++)
                            {
                                lt[k].value=LC;
                                fprintf(fp2,"(%03d) (%s)\n ",LC++,lt[k].name);
							}
                       }
                       break;
                case 2: i=searchpot(Tok1,pot);
                        if(Tok1[strlen(Tok1)-1]==':')
                        {
                            char temp[10];
                            int l;
                            for(l=0;Tok1[l]!=':';l++)
                            {
                                temp[l]=Tok1[l];
                            }
                            temp[l]='\0';
                            i=searchsym(temp,symbol);
                            if(i==-1)
                            {
                                strcpy(symbol[symcount].name,temp);
                                symbol[symcount++].value=LC;
                            }
                            symbol[i].value=LC;
                            int s=searchmot(Tok2,mot);
                            if(lctemp!=0)
                        	{
                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
                        		lctemp=0;
                        		break;
							}
                            fprintf(fp2,"(%03d) (IS %d)\n ",LC++,s);
                            break;
                        }
                        if(i==1)
                        {
                            LC=atoi(Tok2);
                            fprintf(fp2,"(AD, %02d) (C, %03d)\n",i,LC);
                            break;
                        }

                        if(i==4)
                        {
                            char temp1[10],temp2[10];
                            int j,k;
                            for(j=0;Tok2[j]!='+';j++)
                            {
                                temp1[j]=Tok2[j];
                            }
                            temp1[j]='\0';
                            int t=0;
                            for(k=j+1;Tok2[k]!='\0';k++)
                            {
                                temp2[t++]=Tok2[k];
                            }
                            temp2[t]='\0';
                            int inc=atoi(temp2);
                            int lc=searchsym(temp1,symbol);
                            if(lc!=-1)
                            {
                                lctemp=symbol[lc].value+inc;
                            }
                            else
                            {
                                printf("Symbol not Present!!!\n");
                            }
                            break;
						}
						break;
                case 3: i=searchmot(Tok1,mot);
                        if(i>=1&&i<=8)
                        {
                            int j=searchcompare(Tok2,compare);
                            if(j!=-1)
                            {
                                strcpy(symbol[symcount].name,Tok3);
                                symbol[symcount++].value=0;
                                if(lctemp!=0)
	                        	{
	                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
	                        		lctemp=0;
	                        		break;
								}
                                fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",LC++,i,j,symcount-1);
                                break;
                            }

                            char temp[10];
                            for(j=0;Tok2[j]!=',';j++)
                            {
                                temp[j]=Tok2[j];
                            }
                            temp[j]='\0';
                            int k=searchreg(temp,reg);
                            if(k!=-1)
                            {
                                    if(Tok3[0]=='=')
                                    {
                                    	char temp[10];
                                    	int p;
                                    	for(p=2;p<strlen(Tok3)-1;p++)
                                    	{
                                    		temp[p-2]=Tok3[p];
										}
										temp[p-2]='\0';
										int t=searchlt(temp,lt);
										if(t==-1)
										{
											strcpy(lt[LitCnt].name,temp);
											lt[LitCnt].value=-1;
											lt[LitCnt].flag=flag1;
											if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
				                        		lctemp=0;
				                        		break;
											}
											fprintf(fp2,"(%03d) (IS, %02d) (%03d) (L,%d)\n",LC++,i,k,LitCnt++);
                                            break;
										}
										else
										{
											if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
				                        		lctemp=0;
				                        		break;
											}
											fprintf(fp2,"(%03d) (IS, %02d) (%03d) (L,%d)\n",LC++,i,k,t);
                                            break;
										}

                                    }
                                    else
                                    {
                                    	int t=searchsym(Tok3,symbol);
										if(t==-1)
										{
											strcpy(symbol[symcount].name,Tok3);
	                                        symbol[symcount].value=-1;
	                                        if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
				                        		lctemp=0;
				                        		break;
											}
	                                        fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",LC++,i,k,symcount++);
	                                        break;
										}
										else
										{
											if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
				                        		lctemp=0;
				                        		break;
											}
											fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",LC++,i,k,t);
                                            break;
										}

                                    }
                            }
                            break;
                        }
				        int k=searchds(Tok2,ds);
                        if(k==1)
                        {
                            int t;
                            char temp[10];
                            for(t=1;t<strlen(Tok3)-1;t++)
                            {
                                temp[t-1]=Tok3[t];
                            }
                            temp[t-1]='/0';
                            t=atoi(temp);
                            i=searchsym(Tok1,symbol);
                            if(i==-1)
                            {
                                strcpy(symbol[symcount].name,Tok1);
                                symbol[symcount].value=LC;
                                if(lctemp!=0)
	                        	{
	                        		fprintf(fp2,"(%03d) (IS %02d)\n",lctemp,i);
	                        		lctemp=0;
	                        		break;
								}
                                fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",LC++,symcount++,k,t);
                                break;
                            }
                            symbol[i].value=LC;
                            if(lctemp!=0)
                        	{
                        		fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",lctemp,i,k,t);
                        		lctemp=0;
                        		break;
							}
                            fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",LC++,i,k,t);
                            break;
				        }
                        if(k==2)
                        {
                            i=searchsym(Tok1,symbol);
                            if(i==-1)
                            {
                                strcpy(symbol[symcount].name,Tok1);
                                if(lctemp!=0)
	                        	{
	                        		symbol[symcount].value=lctemp;
	                        		fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",lctemp,symcount++,k,atoi(Tok3));
	                        		lctemp=0;
	                        		LC=LC+atoi(Tok3);
	                        		break;
								}
								symbol[symcount].value=LC;
                                fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",LC,symcount++,k,atoi(Tok3));
                                LC=LC+atoi(Tok3);
                                break;
                            }
                            if(lctemp!=0)
	                        	{
	                        		symbol[i].value=lctemp;
	                        		fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",lctemp,i,k,atoi(Tok3));
	                        		lctemp=0;
	                        		LC=LC+atoi(Tok3);
	                        		break;
								}
                            symbol[i].value=LC;
                            fprintf(fp2,"(%03d) (S, %02d) (DL %03d) (C %d)\n",LC,i,k,atoi(Tok3));
                            LC=LC+atoi(Tok3);
                            break;
                        }
                        if(strcmp(Tok2,"EQU")==0)
                        {
                             i=searchsym(Tok3,symbol);
                             int j=searchsym(Tok1,symbol);
                             symbol[j].value=symbol[i].value;
                             break;
						}
                        break;
                case 4: printf(" ");
						char temp[10];
                        int l;
                        for(l=0;Tok1[l]!=':';l++)
                        {
                            temp[l]=Tok1[l];
                        }
                        temp[l]='\0';
                        i=searchsym(temp,symbol);
                        if(i==-1)
                        {
                        	strcpy(symbol[symcount].name,temp);
                            symbol[symcount++].value=LC;
						}
						else
						{
							symbol[i].value=LC;
						}
						i=searchmot(Tok2,mot);
                        if(i>=1&&i<=8)
                        {
                             char temp[10];
                            for(j=0;Tok3[j]!=',';j++)
                            {
                                temp[j]=Tok3[j];
                            }
                            temp[j]='\0';
                            int k=searchreg(temp,reg);
                            if(k!=-1)
                            {
                                    if(Tok4[0]=='=')
                                    {
                                    	char temp[10];
                                    	int p;
                                    	for(p=2;p<strlen(Tok4)-1;p++)
                                    	{
                                    		temp[p-2]=Tok4[p];
										}
										temp[p-2]='\0';
										int t=searchlt(temp,lt);
										if(t==-1)
										{
											strcpy(lt[LitCnt].name,temp);
											lt[LitCnt].value=-1;
											lt[LitCnt].flag=flag1;
											if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS, %02d) (%03d) (L,%d)\n",lctemp,i,k,LitCnt++);
				                        		lctemp=0;
				                        		break;
											}
											fprintf(fp2,"(%03d) (IS, %02d) (%03d) (L,%d)\n",LC++,i,k,LitCnt++);
                                            break;
										}
										else
										{
											fprintf(fp2,"(%03d) (IS, %02d) (%03d) (L,%d)\n",LC++,i,k,t);
                                            break;
										}

                                    }
                                    else
                                    {
                                    	int t=searchsym(Tok4,symbol);
										if(t==-1)
										{
											strcpy(symbol[symcount].name,Tok3);
	                                        symbol[symcount].value=-1;
	                                        if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",lctemp,i,k,symcount++);
				                        		lctemp=0;
				                        		break;
											}
	                                        fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",LC++,i,k,symcount++);
	                                        break;
										}
										else
										{
											 if(lctemp!=0)
				                        	{
				                        		fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",lctemp,i,k,t);
				                        		lctemp=0;
				                        		break;
											}
											fprintf(fp2,"(%03d) (IS, %02d) (%03d) (S,%d)\n",LC++,i,k,t);
                                            break;
										}

                                    }
                            }
                            else
                            {
                            	printf("Register not present!!!");
                            	return 0;
							}
                            break;
                        }
                        else
						{
                        	printf("IS not present!!!!");
                        	return 0;
						}
                        break;
			}
        }

    printf("Literal Table=====>\n");
    for(i=1;i<LitCnt;i++)
    {
    	printf("%s %d \n",lt[i].name,lt[i].value);
	}
	printf("\n");
	printf("Symbol Table=====>\n");
	for(i=1;i<symcount;i++)
    {
    	printf("%s %d\n",symbol[i].name,symbol[i].value);
	}
	printf("\n");
	printf("PoolTab====>\n");
	{
		printf("1\n");
		for(i=2;i<LitCnt;i++)
		{
			if(lt[i].flag!=lt[i-1].flag)
			 	printf("%d\n",i);
		}
	}
    return 0;
}


