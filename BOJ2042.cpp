#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct segtree {
    int n;
    vector<ll> tree;

    segtree(const vector<ll>& a) {
        n = a.size();
        tree.resize(4 * n);
        init(a, 0, n - 1, 1);
    }

    ll init(const vector<ll>& a, int left, int right, int node) {
        if (left == right) {
            tree[node] = a[left];
            return tree[node];
        }

        int mid = (left + right) / 2;

        ll linit = init(a, left, mid, node * 2);
        ll rinit = init(a, mid+1, right, node * 2 + 1);

        tree[node] = linit + rinit;
        return tree[node];
    }

    ll query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (left > nodeRight || right < nodeLeft) {
            return 0;
        }

        if (left <= nodeLeft && right >= nodeRight) {
            return tree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;

        ll lquery = query(left, right, node * 2, nodeLeft, nodeMid);
        ll rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);

        return (lquery + rquery);
    }

    ll update(ll value, int index, int node, int nodeLeft, int nodeRight) {
        if (index < nodeLeft || index > nodeRight) {
            return tree[node];
        }

        if (nodeLeft == nodeRight) {
            tree[node] = value;
            return tree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;
        tree[node] = update(value, index, node * 2, nodeLeft, nodeMid)
            + update(value, index, node * 2 + 1, nodeMid + 1, nodeRight);

        return tree[node];
    }

    ll querycall(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }

    ll updatecall(ll diff, int index) {
        return update(diff, index, 1, 0, n - 1);
    }
};

int N, M, K;
vector<ll> input;

int main()
{
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 0; i < N; ++i) {
        ll t = 0;
        scanf("%lld", &t);
        input.push_back(t);
    }

    segtree S(input);

    for (int i = 0; i < M + K; ++i) {
        ll a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        if (a == 1) {
            S.updatecall(c, b - 1);
        }
        if (a == 2) {
            printf("%lld\n", S.querycall(b - 1, c - 1));
        }
    }

    return 0;
}
