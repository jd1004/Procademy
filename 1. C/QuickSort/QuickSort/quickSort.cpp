#include "quickSort.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

void ArrayPrint(int Array[], int iClosePos1, int iClosePos2, bool bLine)
{
	for (int i = 0; i < 12; i++)
	{
		// bLine�� true�� ��� Pos1 - Pos2�� ���ٸ� �׾��ش�.
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
	// ó�� �Է� ���� ��,�� ��ġ�� �����Ѵ�.
	int iLeftOrigin = iLeft;
	int iRightOrigin = iRight;

	// ������ �����Ϳ� ��ġ
	int iPivotData, iPivotPos;

	ArrayPrint(Array, iLeft, iRight, true);

	// ��,�� ��ġ �񱳷� �˻��� �������� Ȯ��
	if (iLeft >= iRight)
		return;

	// ���� ������ ����
	iPivotData = Array[iLeft];
	iPivotPos = iLeft;

	// ���� ������ ��ġ �������� Ž��
	iLeft++;

	// ���ʰ� �������� ���� �� Right�� �������� �� ĭ�� �� ���� �� ���� �ݺ�
	while (iLeft <= iRight)
	{
		// ��->�� �� ���� �����ͺ��� ū ���� ã�´�.
		while (iLeft < iRight && Array[iLeft] <= iPivotData)
			iLeft++;

		// ��->�� �� ���� �����ͺ��� ���� ���� ã�´�.
		while (iLeft <= iRight && Array[iRight] > iPivotData)
			iRight--;

		// �������� ���� �����ʿ� �ִ� ���·� ����ٸ� ����
		// �������� ���ʺ��� �۾����ٸ� �ߴ�
		if (iLeft < iRight)
			Swap(Array, iLeft, iRight);
		else
			break;
	}

	// ���� �����͸� �������� ������ ����, ū�� �������� �ű�
	// �׷� �������� ���� Right �ڸ��� ���� �����Ͱ� �� �߾� �ڸ���.
	if (iPivotPos != iRight)
		Swap(Array, iPivotPos, iRight);

	// iRight�������� ���� ������ �ٽ� �ѹ� ����Ʈ(����Լ�ȣ��) ���ش�.
	QuickSort(Array, iLeftOrigin, iRight - 1);
	QuickSort(Array, iRight + 1, iRightOrigin);
}

