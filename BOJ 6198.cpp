#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int N;
int bld[80080];

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &bld[i]);
    }

    stack<int> s;
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        while (!s.empty() && bld[s.top()] <= bld[i]) {
            s.pop();
        }
        ans += s.size();
        s.push(i);
    }

    printf("%lld", ans);

    return 0;
}

//https://contest.usaco.org/NOV06.htm