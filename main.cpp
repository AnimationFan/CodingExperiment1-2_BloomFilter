#include<iostream>
#include<stdio.h>
#include"BloomFilter.h"
#include"FileOption.h"
#include<time.h>
//test
void test_BFilterInit() {
	float errorRate = 0.001;
	unsigned int sourceSum = 15000000;
	BloomFilter BFilter(errorRate, sourceSum);
	printf("Ŀ���ַ���������%d ,��������ʣ� %f\n", sourceSum, errorRate);
	printf("��ϣ����������%d, ʹ�����鳤�ȣ�%d B,��Ӧ%d b \n", BFilter.hashNum, BFilter.memSize,BFilter.memSize<<3);
	printf("�������Ϊ��\n");
	for (int i = 0; i < 10; i++)
		printf("%d \n",BFilter.seed[i]);
}
//ͨ��

int main() {
	float errorRate = 0.001;
	unsigned int sourceSum = 15000000;
	BloomFilter* filter = new BloomFilter(errorRate,sourceSum);

	FileReader* sourceFile = new FileReader();
	bool openRe = sourceFile->openFile("D:/Programming/C++/CodingExpriment1-2_BloomFilter/dict.txt","r");
	if (openRe == false) {
		printf("Դ�ļ��򿪴���\n");
		return 0;
	}
	
	//д�������
	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (sourceFile->getline(data))
	{
		filter->put(data);
		memset(data, 0x00, BUFFER_SIZE);
	}
	sourceFile->closeFile();
	delete sourceFile;

	
	//���
	FileReader* targetFile = new FileReader();
	openRe = targetFile->openFile("D:/Programming/C++/CodingExpriment1-2_BloomFilter/string.txt", "r");
	if (openRe == false) {
		printf("Ŀ���ļ��򿪴���\n");
		return 0;
	}
	memset(data, 0x00, BUFFER_SIZE);
	int i = 0;
	while (targetFile->getline(data))
	{
		int length = strlen(data);
		if (length == 0) continue;
		int getRe = filter->get(data);
		if ( getRe== 1) {
			//printf("���� %s \n",data);
			i++;
		}
		memset(data, 0x00, BUFFER_SIZE);
	}
	printf("�ܼƲ��ҳɹ����� %d \n", i);
	delete targetFile;
	delete filter;
	delete data;
	system("pause");
	return 0;
}