#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[505][505];
char input[505][505];
int cache[505][505];

int N, M;

bool isinside(int a, int b) {
    if (a<1 || a > N || b < 1 || b > M) return false;
    return true;
}

int chk = 0;

int dfs(int a, int b) {
    if (!isinside(a, b)) {
        ++chk;
        return 1;
    }

    int& ret = cache[a][b];

    if (ret != -1) return ret;

    ret = 0;

    if (input[a][b] == 'U') {
        return ret = dfs(a - 1, b);
    }
    if (input[a][b] == 'R') {
        return ret = dfs(a, b + 1);
    }
    if (input[a][b] == 'D') {
        return ret = dfs(a + 1, b);
    }
    if (input[a][b] == 'L') {
        return ret = dfs(a, b - 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(input, 0, sizeof(input));
    memset(cache, -1, sizeof(cache));

    ifstream cin;
    cin.open("input.txt");

    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < M; ++j) {
            input[i][j + 1] = s[j];
        }
    }

    int cnt = 0;
    int loop = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cnt += dfs(i, j);
        }
    }

    printf("%d", cnt);
    printf("%d\n", chk);

    return 0;
}


/*
//first attempt. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[505][505];
char input[505][505];

int N, M;

bool isinside(int a, int b) {
    if (a<1 || a > N || b < 1 || b > M) return false;
    return true;
}

int dfs(int a, int b) {
    if (!isinside(a, b)) return 1;

    visited[a][b] = true;
    if (input[a][b] == 'U') {
        if (visited[a - 1][b]) return 0;
        else return dfs(a - 1, b);
    }
    if (input[a][b] == 'R') {
        if (visited[a][b+1]) return 0;
        else return dfs(a, b+1);
    }
    if (input[a][b] == 'D') {
        if (visited[a + 1][b]) return 0;
        else return dfs(a + 1, b);
    }
    if (input[a][b] == 'L') {
        if (visited[a][b-1]) return 0;
        else return dfs(a, b-1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(visited, 0, sizeof(visited));
    memset(input, 0, sizeof(input));

    //ifstream cin;
    //cin.open("input.txt");

    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < M; ++j) {
            input[i][j+1] = s[j];
        }
    }

    int cnt = 0;
    int loop = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            memset(visited, 0, sizeof(visited));
            cnt += dfs(i, j);
            //printf("%d\n", loop);
            //++loop;
        }
    }

    printf("%d", cnt);

    return 0;
}

*/