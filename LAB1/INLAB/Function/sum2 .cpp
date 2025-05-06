void sum2(int * array, int numEls, int &result)
{
    // TODO
    if (!array) {
        return;
    }
    
    int sum = 0;
    for (int i = 0; i < numEls; i++) {
        sum += array[i];
    }
    result = sum;
    return;
}