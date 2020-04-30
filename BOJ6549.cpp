#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll sweep(vector<ll> hlist) {
    stack<ll> hstack;
    hlist.push_back(0);

    ll ret = -1;

    for (int i = 0; i < hlist.size(); ++i) {

        while (!hstack.empty() && hlist[hstack.top()] >= hlist[i]) {
            ll t = hstack.top();
            hstack.pop();

            ll width = -1;

            if (hstack.empty()) {
                width = i;
            }
            else {
                width = i - hstack.top() - 1;
            }
            ret = max(ret, hlist[t] * width);
        }

        hstack.push(i);
    }

    return ret;
}

int main()
{
    while (1) {
        int N;
        scanf("%d", &N);

        if (N == 0) {
            break;
        }

        vector<ll> hlist;
        for (int i = 0; i < N; ++i) {
            int t;
            scanf("%d", &t);
            hlist.push_back(t);
        }

        printf("%lld\n", sweep(hlist));
    }

    return 0;
}
