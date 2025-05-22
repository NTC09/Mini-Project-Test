int mySqrt(int num) {
    float temp, sqrt;
    int number;
    number = num;
    sqrt = number / 2;
    temp = 0;

    // It will stop only when temp is the square of our number
    while (sqrt != temp) {
        // setting sqrt as temp to save the value for modifications
        temp = sqrt;

        // main logic for square root of any number (Non Negative)
        sqrt = (number / temp + temp) / 2;
    }
    return (sqrt);
}

int log2(int n) {
    if (n == 0)  // throw ...
    {
        // Here we have error
        // you can use exception to handle this error or return Zero
        throw("Opps");
    }
    int logValue = -1;
    while (n) {  //
        logValue++;
        n >>= 1;
    }
    return logValue;
}