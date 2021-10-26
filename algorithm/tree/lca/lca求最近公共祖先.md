## **LCA 最近公共祖先**

 　在一棵没有环的树上，每个节点肯定有其父亲节点和祖先节点，而最近公共祖先，就是两个节点在这棵树上深度最大的公共的祖先节点。
 　换句话说，就是两个点在这棵树上距离最近的公共祖先节点。
 　对于一棵有权树，**假设u,v两点的最近公共祖先lca(v),若dis[u]表示根节点到u的长度， 则uv间的距离为dis=dis[u]+dis[v]-2\*dis[lca(v)]**
 有人可能会问：那他本身或者其父亲节点是否可以作为祖先节点呢？
 　　　答案是肯定的，很简单，按照人的亲戚观念来说，**你的父亲也是你的祖先**，而LCA还可以**将自己视为祖先节点**。
 　　　举个例子吧，如下图所示**４**和**５**的**最近公共祖先是２**，**５**和**３**的**最近公共祖先**是**１**，**２**和**１**的**最近公共祖先**是**１**。　

![img](https:////upload-images.jianshu.io/upload_images/4429524-37b9c1778ca272ac.png?imageMogr2/auto-orient/strip|imageView2/2/w/819/format/webp)



求LCA主要有两种方法:**离线的DFS+并查集**和**在线的RMQ算法**
 　这里简单说一说在线和离线的区别:在计算机科学中，一个在线算法是指它可以以序列化的方式一个个的处理输入，也就是说在开始时并不需要已经知道所有的输入。相对的，对于一个离线算法，在开始时就需要知道问题的所有输入数据，而且在解决一个问题后就要立即输出结果。

其中,根节点是可以随意选择的



# RMQ算法

 一：LCA和RMQ是可以相互转化的
 LCA转RMQ算法是一个在线算法：先用时间去做预处理，然后每读入一个询问，就用很短的时间去回答它，即”问一个答一个，回答时间很短“
 预备知识：LCA转为RMQ后，几乎是裸的RMQ，这里推荐ST算法求解，如果不懂ST算法，先学习一下

![img](https:////upload-images.jianshu.io/upload_images/4429524-9ce79ff73df0eb12.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/388/format/webp)



![img](https:////upload-images.jianshu.io/upload_images/4429524-e05e20dcb81ece90.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/811/format/webp)

![img](https:////upload-images.jianshu.io/upload_images/4429524-b032a1dab59c1256.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/697/format/webp)

![img](https:////upload-images.jianshu.io/upload_images/4429524-26ceb12a22b48fb3.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/758/format/webp)



![img](https:////upload-images.jianshu.io/upload_images/4429524-9508fac52b350f50.jpg?imageMogr2/auto-orient/strip|imageView2/2/w/615/format/webp)



RMQ算法求LCA的模板如下:

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500010;
const int MAXE=500010;
struct Node
{
    int to,next,val;
};
Node edge[MAXE];
int head[MAXN],cnt;
void addEdge(int u,int v,int val)
{
    edge[cnt].to=v;
    edge[cnt].val=val;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
int sequence[MAXN*2];//保存遍历的节点序列,长度为2*n-1,从下标1开始保存
int deep[MAXN*2];//和遍历序列对应的深度数组,长度为2*n-1,从下标1开始保存
int first[MAXN];//每个节点在遍历序列时第一次出现的位置
int dis[MAXN];//每个节点到树根的距离
int dp[MAXN*1][25];//Sparse_table
bool vis[MAXN];//DFS遍历的访问数组
int tot;//序列下标记录
void DFS(int u,int dep)
{
    vis[u]=1;
    sequence[++tot]=u;first[u]=tot;deep[tot]=dep;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(vis[v]==0)
        {
            dis[v]=dis[u]+edge[i].val;
            DFS(v,dep+1);
            sequence[++tot]=u;
            deep[tot]=dep;
        }
    }
}
void ST(int len)//index from 1 - len
{
    for(int i=1;i<=len;i++) dp[i][0]=i;

    for(int j=1;(1<<j)<=len;j++)//(length)=j<<1
        for(int i=1;i+(1<<j)-1<=len;i++)
        {
            int a=dp[i][j-1],b=dp[i+(1<<(j-1))][j-1];
            if(deep[a]<deep[b]) dp[i][j]=a;
            else dp[i][j]=b;
        }
}
int RMQ(int x,int y)
{
    int k=0;
    while(1<<(k+1)<=y-x+1) k++;
    int a=dp[x][k],b=dp[y-(1<<k)+1][k];
    if(deep[a]<deep[b]) return a;
    else return b;
}
int LCA(int a,int b)
{
    int x=first[a],y=first[b];
    if(x>y) swap(x,y);
    return sequence[RMQ(x,y)];
}
int main()
{
    int t,n,m,u,v,val;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        cnt=tot=0;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&val);
            addEdge(u,v,val);
            addEdge(v,u,val);
        }
        dis[1]=0;
        DFS(1,1);
        ST(tot);
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            printf("%d\n",dis[u]+dis[v]-2*dis[LCA(u,v)]);
        }
    }
}
```

