#include<iostream>
#include<stdio.h> 
#include<string.h>
#include<cmath>//abs(b-a)
#pragma warning(disable:4996)//���Ծ���4996
using namespace  std;
double a[20][20];//��ʼ���ݾ���
double difference[20][20];//������Ϣ����
double relate[20][20];//�ҹ���ϵ������
double relation[20][20];//�Ҿ������ 
double Diff[20][20];//�򻯰��ʼ���ݾ���

int whether[20];
int Class[20][20];
//�����ʼ����
int getShuJu() {
	int i, j;
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			cin >> a[i][j];
		}
	}

	return 0;
}
// ��� int
int myCOUT(int ppp[20][20]) {
	int i, j;
	for (i = 0; i <= 15; i++)
	{

		printf("��%02d�� ", i);
		//cout << "��" << i << "��";
		for (j = 0; j <= 9; j++)
		{
			if (i == 0 && j != 0) cout << "��" << j << "�� ";
			else if (j != 0) {
				//printf("%02d ", a[i][j]);//�����ʼ����
				printf("%05d ", ppp[i][j]);
			}
		}
		cout << endl;
	}
	return 0;

}

// ��� double
int myCOUT(double ppp[20][20], int hang_end, int lie_end) {
	int i, j;
	for (i = 0; i <= hang_end; i++)
	{

		printf("��%02d�� ", i);
		//cout << "��" << i << "��";
		for (j = 0; j <= lie_end; j++)
		{
			if (i == 0 && j != 0) printf("��%02d��    ", j); //cout << "��" << j << "��    ";
			else if (j != 0) {
				//printf("%02d ", a[i][j]);//�����ʼ����
				printf("%07.4f   ", ppp[i][j]);
			}
		}
		cout << endl;
	}
	return 0;

}

//��д�������
int getMyDiff(int hang_start, int hang_end, int target_hang, double p[20][20]) {
	int m, n;
	for (m = hang_start; m <= hang_end; m++) {
		for (n = 1; n <= 9; n++) {
			difference[m][n] = abs(p[m][n] - p[target_hang][n]);
		}
	}

	return 0;
}
//���������������Ϣ
double get_M(int hang_start, int hang_end, int lie_end) {
	int p, k;
	double max = difference[hang_end][lie_end];
	for (p = hang_start; p <= hang_end; p++) {
		for (k = 1; k <= lie_end; k++) {
			if (max <= difference[p][k])
				max = difference[p][k];
		}
	}
	return max;
}
//���������С������Ϣ
double get_m(int hang_start, int hang_end, int lie_end) {
	int p, k;
	double min = difference[hang_end][lie_end];
	for (p = hang_start; p <= hang_end; p++) {
		for (k = 1; k <= lie_end; k++) {
			if (min >= difference[p][k])
				min = difference[p][k];
		}
	}
	return min;
}
//�������ϵ������
int calculateRelate(double m, double M, int hang_start, int hang_end, int lie_end) {
	// ����ѡ0.5
	int p, k;
	double son;
	double mom;


	for (p = hang_start; p <= hang_end; p++) {
		double sum = 0;
		for (k = 1; k <= lie_end; k++) {
			son = m + 0.5 * M;
			mom = difference[p][k] + 0.5 * M;
			relate[p][k] = son / mom;
			sum = sum + relate[p][k];
		}
	}
	return 0;
}
//����Ҿ���ֵ
int getRelation(int i, int hang_end, int lie_end) {
	int p, k;
	int r = i;
	for (p = i; p <= hang_end; p++) {
		double sum = 0;

		for (k = 1; k <= lie_end; k++) {
			sum = sum + relate[p][k];
		}
		relation[i][r] = sum / 9;
		r++;
	}

	return 0;
}

//���㵥���ҹ���
double getRelate(int Comparison_target, int Comparison_candidates, int hang_start, int hang_end, int lie_end) {
	//�ڴ�֮ǰ������Ϣ�����Ѿ����������

	double M = get_M(hang_start, hang_end, lie_end);
	//	cout << "M = " << M;

	double m = get_m(hang_start, hang_end, lie_end);
	//	cout << "   m = " << m << endl;

	calculateRelate(m, M, hang_start, hang_end, lie_end);
	return 0;
}
//�����������ٺͼ���
int clear(int hang_end, int lie_end) {
	/*int i, j;
	double temp;
	for (i = 1; i <= hang_end; i++) {
	temp = a[i][1];
	for (j = 1; j <= lie_end; j++) {
	a[i][j] = a[i][j] / temp ;
	}
	}*/
	int i, j;
	double temp;
	for (i = 1; i <= hang_end; i++) {
		double min = a[i][1];
		double max = a[i][1];
		for (j = 1; j <= lie_end; j++) {
			if (max <= a[i][j]) max = a[i][j];
			if (min >= a[i][j]) min = a[i][j];
		}

		for (j = 1; j <= lie_end; j++) {
			a[i][j] = abs(a[i][j] - min) / (max - min);
		}
	}
	return 0;
}

