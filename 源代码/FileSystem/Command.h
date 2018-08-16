#pragma once

#include "dataStructure.h"
using namespace std;

//ָ��ṹ����һ�㲻����4������
typedef struct cmd
{
	string insPart[4];
}COMMAND;
COMMAND Instruction;

//Help��������ָ����ʹ�ñ��ļ�ϵͳ
void Help()
{
	cout << "Help                                 ��ʾ��ϵͳ����" << endl;
	cout << "Create   filename protection         �����ļ�" << endl;
	cout << "Delete   filename                    ɾ���ļ�" << endl;
	cout << "Open     filename protection         ���ļ�" << endl;
	cout << "Close    filename                    �ر��ļ�" << endl;
	cout << "Write    filename bytes              д�ļ�" << endl;
	cout << "Read     filename bytes              ���ļ�" << endl;
	cout << "ls                                   �鿴ϵͳ�����ļ�" << endl;
	cout << "Clear                                ����" << endl;
	cout << "Exit                                 �˳�����" << endl;
}


//�����ļ�����
void Create() {
	//����һ��ͨ��ģ�飬�����ж��û��Ƿ�����ָ���ʽ����
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || Instruction.insPart[2].length()>1 || ('3' < Instruction.insPart[2].c_str()[0] || Instruction.insPart[2].c_str()[0]< '1')) {             //�ж�ʻ���ʽ
		cout << "�����ʽ����" << endl;
		return;
	}

	bool flag = true;//�����ж��ļ����Ƿ����
					 //���������ļ�������ͬ�������ܴ���
	for (int i = 0; i < AllUFD.size(); i++)
	{
		if (AllUFD[i].fileName == Instruction.insPart[1]) //�ҵ�����ͬ���ļ����޷�����
		{
			cout << "�ļ���" << Instruction.insPart[1] << "�Ѿ�����,���ܽ���!" << endl;
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		//�����µ�UFD��UOF�ṹ�����ڱ����½��ļ���Ϣ
		UFD newUFD;
		UOF newUOF;

		//��������Ϣ����
		newUFD.protection = atoi(Instruction.insPart[2].c_str());
		newUFD.fileName = Instruction.insPart[1];
		newUFD.fileLocation = startBlock + fileNumber * 100;//ע���ļ�λ��
		newUFD.NowLength = 0;

		newUOF.state = 0;
		newUOF.filename = Instruction.insPart[1];
		newUOF.readPoint = 0;
		newUOF.writePoint = 0;
		newUOF.fileLocation = startBlock + fileNumber * 100;
		C1 = startBlock + fileNumber * 100 + 100;//��¼����ʹ�����

		fileNumber++;//�ļ���Ŀ��һ

					 //�����ܵ�UFD��UOF�У�����push_back����
		AllUFD.push_back(newUFD);
		AllUOF.push_back(newUOF);
		cout << "�½��ļ�" << Instruction.insPart[1] << "�ɹ�!" << endl;//���سɹ���Ϣ
	}
}

//�������ڳ�ʼ�������ĺ�����������Create������ͬ���ڲ�ʹ��
void Create2(string T_fileName, int T_protection)
{
	bool flag = true;
	//���������ļ�������ͬ�������ܴ���
	for (int i = 0; i < AllUFD.size(); i++)
	{
		if (AllUFD[i].fileName == T_fileName)//ͬ��
		{
			cout << "�ļ���\"" << T_fileName << "\"�Ѿ�����,���ܽ���!" << endl;
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		//�����µ�UFD��UOF�ṹ�����ڱ����½��ļ���Ϣ
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

		//�����ܵ�UFD��UOF��
		AllUFD.push_back(newUFD);
		AllUOF.push_back(newUOF);
	}
}

//���ļ�����
void Open()
{
	//����һ��ͨ��ģ�飬�����ж��û��Ƿ�����ָ���ʽ����
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || Instruction.insPart[2].length() > 1 || ('3' < Instruction.insPart[2].c_str()[0] || Instruction.insPart[2].c_str()[0] < '1'))
	{
		cout << "�����ʽ����" << endl;
		return;
	}

	bool flag1 = false;//�ж��ļ��Ƿ����
	bool flag2 = false;//�ж��ļ��Ƿ��Ѵ�

	if (C <= 3)//���ܳ���4
	{
		//�ȱȶ��ļ���
		for (int i = 0; i < AllUFD.size(); i++)
		{
			if (AllUFD[i].fileName == Instruction.insPart[1])
			{
				flag1 = true;
				//��Ҫ��֮ǰ����Ҫȷ���ļ���protection��atoi�ǽ�stringת��Ϊint
				if (AllUFD[i].protection != atoi(Instruction.insPart[2].c_str()))//�жϴ�Ȩ��
				{
					cout << "�ļ���protectionΪ" << AllUFD[i].protection << " �޷��򿪣�" << endl;
					cout << "protectionӦ����ͬ��" << endl;
				}
				else
				{
					for (int j = 0; j < AllUOF.size(); j++)
					{
						//��ȷ�����ļ��Ƿ��ѱ��򿪣�����ͬ��
						if (AllUOF[j].filename == Instruction.insPart[1])//�ж�ͬ��
						{
							if (AllUOF[i].state == 1)
							{
								flag2 = true;
								cout << "�ļ�" << Instruction.insPart[1] << "�Ѿ���!" << endl;
							}
							else
							{
								C++;//���Ӵ��ļ���Ŀ
								AllUOF[i].state = 1;//����״̬
								cout << "�ļ�" << Instruction.insPart[1] << "�򿪳ɹ�!" << endl;
							}
						}
					}
				}
			}
		}
		if (flag1 == false)
			//���ش�����Ϣ
			cout << "�ļ�" << Instruction.insPart[1] << "������!����ָ��ls�鿴�ļ��б�" << endl;

	}
	else
		cout << "���ļ���Ŀ���ܳ���4����" << endl;
}

//��ָ������д���ļ�
void Read()
{
	//����һ��ͨ��ģ�飬�����ж��û��Ƿ�����ָ���ʽ����
	int bytes = atoi(Instruction.insPart[2].c_str());
	bool flag = false;
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || bytes<0)
	{
		cout << "�����ʽ����" << endl;
		return;
	}
	for (int i = 0; i < AllUFD.size(); i++)
	{
		//�ȶ��ļ���
		if (AllUFD[i].fileName == Instruction.insPart[1])
		{
			flag = true;
			//ȷ���Ƿ���д��Ȩ��
			if (AllUFD[i].protection == 2)
			{
				cout << "�ļ�" << Instruction.insPart[1] << "Ȩ��Ϊֻд�����ɶ���!" << endl;
				return;
			}
			for (int j = 0; j < AllUOF.size(); j++)
			{
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					//ȷ���ļ�״̬
					if (AllUOF[j].state == 0)//δ��
					{
						cout << "�ļ�δ��,���ȴ��ļ�!" << endl;
						return;
					}
					else
					{
						AllUOF[i].readPoint = AllUOF[i].readPoint + bytes;//���Ķ�ָ��λ��
						cout << "����ɹ���" << endl;
						return;
					}
				}
			}
		}
	}
	if (flag == false)
		//���ش�����Ϣ
		cout << "�ļ�" << Instruction.insPart[1] << "������!����ָ��ls�鿴�ļ��б�" << endl;
}

//��ָ������д���ļ�
void Write()
{
	//����һ��ͨ��ģ�飬�����ж��û��Ƿ�����ָ���ʽ����
	int bytes = atoi(Instruction.insPart[2].c_str());
	bool flag = false;
	if (Instruction.insPart[1] == "" || Instruction.insPart[2] == "" || bytes<0)
	{
		cout << "�����ʽ����" << endl;
		return;
	}
	for (int i = 0; i < AllUFD.size(); i++)
	{
		//�ȶ��ļ���
		if (AllUFD[i].fileName == Instruction.insPart[1])
		{
			flag = true;
			//ȷ���Ƿ���д��Ȩ��
			if (AllUFD[i].protection == 1)
			{
				cout << "�ļ�" << Instruction.insPart[1] << "Ȩ��Ϊֻ��������д��!" << endl;
				return;
			}
			for (int j = 0; j < AllUOF.size(); j++)
			{
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					//ȷ���ļ�״̬
					if (AllUOF[j].state == 0)//δ��
					{
						cout << "�ļ�δ��,���ȴ��ļ�!" << endl;
						return;
					}
					else
					{
						AllUFD[i].fileLocation = AllUFD[i].fileLocation + bytes / 64 + 1;//д�����ļ�λ��Ҫ�ı�
						AllUOF[i].writePoint = AllUOF[i].writePoint + bytes;//�ı�дָ��λ��
						AllUFD[i].NowLength = AllUFD[i].NowLength + bytes;//�����ļ���ǰ��С
						cout << "д��ɹ���" << endl;
						return;
					}
				}
			}
		}
	}
	if (flag == false)
		//���ش�����Ϣ
		cout << "�ļ�" << Instruction.insPart[1] << "������!����ָ��ls�鿴�ļ��б�" << endl;
}

//�ر��ļ�����
void Close()
{
	//����һ��ͨ��ģ�飬�����ж��û��Ƿ�����ָ���ʽ����
	if (Instruction.insPart[1] == "")
	{
		cout << "�����ʽ����" << endl;
		return;
	}

	bool flag1 = false;//�ж��ļ��Ƿ����
					   //�ȱȶ��ļ���
	for (int i = 0; i < AllUFD.size(); i++)
	{
		if (AllUFD[i].fileName == Instruction.insPart[1])
		{
			flag1 = true;
			for (int j = 0; j < AllUOF.size(); j++)
			{
				//��ȷ�����ļ��Ƿ��ѱ��򿪣�����ͬ��
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					if (AllUOF[i].state == 1)
					{
						AllUOF[i].state = 0;//����״̬
						C--;//�Դ򿪵��ļ���Ŀ��һ
					}
					cout << "�ļ�" << Instruction.insPart[1] << "�ѹر�!" << endl;
				}
			}
		}
	}
	if (flag1 == false)
		//���ش�����Ϣ
		cout << "�ļ�" << Instruction.insPart[1] << "������!����ָ��ls�鿴�ļ��б�" << endl;
}

