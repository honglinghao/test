#include <iostream> 
#include <winsock.h>
#include <mysql.h>      //sqlͷ�ļ�
#include <stdlib.h>
#include <iomanip>     //��Ҫ�Ƕ�cin,cout֮���һЩ��������,��I/O������ͷ�ļ��� 
#include <stdio.h>  
#pragma comment(lib,"libmysql.lib")//����MysQL��Ҫ�Ŀ�
using namespace std;
class Student
{
public:
	int term;     //ѧ��
	int num;      //ѧ�� 
	char name[10];     //���� 
	float mark1;     //�ɼ�1  
	float mark2;     //�ɼ�2  
	float mark3;     //�ɼ�3  
	float sum;      //�ܷ� 
	float average;     //ƽ���� 
};
void mysql_searchnum(Student* r);  //��ѧ�ź�ѧ�ڲ���
void mysql_input(Student* r);       //���� 
void mysql_output(Student* r);      //��� 
void mysql_change(Student* r);      //��ѧ���޸���Ϣ 
void mysql_insert(Student* r);  //������Ϣ     
void mysql_tongji(Student* r);      //ͳ�Ƹ����ֺܷ�ƽ������Ϣ   
int num = 0;
int connectmysql() {
	MYSQL mysql;//һ�����ݿ�ṹ��

	MYSQL_RES* res;//һ��������ṹ��
	MYSQL_ROW row;//char**��ά����,���һ������¼
		//��ʼ�����ݿ�
	mysql_init(&mysql);
	//���ñ��뷽ʽ
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	//�ж��������ʧ�ܾ��������ʧ��
	//ע�����ӵ��˻���������
	if (mysql_real_connect(&mysql, "localhost", "root", "", "test", 3306, NULL, 0) == NULL)
		printf("����ʧ��\\n");
	return true;
}

int main()
{
	cout << "����ѧ���ĸ���:";
	cin >> num;                 //ȫ�ֱ��� 
	Student* p = (Student*)new Student[num];   //����ָ�����飬���ѧ������ 
	int m;
	do
	{
		cout << endl;
		cout << endl;
		cout << "\t*----------------------------->�˵���< ---------------------------- - *\n" << endl;
		cout << "\t* <1> ����ѧ����Ϣ�����浽���ݿ�            * " << endl;
		cout << "\t* <2> ��ȡ���ݿⲢ���ѧ����Ϣ         *" << endl;
		cout << "\t* <3> ��ѧ�ź�ѧ�ڲ�ѯ                      *" << endl;
		cout << "\t* <4> ��ѧ�ź�ѧ���޸���Ϣ             *" << endl;
		cout << "\t* <5> ������Ϣ            *" << endl;
		cout << "\t* <6> ͳ�Ƹ����ֺܷ�ƽ������Ϣ        	* " << endl; 
		cout << "\t * <7> �˳�* " << endl;
		cout << "\t*------------------------------------------------------------------*\n" << endl;
		cout << "��ѡ��:";



		cin >> m;
		switch (m)
		{
		case 1:
			mysql_input(p);       //���� 
			break;
		case 2:
			mysql_output(p);     //���
			break;
		case 3:
			mysql_searchnum(p);   //��ѧ�ź�ѧ�ڲ���
		break;   case 4:
			mysql_change(p);     //��ѧ�ź�ѧ���޸���Ϣ
			break;
		case 5:
			mysql_insert(p);    //������Ϣ
			break;
		case 6:
			mysql_tongji(p);     //ͳ�Ƹ����ֺܷ�ƽ������Ϣ
			break;

		case 7:                    //�˳� 
			break;
		}
	} while (m != 7);
}
//������Ϣ 
void mysql_input(Student* r)
{
	int i, n, t;
	for (i = 0; i < num; i++)
	{
		cout << "������ѧ��:";   cin >> r[i].term;
		cout << "�������" << i + 1 << "���˵�ѧ��:";   cin >> r[i].num;
		if (i >= 1)
		{
			for (n = 0; n < i; n++)
			{
				if (r[n].num == r[i].num)
				{
					cout << "��ѧ���Ѵ��ڣ���" << endl;
					t = 1;
				}
			}
		}
		if (t == 1)     //��ʾ���ظ� 
		{
			i--;
			t = 0;
			continue;
		}
		cout << "����������:";
		cin >> r[i].name;
		cout << "������ �ߵ���ѧ �ɼ�:";
		cin >> r[i].mark1;
		cout << "������ ���ݽṹ �ɼ�:";
		cin >> r[i].mark2;
		cout << "������ ��ѧӢ�� �ɼ�:";
		cin >> r[i].mark3;
		r[i].sum = r[i].mark1 + r[i].mark2 + r[i].mark3;
		r[i].average = (r[i].mark1 + r[i].mark2 + r[i].mark3) / 3;
	}
}

