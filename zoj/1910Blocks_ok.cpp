#include <iostream>using namespace std;

const int MAXSIZE = 1000;
int MinArea[MAXSIZE+1];

//Calculate the min area each count of block need
void Init()
{
	int i;
	//The min value is at most if they are in one line
	for(i = 0 ; i <= MAXSIZE ; i ++)
		MinArea[i] = i * 4 + 2;
	//Calculate
	for(i = 1 ; i <= MAXSIZE ; i ++)
	{
		int MaxJ = MAXSIZE / i;
		for(int j = 1 ; j <= MaxJ ; j ++)
		{
			int MaxK = MaxJ / j;
			for(int k = 1 ; k <= MaxK ; k ++)
			{
				int Size = i * j * k;
				int Area = (i * j + j * k + k * i)*2;
				if(Area < MinArea[Size])
					MinArea[Size] = Area;
			}
		}
	}
	MinArea[0] = 0;
}

int main()
{
	Init();
	int Test;
	cin>>Test;
	for(int i = 0; i < Test ; i ++)
	{
		int Size;
		cin>>Size;
		cout<<MinArea[Size]<<endl;
	}
	return 0;
}