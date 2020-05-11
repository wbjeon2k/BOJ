#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct segMax {
    int n;
    vector<int> tree;

    segMax(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        init(a, 0, n - 1, 1);
    }

    int init(const vector<int>& a, int left, int right, int node) {
        if (left == right) {
            tree[node] = a[left];
            return tree[node];
        }

        int mid = (left + right) / 2;

        int linit = init(a, left, mid, node * 2);
        int rinit = init(a, mid + 1, right, node * 2 + 1);

        tree[node] = max(linit, rinit);

        return tree[node];
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (left > nodeRight || right < nodeLeft) {
            return -(INT_MAX - 10000);
        }

        if (left <= nodeLeft && right >= nodeRight) {
            return tree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;
        int lquery = query(left, right, node * 2, nodeLeft, nodeMid);
        int rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);

        return max(lquery, rquery);
    }

    int querycall(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

struct segMin {
    int n;
    vector<int> tree;

    segMin(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        init(a, 0, n - 1, 1);
    }

    int init(const vector<int>& a, int left, int right, int node) {
        if (left == right) {
            tree[node] = a[left];
            return tree[node];
        }

        int mid = (left + right) / 2;

        int linit = init(a, left, mid, node * 2);
        int rinit = init(a, mid + 1, right, node * 2 + 1);

        tree[node] = min(linit, rinit);

        return tree[node];
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (left > nodeRight || right < nodeLeft) {
            return (INT_MAX - 10000);
        }

        if (left <= nodeLeft && right >= nodeRight) {
            return tree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;
        int lquery = query(left, right, node * 2, nodeLeft, nodeMid);
        int rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);

        return min(lquery, rquery);
    }

    int querycall(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

vector<int> input;
int N, M;

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);
        input.push_back(t);
    }

    segMax maxi(input); segMin mini(input);

    for (int i = 0; i < M; ++i) {
        int s, e;
        scanf("%d %d", &s, &e);

        printf("%d %d\n", mini.querycall(s - 1, e - 1), maxi.querycall(s - 1, e - 1));
    }

    return 0;
}
