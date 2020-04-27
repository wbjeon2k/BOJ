#define _CRT_SECURE_NO_WARNINGS

#define ll long long
#include <bits/stdc++.h>

using namespace std;

ll raw[50];
ll cache[50];

void calcraw() {
    //normal tiling
    raw[0] = 0;
    raw[1] = 1;
    raw[2] = 3;
    for(int i=3;i<31;++i){
        
        raw[i] = 2 * raw[i - 2] + raw[i - 1];
    }
}

void calcdp() {
    //symmetrical tiling
    cache[0] = 1;
    cache[1] = 1;
    cache[2] = 3;
    cache[3] = 1;

    for (int i = 4; i < 31; ++i) {
        cache[i] = 2*cache[i-4] + cache[i-2] ;
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    calcraw();
    calcdp();

    //(general-sym)/2 + sym;
    ll ans = (raw[N] + cache[N]) / 2;
    printf("%lld", ans);

    return 0;
}