int visit(int i) {
	cout << i << " ";
	whether[i] = 1;
	int v;
	for (v = 0; v < 15; v++) {
		if (whether[v] == 0 && Class[i][v] == 1)
			visit(v);
	}
	return 0;
}
////�Ҿ���ָ��  >=0.8
//int getClass() {
//	int i, j;
//	int p, k;
//	int m = 1, n = 1;
//	cout << "�ڽӾ��� " << "----------------------------------------------------" << endl;
//	for (i = 1; i <= 15; i++) {	
//		for (j = 1; j <= 15; j++) {
//			if (relation[i][j] >= 0.8 && i != j)
//			{
//				Class[i][j] = 1;
//				Class[j][i] = 1;
//				
//			}
//			
//			cout << Class[i][j] << " ";			
//		}
//		cout << endl;
//	}
//
//	for (i = 1; i <= 15; i++) {
//		visit(i);
//	}
//	return 0;
//}
//�õ��µ���������
int getDiff(int hang_end, int lie_end) {
	int i, j;
	for (int i = 1; i <= hang_end; i++) {
		for (j = 1; j <= lie_end; j++) {
			if (i == 1) { Diff[i][j] = a[1][j]; }
			if (i == 2) { Diff[i][j] = a[6][j]; }
			if (i == 3) { Diff[i][j] = a[7][j]; }
			if (i == 4) { Diff[i][j] = a[11][j]; }
			if (i == 5) { Diff[i][j] = a[12][j]; }
			if (i == 6) { Diff[i][j] = a[14][j]; }

		}
	}

	return 0;
}
//��ȡ��������
int getStand(int hang_end, int lie_end) {
	int i, j;

	for (i = 1; i <= lie_end; i++) {
		double max = 0;
		for (j = 1; j <= hang_end; j++) {
			if (max <= Diff[j][i])
			{
				max = Diff[j][i];
			}

		}
		j = j;
		Diff[j][i] = max;

	}
	return 0;
}
//�õ��޸ĺ�Ļ�ɫϵ������
int getRelation2(int hang_end, int lie_end) {
	int i, j;
	for (j = 1; j <= lie_end; j++) {
		double sum = 0;
		for (i = 1; i <= hang_end; i++) {
			sum = sum + relate[i][j];
		}
		relate[hang_end + 1][j] = sum / hang_end;
	}

	return 0;
}

void function_A() {
	int i, j;
	for (i = 1; i <= 14; i++) {
		memset(difference, 0, sizeof(difference));// �ÿղ�����Ϣ����
		memset(relate, 0, sizeof(relate));//�ÿջҹ���ϵ������

		getMyDiff(i, 15, i, a);//��д�������


							   /*{
							   cout << "��" << i << "��Ϊ��׼�Ĳ�����Ϣ����Ϊ��(difference[][])" << endl;
							   myCOUT(difference, 15, 9);
							   cout << "--------------------------------" << endl;
							   }*/

		for (j = i; j <= 15; j++) {
			getRelate(i, j, i, 15, 9);//��д�ҹ���ϵ������
		}

		getRelation(i, 15, 15);//��д�Ҿ������
		if (i == 14)
		{
			cout << "��" << i << "��Ϊ��׼�ĻҾ������Ϊ��(relation[][])" << endl;
			myCOUT(relation, 15, 15);
			cout << "--------------------------------" << endl;

		}


	}
}

void function_B() {
	int i, j;
	getDiff(6, 9);
	cout << "�����ʼ������������" << endl;   myCOUT(Diff, 6, 9); cout << "--------------------------------" << endl;
	getStand(6, 9);
	cout << "�����ʼ������������,���е�7����ʾΪ��������" << endl;   myCOUT(Diff, 7, 9); cout << "--------------------------------" << endl;

	memset(difference, 0, sizeof(difference));// �ÿղ�����Ϣ����
	memset(relate, 0, sizeof(relate));//�ÿջҹ���ϵ������
	getMyDiff(1, 6, 7, Diff);//�õ��µĲ�����Ϣ����
	cout << "�µĲ�����Ϣ����Ϊ" << endl; myCOUT(difference, 6, 9); cout << "--------------------------------" << endl;

	for (i = 1; i <= 6; i++)
		getRelate(7, i, 1, 6, 9);//��д�ҹ���ϵ������  ��һ������Ϊ�Ƚ�Ŀ�꣬�ڶ���Ϊ�ȽϺ�ѡ��
	cout << "�»ҹ���ϵ������Ϊ��(relate[][])" << endl; myCOUT(relate, 6, 9);   cout << "--------------------------------" << endl;

	cout << "�ɴ˿ɵ��ۺ����н������ " << endl;
	getRelation2(6, 9);

	for (i = 1; i <= 9; i++)
		cout << relate[7][i] << " ";



}
int main() {
	relation[15][15] = 1.0;
	//freopen("C:\\Users\\linkey\\Desktop\\��ɫ\\ѡ��in.txt", "r", stdin);//�����ض������������ļ�
	freopen("C:\\Users\\linkey\\Desktop\\��ɫ\\ѡ��out.txt", "w", stdout);
	freopen("\\ѡ��in.txt", "r", stdin);
	getShuJu();//��ȡ��ʼ����

				 //myCOUT(a, 15,9);
	clear(15, 9);//�������Ժ�����
	{//��ӡ��������ݼ����Ƿ���ȷ
		cout << "�����ʼ�����������ٺ���������" << endl;
		myCOUT(a, 15, 9);
		cout << "--------------------------------" << endl;
	}

	function_A();// 


				 //�ٽ�ȡֵ>=0.8

	cout << "�����Ϸ�����֪ X1��X2, X3��X4��X5��X8��X9��X10��11��X13��X14��Ϊһ��" << endl;
	cout << "X6��Ϊһ��" << endl;
	cout << "X7��Ϊһ��" << endl;
	cout << "X11��Ϊһ��" << endl;
	cout << "X12��Ϊһ��" << endl;
	cout << "X14��Ϊһ��" << endl;
	cout << "һ��6������" << endl;
	cout << "ÿһ����С�Ǳ�����Ϊ���������趨��ʼ���ݣ����ûҹ�������" << endl;

	function_B();

	//freopen("CON", "r", stdin);//�����������ض�������̨
	fclose(stdin);//�ر��ļ� 
	fclose(stdout);//�ر��ļ� 
	system("pause");//��ͣ
	return 0;

}

