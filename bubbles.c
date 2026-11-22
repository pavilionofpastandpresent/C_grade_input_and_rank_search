#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>
//不想要之前录入的历史数据，就把第48行（import_from_file函数的那行）注释掉

typedef struct{
	char name[31];//嗨嗨嗨~谁名字会>10个字啊，我分配的字符串的内存大小包安全的
	int score;
}Student;

void bubble(int n,Student students[]);
char* show_me_the_grade(int n );
void errorBeep();
void addstudents(Student *students,char nam[31],int *t,int sco);
void add_to_file(Student *students,int t);
void import_from_file(Student **students,int *t,int *capacity);

int truee=1;//控制循环的退出
int t=0;//记录登记的学生人数
int n;//接受客户输入的功能数字
char nam[31];//接受客户输入的姓名
int sco;//接受客户输入的分数
int capacity = 77;
enum Flag {ADD_OR_MODIFY=1,VIEW_SCORE_RANK,QUERY_BY_RANK,VIEW_GRADE,STAND_ALONE_GRADE_TRANSFORM,SHOW_ALL_INFO,QUIT};

int main(){
	
	printf("\n   **\n"
		   "* **** *\n"
		   "   **\n"
		   "1 录入或修改学生成绩\n"
		   "2 查看学生成绩和排名\n"
		   "3 根据排名查询学生的姓名和成绩\n"
		   "4 查看学生的成绩等级（A+ ~ F-）\n"
		   "5 来个成绩---自动判断成绩属于什么等级\n"
		   "6 查看所有学生的全部信息\n"
		   "7 退出\n"
		   "\n>>>>>>>请输入对应的数字来使用不同的功能<<<<<<<\n\n");
	
	Student *students= (Student *)malloc(capacity * sizeof(Student));
	if(students==NULL){
		printf("内存分配失败");
		errorBeep();
		return 0;
	}
	
	import_from_file(&students,&t,&capacity);//这是不让旧文件被覆盖的关键
	
	while(truee){
	printf("\n数字：");
		if(scanf("%d",&n) ==1)
		{
			switch(n){
			
			case ADD_OR_MODIFY:{
			if(t>=capacity){
				capacity *= 2;
				Student *temp= (Student *)realloc(students,(capacity * sizeof(Student)));
				if(temp==NULL){
					printf("内存分配失败");
					errorBeep();
					capacity /=2;//严谨
					break;
				}
				students = temp;
			}
			printf("请输入学生姓名：");
			scanf("%10s",nam);
			printf("请输入学生的成绩:");
			if(scanf("%d",&sco) != 1)
			{
			while(getchar() != '\n');
			printf("成绩输入无效\n");
			errorBeep();
			continue;
			}
			addstudents(students,nam,&t,sco);
			printf("完成！\n");
			}break;
						
			case VIEW_SCORE_RANK:{
				printf("请输入学生姓名：");
				scanf("%s",nam);
				int found=0;
				int i;
				for( i=0;i<=t-1;i++)
				{
					if(strcmp(students[i].name,nam)==0)
					{
						printf("%s的成绩是  %d\n",students[i].name,students[i].score);
						printf("%s的排名为  %d\n",students[i].name,i+1);
						found=1;
						break;
					}
				}
				if(!found){printf("该学生的成绩尚未录入\n");errorBeep();}
			}break;
			
			case QUERY_BY_RANK:{
				printf("请输入学生排名：");
				int rank;
				scanf("%d",&rank);
				int found=0;
				
					if(rank>=1 && rank<=t)
					{
						printf("%s的成绩是%d\n",students[rank-1].name,students[rank-1].score);
						found=1;
						break;
					}
				
				if(!found){printf("未查到，目前最低排名为%d\n",t);errorBeep();}
			}break;
			
			case VIEW_GRADE:{
				printf("请输入学生姓名：");
				scanf("%s",nam);
				int found=0;
				int i;
				for( i=0;i<=t-1;i++)
				{
					if(strcmp(students[i].name,nam)==0)
					{
						char* grade=show_me_the_grade(students[i].score);
						printf("%s的成绩(%d)等级是%s\n",students[i].name,students[i].score,grade);
						found=1;
						break;
					}
				}
				if(!found){printf("该学生的成绩尚未录入\n");errorBeep();}
			}break;
				
			
			case STAND_ALONE_GRADE_TRANSFORM:{
				printf("输入你要检测的成绩，"
					   "我将自动算出对应的成绩等级和绩点\n");
				scanf("%d",&sco);
				printf("Your 'Grade' and GPA:%s\n",show_me_the_grade(sco));
			}break;
			
			case SHOW_ALL_INFO:{
				if(t)
				{
					int i;
					for( i=0;i<t;i++)
						printf("第%d名：%s\t"
							   "成绩：%-8d"
							   "等级:%s\n"
							   ,i+1,students[i].name,students[i].score,show_me_the_grade(students[i].score));
				}
				else {printf("无---请先录入学生成绩\n");errorBeep();}
			}break;
			
//			case IMPORT:{
//			import_from_file(students,&t,&capacity);
//			}break;
				
			case QUIT:{truee=0;printf("\n   **                                                    **\n"
								        "* **** *       \"可曾初心高于胜负，成长胜于输赢\"       * **** *\n"
								        "   **                                                    **\n");break;		
			default:{printf("\n无效的操作，请重新输入\n");errorBeep();} 
		}
		}
		}
		else {while (getchar()!='\n'){};printf(">>>  NO!杂鱼，你应该给我一个数字。Try it again.  <<<\n");errorBeep();}
}
	add_to_file(students,t);//文件持久化
	free(students);//有借有还，再借不难
	students=NULL;//好习惯
	return 0;
}
	
	
void bubble(int n,Student students[])
{
	int i;
	for( i=0;i<=n-2;i++)
	{
		int j;
		for( j=0;j<=n-2-i;j++)
			if (students[j].score<students[j+1].score)
			{
				Student tmp =students[j];
				students[j]=students[j+1];
				students[j+1]=tmp;
			}
	}
//	for(int i=0;i<=n-1;i++){
//		printf("%d ",students[i].score);
//	}
}

