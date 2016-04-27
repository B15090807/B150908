/*②consumption.c文件的完整内容*/
#include "consumption.h"
#include <stdio.h>

int readCon(Consumption *con, int n)														/*读入消费结构体的各项值，记录到NUM时停止*/
{
	int i,j;
	for (i=0; i<n; i++)
	{
		printf(" 按以下提示输入一笔账单信息\n");                                        /*根据提示输入账单信息的年月日*/
		printf(" 请输入日期\n");
		printf(" 年:  ");
		scanf("%d", &con[i].date.year);
		printf(" 月:  ");
		scanf("%d", &con[i].date.month);
		printf(" 日:  ");
		scanf("%d", &con[i].date.day);
		printf(" 请按顺序输入餐饮、娱乐、购物、交通费用详情 : ");                       /*根据提示输入账单信息四项具体花销*/
		for (j=0; j<4; j++)
	    {
		    scanf("%lf",&con[i].fourObj[j]);
			//scanf("%s",&con[i].detail);	
		}
		con[i].rank=0;                                                                  /*排名需要根据总分来计算，初值置为0*/
	}
	return i;                                                                           /*返回实际读入的记录条数*/
}

void readDate(Consumption *c, int condition)											/*根据条件读入为consumption读入日期：年、年月、年月日*/
{                   
	Date date;
	int i;
	printf(" 请输入日期\n");
	switch (condition)
	{
		case 1:	
			printf(" 请输入你想搜索的年份 (year):");									/*输入年信息*/
			scanf("%d",&date.year);
			c->date.year = date.year;
			break;
		case 2:																			/*输入年月信息*/
			printf(" 请输入你想搜索的年份和月份（year month）:");
			scanf("%d%d",&date.year,&date.month);
			c->date.year = date.year;
			c->date.month = date.month;
			break;
		case 3:																			/*输入年月日信息*/
			printf(" 请输入你想搜索的年月日（year month day）:");
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

void printCon (Consumption *con, int n, int condition)									/*根据条件输出消费记录的值*/
{
    int i,j;
	switch(condition)
	{
	case 1: printf("%s\t        %s\t%s\t%s\t%s\t","日期","餐饮","购物","娱乐","交通");
			for (i=0; i<n; i++)
			{
				printf("\n%d/%d/%d\t",con[i].date.year,con[i].date.month,con[i].date.day);
				for (j=0; j<4; j++)
				{	
					printf("%.2f\t",con[i].fourObj[j]);
				}
			}
		break;
	case 2: printf("%s\t        %s\t%s\t%s\t%s\t%s\t","日期","餐饮","购物","娱乐","交通","总额");
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
	case 3:	 printf("%s\t        %s\t%s\t%s\t%s\t%s\t%s\t","日期","餐饮","购物","娱乐","交通","总额","排名");
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

void reverse(Consumption con[], int n)													/*消费记录数组元素的逆置*/
{
	Consumption temp;
	int i;
	for (i=0; i<n/2; i++)																/*循环次数为元素数量的一半*/
	{
		temp=con[i];
		con[i]=con[n-1-i];
		con[n-1-i]=temp;
	}
}

void calcuTotal(Consumption con[],int n)												/*计算每天四项消费的总金额*/
{
	int i,j;
	for (i=0; i<n; i++)																	/*外层循环控制总的消费记录*/
	{
		con[i].total = 0;
		for (j=0; j<4; j++)																/*内层循环控制四个项目*/
		{
			con[i].total += con[i].fourObj[j];
		}
	}	
}

void calcuRank(Consumption con[],int n)                                                 /*根据总金额计算消费的名次，允许有并列名次*/
{
	int i , j ,minpos ;                       
	Consumption c;
	for (i = 0; i < n-1; i++)															/*根据总金额计算消费，用选择排序的方法排序*/
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
	reverse(con,n);																		/*再逆置，则按消费总金额由大到小排序了*/
	con[0].rank=1;																		/*第一条记录的排名一定是1*/
	for (i=1; i<n; i++)																	/*从第二条记录一直到最后一条进行循环*/
	{
		if (con[i].total == con[i-1].total)												/*当前记录与其相邻的前一条记录如果消费总金额相等*/
			con[i].rank=con[i-1].rank;													/*当前记录名次等于其相邻的前一条记录排名*/ 
	    else
			con[i].rank=i+1;															/*不相等时当前记录排名等于其下标号+1*/
	}
}

void sortCon(Consumption con[],int n)													/*选择法根据日期（年月日）从小到大排序*/
{
	int i,j1,j2,j3,minpos;																/*minpos用来存储本趟最小元素所在的下标*/
	Consumption c;
	for (i=0;i<n-1;i++)																	/*控制循环的n-1趟*/
	{
		minpos=i;																		/*寻找本趟最小元素所在的下标*/
			for (j1=i+1; j1<n; j1++)
			{
				if (con[i].date.year > con[j1].date.year)
					minpos=j1;
			}
			if (i!=minpos)																/*保证本趟最小元素到达下标为i的位置*/
			{
				c=con[i];
				con[i]=con[minpos];
				con[minpos]=c;
			}
	}
	for (i=0;i<n-1;i++)																	/*控制循环的n-1趟*/
	{
		minpos=i;																		/*寻找本趟最小元素所在的下标*/
			for (j2=i+1; j2<n; j2++)
			{
				if (con[i].date.year == con[j1].date.year && con[i].date.month > con[j1].date.month)
					minpos=j2;
			}
			if (i!=minpos)																/*保证本趟最小元素到达下标为i的位置*/
			{
				c=con[i];
				con[i]=con[minpos];
				con[minpos]=c;
			}
	}
	for (i=0;i<n-1;i++)																	/*控制循环的n-1趟*/
	{
		minpos=i;																		/*寻找本趟最小元素所在的下标*/
			for (j3=i+1; j3<n; j3++)
			{
				if (con[i].date.year == con[j1].date.year && con[i].date.month == con[j1].date.month && con[i].date.day == con[j1].date.day)
					minpos=j1;
			}
			if (i!=minpos)																/*保证本趟最小元素到达下标为i的位置*/
			{
				c=con[i];
				con[i]=con[minpos];
				con[minpos]=c;
			}
	}
			
}

int searchCon(Consumption con[],int n,Consumption c,int condition,int f[])				/*按照给定的条件（年月日的信息）进行相关的搜索*/
/*与c相同的元素*/
{
	int i,j=0,find=0;
	switch (condition)
	{
		case 1:	for (i=0; i<n; i++)														/*待查找的元素按照年*/
					if (con[i].date.year == c.date.year)  
					{
						f[j++]=i;														/*找到了相等的元素，将其下标放到find中*/
						find++;
					}
					return find;														/*返回find，其值为0则表示没找到*/ 
		case 2:	for (i=0; i<n; i++)														/*待查找的元素按照年月*/
					if (con[i].date.year == c.date.year && con[i].date.month == c.date.month)  
					{
						f[j++]=i;														/*找到了相等的元素，将其下标放到find中*/
						find++;
					}
					return find;														/*返回find，其值为0则表示没找到*/ 
		case 3:for (i=0; i<n; i++)														/*待查找的元素按照年月日*/
					if (con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day == c.date.day)  
					{
						f[j++]=i;														/*找到了相等的元素，将其下标放到find中*/
						find++;
					}
					return find;														/*返回find，其值为0则表示没找到*/ 
	}	
}

int insertCon(Consumption con[],int n,Consumption c)                                    /*按日期有序向consumption数组中插入一个元素*/
{
	int i;
	sortCon(con,n);																		/*先调用函数进行排序*/
	for (i=0;i<n;i++)
	{
		if (con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day == c.date.day)                      /*学号相同不允许插入，保证学号的唯一性*/
		{
		    printf(" 想添加的日期已录入，不可添加！请选择“更改”菜单\n");
		    return n;
		}
	}
	for (i=n-1;i>=0;i--)																/*按从小到大有序*/
	{
		if (!(con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day > c.date.day))                    /*如果s大于当前元素stu[i]，则退出循环*/
		break;
		con[i+1]=con[i];																/*否则元素con[i]后移一个位置*/
	}
	con[i+1]=c;																			/*在下标i+1处插入元素s*/                                   
	n++;																				/*元素个数增加1*/
	return n;																			/*返回现有元素个数*/
}

int deleteCon(Consumption con[],int n,Consumption c)									/*从consumption数组中删除一个指定日期的元素*/
{
	int i,j;
	for (i=0;i<n;i++)																	/*寻找待删除的元素*/
		if (con[i].date.year == c.date.year && con[i].date.month == c.date.month && con[i].date.day == c.date.day)   break;            /*如果找到相等元素则退出循环*/
	if (i==n)																			/*如果找不到待删除的元素*/
	{
		printf("该日期为未录入，请核对后重新输入!\n");										/*给出提示信息然后返回*/
		return n;
	}
	for (j=i; j<n-1; j++)																/*此处隐含条件为i<n且equal(stu[i],s,1)成立*/ 
		con[j]=con[j+1];																/*通过移动覆盖删除下标为i的元素*/
                                                                            
	n--;																				/*元素个数减少加1*/
	return n;																			/*返回现有个数*/
}