//ɾ������
void Delete() {
	//����һ��ͨ��ģ�飬�����ж��û��Ƿ�����ָ���ʽ����
	if (Instruction.insPart[1] == "") {
		cout << "�����ʽ����" << endl;
		return;
	}
	for (int i = 0; i < AllUFD.size(); i++) {
		//���ȱȶ��ļ���
		if (AllUFD[i].fileName == Instruction.insPart[1]) {
			//����������ռ�ã�������Ϊ��
			AllUFD.erase(AllUFD.begin() + i);//����vector�Ĳ�������
			for (int j = 0; j < AllUOF.size(); j++)
				if (AllUOF[j].filename == Instruction.insPart[1])
				{
					AllUOF.erase(AllUOF.begin() + j);
					C--;//���ļ���Ŀ��һ
				}
			cout << "�ļ�" << Instruction.insPart[1] << "ɾ���ɹ�!" << endl;
			return;
		}
	}
	cout << "�ļ�" << Instruction.insPart[1] << "������!����ָ��ls�鿴�ļ��б�" << endl;
}

//����û�ӵ�е��ļ���Ϣ
void ls() {
	//�Ա�������ʽ�����������Ϣ
	cout << "fileName    " << "protection   " << "nowLength   " << "maxLength   " << "fileLocation   " << endl;
	for (int i = 0; i < AllUFD.size(); i++)
	{
		cout << AllUFD[i].fileName << setw(10);
		cout << AllUFD[i].protection << setw(15);
		cout << AllUFD[i].NowLength << setw(15);
		cout << AllUFD[i].maxLength << setw(10);
		cout << AllUFD[i].fileLocation << endl;
	}
	cout << "����ʹ�ÿ���:" << C1 << endl;
}

//��ʼ�����������д���10���ļ�
void Init()
{
	for (int i = 0; i < 10; i++)
	{
		srand(time(0));
		string T_fileName = "File" + to_string(i);
		int T_protection = rand() % 3 + 1;//������ɱ�������
		Create2(T_fileName, T_protection);//���ö��ഴ������
	}
}

//��������
void Clear()
{
	system("cls");
}

//�˳�����
void Exit()
{
	cout << "�ɹ��˳�!" << endl;
	exit(0);
}

//�û���ʾ����
void Welcome() {
	cout << "Ĭ���û�Ϊroot�������Զ���ʼ��������10���ļ�,�����ļ���С���ֽڼ��㣬�ļ�λ���Կ���㡣" << endl;
	cout << "Ϊ��ϵͳ�������ԣ�������ls��Clear��Exit����" << endl;
	cout << "Help                                 ��ʾ��ϵͳ����" << endl;
	cout << "Create   filename protection         �����ļ�" << endl;
	cout << "Delete   filename                    ɾ���ļ�" << endl;
	cout << "Open     filename protection         ���ļ�" << endl;
	cout << "Close    filename                    �ر��ļ�" << endl;
	cout << "Write    filename bytes              д�ļ�" << endl;
	cout << "Read     filename bytes              ���ļ�" << endl;
	cout << "ls                                   �鿴ϵͳ�����ļ�" << endl;
	cout << "Clear                                ����" << endl;
	cout << "Exit                                 �˳�����" << endl;
}

typedef void(*func)(void);//ͨ�õĺ����ṹ
typedef struct hand
{
	const char *instruction;//ָ��
	func handler;//��Ӧ�Ĵ�����
}HAND_TO;

//ָ���б�
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

//���ǰһ�ε�ָ��
void clearcmdLine() {
	for (int i = 0; i < 4; i++)
		Instruction.insPart[i] = "";//��Ϊ��
}

//����ָ���������
void commandParse() {
	string s;
	getline(cin, s);//��ȡ���������ָ��
	stringstream stream(s);
	int i = 0;//��������ּ���
			  //���������cmd_line ��
			  //�������������
	while (stream >> Instruction.insPart[i]) {
		i++;
		if (i > 3)//����ֲ�����4
			break;
	}

	bool checkCMD = true;//����������ȷָ��
	for (int i = 0; handlerlist[i].instruction != NULL; i++)
	{
		//��strcmp����ָ��ȶԣ�ѡ����Ӧָ�����
		if (strcmp(handlerlist[i].instruction, Instruction.insPart[0].c_str()) == 0)
		{
			checkCMD = false;
			handlerlist[i].handler();
			break;
		}
	}
	if (checkCMD && Instruction.insPart[0] != "")
		cout << "����ָ��" << Instruction.insPart[0] << "δ֪ ������������ Help ��ȡ�������" << endl;

	clearcmdLine();//���ǰһ�ε�ָ��
	stream.clear();//�������
}

