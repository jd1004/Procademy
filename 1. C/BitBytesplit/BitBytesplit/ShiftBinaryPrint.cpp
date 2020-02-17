#include <stdio.h>
#include <math.h>
#include <Windows.h>

/*
	unsigned short (16bit) ������ �� ��Ʈ�� ��Ʈ�� �ϱ�

	 - unsigned short ���� = 0 ���� �ʱⰪ ����.
	 - Ű����� 1 ~ 16�� ��Ʈ �ڸ� �Է��� ����
	 - 1 / 0  �� ����ڷκ��� �޾Ƽ� ������ �ڸ��� ��Ʈ�� 0 �Ǵ� 1�� �ٲ���.

	 - �ٸ� ��ġ�� �Էµ� ���� �����ʹ� ������ �Ǿ�� ��
*/

int main()
{
	unsigned short num = 0;
	int input1, input2;

	while (1)
	{
		printf("��Ʈ��ġ: ");
		scanf_s("%d", &input1);

		printf("OFF/ON [0,1] : ");
		scanf_s("%d", &input2);

		int j = pow(2, input1 - 1);

		if (input2 == 0)
		{
			num = num & ~j;
		}
		else
		{
			num = num | j;
		}

		for (int i = 15; i >= 0; i--)
		{
			if (((num >> i) & 1) == 1)
			{ 
				printf("%d �� Bit : ON\n", i + 1);
			}
			else
			{
				printf("%d �� Bit : OFF\n", i + 1);
			}

		}
		puts("");
	}
	system("pause");

	return 0;
}