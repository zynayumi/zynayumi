// type_info::name example
#include <iostream> // std::cout
#include <typeinfo>
#include <vector> // operator typeid

int main()
{
    std::vector<int> v{0, 1, 2, 3};
    int i;
    int *pi;
    std::cout << "int is: " << typeid(int).name() << '\n';
    std::cout << "  i is: " << typeid(i).name() << '\n';
    std::cout << " pi is: " << typeid(pi).name() << '\n';
    std::cout << "*pi is: " << typeid(*pi).name() << '\n';
    std::cout << "v[0] is: " << typeid(v[0]).name() << '\n';
    return 0;
}