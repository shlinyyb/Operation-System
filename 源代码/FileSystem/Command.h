#pragma once

#include "dataStructure.h"
using namespace std;

//指令结构，且一般不超过4个部分
typedef struct cmd
{
	string insPart[4];
}COMMAND;
COMMAND Instruction;

//Help函数用于指导用使用本文件系统
void Help()
{
	cout << "Help                                 显示本系统命令" << endl;
	cout << "Create   filename protection         建立文件" << endl;
	cout << "Delete   filename                    删除文件" << endl;
	cout << "Open     filename protection         打开文件" << endl;
	cout << "Close    filename                    关闭文件" << endl;
	cout << "Write    filename bytes              写文件" << endl;
	cout << "Read     filename bytes              读文件" << endl;
	cout << "ls                                   查看系统已有文件" << endl;
	cout << "Clear                                清屏" << endl;
	cout << "Exit                                 退出程序" << endl;
}


//创建文件函数
void Create() {
	//这是一个通用模块，用于判断用户是否输入指令格式错误
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || Instruction.insPart[2].length()>1 || ('3' < Instruction.insPart[2].c_str()[0] || Instruction.insPart[2].c_str()[0]< '1')) {             //判断驶入格式
		cout << "输入格式错误" << endl;
		return;
	}

	bool flag = true;//用于判断文件名是否存在
					 //遍历所有文件名，若同名，则不能创建
	for (int i = 0; i < AllUFD.size(); i++)
	{
		if (AllUFD[i].fileName == Instruction.insPart[1]) //找到与其同名文件则无法建立
		{
			cout << "文件名" << Instruction.insPart[1] << "已经存在,不能建立!" << endl;
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		//创建新的UFD，UOF结构，用于保存新建文件信息
		UFD newUFD;
		UOF newUOF;

		//将创建信息输入
		newUFD.protection = atoi(Instruction.insPart[2].c_str());
		newUFD.fileName = Instruction.insPart[1];
		newUFD.fileLocation = startBlock + fileNumber * 100;//注意文件位置
		newUFD.NowLength = 0;

		newUOF.state = 0;
		newUOF.filename = Instruction.insPart[1];
		newUOF.readPoint = 0;
		newUOF.writePoint = 0;
		newUOF.fileLocation = startBlock + fileNumber * 100;
		C1 = startBlock + fileNumber * 100 + 100;//记录磁盘使用情况

		fileNumber++;//文件数目加一

					 //存入总的UFD，UOF中，调用push_back函数
		AllUFD.push_back(newUFD);
		AllUOF.push_back(newUOF);
		cout << "新建文件" << Instruction.insPart[1] << "成功!" << endl;//返回成功信息
	}
}

//这是用于初始化创建的函数，大体与Create函数相同，内部使用
void Create2(string T_fileName, int T_protection)
{
	bool flag = true;
	//遍历所有文件名，若同名，则不能创建
	for (int i = 0; i < AllUFD.size(); i++)
	{
		if (AllUFD[i].fileName == T_fileName)//同命
		{
			cout << "文件名\"" << T_fileName << "\"已经存在,不能建立!" << endl;
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		//创建新的UFD，UOF结构，用于保存新建文件信息
		UFD newUFD;
		UOF newUOF;

		newUFD.protection = T_protection;
		newUFD.fileName = T_fileName;
		newUFD.fileLocation = startBlock + fileNumber * 100;
		newUFD.NowLength = 0;

		newUOF.state = 0;
		newUOF.filename = T_fileName;
		newUOF.readPoint = 0;
		newUOF.writePoint = 0;
		newUOF.fileLocation = startBlock + fileNumber * 100;
		C1 = startBlock + fileNumber * 100 + 100;

		fileNumber++;

		//存入总的UFD，UOF中
		AllUFD.push_back(newUFD);
		AllUOF.push_back(newUOF);
	}
}

//打开文件函数
void Open()
{
	//这是一个通用模块，用于判断用户是否输入指令格式错误
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || Instruction.insPart[2].length() > 1 || ('3' < Instruction.insPart[2].c_str()[0] || Instruction.insPart[2].c_str()[0] < '1'))
	{
		cout << "输入格式错误" << endl;
		return;
	}

	bool flag1 = false;//判断文件是否存在
	bool flag2 = false;//判断文件是否已打开

	if (C <= 3)//不能超过4
	{
		//先比对文件名
		for (int i = 0; i < AllUFD.size(); i++)
		{
			if (AllUFD[i].fileName == Instruction.insPart[1])
			{
				flag1 = true;
				//在要打开之前还需要确定文件的protection，atoi是将string转化为int
				if (AllUFD[i].protection != atoi(Instruction.insPart[2].c_str()))//判断打开权限
				{
					cout << "文件的protection为" << AllUFD[i].protection << " 无法打开！" << endl;
					cout << "protection应当相同！" << endl;
				}
				else
				{
					for (int j = 0; j < AllUOF.size(); j++)
					{
						//再确定该文件是否已被打开，方法同样
						if (AllUOF[j].filename == Instruction.insPart[1])//判断同名
						{
							if (AllUOF[i].state == 1)
							{
								flag2 = true;
								cout << "文件" << Instruction.insPart[1] << "已经打开!" << endl;
							}
							else
							{
								C++;//增加打开文件数目
								AllUOF[i].state = 1;//更改状态
								cout << "文件" << Instruction.insPart[1] << "打开成功!" << endl;
							}
						}
					}
				}
			}
		}
		if (flag1 == false)
			//返回错误信息
			cout << "文件" << Instruction.insPart[1] << "不存在!输入指令ls查看文件列表" << endl;

	}
	else
		cout << "打开文件数目不能超过4个！" << endl;
}

