#include "vector.h"

using namespace meowdada;

vector<int> return_rvalue(vector<int> temp)
{
    return temp;
}

int main()
{
    vector<int> vec1 { 1, 2, 3 };           // constructed by initializer_list
    vector<int> vec2 ( { 1, 2, 3, 4} );     // constructed by initializer_list
    vector<int> vec3 = { 1, 2, 3 };         // constructed by initializer_list
    vector<int> vec4 = vec1;                // copy constructor
    vector<int> vec5(vec2);                 // copy constructor
    vector<int> vec6(std::move(vec3));      // move constructor

    vector<int> vec = { 1, 2, 3, 4, 5, 6 };
    vec.dump();
    vec.push_back(5);     // { 1, 2, 3, 4, 5 ,6 ,5 }
    vec.push_back(6);     // { 1, 2, 3, 4, 5, 6, 5, 6 }
    vec.push_front(-2);   // { -2, 1, 2, 3, 4, 5, 6, 5, 6 }
    vec.push_front(-6);   // { -6, -2, 1, 2, 3, 4, 5, 6, 5, 6 }
    vec.dump();

    vec.pop_front();      // { -2, 1, 2, 3, 4, 5, 6, 5, 6 }
    vec.pop_front();      // { 1, 2, 3, 4, 5, 6, 5, 6 }
    vec.pop_back();       // { 1, 2, 3, 4, 5, 6, 5 }
    vec.pop_front();      // { 2, 3, 4, 5, 6, 5 }
    vec.dump();

    std::sort(vec.begin(), vec.end());  // { 2, 3, 4, 5, 5, 6 }
    vec.dump();

    std::cout << "vec[3] = " << vec[3] << std::endl;  // vec[3] = 5

    return 0;
}