#include "textParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 파일 읽어올 버퍼
char* chpBuffer;

void main()
{
	Data data;

	bool bFileCheck;

	bFileCheck = Parser_LoadFile("Config.txt");
	if (bFileCheck == false)
	{
		printf("존재하지 않는 파일입니다.\n");
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

	printf("##파일 크기: %d##\n", iSize);

	chpBuffer = (char*)malloc(iSize);

	iFileLoad = fread(chpBuffer, iSize, 1, fp);

	return true;
}

bool SkipNoneCommand(char chpTempBuffer)
{
	// 스페이스, 탭, 엔터코드, 주석 등 처리
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

	// 단어의 시작 위치를 찾는다
	// true면 계속 스킵, false면 벗어남
	while (SkipNoneCommand(chpBuffer[*ipLength]))
	{
		// 배열을 벗어나면 리턴한다
		if (*ipLength > strlen(chpBuffer))
			return false;

		(*ipLength)++;
	}

	// 단어의 끝 위치를 찾는다
	while (1)
	{
		// 배열을 벗어나면 리턴한다
		if (*ipLength > strlen(chpBuffer))
			return false;

		// 스페이스, 탭, '"' 등을 만나면 끝 위치를 찾은 것이니 while문 종료
		else if (chpBuffer[*ipLength] == ',' ||
			chpBuffer[*ipLength] == '"' || chpBuffer[*ipLength] == 0x20 ||
			chpBuffer[*ipLength] == 0x08 || chpBuffer[*ipLength] == 0x09 ||
			chpBuffer[*ipLength] == 0x0a || chpBuffer[*ipLength] == 0x0d)
			break;

		// 값을 넣는다
		cTempWord[i] = chpBuffer[(*ipLength)];

		// 다음 값을 위해 배열의 위치를 1칸 ++
		i++;
		(*ipLength)++;

	}

	// 단어끝에 null문자를 넣어 문자열로 만든다
	cTempWord[i] = '\0';
	(*ipLength)++;

	// 문자열 복사
	memset(chppBuffer, 0, 50);
	strcpy_s(chppBuffer, sizeof(cTempWord), cTempWord);

	return true;
}

bool Parser_GetValue_Int(const char* szName, int* ipValue)
{
	char chWord[50];
	int iLength = 0;

	// 찾는 단어가 나올때까지 while
	while (GetNextWord(chWord, &iLength))
	{
		// 단어가 같은지 체크
		if (strcmp(chWord, szName) == 0)
		{
			// 같다면 바로 뒤에 = 을 찾는다
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

	// 찾는 단어가 나올때까지 while
	while (GetNextWord(chWord, &iLength))
	{
		// 단어가 같은지 체크
		if (strcmp(chWord, chppBuffer) == 0)
		{
			// 같다면 바로 뒤에 = 을 찾는다
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