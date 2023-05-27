#include <iostream>
#include <stdlib.h>

//#define FROMFILE
#ifdef FROMFILE
#include<fstream.h>
#define cin infile
ifstream infile("test.txt");
#endif

#define _ASSERT(x) if(!(x)) {int k=0;k/=k;}

struct SPEED
{
   int Index;
   int Speed;
};
struct WEIGHT
{
   int Weight;
   int SpeedCount;
   SPEED Speed[1000];
}Weight[1000];
int WeightCount;

int CompareWeight(const void* Weight1,const void* Weight2)
{
   WEIGHT* p1=(WEIGHT*)Weight1;
   WEIGHT* p2=(WEIGHT*)Weight2;
   if(p1->Weight<p2->Weight)
      return -1;
   if(p1->Weight>p2->Weight)
      return 1;
   _ASSERT(0);
   return 0;
}
int CompareSpeed(const void* Speed1,const void* Speed2)
{
   SPEED* p1=(SPEED*)Speed1;
   SPEED* p2=(SPEED*)Speed2;
   if(p1->Speed<p2->Speed)
      return -1;
   if(p1->Speed>p2->Speed)
      return 1;
   _ASSERT(0);
   return 0;
}

void Input()
{
   int Index=0;
   WeightCount=0;
   while(1)
   {
      int w,s;
      std::cin>>w>>s;
      if(!std::cin)
         break;
      Index++;
      int i,j;
      for(i=0;i<WeightCount;i++)
         if(Weight[i].Weight==w)
            break;
      if(i==WeightCount)
      {
         Weight[WeightCount].Weight=w;
         Weight[WeightCount].SpeedCount=0;
         WeightCount++;
      }
      for(j=0;j<Weight[i].SpeedCount;j++)
         if(Weight[i].Speed[j].Speed==s)
            break;
      if(j==Weight[i].SpeedCount)
      {
         Weight[i].Speed[Weight[i].SpeedCount].Index=Index;
         Weight[i].Speed[Weight[i].SpeedCount].Speed=s;
         Weight[i].SpeedCount++;
      }
   }
   qsort(Weight,WeightCount,sizeof(WEIGHT),&CompareWeight);
   for(int i=0;i<WeightCount;i++)
      qsort(Weight[i].Speed,Weight[i].SpeedCount,sizeof(SPEED),&CompareSpeed);
}

struct TABLE
{
   int Count;
   int NextWeight;
   int NextSpeed;
}Table[1000][1000];
int FirstWeight,FirstSpeed;

void Calculate()
{
   FirstWeight=WeightCount-1;
   FirstSpeed=0;
   int i,j;
   for(i=WeightCount-1;i>=0;i--)
      for(j=0;j<Weight[i].SpeedCount;j++)
      {
         Table[i][j].Count=1;
         Table[i][j].NextWeight=Table[i][j].NextSpeed=-1;
         int k,l;
         for(k=i+1;k<WeightCount-1;k++)
            for(l=0;l<Weight[k].SpeedCount&&Weight[k].Speed[l].Speed<Weight[i].Speed[j].Speed;l++)
            {
               if(Table[i][j].Count<Table[k][l].Count+1)
               {
                  Table[i][j].Count=Table[k][l].Count+1;
                  Table[i][j].NextWeight=k;
                  Table[i][j].NextSpeed=l;
               }
            }
         if(Table[i][j].Count>Table[FirstWeight][FirstSpeed].Count)
         {
            FirstWeight=i;
            FirstSpeed=j;
         }
      }
}

void Output()
{
/*   for(int i=0;i<WeightCount;i++)
   {
      cout<<Weight[i].Weight<<":";
      for(int j=0;j<Weight[i].SpeedCount;j++)
         cout<<Weight[i].Speed[j].Speed<<' ';
      cout<<endl;
   }*/
   std::cout<<Table[FirstWeight][FirstSpeed].Count<<std::endl;
   while(FirstWeight!=-1)
   {
      std::cout<<Weight[FirstWeight].Speed[FirstSpeed].Index<<std::endl;
      int NextWeight=Table[FirstWeight][FirstSpeed].NextWeight;
      int NextSpeed=Table[FirstWeight][FirstSpeed].NextSpeed;
      FirstWeight=NextWeight;
      FirstSpeed=NextSpeed;
   }
}

int main()
{
   Input();
   Calculate();
   Output();
#ifdef FROMFILE
   while(1);
#endif
}