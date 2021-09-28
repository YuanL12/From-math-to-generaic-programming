#pragma once

#include<iostream>
#include <random>
#include <chrono>
#include <vector>
#include <tuple>

#define Integer typename
#define EuclideanDomain typename
#define Regular typename
#define SemigroupOperation typename

template <typename I>
I half(I a){
  return a >> 1;
}

template <typename I>
bool odd(I n)
{
    return n & 0x1;
}


template <typename integer, typename line_segment>
line_segment largest_doubling(line_segment a, line_segment b) { 
    // precondition: b != 0
    while (a - b >= b) b = b + b;
    return b;
}

// coumpute the quotient and remainder of a and b
// return 
// 1) quotient 
// 2) remainder
template <typename integer, typename line_segment>
std::pair<integer, line_segment> quotient_remainder(line_segment a, line_segment b) { 
    // Precondition: b > 0
    if (a < b) return {integer(0), a};
    line_segment c = largest_doubling<integer, line_segment>(a, b);
    integer n(1);
    a = a - c; 
    while (c != b) {
        c = half(c); n = n + n;
        if (c <= a) { a = a - c; n = n + 1; } 
    }
    return {n, a}; 
}


// find the greate common divisor of a and b
// return
// 1) the value of x in Bezout's identity: x*a + y*b = gcd(a,b)
// 2) gcd(a,b)
template <EuclideanDomain E>
std::pair<E, E> extended_gcd(E a, E b) {
    E x0(1);
    E x1(0);
    while (b != E(0)) {
        // compute new r and x
        std::pair<E, E> qr = quotient_remainder<E,E>(a, b); 
        E x2 = x0 - qr.first * x1;
        // shift r and x
        x0 = x1;
        x1 = x2;
        a = b;
        b = qr.second;
    }
    return {x0, a};
}

// compute the multiplicative inverse of a in Z mod n
template <Integer I>
I multiplicative_inverse(I a, I n) {
    std::pair<I, I> p = extended_gcd(a, n);
    if (p.second != I(1)) return I(0);
    if (p.first < I(0)) return p.first + n;
    return p.first;
}


// compute the r * a^n
template <Regular A, Integer N, SemigroupOperation Op> // requires (Domain<Op, A>)
A power_accumulate_semigroup(A r, A a, N n, Op op) {
    // precondition(n >= 0);
    if (n == 0) return r;
    while (true) {
        if (odd(n)) {
            r = op(r, a);
            if (n == 1) return r;
        }
        n = half(n);
        a = op(a, a); 
    }
}

