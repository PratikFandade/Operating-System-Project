#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fp,*fp1;
char buffer[40];
char M[300][4];
char IR[4];
char R[4];
int PTR,IC,SI,PI,TI;
int ranum[30] = {0};
int C;

typedef struct PCB{
    int tll;
    int ttl;
    int llc;
    int ttc;
    int jobid;
}PCB;
PCB *pcb;
void init_pcb()
{
    pcb = (PCB*)malloc(sizeof(PCB));
    pcb->llc = 0;
    pcb->ttc = 0;
    char temp[4];
    temp[0]=buffer[4];
    temp[1]=buffer[5];
    temp[2]=buffer[6];
    temp[3]=buffer[7];
      pcb->jobid=atoi(temp);
      /* Extract Total Time limit */
    temp[0]=buffer[8];
    temp[1]=buffer[9];
    temp[2]=buffer[10];
    temp[3]=buffer[11];
      pcb->ttl=atoi(temp);
      //ttl = pcb->TTL;
      /* Extract Total buffer Limit */
    temp[0]=buffer[12];
    temp[1]=buffer[13];
    temp[2]=buffer[14];
    temp[3]=buffer[15];
      pcb->tll=atoi(temp);
      //tll = pcb->TLL;

}

void read()
{
    printf("\nIn Read\n");
    SI=0;
    IR[3]='0';
    char temp;
    int val=((int)IR[2] -48)*10 + ((int)IR[3] -48);
    int i,p=0,j;
    memset(buffer,0,40);
        for(i=0;i<40&&getc(fp)!=EOF;i++)
		{
		    fseek(fp,-1L,SEEK_CUR);
			temp = (char)(getc(fp));
			if(temp=='\n')
				break;
			//store in buffer

			buffer[i]=temp;

		}
		printf("\nBuffer contents\n");
        for(i=0;i<40;i++)printf("%c ",buffer[i]);
        printf("\n");

		if(buffer[0]!='$')
		{
		int ra=admap(val);
		int sh=ra;

		do{


		for(j=0;j<4&&buffer[p]!='\n'&&buffer[p]!=NULL;j++)
		{

			M[ra][j]=buffer[p++];

		}
			ra++;
		}while(buffer[p]!=NULL&&buffer[p]!='\n');

		printf("\nMemory\n");
						for(i=sh;i<=sh+9;i++)
                        {
                            printf("M[%d]=",i);
                            for(j=0;j<4;j++)
                            {
                                printf("%c",M[i][j]);
                            }
                            printf("\n");
                        }


		exec_user_prog();
		}
		else
		{

			terminate(1);
		}



}

void write()
{
    printf("\nIn Write\n");
    SI=0;
    IR[3]='0';
    int val=((int)IR[2] -48)*10 + ((int)IR[3] -48);
    pcb->llc++;
		if(pcb->llc>pcb->tll)
			terminate(2);
		else
		{
		int j=0,i=0;

			int ra=admap(val);
			while(i<10)
			{

				if(M[ra][j]!='\n'&&M[ra][j]!=NULL&&M[ra][j]!='$')
                    fputc(M[ra][j],fp1);
				j++;
				if(j==4)
				{
					ra++;
                    i++;
					j=0;
				}

			}


		fputc('\n',fp1);
		if(TI==0)
            exec_user_prog();        //check here
		}

}

