/*��consumption.c�ļ�����������*/
#include "consumption.h"
#include <stdio.h>

int readCon(Consumption *con, int n)														/*�������ѽṹ��ĸ���ֵ����¼��NUMʱֹͣ*/
{
	int i,j;
	for (i=0; i<n; i++)
	{
		printf(" ��������ʾ����һ���˵���Ϣ\n");                                        /*������ʾ�����˵���Ϣ��������*/
		printf(" ����������\n");
		printf(" ��:  ");
		scanf("%d", &con[i].date.year);
		printf(" ��:  ");
		scanf("%d", &con[i].date.month);
		printf(" ��:  ");
		scanf("%d", &con[i].date.day);
		printf(" �밴˳��������������֡������ͨ�������� : ");                       /*������ʾ�����˵���Ϣ������廨��*/
		for (j=0; j<4; j++)
	    {
		    scanf("%lf",&con[i].fourObj[j]);
			//scanf("%s",&con[i].detail);	
		}
		con[i].rank=0;                                                                  /*������Ҫ�����ܷ������㣬��ֵ��Ϊ0*/
	}
	return i;                                                                           /*����ʵ�ʶ���ļ�¼����*/
}

void readDate(Consumption *c, int condition)											/*������������Ϊconsumption�������ڣ��ꡢ���¡�������*/
{                   
	Date date;
	int i;
	printf(" ����������\n");
	switch (condition)
	{
		case 1:	
			printf(" ������������������� (year):");									/*��������Ϣ*/
			scanf("%d",&date.year);
			c->date.year = date.year;
			break;
		case 2:																			/*����������Ϣ*/
			printf(" ������������������ݺ��·ݣ�year month��:");
			scanf("%d%d",&date.year,&date.month);
			c->date.year = date.year;
			c->date.month = date.month;
			break;
		case 3:																			/*������������Ϣ*/
			printf(" ���������������������գ�year month day��:");
			scanf("%d%d%d",&date.year,&date.month,&date.day);
			c->date.year = date.year;
			c->date.month = date.month;
			c->date.day = date.day;
			break;
	}
	for (i=0; i<4; i++)
	    {
		    c->fourObj[i] = 0;
			//c->detail[40] = "";
		}
		c->total = 0;
		c->rank = 0;
}

void printCon (Consumption *con, int n, int condition)									/*��������������Ѽ�¼��ֵ*/
{
    int i,j;
	switch(condition)
	{
	case 1: printf("%s\t        %s\t%s\t%s\t%s\t","����","����","����","����","��ͨ");
			for (i=0; i<n; i++)
			{
				printf("\n%d/%d/%d\t",con[i].date.year,con[i].date.month,con[i].date.day);
				for (j=0; j<4; j++)
				{	
					printf("%.2f\t",con[i].fourObj[j]);
				}
			}
		break;
	case 2: printf("%s\t        %s\t%s\t%s\t%s\t%s\t","����","����","����","����","��ͨ","�ܶ�");
			for (i=0; i<n; i++)
			{
				printf("\n%d/%d/%d\t",con[i].date.year,con[i].date.month,con[i].date.day);
				for (j=0; j<4; j++)
				{	
					printf("%.2f\t",con[i].fourObj[j]);
				}
				printf("%.2f\t",con[i].total);
			}
		break;
	case 3:	 printf("%s\t        %s\t%s\t%s\t%s\t%s\t%s\t","����","����","����","����","��ͨ","�ܶ�","����");
			for (i=0; i<n; i++)
			{
				printf("\n%d/%d/%d\t",con[i].date.year,con[i].date.month,con[i].date.day);
				for (j=0; j<4; j++)
				{	
					printf("%.2f\t",con[i].fourObj[j]);
				}
				printf("%.2f\t",con[i].total);
				printf("%d\t",con[i].rank);
			}
		break;
	case 4:
		for (i=0; i<n; i++)
		{
			printf("%d/%d/%d\t",con[i].date.year,con[i].date.month,con[i].date.day);
			for (j=0; j<4; j++)
			{
			printf("%.2f\t",con[i].fourObj[j]);
			}
			printf("\n");
		}
		break;
	}
}

