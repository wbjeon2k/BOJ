#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

string input;
vector<int> laser;
stack<int> s;

int main()
{
    cin >> input;
    int ans = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == '(') {
            s.push(i);
        }
        else {
            if (s.top() == i - 1) {
                laser.push_back(i - 1);
            }
            else {
                int t = 1;
                for (int j = 0; j < laser.size(); ++j) {
                    if (s.top() < laser[j] && laser[j] < i) {
                        ++t;
                    }
                }
                ans += t;
            }
            s.pop();
        }
    }

    printf("%d", ans);

    return 0;
}


/*
//kks227's solution.
#include <cstdio>
using namespace std;

int main(){
    char c, prev = '.';
    int sum = 0, cnt = -1;
    while((c=getchar())>'\n'){
        if(c=='(') cnt++;
        else{
            if(prev=='(') sum += cnt;
            else sum++;
            cnt--;
        }
        prev = c;
    }
    printf("%d\n", sum);
}


*/