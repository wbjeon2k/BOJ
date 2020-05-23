#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int input[100100];
int N;

long long calc() {

    stack<ll> s;
    ll ret = 0;
    input[N] = 0;
    for (int i = 0; i <= N; ++i) {
        while (!s.empty() && input[s.top()] >= input[i]) {
            ll t = s.top();
            ll width = 0;
            s.pop();

            if (s.empty()) {
                width = i;
            }
            else {
                width = i - s.top() - 1;
            }
            ret = max(ret, input[t] * width);
        }

        s.push(i);
    }

    return ret;
}

int main()
{
    
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", &input[i]);
    }

    ll ans = calc();
    printf("%lld", ans);

    return 0;
}
