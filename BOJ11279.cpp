#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, less<int>> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;


int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);

        if (t == 0) {
            if (maxHeap.empty()) {
                printf("0\n");
            }
            else {
                printf("%d\n", maxHeap.top());
                maxHeap.pop();
            }
        }
        else {
            maxHeap.push(t);
        }
    }

    return 0;
}
