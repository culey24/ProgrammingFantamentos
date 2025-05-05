bool isSymmetry(int *head, int *tail)
{
    int start_idx = 0;
    int end_idx = tail - head;
    while (start_idx < end_idx) {
        if (*(head + start_idx) != *(head + end_idx)) return false;
        start_idx++;
        end_idx--;
    }
    return true;
}