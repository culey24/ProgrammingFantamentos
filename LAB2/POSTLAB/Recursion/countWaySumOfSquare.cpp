int helpCount(int remainingSum, int base=1) {
    int result = base * base;
    if (remainingSum == result) return 1;
    if (remainingSum < result) return 0;
    return helpCount(remainingSum - result, base + 1) + helpCount(remainingSum, base + 1);
}

int countWaySumOfSquare(int x)
{
	/*
	* STUDENT ANSWER
	*/
	
	return helpCount(x);
}
