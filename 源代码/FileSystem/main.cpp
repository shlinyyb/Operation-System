#include "Command.h"
#include "dataStructure.h"
using namespace std;


int main() {
	//调用初始化函数，初始化系统
	Init();
	//系统使用提示
	Welcome();
	//使用永真的条件使得用户可以持续输入指令
	while (true) {
		cout << "root@FileSystem:" << "$ ";
		commandParse();//用于指令的读取翻译，选择
	}
	system("pause");
	return 0;
}