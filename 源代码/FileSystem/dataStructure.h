#pragma once

//所需的各类头文件
#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

//根据老师所给的文件建立相应的结构

typedef struct mfd
{
	const string username = "root";//用户名
	int UFDLocaton;  //该用户的UFD所在的盘号//自增
}MFD;

//自定义文件最大占用100个block
//文件位置表示文件使用的最后一个块，减去文件当前大小，即可求得文件的第一个块
typedef struct ufd
{
	string fileName;//文件名
	int protection; // 保护方式
	int NowLength; //文件当前大小
	int maxLength = 100;//文件最大大小,100个块
	int fileLocation;//文件所在位置
}UFD;

typedef struct uof
{
	string filename;//文件名
	int state; //0建立,1打开
	int readPoint = 1; //读指针
	int writePoint; //写指针
	int nowlength;//文件当前大小
	int fileLocation;//文件所在位置
}UOF;

typedef struct block
{
	const int size = 64;//磁盘块大小为64字节
}Block;


//一些静态变量
static int startBlock = 10;//初始位置
static int C = 0;//记录打开文件数
static int C1 = 10;//磁盘使用情况
static int fileNumber = 0;//系统已有文件数
static string buffer;//用于读写的buffer

vector<MFD> AllMFD;   //存放用户信息
vector<UFD> AllUFD; //存放所有UFD数据
vector<UOF> AllUOF;//存放所有UOF数据

