//BOJ18286
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define MAXI 1000000000
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 4;

#define MOD 1000000007
ll N, M;

//state 의 p 번째 비트가 켜져있는가?
inline bool isOn(int state, int p){
    if ((state & (1 << p)) != 0) return true;
    return false;
}

//state0 와 state1이 2x2 정사각형을 만들면 false, 괜찮으면 true
inline bool chk(int state0, int state1){
    for (int i = 0; i < (M-1);++i){
        bool a, b, c, d;
        a = isOn(state0, i);
        b = isOn(state0, i + 1);
        c = isOn(state1, i);
        d = isOn(state1, i + 1);
        if ((a == b) && (a == c) && (a == d)) return false;
    }
    return true;
}

struct Matrix {
    ll mat_mod = MOD;
    int size = 32;
    ll mat[32][32];
};

Matrix mat_mult(Matrix A, Matrix B) {
    Matrix ans;
    int s = A.size;

    memset(ans.mat, 0, sizeof(ans.mat));

    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            for (int k = 0; k < s; ++k) {
                ans.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                ans.mat[i][j] %= MOD;
            }
        }
    }

    return ans;
}

Matrix mat_pow(Matrix A, ll p) {
    Matrix ans;
    memset(ans.mat, 0, sizeof(ans.mat));

    for (int i = 0; i < ans.size; ++i) {
        ans.mat[i][i] = 1;
    }

    while (p) {
        if (p % 2) ans = mat_mult(ans, A);
        A = mat_mult(A, A);
        p /= 2;
    }

    return ans;
}

Matrix path;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    cin >> N >> M;

    //full state: 0~(M-1) 번째 비트까지 다 차있는 상태.
    int full_state = (1 << M) - 1;
    for (int i = 0; i <= full_state;++i){
        for (int j = 0; j <= full_state;++j){
            if (chk(i, j)) path.mat[i][j] = 1;
            else
                path.mat[i][j] = 0;
        }
    }

    Matrix ans = mat_pow(path, N-1);

    ll total = 0;
    for (int i = 0;i<=full_state;++i){
        for (int j = 0;j<=full_state;++j){
            total += ans.mat[i][j];
            total %= MOD;
        }
    }

    printf("%lld\n", total);
    return 0;
}

//First trial, TLE

/*

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define MAXI 1000000000
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 4;

#define MOD 1000000007
int N, M;

//state 의 p 번째 비트가 켜져있는가?
inline bool isOn(int state, int p){
    if ((state & (1 << p)) != 0) return true;
    return false;
}

//state0 와 state1이 2x2 정사각형을 만들면 false, 괜찮으면 true
inline bool chk(int state0, int state1){
    for (int i = 0; i < (M-1);++i){
        bool a, b, c, d;
        a = isOn(state0, i);
        b = isOn(state0, i + 1);
        c = isOn(state1, i);
        d = isOn(state1, i + 1);
        if ((a == b) && (a == c) && (a == d)) return false;
    }
    return true;
}

ll dp[2][64];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    cin >> N >> M;

    //full state: 0~(M-1) 번째 비트까지 다 차있는 상태.
    int full_state = (1 << M) - 1;
    for (int i = 0; i <= full_state;++i){
        dp[0][i] = 1;
    }

    //dp(i,state): i번째 줄에서 state 형태로 끝나게 색칠할 수 있는 경우의 수
    //dp(i,state) = sum of dp(i-1, j) when chk(j,state) is true,
    //0 <= j <= 31.
    for (int i = 1; i < N;++i){
        if(i%2){
            for (int j = 0; j <= full_state;++j){
                dp[1][j] = 0;
                for (int k = 0; k <= full_state;++k){
                    if (chk(j, k)) {
                        dp[1][j] += dp[0][k];
                        dp[1][j] %= MOD;
                    }
                }
            }
        }
        else {
            for (int j = 0; j <= full_state; ++j) {
                dp[0][j] = 0;
                for (int k = 0; k <= full_state; ++k) {
                    if (chk(j, k)) {
                        dp[0][j] += dp[1][k];
                        dp[0][j] %= MOD;
                    }
                }
            }
        }
    }

    ll ans = 0;
    //N 번째 모든 state 경우의 수 합
    for (int i = 0;i<=full_state;++i){
        ans += dp[(N-1) % 2][i];
        ans %= MOD;
    }

    printf("%lld\n", ans);

    return 0;
}

*/
