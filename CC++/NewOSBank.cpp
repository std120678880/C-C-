#include<stdio.h>
#include<stdbool.h>

#define MAXPRO 10
#define MAXRES 10

int ProcessNum;                            //��������
int ResourceNum;                           //��Դ����
int MaxResource[MAXRES];                   //������Դ����ԭʼ����
int NowResource[MAXRES];                   //������Դ������������
int ProcessRequire[MAXPRO][MAXRES];        //������������Ҫ����Դ����
int ProcessAllocation[MAXPRO][MAXRES];     //���������Ѿ����䵽����Դ����
int ProcessNeed[MAXPRO][MAXRES];           //�������̻���Ҫ����Դ����
int ProcessRequest[MAXPRO][MAXRES];        //���������������Դ����

int SafeSeq[MAXPRO];                       //��ȫ��������
bool SafeProcess[MAXPRO];                  //���̰�ȫ��������

bool Init();
void Bank();
bool IsSafe();
void Release(int process);

int main()
{
	bool IsSuccess = Init();
	if (!IsSuccess)
	{
		printf("����������������,���½�����Դ����������ϵͳ��Դ������");
	}
	Bank();
}

bool Init()
{
	int process, resource;
	int totle;                //���н���ʹ��ͬһ��Դ����Ŀ�ͣ����ڸ�����Դ����ģ��
	
	//���������������Դ����
	printf("���������������Դ��������: ");
	scanf("%d%d", &ProcessNum, &ResourceNum);
	printf("\n");

	//���������Դ����Դ����
	printf("������%2d����Դ�ĸ�����Դ��������: ", ResourceNum);
	for (resource = 1; resource <= ResourceNum; resource++)
	{
		scanf("%d", &MaxResource[resource-1]);
		NowResource[resource - 1] = MaxResource[resource - 1];
	}
	printf("\n");

	//�������������Ҫ��ɹ�������Ҫ�ĸ�����Դ����
	printf("���������������Ҫ��ɹ�����Ҫ�Ľ�����Դ����: \n");
	for (process = 1; process <= ProcessNum; process++)
	{
		printf("��%2d����������Ҫ�ĸ�����Դ��Ϊ: ", process);

		for (resource = 1; resource <= ResourceNum; resource++)
		{
			scanf("%d", &ProcessRequire[process - 1][resource - 1]);
		}
	}
	printf("\n");

	//������������Ѿ����䵽�ĸ�����Դ����
	printf("��������������Ѿ����䵽�Ľ��̸�����Դ����: \n");
	for (process = 1; process <= ProcessNum; process++)
	{
		printf("��%2d�������Ѿ����䵽�ĸ�����Դ��Ϊ: ", process);

		for (resource = 1; resource <= ResourceNum; resource++)
		{
			scanf("%d", &ProcessAllocation[process - 1][resource - 1]);
		}
	}
	printf("\n");

	//����NowResource���飬���¸�����Դ����
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

	//��ʼ��ProcessNeed����
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
	
	//���Դ���
	/*
	printf("ϵͳʣ����Դ��: ");
	for (resource = 1; resource <= ResourceNum; resource++)
	{
		printf("%d ", NowResource[resource - 1]);
	}
	printf("\n");
	*/
	if (IsSafe())
	{
		printf("��ȫ����Ϊ: ");
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

	//�����̰�ȫ��������ȫ����ֵΪfalse��������ȫ
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
		else  //���̿�ʼ���а�ȫ����
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


	//���Դ���
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