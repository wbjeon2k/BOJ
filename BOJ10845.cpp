#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

queue<int> q;

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        string s;
        int t;
        cin >> s;
        if (s == "push") {
            scanf("%d", &t);
            q.push(t);
        }
        else if (s == "pop") {
            if (q.empty()) {
                printf("-1\n");
            }
            else {
                printf("%d\n", q.front());
                q.pop();
            }
        }
        else if (s == "empty") {
            if (q.empty()) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
        }
        else if (s == "front") {
            if (q.empty()) {
                printf("-1\n");
            }
            else {
                printf("%d\n", q.front());
            }
        }
        else if (s == "back") {
            if (q.empty()) {
                printf("-1\n");
            }
            else {
                printf("%d\n", q.back());
            }
        }
        else if (s == "size") {
            printf("%d\n", q.size());
        }
    }

    return 0;
}