char* show_me_the_grade(int n)
{
		if(n>=97) return "A+   绩点:4.5";
		else if(n>=93) return "A     绩点:4.3";
		else if(n>=89) return "A-   绩点:4.0";
		else if(n>=85) return "B+   绩点:3.8";
		else if(n>=81) return "B     绩点:3.4";
		else if(n>=77) return "B-   绩点:3.0";
		else if(n>=73) return "C+   绩点:2.6";
		else if(n>=69) return "C     绩点:2.2";
		else if(n>=65) return "C-   绩点:1.8";
		else if(n>=60) return "D     绩点:1.2";
		else if(n>=40) return "F     绩点:0";
		else return "F-    绩点:0";
}

void errorBeep()
{
	Beep(784,300);
	Beep(659,300);
	Beep(523,300);
}

void addstudents(Student *students,char nam[31],int *t,int sco){
	int found=0;
	int i;
	for( i=0;i<=*t-1;i++)
	{
		if(strcmp(students[i].name,nam)==0)
		{
		students[i].score=sco;
		found=1;
		break;
		}
	}
	if(!found){students[*t].score=sco;strcpy(students[*t].name,nam);(*t)++;}
	bubble(*t,students);
}

void add_to_file(Student *students,int t)
{
	FILE *fp = fopen("stu_data","wb");
	if (fp ==NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	fwrite(students,sizeof(Student),t,fp);
	fclose(fp);
}

void import_from_file(Student **students,int *t,int *capacity)//我把*students当数组用了，函数里面全局修改它就需要二级指针
{
	FILE *fp = fopen("stu_data","rb");
	if(fp == NULL)
	{
		printf("打开文件失败，文件导入失败\n");
		return;
	}
	Student temp1;
	int number=0;
	while(fread(&temp1,sizeof(Student),1,fp) == 1)
	{
		if(*t>=*capacity){
			(*capacity) *= 2;
			Student *temp2= (Student *)realloc(*students,((*capacity) * sizeof(Student)));
			if(temp2==NULL){
				printf("内存分配失败\n");
				errorBeep();
				(*capacity)/=2;//严谨
				break;
			}
			*students = temp2;
		}
		(*students)[*t]=temp1;
		(*t)++;
		number++;
	}
	printf("\t(成功导入%d个历史数据)\n",number);
	fclose(fp);
}
