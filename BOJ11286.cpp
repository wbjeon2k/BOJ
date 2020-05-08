#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, less<int>> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;



struct cmp {
    bool operator()(int t, int u) {
        if (abs(t) > abs(u)) {
            return true;
        }
        else if (abs(t) == abs(u)) {
            return t > u;
        }
        else {
            return false;
        }
    }
};
priority_queue<int, vector<int>, cmp> absHeap;

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);

        if (t == 0) {
            if (absHeap.empty()) {
                printf("0\n");
            }
            else {
                printf("%d\n", absHeap.top());
                absHeap.pop();
            }
        }
        else {
            absHeap.push(t);
        }
    }

    return 0;
}
