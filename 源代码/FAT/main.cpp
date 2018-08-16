#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<string>
#include <sstream>
using namespace std;

const int FDF = -11;//FAT首块
const int FFF = -1;//代表文件的最后一块
int FAT[100] = { 0 };//先全部初始化为0
int freeBlock = 98; //FAT 表和剩余空间
int fileNumber=0;// 文件数量

struct FILEINFO {
	char name[10];//文件名
	int firstBlock;//文件第一块
	int length;//文件长度
};
FILEINFO file[10];

typedef struct cmd//指令结构
{
	string insPart[4];
}COMMAND;
COMMAND Instruction;

void Help(char *Nomean, int nomean);//显示帮助指令
void write(char *filename, int T_length);//写指令
void insert(char *filename, int insertpoint);//插入指令
void Diretory(char *Nomean, int nomean);//显示文件目录，参数无意义
void showFAT(char *Nomean, int nomean);//显示FAT使用情况 参数无意义
void commandParse();//读取指令
void clearcmdLine();//清空命令行
void Exit(char *Nomean, int nomean);//退出 参数无意义

typedef void(*func)(char*,int);//通用的函数结构
typedef struct hand
{
	const char *instruction;//指令
	func handler;//对应的处理函数
}HAND_TO;

//指令列表
HAND_TO handlerlist[] =
{
	{ "Write", write },
    {  "Insert",insert},
    { "FAT", showFAT },
    { "Directory",Diretory },
    {"Help",Help},
    {"Exit",Exit},
     { NULL  ,  NULL }
};

int main()
{
	//进一步初始化 FAT 表
	FAT[0] = FDF;
	FAT[1] = FFF;

	cout << "用户指令帮助：" << endl;
	cout << "Write指令: Write filename records;" << endl;
	cout << "insert指令: Insert filename records;" << endl;
	cout << "输出FAT使用情况: FAT;" << endl;
	cout << "输出文件列表: Directory." << endl;
	while (true) {//让用户持续输入指令
		cout<< "Kobe@MS-DOS:" << "$ ";
		commandParse();
	}
	
}

void commandParse() {
	string s;
	getline(cin, s);//获取输入的完整指令
	stringstream stream(s);
	int i = 0;
	//用于命令部分计数
    //命令解析至cmd_line 中
    //遍历输入命令部分
	while (stream >> Instruction.insPart[i]) {
		i++;
		if (i > 2)//命令部分不大于4
			break;
	}

	bool checkCMD = true;//假设输入正确指令
	for (int i = 0; handlerlist[i].instruction != NULL; i++)
	{
		//用strcmp进行指令比对，选择相应指令操作
		if (strcmp(handlerlist[i].instruction, Instruction.insPart[0].c_str()) == 0)
		{
			checkCMD = false;
			handlerlist[i].handler((char *)Instruction.insPart[1].data(),atoi(Instruction.insPart[2].c_str()));
			break;
		}
	}
	if (checkCMD && Instruction.insPart[0] != "")
		cout << "输入指令\"" << Instruction.insPart[0] << "\"未知\n可以输入命令 Help 获取命令帮助" << endl;

	clearcmdLine();//清空前一次的指令
	stream.clear();//清空输入
}

void Help(char *Nomean, int nomean)
{
	cout << "用户指令帮助：" << endl;
	cout << "Write指令: Write filename records;" << endl;
	cout << "insert指令: Insert filename records;" << endl;
	cout << "输出FAT使用情况: FAT;" << endl;
	cout << "输出文件列表: Directory." << endl;
}

void write(char *filename, int T_length)
{
	int last;
	strcpy(file[fileNumber].name, filename);// 创建文件，复制文件名和文件块个数
	file[fileNumber].length = T_length;
	for (int i = 2; i<100; i++) { 
		if (FAT[i] == 0) {//寻找空闲块
			file[fileNumber].firstBlock = i;// 首个空闲块为文件开始块
			last = i;
			FAT[last] = FFF;//暂定文件只占一块
			break;
		}
	}
	for (int i = 1; i<T_length; i++) { //last 为上个记录的位置
		for (int j = 2; j<100; j++)
			if (FAT[j] == 0) {
				FAT[last] = j;
				last = j;
				FAT[last] = FFF;//重复寻找下一个空闲块，直到把文件保存下来
				break;
			}
	}
	FAT[last] = FFF;// 文件末存结束标记
	freeBlock -= T_length;// 改变空闲块个数
	fileNumber++;//文件数目自增
}

void insert(char *tmpname, int insertpoint)
{
	int i;
	int last, temp;
	bool flag = false;
	for (i = 0; i<fileNumber; i++)// 寻找要执行插入操作的文件，将其数组下标存入 last
	{
		if (strcmp(file[i].name, tmpname) == 0)// 比较插入文件名与已存在文件名是否相同
		{
			last = i;//确定要插入的是哪个文件
			flag = true;
			break;
		}
	}

	if (flag == true)  //要插入的文件存在
	{
		temp = file[last].firstBlock; //记录当前文件扫描到的位置
		for (i = 0; i < insertpoint - 1; i++)
		{
			temp = FAT[temp]; // 扫描直到找到插入位置
		}
		for (i = 0; i < 100; i++)// 寻找一个空闲块插入被替换的记录
		{
			if (FAT[i] == 0)//空闲
			{
				FAT[i] = FAT[temp];
				FAT[temp] = i;
				break;
			}
		}
		file[last].length++; //改变空闲块个数与文件长度
		freeBlock--;//空闲块自减
	}
	else
		cout << "该文件不存在无法插入" << endl;
}


void Diretory(char *Nomean, int nomean)
{
	cout << "              文件个数：" << fileNumber << endl;
	cout << "              文件名         起始块号           文件长度 " << endl;
	//以遍历的方式输出所有文件信息
	for (int i = 0; i<fileNumber; i++) {
		cout << "              " << file[i].name << "      " << file[i].firstBlock << "                      " << file[i].length << endl;
	}
}

void showFAT(char *Nomean, int nomean)
{
	cout << "空闲块数：" << freeBlock << endl;
	//以遍历的方式输出所有文件信息
	for (int i = 0; i<100; i++) {
		cout << "第" << i<<"块"<< "  " << FAT[i] << endl;
	}
}

void clearcmdLine() {
	for (int i = 0; i < 4; i++)
		Instruction.insPart[i] = "";//置为空
}
//退出程序
void Exit(char *Nomean, int nomean)     
{
	cout << "成功退出!" << endl;
	exit(0);
}