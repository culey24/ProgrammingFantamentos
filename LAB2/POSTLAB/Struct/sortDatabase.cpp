void swapSCP(SCP*& A, SCP*& B) {
    SCP* temp = A;
    A = B;
    B = temp;
    return;
}

SCP** sortDatabase(SCP** arr, int n) {
    // Student answer
    SCP** newArr = new SCP*[n];
    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (newArr[j]->id > newArr[j + 1]->id) {
                swapSCP(newArr[j], newArr[j + 1]);
            }
        }
    }
    return newArr;
}