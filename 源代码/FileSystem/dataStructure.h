#pragma once

//����ĸ���ͷ�ļ�
#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

//������ʦ�������ļ�������Ӧ�Ľṹ

typedef struct mfd
{
	const string username = "root";//�û���
	int UFDLocaton;  //���û���UFD���ڵ��̺�//����
}MFD;

//�Զ����ļ����ռ��100��block
//�ļ�λ�ñ�ʾ�ļ�ʹ�õ����һ���飬��ȥ�ļ���ǰ��С����������ļ��ĵ�һ����
typedef struct ufd
{
	string fileName;//�ļ���
	int protection; // ������ʽ
	int NowLength; //�ļ���ǰ��С
	int maxLength = 100;//�ļ�����С,100����
	int fileLocation;//�ļ�����λ��
}UFD;

typedef struct uof
{
	string filename;//�ļ���
	int state; //0����,1��
	int readPoint = 1; //��ָ��
	int writePoint; //дָ��
	int nowlength;//�ļ���ǰ��С
	int fileLocation;//�ļ�����λ��
}UOF;

typedef struct block
{
	const int size = 64;//���̿��СΪ64�ֽ�
}Block;


//һЩ��̬����
static int startBlock = 10;//��ʼλ��
static int C = 0;//��¼���ļ���
static int C1 = 10;//����ʹ�����
static int fileNumber = 0;//ϵͳ�����ļ���
static string buffer;//���ڶ�д��buffer

vector<MFD> AllMFD;   //����û���Ϣ
vector<UFD> AllUFD; //�������UFD����
vector<UOF> AllUOF;//�������UOF����

