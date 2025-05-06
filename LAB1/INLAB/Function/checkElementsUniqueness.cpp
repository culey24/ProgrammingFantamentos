bool checkElementsUniqueness(int* arr, int n) {
    // Write your code 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i ==j) {
                continue;
            }
            if (arr[i] == arr[j]) {
                return false;
            }
        } 
    }
    return true;
}