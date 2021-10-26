> # Tarjan离线求lca
>
> 下面详细介绍一下Tarjan算法的基本思路：
>
> **1. 任选一个点为根节点，从根节点开始。**
>
> **2.遍历该点u所有子节点v，并标记这些子节点v已被访问过。**
>
> **3.若是v还有子节点，返回2，否则下一步。**
>
> **4.合并v到u上。**
>
> **5.寻找与当前点u有询问关系的点v。**
>
> **6.若是v已经被访问过了，则可以确认u和v的最近公共祖先为v被合
>  并到的父亲节点a。**
>
> 遍历的话需要用到**dfs**来遍历(我相信来看的人都懂吧...)，至于合并，最优化的方式就是利用并查集来合并两个节点。



```cpp
void dfs(int u)
{
    vis[u]=1;
    for(int i=0;i<ve[u].size();i++)//遍历子节点
    {
        int v=ve[u][i];
        dfs(ve[u][i]);//还有子节点
        ouin(u,ve[u][i]);//合并父子节点
    }
    for(int j=0;j<pp[u].size();j++)//寻找当前点u有询问关系的点
    {
        int w=pp[u][j];
        if(vis[w]==1)//如果点已经被访问，就确认父节点是谁
        {
            ans=find(w);
        }
    }
}
```



> 假设我们有一组数据 9个节点 8条边 联通情况如下：
>
> 1--2，1--3，2--4，2--5，3--6，5--7，5--8，7--9 即下图所示的树
>
> 设我们要查找最近公共祖先的点为9--8，4--6，7--5，5--3；
>
> 
>
> 
>
> 设f[]数组为并查集的父亲节点数组，初始化f[i]=i，vis[]数组为是否访问过的数组，初始为0;
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-c24fefb2fef57e10.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/819/format/webp)
>
> 下面开始模拟过程：
>
> 取1为**根节点**，**往下搜索**发现有两个儿子2和3；
>
> 先搜2，发现2有两个儿子4和5，先搜索4，发现4**没有子节点**，则寻找与其有关系的点；
>
> 发现6与4有关系，但是**vis[6]=0**，即6还没被搜过，所以**不操作**；
>
> 发现没有和4有询问关系的点了，返回此前一次搜索，**更新vis[4]=1**；
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-04243d1940968efa.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)
>
> 表示4已经被搜完，**更新f[4]=2**，继续**搜5**，发现5有两个儿子7和8;
>
> 先**搜7**，发现7有一个子节点9，**搜索9**，发现没有子节点，寻找与其>有关系的点；
>
> 发现8和9有关系，但是**vis[8]=0**,即8没被搜到过，所以不操作；
>
> 发现没有和9有询问关系的点了，返回此前一次搜索，**更新vis[9]=1**；
>
> 表示9已经被搜完，**更新f[9]=7**，发现7没有没被搜过的子节点了，寻找>与其有关系的点；
>
> 发现5和7有关系，但是**vis[5]=0**，所以**不操作**；
>
> 发现没有和7有关系的点了，返回此前一次搜索，**更新vis[7]=1**；
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-cb5de76794fe170a.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)
>
> 表示7已经被搜完，**更新f[7]=5**，继续**搜8**，发现8没有子节点，则寻找与其有关系的点；
>
> 发现9与8有关系，**此时vis[9]=1**，则他们的**最近公共祖先**为>**find(9)=5**；
>
> (find(9)的顺序为f[9]=7-->f[7]=5-->f[5]=5 return 5;)
>
> 发现没有与8有关系的点了，返回此前一次搜索，**更新vis[8]=1**；
>
> 表示8已经被搜完，**更新f[8]=5**，发现5没有没搜过的子节点了，寻找与其有关系的点；
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-66bdfb26883fc25a.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)
>
> 发现7和5有关系，**此时vis[7]=1**，所以他们的**最近公共祖先**为**find(7)=5**；
>
> (find(7)的顺序为f[7]=5-->f[5]=5 return 5;)
>
> 又发现5和3有关系，但是**vis[3]=0**，所以**不操作**，此时5的子节点全
>  部搜完了；
>
> 返回此前一次搜索，**更新vis[5]=1**，表示5已经被搜完，**更新f[5]=2**；
>
> 发现2没有未被搜完的子节点，寻找与其有关系的点；
>
> 又发现没有和2有关系的点，则此前一次搜索，**更新vis[2]=1**；
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-033d734f5b4ce8ae.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)
>
> 表示2已经被搜完，**更新f[2]=1**，继续**搜3**，发现3有一个子节点6；
>
> **搜索6**，发现6没有子节点，则寻找与6有关系的点，发现4和6有关系；
>
> **此时vis[4]=1**，所以它们的**最近公共祖先**为**find(4)=1**;
>
> (find(4)的顺序为f[4]=2-->f[2]=2-->f[1]=1 return 1;)
>
> 发现没有与6有关系的点了，返回此前一次搜索，**更新vis[6]=1**，表示6已>经被搜完了；
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-090a52d5c22d0525.png?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)
>
> **更新f[6]=3**，发现3没有没被搜过的子节点了，则寻找与3有关系的点；
>
> 发现5和3有关系，**此时vis[5]=1**，则它们的**最近公共祖先**为>**find(5)=1**；
>
> (find(5)的顺序为f[5]=2-->f[2]=1-->f[1]=1 return 1;)
>
> 发现没有和3有关系的点了，返回此前一次搜索，**更新vis[3]=1**；
>
> ![img](https:////upload-images.jianshu.io/upload_images/17045881-1cae1c4986cf1ea0.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/600/format/webp)
>
> **更新f[3]=1**，发现1没有被搜过的子节点也没有有关系的点，此时可以**退出整个dfs**了。
>
> 经过这次dfs我们得出了所有的答案，有没有觉得很神奇呢？是否对Tarjan算法有更深层次的理解了呢？



```cpp
#include<iostream>
#include<cstdio>
#include<string.h>
#include<vector>
#define MAN 10005
using namespace std;
vector<int> ve[MAN];
vector<int> pp[MAN];
int fa[MAN],vis[MAN];
int ans,n;
int find(int x)
{
    if(x==fa[x])
    {
        return x;
    }
    else
    {
        return find(fa[x]);
    }
}
void ouin(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x!=y)
    {
        fa[y]=x;
    }
}
void init( )
{
    for(int i=0;i<=n;i++)
    {
        fa[i]=i;
        ve[i].clear();
        pp[i].clear();
        vis[i]=0;
    }
}
void dfs(int u)
{
    vis[u]=1;
    for(int i=0;i<ve[u].size();i++)
    {
        int v=ve[u][i];
        dfs(ve[u][i]);
        ouin(u,ve[u][i]);
    }
    for(int j=0;j<pp[u].size();j++)
    {
        int w=pp[u][j];
        if(vis[w]==1)
        {
            //cout<<w<<endl;
            ans=find(w);
        }
    }
}
int main( )
{
    int t,x,y,a,b;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        init( );
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&x,&y);
            ve[x].push_back(y);
            vis[y]=1;
        }
        scanf("%d%d",&a,&b);
        pp[a].push_back(b);
        pp[b].push_back(a);
        for(int i=1;i<=n;i++)
        {
            if(vis[i]==0)
            {
                memset(vis,0,sizeof(vis));
                dfs(i);
                break;
            }
        }
        // for(int i=1;i<=n;i++)
        // {
        //  cout<<fa[i]<<" ";
        // }
        cout<<endl;
        printf("%d\n",ans);
    }
    return 0;
}
```

