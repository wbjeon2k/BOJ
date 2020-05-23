#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

queue<int> q;
vector<int> ans;

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; ++i) {
        q.push(i + 1);
    }

    while (!q.empty()) {
        for (int i = 0; i < K-1; ++i) {
            int t = q.front();
            q.pop();
            q.push(t);
        }
        ans.push_back(q.front());
        q.pop();
    }


    printf("<");
    for (int i = 0; i < ans.size(); ++i) {
        printf("%d", ans[i]);
        if (i != ans.size() - 1) {
            printf(", ");
        }
    }
    printf(">");

    return 0;
}
