#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<string>
#include <sstream>
using namespace std;

const int FDF = -11;//FAT�׿�
const int FFF = -1;//�����ļ������һ��
int FAT[100] = { 0 };//��ȫ����ʼ��Ϊ0
int freeBlock = 98; //FAT ���ʣ��ռ�
int fileNumber=0;// �ļ�����

struct FILEINFO {
	char name[10];//�ļ���
	int firstBlock;//�ļ���һ��
	int length;//�ļ�����
};
FILEINFO file[10];

typedef struct cmd//ָ��ṹ
{
	string insPart[4];
}COMMAND;
COMMAND Instruction;

void Help(char *Nomean, int nomean);//��ʾ����ָ��
void write(char *filename, int T_length);//дָ��
void insert(char *filename, int insertpoint);//����ָ��
void Diretory(char *Nomean, int nomean);//��ʾ�ļ�Ŀ¼������������
void showFAT(char *Nomean, int nomean);//��ʾFATʹ����� ����������
void commandParse();//��ȡָ��
void clearcmdLine();//���������
void Exit(char *Nomean, int nomean);//�˳� ����������

typedef void(*func)(char*,int);//ͨ�õĺ����ṹ
typedef struct hand
{
	const char *instruction;//ָ��
	func handler;//��Ӧ�Ĵ�����
}HAND_TO;

//ָ���б�
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
	//��һ����ʼ�� FAT ��
	FAT[0] = FDF;
	FAT[1] = FFF;

	cout << "�û�ָ�������" << endl;
	cout << "Writeָ��: Write filename records;" << endl;
	cout << "insertָ��: Insert filename records;" << endl;
	cout << "���FATʹ�����: FAT;" << endl;
	cout << "����ļ��б�: Directory." << endl;
	while (true) {//���û���������ָ��
		cout<< "Kobe@MS-DOS:" << "$ ";
		commandParse();
	}
	
}

void commandParse() {
	string s;
	getline(cin, s);//��ȡ���������ָ��
	stringstream stream(s);
	int i = 0;
	//��������ּ���
    //���������cmd_line ��
    //�������������
	while (stream >> Instruction.insPart[i]) {
		i++;
		if (i > 2)//����ֲ�����4
			break;
	}

	bool checkCMD = true;//����������ȷָ��
	for (int i = 0; handlerlist[i].instruction != NULL; i++)
	{
		//��strcmp����ָ��ȶԣ�ѡ����Ӧָ�����
		if (strcmp(handlerlist[i].instruction, Instruction.insPart[0].c_str()) == 0)
		{
			checkCMD = false;
			handlerlist[i].handler((char *)Instruction.insPart[1].data(),atoi(Instruction.insPart[2].c_str()));
			break;
		}
	}
	if (checkCMD && Instruction.insPart[0] != "")
		cout << "����ָ��\"" << Instruction.insPart[0] << "\"δ֪\n������������ Help ��ȡ�������" << endl;

	clearcmdLine();//���ǰһ�ε�ָ��
	stream.clear();//�������
}

void Help(char *Nomean, int nomean)
{
	cout << "�û�ָ�������" << endl;
	cout << "Writeָ��: Write filename records;" << endl;
	cout << "insertָ��: Insert filename records;" << endl;
	cout << "���FATʹ�����: FAT;" << endl;
	cout << "����ļ��б�: Directory." << endl;
}

void write(char *filename, int T_length)
{
	int last;
	strcpy(file[fileNumber].name, filename);// �����ļ��������ļ������ļ������
	file[fileNumber].length = T_length;
	for (int i = 2; i<100; i++) { 
		if (FAT[i] == 0) {//Ѱ�ҿ��п�
			file[fileNumber].firstBlock = i;// �׸����п�Ϊ�ļ���ʼ��
			last = i;
			FAT[last] = FFF;//�ݶ��ļ�ֻռһ��
			break;
		}
	}
	for (int i = 1; i<T_length; i++) { //last Ϊ�ϸ���¼��λ��
		for (int j = 2; j<100; j++)
			if (FAT[j] == 0) {
				FAT[last] = j;
				last = j;
				FAT[last] = FFF;//�ظ�Ѱ����һ�����п飬ֱ�����ļ���������
				break;
			}
	}
	FAT[last] = FFF;// �ļ�ĩ��������
	freeBlock -= T_length;// �ı���п����
	fileNumber++;//�ļ���Ŀ����
}

void insert(char *tmpname, int insertpoint)
{
	int i;
	int last, temp;
	bool flag = false;
	for (i = 0; i<fileNumber; i++)// Ѱ��Ҫִ�в���������ļ������������±���� last
	{
		if (strcmp(file[i].name, tmpname) == 0)// �Ƚϲ����ļ������Ѵ����ļ����Ƿ���ͬ
		{
			last = i;//ȷ��Ҫ��������ĸ��ļ�
			flag = true;
			break;
		}
	}

	if (flag == true)  //Ҫ������ļ�����
	{
		temp = file[last].firstBlock; //��¼��ǰ�ļ�ɨ�赽��λ��
		for (i = 0; i < insertpoint - 1; i++)
		{
			temp = FAT[temp]; // ɨ��ֱ���ҵ�����λ��
		}
		for (i = 0; i < 100; i++)// Ѱ��һ�����п���뱻�滻�ļ�¼
		{
			if (FAT[i] == 0)//����
			{
				FAT[i] = FAT[temp];
				FAT[temp] = i;
				break;
			}
		}
		file[last].length++; //�ı���п�������ļ�����
		freeBlock--;//���п��Լ�
	}
	else
		cout << "���ļ��������޷�����" << endl;
}


void Diretory(char *Nomean, int nomean)
{
	cout << "              �ļ�������" << fileNumber << endl;
	cout << "              �ļ���         ��ʼ���           �ļ����� " << endl;
	//�Ա����ķ�ʽ��������ļ���Ϣ
	for (int i = 0; i<fileNumber; i++) {
		cout << "              " << file[i].name << "      " << file[i].firstBlock << "                      " << file[i].length << endl;
	}
}

void showFAT(char *Nomean, int nomean)
{
	cout << "���п�����" << freeBlock << endl;
	//�Ա����ķ�ʽ��������ļ���Ϣ
	for (int i = 0; i<100; i++) {
		cout << "��" << i<<"��"<< "  " << FAT[i] << endl;
	}
}

void clearcmdLine() {
	for (int i = 0; i < 4; i++)
		Instruction.insPart[i] = "";//��Ϊ��
}
//�˳�����
void Exit(char *Nomean, int nomean)     
{
	cout << "�ɹ��˳�!" << endl;
	exit(0);
}