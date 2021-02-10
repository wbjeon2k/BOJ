// codeforces
//https://codeforces.com/contest/680/problem/E

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

int board[505][505];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

ll ans = 0;
int component[200200], csize[200200];

inline bool isinside(int x, int y) {
    if (x<1 || x>n || y<1 || y>n) return false;
    return true;
}

void printboard() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int dfs(int x, int y, int comp) {
    int ret = 0;
    board[x][y] = comp;
    for (int i = 0; i < 4; ++i) {
        int nx, ny;
        nx = x + dx[i];
        ny = y + dy[i];
        if (!isinside(nx, ny)) continue;
        if (board[nx][ny] != -1) continue;
        board[nx][ny] = comp;
        ret += dfs(nx, ny, comp);
    }
    ret++;
    return ret;
}

void findcc() {
    int comp = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (board[i][j] == -1) {
                ++comp;
                int ccsize = dfs(i, j, comp);
                csize[comp] = ccsize;
            }

        }
    }
}

set<int> st;

int tsize = 0;
void findadj(int x, int y) {
    st.clear();
    vector<int> visited;
    tsize = 0;
    //top edge
    for (int i = y; i < y + k; ++i) {
        if (!isinside(x - 1, i)) continue;
        if (board[x - 1][i]) {
            visited.push_back(board[x - 1][i]);
        }
    }
    //bottom edge
    for (int i = y; i < y + k; ++i) {
        if (!isinside(x + k, i)) continue;
        if (board[x + k][i]) {
            visited.push_back(board[x + k][i]);
        }
    }
    //left edge
    for (int i = x; i < x + k; ++i) {
        if (!isinside(i, y - 1)) continue;
        if (board[i][y - 1]) {
            visited.push_back(board[i][y - 1]);
        }
    }
    //right edge
    for (int i = x; i < x + k; ++i) {
        if (!isinside(i, y + k)) continue;
        if (board[i][y + k]) {
            visited.push_back(board[i][y + k]);
        }
    }

    sort(visited.begin(), visited.end());

    if (visited.size() == 0) {
        tsize = 0;
        return;
    }

    tsize = csize[visited[0]];
    int last = visited[0];
    for (int i = 1; i < visited.size(); ++i) {
        if (visited[i] == last) continue;
        last = visited[i];
        tsize += csize[visited[i]];
    }
    /*
    for(auto iter = st.begin() ; iter != st.end();++iter){
        tsize += csize[*iter];
    }
    */
}

void findinside(int x, int y) {
    for (int i = x; i < x + k; ++i) {
        for (int j = y; j < y + k; ++j) {
            if (board[i][j] == 0) continue;
            csize[board[i][j]]--;
        }
    }
}

void restore(int x, int y) {
    for (int i = x; i < x + k; ++i) {
        for (int j = y; j < y + k; ++j) {
            if (board[i][j] == 0) continue;
            csize[board[i][j]]++;
        }
    }
}

void findans() {

    for (int i = 1; i + k <= n + 1; ++i) {
        findinside(i, 1);
        for (int j = 1; j + k <= n + 1; ++j) {
            findadj(i, j);
            ans = max(ans, k * k + tsize);
            if (j + k != n + 1) {
                for (int x = i; x < i + k; ++x) {
                    csize[board[x][j]]++;
                    csize[board[x][j + k]]--;
                }
            }
        }
        restore(i, n - k + 1);
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; ++j) {
            if (s[j - 1] == '.') board[i + 1][j] = -1;
            else board[i + 1][j] = 0;
        }
    }
    findcc();
    findans();


    printf("%lld\n", ans);


    return 0;
}
