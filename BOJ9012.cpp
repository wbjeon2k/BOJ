#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
#include <stack>
#include <string>

using namespace std;


bool chk(string input) {
    stack<char> pstack;

    for (int j = 0; j < input.size(); ++j) {

        if (input[j] == '(') {
            pstack.push('(');
        }
        else {
            if (pstack.empty()) {
                return false;
                break;
            }
            else {
                pstack.pop();
            }
        }
    }

    if (!pstack.empty()) {
        return false;
    }
    else {
        return true;
    }
}

int main()
{
    

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        string input;
        cin >> input;

        if (chk(input)) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}
