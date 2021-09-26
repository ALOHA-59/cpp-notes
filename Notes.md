# 算法

### 模板

#### 并查集

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Disjoint_set {
public:
    vector<int> parent;
    vector<int> rank;
    //记录连通分支和冗余连接的数量
    int set_cnt, res_edge;
    Disjoint_set(const int & n) : parent(vector<int>(n, 0)), rank(vector<int>(n, 0)), set_cnt(n), res_edge(0) {
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_parent(const int & x) {
        if(x == parent[x])
            return x;
        else
            return find_parent(parent[x]);
    }

    void merge(const int & x, const int & y) {
        int x_root = find_parent(x);
        int y_root = find_parent(y);
        
        if(x_root == y_root) {
            // 合并失败，说明成环，有多余的连接边，冗余连接加一
            res_edge++;
            return;
        }
            
        else if(x_root != y_root && rank[x] > rank[y])
            parent[y_root] = x_root;
        else if(x_root != y_root && rank[x] < rank[y])
            parent[x_root] = y_root;
        else {
            parent[y_root] = x_root;
            rank[x_root]++;
        }
        // 合并连通分支减一
        set_cnt--;
        return;
    }
};
```



#### 线段树

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
void buildTree(int array[],int arrayTree[],int node,int start,int end){
    if(start==end)
        arrayTree[node] = array[start];
    else{
        int leftNode = node * 2 + 1;
        int rightNode = node * 2 + 2;
        int mid = (start + end) / 2;
        buildTree(array,arrayTree,leftNode,start,mid);
        buildTree(array,arrayTree,rightNode,mid+1,end);
        arrayTree[node] = arrayTree[leftNode] + arrayTree[rightNode];   
    }
}
void updateTree(int array[],int arrayTree[],int node,int start,int end,int index,int value){
    if(end==start){
        array[index] = value;
        arrayTree[node] = value;
    }else{
        int mid = ( start + end ) / 2;
        int leftNode = node * 2 + 1;
        int rightNode = node * 2 + 2;
        if(index >= start && index <= mid){
            updateTree(array,arrayTree,leftNode,start,mid,index,value);
        }else{
            updateTree(array,arrayTree,rightNode,mid+1,end,index,value);
        }
        arrayTree[node] = arrayTree[leftNode] + arrayTree[rightNode];
    }
}
int queryTree(int arrayTree[],int node,int start,int end,int L,int R){
    if(L > end || R < start) return 0;
    else if(start>=L && end <= R) return arrayTree[node];
    else if(start == end) return arrayTree[node];
    else{
        int mid = (start + end) / 2;
        int leftNode = node * 2 + 1;
        int rightNode = node * 2 + 2;
        int sumLeft = queryTree(arrayTree,leftNode,start,mid,L,R);
        int sumRight = queryTree(arrayTree,rightNode,mid+1,end,L,R);
        return sumLeft + sumRight;
    }
}
int main(){
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    int arrayTree[1000] = {0};
    buildTree(array,arrayTree,0,0,9);
    for(int i=0;i<=32;i++) printf("arrayTree[%d] = %d \n",i,arrayTree[i]);
    cout << arrayTree[0] << endl;
    updateTree(array,arrayTree,0,0,9,0,10);
    for(int i=0;i<=9;i++) printf("array[%d] = %d \n",i,array[i]);
    cout << arrayTree[0] << endl;
    for(int i=0;i<=32;i++) printf("arrayTree[%d] = %d \n",i,arrayTree[i]);
    cout << queryTree(arrayTree,0,0,9,0,1);
}
```

### 题目及题解

#### 最长公共子序列

给定两个字符串 `text1` 和` text2`，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

* 解法

  动态规划。`m`，`n`分别为两个字符串的长度，创建`dp`数组，`dp[i][j]`表示两个字符串中从`0`开始，长度分别为`i`和`j`的字串的最长公共子序列长度，不难推出，当`text1[i-1]==text2[j-1]`时（这里是长度分别为`i`和`j`，对应的下标是`i-1`和`j-1`），`dp[i][j]=dp[i-1][j-1]+1`，而当`text1[i-1]≠text2[j-1]`时，`dp[i][j]=max(dp[i-1][j], dp[i][j-1])`。

  ```cpp
  class Solution {
  public:
      int longestCommonSubsequence(string text1, string text2) {
          int m = text1.size(), n = text2.size();
          vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
          for(int i = 1; i <= m; i++) {
              for(int j = 1; j <= n; j++) {
                  if(text1[i-1] == text2[j-1])
                      dp[i][j] = dp[i-1][j-1] + 1;
                  else
                      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
              }
          }
          return dp[m][n];
      }
  };
  ```

  

