#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define XOR 0x44

void main()
{
	char fileName[256];
	char ch[5] = { 0 };
	
	printf("��ȣȭ �ϰų� ��ȣȭ �� ���� �̸� �Է� : ");
	scanf_s("%s", fileName, sizeof(fileName));

	FILE* fp;
	fopen_s(&fp, fileName, "rb");

	for (int i = 0; i < 4; i++) {
		ch[i] = fgetc(fp);
	}

	if (memcmp(ch, "1234", 5) == 0) {
		//��ȣȭ
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp) - 4;
		fseek(fp, 4, SEEK_SET);

		char* p = (char*)malloc(size);
		fread(p, size, 1, fp);

		for (int i = 0; i < size; i++) {
			p[i] = p[i] ^ XOR;
		}

		fclose(fp);

		FILE* fp;
		fopen_s(&fp, fileName, "wb");
		fwrite(p, size, 1, fp);

		printf("�Ϸ�\n");

		fclose(fp);
		free(p);

	}
	else {
		//��ȣȭ
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char* p = (char*)malloc(size);
		fread(p, size, 1, fp);

		for (int i = 0; i < size; i++) {
			p[i] = p[i] ^ XOR;
		}

		fclose(fp);

		FILE* fp;
		fopen_s(&fp, fileName, "wb");
		fwrite("1234", 4, 1, fp);
		fwrite(p, size, 1, fp);

		printf("�Ϸ�\n");

		fclose(fp);
		free(p);
	}

}