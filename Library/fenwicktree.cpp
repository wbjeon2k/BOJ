#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct fenwickTree {
    vector<int> ftree;

    fenwickTree() {
        ftree.resize(1000001,0);
    }

    void add(int pos, int val) {
        while (pos < ftree.size()) {
            ftree[pos] += val;
            pos += pos & (-pos);
        }
    }

    int sum(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += ftree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }
};

int N;
int input[1001000];

int main()
{
    memset(input, 0, sizeof(input));
    scanf("%d", &N);

    fenwickTree F;

    for (int i = 1; i <= N; ++i) {
        int t;
        scanf("%d", &t);
        input[t] = i;
        //F.add(i, 1);
    }

    ll ret = 0;
    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);
        
        //printf("%d %d\n", F.sum(1000000), F.sum(input[t]));

        ret += (ll)(F.sum(1000000) - F.sum(input[t]));
        F.add(input[t], 1);
    }

    printf("%lld", ret);

    return 0;
}
