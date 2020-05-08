#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int T, N;

int main()
{
    scanf("%d", &T);

    for(int j=0;j<T;++j) {
        scanf("%d", &N);

        priority_queue<int, vector<int>, less<int>> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;

        printf("%d\n", (N / 2) + (N % 2));

        for (int i = 0; i < N; ++i) {
            int t;
            scanf("%d", &t);

            if (maxHeap.size() == minHeap.size()) {
                maxHeap.push(t);
            }
            else {
                minHeap.push(t);
            }

            if (!maxHeap.empty() && !minHeap.empty() && minHeap.top() < maxHeap.top()) {
                int a, b;
                a = minHeap.top();
                b = maxHeap.top();

                minHeap.pop(); maxHeap.pop();

                minHeap.push(b);
                maxHeap.push(a);
            }

            if ((i+1) % 2 == 1) {
                printf("%d ", maxHeap.top());
            }
            if ((i + 1) % 20 == 0) {
                printf("\n");
            }
        }
        printf("\n");

    }
}
