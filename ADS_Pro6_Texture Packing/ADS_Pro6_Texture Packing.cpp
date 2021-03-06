// ADS_Pro6_Texture Packing.cpp: 定义控制台应用程序的入口点。
// Describe: 像素打包问题（二维装箱问题）
// Author: Gucktti
// Date: 2018-5-26
// Version: v1.0

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void InsertBox(vector<int> v, int iBoxSize);
bool large(int&a, int&b) 
{
	return a > b;
}

struct Box_t
{
	int remainder;//
	vector<int> items;
	bool operator <(Box_t&b) {
		return this->remainder < b.remainder;
	}
};

/**
 * [初始化]
 */
bool Init() 
{
	cout << "请输入箱子大小\n";
	int iBoxSize;
	cin >> iBoxSize;
	if (iBoxSize < 1)
	{
		cout << "请输入正确的箱子大小\n";
		return false;
	}
	cout << "请输入物品数量\n";
	int iItem;
	cin >> iItem;
	if (iItem < 1)
	{
		cout << "请输入合法的物品数量";
		return false;
	}

	vector<int> v;
	int tmp;
	for (int i = 0; i < iItem; i++)
	{
		cout << "请输入第" << i + 1 << "个值" << endl;
		cin >> tmp;
		if (tmp < 1 || tmp > iBoxSize)
		{
			cout << "请输入合法的值";
			i--;
			continue;
		}
		v.push_back(tmp);
	}

	InsertBox(v, iBoxSize);
	return true;
}
void Output(vector<Box_t> v) {
	for (unsigned int i = 0; i < v.size(); i++)
	{
		cout << "第" << i + 1 << "个箱子的物品分别是\n";
		for (unsigned int j = 0; j < v[i].items.size(); j++)
		{
			cout << v[i].items[j] << "\t";
		}
		cout << endl;
	}

}

void InsertBox(vector<int> v, int iBoxSize)
{

	vector<Box_t> vtBox;
	sort(v.begin(), v.end(), large); //物品从大到小排序
	for (unsigned int k = 0; k < v.size(); k++)
	{
		int tmp = v[k];
		bool bInsert = false;
		for (unsigned int j = 0; j < vtBox.size(); j++)
		{
			if (vtBox[j].remainder > tmp)
			{
				vtBox[j].remainder -= tmp;
				bInsert = true;
				vtBox[j].items.push_back(k);
				break;
			}
		}
		if (bInsert == false)
		{
			Box_t box;
			box.items.push_back(k);
			box.remainder = iBoxSize - tmp;
			vtBox.push_back(box);
		}
		sort(vtBox.begin(), vtBox.end());//对箱子进行排序
	}

	Output(vtBox);
}

int main(int argc, char* argv[]) {
	//  vector<int> v = {1250,3000,2680,3860,560,800};
	//  InsertBox(v,6000);
	while (!Init()) {}
	system("pause");
	return 0;
}
