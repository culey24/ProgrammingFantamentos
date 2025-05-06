void findAllIndex(string s1, string s2){
    // TO DO
    if (s1.empty() || s2.empty()) {
        cout<<-1;
        return;
    }
    char s2_first_char = s2[0];
    int index = s1.find(s2_first_char);
    if (index != string::npos) {
        cout<<index;
        index = s1.find(s2_first_char, index + 1);
    }
    else {
        cout<<-1;
        return;
    }
    while (index != string::npos) {
        cout<<' '<<index;
        index = s1.find(s2_first_char, index + 1);
    }
    return;
}