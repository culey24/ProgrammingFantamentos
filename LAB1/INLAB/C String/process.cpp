// Student may implement another function as need

void process(char str[], char outstr[]) {
    // TODO
    if (!str) return;
    int outstr_count = 0;
    int str_len = strlen(str);
    int initial_idx = 0;
    while (str[initial_idx] == ' ') {
        initial_idx++;
    }
    int final_idx = str_len - 1;
    while (str[final_idx] == ' ') {
        final_idx--;
    }
    bool onespace = false;
    for (int i = initial_idx; i <= final_idx; i++) {
        if (str[i] != ' ') {
            outstr[outstr_count++] = str[i];
            onespace = false;
        }
        else {
            if (!onespace) {
                outstr[outstr_count++] = ' ';
                onespace = true;
            }
            else {
                continue;
            }
        }
    }
    outstr[outstr_count] = '\0';
}