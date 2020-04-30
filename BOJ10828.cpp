#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

stack<int> s;

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        string tmp;
        int t;
        cin >> tmp;
        if (tmp == "push") {
            scanf("%d", &t);
            s.push(t);
        }
        else if (tmp == "pop") {
            if (s.empty()) {
                printf("-1\n");
            }
            else {
                printf("%d\n", s.top());
                s.pop();
            }
        }
        else if (tmp == "size") {
            printf("%d\n", s.size());
        }
        else if (tmp == "empty") {
            printf("%d\n", (s.empty() ? 1 : 0));
        }
        else if (tmp == "top") {
            if (s.empty()) {
                printf("-1\n");
            }
            else printf("%d\n", s.top());
        }
    }

    return 0;
}


/*
//rlash00n's solution. without STL
#include <stdio.h>

int main() {
    int n;
    int stack[10000];
    scanf("%d", &n);
    int cur = -1, x;
    for (int i = 0; i < n; i++) {
        char cmd[6];
        scanf("%s", &cmd);
        if (cmd[0] == 'p') {
            if (cmd[1] == 'u') {
                scanf("%d", &x);
                stack[++cur] = x;
            }
            if (cmd[1] == 'o') {
                if (cur == -1) printf("-1\n");
                else printf("%d\n", stack[cur--]);
            }
        }
        if (cmd[0] == 's') {
            printf("%d\n", cur + 1);
        }
        if (cmd[0] == 'e') {
            if (cur == -1) printf("1\n");
            else printf("0\n");
        }
        if (cmd[0] == 't') {
            if (cur == -1) printf("-1\n");
            else printf("%d\n", stack[cur]);
        }
    }
}

*/