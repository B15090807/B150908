/* ��car.h�ļ����������� */
#ifndef _car             /*�������룬��ֹ�ظ������Ĵ���*/
#define _car
#include <string.h>
#define NUM 20                /*���峵���������˴����Ը���ʵ����Ҫ�޸ĳ���ֵ*/
struct car 
{
	long number;													//���ƺ�
	char name[20];												   //��������
    char chexing[10];                                          //����
    char color[4];                                               //��ɫ
	int grade;													      //�۷�
	int money;													     //����
	Char weigui[10];                                   		//Υ�����
		int rank;                                          //����
} ;

typedef struct car car;
#define sizeche sizeof(car)      /*������¼����Ҫ���ڴ�ռ��С*/
int readche(car che[],int n);       /*���복����¼ֵ�����ƺ�Ϊ0������涨������¼ʱֹͣ*/
void printche(car  *che , int n);   /*������г�����¼��ֵ*/

int equal(car s1,car s2,int condition);  /*����condition�����ж�����car����������ȷ�*/
int larger(car s1,car s2,int condition);  /*����condition�Ƚ�car�������ݴ�С*/
void reverse(car che[],int n);             /*������¼����Ԫ������*/

void calcuTotal(car che[],int n);           /*�������г������ܿ۷�*/
void calcuRank(car che[],int n);           /*���ݿ۷ֶ��ٽ������У������в�������*/


void sortche(car che[],int n,int condition);   /*ѡ�񷨴�С�������򣬰�condition���涨������*/

int searchche(car che[],int n,car s,int condition,int f[]) ;  /*������������������s��ȵĸ�Ԫ��*/
/*�±�����f�����У���f��������Ϊ���ҽ�����ܲ�ֹһ����¼*/
int insertche(car che[],int n,car s);                   /*�������в���һ��Ԫ�ذ����ƺ�����*/
int deleteStu(car che[],int n,car s);                   /*��������ɾ��һ��ָ�����ƺŵ�Ԫ��*/
#endif
