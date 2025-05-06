void cutString(string s, int index){
    // TO DO
    int len = s.length();
    if (index < 0 || index >= len) return;
    cout<<s.substr(index)<<endl;
}