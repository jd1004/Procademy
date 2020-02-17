////////////// 진짜 랜덤 가챠 //////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct st_ITEM
{
	char	Name[30];
	int		Rate;		// 아이템이 뽑힐 비율
};

st_ITEM g_Gatcha[] = {
	{ "칼",		20 },
	{ "방패",		20 },
	{ "신발",		20 },
	{ "물약",		20 },
	{ "초강력레어무기",	5 },
	{ "초강력방패",		5 },
	{ "초강력레어레어레어신발", 1 }
};


void Gatcha()
{
	// 1. 전체 아이템들의 비율 총 합을 구함.
	int sum = 0;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++)
		sum += g_Gatcha[i].Rate;
	

	// 2. rand() 함수로 확률을 구함
	// 여기서 확률은 1/100 이 아니며, 1/총합비율 임.
	// int iRand = 확률구하기
	int iRand = (double)rand() / (RAND_MAX)*(sum - 1) + 1;

	
	// 3. 전체 아이템 테이블을 돌면서
	// 위에서 구한 Rand 값에 해당 지점의 아이템을 찾는다.
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