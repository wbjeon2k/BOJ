


#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

int Mod = 9901;
int dp[100010][3];

void calc() {
    for (int i = 2; i < 100010; ++i) {
        dp[i][0] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][0]) % Mod;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][2])%Mod;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][1])%Mod;
    }
}

int ans(int n) {
    return (dp[n][0] + dp[n][1] + dp[n][2]) % Mod;
}

int main()
{
    
    dp[0][1] = 0;
    dp[0][2] = 0;
    dp[0][0] = 1;

    dp[1][1] = 1;
    dp[1][2] = 1;
    dp[1][0] = 1;

    calc();

    int N;
    scanf("%d", &N);
    printf("%d", ans(N));

    return 0;
}

/*

*/