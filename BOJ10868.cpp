#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int Max = INT_MAX - 10000;

struct seg {
    int n;
    vector<int> tree;

    seg(const vector<int>& a) {
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

    int query(int left, int right, int node, int nodeleft, int noderight) {
        if (right < nodeleft || left > noderight) {
            return Max;
        }

        if (left <= nodeleft && right >= noderight) {
            return tree[node];
        }

        int nodemid = (nodeleft + noderight) / 2;

        int lquery, rquery;
        lquery = query(left, right, node * 2, nodeleft, nodemid);
        rquery = query(left, right, node * 2 + 1, nodemid+1, noderight);

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

    //sort(input.begin(), input.end());

    seg S(input);

    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%d\n", S.querycall(a-1, b-1));
    }
}
