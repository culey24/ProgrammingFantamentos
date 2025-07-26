int gcdRecursion(int p, int q)
{
    // BEGIN YOUR IMPLEMENTATION [1]
    // TODO
    if (p == q) return p;
    else if (p > q) return gcdRecursion(p - q, q);
    else return gcdRecursion(p, q - p);
    // END YOUR IMPLEMENTATION [1]
    
}
int gcdIteration(int p, int q)
{
    // BEGIN YOUR IMPLEMENTATION [2]
    // TODO
    while (p != q) {
        if (p > q) p -= q;
        else if (p < q) q -= p;
    }
    return p;
    // END YOUR IMPLEMENTATION [2]
}