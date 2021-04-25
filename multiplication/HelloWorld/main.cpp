#include <iostream>
#include "include/add.h"
// return a half of an integer 
int half(int n)
{
    return n >> 1;
}

// test if an integer is odd or not
bool odd(int n)
{
    return n & 0x1;
}

// multiplication of na
int multiply1(int a, int n)
{
    if (n == 1) return a;
    int result = multiply1(half(n), a+a);
    if (odd(n)) result = result + a;
    return result;
}

int main()
{
    int a{4};
    //std::cout << half(a) << '\n';
    //std::cout << odd(a) << '\n'; // bool true is 1 ,false is zero
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';

    return 0;
}