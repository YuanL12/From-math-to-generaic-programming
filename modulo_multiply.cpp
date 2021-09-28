#include <iostream>
#include <string>
#include<cmath>

#define Integer typename

// modulo structure used to do  modulo multiplication
template <Integer I>
struct modulo_multiply {
    I modulus;
    modulo_multiply(const I& i) : modulus(i) {}

    // compute n * m mod modulus
    I operator() (const I& n, const I& m) const {
        return (n * m) % modulus;
    } 
};


// Function to compute m mod a
template <Integer I>
I mod(std::string m, int a)
{   
    std::string s_m = std::to_string(m);
    // Initialize result
    I res = 0;
 
    // One by one process all digits of 'num'
    for (int i = 0; i < s_m.length(); i++){
        // std::cout << (int)num[i] - '0' << std::endl;
        res = (res * 10 + (int)s_m[i] - '0') % a;
    }
    return res;
}

// Function to compute n * m (mod a)
template <Integer I>
I multiply_mod(I n, I m, I a)
{
    std::string s_m = std::to_string(m);
    // Initialize result
    I res = 0;
    size_t power = 0;

    for (auto iter = s_m.end()-1; iter >= s_m.begin(); iter--){
        I m_digit = (I)*iter - '0';
        
        int tenth = std::pow(10,power);
        std::cout << "m_digit = "<< m_digit << std::endl;
        std::cout << "tenth = "<< tenth << std::endl;
        res = (n * m_digit * tenth + res) % a;
        std::cout << "res = "<< res << std::endl;
        power++;
    }

    return res;
}
 


// Returns (a * b) % mod
long long moduloMultiplication(long long a,
                            long long b,
                            long long mod)
{
    long long res = 0; // Initialize result
 
    // Update a if it is more than
    // or equal to mod
    a %= mod;
 
    while (b)
    {
        // If b is odd, add a with result
        if (b & 1)
            res = (res + a) % mod;
 
        // Here we assume that doing 2*a
        // doesn't cause overflow
        a = (2 * a) % mod;
 
        b >>= 1; // b = b / 2
    }
 
    return res;
}
 

int main(int argc, char const *argv[])
{
    
    std::string num = "12345678";
    std::cout << moduloMultiplication(810000, 810000, 2364059) << std::endl;
    // int a = std::stoi(num); // string to int 
    // std::cout <<  mod<int>(num, 10) << std::endl;

    // for (auto iter = num.end()-1; iter >= num.begin(); iter--){
    //     int m_digit = (int)*iter - '0';
    //     std::cout << m_digit << std::endl;
    // }

    // int to string 
    // std::string s = std::to_string(42);
    // std::cout << s << std::endl;
    return 0;
}
