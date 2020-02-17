#pragma warning(disable:4996)

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main()
{
	int iMode;
	printf("1. 패킹\n2. 언패킹\n");
	scanf("%d", &iMode);
	printf("\n");

	switch (iMode)
	{
	case 1:
		ModePacking();
		break;
	case 2:
		ModeUnpacking();
		break;
	default:
		break;
	}
}

void FilePacking(char* szPackingFile, int iElementFileNum, char** szElementNameArray)
{
	FILE* pPackingFile;
	FILE** pElementFile;

	stPACK_HEADER PackHeader;
	stPACK_FILEINFO FileInfo;

	int iMaxFile = 0;
	int iFileSize;

	//=========================================================
	// 패킹파일 헤더 셋팅
	//=========================================================
	PackHeader.iType = 0x99886655;
	PackHeader.iFileNum = iElementFileNum;

	//=========================================================
	// 패킹 대상 파일 오픈
	//=========================================================
	fopen_s(&pPackingFile, szPackingFile, "w+b");
	if (pPackingFile == NULL)
	{
		printf("패킹파일 %s를 열 수 없습니다.\n", szPackingFile);
		return;
	}

	//=========================================================
	// 요소파일용 FILE 포인터 배열 생성
	//=========================================================
	pElementFile = (FILE**)malloc(sizeof(FILE*) * iElementFileNum);

	//=========================================================
	// 요소파일을 모두 오픈
	//=========================================================
	for (int i = 0; i < iElementFileNum; i++)
	{
		fopen_s(&pElementFile[i], szElementNameArray[i], "r+b");

		if (pElementFile[i] == NULL)
		{
			printf("요소파일 %s를 열 수 없습니다.\n", szElementNameArray[i]);
			fclose(pPackingFile);
			free(pElementFile);
			return;
		}
	}

	//=========================================================
	// 패킹파일 헤더 저장
	//=========================================================
	fwrite(&PackHeader, sizeof(stPACK_HEADER), 1, pPackingFile);

	//=========================================================
	// 각 파일들 사이즈 구해서 파일정보 저장
	//=========================================================
	for (int i = 0; i < iElementFileNum; i++)
	{
		fseek(pElementFile[i], 0, SEEK_END);
		FileInfo.iFileSize = ftell(pElementFile[i]);
		strcpy_s(FileInfo.szFileName, szElementNameArray[i]);

		fwrite(&FileInfo, sizeof(FileInfo), 1, pPackingFile);

		if (iMaxFile < FileInfo.iFileSize)
			iMaxFile = FileInfo.iFileSize;
	}

	//=========================================================
	// 각 파일들 내용을 읽어서 패킹파일에 저장
	//=========================================================
	char* pBuffer = (char*)malloc(iMaxFile);

	for (int i = 0; i < iElementFileNum; i++)
	{
		fseek(pElementFile[i], 0, SEEK_END);
		iFileSize = ftell(pElementFile[i]);
		rewind(pElementFile[i]);

		fread(pBuffer, iFileSize, 1, pElementFile[i]);
		fwrite(pBuffer, iFileSize, 1, pPackingFile);
		fclose(pElementFile[i]);
	}

	fclose(pPackingFile);

	free(pBuffer);
	free(pElementFile);
}

