#include <iostream>
#include <vector>
using namespace std;
int main()
{
    // Declaring a vector
    vector<bool> v = { true, false, true };
    cout << "size of bool is :" << sizeof(bool) << " bytes\n";
    // Declaring an iterator
    vector<bool>::iterator i;
    

    //cout << i[0] << '\n';

    int j;
  
    cout << "Without iterators = ";
      
    // Accessing the elements without using iterators
    for (j = 0; j < 3; ++j) 
    {
        cout << v[j] << " ";
    }
  
    cout << "\nWith iterators = ";
      
    // Accessing the elements using iterators
    for (i = v.begin(); i != v.end(); ++i)
    {
        cout << *i << " ";
    }
  
    // Adding one more element to vector
    v.push_back(4);
  
    cout << "\nWith iterators = ";
      
    // Accessing the elements using iterators
    for (i = v.begin(); i != v.end(); ++i) 
    {
        cout << *i << " ";
    }
    cout << "\n";
    return 0;
}