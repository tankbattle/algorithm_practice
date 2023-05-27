#include <iostream>using namespace std;

#define _ASSERT(x) if(!(x)){ int k=0;k/=k;}

//#define DEBUG

#ifdef DEBUG
#include<fstream.h>
#define cin infile
ifstream infile("test.txt");
#endif

int PersonCount;
int StickCount;
int Stick[5000];

int BADNESS[5001];
void Input()
{
   cin>>PersonCount;
   PersonCount+=8;
   cin>>StickCount;
   for(int i=0;i<StickCount;i++)
      cin>>Stick[StickCount-1-i];
   for(int i=1;i<StickCount;i++)
      BADNESS[i]=(Stick[i]-Stick[i-1])*(Stick[i]-Stick[i-1]);
}

#define IMPOSSIBLE 1000000000

int Badness[5001][1001];
int Calculate()
{
   for(int Stick=0;Stick<StickCount;Stick++)
      if(Stick<2)
         Badness[Stick][0]=IMPOSSIBLE;
      else
         if(Badness[Stick-1][0]>BADNESS[Stick])
            Badness[Stick][0]=BADNESS[Stick];
         else
            Badness[Stick][0]=Badness[Stick-1][0];
   for(int Person=1;Person<PersonCount;Person++)
   {
      for(int Stick=0;Stick<(Person+1)*3-1;Stick++)
         Badness[Stick][Person]=IMPOSSIBLE;
      Badness[(Person+1)*3-1][Person]=Badness[Person*3][Person-1]+BADNESS[(Person+1)*3-1];
      for(int Stick=(Person+1)*3;Stick<StickCount;Stick++)
      {
         if(Badness[Stick-2][Person-1]+BADNESS[Stick]>Badness[Stick-1][Person])
            Badness[Stick][Person]=Badness[Stick-1][Person];
         else
            Badness[Stick][Person]=Badness[Stick-2][Person-1]+BADNESS[Stick];
      }
   }
   return Badness[StickCount-1][PersonCount-1];
}

int main()
{
   int TestCount;
   cin>>TestCount;
   for(int i=0;i<TestCount;i++)
   {
      Input();
      cout<<Calculate()<<endl;
   }
   return 0;
}