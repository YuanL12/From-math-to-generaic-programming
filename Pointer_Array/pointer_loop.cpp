#include <array>
#include <cstddef>
#include <iostream>
 
int main()
{
  // The type is automatically deduced to std::array<int, 7> (Requires C++17).
  // Use the type std::array<int, 7> if your compiler doesn't support C++17.
  std::array<int, 7>  data{ 0, 1, 2, 3, 4, 5, 6 };
  std::size_t length{ data.size() };
 
 
  // for-loop with pointer (Note: ptr can't be const, because we increment it)
  for (auto ptr{ &data[0] }; ptr != (&data[0] + length); ++ptr)
  {
    std::cout << ptr << ' ';
    std::cout << *ptr << '\n';
  }

  std::cout << "The substraction of pointer or iterators: \n" ;
  std::cout << &data[1] - &data[0]<< '\n'; // number of elements of that type (int) or distance
  return 0;
}