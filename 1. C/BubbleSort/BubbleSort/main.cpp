#include "bubbleSort.h"

void main()
{
	int Array[def_ARRAY_SIZE] = { 2,16,13,5,18,7,1,11,14,6,12,3,8,9,19,17,4,15,10,20 };
	BubbleSort(Array, def_ARRAY_SIZE);
	ArrayPrint(Array, 100, 100);
}