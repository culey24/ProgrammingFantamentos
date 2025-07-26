// Student may implement another function as need

void reverse(char str[]) {
    // TODO
    if (!str) { 
        return;
    }
    int str_length = strlen(str);
    int left_idx = 0;
    int right_idx = str_length - 1;
    while (left_idx < right_idx) {
        swap(str[left_idx], str[right_idx]);
        left_idx++;
        right_idx--;
    }
    return;
}