#include <iostream>
using namespace std;

template <typename T>
void addItems(T lo, T hi, T step)
{
    T i = lo;
    while (i <= hi)
    {
        cout << i << "\n";
        i += step;
    }
};

int main(int argc, char const *argv[])
{
    addItems<int>(1, 12, 1);
    return 0;
}