//将指定内容写入文件
void Read()
{
	//这是一个通用模块，用于判断用户是否输入指令格式错误
	int bytes = atoi(Instruction.insPart[2].c_str());
	bool flag = false;
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || bytes<0)
	{
		cout << "输入格式错误" << endl;
		return;
	}
	for (int i = 0; i < AllUFD.size(); i++)
	{
		//比对文件名
		if (AllUFD[i].fileName == Instruction.insPart[1])
		{
			flag = true;
			//确定是否有写的权限
			if (AllUFD[i].protection == 2)
			{
				cout << "文件" << Instruction.insPart[1] << "权限为只写，不可读入!" << endl;
				return;
			}
			for (int j = 0; j < AllUOF.size(); j++)
			{
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					//确定文件状态
					if (AllUOF[j].state == 0)//未打开
					{
						cout << "文件未打开,请先打开文件!" << endl;
						return;
					}
					else
					{
						AllUOF[i].readPoint = AllUOF[i].readPoint + bytes;//更改读指针位置
						cout << "读入成功！" << endl;
						return;
					}
				}
			}
		}
	}
	if (flag == false)
		//返回错误信息
		cout << "文件" << Instruction.insPart[1] << "不存在!输入指令ls查看文件列表" << endl;
}

//将指定内容写入文件
void Write()
{
	//这是一个通用模块，用于判断用户是否输入指令格式错误
	int bytes = atoi(Instruction.insPart[2].c_str());
	bool flag = false;
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || bytes<0)
	{
		cout << "输入格式错误" << endl;
		return;
	}
	for (int i = 0; i < AllUFD.size(); i++)
	{
		//比对文件名
		if (AllUFD[i].fileName == Instruction.insPart[1])
		{
			flag = true;
			//确定是否有写的权限
			if (AllUFD[i].protection == 1)
			{
				cout << "文件" << Instruction.insPart[1] << "权限为只读，不可写入!" << endl;
				return;
			}
			for (int j = 0; j < AllUOF.size(); j++)
			{
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					//确定文件状态
					if (AllUOF[j].state == 0)//未打开
					{
						cout << "文件未打开,请先打开文件!" << endl;
						return;
					}
					else
					{
						AllUFD[i].fileLocation = AllUFD[i].fileLocation + bytes / 64 + 1;//写入则文件位置要改变
						AllUOF[i].writePoint = AllUOF[i].writePoint + bytes;//改变写指针位置
						AllUFD[i].NowLength = AllUFD[i].NowLength + bytes;//更新文件当前大小
						cout << "写入成功！" << endl;
						return;
					}
				}
			}
		}
	}
	if (flag == false)
		//返回错误信息
		cout << "文件" << Instruction.insPart[1] << "不存在!输入指令ls查看文件列表" << endl;
}

//关闭文件函数
void Close()
{
	//这是一个通用模块，用于判断用户是否输入指令格式错误
	if (Instruction.insPart[1] == "")
	{
		cout << "输入格式错误" << endl;
		return;
	}

	bool flag1 = false;//判断文件是否存在
					   //先比对文件名
	for (int i = 0; i < AllUFD.size(); i++)
	{
		if (AllUFD[i].fileName == Instruction.insPart[1])
		{
			flag1 = true;
			for (int j = 0; j < AllUOF.size(); j++)
			{
				//再确定该文件是否已被打开，方法同样
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					if (AllUOF[i].state == 1)
					{
						AllUOF[i].state = 0;//更改状态
						C--;//以打开的文件数目减一
					}
					cout << "文件" << Instruction.insPart[1] << "已关闭!" << endl;
				}
			}
		}
	}
	if (flag1 == false)
		//返回错误信息
		cout << "文件" << Instruction.insPart[1] << "不存在!输入指令ls查看文件列表" << endl;
}

