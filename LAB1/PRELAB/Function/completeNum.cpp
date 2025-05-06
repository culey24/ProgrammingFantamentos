bool completeNum(int N)
{
    // TODO
    int sum = 0;
    for (int i = 1; i < N; i++) {
        if (N % i == 0) {
            sum += i;
        }
    }
    return N == sum;
}