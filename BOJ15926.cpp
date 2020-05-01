#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
string input;
int nlist[200200];
stack<int> s;

int main()
{
    scanf("%d", &N);
    cin >> input;

    for (int i = 0; i < N;++i) {
        if (input[i] == '(') {
            s.push(i);
        }
        else {
            if (!s.empty()) {
                nlist[i] = 1;
                nlist[s.top()] = 1;
                s.pop();
            }
        }
    }

    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (nlist[i] == 1) {
            ++cnt;
            ans = max(ans, cnt);
        }
        else {
            cnt = 0;
        }
    }

    printf("%d", ans);

    return 0;
}

/*

//csehydrogen's solution

#include <cstdio>
#include <algorithm>
char a[200001];
int s[200001], st;
int main() {
    int n, ans = 0;
    scanf("%d%s", &n, a);
    s[st++] = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == '(') {
            s[st++] = i;
        } else {
            --st;
            if (st == 0) {
                s[st++] = i;
            } else {
                ans = std::max(ans, i - s[st - 1]);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}


*/