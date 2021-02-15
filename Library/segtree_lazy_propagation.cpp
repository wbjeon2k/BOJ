//BOJ10999

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 1001000
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = LLONG_MAX/2;

typedef struct {
    ll val, lazy;
} segnode;

ll input[MAXI];

struct segtree {
    segnode tree[4 * MAXI];

    ll init(int node, int left, int right) {
        if (left == right) {
            tree[node].val = input[left];
            return tree[node].val;
        }
        int mid = (left + right) / 2;
        tree[node].val = init(node * 2, left, mid) + init(node * 2 + 1, mid + 1, right);
        return tree[node].val;
    }

    void propagate(int node, int nodel, int noder) {
        if (tree[node].lazy == 0) return;

        tree[node].val += tree[node].lazy * (noder - nodel + 1);

        if (nodel != noder) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }

    void range_update(int left, int right, int val, int node, int nodel, int noder) {
        propagate(node, nodel, noder);

        if (right < nodel || left > noder) return;

        if (left <= nodel && noder <= right) {
            tree[node].lazy += val;
            propagate(node, nodel, noder);
            return;
        }
        int mid = (nodel + noder) / 2;
        range_update(left, right, val, node * 2, nodel, mid);
        range_update(left, right, val, node * 2 + 1, mid + 1, noder);

        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    ll query(int left, int right, int node, int nodel, int noder) {
        propagate(node, nodel, noder);

        if (left > noder || right < nodel) return 0;

        if (left <= nodel && noder <= right) return tree[node].val;

        int mid = (nodel + noder) / 2;
        return query(left, right, node * 2, nodel, mid) + query(left, right, node * 2 + 1, mid + 1, noder);
    }
};

int n, m, k;
segtree SEG;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> input[i + 1];

    SEG.init(1, 1, n);

    int s, e, v;
    for (int i = 0; i < m + k; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            cin >> s >> e >> v;
            SEG.range_update(s, e, v, 1, 1, n);
        }
        else {
            cin >> s >> e;
            printf("%lld\n", SEG.query(s, e, 1, 1, n));
        }
    }


    return 0;
}