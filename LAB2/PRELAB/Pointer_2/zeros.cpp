int* zeros(int n) {
    // TODO
    if (n <= 0) return nullptr;
    int* result = new int[n];
    for (int i = 0; i < n; i++) {
        result[i] = 0;
    }
    return result;
}