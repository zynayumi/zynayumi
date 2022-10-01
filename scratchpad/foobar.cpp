#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct data_
{
    vector<const char *> str;
};

unordered_map<int, data_> myData{
    {42, {{"hello", "world"}}},
    {69, {{"what", "the hecc"}}}};

int main()
{
   for (auto &&i : myData)
   {
       for (auto &&f : i.second.str)
       {
           cout << f << endl;
       }
   }
}
