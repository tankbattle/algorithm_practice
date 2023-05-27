#include <iostream>
#include <string>
using namespace std;

double Line[10];
double Col[10];
int MatrixCount;

int Input()
{
	cin>>MatrixCount;
	if(MatrixCount==0)
		return 0;
	for(int i=0;i<MatrixCount;i++)
		cin>>Line[i]>>Col[i];
	return 1;
}

void AppendIntToString(string& String,int Int)
{
	char Digit[20];
	int HighBit;
	for(HighBit=0;Int!=0;HighBit++)
	{
		Digit[HighBit]=Int%10+'0';
		Int/=10;
	}
	for(HighBit--;HighBit>=0;HighBit--)
	{
		String+=Digit[HighBit];
	}
}

double Calculate(string& BestAnswer,int Start,int End)
{
	if(End-Start==1)
	{
		BestAnswer="A";
		AppendIntToString(BestAnswer,Start+1);
		return 0;
	}
	double MinMultCount=1e+100;;
	for(int i=1;i<End-Start;i++)
	{
		string SubAnswer1,SubAnswer2;
		double MultCount=Line[Start]*Line[Start+i]*Col[End-1];
		MultCount+=Calculate(SubAnswer1,Start,Start+i);
		MultCount+=Calculate(SubAnswer2,Start+i,End);
		if(MultCount<MinMultCount)
		{
			BestAnswer="("+SubAnswer1+" x "+SubAnswer2+")";
			MinMultCount=MultCount;
		}
	}
	return MinMultCount;
}

int main()
{
	int Test=0;
	while(Input())
	{
		cout<<"Case "<<++Test<<": ";
		string BestAnswer;
		Calculate(BestAnswer,0,MatrixCount);
		cout<<BestAnswer<<endl;
	}
	return 0;
}