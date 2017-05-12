#include<iostream>
using namespace std;

#define MAXPRO 20
#define MAXRES 20

int ProcessNum;         //���̵�����
int ResourcesNum;       //��Դ��������
int Resources[MAXRES];           //������Դ��������
int Max[MAXPRO][MAXRES];         //����������Դ�����ֵ
int Allocation[MAXPRO][MAXRES];  //�����Ѿ��������Դ����
int Need[MAXPRO][MAXRES];        //���̻���Ҫ����Դ����
int Request[MAXPRO][MAXRES];     //�����������Դ����

int Work[MAXRES];                //ϵͳ���ṩ���������еĸ�����Դ��Ŀ
bool Finish[MAXPRO];             //�����Ƿ�Safe

int p[MAXPRO];

void Init();
bool Safe();
void Bank();


int main()
{
	Init();
	Bank();
	return 0;
}

//��ʼ��
void Init()
{
	int process, resource;

	cout << "��������̵�����:" << endl;
	cin >> ProcessNum;

	cout << "��������Դ��������:" << endl;
	cin >> ResourcesNum;

	cout << "������ÿ�����̶Ը�����Դ�������������:" << endl;
	cout << endl;
	for (process = 0; process < ProcessNum; process++)
	{
		cout << process << " �Ž���������Դ��������Ϊ: ";
		for (resource = 0; resource < ResourcesNum; resource++)
		{
			cin >> Max[process][resource];
		}
	}

	cout << endl;
	cout << "������ÿ���������еĸ�����Դ����" << endl;
	cout << endl;
	for (process = 0; process < ProcessNum; process++)
	{
		cout << process << " �Ž���ӵ�е�";
		for (resource = 0; resource < ResourcesNum; resource++)
		{
			cout << resource << " ����Դ����Ϊ: ";
			cin >> Allocation[process][resource];

			Need[process][resource] = Max[process][resource] - Allocation[process][resource];
			if (Need[process][resource] < 0)
			{
				cout << "�˽�������Ҫ��" << resource << "����Դ����ֵ����������Դֵ������������" << endl;
				resource--;
				continue;
			}
		}
	}

	cout << endl;
	cout << "�����������Դ���е�����:" << endl;
	for (resource = 0; resource < ResourcesNum; resource++)
	{
		cout << resource << "����Դ��������Ϊ�� ";
		cin >> Resources[resource];
	}

}

void Bank()
{
	int process;
	int res;

	do
	{
		cout << endl;
		cout << "������������Դ�Ľ��̺�: " << endl;
		cin >> process;
	} while (process > ProcessNum);

	cout << "������" << process << " �Ž�������";
	for (res = 0; res < ResourcesNum; res++)
	{
		cout << res << " ����Դ������: ";
		cin >> Request[process][res];

		if (Request[process][res] > Need[process][res])
		{
			cout << "�������Դ��������������Դ���� " << endl;
			cout << "Unsafe" << endl;
			return;
		}

		else if (Request[process][res] > Resources[res])
		{
			cout << "�������Դ��������ϵͳ��Դ����" << endl;
			cout << "Unsalf" << endl;
			return;
		}
	}

	for (res = 0; res < ResourcesNum; res++)
	{
		Resources[res] -= Request[process][res];
		Allocation[process][res] += Request[process][res];
		Need[process][res] -= Request[process][res];
	}

	if (Safe())
	{
		cout << "Safe" << endl;
		//�����ȫ��������
	}
	else
	{
		Resources[res] += Request[process][res];
		Allocation[process][res] -= Request[process][res];
		Need[process][res] += Request[process][res];

		cout << "Unsafe" << endl;
	}

}

bool Safe()
{
	int process, resource;
	int pro_count = 0;
	int loop_count = 0;
	int true_count = 0;

	for (resource = 0; resource < ResourcesNum; resource++)
	{
		Work[resource] = Resources[resource];
	}

	for (process = 0; process < ProcessNum; process++)
	{
		Finish[process] = false;
	}

	//for (process = 0; process < ProcessNum; process++)
	while(true)
	{

		//cout << "����ѭ��" << endl;
		process = process % ProcessNum;

		if(Finish[process] == false)
		{
			for (resource = 0; resource < ResourcesNum; resource++)
			{
				if (Need[process][resource] > Work[resource])
					break;
			}

			if (resource == ResourcesNum)
			{
				Finish[process] = true;
				true_count++;
				for (resource = 0; resource < ResourcesNum; resource++)
				{
					Work[resource] += Allocation[process][resource];
				}
				p[pro_count] = process;
				pro_count++;
				loop_count = 0;
			}
			else
			{
				loop_count++;
				continue;
			}
		}

		if (loop_count >= ProcessNum || true_count >= ProcessNum)
		{
			break;
		}
		process++;
	}

	if (pro_count == ProcessNum)
	{
		cout << "��ȫ����: ";
		for (int i = 0; i < pro_count; i++)
		{
			cout << p[i] << " ";
		}
		cout << endl;
		return true;
	}
	else
	{
		return false;
	}
}