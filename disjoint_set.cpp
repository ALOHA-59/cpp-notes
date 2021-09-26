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