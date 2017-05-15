#include<stdio.h>
#include<stdbool.h>

#define MAXPRO 10
#define MAXRES 10

int ProcessNum;                            //进程总数
int ResourceNum;                           //资源总数
int MaxResource[MAXRES];                   //各个资源数量原始数组
int NowResource[MAXRES];                   //各个资源数量跟踪数组
int ProcessRequire[MAXPRO][MAXRES];        //各个进程所需要的资源总量
int ProcessAllocation[MAXPRO][MAXRES];     //各个进程已经分配到的资源数量
int ProcessNeed[MAXPRO][MAXRES];           //各个进程还需要的资源数量
int ProcessRequest[MAXPRO][MAXRES];        //各个进程请求的资源数量

int SafeSeq[MAXPRO];                       //安全序列数组
bool SafeProcess[MAXPRO];                  //进程安全测试数组

bool Init();
void Bank();
bool IsSafe();
void Release(int process);

int main()
{
	bool IsSuccess = Init();
	if (!IsSuccess)
	{
		printf("测试数据输入有误,导致进程资源分配量大于系统资源总量。");
	}
	Bank();
}

bool Init()
{
	int process, resource;
	int totle;                //所有进程使用同一资源的数目和，用于跟踪资源函数模块
	
	//输入进程总数和资源总数
	printf("请输入进程数和资源的种类数: ");
	scanf("%d%d", &ProcessNum, &ResourceNum);
	printf("\n");

	//输入各个资源的资源总数
	printf("请输入%2d种资源的各个资源具体数量: ", ResourceNum);
	for (resource = 1; resource <= ResourceNum; resource++)
	{
		scanf("%d", &MaxResource[resource-1]);
		NowResource[resource - 1] = MaxResource[resource - 1];
	}
	printf("\n");

	//输入各个进程所要完成工作所需要的各个资源数量
	printf("请输入各个进程所要完成工作需要的进程资源数量: \n");
	for (process = 1; process <= ProcessNum; process++)
	{
		printf("第%2d个进程所需要的各个资源量为: ", process);

		for (resource = 1; resource <= ResourceNum; resource++)
		{
			scanf("%d", &ProcessRequire[process - 1][resource - 1]);
		}
	}
	printf("\n");

	//输入各个进程已经分配到的各个资源数量
	printf("请输入各个进程已经分配到的进程各个资源数量: \n");
	for (process = 1; process <= ProcessNum; process++)
	{
		printf("第%2d个进程已经分配到的各个资源量为: ", process);

		for (resource = 1; resource <= ResourceNum; resource++)
		{
			scanf("%d", &ProcessAllocation[process - 1][resource - 1]);
		}
	}
	printf("\n");

	//更新NowResource数组，更新各个资源数量
	for (resource = 1; resource <= ResourceNum; resource++)
	{
		totle = 0;
		for (process = 1; process <= ProcessNum; process++)
		{
			totle += ProcessAllocation[process - 1][resource - 1];
		}
		NowResource[resource - 1] -= totle;
		if (NowResource[resource - 1] < 0)
		{
			return false;
		}
	}

	//初始化ProcessNeed数组
	for (process = 1; process <= ProcessNum; process++)
	{
		for (resource = 1; resource <= ResourceNum; resource++)
		{
			ProcessNeed[process - 1][resource - 1] = ProcessRequire[process - 1][resource - 1] - ProcessAllocation[process - 1][resource - 1];
		}
	}

	return true;
}

void Bank()
{
	int process, resource;
	
	//测试代码
	/*
	printf("系统剩余资源量: ");
	for (resource = 1; resource <= ResourceNum; resource++)
	{
		printf("%d ", NowResource[resource - 1]);
	}
	printf("\n");
	*/
	if (IsSafe())
	{
		printf("安全序列为: ");
		for (process = 1; process <= ProcessNum; process++)
		{
			printf("%d ", SafeSeq[process - 1]);
		}
		printf("\n");
	}
	else
	{
		printf("UnSafe!\n");
	}
}

bool IsSafe()
{
	int process, resource;
	int safeCount = 0;
	int proCount = 0;

	//将进程安全测试数组全部赋值为false，即不安全
	for (process = 1; process <= ProcessNum; process++)
	{
		SafeProcess[process - 1] = false;
	}

	for (process = 1; process <= ProcessNum; process++)
	{
		if (SafeProcess[process - 1])
		{
			continue;
		}
		else  //进程开始进行安全测试
		{
			for (resource = 1; resource <= ResourceNum; resource++)
			{
				if (NowResource[resource - 1] < ProcessNeed[process - 1][resource - 1])
				{
					break;
				}
				else
				{
					if (NowResource[resource - 1] >= ProcessNeed[process - 1][resource - 1])
					{
						if (resource == ResourceNum)
						{
							SafeProcess[process - 1] = true;
							Release(process);
							SafeSeq[proCount++] = process;
							process = 0;
							break;
						}
						else continue;
						
					}
					else continue;
				}
			}
		}
	}

	for (process = 1; process <= ProcessNum; process++)
	{
		if (SafeProcess[process - 1] == true)
			safeCount++;
	}

	if (safeCount == ProcessNum)
		return true;
	else
		return false;
}

void Release(int process)
{
	int resource;

	for (resource = 1; resource <= ResourceNum; resource++)
	{
		NowResource[resource - 1] += ProcessAllocation[process - 1][resource - 1];
		ProcessAllocation[process - 1][resource - 1] = 0;
		ProcessNeed[process - 1][resource - 1] = 0;
		ProcessRequest[process - 1][resource - 1] = 0;
		ProcessRequire[process - 1][resource - 1] = 0;
	}


	//测试代码
	/*for (resource = 1; resource <= ResourceNum; resource++)
	{
		printf("%d ", NowResource[resource - 1]);
	}
	printf("\n");

	for (int pro = 1; pro <= ProcessNum; pro++)
	{
		printf("%d ", SafeProcess[pro - 1]);
	}
	printf("\n");
	*/
}