#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int adjMat[1010][1010];

vector<int> circuit;
int N;

void getCircuit(int here, vector<int>& c) {
    for (int i = 1; i <= N; ++i) {
        while (adjMat[here][i] > 0) {
            adjMat[here][i]--;
            adjMat[i][here]--;
            getCircuit(i, c);
        }
    }
    c.push_back(here);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> adjMat[i][j];
        }
    }

    getCircuit(1, circuit);

    if (circuit.front() != circuit.back()) {
        printf("-1\n");
    }
    else {
        for (int i = 0; i < circuit.size(); ++i) {
            printf("%d ", circuit[i]);
        }
    }

    return 0;
}
