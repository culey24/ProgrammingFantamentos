int findMax(int *ptr, int n)
{
    int max = *ptr;
    for (int i = 1; i < n; i++) {
        if (*(ptr + i) > max) max = *(ptr + i);
    }
    return max;
}