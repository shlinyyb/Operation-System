#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getModel(vector<int> a);

int main()
{
	vector<int> model;
	int sizeOfModel;
	cout << "请输入数组大小:";
	cin >> sizeOfModel;
	int factorOfModel;
	cout << "请输入数组元素：";
	for (int i = 0; i < sizeOfModel; i++)
	{
		cin >> factorOfModel;
		model.push_back(factorOfModel);
	}
	sort(model.begin(), model.end());
	/*for (int i = 0; i < sizeOfModel; i++)
		cout << model.at(i) << "  ";*/
	cout << "模式是: " << model.at(getModel(model)) << endl;
	system("pause");
}

int getModel(vector<int> a)
{
	int count = 0;
	int count1 = 0;
	int place = 0;
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = i; j < a.size(); j++)
		{
			if (a.at(i) == a.at(j))
				count++;
			else
			  {
				if (count > count1)
				{
					count1 = count;
					place = i;
				}
				break;
			   }
		}
	}
	return place;
}