void terminate(int em)
{
    switch(em)
		{
			case 0:
			fputs("No error",fp1);
			break;
			case 1:
			fputs("Out Of Data",fp1);
			break;
			case 2:
			fputs("Line Limit Exceeded",fp1);
			break;
			case 3:
			fputs("Time Limit Exceeded",fp1);
			break;
			case 4:
			fputs("Operation Code Error",fp1);
			break;
			case 5:
			fputs("Operand Error",fp1);
			break;
			case 6:
			fputs("Invalid Page Fault",fp1);
			break;
			case 7:
			fputs("Time Limit Exceeded and Operation Code Error",fp1);
			break;
			case 8:
			fputs("Time Limit Exceeded and Operand Error",fp1);
			break;

		}
		fputc('\n',fp1);
		fputs("Job status - ID=",fp1);
        fprintf(fp1,"%d",pcb->jobid);
        fputs(" TTL=",fp1);
        fprintf(fp1,"%d",pcb->ttl);
        fputs(" TLL=",fp1);
        fprintf(fp1,"%d",pcb->tll);
        fputs(" TTC=",fp1);
        fprintf(fp1,"%d",pcb->ttc);
        fputs(" LLC=",fp1);
        fprintf(fp1,"%d",pcb->llc);
        fputs(" IC=",fp1);
        fprintf(fp1,"%d",IC);
        fputs(" IR=",fp1);
        fprintf(fp1,"%s",IR);


		fputc('\n',fp1);
		fputc('\n',fp1);
		fputc('\n',fp1);

}
void init()
{
    init_pcb();
    int i, j;
    for(i=0;i<300;i++)
    {
        for(j=0;j<4;j++)
        {
            M[i][j]='$';
        }
    }
    for(i=0;i<4;i++)
    {
        IR[i]='$';
        R[i]='$';
    }
    PTR = 0;
    IC = 0;
    SI = 0;
    PI = 0;
    TI = 0;
    for(i=0;i<30;i++)ranum[i]=0;
}
int admap(int va)
{
    int j;
    int PTE = PTR + (va/10);
    char temp[4];
    for(j=0;j<4;j++)
		temp[j]=M[PTE][j];

    int ra=30;

    if(temp[0]=='0'||temp[0]=='1'||temp[0]=='2')
    {
        ra = ((int)temp[0] -48)*10 + ((int)temp[1] -48);
    }
    if(ra>=0&&ra<30)
			{
				ra = ra*10;
				ra = ra + (va)%10;

			}
			else
            {
                PI = 3;
            }

            return(ra);
}

void MOS()
{
    printf("\nIn MOS with IR=%c%c SI=%d PI=%d TI=%d\n",IR[0],IR[1],SI,PI,TI);

		if(PI!=0)
		{
		if(TI==0)
		{
			if(PI==1)
				terminate(4);
			else if(PI==2)
				terminate(5);
			else if(PI==3)
			{


				if((IR[0]=='G'&& IR[1]=='D' ) ||  (IR[0]=='S'&& IR[1]=='R' ))
				{

					int ra=((int)IR[2] -48)*10 + ((int)IR[3] -48);
					int m= PTR + (ra/10);

					int t = allocate();
					printf("\nValid Page Fault Handled with Block No. - %d\n",t);
                    int j = t/10;
                    j=j+'0';
                    M[m][0]= j;
                    j = t%10;
                    j=j+'0';
                    M[m][1]= j;

					IC--;
					PI=0;
					exec_user_prog();



				}
				else
					terminate(6);            //check here

			}

		}
		else if(TI==2)
		{

			if(PI==1)
				terminate(7);
			else if(PI==2)
				terminate(8);
			else if(PI==3)
				terminate(3);
		}
		}
		else
		{
		if(TI==0)
		{
			if(SI==1)
				read();
			else if(SI==2)
				write();
			else if(SI==3)
				terminate(0);
		}
		else if(TI==2)
		{
			if(SI==1)
				terminate(3);
			else if(SI==2)
			{
				write();
				terminate(3);
			}
			else if(SI==3)
			{

				terminate(0);
			}
			else if(SI==0)
			{
				terminate(3);
			}
		}

		}
}


