void replaceString(string s, string s1, string s2){
    //TO DO
    int s1_idx = s.rfind(s1);
    if (s1_idx != string::npos) {
        s.replace(s1_idx, s1.length(), s2);
        cout<<s;
    }
    else {
        cout<<s;
    }
}