void FileUnpacking(char* szFile)
{
	FILE* pPackingFile;
	FILE* pSplitFile;
	stPACK_HEADER PackHeader;
	stPACK_FILEINFO* FileInfo;

	//=========================================================
	// 패킹 파일 오픈
	//=========================================================
	fopen_s(&pPackingFile, szFile, "r+b");
	if (pPackingFile == NULL)
	{
		printf("패킹파일 %s을 열 수 없습니다.\n", szFile);
		return;
	}

	//=========================================================
	// 패킹 파일 헤더 읽기
	//=========================================================
	int iRead = fread(&PackHeader, sizeof(stPACK_HEADER), 1, pPackingFile);
	if (iRead != 1)
	{
		printf("패킹파일 헤더를 읽을 수 없습니다.\n");
		fclose(pPackingFile);
		return;
	}

	//=========================================================
	// 헤더 타입 체크
	//=========================================================
	if (PackHeader.iType != 0x99886655)
	{
		printf("패킹파일 헤더가 일치하지 않습니다.\n");
		fclose(pPackingFile);
		return;
	}

	//=========================================================
	// 요소파일 개수만큼 파일정보 읽기
	//=========================================================
	iRead = sizeof(stPACK_FILEINFO) * PackHeader.iFileNum;
	FileInfo = (stPACK_FILEINFO*)malloc(iRead);
	memset(FileInfo, 0, iRead);

	iRead = fread(FileInfo, iRead, 1, pPackingFile);
	if (iRead != 1)
	{
		printf("패킹파일 정보를 읽을 수 없습니다.\n");
		fclose(pPackingFile);
		free(FileInfo);
		return;
	}

	//=========================================================
	// 요소파일의 최대 사이즈 구하기. 가장 큰 파일 기준으로 메모리 버퍼를 잡기 위해서
	int iMaxFile = 0;

	for (int i = 0; i < PackHeader.iFileNum; i++)
	{
		if (iMaxFile < FileInfo->iFileSize)
			iMaxFile = FileInfo[i].iFileSize;
	}

	char* pBuffer = (char*)malloc(iMaxFile);

	//=========================================================
	// 읽혀진 파일 정보 개수대로 돌면서 파일 분리
	//=========================================================
	for (int i = 0; i < PackHeader.iFileNum; i++)
	{
		printf("%s 파일 | 사이즈 : %d \n", FileInfo[i].szFileName, FileInfo[i].iFileSize);

		fopen_s(&pSplitFile, FileInfo[i].szFileName, "wb");
		fread(pBuffer, FileInfo[i].iFileSize, 1, pPackingFile);
		fwrite(pBuffer, FileInfo[i].iFileSize, 1, pSplitFile);
		fclose(pSplitFile);
	}

	free(pBuffer);
	free(FileInfo);
	fclose(pPackingFile);
}

void ModePacking()
{
	int iFileNum;
	char szPackingFile[128] = "";

	//=========================================================
	// 총 패킹 파일의 개수 입력
	//=========================================================
	printf("패킹 할 파일 개수 입력: ");
	scanf("%d", &iFileNum);
	while (getchar() != '\n');

	//=========================================================
	// 파일 개수에 맡게 파일이름 입력받을 버퍼 생성
	//
	// char[128]을 FileNum만큼 생성
	//
	// 방법 1. 지금처럼 최대 개수를 입력받아 그만큼 동적생성
	// 방법 2. 파일 이름을 링크드 리스트로 관리
	// 방법 3. 최대치를 고정하여 정적 생성
	//=========================================================
	char** szNameArray = (char**)malloc(sizeof(char*) * iFileNum);

	for (int i = 0; i < iFileNum; i++)
	{
		//=========================================================
		// szNameArray[x]가 char* 였으므로 여기에 char[128]을 만들어주고 파일 이름을 받는다.
		//=========================================================
		szNameArray[i] = (char*)malloc(128);
		memset(szNameArray[i], 0, 128);

		printf("%d번 파일 이름: ", i);
		scanf("%s", szNameArray[i]);
		printf("\n");
	}

	//=========================================================
	// 요소 파일들을 모아서 묶음파일 이름 받기
	//=========================================================
	printf("패킹될 파일 이름: ");
	scanf("%s", szPackingFile);
	while (getchar() != '\n');

	//=========================================================
	// 패킹
	//=========================================================
	FilePacking(szPackingFile, iFileNum, szNameArray);

	//=========================================================
	// 위에서 파일 이름을 받기위해 동적할당 했던 메모리들 해제
	//=========================================================
	for (int i = 0; i < iFileNum; i++)
		free(szNameArray[i]);

	free(szNameArray);
}

void ModeUnpacking()
{
	char szPackingFile[128];

	//=========================================================
	// 총 패킹 파일의 개수 입력
	//=========================================================
	printf("분리 할 패킹 파일 이름 입력: ");
	scanf("%s", szPackingFile);

	//=========================================================
	// 언패킹
	//=========================================================
	FileUnpacking(szPackingFile);
}