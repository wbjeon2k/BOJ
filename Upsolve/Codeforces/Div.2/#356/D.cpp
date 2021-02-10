// codeforces
// https://codeforces.com/contest/680/problem/D

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int, int>
#define pll pair<ll, ll>
#define MAXI 100100
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 2;
// interactive: fflush(stdout);

ll n, k;

inline ll cube(ll a) { return a * a * a; }

ll bisearch(ll a) {
    ll lo, hi;
    lo = 1;
    hi = a;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;

        if (cube(mid) > a) {
            hi = mid;
        }
        else lo = mid;

    }
    return lo;
}

pll ans = { 0,0 };

void blocks(ll capacity, ll blk, ll csum) {
    if (capacity < 0) return;

    if (capacity == 0) {
        ans = max(ans, make_pair(blk, csum));
        return;
    }

    ll a, b, largest;
    largest = 1;
    while (cube(largest + 1) <= capacity) ++largest;
    //a = capacity - cube(largest);
    //b = cube(largest) - 1 - cube(largest - 1);
    blocks(capacity - cube(largest), blk + 1, csum + cube(largest));
    if (largest >= 1) blocks(cube(largest) - 1 - cube(largest - 1), blk + 1, csum + cube(largest - 1));
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    //cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    cin >> n;
    blocks(n, 0, 0);

    printf("%lld %lld\n", ans.first, ans.second);

    return 0;
}