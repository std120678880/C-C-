#include<iostream>
using namespace std;

#define MAXPRO 20
#define MAXRES 20

int ProcessNum;         //进程的数量
int ResourcesNum;       //资源的种类数
int Resources[MAXRES];           //可用资源数量数组
int Max[MAXPRO][MAXRES];         //进程所需资源的最大值
int Allocation[MAXPRO][MAXRES];  //进程已经分配的资源数量
int Need[MAXPRO][MAXRES];        //进程还需要的资源数量
int Request[MAXPRO][MAXRES];     //进程请求的资源数量

int Work[MAXRES];                //系统可提供给进程运行的各类资源数目
bool Finish[MAXPRO];             //进程是否Safe

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

//初始化
void Init()
{
	int process, resource;

	cout << "请输入进程的数量:" << endl;
	cin >> ProcessNum;

	cout << "请输入资源种类数量:" << endl;
	cin >> ResourcesNum;

	cout << "请输入每个进程对各个资源的最大需求数量:" << endl;
	cout << endl;
	for (process = 0; process < ProcessNum; process++)
	{
		cout << process << " 号进程所需资源数量依次为: ";
		for (resource = 0; resource < ResourcesNum; resource++)
		{
			cin >> Max[process][resource];
		}
	}

	cout << endl;
	cout << "请输入每个进程已有的各个资源数量" << endl;
	cout << endl;
	for (process = 0; process < ProcessNum; process++)
	{
		cout << process << " 号进程拥有的";
		for (resource = 0; resource < ResourcesNum; resource++)
		{
			cout << resource << " 号资源数量为: ";
			cin >> Allocation[process][resource];

			Need[process][resource] = Max[process][resource] - Allocation[process][resource];
			if (Need[process][resource] < 0)
			{
				cout << "此进程所需要的" << resource << "号资源分配值大于所需资源值。请重新输入" << endl;
				resource--;
				continue;
			}
		}
	}

	cout << endl;
	cout << "请输入各个资源现有的数量:" << endl;
	for (resource = 0; resource < ResourcesNum; resource++)
	{
		cout << resource << "号资源现有数量为： ";
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
		cout << "请输入请求资源的进程号: " << endl;
		cin >> process;
	} while (process > ProcessNum);

	cout << "请输入" << process << " 号进程所需";
	for (res = 0; res < ResourcesNum; res++)
	{
		cout << res << " 号资源的数量: ";
		cin >> Request[process][res];

		if (Request[process][res] > Need[process][res])
		{
			cout << "请求的资源数量大于所需资源数量 " << endl;
			cout << "Unsafe" << endl;
			return;
		}

		else if (Request[process][res] > Resources[res])
		{
			cout << "请求的资源数量大于系统资源总量" << endl;
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
		//输出安全进程序列
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

		//cout << "进入循环" << endl;
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
		cout << "安全序列: ";
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