//删除函数
void Delete() {
	//这是一个通用模块，用于判断用户是否输入指令格式错误
	if (Instruction.insPart[1] == "") {
		cout << "输入格式错误" << endl;
		return;
	}
	for (int i = 0; i < AllUFD.size(); i++) {
		//首先比对文件名
		if (AllUFD[i].fileName == Instruction.insPart[1]) {
			//清除物理分区占用，将其置为空
			AllUFD.erase(AllUFD.begin() + i);//调用vector的擦除函数
			for (int j = 0; j < AllUOF.size(); j++)
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					AllUOF.erase(AllUOF.begin() + j);
					C--;//打开文件数目减一
				}
			cout << "文件" << Instruction.insPart[1] << "删除成功!" << endl;
			return;
		}
	}
	cout << "文件" << Instruction.insPart[1] << "不存在!输入指令ls查看文件列表" << endl;
}

//输出用户拥有的文件信息
void ls() {
	//以遍历的形式，输出各种信息
	cout << "fileName    " << "protection   " << "nowLength   " << "maxLength   " << "fileLocation   " << endl;
	for (int i = 0; i < AllUFD.size(); i++)
	{
		cout << AllUFD[i].fileName << setw(10);
		cout << AllUFD[i].protection << setw(15);
		cout << AllUFD[i].NowLength << setw(15);
		cout << AllUFD[i].maxLength << setw(10);
		cout << AllUFD[i].fileLocation << endl;
	}
	cout << "磁盘使用块数:" << C1 << endl;
}

//初始化函数，自行创建10个文件
void Init()
{
	for (int i = 0; i < 10; i++)
	{
		srand(time(0));
		string T_fileName = "File" + to_string(i);
		int T_protection = rand() % 3 + 1;//随机生成保护函数
		Create2(T_fileName, T_protection);//调用二类创建函数
	}
}

//清屏函数
void Clear()
{
	system("cls");
}

//退出函数
void Exit()
{
	cout << "成功退出!" << endl;
	exit(0);
}

//用户提示函数
void Welcome() {
	cout << "默认用户为root，并且自动初始化创建了10个文件,并且文件大小以字节计算，文件位置以块计算。" << endl;
	cout << "为了系统的完整性，增加了ls，Clear，Exit函数" << endl;
	cout << "Help                                 显示本系统命令" << endl;
	cout << "Create   filename protection         建立文件" << endl;
	cout << "Delete   filename                    删除文件" << endl;
	cout << "Open     filename protection         打开文件" << endl;
	cout << "Close    filename                    关闭文件" << endl;
	cout << "Write    filename bytes              写文件" << endl;
	cout << "Read     filename bytes              读文件" << endl;
	cout << "ls                                   查看系统已有文件" << endl;
	cout << "Clear                                清屏" << endl;
	cout << "Exit                                 退出程序" << endl;
}

typedef void(*func)(void);//通用的函数结构
typedef struct hand
{
	const char *instruction;//指令
	func handler;//对应的处理函数
}HAND_TO;

//指令列表
HAND_TO handlerlist[] =
{
	{ "Create", Create },
{ "Delete", Delete },
{ "Open" , Open },
{ "Close", Close },
{ "Write", Write },
{ "Read" , Read },
{ "Exit" , Exit },
{ "ls"   , ls },
{ "Clear", Clear },
{ "Help" , Help },
{ NULL   ,  NULL }
};

//清空前一次的指令
void clearcmdLine() {
	for (int i = 0; i < 4; i++)
		Instruction.insPart[i] = "";//置为空
}

//输入指令解析函数
void commandParse() {
	string s;
	getline(cin, s);//获取输入的完整指令
	stringstream stream(s);
	int i = 0;//用于命令部分计数
			  //命令解析至cmd_line 中
			  //遍历输入命令部分
	while (stream >> Instruction.insPart[i]) {
		i++;
		if (i > 3)//命令部分不大于4
			break;
	}

	bool checkCMD = true;//假设输入正确指令
	for (int i = 0; handlerlist[i].instruction != NULL; i++)
	{
		//用strcmp进行指令比对，选择相应指令操作
		if (strcmp(handlerlist[i].instruction, Instruction.insPart[0].c_str()) == 0)
		{
			checkCMD = false;
			handlerlist[i].handler();
			break;
		}
	}
	if (checkCMD && Instruction.insPart[0] != "")
		cout << "输入指令" << Instruction.insPart[0] << "未知 可以输入命令 Help 获取命令帮助" << endl;

	clearcmdLine();//清空前一次的指令
	stream.clear();//清空输入
}

