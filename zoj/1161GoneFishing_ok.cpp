#include <iostream>

#define _ASSERT(x) if(!(x)){int k=0;k/=k;}

typedef char BYTE;
typedef short int WORD;
typedef int DWORD;

const int MAXTIME=200;
const int MAXLAKE=25;

struct EXPECT
{
	DWORD Expect;
	DWORD TimeUsed;
}Expect[MAXLAKE][MAXTIME];
int InitExpect[MAXLAKE];
int Decrease[MAXLAKE];
int Path[MAXLAKE];
int LakeCount;
int TotalTime;

int Input()
{
	std::cin>>LakeCount;
	if(LakeCount==0)
		return 0;
	std::cin>>TotalTime;
	_ASSERT(LakeCount<=MAXLAKE);
	TotalTime*=12;
	_ASSERT(TotalTime<=MAXTIME)
	int i;
	for(i=0;i<LakeCount;i++)
		std::cin>>InitExpect[i];
	for(i=0;i<LakeCount;i++)
		std::cin>>Decrease[i];
	Path[0]=0;
	for(i=1;i<LakeCount;i++)
		std::cin>>Path[i];
	return 1;
}

void Calculate()
{
	int n,t;
	for(n=0;n<LakeCount;n++)
		for(t=0;t<=TotalTime;t++)
			Expect[n][t].Expect=-1;
	Expect[0][0].Expect=0;
	Expect[0][0].TimeUsed=0;
	int NextExpect=0;
	for(t=1;t<=TotalTime;t++)
	{
		int ThisExpect=InitExpect[0]-Decrease[0]*(t-1);
		if(ThisExpect>0)
			NextExpect+=ThisExpect;
		Expect[0][t].Expect=NextExpect;
		Expect[0][t].TimeUsed=t;
	}
	for(n=0;n<LakeCount-1;n++)
		for(t=TotalTime;t>=0;t--)
			if(Expect[n][t].Expect>=0)
			{
				int tt;
				int NextExpect=Expect[n][t].Expect;
				if(t+Path[n+1]<=TotalTime)
				{
					Expect[n+1][t+Path[n+1]].Expect=NextExpect;
					Expect[n+1][t+Path[n+1]].TimeUsed=Path[n+1];
				}
				for(tt=Path[n+1]+1;t+tt<=TotalTime;tt++)
				{
					int ThisExpect=InitExpect[n+1]-Decrease[n+1]*(tt-Path[n+1]-1);
					if(ThisExpect>0)
						NextExpect+=ThisExpect;
					if(NextExpect>Expect[n+1][t+tt].Expect)
					{
						Expect[n+1][t+tt].Expect=NextExpect;
						Expect[n+1][t+tt].TimeUsed=tt;
					}
				}
			}
}

void Output()
{
	int n;
	int BestLake=0;
	for(n=0;n<LakeCount;n++)
		if(Expect[n][TotalTime].Expect>Expect[BestLake][TotalTime].Expect)
			BestLake=n;
	int BestExpect=Expect[BestLake][TotalTime].Expect;
	int TimeUsed[MAXLAKE];
	for(n=0;n<LakeCount;n++)
		TimeUsed[n]=0;
	int Time=TotalTime;
	while(BestLake>=0)
	{
		TimeUsed[BestLake]=Expect[BestLake][Time].TimeUsed-Path[BestLake];
		Time-=Expect[BestLake][Time].TimeUsed;
		BestLake--;
	}
	for(n=0;n<LakeCount;n++)
	{
		if(n)
			std::cout<<", ";
		_ASSERT(TimeUsed[n]>=0);
		std::cout<<TimeUsed[n]*5;
	}
	std::cout<<std::endl;
	std::cout<<"Number of fish expected: "<<BestExpect<<std::endl;
}

int main()
{
	int Case;
	std::cin>>Case;
	for(int i=0;i<Case;i++)
	{
		if(i)
			std::cout<<std::endl;
		int Test=0;
		while(Input())
		{
			if(Test++)
				std::cout<<std::endl;
			Calculate();
			Output();
		}
	}
	return 0;
}