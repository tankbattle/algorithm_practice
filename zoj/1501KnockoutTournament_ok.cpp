#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

const int MAX = 128;
const int WIN = 1, LOSE = -1 , UNKNOWN = 0;
int FightResult[MAX][MAX];
int Winner[MAX];
int PersonCount;
int Power;

//Calculate how many person can really beat some one
void CalculateFightResult()
{
	int i, j;
	//Clear the matrix
	for(i = 0 ; i < PersonCount ; i ++)
		for(j = 0 ; j < PersonCount ; j ++)
			FightResult[i][j] = UNKNOWN;
	//Put the direct result in the matrix
	//Simulate the actual competition
	int PersonRemain = PersonCount; //Person count in every turn
	int Competitor[MAX];
	//Initially, there are PersonCount person in the contest
	for(i = 0 ; i < PersonRemain ; i ++)
		Competitor[i] = i;
	//Knock out
	int Contest = 0;
	for(i = 0 ; i < Power ; i ++)
	{
		for(int j = 0 ; j < PersonRemain/2 ; j ++)
		{
			assert(Winner[Contest + j]==Competitor[j*2] || Winner[Contest + j]==Competitor[j*2+1]);
#ifndef ONLINE_JUDGE
				cout<<Competitor[j * 2]<<" vs "<<Competitor[j * 2 + 1];
#endif
			if(Winner[Contest + j] == Competitor[j * 2]) //Competitor[j*2] wins
			{
				FightResult[Competitor[j * 2]][Competitor[j * 2 + 1]] = WIN;
				FightResult[Competitor[j * 2 + 1]][Competitor[j * 2]] = LOSE;
				Competitor[j] = Competitor[j*2];
#ifndef ONLINE_JUDGE
				cout<<" winner:"<<Competitor[j * 2]<<endl;
#endif
			}
			else
			{
				//Competitor[j*2+1] wins
				FightResult[Competitor[j * 2]][Competitor[j * 2 + 1]] = LOSE;
				FightResult[Competitor[j * 2 + 1]][Competitor[j * 2]] = WIN;
				Competitor[j] = Competitor[j*2+1];
#ifndef ONLINE_JUDGE
				cout<<" winner:"<<Competitor[j * 2+1]<<endl;
#endif
			}
		}
		Contest += PersonRemain/2;
		PersonRemain /= 2;
	}
	//Calculate the close packet
	bool Changed = true;
	while(Changed)
	{
		Changed = false;
		for(int i = 0 ; i < PersonCount ; i ++)
			for(int j = 0 ; j < PersonCount ; j ++)
				if(FightResult[i][j] == UNKNOWN)
					for(int k = 0 ; k < PersonCount ; k ++)
						if(FightResult[i][k] == WIN && FightResult[k][j] == WIN)
						{
							FightResult[i][j] = WIN;
							FightResult[j][i] = LOSE;
							Changed = true;
						}
	}
}

int main()
{
	bool bIsFirst = true;
	while(1)
	{
		int i;
		cin>>Power;
		if(Power == 0)
			break;
		//Output a blank line if not first test case
		if(bIsFirst)
			bIsFirst = false;
		else
			cout<<endl;
		assert(Power< 8);
		PersonCount = (int)(pow(2, Power) + 0.000001);
		for(i = 0 ; i < PersonCount-1; i ++)
		{
			cin>>Winner[i];
			Winner[i] --;
		}
		CalculateFightResult();
		//Get persons and calculate the result
		int TestCount;
		cin>>TestCount;
		for(i = 0 ; i < TestCount ; i ++)
		{
			int Person;
			cin>>Person;
			Person--;
			int Win = 0, Lose = 0; //Win is the the base line of worst, and lose is the top of best
			for(int j = 0 ; j < PersonCount ; j ++)
				if(FightResult[Person][j] == WIN)
					Win++;
				else
					if(FightResult[Person][j] == LOSE)
						Lose ++;
			cout<<"Player "<<Person+1<<" can be ranked as high as "
				<<Lose + 1<<" or as low as "<<PersonCount - Win<<"."<<endl;
		}
	}
	return 0;
}