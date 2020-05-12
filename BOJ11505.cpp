#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct segtree {
    int n;
    ll M = 1000000007;
    vector<ll> tree;

    segtree(const vector<ll>& a) {
        n = a.size();
        tree.resize(4 * n);
        init(a, 0, n - 1, 1);
    }

    ll init(const vector<ll>& a, int left, int right, int node) {
        if (left == right) {
            tree[node] = a[left] % M;
            return tree[node];
        }

        int mid = (left + right) / 2;
        ll linit = init(a, left, mid, node * 2);
        ll rinit = init(a, mid+1, right, node * 2 + 1);

        tree[node] = (linit % M) * (rinit % M) % M;
        return tree[node];
    }

    ll query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (left > nodeRight || right < nodeLeft) {
            return 1;
        }

        if (left <= nodeLeft && right >= nodeRight) {
            return tree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;
        ll lquery = query(left, right, node * 2, nodeLeft, nodeMid) % M;
        ll rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight) % M;

        return (lquery * rquery) % M;
    }

    ll update(int value, int index, int node, int nodeLeft, int nodeRight) {
        if (index < nodeLeft || index > nodeRight) {
            return tree[node] % M;
        }

        if (nodeLeft == nodeRight) {
            tree[node] = value % M;
            return tree[node] % M;
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;

        tree[node] = (update(value, index, node * 2, nodeLeft, nodeMid) % M)
            * (update(value, index, node * 2 + 1, nodeMid + 1, nodeRight) % M) % M;

        return tree[node];  
    }

    ll querycall(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }

    ll updatecall(int value, int index) {
        return update(value, index, 1, 0, n - 1);
    }
};

int N, M, K;
vector<ll> input;

int main()
{
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < N; ++i) {
        ll t;
        scanf("%lld", &t);
        input.push_back(t);
    }

    segtree S(input);

    for (int i = 0; i < M + K; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        if (a == 1) {
            S.updatecall(c, b - 1);
        }
        else {
            printf("%lld\n", S.querycall(b - 1, c - 1));
        }
    }

    return 0;
}

