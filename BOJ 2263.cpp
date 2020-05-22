#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;


vector<int> inorder, postorder;


vector<int> interval(const vector<int>& v, int a, int b) {
    return vector<int>(v.begin() + a, v.begin() + b);
}

void preorder(int ins, int ine, int pos, int poe) {
    if (pos == poe || ins == ine) {
        printf("%d ", postorder[pos]);
        return;
    }

    if (pos > poe || ins > ine) {
        return;
    }

    int root = postorder[poe];

    int L = find(inorder.begin() + ins, inorder.begin() + ine, root) - inorder.begin() - ins;
    int N = ine - ins + 1;

    printf("%d ", root);

    
    preorder(ins, ins+L-1, pos, pos+L-1);
    preorder(ins+L+1, ine, pos+L, poe-1);

}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);
        inorder.push_back(t);
    }
    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);
        postorder.push_back(t);
    }

    preorder(0,N-1,0, N-1);

    return 0;
}

/*
//kks227's solution
#include <cstdio>
using namespace std;

int postorder[100000], inorder[100000], inPos[100000];

void preorder(int start, int end, int rootPos){
    if(start == end) return;
    int root = postorder[rootPos];
    printf("%d ", root+1);
    int pivot = inPos[root];
    preorder(start, pivot, rootPos-end+pivot);
    preorder(pivot+1, end, rootPos-1);
}

int main(){

    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", inorder+i);
        inorder[i]--;
        inPos[inorder[i]] = i;
    }
    for(int i=0; i<N; i++){
        scanf("%d", postorder+i);
        postorder[i]--;
    }
    preorder(0, N, N-1);

    return 0;
}

*/