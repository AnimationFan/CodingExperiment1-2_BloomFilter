#pragma once



class BloomFilter {
private:
	//维护对应的二进制字符串
	char* mem; 
	//临时存放字符串的缓冲区
	unsigned int* hashBuffer;

public:
	//存放哈希母函数使用的随机在种子的数据
	unsigned int* seed;
	//二进制序列的尺寸，单位字节
	unsigned int memSize;
	//需要使用的哈希函数的数量
	unsigned int hashNum;

	//计算需要的二进制序列的大小，单位字节
	unsigned int getMemSize(unsigned int sourceNum, float errorRate);
	//计算需要的哈希函数数量
	unsigned int getHashNum(unsigned int sourceNum, unsigned int memSize);

	//构造函数
	BloomFilter(float errorRate, unsigned int sourceNum);
	//生成哈希值
	void getHash(unsigned int* val,char* str,int len);
	//将二进制序列上对应的位设置为1
	bool setOne(unsigned int loc);
	//检查对应的二进制位是否为1，为1返回1，为0返回0，超出范围返回-1
	int checkOne(unsigned int loc);
	//根据字符串内容将对应的数据位设置为1
	bool put(char* str);
	//根据字符串内容，计算对应的哈希值，根据二进制序列上的值判断该字符串是否存在于数据当中
	int get(char* str);
	//析构函数
	~BloomFilter();
};