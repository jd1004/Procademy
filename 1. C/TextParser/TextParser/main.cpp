#include "textParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� �о�� ����
char* chpBuffer;

void main()
{
	Data data;

	bool bFileCheck;

	bFileCheck = Parser_LoadFile("Config.txt");
	if (bFileCheck == false)
	{
		printf("�������� �ʴ� �����Դϴ�.\n");
		return;
	}

	Parser_GetValue_Int("m_iVersion", &data.m_iVersion);
	Parser_GetValue_Int("m_iServerID", &data.m_iServerID);
	Parser_GetValue_String("m_chServerBindIP", data.m_chServerBindIP);
	Parser_GetValue_Int("m_iServerBindPort", &data.m_iServerBindPort);
	Parser_GetValue_Int("m_iWorkerThread", &data.m_iWorkerThread);
	Parser_GetValue_Int("m_iMaxUser", &data.m_iMaxUser);

	PrintData(data);

	return;
}

bool Parser_LoadFile(const char* chFileName)
{
	FILE* fp;

	int iFileLoad = fopen_s(&fp, chFileName, "rt");
	if (iFileLoad != 0)
		return false;

	fseek(fp, 0, SEEK_END);
	int iSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	printf("##���� ũ��: %d##\n", iSize);

	chpBuffer = (char*)malloc(iSize);

	iFileLoad = fread(chpBuffer, iSize, 1, fp);

	return true;
}

bool SkipNoneCommand(char chpTempBuffer)
{
	// �����̽�, ��, �����ڵ�, �ּ� �� ó��
	if (chpTempBuffer == ',' || chpTempBuffer == '"' || chpTempBuffer == '/' || chpTempBuffer == 0x20 ||
		chpTempBuffer == 0x0D || chpTempBuffer == 0x7B ||
		chpTempBuffer == 0x08 || chpTempBuffer == 0x09 || chpTempBuffer == 0x0a || chpTempBuffer == 0x0d)
		return true;

	return false;
}

bool GetNextWord(char* chppBuffer, int* ipLength)
{
	int i = 0;
	char cTempWord[50];

	// �ܾ��� ���� ��ġ�� ã�´�
	// true�� ��� ��ŵ, false�� ���
	while (SkipNoneCommand(chpBuffer[*ipLength]))
	{
		// �迭�� ����� �����Ѵ�
		if (*ipLength > strlen(chpBuffer))
			return false;

		(*ipLength)++;
	}

	// �ܾ��� �� ��ġ�� ã�´�
	while (1)
	{
		// �迭�� ����� �����Ѵ�
		if (*ipLength > strlen(chpBuffer))
			return false;

		// �����̽�, ��, '"' ���� ������ �� ��ġ�� ã�� ���̴� while�� ����
		else if (chpBuffer[*ipLength] == ',' ||
			chpBuffer[*ipLength] == '"' || chpBuffer[*ipLength] == 0x20 ||
			chpBuffer[*ipLength] == 0x08 || chpBuffer[*ipLength] == 0x09 ||
			chpBuffer[*ipLength] == 0x0a || chpBuffer[*ipLength] == 0x0d)
			break;

		// ���� �ִ´�
		cTempWord[i] = chpBuffer[(*ipLength)];

		// ���� ���� ���� �迭�� ��ġ�� 1ĭ ++
		i++;
		(*ipLength)++;

	}

	// �ܾ�� null���ڸ� �־� ���ڿ��� �����
	cTempWord[i] = '\0';
	(*ipLength)++;

	// ���ڿ� ����
	memset(chppBuffer, 0, 50);
	strcpy_s(chppBuffer, sizeof(cTempWord), cTempWord);

	return true;
}

bool Parser_GetValue_Int(const char* szName, int* ipValue)
{
	char chWord[50];
	int iLength = 0;

	// ã�� �ܾ ���ö����� while
	while (GetNextWord(chWord, &iLength))
	{
		// �ܾ ������ üũ
		if (strcmp(chWord, szName) == 0)
		{
			// ���ٸ� �ٷ� �ڿ� = �� ã�´�
			if (GetNextWord(chWord, &iLength))
			{
				if (strcmp(chWord, "=") == 0)
				{
					if (GetNextWord(chWord, &iLength))
					{
						*ipValue = atoi(chWord);
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Parser_GetValue_String(const char* chppBuffer, char* value)
{
	char chWord[50];
	int iLength = 0;

	// ã�� �ܾ ���ö����� while
	while (GetNextWord(chWord, &iLength))
	{
		// �ܾ ������ üũ
		if (strcmp(chWord, chppBuffer) == 0)
		{
			// ���ٸ� �ٷ� �ڿ� = �� ã�´�
			if (GetNextWord(chWord, &iLength))
			{
				if (strcmp(chWord, "=") == 0)
				{
					if (GetNextWord(chWord, &iLength))
					{
						strcpy_s(value, sizeof(chWord), chWord);
						return true;
					}
				}
			}
		}
	}

	return false;
}

void PrintData(Data data)
{
	printf("Version: %d\n", data.m_iVersion);
	printf("ServerID: %d\n", data.m_iServerID);
	printf("ServerBindIP: %s\n", data.m_chServerBindIP);
	printf("ServerBindPort: %d\n", data.m_iServerBindPort);
	printf("WorkerThread: %d\n", data.m_iWorkerThread);
	printf("MaxUser: %d\n", data.m_iMaxUser);
}