// compute a^n with the group operation Op
template <Regular A, Integer N, SemigroupOperation Op> // requires (Domain<Op, A>)
A power_semigroup(A a, N n, Op op) {
    // precondition(n > 0);
    while (!odd(n)) { // if n is even 
        a = op(a, a);
        n = half(n);
    }
    if (n == 1) return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
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

// modulo structure used to do modulo multiplication
template <Integer I>
struct modulo_multiply{
    I modulus;
    modulo_multiply(const I& i) : modulus(i) {}

    // compute n * m mod modulus
    I operator() (const I& n, const I& m) const {
        return moduloMultiplication(n, m, modulus);
    } 
};

template <Integer I>
I identity_element(const modulo_multiply<I>&) {
    return I(1);
}

// Miller Rabin test to check if a number n is prime 
// n - 1 = 2^k * q
// input: 
// (1) the number to test: n (should be odd, otherwise is trivial, since 2 is a divisor)
// (2) factor out q and k in the expression: n - 1 = 2^k * q
// (3) a randomly choosen witness number w
// return: true if n is probably a prime number, false if n is definitely not
template <Integer I>
bool miller_rabin_test(I n, I q, I k, I w) {
    
    // precondition n>1 and n−1 = 2^k * q and q is odd
    modulo_multiply<I> mmult(n);
    I x = power_semigroup(w, q, mmult);
    if (x == I(1) || x == n - I(1)) return true; 
    for (I i(1); i < k; ++i) {

        x = mmult(x, x);
        if (x == n - I(1)) return true; 
        if (x == I(1)) return false;
    }
    return false;
}

// compute the 2 factorization of a even number 
// a =  2^k * q, where q is odd
// return q and k
template <EuclideanDomain E>
std::pair<E, E> factor_2(E a) {
    E k(0);
    while(!odd(a)){ // if a is even continue
        a = half(a);
        k++;
    }
    
    return {a, k};
}

// Miller Rabin test to check if a number n is prime 
// we will test 2, 3, 5, 7, 11, 13, and 17.
// input: 
// (1) the number to test: n (should be odd, otherwise is trivial, since 2 is a divisor)
// return: true if n is a prime number
template <Integer I>
bool miller_rabin_test_general(I n) {
    
    // precondition n>1 and n−1 = 2^k * q and q is odd
    auto factor_result = factor_2(n-1);
    I q = factor_result.first;
    I k = factor_result.second;
    // return miller_rabin_test(n, q, k, I(150));
    std::vector<I> witness_candidates = {2, 3, 5, 7, 11, 13,17};
    // assume it is prime at first, 
    // since miller_rabin_test is always correct when n is not prime
    bool test_result = true;   
    for (auto& wit_number: witness_candidates){ 
        // if there is only once fail, then n is not prime
        if(!miller_rabin_test(n, q, k, wit_number)){ 
            test_result = false;
            break;
        }
    }
    return test_result;
}

template <Integer I>
I random_number() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1000,5000);

    return distribution(generator);
}

template <Integer I>
I random_number(const int& start_point, const int& end_point) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(start_point,start_point);

    return distribution(generator);
}

template <Integer I>
I random_prime_number() {
    while(true){
        I number = random_number<I>(); 
        if(miller_rabin_test_general(number)){
            return number;
        }
    }
}

template <EuclideanDomain E>
std::tuple<E, E, E> RSA_generation() {
    E n; // product of p1 and p2
    E pub_key = random_number<E>();
    E prv_key;
    
    E p1 = random_prime_number<E>();
    E p2 = random_prime_number<E>();
    n = p1*p2;
    E euler_func = (p1-1)*(p2-1);

    // start generating a random public key and 
    // stop when public key is coprime with the Euler function
    while (extended_gcd(pub_key, euler_func).second != E(1)) {
        pub_key = random_number<E>();
    }
    

    prv_key = multiplicative_inverse(pub_key, euler_func);

    return {n, pub_key, prv_key};
}

template <class E>
class RSA_generation_lib
{
private:
    E p1; // two prime numbers p1 and p2
    E p2;
public:
    E n; // product of p1 and p2
    E pub_key; // public key 
    E prv_key; // private key
    E euler_func; // euler function of n

    RSA_generation_lib(){
        // generate two prime random numbers
        p1 = random_prime_number<E>();
        p2 = random_prime_number<E>();
        // set the values of n and euler function number
        n = p1*p2; 
        euler_func = (p1-1)*(p2-1);

        // start generating a random public key and 
        // stop when public key is coprime with the Euler function
        pub_key = random_number<E>();
        while (extended_gcd(pub_key, euler_func).second != E(1)) {
            pub_key = random_number<E>();
        }

        // compute the private key
        prv_key = multiplicative_inverse(pub_key, euler_func);
    }
    
    // return n
    E get_n(){
        return n;
    }

    // compute the encoded message by powering them
    E encode(E message){
        return power_semigroup(message, pub_key, modulo_multiply<E>(n));
    }

    // compute the decoded message by powering them
    E decode(E message){
        // E result = power_semigroup(message, RSA_info.prv_key, modulo_multiply<E>(RSA_info.n));
        return power_semigroup(message, prv_key, modulo_multiply<E>(n));
    }
};
