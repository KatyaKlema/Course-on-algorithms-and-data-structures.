#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool Zfunc(const string& s, string& prefix, int len) {
    vector<int> z(s.size(), 0);
    z[0] = s.size();
    int cur_zero = len + 1;
    int cur_i = cur_zero;
    for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
        z[i] = max(0, min(r - i, z[i - l]));
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
        if (i >= len + 1 && i > cur_zero) {
            return false;
        }
        else if (i >= len + 1 && i + z[i] >= cur_zero) {
            if (i > len + 1) {
                for (int j = cur_i; j < i; j++) {
                    prefix += s[j];
                }
                if (cur_i < i) {
                    prefix += ' ';
                }
            }
            cur_zero = i + z[i];
            cur_i = i;
        }
    }
    if (cur_zero < s.size()) {
        return false;
    }
    for (int j = cur_i; j < s.size(); ++j) {
        prefix += s[j];
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string S, T, sum, prefix;
    cin >> S >> T;
    sum = S + '0' + T;
    bool ind = Zfunc(sum, prefix, S.size());
    if (ind) {
        cout << "No" << endl << prefix << endl;
    }
    else {
        cout << "Yes" << endl;
    }
    return 0;
}