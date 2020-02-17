#pragma warning(disable:4996)

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main()
{
	int iMode;
	printf("1. ��ŷ\n2. ����ŷ\n");
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
	// ��ŷ���� ��� ����
	//=========================================================
	PackHeader.iType = 0x99886655;
	PackHeader.iFileNum = iElementFileNum;

	//=========================================================
	// ��ŷ ��� ���� ����
	//=========================================================
	fopen_s(&pPackingFile, szPackingFile, "w+b");
	if (pPackingFile == NULL)
	{
		printf("��ŷ���� %s�� �� �� �����ϴ�.\n", szPackingFile);
		return;
	}

	//=========================================================
	// ������Ͽ� FILE ������ �迭 ����
	//=========================================================
	pElementFile = (FILE**)malloc(sizeof(FILE*) * iElementFileNum);

	//=========================================================
	// ��������� ��� ����
	//=========================================================
	for (int i = 0; i < iElementFileNum; i++)
	{
		fopen_s(&pElementFile[i], szElementNameArray[i], "r+b");

		if (pElementFile[i] == NULL)
		{
			printf("������� %s�� �� �� �����ϴ�.\n", szElementNameArray[i]);
			fclose(pPackingFile);
			free(pElementFile);
			return;
		}
	}

	//=========================================================
	// ��ŷ���� ��� ����
	//=========================================================
	fwrite(&PackHeader, sizeof(stPACK_HEADER), 1, pPackingFile);

	//=========================================================
	// �� ���ϵ� ������ ���ؼ� �������� ����
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
	// �� ���ϵ� ������ �о ��ŷ���Ͽ� ����
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
	// ��ŷ ���� ����
	//=========================================================
	fopen_s(&pPackingFile, szFile, "r+b");
	if (pPackingFile == NULL)
	{
		printf("��ŷ���� %s�� �� �� �����ϴ�.\n", szFile);
		return;
	}

	//=========================================================
	// ��ŷ ���� ��� �б�
	//=========================================================
	int iRead = fread(&PackHeader, sizeof(stPACK_HEADER), 1, pPackingFile);
	if (iRead != 1)
	{
		printf("��ŷ���� ����� ���� �� �����ϴ�.\n");
		fclose(pPackingFile);
		return;
	}

	//=========================================================
	// ��� Ÿ�� üũ
	//=========================================================
	if (PackHeader.iType != 0x99886655)
	{
		printf("��ŷ���� ����� ��ġ���� �ʽ��ϴ�.\n");
		fclose(pPackingFile);
		return;
	}

	//=========================================================
	// ������� ������ŭ �������� �б�
	//=========================================================
	iRead = sizeof(stPACK_FILEINFO) * PackHeader.iFileNum;
	FileInfo = (stPACK_FILEINFO*)malloc(iRead);
	memset(FileInfo, 0, iRead);

	iRead = fread(FileInfo, iRead, 1, pPackingFile);
	if (iRead != 1)
	{
		printf("��ŷ���� ������ ���� �� �����ϴ�.\n");
		fclose(pPackingFile);
		free(FileInfo);
		return;
	}

	//=========================================================
	// ��������� �ִ� ������ ���ϱ�. ���� ū ���� �������� �޸� ���۸� ��� ���ؼ�
	int iMaxFile = 0;

	for (int i = 0; i < PackHeader.iFileNum; i++)
	{
		if (iMaxFile < FileInfo->iFileSize)
			iMaxFile = FileInfo[i].iFileSize;
	}

	char* pBuffer = (char*)malloc(iMaxFile);

	//=========================================================
	// ������ ���� ���� ������� ���鼭 ���� �и�
	//=========================================================
	for (int i = 0; i < PackHeader.iFileNum; i++)
	{
		printf("%s ���� | ������ : %d \n", FileInfo[i].szFileName, FileInfo[i].iFileSize);

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
	// �� ��ŷ ������ ���� �Է�
	//=========================================================
	printf("��ŷ �� ���� ���� �Է�: ");
	scanf("%d", &iFileNum);
	while (getchar() != '\n');

	//=========================================================
	// ���� ������ �ð� �����̸� �Է¹��� ���� ����
	//
	// char[128]�� FileNum��ŭ ����
	//
	// ��� 1. ����ó�� �ִ� ������ �Է¹޾� �׸�ŭ ��������
	// ��� 2. ���� �̸��� ��ũ�� ����Ʈ�� ����
	// ��� 3. �ִ�ġ�� �����Ͽ� ���� ����
	//=========================================================
	char** szNameArray = (char**)malloc(sizeof(char*) * iFileNum);

	for (int i = 0; i < iFileNum; i++)
	{
		//=========================================================
		// szNameArray[x]�� char* �����Ƿ� ���⿡ char[128]�� ������ְ� ���� �̸��� �޴´�.
		//=========================================================
		szNameArray[i] = (char*)malloc(128);
		memset(szNameArray[i], 0, 128);

		printf("%d�� ���� �̸�: ", i);
		scanf("%s", szNameArray[i]);
		printf("\n");
	}

	//=========================================================
	// ��� ���ϵ��� ��Ƽ� �������� �̸� �ޱ�
	//=========================================================
	printf("��ŷ�� ���� �̸�: ");
	scanf("%s", szPackingFile);
	while (getchar() != '\n');

	//=========================================================
	// ��ŷ
	//=========================================================
	FilePacking(szPackingFile, iFileNum, szNameArray);

	//=========================================================
	// ������ ���� �̸��� �ޱ����� �����Ҵ� �ߴ� �޸𸮵� ����
	//=========================================================
	for (int i = 0; i < iFileNum; i++)
		free(szNameArray[i]);

	free(szNameArray);
}

void ModeUnpacking()
{
	char szPackingFile[128];

	//=========================================================
	// �� ��ŷ ������ ���� �Է�
	//=========================================================
	printf("�и� �� ��ŷ ���� �̸� �Է�: ");
	scanf("%s", szPackingFile);

	//=========================================================
	// ����ŷ
	//=========================================================
	FileUnpacking(szPackingFile);
}