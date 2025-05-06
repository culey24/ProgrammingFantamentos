#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string s) {
    int left_idx = 0;
    int right_idx = s.length() - 1;
    while (left_idx < right_idx) {
        if (s[left_idx] != s[right_idx]) {
            return false;
        }
        left_idx++;
        right_idx--;
    }
    return true;
}

bool checkPalindrome(string s, int left_idx, int right_idx) {
    while (left_idx < right_idx) {
        if (s[left_idx] != s[right_idx]) {
            return false;
        }
        left_idx++;
        right_idx--;
    }
    return true;
}

int main()  {
    // TODO
    string s;
    getline(cin, s);
    int maxLen = 1;
    int substrIndex = 0;
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            if (checkPalindrome(s,i,j) && (j - i + 1) > maxLen) {
                substrIndex = i;
                maxLen = j - i + 1;
            }
        }
    }
    cout<<s.substr(substrIndex, maxLen);
    return 0;
}