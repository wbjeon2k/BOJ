//BOJ1915

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 1001000
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = LLONG_MAX/4;

int board[1010][1010];
int cache[1010][1010];

int n, m;

int dp(int x, int y) {
    int& ret = cache[x][y];
    if (ret != -1) return ret;

    if (!board[x][y]) {
        ret = 0;
        return ret;
    }

    int a, b, c;
    a = dp(x - 1, y);
    b = dp(x, y - 1);
    c = dp(x - 1, y - 1);

    ret = min({ a, b, c }) + 1;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j) {
            board[i][j] = (s[j - 1] - '0');
        }
    }

    memset(cache, -1, sizeof(cache));

    for (int i = 0; i < 1010; ++i) {
        cache[i][0] = 0;
        cache[0][i] = 0;
    }

    int ans = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ans = max(ans, dp(i, j));
        }
    }

    printf("%d\n", ans * ans);

    return 0;
    
}