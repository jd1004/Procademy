////////////// ���̺� ���� ��í //////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct st_ITEM
{
	char	Name[30];
	int		Rate;		// �Ϲ� ���� �̱�� ���� �뵵
	int		WinTime;	// �� �������� ���� �̱� ȸ��
						// 0 �̸� �Ϲ� ������
						// 0 �� �ƴϸ� �� ȸ������ ����
};

st_ITEM g_Gatcha[] = {
	{ "Į",				20, 0 },
	{ "����",				20, 0 },
	{ "�Ź�",				20, 0 },
	{ "����",				20, 0 },
	{ "�ʰ��·����",		5, 0 },
	{ "�ʰ��¹���",			5, 0 },
	{ "�ʰ��·�����Ź�1", 1, 50 },
	{ "�ʰ��·�����Ź�2", 1, 51 },
	{ "�ʰ��·�����Ź�3", 1, 10 }

	// ������ 3���� �������� �Ϲ� Ȯ���δ� ������ ������
	// �ڿ� �Էµ� WinTime ȸ������ 100% �� ����.
};

// �̱��� ȸ���� ���� ����� �ǰ� �־�� ��.
int iCount = 0;

int count = 0;

void Gatcha()
{
	// �̱� ȸ�� ����. (�̴� ���������� ��� �Ǿ�� ��)
	iCount++;
	count++;

	// 1. ��ü �����۵��� ���� �� ���� ����.
	// ��, WinTime �� ������ �������� Ȯ���� ��� ��ü�� �ƴϱ� ������ ����.
	int sum = 0;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++) {

		if (g_Gatcha[i].WinTime == 0)
			sum += g_Gatcha[i].Rate;
	}
	
	// 2. �� �̱� ȸ���� ���� ���� �������� �ִ��� Ȯ��
	// WinTime �� iCount �� ���� �������� ã�´�.
	// �ִٸ�.. �� �������� �̰� �ߴ�.
	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++) {
		
		if (g_Gatcha[i].WinTime == iCount)
		{
			printf("%d %s\n", count, g_Gatcha[i].Name);

			if (iCount == 51) 
				iCount = 0;

			return;
		}

	}
	
	// 3. rand() �Լ��� Ȯ���� ����
	// ���⼭ Ȯ���� 1/100 �� �ƴϸ�, 1/���պ��� ��.
	// int iRand = Ȯ�����ϱ�;
	int iRand = (double)rand() / (RAND_MAX)*(sum - 1) + 1;


	// 4. ��ü ������ ���̺��� ���鼭
	// ������ ���� Rand ���� �ش� ������ �������� ã�´�.
	int select = g_Gatcha[0].Rate;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++) {

		if (iRand <= select) {
			printf("%d %s\n", count, g_Gatcha[i].Name);
			break;
		}
		else {
			select += g_Gatcha[i + 1].Rate;
		}
	}

	// 5. �̱� ȸ���� �ʱ�ȭ �ؾ����� �Ǵ��Ͽ� �ʱ�ȭ.
	if (iCount == 51) {
		iCount = 0;
	}
}

void main()
{
	srand((unsigned)time(NULL));

	while (1)
	{
		getchar();
		Gatcha();
	}
}