void reverse(Consumption con[], int n)													/*���Ѽ�¼����Ԫ�ص�����*/
{
	Consumption temp;
	int i;
	for (i=0; i<n/2; i++)																/*ѭ������ΪԪ��������һ��*/
	{
		temp=con[i];
		con[i]=con[n-1-i];
		con[n-1-i]=temp;
	}
}

void calcuTotal(Consumption con[],int n)												/*����ÿ���������ѵ��ܽ��*/
{
	int i,j;
	for (i=0; i<n; i++)																	/*���ѭ�������ܵ����Ѽ�¼*/
	{
		con[i].total = 0;
		for (j=0; j<4; j++)																/*�ڲ�ѭ�������ĸ���Ŀ*/
		{
			con[i].total += con[i].fourObj[j];
		}
	}	
}

void calcuRank(Consumption con[],int n)                                                 /*�����ܽ��������ѵ����Σ������в�������*/
{
	int i , j ,minpos ;                       
	Consumption c;
	for (i = 0; i < n-1; i++)															/*�����ܽ��������ѣ���ѡ������ķ�������*/
	{
		minpos = i;
		for(j = i + 1; j < n; j++)
			if (con[minpos].total > con[j].total )
				minpos = j;
		if (i != minpos)
		{
			c = con[i];
			con[i] = con[minpos];
			con[minpos] = c;
		}
	}
	reverse(con,n);																		/*�����ã��������ܽ���ɴ�С������*/
	con[0].rank=1;																		/*��һ����¼������һ����1*/
	for (i=1; i<n; i++)																	/*�ӵڶ�����¼һֱ�����һ������ѭ��*/
	{
		if (con[i].total == con[i-1].total)												/*��ǰ��¼�������ڵ�ǰһ����¼��������ܽ�����*/
			con[i].rank=con[i-1].rank;													/*��ǰ��¼���ε��������ڵ�ǰһ����¼����*/ 
	    else
			con[i].rank=i+1;															/*�����ʱ��ǰ��¼�����������±��+1*/
	}
}

void sortCon(Consumption con[],int n)													/*ѡ�񷨸������ڣ������գ���С��������*/
{
	int i,j1,j2,j3,minpos;																/*minpos�����洢������СԪ�����ڵ��±�*/
	Consumption c;
	for (i=0;i<n-1;i++)																	/*����ѭ����n-1��*/
	{
		minpos=i;																		/*Ѱ�ұ�����СԪ�����ڵ��±�*/
			for (j1=i+1; j1<n; j1++)
			{
				if (con[i].date.year > con[j1].date.year)
					minpos=j1;
			}
			if (i!=minpos)																/*��֤������СԪ�ص����±�Ϊi��λ��*/
			{
				c=con[i];
				con[i]=con[minpos];
				con[minpos]=c;
			}
	}
	for (i=0;i<n-1;i++)																	/*����ѭ����n-1��*/
	{
		minpos=i;																		/*Ѱ�ұ�����СԪ�����ڵ��±�*/
			for (j2=i+1; j2<n; j2++)
			{
				if (con[i].date.year == con[j1].date.year && con[i].date.month > con[j1].date.month)
					minpos=j2;
			}
			if (i!=minpos)																/*��֤������СԪ�ص����±�Ϊi��λ��*/
			{
				c=con[i];
				con[i]=con[minpos];
				con[minpos]=c;
			}
	}
	for (i=0;i<n-1;i++)																	/*����ѭ����n-1��*/
	{
		minpos=i;																		/*Ѱ�ұ�����СԪ�����ڵ��±�*/
			for (j3=i+1; j3<n; j3++)
			{
				if (con[i].date.year == con[j1].date.year && con[i].date.month == con[j1].date.month && con[i].date.day == con[j1].date.day)
					minpos=j1;
			}
			if (i!=minpos)																/*��֤������СԪ�ص����±�Ϊi��λ��*/
			{
				c=con[i];
				con[i]=con[minpos];
				con[minpos]=c;
			}
	}
			
}

