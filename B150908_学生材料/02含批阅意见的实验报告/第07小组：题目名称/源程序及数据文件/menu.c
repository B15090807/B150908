#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"file.h"
#include"consumption.h"

void printHead( )      /*��ӡѧ��������Ϣ�ı�ͷ*/
{
	printf("%s\t        %s\t%s\t%s\t%s\t\n","����","����","����","����","��ͨ");
}

void menu( )         /*����˵�����*/
{
		printf("\n");
		printf("************ 1. ��ʾ�����˵���Ϣ  ************\n");
		printf("************ 2. ������Ϣ����      ************\n");
		printf("************ 3. ������Ϣ����      ************\n");
		printf("************ 4. ������Ϣͳ��      ************\n");
        printf("************ 5. ����������ѯ      ************\n");
		printf("************ 0. �˳�              ************\n");
}

void menuBase( )     /*2��������Ϣ����˵�����*/
{
		printf("\n");
		printf("%%%%%%%%%%%% 1. ���һ���˵�      %%%%%%%%%%%%\n");
		printf("%%%%%%%%%%%% 2. ɾ��һ���˵�      %%%%%%%%%%%%\n");
		printf("%%%%%%%%%%%% 3. �޸�һ���˵�      %%%%%%%%%%%%\n");
		printf("%%%%%%%%%%%% 0. �����ϲ�˵�      %%%%%%%%%%%%\n");
}

void menuScore( )     /*3��������Ϣ����˵�����*/
{
		printf("\n");
		printf("@@@@@@@@@@@@ 1. ����ÿ�����ѵ��ܶ� @@@@@@@@@@@\n");
		printf("@@@@@@@@@@@@ 2. ����ÿ�ս������   @@@@@@@@@@@\n");
		printf("@@@@@@@@@@@@ 0. �����ϲ�˵�       @@@@@@@@@@@\n");
}

void menuCount( )    /*4��������Ϣͳ�Ʋ˵�����*/
{
	    printf("\n");
		printf("&&&&&&&& 1. ĳ��ĳ�������ܶ�          &&&&&&&&\n");
		printf("&&&&&&&& 2. ĳ��ĳ����Ŀ���ѱ���      &&&&&&&&\n");
		printf("&&&&&&&& 3. ĳ��ĳ�³���Ԥ��������  &&&&&&&&\n");
		printf("&&&&&&&& 0. �����ϲ�˵�              &&&&&&&&\n");
}

void menuSearch()    /*5������������ѯ�˵�����*/
{
		printf("\n");
		printf("######## 1. �����ڣ��꣩��ѯ�˵�����  ########\n");
		printf("######## 2. �����ڣ��£���ѯ�˵�����  ########\n");
		printf("######## 3. �����ڣ��գ���ѯ�˵�����  ########\n");
		printf("######## 0. �����ϲ�˵�              ########\n");
}

int baseManage(Consumption con[],int n)    																/*�ú�����ɻ�����Ϣ����*/
																										/*�����ڽ��в���ɾ���޸ģ����ڲ����ظ�*/
{  
	int choice,t, find[NUM];
    Consumption c;
	do{   
	menuBase( );																						/*��ʾ��Ӧ�Ķ����˵�*/
	printf(" ��������ִ�еĲ˵���Ŀ:");
		     scanf("%d",&choice);																		/*����ѡ��*/
		     switch(choice)
		     {
			   case 1:	readCon(&c,1);																	/*����һ������������Ѽ�¼*/
						n=insertCon(con,n,c);															/*���ú����������Ѽ�¼*/
					 break;
			   case 2:  printf(" �������ɾ�������ڣ�year month day��\n");
					    scanf("%d%d%d",&c.date.year,&c.date.month,&c.date.day);							/*����һ����ɾ���ļ�¼*/
					    n=deleteCon(con,n,c);															/*���ú���ɾ��ָ�����ڵ����Ѽ�¼*/
					 break;
			   case 3:  printf(" ��������޸ĵ����ڣ�year month day��\n");
					    scanf("%d%d%d",&c.date.year,&c.date.month,&c.date.day);							/*����һ�����޸ĵļ�¼*/
						t=searchCon(con,n,c,3,find) ;													/*���ú�������ָ�����ڵ����Ѽ�¼*/
						 if (t)																			/*��������ѵļ�¼����*/
						{
							readCon(&c,1);																/*����һ�����������Ѽ�¼��Ϣ*/
							con[find[0]] = c;															/*���ն���ļ�¼��ֵ����Ҫ�޸ĵ������¼*/ 					 
						}					 
						else																			/*�����date�ļ�¼������*/ 
						printf(" ��������ڲ����ڣ���˶Ժ��������룡\n");					/*�����ʾ��Ϣ*/
					 break;
			   case 0: break;
		    }
	}while(choice);
	return n;																							/*���ص�ǰ�����������ʵ�ʼ�¼����*/
}

void scoreManage(Consumption con[],int n)																/*�ú������������Ϣ������*/
{  
	int choice;
	do
	{
		menuScore( );																					/*��ʾ��Ӧ�Ķ����˵�*/
		printf(" ��������ִ�еĲ˵���Ŀ:");
		scanf("%d",&choice);																			/*�������ѡ��*/
		switch(choice)
		{
			case 1:   calcuTotal(con,n);																/*������ÿ�����ѽ����ܶ�*/
					  printCon(con, n, 2);
					  break;
			case 2:   calcuTotal(con,n);																/*������ÿ�����ѽ����ܶ�*/
					  calcuRank(con,n);																	/*����ÿ�����ѽ����ܶ�������*/
				      printCon(con, n, 3);
				      break;		
			case 0:   break;
		}
	}while(choice);
}

