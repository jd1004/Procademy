#include "bubbleSort.h"
#include <stdio.h>
#include <stdlib.h>

void ArrayPrint(int Array[], int iClosePos1, int iClosePos2)
{
	for (int i = 0; i < def_ARRAY_SIZE; i++)
	{
		if (iClosePos1 == i || iClosePos2 == i)
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

	ArrayPrint(Array, iPos1, iPos2);
}

void BubbleSort(int Array[], int iSize)
{
	int iTotal, iSearch;

	//==============================================
	// ó������ ���������� ���鼭 [N] [N+1]�� ���Ͽ� ū ���� �ڷ� ������ �Ѵ�.
	//==============================================
	for (iTotal = 0; iTotal < iSize - 1; iTotal++)
	{
		for (iSearch = 0; iSearch < iSize - 1 - iTotal; iSearch++)
		{
			if (Array[iSearch] > Array[iSearch + 1])
				Swap(Array, iSearch, iSearch + 1);
		}
	}
}