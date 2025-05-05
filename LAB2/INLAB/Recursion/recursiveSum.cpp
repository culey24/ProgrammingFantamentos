int recursiveSum(int arr[], int size) {
    // TODO
    if (size == 0) return 0;
    return arr[0] + recursiveSum(arr + 1, size - 1);
}