bool isPalindrome(const char* str) {
    // Write your code here
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    int left_index = 0;
    int right_index = len - 1;
    while(left_index < right_index) {
        if (str[left_index] != str[right_index]) {
            return false;
        }
        left_index++;
        right_index--;
    }
    return true;;
}