#include "Command.h"
#include "dataStructure.h"
using namespace std;


int main() {
	//���ó�ʼ����������ʼ��ϵͳ
	Init();
	//ϵͳʹ����ʾ
	Welcome();
	//ʹ�����������ʹ���û����Գ�������ָ��
	while (true) {
		cout << "root@FileSystem:" << "$ ";
		commandParse();//����ָ��Ķ�ȡ���룬ѡ��
	}
	system("pause");
	return 0;
}