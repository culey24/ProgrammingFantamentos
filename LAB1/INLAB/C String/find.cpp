// Student may implement another function as need

int find(char str[], char substr[]) {
    // TODO
    if (!str || !substr) return -1;
    int str_len = strlen(str);
    int substr_len = strlen(substr);
    if (str_len < substr_len) return -1;
    for (int i = 0; i <= str_len - substr_len; i++) {
        bool isContain = true;
        for (int j = 0; j < substr_len; j++) {
            if (str[i + j] != substr[j]) {
                isContain = false;
            }
        }
        if (isContain) {
            return i;
        }
    }
    return -1;
}