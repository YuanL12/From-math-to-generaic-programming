#include <iostream>

#include <random>
#include <chrono>
#include <vector>
#include "include/RSA.hpp"
#include <tuple>

int main()
{
    // Function in book
    // std::pair<int, int> p = quotient_remainder<int, int>(20,7);
    // std::cout << "Values returned by Pair: ";
    // std::cout << "Quotient: "<< p.first << " Remainder: " << p.second<<'\n';
    

    // std::pair<int, int> results = extended_gcd<int>(20,7);
    // std::cout << "Values returned by tuple: ";
    // std::cout << "x = "<< results.first << ", and gcd = " << results.second << std::endl;

    // auto inverse = multiplicative_inverse(5,8);
    // std::cout << "\ninverse is " << inverse << std::endl;

    // if(miller_rabin_test(2793, 349, 3, 150)){
    //     std::cout << 2793 << " is a prime number" << std::endl;
    // }else
    // {
    //     std::cout << 2793 << " is a not prime number" << std::endl;
    // }
    

    // results = factor_2(2792);
    // std::cout << "Values returned by tuple: ";
    // std::cout << "k = "<< results.first << ", and q = " << results.second << std::endl;
    // int test_number = 5099;
    // if(miller_rabin_test_general(test_number)){
    //     std::cout << test_number << " is a prime number" << std::endl;
    // }else{
    //     std::cout << test_number << " is not a prime number" << std::endl;
    // }

    // std::cout << "\na random prime number: "<< random_prime_number<int>() << std::endl;
    // for(size_t i = 1; i < 4; i++){
    //     std::cout << "perfom on i = "<< i<< std::endl;
    // }

    auto RSA_info = RSA_generation_lib<int>();
    std::cout << "n = "<< RSA_info.n << ", pub_key = "<< RSA_info.pub_key << ", prv_key = " << RSA_info.prv_key << std::endl;

    int message = 30;
    std::cout << "message is "<< message << std::endl;

    std::cout << "encoded message is "<< RSA_info.encode(message) << std::endl;    
    std::cout << "decoded message is "<<RSA_info.decode(RSA_info.encode(message)) << std::endl;   

    return 0;
}