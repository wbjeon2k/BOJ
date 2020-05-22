#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

int M = 1000000007;
typedef long long ll;

struct fenwickTree {
    vector<ll> ftree;

    fenwickTree() {
        ftree.resize(200200, 0);
    }

    //pos starts from 1
    void add(int pos, int val) {
        while (pos < ftree.size()) {
            ftree[pos] += val;
            //ftree[pos] %= M;
            pos += (pos & -pos);
        }
    }

    ll sum(int pos) {
        ll ret = 0;
        while (pos > 0) {
            ret += ftree[pos];
            //ret %= M;
            pos &= (pos - 1);
        }
        return ret;
    }
};

int N;
bool visited[200200];

int main()
{
    scanf("%d", &N);
    fenwickTree F, IDX;

    memset(visited, 0, sizeof(visited));

    ll ret = 1;
    int cnt = 0;
    while (N--) {
        int t;
        scanf("%d", &t);

        ++t;
        F.add(t, t);
        IDX.add(t, 1);
        
        ll loweridx = (t >1) ? IDX.sum(t - 1) : 0;
        ll upperidx = IDX.sum(200001) - IDX.sum(t);
        ll lowerpsum = (t>1) ? F.sum(t - 1) : 0;
        ll upperpsum = F.sum(200001) - F.sum(t);
        ll cost = (upperpsum - upperidx * (ll)t) + (loweridx * (ll)t - lowerpsum) % M;
        if (cnt != 0) ret = ((ret % M) * (cost % M)) % M;
        ++cnt;
        //printf("cost %lld\n", cost);
    }

    printf("%lld", ret);

    return 0;
}
