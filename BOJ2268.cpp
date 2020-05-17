#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct fenwickTree {
    vector<ll> ftree;

    fenwickTree() {
        ftree.resize(1000001,0);
    }

    void add(int pos, ll val) {
        while (pos < ftree.size()) {
            ftree[pos] += val;
            pos += pos & (-pos);
        }
    }

    ll sum(int pos) {
        ll ret = 0;
        while (pos > 0) {
            ret += ftree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }
};

int N, M;
ll input[1001000];

int main()
{
    scanf("%d %d", &N, &M);

    fenwickTree F;
    memset(input, 0, sizeof(input));
    while (M--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a==1) {
            ll diff = c - input[b];
            input[b] = c;
            F.add(b , diff);
        }
        else {
            if (b > c) swap(b, c);
            ll ans = F.sum(c) - F.sum(b-1);
            printf("%lld\n", ans);
        }
    }

    return 0;
}
