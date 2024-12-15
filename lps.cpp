#include <iostream>
#include <vector>
using namespace std;

vector<int> makeLps(string str) {
    int n = str.length();
    vector<int> ans(n);
    ans[0] = 0; // First element of LPS array is always 0
    int i = 1;
    int len = 0;

    while (i < n) {
        if (str[i] == str[len]) {
            len++;
            ans[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = ans[len - 1];
            } else {
                ans[i] = 0; // If len == 0, set LPS[i] to 0
                i++;
            }
        }
    }
    return ans;
}

int main() {
    string str = "aaacaaaa";
    vector<int> lps = makeLps(str);
    for (auto i : lps) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}