void countManage(Consumption con[],int n)																/*�ú������������Ϣͳ�ƹ���*/
{
		int choice,i,temp;
		int find[NUM],f;
		double sum,sum0,sum1,sum2,sum3;
		double spend = 0;
		Consumption c;
		sortCon(con, n);
		calcuTotal(con, n);
		do
		{
			menuCount( );																				/*��ʾ��Ӧ�Ķ����˵�*/
			printf(" ��������ִ�еĲ˵���Ŀ:");
			scanf("%d",&choice);
			readDate(&c, 2);
			f = searchCon(con, n, c,2,find);
			if (f)
			{
				switch(choice)
				{
					case 1:	printHead();																/*ʵ��ĳ��ĳ�������ܶ��*/
							for (sum = 0,i = 0; i < f; i++)
							{
								sum += con[find[i]].total;
								printCon(&con[find[i]],1,4);
							}
							printf(" %d��%d�¸��������ܽ��Ϊ : %.2f\n",c.date.year,c.date.month,sum);
						  break;
					case 2:	sum0 = sum1 = sum2 = sum3 = 0;                     							/*ʵ��ĳ��ĳ����Ŀ���ѱ�������*/
							printHead(); 
							for (i = 0; i < f; i++)
							{
								sum0 += con[find[i]].fourObj[0];
								sum1 += con[find[i]].fourObj[1];
								sum2 += con[find[i]].fourObj[2];
								sum3 += con[find[i]].fourObj[3];
								printCon(&con[find[i]],1,4);
							}
							for (sum = 0,i = 0; i < f; i++)
							{
								sum += con[find[i]].total;
							}
							printf("������ܶ�      %.2f\t%.2f\t%.2f\t%.2f\t\n",sum0,sum1,sum2,sum3);
							printf("����ռ�ܶ�      %.2f%%\t%.2f%%\t%.2f%%\t%.2f%%\t\n",(sum0 / sum * 100),(sum1 / sum * 100),(sum2 / sum * 100),(sum3 / sum * 100));
						  break;
					 case 3:																			/*ʵ��ĳ��ĳ�³���Ԥ������������*/
							printf(" �����������Ԥ�� :");
							scanf("%lf",&spend);
							for (i = 0,temp = 0; i < f; i++)
							{
								if (fabs(con[find[i]].total - spend) > 0)
								{
									temp++;
								}
							}
							printf(" %d��%d���г���Ԥ��������� :%d\n",c.date.year,c.date.month,temp);
						  break;
					  case 0:																			/*�����ϼ��˵�*/
						  break;
				}
			}
			else
				printf("��������ڲ����ڣ���˶Ժ��������룡");
		}while (choice);
}

void searchManage(Consumption con[],int n)																/*�ú�����ɸ���������ѯ����*/
{
    int i,choice,f,find[NUM];
	Consumption c;
	sortCon(con, n);
	   do
		{
			menuSearch( );																				/*��ʾ��Ӧ�Ķ����˵�*/
			printf(" ��������ִ�еĲ˵���Ŀ:");
			scanf("%d",&choice);
			readDate(&c,choice);																		/*�������ڲ�ѯ*/
		 	if (choice>=1 && choice<=3)
			{ 
				f=searchCon(con,n,c,choice,find);														/*���ҵķ�������Ԫ�ص��±����f������*/
				if (f)																					/*������ҳɹ�*/
				{
			   		printHead( );																		/*��ӡ��ͷ*/
					for (i=0;i<f;i++)																	/*ѭ������f������±�*/
	      			   printCon(&con[find[i]], 1, 4);													/*ÿ�����һ����¼*/
				}
				else
			    	printf(" ��ѯ���ڲ����ڣ���˶Ժ���������!\n");										/*������Ҳ���Ԫ�أ��������ʾ��Ϣ*/
		     }		
	    }while (choice);
}

int runMain(Consumption con[],int n,int choice)															/*����ģ�飬��Ӧ��һ���˵����¸�����ѡ��ִ��*/
{
		switch(choice)
		{
			case 1:
					sortCon(con,n);																		/*��������С�����˳�������¼*/ 
          			printCon(con,n, 1);																	/*��������С�����˳��������м�¼*/
					break;
			case 2: n=baseManage(con,n);																/* 2. ������Ϣ����*/
			   	     break;
			case 3: scoreManage(con,n);																	/* 3. ������Ϣ����*/
					break;
			case 4: countManage(con,n);																	/* 4. ������Ϣͳ��*/
					break;
			case 5: searchManage(con,n);																/* 5. ����������ѯ*/
				     break;
          case 0: break;
		}
		return n;
}

int main( )
{
	Consumption con[NUM];																				/*����ʵ��һά����洢����                                                                                                                                                 ��¼*/
    int choice,n;
	n=readFile(con);																					/*���ȶ�ȡ�ļ�����¼�������ظ�ֵ��n*/      
	if (!n)																								/*���ԭ�����ļ�Ϊ��*/
	{
		n=createFile(con);																				/*������Ҫ�����ļ����Ӽ����϶���һϵ�м�¼�����ļ�*/       
	}	 	 
	do
	{
		menu();																							/*��ʾ���˵�*/
	    printf(" ��������ִ�еĲ˵���Ŀ: ");
	    scanf("%d",&choice);
	    if (choice >= 0 && choice <= 5)
	         n=runMain(con,n,choice);																	/*ͨ�����ô˺�������һ���������ѡ��ִ��*/         
	    else 
		     printf(" ���������˶Ժ����´�����!\n");
	} while (choice);
	sortCon(con,n);																						/*�����ļ�ǰ��date��С��������*/               
	saveFile(con,n);																					/*����������ļ�*/                        
    return 0;
}


