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