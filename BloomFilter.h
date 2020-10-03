#pragma once



class BloomFilter {
private:
	//ά����Ӧ�Ķ������ַ���
	char* mem; 
	//��ʱ����ַ����Ļ�����
	unsigned int* hashBuffer;

public:
	//��Ź�ϣĸ����ʹ�õ���������ӵ�����
	unsigned int* seed;
	//���������еĳߴ磬��λ�ֽ�
	unsigned int memSize;
	//��Ҫʹ�õĹ�ϣ����������
	unsigned int hashNum;

	//������Ҫ�Ķ��������еĴ�С����λ�ֽ�
	unsigned int getMemSize(unsigned int sourceNum, float errorRate);
	//������Ҫ�Ĺ�ϣ��������
	unsigned int getHashNum(unsigned int sourceNum, unsigned int memSize);

	//���캯��
	BloomFilter(float errorRate, unsigned int sourceNum);
	//���ɹ�ϣֵ
	void getHash(unsigned int* val,char* str,int len);
	//�������������϶�Ӧ��λ����Ϊ1
	bool setOne(unsigned int loc);
	//����Ӧ�Ķ�����λ�Ƿ�Ϊ1��Ϊ1����1��Ϊ0����0��������Χ����-1
	int checkOne(unsigned int loc);
	//�����ַ������ݽ���Ӧ������λ����Ϊ1
	bool put(char* str);
	//�����ַ������ݣ������Ӧ�Ĺ�ϣֵ�����ݶ����������ϵ�ֵ�жϸ��ַ����Ƿ���������ݵ���
	int get(char* str);
	//��������
	~BloomFilter();
};