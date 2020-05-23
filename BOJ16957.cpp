#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int cache[505][505];
int input[505][505];
int R, C;

vector<int> anslist(300300, 0);

int dx[8] = { 1,1,1,-1,-1,-1,0,0 };
int dy[8] = { 1,0,-1,1,0,-1,1,-1 };

bool isinside(int a, int b) {
    if (a<1 || a>R || b<1 || b>C) return false;
    return true;
}

int dfs(int a, int b) {
    int& ret = cache[a][b];

    if (ret != -1) return ret;

    int minx ,miny;
    int tmp = INT_MAX;
    for (int i = 0; i < 8; ++i) {
        int nx = a + dx[i], ny = b + dy[i];
        if (isinside(nx, ny) && tmp > input[nx][ny]) {
            tmp = input[nx][ny];
            minx = nx, miny = ny;
        }
    }

    if (tmp > input[a][b]) {
        ret = input[a][b];
        anslist[ret] += 1;
        return ret;
    }
    else {
        ret = dfs(minx, miny);
        anslist[ret] += 1;
        return ret;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    //ifstream cin;
    //cin.open("input.txt");

    cin >> R >> C;

    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            cin >> input[i][j];
        }
    }

    memset(cache, -1, sizeof(cache));
    
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            dfs(i, j);
        }
    }

    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            printf("%d ", anslist[input[i][j]]);
        }
        printf("\n");
    }
    
    return 0;
}
