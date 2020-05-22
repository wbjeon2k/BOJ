#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int input[105][105];
int cache[105][105][100];

string word;
int N, M, K;

bool isinside(int a, int b) {
    if (a<1 || a>N || b<1 || b>M) return false;
    return true;
}

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int dfs(int a, int b, int cnt) {
    int& ret = cache[a][b][cnt];

    if (ret != -1) return ret;

    if (cnt >= word.size()) return ret = -1;

    if (word[cnt] != input[a][b]) return ret = 0;

    if (cnt + 1 == word.size()) return ret = 1;

    int tmp = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j <= K; ++j) {
            int nx = a + dx[i] * j, ny = b + dy[i]*j;
            if (isinside(nx, ny)) tmp += dfs(nx, ny, cnt + 1);
        }
    }

    return ret = tmp;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    memset(cache, -1, sizeof(cache));

    cin >> N >> M >> K;

    for (int i = 1; i <= N; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= M; ++j) {
            input[i][j] = s[j - 1];
        }
    }

    cin >> word;

    int ret = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (input[i][j] == word[0]) {
                ret += dfs(i, j, 0);
            }
        }
    }

    printf("%d", ret);

    return 0;
}
