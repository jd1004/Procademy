#include <stdio.h>
#include <string.h>

char Dictionary[20][2][20] = {

	{"i","나"},
	{"you","너"},
	{"he","그"},
	{"she","그녀"},
	{ "they","그들" },
	{ "am","는" },
	{ "are","는(은)" },
	{ "is","는" },
	{ "her","그녀를" },
	{ "him","그를" },

	{ "love","사랑한다" },
	{ "hate","싫어한다" },
	{ "eat","먹다" },
	{ "play","놀다" },
	{ "like","좋아하다" },

	{ "apple","사과" },
	{ "game","게임" },
	{ "cat","고양이" },
	{ "dog","개" },
	{ "computer", "컴퓨터" }
};

void main()
{
	while (1)
	{
		char OriginArray[100];
		char TransArray[100] = {};
		char* p = OriginArray;

		printf("영어 문장: ");
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

		printf("번역: %s\n\n", TransArray);
	}
}
