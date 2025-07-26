void reverse(int *ptr, int n) {
    int left_idx = 0;
    int right_idx = n - 1;
    while (left_idx < right_idx) {
        int temp = *(ptr + left_idx);
        *(ptr + left_idx) = *(ptr + right_idx);
        *(ptr + right_idx) = temp;
        left_idx++;
        right_idx--;
    }
}