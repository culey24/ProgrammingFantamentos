int findOccurrences(int nums[], int size, int element) {
    // TODO:
    if (size == 0) return 0;
    if (nums[0] == element) return 1 + findOccurrences(nums + 1, size - 1, element);
    else return findOccurrences(nums + 1, size - 1, element);
}