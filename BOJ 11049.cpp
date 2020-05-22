#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

#define pii pair<int,int> 

using namespace std;

struct MAT {
    pii size;
    long long mnum = -1;
};

long long matmult(pii a, pii b) {
    return (a.first * a.second * b.second);
}

MAT cache[505][505];
pii input[505];

MAT dp(int a, int b) {
    MAT& ret = cache[a][b];
    if (ret.mnum != -1) {
        return ret;
    }

    if (a == b) {
        ret.size.first = input[a].first;
        ret.size.second = input[a].second;
        ret.mnum = 0;
        return ret;
    }

    ret.mnum = LLONG_MAX;
    
    for (int i = a; i < b; ++i) {
        MAT lsearch = dp(a, i);
        MAT rsearch = dp(i + 1, b);
        int m = matmult(lsearch.size, rsearch.size);
        if (ret.mnum > lsearch.mnum + rsearch.mnum + m) {
            ret.mnum = lsearch.mnum + rsearch.mnum + m;
            ret.size = make_pair(lsearch.size.first, rsearch.size.second);
        }
    }

    return ret;
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        input[i + 1].first = a;
        input[i + 1].second = b;

    }

    MAT ans = dp(1, N);
    printf("%lld", ans.mnum);

    return 0;
}
