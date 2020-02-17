#include "quickSort.h"

void main()
{
	int Array[12] = { 23,61,12,77,89,41,53,48,78,91,11,2 };

	ArrayPrint(Array, 100, 100, false);
	QuickSort(Array, 0, 12 - 1);		// 0번 배열부터 11번 배열까지 정렬
	ArrayPrint(Array, 100, 100, false);
}