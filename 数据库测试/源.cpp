#include <iostream> 
#include <winsock.h>
#include <mysql.h>      //sql头文件
#include <stdlib.h>
#include <iomanip>     //主要是对cin,cout之类的一些操纵运算,是I/O流控制头文件。 
#include <stdio.h>  
#pragma comment(lib,"libmysql.lib")//连接MysQL需要的库
using namespace std;
class Student
{
public:
	int term;     //学期
	int num;      //学号 
	char name[10];     //姓名 
	float mark1;     //成绩1  
	float mark2;     //成绩2  
	float mark3;     //成绩3  
	float sum;      //总分 
	float average;     //平均分 
};
void mysql_searchnum(Student* r);  //按学号和学期查找
void mysql_input(Student* r);       //输入 
void mysql_output(Student* r);      //输出 
void mysql_change(Student* r);      //按学号修改信息 
void mysql_insert(Student* r);  //插入信息     
void mysql_tongji(Student* r);      //统计各科总分和平均分信息   
int num = 0;
int connectmysql() {
	MYSQL mysql;//一个数据库结构体

	MYSQL_RES* res;//一个结果集结构体
	MYSQL_ROW row;//char**二维数组,存放一条条记录
		//初始化数据库
	mysql_init(&mysql);
	//设置编码方式
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	//判断如果连接失败就输出连接失败
	//注意连接的账户名和密码
	if (mysql_real_connect(&mysql, "localhost", "root", "", "test", 3306, NULL, 0) == NULL)
		printf("连接失败\\n");
	return true;
}

int main()
{
	cout << "输入学生的个数:";
	cin >> num;                 //全局变量 
	Student* p = (Student*)new Student[num];   //定义指针数组，存放学生个数 
	int m;
	do
	{
		cout << endl;
		cout << endl;
		cout << "\t*----------------------------->菜单栏< ---------------------------- - *\n" << endl;
		cout << "\t* <1> 输入学生信息并保存到数据库            * " << endl;
		cout << "\t* <2> 读取数据库并输出学生信息         *" << endl;
		cout << "\t* <3> 按学号和学期查询                      *" << endl;
		cout << "\t* <4> 按学号和学期修改信息             *" << endl;
		cout << "\t* <5> 插入信息            *" << endl;
		cout << "\t* <6> 统计各科总分和平均分信息        	* " << endl; 
		cout << "\t * <7> 退出* " << endl;
		cout << "\t*------------------------------------------------------------------*\n" << endl;
		cout << "请选择:";



		cin >> m;
		switch (m)
		{
		case 1:
			mysql_input(p);       //输入 
			break;
		case 2:
			mysql_output(p);     //输出
			break;
		case 3:
			mysql_searchnum(p);   //按学号和学期查找
		break;   case 4:
			mysql_change(p);     //按学号和学期修改信息
			break;
		case 5:
			mysql_insert(p);    //插入信息
			break;
		case 6:
			mysql_tongji(p);     //统计各科总分和平均分信息
			break;

		case 7:                    //退出 
			break;
		}
	} while (m != 7);
}
//输入信息 
void mysql_input(Student* r)
{
	int i, n, t;
	for (i = 0; i < num; i++)
	{
		cout << "请输入学期:";   cin >> r[i].term;
		cout << "请输入第" << i + 1 << "个人的学号:";   cin >> r[i].num;
		if (i >= 1)
		{
			for (n = 0; n < i; n++)
			{
				if (r[n].num == r[i].num)
				{
					cout << "该学号已存在！！" << endl;
					t = 1;
				}
			}
		}
		if (t == 1)     //表示有重复 
		{
			i--;
			t = 0;
			continue;
		}
		cout << "请输入姓名:";
		cin >> r[i].name;
		cout << "请输入 高等数学 成绩:";
		cin >> r[i].mark1;
		cout << "请输入 数据结构 成绩:";
		cin >> r[i].mark2;
		cout << "请输入 大学英语 成绩:";
		cin >> r[i].mark3;
		r[i].sum = r[i].mark1 + r[i].mark2 + r[i].mark3;
		r[i].average = (r[i].mark1 + r[i].mark2 + r[i].mark3) / 3;
	}
}

