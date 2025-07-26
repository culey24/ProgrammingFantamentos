#include <iostream>
#include <string>

using namespace std;

bool isRepeatedString(string s, int start_idx, int end_idx) {
    for (int i = start_idx; i < end_idx + 1; i++) {
        for (int j = i + 1; j < end_idx + 1; j++) {
            if (s[i] == s[j]) return true;
        }
    }
    return false;
}

int longestNonRepeatSubString(string s) {
    // TO DO 
    int maxLen = 1;
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            if (!isRepeatedString(s, i, j) && (j - i + 1 > maxLen)) {
                maxLen = j - i + 1;
            }
        }
    }
    return maxLen;
}

int main()  {
    string s;
    cin >> s;
    cout << longestNonRepeatSubString(s);
    return 0;
}