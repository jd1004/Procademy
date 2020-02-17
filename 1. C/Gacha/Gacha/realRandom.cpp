////////////// ��¥ ���� ��í //////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct st_ITEM
{
	char	Name[30];
	int		Rate;		// �������� ���� ����
};

st_ITEM g_Gatcha[] = {
	{ "Į",		20 },
	{ "����",		20 },
	{ "�Ź�",		20 },
	{ "����",		20 },
	{ "�ʰ��·����",	5 },
	{ "�ʰ��¹���",		5 },
	{ "�ʰ��·�����Ź�", 1 }
};


void Gatcha()
{
	// 1. ��ü �����۵��� ���� �� ���� ����.
	int sum = 0;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++)
		sum += g_Gatcha[i].Rate;
	

	// 2. rand() �Լ��� Ȯ���� ����
	// ���⼭ Ȯ���� 1/100 �� �ƴϸ�, 1/���պ��� ��.
	// int iRand = Ȯ�����ϱ�
	int iRand = (double)rand() / (RAND_MAX)*(sum - 1) + 1;

	
	// 3. ��ü ������ ���̺��� ���鼭
	// ������ ���� Rand ���� �ش� ������ �������� ã�´�.
	int select = g_Gatcha[0].Rate;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++) {

		if (iRand <= select) {
			printf("%d %s\n", iRand, g_Gatcha[i].Name);
			break;
		}
		else {
			select += g_Gatcha[i + 1].Rate;
		}
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