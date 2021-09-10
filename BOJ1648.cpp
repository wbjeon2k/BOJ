//https://www.acmicpc.net/problem/1648

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int, int>
#define pll pair<ll, ll>
#define MAXI 1000000000
#define cplx complex<double>
#define MOD 9901
const double PI = acos(-1);
const ll INF = INT_MAX / 4;

int N, M;
int cache[300][2 << 15];

int full_state;

int dp(int i, int state) {

    if (i == N * M && state == 0) {
        return 1;
    }
    if (i >= (N * M)) {
        return 0;
    }
    if (state > full_state) {
        return 0;
    }

    int &ret = cache[i][state];
    if (ret != -1) return ret;

    ret = 0;

    if(state & 1){
        ret = dp(i + 1, state >> 1);
    }
    if (!(state & 1)) {
        ret += dp(i + 1, (state >> 1) | (1 << (M - 1)));
        ret %= MOD;
    }
    if ((i % M != M - 1) && !(state & 3)) {
        ret += dp(i + 1, (state >> 1) | 1);
        ret %= MOD;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    memset(cache, -1, sizeof(cache));

    cin >> N >> M;
    full_state = (1 << M) - 1;

    printf("%d\n", dp(0,0) % MOD);

    return 0;
}

/*

//koosaga is god

#include <cstdio>

int main(){
	int dp[15][15]  = {};
	dp[2][1] = 1;
dp[2][2] = 2;
dp[3][2] = 3;
dp[4][1] = 1;
dp[4][2] = 5;
dp[4][3] = 11;
dp[4][4] = 36;
dp[5][2] = 8;
dp[5][4] = 95;
dp[6][1] = 1;
dp[6][2] = 13;
dp[6][3] = 41;
dp[6][4] = 281;
dp[6][5] = 1183;
dp[6][6] = 6728;
dp[7][2] = 21;
dp[7][4] = 781;
dp[7][6] = 1826;
dp[8][1] = 1;
dp[8][2] = 34;
dp[8][3] = 153;
dp[8][4] = 2245;
dp[8][5] = 4923;
dp[8][6] = 8673;
dp[8][7] = 5567;
dp[8][8] = 8605;
dp[9][2] = 55;
dp[9][4] = 6336;
dp[9][6] = 6109;
dp[9][8] = 9894;
dp[10][1] = 1;
dp[10][2] = 89;
dp[10][3] = 571;
dp[10][4] = 8160;
dp[10][5] = 7703;
dp[10][6] = 5208;
dp[10][7] = 7147;
dp[10][8] = 1695;
dp[10][9] = 2331;
dp[10][10] = 5606;
dp[11][2] = 144;
dp[11][4] = 1700;
dp[11][6] = 1778;
dp[11][8] = 8111;
dp[11][10] = 8159;
dp[12][1] = 1;
dp[12][2] = 233;
dp[12][3] = 2131;
dp[12][4] = 6987;
dp[12][5] = 5362;
dp[12][6] = 1795;
dp[12][7] = 5631;
dp[12][8] = 2296;
dp[12][9] = 8412;
dp[12][10] = 5570;
dp[12][11] = 4270;
dp[12][12] = 885;
dp[13][2] = 377;
dp[13][4] = 7410;
dp[13][6] = 7093;
dp[13][8] = 7818;
dp[13][10] = 7982;
dp[13][12] = 1742;
dp[14][1] = 1;
dp[14][2] = 610;
dp[14][3] = 7953;
dp[14][4] = 6182;
dp[14][5] = 5606;
dp[14][6] = 6289;
dp[14][7] = 8010;
dp[14][8] = 7183;
dp[14][9] = 1364;
dp[14][10] = 6167;
dp[14][11] = 3727;
dp[14][12] = 3761;
dp[14][13] = 3971;
dp[14][14] = 990;
int n, m;
scanf("%d %d",&n,&m);
if(n < m) n^=m^=n^=m;
printf("%d",dp[n][m]);
}

}