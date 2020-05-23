#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, less<int>> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;


int main()
{
    int T, N;
    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d", &N);

        if (maxHeap.size() == minHeap.size()) {
            maxHeap.push(N);
        }
        else {
            minHeap.push(N);
        }

        if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
            int a, b;
            a = minHeap.top();
            b = maxHeap.top();

            minHeap.pop();
            maxHeap.pop();

            minHeap.push(b);
            maxHeap.push(a);
        }

        printf("a%d\n", maxHeap.top());
    }

    return 0;
}
