#include "quickSort.h"

void main()
{
	int Array[12] = { 23,61,12,77,89,41,53,48,78,91,11,2 };

	ArrayPrint(Array, 100, 100, false);
	QuickSort(Array, 0, 12 - 1);		// 0�� �迭���� 11�� �迭���� ����
	ArrayPrint(Array, 100, 100, false);
}