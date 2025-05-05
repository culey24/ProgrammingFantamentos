void swap(int *ptr1, int *ptr2)
{
    int temp = *(ptr1);
    *(ptr1) = *(ptr2);
    *(ptr2) = temp;
}