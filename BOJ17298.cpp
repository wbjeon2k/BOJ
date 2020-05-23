#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
int input[1000100];
int ans[1000100];

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", &input[i + 1]);
    }

    input[0] = 0;

    memset(ans, -1, sizeof(ans));

    stack<int> s;

    for (int i = 1; i <= N; ++i) {
        while (!s.empty() && input[i] > input[s.top()]) {
            ans[s.top()] = input[i];
            s.pop();
        }
        s.push(i);
    }

    for (int i = 1; i <= N; ++i) {
        printf("%d", ans[i]);
        if (i != N) {
            printf(" ");
        }
    }
    printf("\n");


    return 0;

}
