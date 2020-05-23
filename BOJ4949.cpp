#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
#include <stack>
#include <string>

using namespace std;

char input[150];

bool chk(int l) {
    stack<char> pstack;

    for (int j = 0; j < l; ++j) {

        if (input[j] == '(') {
            pstack.push('(');
        }
        else if (input[j] == '[') {
            pstack.push('[');
        }
        else if(input[j] == ']' || input[j] == ')') {
            if (pstack.empty()) {
                return false;
                break;
            }

            if (input[j] == ']' && pstack.top() != '[') {
                return false;
            }
            else if (input[j] == ')' && pstack.top() != '(') {
                return false;
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

    while(1) {
        memset(input, 0, sizeof(input));
        fgets(input, 110, stdin);
        int l = strlen(input);

        if (input[0] == '.') break;

        if (chk(l)) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }

    return 0;
}
