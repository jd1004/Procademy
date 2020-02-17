////////////// 랜덤 테이블 가챠 //////////////
//첫번째 진짜 랜덤과 뽑기 부분은 같으나 rand() 함수를 대체할 우리만의 랜덤을 만든다.
//우리가 만드는 랜덤은 지정된 범위 안에서 중복값이 절대 나오지 않는 랜덤 함수.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct st_ITEM
{
	char	Name[30];
	int	Rate;		// 아이템이 뽑힐 비율
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

int RandTable[1000];		// 랜덤 범위를 최대 1000 개로 잡음.
static int RandTableIndex = 0;

int TableRand(int iMax)
{
	// 랜덤 뽑을때마다 뽑혀진 랜덤 값을
	// 모두 저장해야 하므로 저장 위치 배열의 인덱스를 보관 하여 둔다.

	//RandTableIndex == 0 이면 RandTable 초기화.

	if (RandTableIndex == 0)
		RandTable[1000] = { 0 };

	/*do
	{
		1. 일반 랜덤 rand() 으로 랜덤 값 구함.
		
			2. RandTable 에 저장된 값 중 같은값이 있는지 전체를 돌면서 확인.

			3. RandTable 에 같은값이 없다면 방금 뽑은 랜덤값을 RandTable 에 추가저장.
			3. 같은값이 있다면 1번으로 돌아가서 다시 뽑음.

	} while (...);

		RandTableIndex 가 최대 개수를 초과 했다면 0 으로.*/

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
	// 1. 전체 아이템들의 비율 총 합을 구함.
	int sum = 0;

	for (int i = 0; i < sizeof(g_Gatcha) / sizeof(st_ITEM); i++)
		sum += g_Gatcha[i].Rate;
	

	// 2. rand() 함수로 확률을 구함
	// 여기서 확률은 1/100 이 아니며, 1/총합비율 임.
	// int iRand = 확률구하기;

	int iRand = TableRand(sum);//(double)TableRand() / (RAND_MAX)*(sum - 1) + 1;


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