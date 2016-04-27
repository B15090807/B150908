#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"file.h"
#include"consumption.h"

void printHead( )                                                                   /*打印学生消费信息的表头*/
{
printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n","日期","餐饮","购物","娱乐","交通","费用","详情");
}

void menu( )                                                                        /*顶层菜单函数*/
{
		printf("******** 1. 显示所有账单信息         ********\n");
		printf("******** 2. 基本信息管理             ********\n");
		printf("******** 3. 消费信息管理             ********\n");
		printf("******** 4. 消费信息统计             ********\n");
        printf("******** 5. 根据条件查询             ********\n");
		printf("******** 0. 退出                     ********\n");
}

void menuBase( )                                                                    /*2、基本信息管理菜单函数*/
{
		printf("%%%%%%%% 1. 添加一笔账单             %%%%%%%%\n");
		printf("%%%%%%%% 2. 删除一笔账单             %%%%%%%%\n");
		printf("%%%%%%%% 3. 修改一笔账单             %%%%%%%%\n");
		printf("%%%%%%%% 0. 返回上层菜单             %%%%%%%%\n");
}

void menuScore( )                                                                    /*3、消费信息管理菜单函数*/
{
		printf("@@@@@@@@ 1. 计算每日消费的总金额      @@@@@@@@\n");
		printf("@@@@@@@@ 2. 根据每日金额排名          @@@@@@@@\n");
		printf("@@@@@@@@ 0. 返回上层菜单              @@@@@@@@\n");
}

void menuCount( )                                                                    /*4、消费信息统计菜单函数*/
{
		printf("&&&&&&&& 1. 某年某月消费总额          &&&&&&&&\n");
		printf("&&&&&&&& 2. 某年某月项目消费比例      &&&&&&&&\n");
		printf("&&&&&&&& 3. 某年某月超出预算金额天数  &&&&&&&&\n");
		printf("&&&&&&&& 0. 返回上层菜单              &&&&&&&&\n");
}

void menuSearch()                                                                    /*5、根据条件查询菜单函数*/
{
		printf("######## 1. 按日期（年）查询账单详情  ########\n");
		printf("######## 2. 按日期（月）查询账单详情  ########\n");
		printf("######## 3. 按日期（日）查询账单详情  ########\n");
		printf("######## 0. 返回上层菜单              ########\n");
}

int baseManage(Consumption con[],int n)    	                                         /*该函数完成基本信息管理*/
/*按date进行插                                                                       /*插入删除修改，date不能重复*/
{  
	int choice,t, find[NUM];
    Consumption c;
	do{   
	menuBase( );                                                                     /*显示对应的二级菜单*/
	printf("choose one operation you want to do:\n");
		     scanf("%d",&choice);	                                                 /*读入选项*/
		     switch(choice)
		     {
			   case 1:	readCon(&c,1);                                               /*读入一条待插入的date记录*/
						n=insertCon(con,n,c);                                        /*调用函数插入date记录*/
					 break;
			   case 2:  printf("Input the date(year,month,day) deleted\n");
					    scanf("%d%d%d",&c.date.year,&c.date.month,&c.date.day);      /*读入一个待删除的date日期*/
					    n=deleteCon(con,n,c);                                        /*调用函数删除指定date的消费记录*/
					 break;
			   case 3:  printf("Input the date(year,month,day) modified\n");
					    scanf("%d%d%d",&c.date.year,&c.date.month,&c.date.day);      /*读入一个待修改的date日期*/
						t=searchCon(con,n,c,3,find) ;                                /*调用函数查找指定date的消费记录*/
						 if (t)                                                      /*如果该消费的记录存在*/
						{
							readCon(&c,1);                                           /*读入一条完整的消费记录信息*/
							con[t] = c;                                              /*将刚读入的记录赋值给需要修改的数组记录*/ 					 
						}					 
						else                                                         /*如果该date的记录不存在*/ 
						printf("this consumption is not in,can not be modified.\n"); /*输出提示信息*/
					 break;
			   case 0: break;
		    }
	}while(choice);
	return n;                                                                        /*返回当前操作结束后的实际记录条数*/
}

void scoreManage(Consumption con[],int n)                                            /*该函数完成消费信息管理功能*/
{  
	int choice;
	do
	{
		menuScore( );                                                                /*显示对应的二级菜单*/
		printf("choose one operation you want to do:\n");
		scanf("%d",&choice);	                                                     /*读入二级选项*/
		switch(choice)
		{
			case 1:   calcuTotal(con,n);                                             /*求所有每天消费金额的总额*/
					  break;
			case 2:   calcuRank(con,n);                                              /*根据每天消费金额的总额排名次*/
				      break;		
			case 0:   break;
		}
	}while(choice);
}