void exec_user_prog()
{
    int i;
    int ra = admap(IC);

    if(PI==0)
			{
				IR[0]=M[ra][0];
				if(M[ra][1]!='\n'&&M[ra][1]!='$'&&IR[0]!='H')
				{
					IR[1]=M[ra][1];
					IR[2]=M[ra][2];
					IR[3]=M[ra][3];

					printf("\nIR=%s\n",IR);

					IC++;
					int m=(int)IR[3] -48;
					int n=(int)IR[2] -48;
					if(m<10 && n<10 && m>=0 && n>=0)
					{
					n=(n*10)+m;
					ra=admap(n);
					}
					else
                        PI = 2;


                    if(PI==0)
                    {
                            if(IR[0]=='L'&&IR[1]=='R')
                            {
                                printf("\nIn LR\n");
                                for(i=0;i<4;i++)
                                {
                                    R[i]=M[ra][i];

                                }
                            }


						else if(IR[0]=='S'&&IR[1]=='R')

                            {
                                printf("\nIn SR\n");

							for(int i=0;i<4;i++)
                                M[ra][i]=R[i];
							}

                        else if(IR[0]=='C'&&IR[1]=='R')
                        {
                            printf("\nIn CR\n");
							int a;

							for(a=0;a<4;)
							{
							if(M[ra][a]==R[a])
                                a++;
							else
                                break;
							}

							if(a==4)
                                C=1;
							else
                                C=0;
                        }

						else if(IR[0]=='B'&&IR[1]=='T')
                        {
                            printf("\nIn BT\n");

							if(C==1)
                                IC=((int)IR[2] -48)*10 + ((int)IR[3] -48);
                        }

						else if(IR[0]=='G'&&IR[1]=='D')
                        {
                            printf("\nIn GD\n");
                            SI = 1;
                        }
						else if(IR[0]=='P'&&IR[1]=='D')
                        {
                            printf("\nIn PD\n");
                            SI = 2;
                        }
						else PI=1;
                    }
				}
				else if(IR[0]=='H')
                {
                    printf("\nIn H\n");
                    IC++;
                    SI=3;
                }
                else
                    PI = 1;

			}

            pcb->ttc++;
            if(pcb->ttc>=pcb->ttl)
                TI=2;

            if(TI!=0||PI!=0||SI!=0)
			{
				MOS();
			}
			else
                exec_user_prog();


}
void Start()
{
    IC=0;
    exec_user_prog();
}


int allocate()
{
    int n;
    n = rand()%30;
    while(ranum[n]==1)
        n = (rand()%30);
    ranum[n]=1;
//    printf("\n%d = %d\n",n,ranum[n]);
    return n;

}

void load()
{
    int i,k;
    char temp;
    while(getc(fp)!=EOF)
    {
        fseek(fp,-1L,SEEK_CUR);
        memset(buffer,0,40);
        for(i=0;i<40&&getc(fp)!=EOF;i++)
		{
		    fseek(fp,-1L,SEEK_CUR);
			temp = (char)(getc(fp));
			if(temp=='\n')
				break;
			//store in buffer

			buffer[i]=temp;

		}
        //fgets(buffer,41,fp);
        printf("\nBuffer contents\n");
        for(i=0;i<40;i++)printf("%c ",buffer[i]);
        printf("\n");

        if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2] =='M' && buffer[3] == 'J')
        {
                printf("\nProcess started\n");
               //t=0;
                init();
                PTR = allocate();
                PTR = 10*PTR;
                k=PTR;
                printf("\nPTR = %d\n",PTR);
        }
        else if(buffer[0] == '$' && buffer[1] == 'D' && buffer[2] =='T' && buffer[3] == 'A')
        {
            printf("\nIn DTA\n");
            Start();
        }

        else if(buffer[0] == '$' && buffer[1] == 'E' && buffer[2] =='N' && buffer[3] == 'D')
            {
                printf("\nJob Ended\n");
                continue;
            }

        else
            {
                //int k = PTR;
                IC = allocate();
                int j = IC/10;
                j=j+'0';
                M[k][0]= j;
                j = IC%10;
                j=j+'0';
                M[k][1]= j;
                IC = IC*10;
                int sh=IC;

                j=0;
						while(j<40&&buffer[j]!=NULL&&buffer[j]!='\n')
						{
							for(i=0;i<4&&buffer[j]!='\n';i++)
							{
								M[IC][i]=buffer[j++];

							}
							IC++;

						}

						printf("\nMemory\n");
						for(i=sh;i<=sh+9;i++)
                        {
                            printf("M[%d]=",i);
                            for(j=0;j<4;j++)
                            {
                                printf("%c",M[i][j]);
                            }
                            printf("\n");
                        }
               k++;

            }

    }

    fclose(fp);
    fclose(fp1);
}


int main()
{
    fp = fopen("input_phase2.txt","r");
    fp1 = fopen("output_phase2.txt","w");

    load();
    return(0);
}