//输出信息 
void mysql_output(Student* r)
{
	int m;
	system("cls");                   //清屏
	if (num > 0)
	{
		FILE* fp;
		if ((fp = fopen("student.txt", "r")) == NULL) //r只读 
		{
			cout << "不能打开" << endl;
			exit(0);
		}
		for (int n = 0; n < num; n++)
		{

			fscanf(fp, "%d%s%f%f%f%d%f%f", &r[n].num, r[n].name, &r[n].mark1, &r[n].mark2, &r[n].mark3, &r[n].term, &r[n].sum, &r[n].average);
		}
		fclose(fp);                            //关闭文件 

		cout << "已经读入" << endl;
		cout << "----------------------------> 学生信息如下 < ------------------------------" << endl;
		cout << "学号" << setw(6) << "姓名" << setw(10) << "高等数学" << setw(10) << "数据结构" << setw(10) //setw(6) 设置输出宽度 
			<< "大学英语" << setw(6) << "学期" << setw(6) << "总分" << setw(8) << "平均分" << endl;
		cout << "---------------------------------------------------------------" << endl;
		for (m = 0; m < num; m++)
		{
			cout << r[m].num << setw(6) << r[m].name << setw(7) << r[m].mark1 << setw(10)
				<< r[m].mark2 << setw(10) << r[m].mark3 << setw(8) << r[m].term << setw(6) << r[m].sum << setw(6) << r[m].average << endl;
		}
		cout << "\0\0" << endl;
	}
	else   cout << "未输入任何信息！！" << endl;
}
//按学号及学期查找 
void mysql_searchnum(Student* r)
{
	int n, k;
	int m = 0;
	system("cls");                              //清屏 
	if (num > 0) {
		cout << "请输入要查找学生的学号:";   cin >> n;
		cout << "请输入学期号:";
		cin >> k;
		for (int m = 0; m < num; m++) {
			if ((r[m].num == n) &( r[m].term == k))  //如果找到了输出并跳出循环 
			{
				cout << endl;
				cout << "-------------------------> 要查找的信息如下 < ---------------------------- - " << endl;
				cout << "学号" << setw(6) << "姓名" << setw(10) << "高等数学" << setw(10) << "数据结构"
					<< setw(10) << "大学英语" << setw(6) << "学期" << setw(6) << "总分" << setw(8) << "平均分" << endl;
				cout << r[m].num << setw(6) << r[m].name << setw(7) << r[m].mark1 << setw(10) << r[m].mark2 << setw(10) << r[m].mark3 << setw(8) << r[m].term << setw(6) << r[m].sum << setw(8) << r[m].average << endl;
				break;
			}
		}

		if (r[m].num != n && r[m].term != k)   //若没找到提示不存在 
			cout << "该学号不存在,或没有这个学期的成绩!" << endl;
	}
	else   cout << "未输入任何信息！！" << endl;
}
//按学号及学期修改信息      
void mysql_change(Student *r)
{
	FILE* fp;
	int n = 0;
	char chiose = 'Y';
	if (num > 0)
	{
		int n, k;
		int t = 0;
		system("cls");                                  //清屏 
		cout << "输入要修改成绩的学生学号:";
		cin >> n;
		cout << "所需修改的学期:";
		cin >> k;

		for (int m = 0; m < num; m++) {
			if (r[m].num == n && r[m].term == k) {
				int j;
				cout << endl;
				cout << "-------------------------> 修改前的信息如下 < --------------------------" << endl;
				cout << "学号" << setw(6) << "姓名" << setw(10) << "高等数学" << setw(10) << "数据结构"
					<< setw(10) << "大学英语" << setw(6) << "学期" << setw(6) << "总分" << setw(8) << "平均分" << endl;

				cout << r[m].num << setw(6) << r[m].name << setw(7) << r[m].mark1 << setw(10) << r[m].mark2 << setw(10) << r[m].mark3 << setw(8) << r[m].term << setw(6) << r[m].sum << setw(8) << r[m].average << endl;
				cout << endl;
				while (chiose == 'Y' || chiose == 'y') {
					cout << "\t\t\t--------> 可以修改的项目如下 <-------\n" << endl;
					cout << "\t\t\t 1.修改学生的 高等数学 成绩记录\n" << endl;
					cout << "\t\t\t 2.修改学生的 数据结构 成绩记录\n" << endl;
					cout << "\t\t\t 3.修改学生的 大学英语 成绩记录\n" << endl;
					cout << "请选择:";
					cin >> j;
					switch (j)
					{
					case 1:
						cout << "输入新的 高等数学 成绩:";
						cin >> r[m].mark1;
						break;
					case 2:
						cout << "输入新的 数据结构 成绩:";
						cin >> r[m].mark2;
						break;
					case 3:
						cout << "输入新的 大学英语 成绩:";
						cin >> r[m].mark3;
						break;
					}      t = 1;
					cout << "是否要继续修改此学生的其他成绩记录？(Y/N)";
					fflush(stdin);      //清空输入缓冲区，通常是为了确保不影响后面的数据读取
					cin >> chiose;
				}
			}
		}
	}
	else   cout << "未输入任何信息！！" << endl;
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		cout << "不能打开" << endl;
		exit(0);
	}
	for (n = 0; n < num; n++)
	{
		fprintf(fp, "%d   %s   %.1f   %.1f   %.1f   %d   %.1f   %.1f", r[n].num, r[n].name, r[n].mark1, r[n].mark2, r[n].mark3, r[n].term, r[n].sum, r[n].average);
		fprintf(fp, "\n");
	}
	fclose(fp);
	cout << "文件已修改并写入" << endl;
}
//插入 
void mysql_insert(Student* r)
{
	FILE* fp;  int m;  char n;  do
	{
		if ((fp = fopen("student.txt", "r")) == NULL)
		{
			cout << "不能打开" << endl;
			exit(0);
		}
		for (int o = 0; o < num; o++)
		{

			fscanf(fp, "%d%s%f%f%f%d%f%f", &r[o].num, r[o].name, &r[o].mark1, &r[o].mark2, &r[o].mark3, &r[o].term, &r[o].sum, &r[o].average);
		}
		Student* y = (Student*)new Student[num + 1]; //定义另一个数组，用于存放新添加的记录
		for (m = 0; m < num; m++)
		{
			y[m] = r[m];
		}
		r = y;
		cout << "请输入学期:";
		cin >> r[num].term;
		cout << "请输入学号:";
		cin >> r[num].num;
		cout << "请输入姓名:";
		cin >> r[num].name;
		cout << "请输入 高等数学 成绩:";
		cin >> r[num].mark1;
		cout << "请输入 数据结构 成绩:";
		cin >> r[num].mark2;
		cout << "请输入 大学英语 成绩:";
		cin >> r[num].mark3;
		r[num].sum = r[num].mark1 + r[num].mark2 + r[num].mark3;  //计算总分 
		r[num].average = (r[num].mark1 + r[num].mark2 + r[num].mark3) / 3;

		num++;
		cout << "是否继续输入？（继续，输入y，否则输入其他）" << endl;
		cin >> n;
	} while (n == 'y');

	if ((fp = fopen("student.txt", "w+")) == NULL)
	{
		cout << "文件不能打开" << endl;
		exit(0);
	}
	for (n = 0; n < num; n++)
	{

		fprintf(fp, "%d   %s   %.1f   %.1f   %.1f   %d   %.1f   %.1f", r[n].num, r[n].name, r[n].mark1, r[n].mark2, r[n].mark3, r[n].term, r[n].sum, r[n].average);
		fprintf(fp, "\n");
	}

	fclose(fp);
	cout << "已经写入" << endl;
}
//统计各科总分及平均分 
void mysql_tongji(Student* r)
{
	float summark1 = 0, summark2 = 0, summark3 = 0;
	float avemark1 = 0, avemark2 = 0, avemark3 = 0;
	FILE* fp;
	system("cls");                              //清屏 
	if (num > 0)
	{
		for (int m = 0; m < num; m++)
		{
			summark1 = summark1 + r[m].mark1;
			summark2 = summark2 + r[m].mark2;
			summark3 = summark3 + r[m].mark3;
		}
		avemark1 = summark1 / num;
		avemark2 = summark2 / num;
		avemark3 = summark3 / num;
		cout << endl;
		cout << "高等数学 总分为:" << summark1 << "平均分为:" << avemark1 << endl;
		cout << endl;
		cout << "数据结构 总分为:" << summark2 << "平均分为:" << avemark2 << endl;
		cout << endl;
		cout << "大学英语 总分为:" << summark3 << "平均分为:" << avemark3 << endl;
		cout << endl;
		if ((fp = fopen("student.txt", "w")) == NULL)
		{
			cout << "对不起，文件不能打开！" << endl;
			exit(0);
		}
		for (int n = 0; n < num; n++)
		{

			fprintf(fp, "%d   %s   %.1f   %.1f   %.1f   %d   %.1f   %.1f", r[n].num, r[n].name, r[n].mark1, r[n].mark2, r[n].mark3, r[n].term, r[n].sum, r[n].average);
			fprintf(fp, "\n");
		}
		cout << "高等数学 总分为:" << summark1 << endl;
		cout << "数据结构 总分为:" << summark2 << endl;
		cout << "大学英语 总分为:" << summark3 << endl;
	}
	else   cout << "对不起，未输入任何信息！" << endl;
}