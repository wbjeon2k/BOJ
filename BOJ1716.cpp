#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

//#include <bitset>

typedef long long ll;

vector<ll> sieve;
vector<ll> sqsieve;
bitset<1001000> bs;

void gensieve() {
    bs.set();
    bs[0] = 0;
    bs[1] = 0;
    for (ll i = 2; i <= 1000000; ++i) {
        if (bs[i]) {
            for (ll j = i * i; j <= 1000000; j += i) {
                bs[j] = 0;
            }
            sieve.push_back(i);
        }
    }
}

ll MIN, MAX;

bitset<1001000> chkrange;

int main()
{
    scanf("%lld %lld", &MIN, &MAX);

    gensieve();
    for (int i = 0; i < sieve.size(); ++i) {
        sqsieve.push_back(sieve[i] * sieve[i]);
    }

    int cnt = 0;
    chkrange.set();
    for (int i = 0; i < sqsieve.size(); ++i) {
        if (sqsieve[i] > MAX) break;

        ll sp = (MIN / sqsieve[i])*sqsieve[i];
        if (sp < MIN) sp += sqsieve[i];
        sp -= MIN;
        //printf("%d\n", sp);

        for (ll j = sp; j <= MAX - MIN; j += sqsieve[i]) {
            if (chkrange[j]) {
                chkrange[j] = 0;
                //printf("%d\n", j);
                ++cnt;
            }
        }
    }

    printf("%d", MAX - MIN - cnt + 1);
    return 0;
}


/*
//wookje's solution. without explicit sieve. built-in
#include <stdio.h>
typedef long long ll;

bool chk[1000001], aux[1000001];

int main() {
    ll a, b;
    scanf("%lld %lld", &a, &b);

    int ans = b - a + 1;
    for (ll i = 2; i*i <= b; i++) {
        if (aux[i]) continue;
        for (ll j = i; j*j <= b; j += i) aux[j] = 1;
        for (ll j = ((a-1)/(i*i)+1)*i*i; j <= b; j += i*i)
            if (!chk[j - a]) chk[j - a] = 1, ans--;
    }

    printf("%d", ans);

    return 0;
}
*/