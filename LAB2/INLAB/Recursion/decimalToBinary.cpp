long int decimalToBinary(int decimal_number)
{
	/*
	* STUDENT ANSWER
	*/
    if (decimal_number == 0) return 0;
    return (decimal_number % 2) + 10*decimalToBinary(decimal_number / 2);
}