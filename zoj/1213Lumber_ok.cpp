#include <iostream>
#include <iomanip>

using namespace std;

int LumberLen;
int SawCost;
int BlockKind;
int TotalCount;
int BlockCount[12];
int BlockLen[12];

int Input()
{
	char Buf[1000];
	cin.getline(Buf,1000);
	if(!cin||Buf[0]=='\0')
		return 0;
	stringstream str;
	str<<Buf;
	str>>LumberLen>>SawCost;
	cout<<endl;
	cout<<"Board length            ="<<setw(6)<<LumberLen<<endl;
	cout<<"Saw width               ="<<setw(6)<<SawCost<<endl;
	BlockKind=0;
	TotalCount=0;
	while(1)
	{
		int Len;
		str>>Len;
		if(!str)
			break;
		TotalCount++;
		if(BlockKind==0||BlockLen[BlockKind-1]!=Len)
		{
			BlockLen[BlockKind]=Len;
			BlockCount[BlockKind]=1;
			BlockKind++;
		}
		else
			BlockCount[BlockKind-1]++;
	}
	return 1;
}

int Calculate()
{
	int MinCost=12;
	int LumberCost[12]={1};
	int CurrentCost[12]={BlockLen[0]+SawCost};
	BlockCount[0]--;
	int CurrentBlock=1;
	int BlockUsed[12]={0,-1};
	while(CurrentBlock>=1)
	{
		BlockUsed[CurrentBlock]++;
		while(BlockUsed[CurrentBlock]<BlockKind&&BlockCount[BlockUsed[CurrentBlock]]==0)
			BlockUsed[CurrentBlock]++;
		if(BlockUsed[CurrentBlock]==BlockKind)
		{
			CurrentBlock--;
			BlockCount[BlockUsed[CurrentBlock]]++;
			continue;
		}
		if(CurrentCost[CurrentBlock-1]+BlockLen[BlockUsed[CurrentBlock]]<=LumberLen)
		{
			if(BlockLen[BlockUsed[CurrentBlock]]<BlockLen[BlockUsed[CurrentBlock-1]])
				continue;
			LumberCost[CurrentBlock]=LumberCost[CurrentBlock-1];
			CurrentCost[CurrentBlock]=CurrentCost[CurrentBlock-1]+BlockLen[BlockUsed[CurrentBlock]]+SawCost;
		}
		else
		{
			LumberCost[CurrentBlock]=LumberCost[CurrentBlock-1]+1;
			CurrentCost[CurrentBlock]=BlockLen[BlockUsed[CurrentBlock]]+SawCost;
			if(LumberCost[CurrentBlock]>=MinCost)
			{
				CurrentBlock--;
				BlockCount[BlockUsed[CurrentBlock]]++;
				continue;
			}
		}
		if(CurrentBlock==TotalCount-1)
		{
			if(MinCost>LumberCost[CurrentBlock])
				MinCost=LumberCost[CurrentBlock];
		}
		else
		{
			BlockCount[BlockUsed[CurrentBlock]]--;
			CurrentBlock++;
			BlockUsed[CurrentBlock]=-1;
		}
	}
	return MinCost;
}

int main()
{
	cout<<"Problem 7 by team x"<<endl;
	while(Input())
	{
		cout<<"Number of boards needed ="<<setw(6)<<Calculate()<<endl;
	}
	cout<<"End of problem 7 by team x"<<endl;
	return 0;
}