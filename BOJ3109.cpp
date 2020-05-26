#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int R, C;
bool visited[10010][505];
string input[10010];


bool isInside(int x, int y) {
    if (x<1 || x>R || y < 1 || y>C) return false;
    return true;
}

bool isPossible(int x, int y) {
    if (isInside(x, y) && !visited[x][y] && input[x][y] != 'x') return true;
    else return false;
}

bool dfs(int x, int y) {
    visited[x][y] = true;
    if (y == 1) {
        return true;
    }

    //bool ret = false;

    if (isPossible(x - 1, y - 1) && dfs(x - 1, y - 1)) return true;

    if (isPossible(x, y - 1) && dfs(x, y - 1)) return true;

    if (isPossible(x + 1, y - 1) && dfs(x + 1, y - 1)) return true;

    /*
    if (isPossible(x-1, y-1)) ret = dfs(x - 1, y - 1);
    if (ret) return true;

    if (isPossible(x, y - 1)) ret = dfs(x, y - 1);
    if (ret) return true;

    if (isPossible(x + 1, y - 1)) ret = dfs(x + 1, y - 1);
    if (ret) return true;
    */

    //visited[x][y] = false;
    return false;   
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    cin >> R >> C;

    for (int i = 1; i <= R; ++i) {
        string s = "0";
        string t;
        cin >> t;
        input[i] = s + t;
    }

    int ans = 0;
    for (int i = 1; i <= R; ++i) {
        ans += dfs(i, C);
    }

    printf("%d", ans);
    return 0;
}
