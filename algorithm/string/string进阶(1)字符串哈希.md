## hash入门

首先介绍一下hash？

~~事实上是一种叫做**的病毒~~

以下讲到的hash都是OI/ACM中最常用到的hash方法：进制哈希

做法：

首先设一个进制数base，并设一个模数mod

而哈希其实就是把一个数转化为一个值，这个值是base进制的，储存在哈希表中，注意一下在存入的时候取模一下即可

比如说现在有一个字符串orzc

枚举这个字符串的每一位，与base相乘得到ans，然后mod一下，就得到orzc的哈希值

但是哈希有一个很大的弊端：**哈希冲突**

什么是哈希冲突呢？

就比如说orzc的哈希值是233，而orzhjw的哈希值也是233

那么我们在查询的时候代码会认为这两个字符串是相同的，但显然这两个字符串是不同的

减少哈希冲突的方法很多

自然溢出法，双哈希之类的

看一道例题理解一下

[洛谷P3370 【模板】字符串哈希](https://www.luogu.org/problemnew/show/P3370)

事实上如果理解了刚刚讲的hash的原理的话，这道题就很水了，因为本来就是模板题

用一段hash的代码再来巩固一下刚才的知识

```c++
#define base 233
#define inf 1<<30
ull mod=inf;
//定义一个大数(最好是质数)作为模数，这里用的是1<<30
//定义一个base进制，这里是233
il ull hash(char s[]){
    ll ans=0,len=strlen(s);
    for(ll i=0;i<len;i++){
        ans=(base*ans+(ull)s[i])%mod;
    }
    return ans;
    //枚举该字符串的每一位，与base相乘，转化为base进制，加(ull)是为了防止爆栈搞出一个负数，(ull)是无符号的，但其实加了一个ull是可以不用mod的，加个mod更保险
    //然而加了mod会很玄学，莫名比不加mod慢了300多ms
}
```



最后贴一下刚刚的例题的两种解法：

解法1：单hash/自然溢出法

这里就当一种解法来说吧

因为代码差异不大

这道题的话单hash mod开大质数是可以过的，但是在大多数难一些的题目里面是会被卡掉的

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll int
#define inf 1<<30
#define mt(x,y) memset(x,y,sizeof(x))
#define il inline 
#define ull unsigned long long
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll abs(ll x){return x>0?x:-x;}
il ll swap(ll x,ll y){ll t=x;x=y;y=t;}
il void read(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
using namespace std;
#define N 10001
#define base 233
ull mod=212370440130137957ll;
ll f[N],n;
char a[N];
//ull hash(char s[]){ ll ans=0,len=strlen(s); for(ll i=0;i<len;i++){ ans=((base*ans+(ull)s[i])+mod)%mod; } return ans; }
//这个是单hash+大质数mod，也是可以过的，但是会比较慢

ull hash(char s[]){//自然溢出
    ull ans=0,len=strlen(s);
    for(ll i=0;i<len;i++){
        ans=base*ans+(ull)s[i];
        //这里不使用mod让它自然溢出，定义为ull的数在超过2^32的时候会自然溢出
        //如果把这个换成上面的hash就会400ms+
        //所以说自然溢出大法好
    }
    return ans;
}
int main(){
    read(n);
    for(ll i=1;i<=n;i++){
        scanf("%s",a);
        f[i]=hash(a);
    }
    sort(f+1,f+n+1);ll ans=1;
    for(ll i=1;i<n;i++){
        if(f[i]!=f[i+1])ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```

解法2：双hash

其实就是用两个不同的mod来算hash，哈希冲突的概率是降低了很多，不过常数大，容易被卡，这道题要700ms+

本人还是更推荐自然溢出法



```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll int
#define inf 1<<30
#define mt(x,y) memset(x,y,sizeof(x))
#define il inline 
#define ull unsigned long long
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll abs(ll x){return x>0?x:-x;}
il ll swap(ll x,ll y){ll t=x;x=y;y=t;}
il void read(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
using namespace std;
#define N 10001
#define base 233
ull mod1=212370440130137957ll;
ull mod2=inf;
ll n;
char a[N];
struct node{ll x,y;}f[N];
il ull hash1(char s[]){
    ll ans=0,len=strlen(s);
    for(ll i=0;i<len;i++){
        ans=(base*ans+(ull)s[i])%mod1;
    }
    return ans;
}
il ull hash2(char s[]){
    ll ans=0,len=strlen(s);
    for(ll i=0;i<len;i++){
        ans=(base*ans+(ull)s[i])%mod2;
    }
    return ans;
}
il bool cmp1(node a,node b){return a.x<b.x;}
il bool cmp2(node a,node b){return a.y<b.y;}
int main(){
    read(n);
    for(ll i=1;i<=n;i++){
        scanf("%s",a);
        f[i].x=hash1(a);
        f[i].y=hash2(a);
    }
    sort(f+1,f+n+1,cmp1);sort(f+1,f+n+1,cmp2);
    ll ans=1;
    for(ll i=1;i<n;i++){
        if(f[i].x!=f[i+1].x||f[i].y!=f[i+1].y)ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```



## hash进阶：使用字符串hash乱搞的姿势

## 查询子串hash值

必备的入门操作，因为OI中用到的hash一般都是**进制哈希**，因为它有一些极其方便的性质，比如说，是具有和前缀和差不多的性质的。

假设一个字符串的前缀hash值记为h[i]h[i]h[i]，我们hash时使用的进制数为basebasebase，那么显然h[i]=h[i−1]∗base+s[i]h[i]=h[i-1]*base+s[i]h[i]=h[i−1]∗base+s[i]

记p[i]p[i]p[i]表示basebasebase的iii次方，那么我们可以通过这种方式O(1)O(1)O(1)得到一个子串的hash值（设这个子串为s[l]...s[r])



```c++
typedef unsigned long long ull;
ull get_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}
```

**可是为什么呢？**

我们知道，进行进制哈希的过程本质上就是把原先得到的哈希值在basebasebase进制上强行左移一位，然后放进去当前的这个字符。

现在的目的是，取出lll到rrr这段子串的hash值，也就是说，h[l−1]h[l-1]h[l−1]这一段是没有用的，我们把在h[r]h[r]h[r]这一位上，h[l−1]h[l-1]h[l−1]这堆字符串的hash值做的左移运算全部还原给h[l−1]h[l-1]h[l−1]，就可以知道h[l−1]h[l-1]h[l−1]在h[r]h[r]h[r]中的hash值，那么减去即可。（简单的容斥思想）

这是基本操作，现在来看一个这个的拓展问题。

### 题意

现在有一个字符串s，每次询问它的一个子串删除其中一个字符后的hash值（删除的字符时给定的）

要求必须O回答询问

### Sol

删除操作？那不能像上面那样子简单粗暴的来搞了，但是其实本质上是一样的。

假设我们现在询问的区间为[l,r]，删除的字符为x（指位置，不是字符）

类比上面的做法，我们可以先O(1)得到区间[l,x−1]和区间[x+1,r]的hash值，那么现在要做的事情就是把这两段拼起来了，由于我们使用的是进制hash，所以其实很简单，强行将前面的区间强行左移r−x位就好。

代码实现也很简单



```C++
typedef unsigned long long ull;
ull get_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}
ull get_s(int l, int r, int x) {
    return get_hash(l, x - 1) * p[r - x] + get_hash(x + 1, r);
}
```

这题的原题是[LOJ#2823. 「BalticOI 2014 Day 1」三个朋友](https://loj.ac/problem/2823) ，需要分类讨论一下，不过知道上面这个也就不难了

## 用hash求[最长回文子串]()/回文子串数

马拉车！可以O(n)！

可是马拉车代码难度较高

这时候就得靠hash来水

我们知道，回文子串是具有单调性的

```
如果字符串s[l...r]为回文子串，那么s[x...y](l<x,y<r)也一定是回文子串
```

单调性！我们是不是可以二分？

我们暂时只讨论长度为奇数的回文子串。（事实上，长度为偶数的回文子串与奇数的只是处理上的一些细节不同，仅此而已）

考虑枚举回文子串的中点，并二分回文子串的长度（不过一般来说，二分回文子串的长度的1/2可能会更好写一点），那么我们使用上文提到的O(1)查询子串hash值的方法，就可以O(1)判断二分得到的这个子串是不是回文子串了。

对于长度为偶数的回文子串，枚举中点左边/右边的字符即可

效率是O(nlogn)的，复杂度较马拉车算法比较逊色，不过如果马拉车算法打挂或者是时间复杂度允许的情况下，hash也是一个不错的选择。

然后还有一种方法，适合像我这种下标总是搞错的，可以直接处理出正串和反串的hash值，然后每次根据二分出来的长度计算整个字符串的起止，判断正串和反串的hash值是否相等即可。（这样就不用研究恶心的下标了...研究下标还得分奇偶讨论...）

**字符串的很多特性是具有单调性的，二分求解是一个常见的思路，配合哈希进行判断操作一般可以做到在O(nlogn)O(nlogn)O(nlogn)效率内完成问题**

例题：[SP7586 NUMOFPAL - Number of Palindromes](https://www.luogu.org/problemnew/show/SP7586)

练习：[LOJ#2452. 「POI2010」反对称 Antisymmetry](https://www.cnblogs.com/henry-1202/p/10321013.html)

例题代码

```c++
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
#define N 10100
#define base 13131

char s[N];
ull h1[N], p[N], h2[N], ans = 0;
int n;

ull gh1(int l, int r) { return h1[r] - h1[l - 1] * p[r - l + 1]; }
ull gh2(int l, int r) { return h2[l] - h2[r + 1] * p[r - l + 1]; }

ull query1(int x) { //奇 
    int l = 1, r = min(x, n - x);
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(gh1(x - mid, x + mid) == gh2(x - mid, x + mid)) l = mid + 1;
        else r = mid - 1; 
    }
    return r;
}

ull query2(int x) { //偶 
    int l = 1, r = min(x, n - x); 
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(gh1(x - mid + 1, x + mid) == gh2(x - mid + 1, x + mid)) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}

int main() {
    scanf("%s", s + 1); p[0] = 1;
    n = strlen(s + 1);
    for(int i = 1; i <= n; ++i) {
        h1[i] = h1[i - 1] * base + s[i];
        p[i] = p[i - 1] * base;
    }
    for(int i = n; i; i--) h2[i] = h2[i + 1] * base + s[i];
    for(int i = 1; i < n; ++i) {
        ans += query1(i) + query2(i);
    }
    printf("%llu\n", ans + n);
}
```

## 用hash代替kmp算法

我们这里不讲kmp算法，我们利用hash来代替kmp算法求解单模式串匹配问题。

但是kmp算法的next数组真的很妙！可以解决很多神奇的东西，强烈推荐去学学！

好了，步入正题。

**单模式串匹配问题是什么？**

给出两个字符串s1和s2，其中s2为s1的子串，求s2在s1中出现多少次/出现的位置。

如果有认真看过该篇文章的第一子目的话，应该不难想到这题的hash做法。

具体做法是预处理出来两个串的hash值，因为求的是s2在s1中出现的次数，所以我们要匹配的长度被压缩到了s2的长度，所以我们只需要枚举s2在s1中的起点，看看后面一段长度为len的区间的hash值和s2的hash值一不一样就好。

时间复杂度是O(n+m)的！和kmp算法一样！

例题：[LOJ #103. 子串查找](https://loj.ac/problem/103) 

练习：[UVA10298 Power Strings](https://www.luogu.org/problemnew/show/UVA10298)

例题代码

```c++
#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define ull unsigned long long
#define base 233

ull h[N], p[N], ha;
char s1[N], s2[N];

int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    int n = strlen(s1 + 1), m = strlen(s2 + 1);
    for(int i = 1; i <= m; ++i) ha = ha * base + (ull)s2[i];
    p[0] = 1;
    for(int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] * base + (ull)s1[i];
        p[i] = p[i - 1] * base;
    }
    int l = 1, r = m, ans = 0;
    while(r <= n) {
        if(h[r] - h[l - 1] * p[m] == ha) ++ans;
        ++l, ++r;
    }
    printf("%d\n", ans);
}
```