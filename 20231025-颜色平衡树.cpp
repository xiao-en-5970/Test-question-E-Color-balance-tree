#include <iostream>
#include <map>
#include <vector>

using namespace std;

//定义一个树先
//用链表链接树，用vector存放子节点的地址
typedef struct tree
{
	map<int, int>colors;//
	int color = 0;//
	vector<struct tree*> child = { nullptr };
	int child_amount = 0;
	int id;
}
Tree, * PTree;

//全局变量
int n;
int c;
int f;
static int uid = 0;
int temp = 0;
int ans = 0;
int ok = 1;
vector<PTree> address;

//创建树
void create_tree(PTree& new_tree, int& c)
{
	uid++;
	new_tree->id = uid;
	new_tree->color = c;
	address[uid] = new_tree;
	new_tree->child.resize(5000);
}

//插入树
void insert_tree(PTree& root, int& c, int& f)
{
	uid++;
	PTree new_tree = new Tree;
	new_tree->color = c;
	address[f]->child[address[f]->child_amount] = new_tree;
	address[f]->child_amount++;
	address[uid] = new_tree;
	new_tree->id = uid;
	new_tree->child.resize(5000);
}

//检查是否合要求
void check(PTree& root)
{
	int j = uid;
	int i = 0;
	while (j >= 1)
	{
		ok = 1;
		i = 0;
		while (address[j]->child[i] != nullptr)
		{
			for (map<int, int>::iterator it = address[j]->child[i]->colors.begin(); it != address[j]->child[i]->colors.end(); it++)
			{
				address[j]->colors[it->first] += it->second;
			}
			delete address[j]->child[i];
			address[j]->child[i] = nullptr;
			i++;
		}

		address[j]->colors[address[j]->color]++;
		temp = address[j]->colors.begin()->second;
		for (map<int, int>::iterator it = address[j]->colors.begin(); it != address[j]->colors.end(); it++)
		{
			if (it->second != temp)
			{
				ok = 0;
			}
		}
		if (ok)
		{
			ans++;
		}
		j--;
	}

}

int main()
{
	address.resize(10000);
	cin >> n;
	PTree root = new Tree;
	for (int i = 0; i < n; i++)
	{
		cin >> c >> f;
		if (f == 0)
		{
			create_tree(root, c);
		}
		else
		{
			insert_tree(root, c, f);
		}
	}
	check(root);
	cout << ans << endl;
}
