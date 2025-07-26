bool is_lower(char ch) {
    return ch >= 'a' && ch <= 'z';
}

string to_upper(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (is_lower(s[i])) {
            result += s[i] + 'A' - 'a';
        }
        else {
            result += s[i];
        }
    }
    return result;
}

void uppercase(string output)   {
    // TODO
    string user_input;
    getline(cin, user_input);
    
    ofstream file(output);
    file<<to_upper(user_input);
    return;
}