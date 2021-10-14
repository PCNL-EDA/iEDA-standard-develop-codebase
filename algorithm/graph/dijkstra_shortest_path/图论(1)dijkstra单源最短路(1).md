**Dijkstra 算法**，是由荷兰计算机科学家 Edsger Wybe Dijkstra 在1956年发现的算法，戴克斯特拉算法使用类似广度优先搜索的方法解决**赋权图的单源最短路径问题**。Dijkstra 算法原始版本仅适用于找到两个顶点之间的最短路径，后来更常见的变体固定了一个顶点作为源结点然后找到该顶点到图中所有其它结点的最短路径，产生一个最短路径树。本算法每次取出未访问结点中距离最小的，用该结点更新其他结点的距离。需要注意的是绝大多数的Dijkstra 算法不能有效处理带有**负权边**的图。

下面，我们就从一个赋权的有向图为例开始解释Dijkstra 算法。

设一个赋权有向图 ![[公式]](https://www.zhihu.com/equation?tex=G%3D%28V%2C%5C%2CE%2C%5C%2CW%29) 。其中的每条边 ![[公式]](https://www.zhihu.com/equation?tex=e_%7Bi%2Cj%7D%3A%3D%5Cleft%5C%7Bv_i%2C%5C%2Cv_j%5Cright%5C%7D) 的权值为一个非负的实数 ![[公式]](https://www.zhihu.com/equation?tex=w_%7Bi%2Cj%7D%28e_%7Bi%2Cj%7D%29) ，**该权值表示从顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 的距离**。并设一单源点 ![[公式]](https://www.zhihu.com/equation?tex=s%5Cin+V) 。现在我们的任务是：找出从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 出发，到 ![[公式]](https://www.zhihu.com/equation?tex=V%5Csetminus%5C%7Bs%5C%7D) 中所有的节点的最短路径。

我们来看一个具体的例子：

![img](https://s3.bmp.ovh/imgs/2021/09/a0052889d5d9f7d1.png)图片1：例图。

这是一个具有 ![[公式]](https://www.zhihu.com/equation?tex=6) 个顶点的赋权有向图，其顶点集合为 ![[公式]](https://www.zhihu.com/equation?tex=V%3D%5Cleft%5C%7Bv_1%2Cv_2%2Cv_3%2Cv_4%2Cv_5%2Cv_6%5Cright%5C%7D) ，其权值分别为：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+w_%7B1%2C2%7D%5Cleft%28e_%7B1%2C2%7D%5Cright%29%3D10%26+w_%7B2%2C3%7D%5Cleft%28e_%7B2%2C3%7D%5Cright%29%3D7%5C%5C+w_%7B4%2C3%7D%5Cleft%28e_%7B4%2C3%7D%5Cright%29%3D4%26+w_%7B4%2C5%7D%5Cleft%28e_%7B4%2C5%7D%5Cright%29%3D7%5C%5C++w_%7B6%2C5%7D%5Cleft%28e_%7B6%2C5%7D%5Cright%29%3D1%26++w_%7B1%2C6%7D%5Cleft%28e_%7B1%2C6%7D%5Cright%29%3D3%5C%5C++w_%7B6%2C2%7D%5Cleft%28e_%7B6%2C2%7D%5Cright%29%3D2%26++w_%7B4%2C1%7D%5Cleft%28e_%7B4%2C1%7D%5Cright%29%3D3%5C%5C++w_%7B2%2C4%7D%5Cleft%28e_%7B2%2C4%7D%5Cright%29%3D5%26++w_%7B6%2C4%7D%5Cleft%28e_%7B6%2C4%7D%5Cright%29%3D6+%5Cend%7Bmatrix%7D%5Ctag%7B1%7D)

现在我们选定 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 为原点 ![[公式]](https://www.zhihu.com/equation?tex=s) ：

![img](https://i.bmp.ovh/imgs/2021/09/a465369bd902235e.png)图片2：选择v_1作为原点s。

则从源点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 出发，到 ![[公式]](https://www.zhihu.com/equation?tex=V%5Csetminus+%5Cleft%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%5Cright%5C%7D) 中所有顶点的最短路径分别为：

![img](https://i.bmp.ovh/imgs/2021/09/964e1ba205b77c5b.png)图片3：V中的源点s(v_1)到V中其余点的最短路径。

即：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Balign%2A%7D++%26%5Cmathrm%7Bshort%7D%5Cleft%5B2%5Cright%5D%3A%5Ccolor%7Bred%7D%7Bv_1%7D%5Cto+v_6%5Cto+v_2%5CRightarrow+%5Cmathrm%7Bshort%7D%5Cleft%5B2%5Cright%5D%3Dw_%7B1%2C6%7D%2Bw_%7B6%2C2%7D%3D5%5Ctag%7B2%7D%5C%5C+%26%5Cmathrm%7Bshort%7D%5Cleft%5B3%5Cright%5D%3A%5Ccolor%7Bred%7D%7Bv_1%7D%5Cto+v_6%5Cto+v_2%5Cto+v_3%5CRightarrow+%5Cmathrm%7Bshort%7D%5Cleft%5B3%5Cright%5D%3Dw_%7B1%2C6%7D%2Bw_%7B6%2C2%7D%2Bw_%7B2%2C3%7D%3D12%5Ctag%7B3%7D%5C%5C+%26%5Cmathrm%7Bshort%7D%5Cleft%5B4%5Cright%5D%3A%5Ccolor%7Bred%7D%7Bv_1%7D%5Cto+v_6%5Cto+v_4%5CRightarrow+%5Cmathrm%7Bshort%7D%5Cleft%5B4%5Cright%5D%3Dw_%7B1%2C6%7D%2Bw_%7B6%2C4%7D%3D9%5Ctag%7B4%7D%5C%5C+%26%5Cmathrm%7Bshort%7D%5Cleft%5B5%5Cright%5D%3A%5Ccolor%7Bred%7D%7Bv_1%7D%5Cto+v_6%5Cto+v_5%5CRightarrow+%5Cmathrm%7Bshort%7D%5Cleft%5B5%5Cright%5D%3Dw_%7B1%2C6%7D%2Bw_%7B6%2C5%7D%3D4%5Ctag%7B5%7D%5C%5C+%26%5Cmathrm%7Bshort%7D%5Cleft%5B6%5Cright%5D%3A%5Ccolor%7Bred%7D%7Bv_1%7D%5Cto+v_6%5CRightarrow+%5Cmathrm%7Bshort%7D%5Cleft%5B6%5Cright%5D%3Dw_%7B1%2C6%7D%3D3%5Ctag%7B6%7D+%5Cend%7Balign%2A%7D)

其中， ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bshort%7D%5B%5Cbullet%5D) 表示从源点 ![[公式]](https://www.zhihu.com/equation?tex=s%28%5Ccolor%7Bred%7D%7Bv_1%7D%29) 出发，到 ![[公式]](https://www.zhihu.com/equation?tex=V%5Csetminus%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%5C%7D) 中的顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbullet) 的最短路径。

> 注：**最短路径可以理解为所有可能的路径中总权和最小的那一条路径**。举一个再简单不过的例子：你开车从城市 ![[公式]](https://www.zhihu.com/equation?tex=A) 到城市 ![[公式]](https://www.zhihu.com/equation?tex=B) ，假设有很多条路可以走，最短的那条路就是最短路径，总权和可以理解为总的公里数。

以上是我们通过观察和计算比对出来的最短路径，下面我们就来看看Dijkstra 算法是如何帮助我们找到这些所有的最短路径的。

在开始之前，有几个概念需要明确一下。

- 定义一个集合 ![[公式]](https://www.zhihu.com/equation?tex=S) ，如果集合 ![[公式]](https://www.zhihu.com/equation?tex=V%5Csetminus+%5C%7Bs%5C%7D) 中的某个顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中了，那么就说明从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cin+V%5Csetminus+%5C%7Bs%5C%7D) 的最短路径已经被找到，而在算法一开始的时候，集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中只有源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 。即：

![[公式]](https://www.zhihu.com/equation?tex=S%3A%3D%5Cleft%5C%7Bv_i%5Cin+V%5C%2C%3A%5C%2C+%5Cmathrm%7Bthe%5C%2C%5C%2C+shortest%5C%2C%5C%2Cpath%5C%2C%5C%2Cof%5C%2C%5C%2Cvertex%5C%2C%5C%2C%7Dv_i%5C%2C%5C%2C%5Cmathrm%7Bhas%5C%2C%5C%2C+been%5C%2C%5C%2C+found%7D%5Cright%5C%7D%5Ctag%7B7%7D)

而且，当且仅当 ![[公式]](https://www.zhihu.com/equation?tex=S%3DV) 的时候算法执行完毕。此时顶点集 ![[公式]](https://www.zhihu.com/equation?tex=V) 中的所有元素都被放进了集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 种，也就是说除了源点以外的所有从源点出发到其余所有顶点的最短路径已被找到。

> 注：当然了，你也可以认为源点到自己本身的最短路径也被找到了。对于任意一个**无自环的**源点，它到自己本身的最短路径都是 ![[公式]](https://www.zhihu.com/equation?tex=0) 。

- 下面这个概念可能稍微有些抽象，不过没有关系，这里理解不了的话我们一会讲例子的时候会进行具体说明。这个概念叫做**从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cin+V)** （一开始 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cnotin+S) ）**的相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径**。 即从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cin+V) 的路径**中间**只能经过已经包含在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中的顶点，而不能经过其余的还未在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中的顶点。而这个相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径的长度我们记作：

![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5Ctag%7B8%7D)

而我们之前的 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bshort%7D%5B%5Cbullet%5D%5Cleft%28%5CLeftrightarrow%5Cmathrm%7Bshort%7D%5Bs%2Cv_i%5D%5Cright%29) 表示的是**全局的**从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cin+V%5Csetminus%5Cleft%5C%7Bs%5Cright%5C%7D) 的最短路径，这个最短路径没有限制“必须在路径中间只能经过已经包含在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中的顶点”，这个全局的最短路径才是我们要的最终解。所以，一般有关系：

![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5Cge%5Cmathrm%7Bshort%7D%5Bs%2Cv_i%5D%5Ctag%7B9%7D)

而我们的Dijkstra 算法要做的就是通过不断计算 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D) 进而不断的扩充集合 ![[公式]](https://www.zhihu.com/equation?tex=S) ，当集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 不断被扩充的时候，相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径会越来越短，直到 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 入集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 之时，此时我们便得到了 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bshort%7D%5Bs%2Cv_i%5D) ，且此时有 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%3D%5Cmathrm%7Bshort%7D%5Bs%2Cv_i%5D+) 。下面我们来看看算法的设计思想：

> **输入**：赋权有向图 ![[公式]](https://www.zhihu.com/equation?tex=G%3D%28V%2C%5C%2CE%2C%5C%2CW%29%2C%5Cquad+V%3D%5Cleft%5C%7Bv_1%2Cv_2%2C%5Cldots%2Cv_n%5Cright%5C%7D%2C%5Cquad+s%3A%3Dv_1) 。
> **输出**：从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到所有的 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cin+V%5Csetminus%5C%7Bs%5C%7D) 的最短路径。
> ![[公式]](https://www.zhihu.com/equation?tex=1.) 初始 ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5Cleft%5C%7Bv_1%5Cright%5C%7D) ；
> ![[公式]](https://www.zhihu.com/equation?tex=2.) 对于 ![[公式]](https://www.zhihu.com/equation?tex=v_i%5Cin+V-S) ，计算 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D) ；
> ![[公式]](https://www.zhihu.com/equation?tex=3.) 选择 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmin_%7Bv_j+%5Cin+V%7D%5C%2C%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D) ，并将这个 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中，更新 ![[公式]](https://www.zhihu.com/equation?tex=V-S) 中的顶点的 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D) 值；
> ![[公式]](https://www.zhihu.com/equation?tex=4.) 重复 ![[公式]](https://www.zhihu.com/equation?tex=1) ，直到 ![[公式]](https://www.zhihu.com/equation?tex=S%3DV) 。

然后是Dijkstra 算法的伪码：

![[公式]](https://www.zhihu.com/equation?tex=%5Cboxed%7B%5Clarge%5Cbegin%7Balign%2A%7D+%26%5Clarge%7B%5Cbm%7B%5Crm%7BAlgorithm%3ADijkstra%7D%7D%7D%5C%5C+%26%5C%5C+%26%5Cbm%7B%5Cmathrm%7BInput%3A%7D%7D%5Cmathrm%7BDirected%5C%2C%5C%2C+graph%5C%2C%5C%2C%7DG%3D%28V%2CE%2CW%29%5C%2C%5C%2C%5Cmathrm%7Bwith%5C%2C%5C%2C+weight%7D%5C%5C+%26%5C%5C+%26%5Cbm%7B%5Cmathrm%7BOutput%3A%7D%7D%5Cmathrm%7BAll%5C%2C%5C%2C+the%5C%2C%5C%2Cshortest%5C%2C%5C%2Cpaths%5C%2C%5C%2C+from%5C%2C%5C%2C+the%5C%2C%5C%2C+source%5C%2C%5C%2Cvertex%5C%2C%5C%2C%7Ds%5Cmathrm%7B%5C%2C%5C%2Cto%5C%2C%5C%2Cevery%5C%2C%5C%2Cvertex%5C%2C%5C%2C%7Dv_i%5Cin+V%5Csetminus%5Cleft%5C%7Bs%5Cright%5C%7D%5C%5C+%26%5C%5C+%261%3AS%5Cleftarrow+%5Cleft+%5C%7B+s+%5Cright+%5C%7D%5C%5C+%262%3A%5Cmathrm%7Bdist%7D%5Bs%2Cs%5D%5Cleftarrow+0%5C%5C+%263%3A%5Cbm%7B%5Cmathrm%7Bfor%7D%7D%5C%2C%5C%2C+v_i%5Cin+V-%5Cleft+%5C%7B+s+%5Cright+%5C%7D%5C%2C%5C%2C%5Cbm%7B%5Cmathrm%7Bdo%7D%7D%5C%5C+%264%3A%5Cquad%5C%2C%5C%2C+%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5Cleftarrow+w%28s%2Cv_i%29%5C%5C+%26%5Cquad+%5C%2C%5C%2C%5C%2C%5Cquad+%28%5Cmathrm%7Bwhen%5C%2C%5C%2C%7Dv_i%5C%2C%5C%2C%5Cmathrm%7Bnot%5C%2C%5C%2Cfound%7D%2C%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5Cleftarrow+%5Cinfty%29%5C%5C+%265%3A%5Cbm%7B%5Cmathrm%7Bwhile%7D%7D%5C%2C%5C%2CV-S%5Cne%5Cvarnothing+%5C%2C%5C%2C%5Cbm%7B%5Cmathrm%7Bdo%7D%7D%5C%5C+%266%3A%5Cquad%5C%2C%5C%2C%5C%2C%5C%2C+%5Cmathrm%7Bfind%5C%2C%5C%2C%7D%5Cmin_%7Bv_j%5Cin+V%7D%5C%2C%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5C%2C%5C%2C%5Cmathrm%7Bfrom%5C%2C%5C%2C+the%5C%2C%5C%2C+set%5C%2C%5C%2C%7DV-S%5C%5C+%267%3A%5Cquad%5C%2C%5C%2C%5C%2C%5C%2C+S%5Cleftarrow+S%5Ccup+%5Cleft%5C%7Bv_j%5Cright%5C%7D%5C%5C+%268%3A%5C%2C%5C%2C%5C%2C%5C%2C%5Cquad+%5Cbm%7B%5Cmathrm%7Bfor%5C%2C%5C%2C%7D%7Dv_i%5Cin+V-S%5C%2C%5C%2C%5Cbm%7B%5Cmathrm%7Bdo%7D%7D%5C%5C+%269%3A%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5Cquad%5Cquad+%5Cbm%7B%5Cmathrm%7Bif%5C%2C%5C%2C%7D%7D%5Cmathrm%7Bdist%7D%5Bs%2Cv_j%5D%2Bw_%7Bj%2Ci%7D%3C%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5C%2C%5C%2C%5Cbm%7B%5Cmathrm%7Bthen%7D%7D%5C%5C+%2610%3A%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5Cquad%5Cquad%5Cquad+%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%5Cleftarrow+%5Cmathrm%7Bdist%7D%5Bs%2Cv_j%5D%2Bw_%7Bj%2Ci%7D+%5Cend%7Balign%2A%7D%7D%5Ctag%7B10%7D)

下面我们来解释一下这个伪码：

![[公式]](https://www.zhihu.com/equation?tex=1%3A) 算法初始，将选择的源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中；

![[公式]](https://www.zhihu.com/equation?tex=2%3A) 无自环的源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到自己的最短路径为 ![[公式]](https://www.zhihu.com/equation?tex=0) ；

![[公式]](https://www.zhihu.com/equation?tex=3%3A) 当顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 不在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中时（此时集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中仍只有源点 ![[公式]](https://www.zhihu.com/equation?tex=s) ），开始进入循环；

![[公式]](https://www.zhihu.com/equation?tex=4%3A) 将源点 ![[公式]](https://www.zhihu.com/equation?tex=+s) 与点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 之间的权值赋给 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D) 。由于是有向图，所以当源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 不指向任何其他集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 外的顶点时， ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2Cv_i%5D%3D%5Cinfty) 。可以理解为**此时**从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 出发，**暂时**是达到不了 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 的。不过后来随着集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的扩充，从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 出发一定能到达所有的顶点。一会我们讲解例子时会出现这种情况。此时第一个 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bfor%7D%7D) 循环结束。

![[公式]](https://www.zhihu.com/equation?tex=5%3A) 如果集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) 不是空集，则进入循环；

![[公式]](https://www.zhihu.com/equation?tex=6%3A) 选出经过第一个 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bfor%7D%7D) 循环之后的，在集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) 中的，且相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径中距离最短的那个顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) ;

![[公式]](https://www.zhihu.com/equation?tex=7+%3A) 将这个顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 并入集合 ![[公式]](https://www.zhihu.com/equation?tex=S) ，从而达到扩充集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的目的；

![[公式]](https://www.zhihu.com/equation?tex=8%3A) 将顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 并入集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 之后可能会对其他顶点相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路的长度会有影响，所以进入内 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bfor%7D%7D) 循环对有影响的进行更新；

![[公式]](https://www.zhihu.com/equation?tex=9%3A) 即如果从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到我们在第 ![[公式]](https://www.zhihu.com/equation?tex=6) 步选出的顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 的相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径的长度再加上顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 之间的距离 ![[公式]](https://www.zhihu.com/equation?tex=w_%7Bi%2Cj%7D) 还要小于源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 的相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径的长度还要短的话；

![[公式]](https://www.zhihu.com/equation?tex=10%3A+) 则将源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 的相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径更新成源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 到我们在第 ![[公式]](https://www.zhihu.com/equation?tex=6) 步选出的顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 的相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径再加上顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j) 到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_i) 之间的权值 ![[公式]](https://www.zhihu.com/equation?tex=w_%7Bi%2Cj%7D) 。

下面我们开始讲例子，我们还是以图片1中的赋权有向图进行说明。

![img](https://i.bmp.ovh/imgs/2021/09/508524ef389605e7.png)图片4

首先我们还是选择 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 为原点 ![[公式]](https://www.zhihu.com/equation?tex=s) ，那么在算法的开始， ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%5C%7D) 。之后我们计算除了 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 以外的其余顶点到 ![[公式]](https://www.zhihu.com/equation?tex=s%3D%5Ccolor%7Bred%7D%7Bv_1%7D) 的距离 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bv_2%2Cv_1%5D%5Csim+%5Cmathrm%7Bdist%7D%5Bv_6%2Cv_1%5D) ，即寻找所有的除了 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 以外的所有顶点相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路，即从 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D%7B%7D) 出发，到达所有顶点且只允许通过顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D%7B%7D)（因为此时集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中只有 ![[公式]](https://www.zhihu.com/equation?tex=v_1) 这一个元素）的最短路径。这是我们的算法中的第一个 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bfor%7D%7D) 循环在做的事情。这时候我们发现想要**只通过**顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D%7B%7D) 而到达顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_4%2Cv_3%2Cv_5) 都是不可能的，所以我们有：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3Dw_%7B1%2C2%7D%3D10+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%3D%5Cinfty+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cinfty+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_5%5D%3D%5Cinfty+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_6%5D%3Dw_%7B1%2C6%7D%3D3+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bred%7D%7Bv_1%7D%5D%3D0+%5Cend%7Bmatrix%7D%5Ctag%7B11%7D)

而 ![[公式]](https://www.zhihu.com/equation?tex=v_4%2Cv_3%2Cv_5) 就是算法中所说的暂时到达不了的顶点了。现在算法的前四步已经结束了，现在开始第五步检验集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) 是否是空集，这里显然不是，这里：

![[公式]](https://www.zhihu.com/equation?tex=V-S%3D%5Cleft%5C%7Bv_2%2Cv_3%2Cv_4%2Cv_5%2Cv_6%5Cright%5C%7D%5Ctag%7B12%7D+)

现在进行第六步。第六步是选出经过第一个 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bfor%7D%7D) 循环之后的，在集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) 中的，且相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径中距离最短的那个顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_j)。那我们看看在式 ![[公式]](https://www.zhihu.com/equation?tex=%2811%29) 中那个顶点距离源点 ![[公式]](https://www.zhihu.com/equation?tex=v_1) 最短就好了，显然是 ![[公式]](https://www.zhihu.com/equation?tex=v_6) ，所以，我们这里选择的 ![[公式]](https://www.zhihu.com/equation?tex=v_j%3Dv_6) 。

那么第七步就是将 ![[公式]](https://www.zhihu.com/equation?tex=v_6) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中了。此时集合 ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5Cleft%5C%7Bv_1%2Cv_6%5Cright%5C%7D) 。这就是说明从源点 ![[公式]](https://www.zhihu.com/equation?tex=s) 出发，到顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_6) 的最短路径已经被找到了。

下面我用绿色表示被放入集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中的顶点：

![img](https://s3.bmp.ovh/imgs/2021/09/133e12db5788d53e.png)图片5：顶点v_6被加进集合S中。

![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 的颜色我就不变了，因为它一直都在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中。此时：

![[公式]](https://www.zhihu.com/equation?tex=S%3D%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5C%7D%5Ctag%7B13%7D)

这就说明下次在找相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径的时候 ![[公式]](https://www.zhihu.com/equation?tex=S) 中就有两个点可以被通过了，这样也许就会使得一些原来到达不了的顶点由于可以多经过一个点而到达，这也就是算法中所说的当我将一个新的顶点并入集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 之后，其他的在集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) 以外的顶点的相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径的长度可能会发生改变，因为有些原来暂时到达不了的顶点现在可以到达了。具体的来讲，我们有：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%3D5+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%3D%5Cinfty+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C4%7D%3D9+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_5%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C5%7D%3D4+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%3Dw_%7B1%2C6%7D%3D3+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bred%7D%7Bv_1%7D%5D%3D0+%5Cend%7Bmatrix%7D%5Ctag%7B14%7D)

这个更新步骤我也来详细是说一下，这是算法第八到第十步所做的事情。比如 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D) ，一开始在集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中只有源点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) ，而找到 ![[公式]](https://www.zhihu.com/equation?tex=v_2) 相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径只能通过顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) ，这样我们在式 ![[公式]](https://www.zhihu.com/equation?tex=%2811%29) 中所得到 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3Dw_%7B2%2C1%7D%3D10) 。但是当顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bgreen%7D%7Bv_6%7D) 也进入到集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 之后我们再找 ![[公式]](https://www.zhihu.com/equation?tex=v_2) 相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径时就可以先通过顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bred%7D%7Bv_1%7D) 然后到顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bgreen%7D%7Bv_6%7D) ，最后再到 ![[公式]](https://www.zhihu.com/equation?tex=v_2) 。现在这两种走法都可以，但是算法究竟选择哪种算法还是要判断哪种走法距离最短，即比较 ：

![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%2C%5Cquad%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%5Ctag%7B15%7D)

之间的大小关系，谁小算法就选择谁。经过比较发现：

![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3D10%3E%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%3D5%5Ctag%7B16%7D)

所以选择后者。再比如原来达到不了的 ![[公式]](https://www.zhihu.com/equation?tex=+v_4) ，现在由于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中多了顶点 ![[公式]](https://www.zhihu.com/equation?tex=%5Ccolor%7Bgreen%7D%7Bv_6%7D) 变得可以达到了，即：

![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cinfty%5Cgg%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C4%7D%3D9%5Ctag%7B17%7D)

所以算法肯定选择后者。不过此时算法也没得可选，先要到达顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_4) 就必须走这条路。

其余发生变化的顶点分析类似，大家可以自己试试。

现在算法从头到尾被执行了一遍了，然后我们回到第五步判断 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bwhile%7D%7D) 循环的条件还是否为真，此时：

![[公式]](https://www.zhihu.com/equation?tex=V-S%3D%5Cleft%5C%7Bv_2%2Cv_3%2Cv_4%2Cv_5%5Cright%5C%7D%5Cne%5Cvarnothing%5Ctag%7B18%7D)

所以再执行 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bwhile%7D%7D) 循环，由第六步从式 ![[公式]](https://www.zhihu.com/equation?tex=%2814%29) 中选择出属于集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) ，且相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径中距离最短的那个顶点为 ![[公式]](https://www.zhihu.com/equation?tex=v_j) ，所以，这里我们选择的 ![[公式]](https://www.zhihu.com/equation?tex=v_j%3Dv_5) 。然后第七步 将 ![[公式]](https://www.zhihu.com/equation?tex=v_5) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 。此时，集合 ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5Cleft%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%2C%5Ccolor%7Bgreen%7D%7Bv_5%7D%5Cright%5C%7D) ：

![img](https://s3.bmp.ovh/imgs/2021/09/87c5883f57ecd667.png)图片6：v_5被放进集合S中。

此时我们有：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%3D5+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%3D%5Cinfty+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C4%7D%3D9+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_5%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C5%7D%3D4+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%3Dw_%7B1%2C6%7D%3D3+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bred%7D%7Bv_1%7D%5D%3D0+%5Cend%7Bmatrix%7D%5Ctag%7B19%7D)

可见这次没有发生更新，且此时的：

![[公式]](https://www.zhihu.com/equation?tex=V-S%3D%5Cleft%5C%7Bv_2%2Cv_3%2Cv_4%5Cright%5C%7D%5Cne%5Cvarnothing%5Ctag%7B20%7D)

所以再执行 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bwhile%7D%7D) 循环，由第六步从式 ![[公式]](https://www.zhihu.com/equation?tex=%2819%29) 中选择出属于集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) ，且相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径中距离最短的那个顶点为 ![[公式]](https://www.zhihu.com/equation?tex=v_j) ，所以，这里我们选择的 ![[公式]](https://www.zhihu.com/equation?tex=v_j%3Dv_2) 。然后第七步 将 ![[公式]](https://www.zhihu.com/equation?tex=v_2) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 。此时，集合 ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5Cleft%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%2C%5Ccolor%7Bgreen%7D%7Bv_5%7D%2C%5Ccolor%7Bgreen%7D%7Bv_2%7D%5Cright%5C%7D) ：

![img](https://s3.bmp.ovh/imgs/2021/09/bfaa6ae52898f7e4.png)图片7：v_2被放进集合S中。

此时我们有：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%3D5+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%2Bw_%7B2%2C3%7D%3D12+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C4%7D%3D9+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_5%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C5%7D%3D4+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%3Dw_%7B1%2C6%7D%3D3+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bred%7D%7Bv_1%7D%5D%3D0+%5Cend%7Bmatrix%7D%5Ctag%7B21%7D)

可见这次在顶点 ![[公式]](https://www.zhihu.com/equation?tex=v_3) 处发生了更新（至于为什么 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%5Cne+17) 大家可以自己分析一下试试），且此时的：

![[公式]](https://www.zhihu.com/equation?tex=V-S%3D%5Cleft%5C%7Bv_3%2Cv_4%5Cright%5C%7D%5Cne%5Cvarnothing%5Ctag%7B22%7D)

所以再执行 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bwhile%7D%7D) 循环，由第六步从式 ![[公式]](https://www.zhihu.com/equation?tex=%2819%29) 中选择出属于集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) ，且相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径中距离最短的那个顶点为 ![[公式]](https://www.zhihu.com/equation?tex=v_j) ，所以，这里我们选择的 ![[公式]](https://www.zhihu.com/equation?tex=v_j%3Dv_4) 。然后第七步 将 ![[公式]](https://www.zhihu.com/equation?tex=v_4) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 。此时，集合 ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5Cleft%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%2C%5Ccolor%7Bgreen%7D%7Bv_5%7D%2C%5Ccolor%7Bgreen%7D%7Bv_2%7D%2C%5Ccolor%7Bgreen%7D%7Bv_4%7D%5Cright%5C%7D) ：

![img](https://s3.bmp.ovh/imgs/2021/09/fffdcbbcfcbed040.png)图片8：v_4被放进集合S中。

此时我们有：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%3D5+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%2Bw_%7B2%2C3%7D%3D12+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C4%7D%3D9+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_5%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C5%7D%3D4+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%3Dw_%7B1%2C6%7D%3D3+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bred%7D%7Bv_1%7D%5D%3D0+%5Cend%7Bmatrix%7D%5Ctag%7B23%7D)

可见这次并未发生更新，且此时的：

![[公式]](https://www.zhihu.com/equation?tex=V-S%3D%5Cleft%5C%7Bv_3%5Cright%5C%7D%5Cne%5Cvarnothing%5Ctag%7B24%7D)

所以再执行 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bwhile%7D%7D) 循环，由第六步从式 ![[公式]](https://www.zhihu.com/equation?tex=%2819%29) 中选择出属于集合 ![[公式]](https://www.zhihu.com/equation?tex=V-S) ，且相对于集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 的最短路径中距离最短的那个顶点为 ![[公式]](https://www.zhihu.com/equation?tex=v_j) ，所以，这里我们选择的 ![[公式]](https://www.zhihu.com/equation?tex=v_j%3Dv_3) （至剩下 ![[公式]](https://www.zhihu.com/equation?tex=v_3) 可以被选择了）。然后第七步 将 ![[公式]](https://www.zhihu.com/equation?tex=v_3) 放进集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 。此时，集合 ![[公式]](https://www.zhihu.com/equation?tex=S%3D%5Cleft%5C%7B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%2C%5Ccolor%7Bgreen%7D%7Bv_5%7D%2C%5Ccolor%7Bgreen%7D%7Bv_2%7D%2C%5Ccolor%7Bgreen%7D%7Bv_4%7D%2C%5Ccolor%7Bgreen%7D%7Bv_3%7D%5Cright%5C%7D) ：

![img](https://s3.bmp.ovh/imgs/2021/09/56c1fa442df305ff.png)图片9：v_4被放进集合S中。

此时我们有：

![[公式]](https://www.zhihu.com/equation?tex=%5Cbegin%7Bmatrix%7D+%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_2%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%3D5+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_3%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C2%7D%2Bw_%7B2%2C3%7D%3D12+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_4%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C4%7D%3D9+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2Cv_5%5D%3D%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%2Bw_%7B6%2C5%7D%3D4+%5C%5C++%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bgreen%7D%7Bv_6%7D%5D%3Dw_%7B1%2C6%7D%3D3+%26%5Cmathrm%7Bdist%7D%5B%5Ccolor%7Bred%7D%7Bv_1%7D%2C%5Ccolor%7Bred%7D%7Bv_1%7D%5D%3D0+%5Cend%7Bmatrix%7D%5Ctag%7B25%7D)

这是最后一次了，且这次并未发生更新，且此时的：

![[公式]](https://www.zhihu.com/equation?tex=V-S%3D%5Cleft%5C%7B%5Cright%5C%7D%3D%5Cvarnothing%5Ctag%7B26%7D)

则不满足算法中的 ![[公式]](https://www.zhihu.com/equation?tex=%5Cbm%7B%5Crm%7Bwhile%7D%7D) 循环的条件，循环结束，算法结束。显然，此时有 ![[公式]](https://www.zhihu.com/equation?tex=V%3DS) 。

最后我们来看一看Dijkstra 算法的时间复杂度。

Dijkstra 算法的时间复杂度是 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathcal%7BO%7D%28nm%29) 。其中：

![[公式]](https://www.zhihu.com/equation?tex=n%3D%5Cleft%7C+V%5Cright%7C%2C%5Cquad+m%3D%5Cleft%7C+E%5Cright%7C%5Ctag%7B23%7D)

分别为赋权有向图中的顶点个数和边的个数。Dijkstra 算法的时间复杂度是 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathcal%7BO%7D%28nm%29) 是因为算法总共进行 ![[公式]](https://www.zhihu.com/equation?tex=%28n-1%29) 步，每一步选出一个具有最小 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathrm%7Bdist%7D%5Bs%2C%5Cbullet%5D) 值的顶点放入集合 ![[公式]](https://www.zhihu.com/equation?tex=S) 中，需要 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathcal%7BO%28m%29%7D) 的时间。

而选择基于堆实现的优先队列数据结构，可将Dijkstra 算法的时间复杂度降为 ![[公式]](https://www.zhihu.com/equation?tex=%5Cmathcal%7BO%7D%28+m%5Clog+n%29) 。

```c++
#include<bits/stdc++.h>

const int MaxN = 100010, MaxM = 500010;

struct edge
{
    int to, dis, next;
};

edge e[MaxM];
int head[MaxN], dis[MaxN], cnt;
bool vis[MaxN];
int n, m, s;

inline void add_edge( int u, int v, int d )
{
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

struct node
{
    int dis;
    int pos;
    bool operator <( const node &x )const
    {
        return x.dis < dis;
    }
};

std::priority_queue<node> q;


inline void dijkstra()
{
    dis[s] = 0;
    q.push( ( node ){0, s} );
    while( !q.empty() )
    {
        node tmp = q.top();
        q.pop();
        int x = tmp.pos, d = tmp.dis;
        if( vis[x] )
            continue;
        vis[x] = 1;
        for( int i = head[x]; i; i = e[i].next )
        {
            int y = e[i].to;
            if( dis[y] > dis[x] + e[i].dis )
            {
                dis[y] = dis[x] + e[i].dis;
                if( !vis[y] )
                {
                    q.push( ( node ){dis[y], y} );
                }
            }
        }
    }
}


int main()
{
    scanf( "%d%d%d", &n, &m, &s );
    for(int i = 1; i <= n; i++)dis[i] = 0x7fffffff;
    for(int i = 0; i < m; i++ )
    {
        int u, v, d;
        scanf( "%d%d%d", &u, &v, &d );
        add_edge( u, v, d );
    }
    dijkstra();
    for( int i = 1; i <= n; i++ )
        printf( "%d ", dis[i] );
    return 0;
}

```

