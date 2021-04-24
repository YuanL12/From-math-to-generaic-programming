#include <iostream>
#include<vector>
#define integer typename

using namespace std;
template <integer I, typename N>
void mark_sieve(I first, I last, N factor) {
// loop from the last one and add starting index by a factor
// until the last one.
*first = false;
while (last - first > factor) {
        //cout << last - first << '\n'; // iterator 相减相当于pointer相减
                                      // = distance or the number of elements
                                      // of that type
        first = first + factor;
        *first = false;
    }
}


template <typename I, typename N>
void sift0(I first, N n){
    fill(first, first + n, true);
    N i = 0;
    N index_square(3);
    while (index_square < n){
        if (first[i]){ // if p = 2i+3 is a prime
            mark_sieve(first + index_square, // start from the p*2
                        first + n, // last index of number n  
                        i+i+3); // factor
        }
        //cout << " iteration with i = "<< i<<" end \n";
        ++i;
        index_square = 2 * i * (i+3) +3 ;// 2*i^2 + 6*i + 3
    }
}

template <typename I, typename N>
void sift1(I first, N n){
    I last = first + n;
    fill(first, last, true);
    N i = 0;
    N index_square(3);
    N factor(3);

    while (index_square < n){
        if (first[i]){ // if p = 2i+3 is a prime
            mark_sieve(first + index_square, // start from the p*2
                        last, // last index of number n  
                        factor); // factor
        }
        ++i;
        factor = 2 * i + 3;
        index_square = 2 * i * (i+3) +3 ;// 2*i^2 + 6*i + 3
    }
}

template <typename I, typename N>
void sift(I first, N n){
    I last = first + n;
    fill(first, last, true);
    N i = 0;
    N index_square(3);
    N factor(3);
    
    while (index_square < n){
        if (first[i]){ // if p = 2i+3 is a prime
            mark_sieve(first + index_square, // start from the p*2
                        last, // last index of number n  
                        factor); // factor
        }
        ++i;
        index_square += factor;
        factor += 2; // 虽然将factor单独拎出来算，但是用加法能减少乘法的运算
        index_square += factor;// 2*i^2 + 6*i + 3
    }
}


int main()
{
    int n = 13; // n is the number of odd numbers or the length of vect
                // or the table size no the maximum value to sift m
    vector<bool> vect(n);
    vector<bool>::iterator iter;
    //vector<bool>::iterator first = vect.begin();
    sift1(vect.begin(), n);

    // print all prime numbers before 2n + 3
    cout << boolalpha;// replace bool varible 1/0 with true/false  

    cout << "Prime number in the ture/false list is: \n";
    for (iter = vect.begin(); iter != vect.end(); ++iter)
    {
        cout << *iter << ' ';
    }
    cout << '\n';

    cout << "Prime number before "<< 2*n+3 << " is: \n";
    for (int j = 0; j < n; ++j)
    {
        if (vect[j]){ cout << 2*j + 3 << ' ';}
    }
    cout << '\n';

    return 0;
    
}