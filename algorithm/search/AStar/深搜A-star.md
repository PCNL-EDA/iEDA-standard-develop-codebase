# IDA*

IDA-star为采用了迭代加深算法的 A-star*算法。由于 IDA-star改成了深度优先的方式，相对于 A-star算法，它的优势如下：

1. 不需要判重，不需要排序；
2. 空间需求减少。

基本思想与上篇相同，这里给出例题

##### UVA1343

如图  所示，有一个 “#” 形的棋盘，上面有 1,2,3 三种数字各 8 个。给定 8 种操作，分别为图中的 A∼H。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 8 的序列循环移动 1 个单位。例如下图最左边的 “#” 形棋盘执行操作A 时，会变为图中间的 “#” 形棋盘，再执行操作 C 后会变为图中最右边的 “#” 形棋盘。 ![img](https://s3.bmp.ovh/imgs/2021/12/6490f479a0e6ef8a.png)



现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 88 个格子里的数字相同

```C++
#include<bits/stdc++.h>
using namespace std;
bool flag=false;
char c[20];
int a[9]={5,4,7,6,1,0,3,2,-1};//先把A-H看成1-8,A对应F,B对应E...
//这里的a[8]=-1其实是一个是否为深搜第一层的特判 
int mp[24];
int pos[8][7]=
{
  {0,2,6,11,15,20,22},    //A
  {1,3,8,12,17,21,23},    //B
  {10,9,8,7,6,5,4},       //C
  {19,18,17,16,15,14,13}, //D
  {23,21,17,12,8,3,1},    //E
  {22,20,15,11,6,2,0},    //F
  {13,14,15,16,17,18,19}, //G
  {4,5,6,7,8,9,10}      //H
};
int center[8]={6,7,8,11,12,15,16,17};
//看英文就知道这是中间8块的编号
void change(int x)//x表示那一条(A-H)
{
    int k=mp[pos[x][0]];
    for(int i=0;i<6;i++)
    	mp[pos[x][i]]=mp[pos[x][i + 1]];
    mp[pos[x][6]]=k;
}
bool cmp(int a,int b)
{
    return a>b;
}
int luck()//乐观估计函数
{
    int cnt[3]={0,0,0};
    for(int i=0;i<8;i++)
        cnt[mp[center[i]]-1]++;
    sort(cnt,cnt+3,cmp);
    return 8-cnt[0];
}
void dfs(int dep,int lastx,int maxdep)
//dep是当前深度,lastx是上一次选的操作,maxdep是边界
{
    if(flag)return;
    if(dep>maxdep||dep+luck()>maxdep)return;
    if(luck()==0)
    {
    	flag=true;
        c[dep]='\0';
        cout<<c<<endl;
        cout<<mp[center[0]]<<endl;
        return;
    }
    for(int i=0;i<8;i++)//i枚举变那一条(A-H) 
    {
        if(i!=a[lastx])
        {
            change(i);
            c[dep]=i+'A';//存下来 
            dfs(dep+1,i,maxdep);
            change(a[i]);
        }
    }
}
int main()
{
    while(true)
    {
        for(int i=0;i<24;i++)
        {
            cin>>mp[i];
            if(i==0 && mp[i]==0) return 0;
        }
        if(!luck())
        {
            cout<<"No moves needed"<<endl;
            cout<<mp[center[0]]<<endl;
            continue;
        }
        else
        {
            flag=false;
            for(int maxdep=1;!flag;maxdep++)
            dfs(0,8,maxdep);
        }
    }
    return 0;
}
```