int searchCon(Consumption con[],int n,Consumption c,int condition,int f[])				/*���ո����������������յ���Ϣ��������ص�����*/
/*��c��ͬ��Ԫ��*/
{
	int i,j=0,find=0;
	switch (condition)
	{
		case 1:	for (i=0; i<n; i++)														/*�����ҵ�Ԫ�ذ�����*/
					if (con[i].date.year == c.date.year)  
					{
						f[j++]=i;														/*�ҵ�����ȵ�Ԫ�أ������±�ŵ�find��*/
						find++;
					}
					return find;														/*����find����ֵΪ0���ʾû�ҵ�*/ 
		case 2:	for (i=0; i<n; i++)														/*�����ҵ�Ԫ�ذ�������*/
					if (con[i].date.year == c.date.year && con[i].date.month == c.date.month)  
					{
						f[j++]=i;														/*�ҵ�����ȵ�Ԫ�أ������±�ŵ�find��*/
						find++;
					}
					return find;														/*����find����ֵΪ0���ʾû�ҵ�*/ 
		case 3:for (i=0; i<n; i++)														/*�����ҵ�Ԫ�ذ���������*/
					if (con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day == c.date.day)  
					{
						f[j++]=i;														/*�ҵ�����ȵ�Ԫ�أ������±�ŵ�find��*/
						find++;
					}
					return find;														/*����find����ֵΪ0���ʾû�ҵ�*/ 
	}	
}

int insertCon(Consumption con[],int n,Consumption c)                                    /*������������consumption�����в���һ��Ԫ��*/
{
	int i;
	sortCon(con,n);																		/*�ȵ��ú�����������*/
	for (i=0;i<n;i++)
	{
		if (con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day == c.date.day)                      /*ѧ����ͬ��������룬��֤ѧ�ŵ�Ψһ��*/
		{
		    printf(" ����ӵ�������¼�룬������ӣ���ѡ�񡰸��ġ��˵�\n");
		    return n;
		}
	}
	for (i=n-1;i>=0;i--)																/*����С��������*/
	{
		if (!(con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day > c.date.day))                    /*���s���ڵ�ǰԪ��stu[i]�����˳�ѭ��*/
		break;
		con[i+1]=con[i];																/*����Ԫ��con[i]����һ��λ��*/
	}
	con[i+1]=c;																			/*���±�i+1������Ԫ��s*/                                   
	n++;																				/*Ԫ�ظ�������1*/
	return n;																			/*��������Ԫ�ظ���*/
}

int deleteCon(Consumption con[],int n,Consumption c)									/*��consumption������ɾ��һ��ָ�����ڵ�Ԫ��*/
{
	int i,j;
	for (i=0;i<n;i++)																	/*Ѱ�Ҵ�ɾ����Ԫ��*/
		if (con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day == c.date.day)   break;            /*����ҵ����Ԫ�����˳�ѭ��*/
	if (i==n)																			/*����Ҳ�����ɾ����Ԫ��*/
	{
		printf("������Ϊδ¼�룬��˶Ժ���������!\n");										/*������ʾ��ϢȻ�󷵻�*/
		return n;
	}
	for (j=i; j<n-1; j++)																/*�˴���������Ϊi<n��equal(stu[i],s,1)����*/ 
		con[j]=con[j+1];																/*ͨ���ƶ�����ɾ���±�Ϊi��Ԫ��*/
                                                                            
	n--;																				/*Ԫ�ظ������ټ�1*/
	return n;																			/*�������и���*/
}
