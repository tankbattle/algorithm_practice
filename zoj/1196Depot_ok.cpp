#include <iostream>

using namespace std;

int Rest[200];
int DepotCount;
int RestCount;

int Input()
{
	cin>>RestCount>>DepotCount;
	if(RestCount==0)
		return 0;
	for(int i=0;i<RestCount;i++)
		cin>>Rest[i];
	return 1;
}

int Abs(int a)
{
	if(a<0)
		return -a;
	return a;
}

int PlaceDepot()
{
	int MinCost[200][30];
	int i,j;
	for(i=0;i<RestCount;i++)
	{
		MinCost[i][0]=0;
		for(j=0;j<i;j++)
			MinCost[i][0]+=Rest[i]-Rest[j];
	}
	for(j=1;j<DepotCount;j++)
		for(i=j;i<RestCount;i++)
		{
			MinCost[i][j]=MinCost[i-1][j-1];
			for(int k=j-1;k<i-1;k++)
			{
				int Cost=MinCost[k][j-1];
				for(int l=k+1;l<i;l++)
					if(Rest[l]-Rest[k]>Rest[i]-Rest[l])
						Cost+=Rest[i]-Rest[l];
					else
						Cost+=Rest[l]-Rest[k];
				if(Cost<MinCost[i][j])
					MinCost[i][j]=Cost;
			}
		}
	int FinalMinCost=MinCost[RestCount-1][DepotCount-1];
	for(i=DepotCount-1;i<RestCount-1;i++)
	{
		int TotalCost=MinCost[i][DepotCount-1];
		for(j=i+1;j<RestCount;j++)
			TotalCost+=Rest[j]-Rest[i];
		if(TotalCost<FinalMinCost)
			FinalMinCost=TotalCost;
	}
	return FinalMinCost;
}

int main()
{
	int Count=0;
	while(Input())
	{
		Count++;
		cout<<"Chain "<<Count<<endl;
		cout<<"Total distance sum = "<<PlaceDepot()<<endl;
		cout<<endl;
	}
	return 0;
}