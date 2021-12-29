## 精确覆盖（Exact Cover）问题

### 精确覆盖

S 为集合 X 的若干个子集构成的集合，若存在 S 的一个子集 S*，满足 X 中的元素**有且只有一次**包含在 S* 的一个元素中，那么称 S* 为 X 的一个精确覆盖。

### S*属性

根据定义 S* 具有以下属性：

1. S* 中任意两个元素交集为空。
2. S* 中所有元素并集为 X。

### 例子

假定 S = { A, B, C, D} ,X = {1, 2, 3, 4, 5, 6} ,其中：
 A = {1, 3, 5}
 B = {2, 4}
 C = {2, 3, 4, 5, 6}
 D = {2, 4, 6}
 那么 S* = {A, D} 是 X 的一个精确覆盖。而 {A, B}、{A, C}
 分别不满足上述属性2、1，因而不是 X 的一个精确覆盖。

### 精确覆盖问题

精确覆盖问题是指给定一个 S，确定是否存在对 X 的一个精确覆盖，这是一个 NP 难问题。
 这个问题可以用一个矩阵来表示



![img](https://s2.loli.net/2021/12/26/UE7ALB1O9XonTve.png)

矩阵表示



在矩阵表示情形下，精确覆盖问题可以表述为选择特定的行使得所有的列有且只含有一个1。



![img](https://s2.loli.net/2021/12/26/8XBpgEtvIyuY7wH.png)

精确覆盖

## Algorithm X

![img](https://s2.loli.net/2021/12/26/FijSePH8GJ5DnxR.png)

X



不要被名字吓到，Donald E. Knuth 这么叫它的，本质上还是一个回溯法。其步骤如下所示：
 维护两个集合——当前尚未满足的限制条件和可供选择的选项。
 1.检查当前未满足的限制条件集合，若为空，则表示问题已经解决，输出答案并返回
 2.否则选择其中一个不满足的限制条件。（可以使用启发式算法尽量加快代码运行）
 3.找满足限制条件的选项集合，若为空，则表示当前这个位置不可能产出正确答案，返回。（剪枝）
 4.否则，遍历上述选项集合（这一步可以是随机选择，这样会导致一个 non-deterministic 算法）：
 （1）当前选项可能满足多个限制条件，故对每个满足的限制条件，将其从未满足限制条件集合中移除，并且将所有能满足这个限制条件的选项也移除（因为精确覆盖要求不可重叠，若考虑完全覆盖则此时不需要移除）
 （2）上述操作完成后形成“尚未满足的限制条件”和“可供选择的选项”这两个集合的子集合——即子问题，对此子问题递归求解。
 （3）复原：上述递归完成后，在测试下一个选项前，我们需要恢复原来两个集合的样子。所以要将之前移除的条件和选项全部恢复。
![img](https://s2.loli.net/2021/12/26/fCTOquYj5GWF83i.png)

X算法求解

## Dancing Links

可以看出上述操作需要一对对偶操作——将一个元素从矩阵中移除，一番操作完成后还要将移除的这个元素重新添加回矩阵中去，这个用普通结构实现可能会比较复杂。

### Insight——双向链表操作

将双向链表中的一个元素拿掉



```swift
x.left.right=x.right
x.right.left=x.left
```



双向链表删除



将该元素重新加入链表



```swift
x.left.right=x
x.right.left=x
```



双向链表恢复

### DLX

我们可以类似地将每个节点都弄成四路链表，将所有连同节点连接起来，如下图所示：



![img](https://s2.loli.net/2021/12/26/BxMylsbn18tNzAG.png)



4 way mesh



再加上约束条件属性和一些其他属性，我们的节点可以声明为如下形式：



```cpp
struct Node
{
public:
    struct Node *left;
    struct Node *right;
    struct Node *up;
    struct Node *down;
    struct Node *column;
    int rowID;
    int colID;
    int nodeCount;
};
```







```cpp
Node *createToridolMatrix()
{
    for(int i = 0; i <= nRow; i++)
    {
        for(int j = 0; j < nCol; j++)
        {
          
            if(ProbMat[i][j])
            {
                int a, b;
                // first row represent constraints
                if(i) Matrix[0][j].nodeCount += 1;
                Matrix[i][j].column = &Matrix[0][j];
                Matrix[i][j].rowID = i;
                Matrix[i][j].colID = j;

                // Left pointer
                a = i; b = j;
                do{ b = getLeft(b); } while(!ProbMat[a][b] && b != j);
                Matrix[i][j].left = &Matrix[i][b];
                // Right pointer
                a = i; b = j;
                do { b = getRight(b); } while(!ProbMat[a][b] && b != j);
                Matrix[i][j].right = &Matrix[i][b];
                // Up pointer
                a = i; b = j;
                do { a = getUp(a); } while(!ProbMat[a][b] && a != i);
                Matrix[i][j].up = &Matrix[a][j];
                // Down pointer
                a = i; b = j;
                do { a = getDown(a); } while(!ProbMat[a][b] && a != i);
                Matrix[i][j].down = &Matrix[a][j];
            }
        }
    }

    //configure header
    header->right = &Matrix[0][0];
    header->left = &Matrix[0][nCol-1];
    Matrix[0][0].left = header;
    Matrix[0][nCol-1].right = header;
    return header;
}
```

**删除节点**
 类比双向链表的删除即可，其主要删除两部分：属性和**满足该属性行**的**除本属性外**的**其它所有子节点**。略拗口，还是看图示吧。

![img](https://s2.loli.net/2021/12/26/nihXw6teloPDA1S.png)

remove


 这是因为无论具体选择哪一行，另一行的其它节点都因为本属性互斥和不能**发挥作用**（**消除限制条件**），所以把他们暂时屏蔽（删除）掉。
 另外要注意只删除上下链，不删除左右链！





```cpp
void remove(struct Node *targetNode)
{
    struct Node *row, *rightNode;
    struct Node *colNode = targetNode->column;
    //delete constraints
    colNode->left->right = colNode->right;
    colNode->right->left = colNode->left;

    //remove each row
    for(row = colNode->down; row != colNode; row = row->down)
    {
        for(rightNode = row->right; rightNode != row;
            rightNode = rightNode->right)
        {
            rightNode->up->down = rightNode->down;
            rightNode->down->up = rightNode->up;
            Matrix[0][rightNode->colID].nodeCount -= 1;
        }
    }
}
```

**恢复节点**
 理解了删除节点，恢复节点就容易了，是上述过程的逆过程。



```cpp
void resume(struct Node *targetNode)
{
    struct Node *rowNode, *leftNode;
    struct Node *colNode = targetNode->column;
    //resume row    
    for(rowNode = colNode->up; rowNode != colNode; rowNode = rowNode->up)
    {
        for(leftNode = rowNode->left; leftNode != rowNode;
            leftNode = leftNode->left)
        {
            leftNode->up->down = leftNode;
            leftNode->down->up = leftNode;          
            Matrix[0][leftNode->colID].nodeCount += 1;
        }    }

    // resume header
    colNode->left->right = colNode;
    colNode->right->left = colNode;
}
```

**启发式选择列**
 我们先选择列节点数个数最少的来挑选，因为先选择其它的这个可能就被限制无法进行选择了。



```cpp
Node *getMinColumn()
{
    struct Node *h = header;
    struct Node *min_col = h->right;
    h = h->right->right;
    do
    {
        if(h->nodeCount < min_col->nodeCount)
        {
            min_col = h;
        }
        h = h->right;
    }while(h != header);
    return min_col;
}
```

**Let's dancing!**
 首先选择某一列，然后对满足该列的行进行遍历，每遍历一行，删除此行中同时满足其它列，进行递归即可。注意递归完成要恢复原样。



```cpp
void dancing(int k)
{
    struct Node *rowNode;
    struct Node *rightNode;
    struct Node *leftNode;
    struct Node *column;
    //found solution
    if(header->right == header)
    {
        printSolutions();
        return;
    }
    // heuristic choose column
    column = getMinColumn();
    // remove chosen column
    remove(column);

    for(rowNode = column->down; rowNode != column;
        rowNode = rowNode->down )
    {
        solutions.push_back(rowNode);

        for(rightNode = rowNode->right; rightNode != rowNode;
            rightNode = rightNode->right)
            remove(rightNode);
        // recursive solve problem
        search(k+1);
        // if solution in not possible, backtrack (resume)
        solutions.pop_back();
        column = rowNode->column;
        for(leftNode = rowNode->left; leftNode != rowNode;
            leftNode = leftNode->left)
            resume(leftNode);
    }
    resume(column);
}
```

### 应用

对于有约束条件的搜索问题，我们可以将约束条件转化为每一列，而将所有可能情形转化为行，那么问题就转化为了前文中的矩阵情形：找出所有可能的行组合使得所有列有且只有一个1！举例如下：
 1.拼图问题
 找出是否存在一种方案，使得使用给定积木恰好填满给定区域。

 2.数独求解



![img](https://s2.loli.net/2021/12/26/ukfv35IzqPjKVRb.png)

数独



3.N皇后问题



![img](https:////upload-images.jianshu.io/upload_images/2702997-e9b3f1e4cfa30b41?imageMogr2/auto-orient/strip|imageView2/2/w/254/format/webp)

N皇后问题


 具体怎么映射限制条件还是有一定 trick 的，这个以后有时间再单独拎出来分析一哈吧。

### 总结

本文主要介绍了精确覆盖问题、Algorithm X 与 DLX，给出了 DLX 的主要操作 remove 和 resume。同时点出了其在解决完全覆盖中的可能方案。最后介绍了精确覆盖问题在实际中的一些应用。



