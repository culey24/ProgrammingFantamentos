int calculate_power(int n, int e) 
{ 
    /*  
     * STUDENT ANSWER
     */
    if (e == 0) return 1;
    return n * calculate_power(n, e - 1);
}