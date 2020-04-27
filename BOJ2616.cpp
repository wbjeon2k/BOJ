#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int cache[50050][5];
int sum[100050];
int input[50050];
int N,K,L;
int M = INT_MAX - 100;

int dp(int n, int k) {
    int& ret = cache[n][k];
    if (ret != -1) {
        return ret;
    }

    if (k == 0) {
        ret = 0;
        return ret;
    }

    if (n > N) {
        ret = -M;
        return ret;
    }

    int c1 = dp(n + 1, k);
    int c2 = ((n+L > N+1) ? -1 : dp(n + L , k - 1) + sum[n] - sum[n + L]);

    ret = (c1 > c2 ? c1 : c2);

    return ret;
}

int main()
{
    scanf("%d", &N);

    memset(cache, -1, sizeof(cache));
    sum[0] = 0;

    for (int i = 1; i <= N; ++i) {
        scanf("%d", &input[i]);
    }

    for (int i = N; i >= 1; --i) {
        sum[i] = sum[i + 1] + input[i];
    }

    scanf("%d", &L);
    int ans = dp(1, 3);

    printf("%d", ans);

    return 0;
}


/*
//koosaga's solution. O(N)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int a[50005], n, l;
int lmax[50005], rmax[50005];

int getsum(int s, int e){
    if(s < 0) return getsum(1, e);
    if(e > n) return getsum(s, n);
    return a[e] - a[s-1];
}

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        a[i] += a[i-1];
    }
    scanf("%d",&l);
    for(int i=1; i<=n; i++){
        lmax[i] = max(getsum(i-l+1, i), lmax[i-1]);
        rmax[n+1-i] = max(getsum(n+1-i, n+1-i+l-1), rmax[n+2-i]);
    }
    int ret = 0;
    for(int i=1; i+l<=n+1; i++){
        ret = max(ret, lmax[i-1] + rmax[i+l] + getsum(i, i+l-1));
    }
    printf("%d",ret);
}

*/