#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int day[30];
int price[30];
int cache[30];

void calc() {
    for (int i = 1; i <= 15; ++i) {
        cache[i + day[i]] = max(cache[i + day[i]], cache[i] + price[i]);
        cache[i + 1] = max(cache[i], cache[i + 1]);
    }
}


int main()
{
    int N;
    scanf("%d", &N);

    memset(day, 0, sizeof(day));
    memset(price, 0, sizeof(price));
    memset(cache, 0, sizeof(cache));

    for (int i = 1; i <= N; ++i) {
        scanf("%d %d", &day[i], &price[i]);
    }

    calc();
    printf("%d", cache[N + 1]);

    return 0;
}
