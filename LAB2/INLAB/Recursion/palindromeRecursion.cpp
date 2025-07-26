string boolToString(bool value) {
    if (value) return "true";
    else return "false";
}

bool palindromeRecursion(string s)
{
    // BEGIN YOUR IMPLEMENTATION [1]
    // TODO
    // END YOUR IMPLEMENTATION [1]
    int size = s.size();
    if (s[0] != s[size - 1]) return false;
    if (size == 1 or size == 2) return true;
    return palindromeRecursion(s.substr(1, size - 2));
}

int main()
{
    hiddenCheck();
    // BEGIN YOUR IMPLEMENTATION [2]
    // TODO
    while (true) {
        string line;
        getline(cin, line);
        if (line[0] == '*') {
            break;
        }
        cout<<boolToString(palindrome(line))<<' '<<boolToString(palindromeRecursion(line))<<endl;
        
    }
    // END YOUR IMPLEMENTATION [2]
    return 0;
}