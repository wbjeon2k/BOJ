#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;


#define ll long long
bool visited[50][50];
int N;
double prob[5];

double p10[30];

ll power10(int a) {
    return p10[a];
}

double dfs(int x, int y, ll cnt, double carry) {
    //printf("x%d y%d\n", x, y);
    if (visited[x][y]) return 0;

    double ret = 0;
    if (cnt == N) {
        return ret = (double)carry;
    }

    visited[x][y] = true;

    ret += dfs(x + 1, y, cnt + 1, carry * prob[1]);
    ret += dfs(x - 1, y, cnt + 1, carry * prob[2]);
    ret += dfs(x, y - 1, cnt + 1, carry * prob[3]);
    ret += dfs(x, y + 1, cnt + 1, carry * prob[4]);

    visited[x][y] = false;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    cin >> N >> prob[1] >> prob[2]
        >> prob[3] >> prob[4];

    prob[1] /= 100;
    prob[2] /= 100;
    prob[3] /= 100;
    prob[4] /= 100;

    memset(visited, 0, sizeof(visited));
    double ans = dfs(20, 20, 0, 1);

    printf("%.9lf", ans);

    return 0;
}
