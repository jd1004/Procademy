#include <stdio.h>
#include <string.h>

char Dictionary[20][2][20] = {

	{"i","��"},
	{"you","��"},
	{"he","��"},
	{"she","�׳�"},
	{ "they","�׵�" },
	{ "am","��" },
	{ "are","��(��)" },
	{ "is","��" },
	{ "her","�׳ฦ" },
	{ "him","�׸�" },

	{ "love","����Ѵ�" },
	{ "hate","�Ⱦ��Ѵ�" },
	{ "eat","�Դ�" },
	{ "play","���" },
	{ "like","�����ϴ�" },

	{ "apple","���" },
	{ "game","����" },
	{ "cat","�����" },
	{ "dog","��" },
	{ "computer", "��ǻ��" }
};

void main()
{
	while (1)
	{
		char OriginArray[100];
		char TransArray[100] = {};
		char* p = OriginArray;

		printf("���� ����: ");
		gets_s(OriginArray, 100);

		int len = 0;
		while (OriginArray[len] != '\0')
			len++;

		_strlwr_s(OriginArray);

		for (int i = 0; i <= len; i++) {

			if (OriginArray[i] == 0x20 || OriginArray[i] == NULL) {

				OriginArray[i] = NULL;

				for (int j = 0; j < 20; j++) {

					if (strcmp(Dictionary[j][0], p) == 0) {
						strcat_s(TransArray, Dictionary[j][1]);
						strcat_s(TransArray, " ");
						break;
					}
				}

				p = OriginArray + i + 1;
			}
		}

		printf("����: %s\n\n", TransArray);
	}
}
