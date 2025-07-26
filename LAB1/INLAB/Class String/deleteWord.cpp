void deleteWord(string s, string s1){
    //TO DO
    int index = 0;
    while((index = s.find(s1)) != string::npos) {
        s.replace(index, s1.length(), "");
    }
    cout<<s;
}