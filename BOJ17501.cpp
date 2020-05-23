#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
vector<int>input(200200,1000000);
vector<int>nlist;
int adjlist[200200][2];
int times[200200];


void dfs(int here, int minuscnt) {

    if (here == 0) return;

    if (here <= N) {
        if (minuscnt % 2 ==0) {
            times[here] = 1;
        }
        else {
            times[here] = -1;
        }
        return;
    }

    if (input[here] == -1) {
        int left = adjlist[here][0], right = adjlist[here][1];
        dfs(left, minuscnt);
        dfs(right, minuscnt + 1);
    }
    else {
        int left = adjlist[here][0], right = adjlist[here][1];
        dfs(left, minuscnt);
        dfs(right, minuscnt);
    }

    return;
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    cin >> N;
    nlist.resize(N);
    for (int i = 1; i <= N; ++i) {
        cin >> input[i];
        nlist[i - 1] = input[i];
    }

    for (int i = 1; i <= N - 1; ++i) {
        char a; int b, c;
        cin >> a >> b >> c;
        if (a == '-') {
            input[N + i] = -1;
            adjlist[N + i][0] = b;
            adjlist[N + i][1] = c;
        }
        if (a == '+') {
            input[N + i] = 1;
            adjlist[N + i][0] = b;
            adjlist[N + i][1] = c;
        }
    }

    dfs(2 * N - 1, 0);

    int cnt = 0;
    for (int i = 1; i <= N; ++i) {
        if (times[i] == -1) ++cnt;
    }

    sort(nlist.begin(), nlist.end());

    int a = 0;
    for (int i = 0; i < cnt; ++i) {
        a += (-1) * nlist[i];
    }
    for (int i = cnt; i < N; ++i) {
        a += nlist[i];
    }

    printf("%d\n", a);

    return 0;
}
