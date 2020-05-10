#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

//priority_queue<ll, vector<ll>, greater<ll>> pq;
multiset<ll> mset;
int K, N;
ll prime[100100];
int main()
{
    scanf("%d %d", &K, &N);

    for (int i = 0; i < K; ++i) {
        scanf("%lld", &prime[i]);
    }

    sort(prime, prime + K);

    for (int i = 0; i < K; ++i) {
        mset.insert(prime[i]);
    }

    multiset<ll>::iterator iter;

    int a = N-1;
    int cnt = 0;
    ll maxi = -1;
    while (a--) {
        ll t = *mset.begin();

        mset.erase(mset.begin());
        for (int i = 0; i < K; ++i) {
            iter = mset.find(prime[i] * t);
            if (iter == mset.end()) {
                if (cnt < N) {
                    mset.insert(prime[i] * t);
                    ++cnt;
                    maxi = max(maxi, prime[i] * t);
                }
                else if (cnt >= N && prime[i] * t < maxi) {
                    mset.insert(prime[i] * t);
                    ++cnt;
                }
            }
        }
    }

    printf("%lld", *mset.begin());

    return 0;
}

/*
//koosaga's solution. koosaga is god
#include <cstdio>
#include <algorithm>
using namespace std;

int a[105],k,n;
int hum[100005];
int pt[105];

int main(){
    scanf("%d %d",&k,&n);
    for (int i=0; i<k; i++) {
        scanf("%d",&a[i]);
    }
    hum[0] = 1;
    hum[1] = a[0];
    for (int i=2; i<=n; i++) {
        hum[i] = 2e9;
        for (int j=0; j<k; j++) {
            while (hum[pt[j]] * a[j] <= hum[i-1]) {
                pt[j]++;
            }
            hum[i] = min(hum[i], hum[pt[j]] * a[j]);
        }
    }
    printf("%d",hum[n]);
}

*/