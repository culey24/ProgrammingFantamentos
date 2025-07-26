void addElement(int*& arr, int n, int val, int index) {
    // TODO
    int* newArr = new int[n + 1];
    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }
    newArr[index] = val;
    for (int i = index + 1; i < n + 1; i++) {
        newArr[i] = arr[i - 1];
    }
    delete[] arr;
    arr = newArr;
} 
