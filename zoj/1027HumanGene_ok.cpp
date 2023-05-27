#include <iostream>

int Len[2];
char Gene[2][128];

const int Value[5][5]={ {5,-1,-2,-1,-3},
						{-1,5,-3,-2,-4},
						{-2,-3,5,-2,-2},
						{-1,-2,-2,5,-1},
						{-3,-4,-2,-1,-1000000}};

void Input()
{
	for(int i=0;i<2;i++)
	{
		std::cin>>Len[i];
		std::cin>>Gene[i];
		for(int j=0;j<Len[i];j++)
			switch(Gene[i][j])
			{
			case 'A':Gene[i][j]=0;
				break;
			case 'C':Gene[i][j]=1;
				break;
			case 'G':Gene[i][j]=2;
				break;
			case 'T':Gene[i][j]=3;
				break;
			}
	}
}

int Match[128][128];

int Calculate()
{
	int i,j;
	for(i=0;i<=Len[0];i++)
		for(j=0;j<=Len[1];j++)
		{
			if(i==0)
				if(j==0)
					Match[i][j]=0;
				else
					Match[i][j]=Match[i][j-1]+Value[Gene[1][j-1]][4];
			else
				if(j==0)
					Match[i][j]=Match[i-1][j]+Value[4][Gene[0][i-1]];
				else
				{
					Match[i][j]=Match[i-1][j-1]+Value[Gene[0][i-1]][Gene[1][j-1]];
					if(Match[i][j]<Match[i-1][j]+Value[Gene[0][i-1]][4])
						Match[i][j]=Match[i-1][j]+Value[Gene[0][i-1]][4];
					if(Match[i][j]<Match[i][j-1]+Value[4][Gene[1][j-1]])
						Match[i][j]=Match[i][j-1]+Value[4][Gene[1][j-1]];
				}
		}
	return Match[Len[0]][Len[1]];
}

int main()
{
	int Count;
	std::cin>>Count;
	for(int i=0;i<Count;i++)
	{
		Input();
		std::cout<<Calculate()<<std::endl;
	}
	return 0;
}