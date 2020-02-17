#include "quickSort.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

void ArrayPrint(int Array[], int iClosePos1, int iClosePos2, bool bLine)
{
	for (int i = 0; i < 12; i++)
	{
		// bLine이 true인 경우 Pos1 - Pos2에 밑줄만 그어준다.
		if (bLine)
		{
			if (i >= iClosePos1 && i <= iClosePos2)
				printf("^^^^");
			else
				printf("    ");
		}
		else if (iClosePos1 == i || iClosePos2 == i)
			printf("[%02d]", Array[i]);
		else
			printf(" %02d ", Array[i]);
	}
	getc(stdin);
}

void Swap(int Array[], int iPos1, int iPos2)
{
	int iTemp;
	iTemp = Array[iPos1];
	Array[iPos1] = Array[iPos2];
	Array[iPos2] = iTemp;
	ArrayPrint(Array, iPos1, iPos2, false);
}

void QuickSort(int Array[], int iLeft, int iRight)
{
	// 처음 입력 받은 좌,우 위치를 저장한다.
	int iLeftOrigin = iLeft;
	int iRightOrigin = iRight;

	// 기준점 데이터와 위치
	int iPivotData, iPivotPos;

	ArrayPrint(Array, iLeft, iRight, true);

	// 좌,우 위치 비교로 검색이 끝났는지 확인
	if (iLeft >= iRight)
		return;

	// 기준 데이터 뽑음
	iPivotData = Array[iLeft];
	iPivotPos = iLeft;

	// 기준 데이터 위치 다음부터 탐색
	iLeft++;

	// 왼쪽과 오른쪽이 만난 후 Right가 왼쪽으로 한 칸을 더 갔을 때 까지 반복
	while (iLeft <= iRight)
	{
		// 좌->우 로 기준 데이터보다 큰 값을 찾는다.
		while (iLeft < iRight && Array[iLeft] <= iPivotData)
			iLeft++;

		// 우->좌 로 기준 데이터보다 작은 값을 찾는다.
		while (iLeft <= iRight && Array[iRight] > iPivotData)
			iRight--;

		// 오른쪽이 아직 오른쪽에 있는 상태로 멈췄다면 스왑
		// 오른쪽이 왼쪽보다 작아졌다면 중단
		if (iLeft < iRight)
			Swap(Array, iLeft, iRight);
		else
			break;
	}

	// 기준 데이터를 기준으로 작은건 좌측, 큰건 우측으로 옮김
	// 그럼 마지막에 남은 Right 자리는 기준 데이터가 들어갈 중앙 자리다.
	if (iPivotPos != iRight)
		Swap(Array, iPivotPos, iRight);

	// iRight기준으로 좌측 우측을 다시 한번 퀵소트(재귀함수호출) 해준다.
	QuickSort(Array, iLeftOrigin, iRight - 1);
	QuickSort(Array, iRight + 1, iRightOrigin);
}

