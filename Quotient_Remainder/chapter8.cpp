#include <iostream>
#include <vector>

#define InputIterator typename
#define Semiring typename

template <InputIterator I, Semiring R>
R polynomial_value(I first, I last, R x) {
    if (first == last) return R(0);
    R sum(*first);
    while (++first != last) {
        sum *= x;
        sum += *first;
    }
return sum; }

// using polynomial<real> = int;
// polynomial<real> gcd(polynomial<real> a, polynomial<real> b) {
//     while (b != polynomial<real>(0)) {
//         a = remainder(a, b);
//         std::swap(a, b);
//     }
// return a; }

int main()
{
    //ploynomial multiplication
    //eg., 4x^4+7x^3−x^2+27x−3 = (((4x+7)x−1)x+27)x−3
    //Horner's rule: nerver have to multiply powers of x higher than 1
    std::vector<int> polynomial_coefficient = {4,7,-1,27,3};
    double x = 1.0; 
    double f_x = polynomial_value(polynomial_coefficient.begin(),polynomial_coefficient.end(), 1); 
    std::cout << f_x << std::endl;
    
    

    //std::cout << 1 << std::endl;
    return 0;
}
