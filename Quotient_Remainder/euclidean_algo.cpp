#include <iostream>
#include <string>
#include<bits/stdc++.h>

/*
compute half by binary operation
eg. 5 >> 1 = 2 with remainder left 
*/
template <typename I>
I half(I a){
  return a >> 1;
}

template <typename integer, typename line_segment>
line_segment largest_doubling(line_segment a, line_segment b) { 
  // precondition: b != 0
  while (a - b >= b) b = b + b;
  return b;
}

template <typename integer, typename line_segment>
std::pair<integer, line_segment> quotient_remainder(line_segment a, line_segment b) { 
    // Precondition: b > 0
    if (a < b) return {integer(0), a};
    line_segment c = largest_doubling<integer, line_segment>(a, b);
    integer n(1);
    a = a - c; while (c != b) {
        c = half(c); n = n + n;
    if (c <= a) { a = a - c; n = n + 1; } }
    return {n, a}; 
}

/*
compute extended euclidean algorithm.
given a and b, compute x and y so that
ax + by = gcd(a,b)
returns x, y, gcd(a,b), a/gcd(a,b), b/gcd(a,b)
*/
template <typename PID>
std::tuple<PID, PID, PID, PID, PID> extended_euclidean(const PID& a, const PID& b) {
    // TODO: check if a or b is 0.
    // if (a == 0) {
    //
    //     return std::tie(old_s, old_t, old_r, t, s); // x, y, gcd, a/gcd, b/gcd
    // } else if (b == 0) {
    //
    // }

    PID s(0), old_s(1);
    PID t(1), old_t(0);
    PID r(b), old_r(a);

    int i = 0;
    while (r != 0) {
        i++;
        // division without remainder i.e., get quotient
        PID quotient = old_r / r; 

        PID tmp = old_r;
        // update r_{i-1}
        old_r = r; 
        // update r_{i}
        r = tmp - quotient * r; // new remainder 

        tmp = old_s;
        old_s = s; // update s_{i-1}
        s = tmp - quotient * s; // update s_{i}

        tmp = old_t;
        old_t = t;
        t = tmp - quotient * t;
    }

    // correct sign of division by gcd
    if ((i & 1)) {t = -t;} // i is odd
    if (!(i & 1)) {s = -s;} // i is even

    return std::tie(old_s, old_t, old_r, t, s); // x, y, gcd, a/gcd, b/gcd
}




int main()
{
  // Function in book
  std::pair<int, int> p = quotient_remainder<int, int>(20,7);
  std::cout << "Values returned by Pair: ";
  std::cout << "Quotient: "<<p.first << "Remainder: " << p.second<<'\n';

  // Function written by Brad
  int x, y, gcd, a_gcd, b_gcd;
  std::tie(x, y, gcd, a_gcd, b_gcd) = extended_euclidean<int>(20,7);
  std::cout << "Values returned by tuple: ";
  std::cout << x << " " << y << " " << gcd << std::endl;
  return 0;
}