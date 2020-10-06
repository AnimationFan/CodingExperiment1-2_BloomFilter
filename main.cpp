#include<iostream>
#include<stdio.h>
#include"BloomFilter.h"
#include"FileOption.h"
#include<time.h>
//test
void test_BFilterInit() {
	float errorRate = 0.0001;
	unsigned int sourceSum = 15000000;
	BloomFilter BFilter(errorRate, sourceSum);
	printf("Ŀ���ַ���������%d ,��������ʣ� %f\n", sourceSum, errorRate);
	printf("��ϣ����������%d, ʹ�����鳤�ȣ�%d B,��Ӧ%d b \n", BFilter.hashNum, BFilter.memSize,BFilter.memSize<<3);
	printf("�������Ϊ��\n");
	for (int i = 0; i < 10; i++)
		printf("%d \n",BFilter.seed[i]);
}
//ͨ��
int sourceSum = 15000000;
float errorRate[] = {0.0001,0.00001,0.000001};
char* sourceFileLoc = { "/home/wanglei/course/dict.txt" };
char* targetFileLoc = { "/home/wanglei/course/string.txt" };
char* resultFiles[] = { "/home/wanglei/course/result/bupt_18_bloom_1.txt",
						"/home/wanglei/course/result/bupt_18_bloom_2.txt" ,  
						"/home/wanglei/course/result/bupt_18_bloom_1.txt" };


int main() {
	time_t start, finish;
	start = clock();
	int count = 0;
	while (count<3)
	{

		//������������������ļ�
		BloomFilter* filter = new BloomFilter(errorRate[count], sourceSum);
		// printf("��ϣ��������Ϊ %d, ���д�СΪ %d KB\n", filter->hashNum, filter->memSize >> 10);

		FileReader* sourceFile = new FileReader();
		bool openRe = sourceFile->openFile(sourceFileLoc, "r");
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


		//�򿪴�ƥ���ַ����ļ�
		FileReader* targetFile = new FileReader();
		openRe = targetFile->openFile(targetFileLoc, "r");
		if (openRe == false) {
			printf("Ŀ���ļ��򿪴���\n");
			return 0;
		}
		//��ƥ�����ļ�׼��д��
		FileWriter* fileWriter = new FileWriter();
		openRe = fileWriter->openFile(resultFiles[count], "w");
		if (openRe == false) {
			printf("�򿪽���ļ�����\n");
			return 0;
		}
		memset(data, 0x00, BUFFER_SIZE);
		int i = 0;
		while (targetFile->getline(data))
		{
			int length = strlen(data);
			if (length == 0) continue;
			int getRe = filter->get(data);
			if (getRe == 1) {
				//printf("���� %s \n",data);
				fileWriter->putline(data);
				i++;
			}
			memset(data, 0x00, BUFFER_SIZE);
		}
		printf("Error rate:%f \t string_march:%d \n",errorRate[count], i);
		delete targetFile;
		delete filter;
		delete[] data;
		delete fileWriter;

		count++;
		finish = clock();

	}
	printf("runtime: %d\n", finish - start);
	_sleep(3000);
	return 0;
}