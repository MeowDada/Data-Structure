#include "vector.h"

using namespace meowdada;

int main()
{
    vector<int> vec = vector<int>();
    vec.push_front(1);
    vec.dump();
    vec.push_back(2);
    vec.dump();
    vec.push_front(3);
    vec.dump();
    vec.push_back(4);
    vec.dump();
    vec.push_back(5);
    vec.dump();
    vec.push_back(6);
    vec.dump();
    vec.pop_front();
    vec.dump();
    vec.pop_front();
    vec.dump();
    vec.pop_back();
    vec.dump();
    vec.pop_back();
    vec.dump();
    vec.push_back(3);
    vec.dump();
    vec.push_back(4);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(3);

    std::sort(vec.begin(), vec.end());

    auto print = [](const int& val) { std::cout << " " << val; };
    std::for_each(vec.begin(), vec.end(), print);
    std::cout << std::endl;

    std::cout << vec[2] << std::endl;

    return 0;
}