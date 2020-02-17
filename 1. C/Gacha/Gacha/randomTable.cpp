////////////// ���� ���̺� ��í //////////////
//ù��° ��¥ ������ �̱� �κ��� ������ rand() �Լ��� ��ü�� �츮���� ������ �����.
//�츮�� ����� ������ ������ ���� �ȿ��� �ߺ����� ���� ������ �ʴ� ���� �Լ�.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct st_ITEM
{
	char	Name[30];
	int	Rate;		// �������� ���� ����
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

int RandTable[1000];		// ���� ������ �ִ� 1000 ���� ����.
static int RandTableIndex = 0;

int TableRand(int iMax)
{
	// ���� ���������� ������ ���� ����
	// ��� �����ؾ� �ϹǷ� ���� ��ġ �迭�� �ε����� ���� �Ͽ� �д�.

	//RandTableIndex == 0 �̸� RandTable �ʱ�ȭ.

	if (RandTableIndex == 0)
		RandTable[1000] = { 0 };

	/*do
	{
		1. �Ϲ� ���� rand() ���� ���� �� ����.
		
			2. RandTable �� ����� �� �� �������� �ִ��� ��ü�� ���鼭 Ȯ��.

			3. RandTable �� �������� ���ٸ� ��� ���� �������� RandTable �� �߰�����.
			3. �������� �ִٸ� 1������ ���ư��� �ٽ� ����.

	} while (...);

		RandTableIndex �� �ִ� ������ �ʰ� �ߴٸ� 0 ����.*/

	int count = 0;
	do {
		count = 0;
		int random = (double)rand() / (RAND_MAX)*(iMax - 1) + 1;

		for (int i = 0; i < RandTableIndex; i++) {
			
			if (RandTable[i] == random)
				count = 1;
		}

		if (count == 0) {
			RandTable[RandTableIndex++] = random;
			return random;
		}

	} while (count==1);


	if (RandTableIndex >= 1000)
		RandTableIndex = 0;
}

void Gatcha()
{
	// 1. ��ü �����۵��� ���� �� ���� ����.
	int sum = 0;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++)
		sum += g_Gatcha[i].Rate;
	

	// 2. rand() �Լ��� Ȯ���� ����
	// ���⼭ Ȯ���� 1/100 �� �ƴϸ�, 1/���պ��� ��.
	// int iRand = Ȯ�����ϱ�;

	int iRand = TableRand(sum);//(double)TableRand() / (RAND_MAX)*(sum - 1) + 1;


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