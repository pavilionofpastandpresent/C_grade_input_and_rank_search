#include<stdio.h>
#include<string.h>
typedef struct{
	char name[31];//嗨嗨嗨~谁名字会>10个字啊，我分配的字符串的内存大小包安全的
	int score;
}Student;
Student students[77]={0};
void bubble(int n,Student students[]);
char* show_me_the_grade(int n);
int truee=1;//控制循环的退出
int t=0;//记录登记的学生人数
int n;//接受客户输入的功能数字
char nam[13];//接受客户输入的姓名
int sco;//接受客户输入的分数
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
	
	while(truee){
	printf("\n数字：");

		if(scanf("%d",&n) ==1)
		{
			switch(n){
			case 1:{
			printf("请输入学生姓名：");
			scanf("%s",nam);
			printf("请输入学生的成绩:");
			scanf("%d",&sco);
			int found=0;
			for(int i=0;i<=t-1;i++)
			{
			if(strcmp(students[i].name,nam)==0)
				{
				students[i].score=sco;
				found=1;
				break;
				}
			}
			if(!found){students[t].score=sco;strcpy(students[t].name,nam);t++;}
			bubble(t,students);
			printf("完成！\n");
			}break;
			
			case 2:{
				printf("请输入学生姓名：");
				scanf("%s",nam);
				int found=0;
				for(int i=0;i<=t-1;i++)
				{
					if(strcmp(students[i].name,nam)==0)
					{
						printf("%s的成绩是  %d\n",students[i].name,students[i].score);
						printf("%s的排名为  %d\n",students[i].name,i+1);
						found=1;
						break;
					}
				}
				if(!found)printf("该学生的成绩尚未录入\n");
			}break;
			
			case 3:{
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
				
				if(!found)printf("未查到，目前最低排名为%d\n",t);
			}break;
			
			case 4:{
				printf("请输入学生姓名：");
				scanf("%s",nam);
				int found=0;
				for(int i=0;i<=t-1;i++)
				{
					if(strcmp(students[i].name,nam)==0)
					{
						char* grade=show_me_the_grade(students[i].score);
						printf("%s的成绩(%d)等级是%s\n",students[i].name,students[i].score,grade);
						found=1;
						break;
					}
				}
				if(!found)printf("该学生的成绩尚未录入\n");
			}break;
				
			
			case 5:{
				printf("输入你要检测的成绩，"
					   "我将自动算出对应的成绩等级和绩点\n");
				scanf("%d",&sco);
				printf("Your 'Grade' and GPA:%s\n",show_me_the_grade(sco));
			}break;
			
			case 6:{
				if(t)
					for(int i=0;i<t;i++)
						printf("第%d名：%s\t"
							   "成绩：%d\t"
							   "等级:%s\n"
							   ,i+1,students[i].name,students[i].score,show_me_the_grade(students[i].score));
				else printf("无---请先录入学生成绩\n");
			}break;
			
			case 7:{truee=0;printf("\n   **                                                    **\n"
								   "* **** *       \"可曾初心高于胜负，成长胜于输赢\"       * **** *\n"
								   "   **                                                    **\n");}break;		
			default:{printf("\n无效的操作，请重新输入\n");} 
		}
		}
		else {while (getchar()!='\n');printf(">>>  NO!杂鱼，你应该给我一个数字。Try it again.  <<<\n");}
}
return 0;}
	
	
	
	
	
	
	
	
	
	
void bubble(int n,Student students[])
{
	for(int i=0;i<=n-2;i++)
		for(int j=0;j<=n-2-i;j++)
			if (students[j].score<students[j+1].score)
			{
				Student tmp =students[j];
				students[j]=students[j+1];
				students[j+1]=tmp;
			}
//	for(int i=0;i<=n-1;i++){
//		printf("%d ",students[i].score);
//	}
}

char* show_me_the_grade(int n)
{
		if(n>=97) return "A+   绩点:4.5";
		else if(n>=93) return "A    绩点:4.3";
		else if(n>=89) return "A-   绩点:4.0";
		else if(n>=85) return "B+   绩点:3.8";
		else if(n>=81) return "B    绩点:3.4";
		else if(n>=77) return "B-   绩点:3.0";
		else if(n>=73) return "C+   绩点:2.6";
		else if(n>=69) return "C    绩点:2.2";
		else if(n>=65) return "C-   绩点:1.8";
		else if(n>=60) return "D    绩点:1.2";
		else if(n>=40) return "F    绩点:0";
		else return "F-    绩点:0";
}