void countManage(Consumption con[],int n)                                            /*该函数完成消费信息统计功能*/
{
		int choice,i,temp;
		int find[NUM],f;
		double sum,sum0,sum1,sum2,sum3;
		double spend = 0;
		Consumption c;
		sortCon(con, n);
		do
		{
			menuCount( );                                                            /*显示对应的二级菜单*/
			printf("choose one operation you want to do:\n");
			scanf("%d",&choice);
			readDate(&c, 2);
			f = searchCon(con, n, c,2,find);
			switch(choice)
			{
				case 1:	                                                              /*实现某年某月消费总额功能*/
						for (sum = 0,i = 0; i < f; i++)
						{
							sum += con[find[i]].total;
							printCon(&con[i],1);
						}
						printf("Totail consumption of this month :\n");
						printf("%ld",sum);
				      break;
				case 2:	 sum0 = sum1 = sum2 = sum3 = 0;                     	     /*实现某年某月项目消费比例功能*/
						for (i = 0; i < f; i++)
						{
							temp = find[i];
							sum0 += con[temp].fourObj[0];
							sum1 += con[temp].fourObj[1];
							sum2 += con[temp].fourObj[2];
							sum3 += con[temp].fourObj[3];
							printCon(&con[i],1);
						}
						printf("Catering,shopping,entertainment,trasportation accounted for the proportion totail:");
						printf("%ld\t%ld\t%ld\t%ld\t\n",(sum0 / f),(sum1 / f),(sum2 / f),(sum3 / f));
				      break;
				 case 3:	                                                          /*实现某年某月超出预算金额天数功能*/
						printf("please input the budget of this month:");
						scanf("%ld",&spend);
						for (i = 0,temp = 0; i < n; i++)
						{
							if (fabs(c.total - spend) > 0)
							{
								temp++;
							}
						}
						printf("The over budget days of this month:%d\n",temp);
				      break;
				  case 0:											                  /*返回上级菜单*/
					  break;
			}
		}while (choice);
}

void searchManage(Consumption con[],int n)                                            /*该函数完成根据条件查询功能*/
{
    int i,choice,f,find[NUM];
	Consumption c;
	sortCon(con, n);
	   do
		{
			menuSearch( );                                                           /*显示对应的二级菜单*/
			printf("choose one operation you want to do:\n");
			scanf("%d",&choice);
			readDate(&c,choice);                                                     /*输入日期查询*/
		 	if (choice>=1&&choice<=3)
			{ 
				f=searchCon(con,n,c,choice,find);                                    /*查找的符合条件元素的下标存于f数组中*/
				if (f)				                                                 /*如果查找成功*/
				{
			   		printHead( );                                                    /*打印表头*/
					for (i=0;i<f;i++){}                                              /*循环控制f数组的下标*/
	      			   printCon(&con[find[i]],1);                                    /*每次输出一条记录*/
				}
				else
			    	printf("this record does not exist!\n");                         /*如果查找不到元素，则输出提示信息*/
		     }		
	    }while (choice);
}

int runMain(Consumption con[],int n,int choice)                                      /*主控模块，对应于一级菜单其下各功能选择执行*/
{
		switch(choice)
		{
			case 1: printHead( );                                                    /* 1. 显示基本信息*/
					sortCon(con,n);                                                  /*按date由小到大的顺序排序记录*/ 
          			printCon(con,n);                                                 /*按date由小到大的顺序输出所有记录*/
					break;
			case 2: n=baseManage(con,n);                                             /* 2. 基本信息管理*/
			   	     break;
			case 3: scoreManage(con,n);                                              /* 3. 消费信息管理*/
					break;
			case 4: countManage(con,n);                                              /* 4. 消费信息统计*/
					break;
			case 5: searchManage(con,n);                                             /* 5. 根据条件查询*/
				     break;
          case 0: break;
		}
		return n;
}

int main( )
{
	Consumption con[NUM];                                                            /*定义实参一维数组存储消费                                                                                                                                                 记录*/
    int choice,n = 0;
	n=readFile(con);                                                                 /*首先读取文件，记录条数返回赋值给n*/      
	if (!n)                                                                          /*如果原来的文件为空*/
	{
		n=createFile(con);                                                           /*则首先要建立文件，从键盘上读入一系列记录存于文件*/       
	}	 	 
	do
	{
		menu();                                                                      /*显示主菜单*/
	    printf("Please input your choice: ");
	    scanf("%d",&choice);
	    if (choice >= 0 && choice <= 5)
	         n=runMain(con,n,choice);                                                /*通过调用此函数进行一级功能项的选择执行*/         
	    else 
		     printf("error input,please input your choice again!\n");
	} while (choice);
	sortCon(con,n);                                                                  /*存入文件前按date由小到大排序*/               
	saveFile(con,n);                                                                 /*将结果存入文件*/                        
    return 0;
}


