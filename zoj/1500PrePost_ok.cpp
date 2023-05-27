#include<iostream>
#include<set>
#include<string>
#include<assert.h>
#include<algorithm>
using namespace std;

int Combination(int Places, int Objects)
{
	int Result = 1;
	int i;
	for(i = Places ; i > Places - Objects ; i --)
		Result *= i;
	for(i = Objects ; i > 0 ; i --)
		Result /= i;
	return Result;
}

int CountTree(int Ary,const string& PreOrder, const string& PostOrder);

int CountForest(int Ary, const string& PreForest, const string& PostForest)
{
#ifndef ONLINE_JUDGE
	cout<<PreForest.size()<<' '<<PostForest.size()<<endl;
#endif
	assert(PreForest.size() == PostForest.size());
	int Result = 1;
	int TreeCount = 0;
	//The first char in PreForest must be somewhere in PostForest, string within this range must
	//be the preorder and post order of a tree
	int TreeBegin = 0;
	while(TreeBegin < PreForest.size())
	{
		char cRoot = PreForest[TreeBegin];
#ifndef ONLINE_JUDGE
		cout<<"Tree root :"<<cRoot<<endl;
#endif
		//Find c in PostForest
		string::const_iterator IPostRoot = find(PostForest.begin(), PostForest.end(), cRoot);
		assert(IPostRoot != PostForest.end());
		int TreeEnd = IPostRoot - PostForest.begin();
		string PreOrder, PostOrder;
		PreOrder.insert(PreOrder.begin(), PreForest.begin() + TreeBegin, PreForest.begin() + TreeEnd + 1);
		PostOrder.insert(PostOrder.begin(), PostForest.begin() + TreeBegin, PostForest.begin() + TreeEnd + 1);
#ifndef ONLINE_JUDGE
		cout<<"Trees are :"<<PreOrder <<' '<<PostOrder <<endl;
#endif
		Result *= CountTree(Ary, PreOrder, PostOrder);
		TreeCount ++;
		TreeBegin = TreeEnd + 1;
	}
	//Apply combination of trees
	Result *= Combination(Ary, TreeCount);
	return Result;
}

int CountTree(int Ary,const string& PreOrder, const string& PostOrder)
{
	//Root mismatch, return 0
	if(PreOrder[0] != PostOrder[PostOrder.size()-1])
		return 0;
	//Substract forests
	string PreForest,PostForest;
	PreForest.insert(PreForest.begin(), PreOrder.begin() + 1, PreOrder.end());
	PostForest.insert(PostForest.begin(), PostOrder.begin(), PostOrder.end() - 1);
	//All empty, regard it as 1 tree
	if(PreForest.empty() && PostForest.empty())
		return 1;
#ifndef ONLINE_JUDGE
	cout<<"Forests are :"<<PreForest<<' '<<PostForest<<endl;
#endif
	return CountForest(Ary, PreForest, PostForest);
}

int main()
{
	while(1)
	{
		int Ary;
		string PreOrder,PostOrder;
		//Input
		cin>>Ary;
		if(Ary == 0)
			break;
		cin>>PreOrder>>PostOrder;
#ifndef ONLINE_JUDGE
		cout<<PreOrder<<' '<< PostOrder <<endl;
#endif
		cout<<CountTree(Ary, PreOrder, PostOrder)<<endl;
	}
	return 0;
}