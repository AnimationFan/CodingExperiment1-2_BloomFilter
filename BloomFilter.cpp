#include "MurmurHash2.h"
#include"BloomFilter.h"
#include <math.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
//计算

unsigned int BloomFilter::getMemSize(unsigned int sourceNum, float errorRate) {
	int temp = ceil((double)sourceNum * 1.44 * log(1 / errorRate) / (log(2.0))) + 1;
	return (temp >> 3) + 1;
};

unsigned int BloomFilter::getHashNum(unsigned int sourceNum, unsigned int memSize) {
	return ceil(0.693 * (double)(memSize << 3) / (double)sourceNum);
}

BloomFilter::BloomFilter(float errorRate, unsigned int sourceNum) {
	//memSize以字节为单位
	this->memSize = this->getMemSize(sourceNum, errorRate);
	this->hashNum = this->getHashNum(sourceNum, this->memSize);
	this->mem = new char[this->memSize];
	this->hashBuffer = new unsigned int[this->hashNum];
	this->seed = new unsigned int[this->hashNum];
	memset(this->mem, 0x00, this->memSize);
	time_t t;
	srand((unsigned int)time(&t));
	for (int i = 0; i < this->hashNum; i++) {
		this->seed[i] = rand();
	}

}

bool BloomFilter::setOne(unsigned int loc){
	unsigned int locInt, locMant;
	locInt = loc >> 3;
	locMant = loc & 0x07;

	if (locInt >= this->memSize) 
		return false;

	char m = 0x01;
	m << locMant;
	this->mem[locInt] = this->mem[locInt] | m;
	return true;
}

int BloomFilter::checkOne(unsigned int loc) {
	unsigned int locInt, locMant;
	locInt = loc >> 3;
	locMant = loc & 0x07;

	if (locInt >= this->memSize)
		return -1;

	int m = 0x01;
	m << locMant;
	m = m & this->mem[locInt];
	
	if (m == 0)
		return 0;
	else
		return 1;
}


void BloomFilter::getHash(unsigned int* m,char* str,int len) {
	if (m == NULL) return;
	memset(m, 0x00, this->hashNum * sizeof(unsigned int));
	for (int i = 0; i < this->hashNum; i++) {
		m[i] = MurmurHash2(str, len , this->seed[i])%(this->memSize<<3);
	}
}

bool BloomFilter::put(char* str) {
	if (str == NULL)
		return false;
	int len = strlen(str);
	memset(this->hashBuffer,0x00,this->hashNum*sizeof(unsigned int));
	this->getHash(this->hashBuffer, str, len);
	for (int i = 0; i < this->hashNum; i++) {
		this->setOne(this->hashBuffer[i]);
	}
	return true;
}

//返回-1则说明出现异常问题
//返回0则说明目标不存在
//返回1则说明目标存在
int BloomFilter::get(char* str) {
	if (str == NULL)
		return -1;
	memset(this->hashBuffer, 0x00, this->hashNum * sizeof(unsigned int));
	int len = strlen(str);
	this->getHash(this->hashBuffer, str, len);
	for (int i = 0; i < this->hashNum; i++) {
		int result = this->checkOne(this->hashBuffer[i]);
		if (result == -1)
			return -1;
		if (result == 0)
			return 0;
	}
	return 1;
}

BloomFilter::~BloomFilter() {
	delete[] this->hashBuffer;
	delete[] this->seed;
	delete[] this->mem;
}