//�����Ϣ 
void mysql_output(Student* r)
{
	int m;
	system("cls");                   //����
	if (num > 0)
	{
		FILE* fp;
		if ((fp = fopen("student.txt", "r")) == NULL) //rֻ�� 
		{
			cout << "���ܴ�" << endl;
			exit(0);
		}
		for (int n = 0; n < num; n++)
		{

			fscanf(fp, "%d%s%f%f%f%d%f%f", &r[n].num, r[n].name, &r[n].mark1, &r[n].mark2, &r[n].mark3, &r[n].term, &r[n].sum, &r[n].average);
		}
		fclose(fp);                            //�ر��ļ� 

		cout << "�Ѿ�����" << endl;
		cout << "----------------------------> ѧ����Ϣ���� < ------------------------------" << endl;
		cout << "ѧ��" << setw(6) << "����" << setw(10) << "�ߵ���ѧ" << setw(10) << "���ݽṹ" << setw(10) //setw(6) ���������� 
			<< "��ѧӢ��" << setw(6) << "ѧ��" << setw(6) << "�ܷ�" << setw(8) << "ƽ����" << endl;
		cout << "---------------------------------------------------------------" << endl;
		for (m = 0; m < num; m++)
		{
			cout << r[m].num << setw(6) << r[m].name << setw(7) << r[m].mark1 << setw(10)
				<< r[m].mark2 << setw(10) << r[m].mark3 << setw(8) << r[m].term << setw(6) << r[m].sum << setw(6) << r[m].average << endl;
		}
		cout << "\0\0" << endl;
	}
	else   cout << "δ�����κ���Ϣ����" << endl;
}
//��ѧ�ż�ѧ�ڲ��� 
void mysql_searchnum(Student* r)
{
	int n, k;
	int m = 0;
	system("cls");                              //���� 
	if (num > 0) {
		cout << "������Ҫ����ѧ����ѧ��:";   cin >> n;
		cout << "������ѧ�ں�:";
		cin >> k;
		for (int m = 0; m < num; m++) {
			if ((r[m].num == n) &( r[m].term == k))  //����ҵ������������ѭ�� 
			{
				cout << endl;
				cout << "-------------------------> Ҫ���ҵ���Ϣ���� < ---------------------------- - " << endl;
				cout << "ѧ��" << setw(6) << "����" << setw(10) << "�ߵ���ѧ" << setw(10) << "���ݽṹ"
					<< setw(10) << "��ѧӢ��" << setw(6) << "ѧ��" << setw(6) << "�ܷ�" << setw(8) << "ƽ����" << endl;
				cout << r[m].num << setw(6) << r[m].name << setw(7) << r[m].mark1 << setw(10) << r[m].mark2 << setw(10) << r[m].mark3 << setw(8) << r[m].term << setw(6) << r[m].sum << setw(8) << r[m].average << endl;
				break;
			}
		}

		if (r[m].num != n && r[m].term != k)   //��û�ҵ���ʾ������ 
			cout << "��ѧ�Ų�����,��û�����ѧ�ڵĳɼ�!" << endl;
	}
	else   cout << "δ�����κ���Ϣ����" << endl;
}
//��ѧ�ż�ѧ���޸���Ϣ      
void mysql_change(Student *r)
{
	FILE* fp;
	int n = 0;
	char chiose = 'Y';
	if (num > 0)
	{
		int n, k;
		int t = 0;
		system("cls");                                  //���� 
		cout << "����Ҫ�޸ĳɼ���ѧ��ѧ��:";
		cin >> n;
		cout << "�����޸ĵ�ѧ��:";
		cin >> k;

		for (int m = 0; m < num; m++) {
			if (r[m].num == n && r[m].term == k) {
				int j;
				cout << endl;
				cout << "-------------------------> �޸�ǰ����Ϣ���� < --------------------------" << endl;
				cout << "ѧ��" << setw(6) << "����" << setw(10) << "�ߵ���ѧ" << setw(10) << "���ݽṹ"
					<< setw(10) << "��ѧӢ��" << setw(6) << "ѧ��" << setw(6) << "�ܷ�" << setw(8) << "ƽ����" << endl;

				cout << r[m].num << setw(6) << r[m].name << setw(7) << r[m].mark1 << setw(10) << r[m].mark2 << setw(10) << r[m].mark3 << setw(8) << r[m].term << setw(6) << r[m].sum << setw(8) << r[m].average << endl;
				cout << endl;
				while (chiose == 'Y' || chiose == 'y') {
					cout << "\t\t\t--------> �����޸ĵ���Ŀ���� <-------\n" << endl;
					cout << "\t\t\t 1.�޸�ѧ���� �ߵ���ѧ �ɼ���¼\n" << endl;
					cout << "\t\t\t 2.�޸�ѧ���� ���ݽṹ �ɼ���¼\n" << endl;
					cout << "\t\t\t 3.�޸�ѧ���� ��ѧӢ�� �ɼ���¼\n" << endl;
					cout << "��ѡ��:";
					cin >> j;
					switch (j)
					{
					case 1:
						cout << "�����µ� �ߵ���ѧ �ɼ�:";
						cin >> r[m].mark1;
						break;
					case 2:
						cout << "�����µ� ���ݽṹ �ɼ�:";
						cin >> r[m].mark2;
						break;
					case 3:
						cout << "�����µ� ��ѧӢ�� �ɼ�:";
						cin >> r[m].mark3;
						break;
					}      t = 1;
					cout << "�Ƿ�Ҫ�����޸Ĵ�ѧ���������ɼ���¼��(Y/N)";
					fflush(stdin);      //������뻺������ͨ����Ϊ��ȷ����Ӱ���������ݶ�ȡ
					cin >> chiose;
				}
			}
		}
	}
	else   cout << "δ�����κ���Ϣ����" << endl;
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		cout << "���ܴ�" << endl;
		exit(0);
	}
	for (n = 0; n < num; n++)
	{
		fprintf(fp, "%d   %s   %.1f   %.1f   %.1f   %d   %.1f   %.1f", r[n].num, r[n].name, r[n].mark1, r[n].mark2, r[n].mark3, r[n].term, r[n].sum, r[n].average);
		fprintf(fp, "\n");
	}
	fclose(fp);
	cout << "�ļ����޸Ĳ�д��" << endl;
}
//���� 
void mysql_insert(Student* r)
{
	FILE* fp;  int m;  char n;  do
	{
		if ((fp = fopen("student.txt", "r")) == NULL)
		{
			cout << "���ܴ�" << endl;
			exit(0);
		}
		for (int o = 0; o < num; o++)
		{

			fscanf(fp, "%d%s%f%f%f%d%f%f", &r[o].num, r[o].name, &r[o].mark1, &r[o].mark2, &r[o].mark3, &r[o].term, &r[o].sum, &r[o].average);
		}
		Student* y = (Student*)new Student[num + 1]; //������һ�����飬���ڴ������ӵļ�¼
		for (m = 0; m < num; m++)
		{
			y[m] = r[m];
		}
		r = y;
		cout << "������ѧ��:";
		cin >> r[num].term;
		cout << "������ѧ��:";
		cin >> r[num].num;
		cout << "����������:";
		cin >> r[num].name;
		cout << "������ �ߵ���ѧ �ɼ�:";
		cin >> r[num].mark1;
		cout << "������ ���ݽṹ �ɼ�:";
		cin >> r[num].mark2;
		cout << "������ ��ѧӢ�� �ɼ�:";
		cin >> r[num].mark3;
		r[num].sum = r[num].mark1 + r[num].mark2 + r[num].mark3;  //�����ܷ� 
		r[num].average = (r[num].mark1 + r[num].mark2 + r[num].mark3) / 3;

		num++;
		cout << "�Ƿ�������룿������������y����������������" << endl;
		cin >> n;
	} while (n == 'y');

	if ((fp = fopen("student.txt", "w+")) == NULL)
	{
		cout << "�ļ����ܴ�" << endl;
		exit(0);
	}
	for (n = 0; n < num; n++)
	{

		fprintf(fp, "%d   %s   %.1f   %.1f   %.1f   %d   %.1f   %.1f", r[n].num, r[n].name, r[n].mark1, r[n].mark2, r[n].mark3, r[n].term, r[n].sum, r[n].average);
		fprintf(fp, "\n");
	}

	fclose(fp);
	cout << "�Ѿ�д��" << endl;
}
//ͳ�Ƹ����ּܷ�ƽ���� 
void mysql_tongji(Student* r)
{
	float summark1 = 0, summark2 = 0, summark3 = 0;
	float avemark1 = 0, avemark2 = 0, avemark3 = 0;
	FILE* fp;
	system("cls");                              //���� 
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
		cout << "�ߵ���ѧ �ܷ�Ϊ:" << summark1 << "ƽ����Ϊ:" << avemark1 << endl;
		cout << endl;
		cout << "���ݽṹ �ܷ�Ϊ:" << summark2 << "ƽ����Ϊ:" << avemark2 << endl;
		cout << endl;
		cout << "��ѧӢ�� �ܷ�Ϊ:" << summark3 << "ƽ����Ϊ:" << avemark3 << endl;
		cout << endl;
		if ((fp = fopen("student.txt", "w")) == NULL)
		{
			cout << "�Բ����ļ����ܴ򿪣�" << endl;
			exit(0);
		}
		for (int n = 0; n < num; n++)
		{

			fprintf(fp, "%d   %s   %.1f   %.1f   %.1f   %d   %.1f   %.1f", r[n].num, r[n].name, r[n].mark1, r[n].mark2, r[n].mark3, r[n].term, r[n].sum, r[n].average);
			fprintf(fp, "\n");
		}
		cout << "�ߵ���ѧ �ܷ�Ϊ:" << summark1 << endl;
		cout << "���ݽṹ �ܷ�Ϊ:" << summark2 << endl;
		cout << "��ѧӢ�� �ܷ�Ϊ:" << summark3 << endl;
	}
	else   cout << "�Բ���δ�����κ���Ϣ��" << endl;
}