#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
int input[500500];
int output[500500];
stack<int> s;

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", &input[i + 1]);
    }

    input[0] = INT_MAX - 100000;

    s.push(0);

    for (int i = 1; i <= N; ++i) {
        while (input[i] > input[s.top()]) {
            s.pop();
        }

        output[i] = s.top();
        if (i<N && input[i]>=input[i + 1]) {
            s.push(i);
        }
    }

    for (int i = 1; i <= N; ++i) {
        printf("%d", output[i]);
        if (i != N) {
            printf(" ");
        }
    }

    return 0;
}
