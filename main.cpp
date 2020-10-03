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
	printf("目标字符串数量：%d ,允许错误率： %f\n", sourceSum, errorRate);
	printf("哈希函数数量：%d, 使用数组长度：%d B,对应%d b \n", BFilter.hashNum, BFilter.memSize,BFilter.memSize<<3);
	printf("随机种子为：\n");
	for (int i = 0; i < 10; i++)
		printf("%d \n",BFilter.seed[i]);
}
//通过

int main() {
	float errorRate = 0.001;
	unsigned int sourceSum = 15000000;
	BloomFilter* filter = new BloomFilter(errorRate,sourceSum);

	FileReader* sourceFile = new FileReader();
	bool openRe = sourceFile->openFile("D:/Programming/C++/CodingExpriment1-2_BloomFilter/dict.txt","r");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return 0;
	}
	
	//写入过滤器
	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (sourceFile->getline(data))
	{
		filter->put(data);
		memset(data, 0x00, BUFFER_SIZE);
	}
	sourceFile->closeFile();
	delete sourceFile;

	
	//检测
	FileReader* targetFile = new FileReader();
	openRe = targetFile->openFile("D:/Programming/C++/CodingExpriment1-2_BloomFilter/string.txt", "r");
	if (openRe == false) {
		printf("目标文件打开错误\n");
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
			//printf("存在 %s \n",data);
			i++;
		}
		memset(data, 0x00, BUFFER_SIZE);
	}
	printf("总计查找成功共计 %d \n", i);
	delete targetFile;
	delete filter;
	delete data;
	system("pause");
	return 0;
}