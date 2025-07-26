bool is_prime(int n) {
    if (n < 2) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool isSpecialNumber(int n) {
    // Write your code 
    int sum = 0;
    int digits = 0;
    int temp = n;
    while (temp != 0) {
        sum += (temp % 10);
        temp /= 10;
    }
    return is_prime(n) && is_prime(sum);
}