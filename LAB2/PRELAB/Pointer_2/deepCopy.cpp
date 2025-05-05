//Code nay co van de
int** deepCopy(int** matrix, int r, int c) 
{
    if (r <= 0 || c <= 0 || matrix == nullptr)
    {
        return nullptr;
    }
    
    int ** newArr = new int * [r];

    for (int i = 0; i < r; i++)
    {
        newArr[i] = new int [c];
    }
    
    newArr = matrix;
    return newArr;
}